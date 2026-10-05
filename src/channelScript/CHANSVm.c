#include "channelScript/CHANSVm.h"
#include "channelScript/CHANSVm/CHANSVmInternal.h"
#include "channelScript/CHANSVmPrivate.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <math.h>
#include <stdlib.h>

#include <private/sc.h>
#include <revolution.h>
#include <revolution/enc.h>
#include <revolution/net/NETMisc.h>
#include <revolution/net/NETDigest.h>

// TODO: Not yet in the SDK; holds 64-bit hash lengths, so it is 8-byte aligned
typedef struct {
    u64 work[0xD0 / sizeof(u64)];
} NETHMACContext;
extern const void* NETGetSHA1Interface(void);
extern void NETHMACInit(NETHMACContext* ctx, const void* interface, const void* key, u32 keyLen);
extern void NETHMACUpdate(NETHMACContext* ctx, const void* data, u32 len);
extern void NETHMACGetDigest(NETHMACContext* ctx, void* digest);
extern char VmReportFormat[];

#define CHANSVmDebugLength 1024
#define VM_FRAME_ARENA_SIZE 8192
#define VM_STRING_SIZE 128

CHANSVmImageCtorCallback VmImageCtorCallback = vmNull;
CHANSVmImageAllocatorCallback VmImageAllocCallback = vmNull;

vmBoolInt CHANSVmDebugVerboseMode = vmFalse;

#define VM_STR_LENGTH(str) (str * sizeof(vmWChar))

#define VM_ALIGNMENT DEFAULT_ALIGN
#define VM_ALIGNED(x) ((x & (VM_ALIGNMENT - 1)) == 0)
#define VM_ALIGN(x) ROUNDUP(x, VM_ALIGNMENT)
#define VM_ALIGN_DOWN(x) ROUNDDOWN(x, VM_ALIGNMENT)

const u64 VmNaN = 0x7FFFFFFFFFFFFFFFULL;
const u64 VmMinusZero = 0x8000000000000000ULL;
const u64 VmInf = 0x7FF0000000000000ULL;
const u64 VmMinusInf = 0xFFF0000000000000ULL;

#define VM_NAN *(f64*)&VmNaN
#define VM_NEG_ZERO *(f64*)&VmMinusZero
#define VM_INF *(f64*)&VmInf
#define VM_NEG_INF *(f64*)&VmMinusInf

#define VM_READ_BE_U16(b, o) ((u16)((b)[(o)] << 8 | (b)[(o) + 1]))
#define VM_READ_BE_U24(b, o) ((u32)((b)[(o)] << 16 | (b)[(o) + 1] << 8 | (b)[(o) + 2]))
#define VM_MAKE_U64(hi, lo) ((u64)(u32)(hi) << 32 | (u64)(lo))

void CHANSVmDebugPrintf(const vmString format, ...) {
    va_list args;
    char str[CHANSVmDebugLength];

    va_start(args, format);
    vsnprintf(str, CHANSVmDebugLength - 2, format, args);
    va_end(args);

    str[CHANSVmDebugLength - 1] = str[CHANSVmDebugLength - 2] = 0;

    OSReport(VmReportFormat, str);
}

#define CHANS_VM_PRINTF(line, msg, ...)                                                                                                              \
    if (CHANSVmDebugVerboseMode)                                                                                                                     \
    CHANSVmDebugPrintf("%s %d" msg, __FUNCTION__, line, __VA_ARGS__)
#define CHANS_VM_PRINT (line, msg, ...) if (CHANSVmDebugVerboseMode) CHANSVmDebugPrintf("%s %d" msg, __FUNCTION__, line)
#define CHANS_VM_PRINTF_CUSTOM(msg, ...)                                                                                                             \
    if (CHANSVmDebugVerboseMode)                                                                                                                     \
        CHANSVmDebugPrintf(msg, __VA_ARGS__);

vmU16 CHANSVmGetSourceLine(CHANSVm* vm) {
    CHANSVmExecutionCtx* ctx;
    CHANSVmModule* module;
    SrcLineEntry* lines;
    SrcLineEntry* entry;
    u32 pc;
    s32 lineOffset;
    u8 lastBit;
    u32 index;
    u8* bitfield;

    ctx = ((CHANSVmPrivate*)vm)->pActiveCtx;
    if (ctx == vmNull) {
        goto error;
    }
    module = ctx->pDbg;
    if (module == vmNull) {
        goto error;
    }
    lines = module->pLineTbl;
    if (lines == vmNull) {
        goto error;
    }
    pc = ctx->pc;
    if (pc >= module->codeSize) {
        goto error;
    }

    entry = &lines[pc / 256];
    lastBit = (u8)pc;
    lineOffset = entry->baseLine;
    bitfield = entry->bitfield;
    for (index = 0; index <= lastBit; index++) {
        if (bitfield[index / 8] & (128 >> (index & 7))) {
            lineOffset += 2;
        }
    }
    if ((u8*)lines + lineOffset + 1 < (u8*)module + module->regionSize) {
        u8* lineData = (u8*)lines + lineOffset;
        return VM_READ_BE_U16(lineData, 0);
    }
error:
    return 0;
}

vmPtr CHANSVmAllocFromGarbage(CHANSVm* vm, vmSize size) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;

    FreeBlock* allocBuf;
    FreeBlock* prevPtr;
    FreeBlock* ptr;
    vmU32 alignOff;
    vmU32 remaining;

    for (prevPtr = vmNull, ptr = pVm->pFreeList; ptr != vmNull; prevPtr = ptr, ptr = ptr->pNext) {
        alignOff = VM_ALIGN((vmU32)ptr) - (vmU32)ptr;
        if (ptr->size >= (size + alignOff)) {
            remaining = ptr->size - (size + alignOff);
            allocBuf = (vmPtr)((vmU32)ptr + alignOff);

            if (remaining < 8) {
                if (prevPtr == vmNull) {
                    pVm->pFreeList = ptr->pNext;
                } else {
                    prevPtr->pNext = ptr->pNext;
                }
            } else {
                ptr->size = remaining;
                if (prevPtr == vmNull) {
                    pVm->pFreeList = (FreeBlock*)((vmU32)allocBuf + size);
                    ((FreeBlock*)((vmU32)allocBuf + size))->pNext = ptr->pNext;
                    pVm->pFreeList->size = ptr->size;
                } else {
                    prevPtr->pNext = (FreeBlock*)((vmU32)allocBuf + size);
                    ((FreeBlock*)((vmU32)allocBuf + size))->pNext = ptr->pNext;
                    prevPtr->pNext->size = ptr->size;
                }
                ptr->size = ptr->size - size;
            }

            memset(allocBuf, 0, size);
            return allocBuf;
        }
    }
    return vmNull;
}

void CHANSVmUpdateSmallestFreeHeapSize(CHANSVm* vm) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;

    vmU32 freeHeapSize = (vmU32)pVm->pObjStackTopBuf - (vmU32)pVm->pFreeExeBuf;
    if (pVm->minFreeHeapSize <= freeHeapSize) {
        return;
    }
    pVm->minFreeHeapSize = freeHeapSize;
}

CHANSVmObjHdr* CHANSVmNewObjHdr(CHANSVm* vm, vmBoolInt noAlloc) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;
    CHANSVmObjHdr* object = vmNull;

    if (!noAlloc) {
        object = CHANSVmAllocFromGarbage(vm, VM_ALIGN(sizeof(CHANSVmObjHdr)));
    }

    if (object == vmNull) {
        vmU8* ptr = pVm->pFreeExeBuf;
        if ((vmU32)pVm->pObjStackTopBuf - (vmU32)ptr >= VM_ALIGN(sizeof(CHANSVmObjHdr))) {
            if (!noAlloc) {
                pVm->pFreeExeBuf = (ptr + VM_ALIGN(sizeof(CHANSVmObjHdr)));
                object = (CHANSVmObjHdr*)ptr;
            } else {
                ptr = pVm->pObjStackTopBuf - sizeof(CHANSVmObjHdr);
                pVm->pObjStackTopBuf = ptr;
                object = (CHANSVmObjHdr*)ptr;
            }

            CHANSVmUpdateSmallestFreeHeapSize(vm);
        }
    }

    if (object != vmNull) {
        memset(object, 0, sizeof(CHANSVmObjHdr));
    }

    return object;
}

vmPtr CHANSVmAlloc(CHANSVm* vm, vmSize size) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;
    vmU8* ptr;
    vmPtr result = vmNull;

    if (size != 0 && (size & 0x1F) == 0) {
        result = CHANSVmAllocFromGarbage(vm, size);

        if (result == vmNull) {
            ptr = pVm->pFreeExeBuf;
            if ((vmU32)pVm->pObjStackTopBuf - (vmU32)ptr >= size) {
                result = ptr;
                pVm->pFreeExeBuf = ptr + size;

                CHANSVmUpdateSmallestFreeHeapSize(vm);
                memset(ptr, 0, size);
            }
        }
    }

    return result;
}

void CHANSVmFree(CHANSVm* vm, vmPtr ptr, vmSize size) NO_INLINE {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;
    FreeBlock* head;
    FreeBlock* current;
    FreeBlock* buffer = ptr;

    if ((FreeBlock*)pVm->pHeapStart > buffer) {
        return;
    }
    if (buffer >= (FreeBlock*)pVm->pFreeExeBuf) {
        return;
    }
    if (size <= 8) {
        return;
    }

    memset(buffer, 0, size);
    buffer->size = size;

    head = pVm->pFreeList;
    if (head == vmNull) {
        pVm->pFreeList = buffer;
    } else if (buffer < head) {
        pVm->pFreeList = buffer;
        if ((FreeBlock*)((u32)buffer + buffer->size) == head) {
            buffer->pNext = head->pNext;
            buffer->size = buffer->size + head->size;
            memset(head, 0, sizeof(FreeBlock));
        } else {
            buffer->pNext = head;
        }
    } else {
        while ((current = head->pNext) != vmNull) {
            if (buffer < current) {
                if ((FreeBlock*)((u32)buffer + buffer->size) == current) {
                    buffer->pNext = current->pNext;
                    buffer->size = buffer->size + head->pNext->size;
                    memset(head->pNext, 0, sizeof(FreeBlock));
                } else {
                    buffer->pNext = current;
                }
                break;
            }
            head = current;
        }

        if ((FreeBlock*)((u32)head + head->size) == buffer) {
            head->pNext = vmNull;
            head->size = head->size + buffer->size;
            memset(buffer, 0, sizeof(FreeBlock));
        } else {
            head->pNext = buffer;
        }
    }

    while (pVm->pFreeList != vmNull) {
        current = vmNull;
        head = pVm->pFreeList;
        while (head->pNext != vmNull) {
            current = head;
            head = head->pNext;
        }

        if (pVm->pFreeExeBuf != (vmU8*)((u32)head + head->size)) {
            return;
        }

        memset(head, 0, sizeof(FreeBlock));
        pVm->pFreeExeBuf = (vmU8*)head;

        if (current == vmNull) {
            pVm->pFreeList = vmNull;
        } else {
            current->pNext = vmNull;
        }
    }
}

CHANSVmErr CHANSVmDeleteObject(CHANSVm* vm, CHANSVmObjHdr* object) {
    if (object != vmNull) {
        if (!(object->flags.raw & CHANSVM_OBJ_FLAG_READONLY)) {
            if (object->hasData) {
                ChunkEntry* dataChunk = (ChunkEntry*)object->value.ptr_v;
                int refCount;

                if (dataChunk->alloc == 0) {
                    refCount = 1;
                } else {
                    if (dataChunk->inUse != 0) {
                        refCount = dataChunk->inUse - 1;
                        dataChunk->inUse = refCount;
                    } else {
                        refCount = -1;
                    }
                }

                if (refCount == 0) {
                    if (object->parentCls == vmNull || object->parentCls->dtor == vmNull || object->parentCls->dtor(vm, object, vmNull)) {
                        CHANSVmFree(vm, dataChunk->pData, dataChunk->alloc);
                        memset(dataChunk, 0, sizeof(ChunkEntry));
                    } else {
                        goto error;
                    }
                }
            }
            memset(object, 0, sizeof(CHANSVmObjHdr));
        }

        return CHANS_VM_OK;
    }

error:
    return CHANS_VM_ERR_DELETE_OBJECT;
}

static inline ChunkEntry* VmReserveChunkEntry(CHANSVmPrivate* pVm) {
    u32 idx;
    union {
        u32 off;
        ChunkEntry* entry;
    } u;
    ChunkEntry* chunk;
    u32 chunkIdx;

    idx = pVm->nextChunkIdx;
    chunk = pVm->pChunks[idx / 1024];
    if (chunk == vmNull || chunk[idx & 0x3FF].inUse != 0) {
        chunkIdx = 0;
        u.off = 0;
        while (chunkIdx < 0x80) {
            chunk = pVm->pChunks[chunkIdx];
            if (chunk == vmNull) {
                chunk = CHANSVmAlloc((CHANSVm*)pVm, 0x4000);
                if (chunk == vmNull) {
                    goto no_entry;
                }
                pVm->pChunks[chunkIdx] = chunk;
            }

            idx = 0;
            while (idx < 0x400) {
                if (chunk[idx].inUse == 0) {
                    u.off = idx + (chunkIdx << 10);
                    idx = u.off;
                    goto found;
                }
                idx++;
            }

            chunkIdx++;
            u.off += 4;
        }
    no_entry:
        u.off = 0;
        goto check_entry;
    }

found:
    pVm->nextChunkIdx = (idx + 1 > 0x1FFFF) ? 0 : idx + 1;
    u.entry = &chunk[idx & 0x3FF];
    memset(u.entry, 0, sizeof(CHANSVmObjHdr));
    u.entry->inUse = 1;

check_entry:
    return u.entry;
}

static inline u32 VmGetAlignedAllocationSize(u32 length) {
    return VM_ALIGN(length);
}

vmPtr CHANSVmNewObjData(CHANSVm* vm, CHANSVmObjHdr* object, u32 length) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;
    ChunkEntry* entry;
    u32 memSize;

    if (object == vmNull || object->hasData != vmFalse || length == 0) {
        goto error;
    }
    entry = VmReserveChunkEntry(pVm);
    if (entry == vmNull) {
        goto error;
    }

    memSize = VmGetAlignedAllocationSize(length);
    {
        void* pData = CHANSVmAlloc(vm, memSize);
        if (pData != vmNull) {
            object->value.data.ptr = entry;
            object->hasData = vmTrue;
            entry->pData = pData;
            entry->size = length;
            entry->alloc = memSize;
            return pData;
        }
    }

error:
    return vmNull;
}

extern const CHANSVmObjHdr CHANSVmConstStringDataEmpty;

CHANSVmObjHdr* CHANSVmNewObject(CHANSVm* vm, vmBoolInt noAlloc, CHANSVmObjHdr* object, CHANSVmObjType type, vmSize len) {
    CHANSVmObjHdr* header;

    if (object != vmNull) {
        memset(object, 0, sizeof(CHANSVmObjHdr));
    } else {
        header = CHANSVmNewObjHdr(vm, noAlloc);
        object = header;
        if (header == vmNull) {
            goto error;
        }
    }

    if (len != 0) {
        if (CHANSVmNewObjData(vm, object, len) == 0) {
            goto error;
        }
    } else {
        if (type == (vmU32)CHANS_VM_OBJ_TYPE_STRING) {
            object->value.ptr_v = (vmPtr)&CHANSVmConstStringDataEmpty;
        }
    }

    object->type = type;
    return object;

error:
    return vmNull;
}

CHANSVmObjHdr* CHANSVmNewStringObject(CHANSVm* vm, CHANSVmObjHdr* obj, vmSize len) {
    return CHANSVmNewObject(vm, vmFalse, obj, CHANS_VM_OBJ_TYPE_STRING, len);
}

CHANSVmObjHdr* CHANSVmCopyObject(CHANSVm* vm, CHANSVmObjHdr* outObj, CHANSVmObjHdr* inObj) {
    if (inObj != vmNull) {
        if (outObj != vmNull) {
            memset(outObj, 0, sizeof(CHANSVmObjHdr));
        } else {
            outObj = CHANSVmNewObjHdr(vm, vmFalse);
            if (outObj == vmNull) {
                goto error;
            }
        }
        memcpy(outObj, inObj, sizeof(CHANSVmObjHdr));

        outObj->flags.raw = outObj->flags.reserved;
        if (outObj->hasData != vmFalse) {
            ChunkEntry* dataChunk = (ChunkEntry*)outObj->value.ptr_v;
            int refCount;

            if (dataChunk->alloc == 0) {
                refCount = 1;
            } else {
                u32 inUse = dataChunk->inUse;
                if (inUse < -1) {
                    refCount = inUse + 1;
                    dataChunk->inUse = refCount;
                } else {
                    refCount = 0;
                }
            }

            if (refCount == 0) {
                goto error;
            }
        }
        return outObj;
    }

error:
    return vmNull;
}

CHANSVmErr CHANSVmPopObject(CHANSVm* vm, CHANSVmObjHdr* object) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;
    CHANSVmObjHdr* nextStackTop;
    CHANSVmErr err = CHANS_VM_ERR_POP_OBJECT;
    CHANSVmObjHdr* stackTop = (CHANSVmObjHdr*)pVm->pObjStackTopBuf;

    if (pVm->pActiveCtx->stackDepth != 0) {
        nextStackTop = stackTop + 1;
        if ((vmU8*)nextStackTop <= pVm->pHeapEnd) {
            err = CHANS_VM_OK;

            if (object != vmNull) {
                if (object == &pVm->accumulator) {
                    err = CHANSVmDeleteObject(vm, object);
                }
                if (err == CHANS_VM_OK) {
                    memcpy(object, stackTop, sizeof(CHANSVmObjHdr));
                    object->flags.raw = object->flags.reserved;
                    memset(stackTop, 0, sizeof(CHANSVmObjHdr));
                }
            } else {
                err = CHANSVmDeleteObject(vm, stackTop);
            }

            if (err == CHANS_VM_OK) {
                pVm->pActiveCtx->stackDepth--;
                pVm->pObjStackTopBuf = (vmU8*)nextStackTop;
            }
        }
    }

    return err;
}

void CHANSVmStrCpyToU16FromU8(vmWString output, vmString input, vmSize length) {
    u8* src = (u8*)input + length;

    while (length > 0) {
        u8 val;
        u32 offset = VM_STR_LENGTH(--length);
        u8* dest = (u8*)output + offset;
        val = *--src;
        dest[1] = val;
        dest[0] = 0;
    }
}

u8* CHANSVmStrCpyToU8FromU16(u8* dest, u8* src, u32 len) {
    u32 i;
    u8* out = dest;

    for (i = 0; i < len; i++) {
        if (src[VM_STR_LENGTH(i)] != 0) {
            return vmNull;
        }

        *out = src[VM_STR_LENGTH(i) + 1];
        out++;
    }

    return dest;
}

vmU32 CHANSVmStrCpyToU8FromStringObject(u8* output, CHANSVmObjHdr* stringObj, vmSize length) {
    u32 offset, result;
    result = 0;
    offset = 0;

    if (output != vmNull && length != 0) {
        memset(output, 0, length);

        if (stringObj != vmNull && stringObj->type == CHANS_VM_OBJ_TYPE_STRING) {
            vmStringObjVal* objValue = stringObj->value.string_v;
            u32 charCount = objValue->len / 2;
            vmString stringData;
            u32 i;

            if (charCount > length) {
                charCount = length;
            }

            stringData = objValue->spData;

            for (i = 0; i < charCount; i++) {
                *output = stringData[offset + 1];
                result++;
                offset += 2;
                output++;
            }
        }
    }

    return result;
}

vmBoolInt VmIsNan(vmFloat value) {
    return isnan(value) || value == VM_NAN;
}

double CHANSVmFloatSign(double value) {
    // Clamp to -1.0~1.0
    return value < 0.0 ? -1.0 : value > 0.0 ? 1.0 : value;
}

vmFloat VmIntToFloat(vmU64 integer) {
    vmFloat result;
    if ((integer & 0x8000000000000000ULL) != 0) {
        result = -(vmFloat)(~integer + 1);
    } else {
        result = (vmFloat)integer;
    }
    return result;
}

static s32 CHANSVmParseInt(const CHANSVmObjHdr* obj, s32 base, u64* out) {
    u8 type = obj->type;
    u32 stringLength;
    u32 charCount;
    u64 number;
    char buf[0x40];
    char* endPtr;

    endPtr = vmNull;
    if (type == CHANS_VM_OBJ_TYPE_STRING) {
        stringLength = obj->value.wstring_v->len;

        if (stringLength != 0 && stringLength <= VM_STRING_SIZE) {
            charCount = stringLength / 2;

            if (CHANSVmStrCpyToU8FromU16((u8*)buf, (u8*)obj->value.wstring_v->spData, charCount) != vmNull) {
                buf[charCount] = '\0';
                number = strtoull(buf, &endPtr, base);
                if (endPtr == buf) {
                    number = 0;
                }
                if (out != vmNull) {
                    *out = number;
                }
                return 1;
            }
        }
    }
    return 0;
}

CHANSVmObjHdr* CHANSVmConvertToIntFromFloat(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* object) {
    // Convert to int from float
    CHANSVmObjHdr* newObj = CHANSVmNewObject(vm, vmFalse, vmNull, CHANS_VM_OBJ_TYPE_INTEGER, 0);
    if (newObj != vmNull) {
        if (VmIsNan(object->value.float_v)) {
            newObj->value.int_v = 0;
        } else {
            newObj->value.int_v = (u64)(CHANSVmFloatSign(object->value.float_v) * floor(fabs(object->value.float_v)));
        }
    }
    return newObj;
}

CHANSVmObjHdr* CHANSVmConvertToIntFromStr(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* object) {
    CHANSVmObjHdr* newObj = CHANSVmNewObject(vm, vmFalse, vmNull, CHANS_VM_OBJ_TYPE_INTEGER, 0);
    if (newObj != vmNull && !CHANSVmParseInt(object, 0, (u64*)&newObj->value.int_v)) {
        newObj = vmNull;
    }
    return newObj;
}

CHANSVmObjHdr* CHANSVmConvertToIntFromArray(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* object) {
    return vmNull;
}

CHANSVmObjHdr* CHANSVmConvertToFloatFromUndefined(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* object) {
    CHANSVmObjHdr* result = CHANSVmNewObject(vm, vmFalse, vmNull, CHANS_VM_OBJ_TYPE_FLOAT, 0);
    if (result != vmNull) {
        result->value.float_v = VM_NAN;
    }
    return result;
}

CHANSVmObjHdr* CHANSVmConvertToFloatFromInt(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* intObj) {
    CHANSVmObjHdr* result = CHANSVmNewObject(vm, vmFalse, vmNull, CHANS_VM_OBJ_TYPE_FLOAT, 0);
    if (result != vmNull) {
        result->value.float_v = VmIntToFloat(intObj->value.int_v);
    }
    return result;
}

// The 16-bit strings use a single null byte for termination for some reason. Because of that, L"..." cannot be used.
u8 scUndefinedUtf16[19] = {0x00, 'u', 0x00, 'n', 0x00, 'd', 0x00, 'e', 0x00, 'f', 0x00, 'i', 0x00, 'n', 0x00, 'e', 0x00, 'd', 0x00};
u8 scInfinityUtf16[17] = {0x00, 'I', 0x00, 'n', 0x00, 'f', 0x00, 'i', 0x00, 'n', 0x00, 'i', 0x00, 't', 0x00, 'y', 0x00};
u8 scMinusInfinityUtf16[19] = {0x00, '-', 0x00, 'I', 0x00, 'n', 0x00, 'f', 0x00, 'i', 0x00, 'n', 0x00, 'i', 0x00, 't', 0x00, 'y', 0x00};

// clang-format off
const CHANSVmObjHdr CHANSVmConstStringObjectUndefined = {{(wchar_t*)scUndefinedUtf16, 18}, {0}, vmNull};
const CHANSVmObjHdr CHANSVmConstStringObjectNaN = {{(wchar_t*)"\0N\0a\0N", 6}, {0}, vmNull};
const CHANSVmObjHdr CHANSVmConstStringObjectInfinity = {{(wchar_t*)scInfinityUtf16, 16}, {0}, vmNull};
const CHANSVmObjHdr CHANSVmConstStringObjectMinusInfinity = {{(wchar_t*)scMinusInfinityUtf16, 18}, {0}, vmNull};
const CHANSVmObjHdr CHANSVmConstStringObjectComma = {{(wchar_t*)"\0,", 2}, {0}, vmNull};
const CHANSVmObjHdr CHANSVmConstStringDataEmpty = {{(wchar_t*)"", 0}, {0}, vmNull};
const CHANSVmObjHdr CHANSVmConstStringObjectUndefined_[] = {{{(void*)&CHANSVmConstStringObjectUndefined, 0}, 0x03800100, vmNull},
                                                            {{(void*)&CHANSVmConstStringObjectNaN, 0}, 0x03800100, vmNull},
                                                            {{(void*)&CHANSVmConstStringObjectInfinity, 0}, 0x03800100, vmNull},
                                                            {{(void*)&CHANSVmConstStringObjectMinusInfinity, 0}, 0x03800100, vmNull},
                                                            {{vmNull, 0}, 0x00800000, vmNull}};
char VmReportFormat[] = "%s";

const CHANSVmFloatConstantList scFloatConstantList[] = {
    { "Infinity", (double*)&VmInf },
    { "+Infinity", (double*)&VmInf },
    { "-Infinity", (double*)&VmMinusInf },
    { "NaN", (double*)&VmNaN }
};
char scFloatPrintfFmt[] = "%.16lg";
// clang-format on

static inline s32 CHANSVmParseFloat(CHANSVmObjHdr* obj, f64* out) {
    u8 type = obj->type;
    u32 stringLength;
    u32 charCount;
    f64 number;
    char buf[0x40];
    char* endPtr;
    char* bufEnd;
    u32 i;

    endPtr = vmNull;
    if (type == CHANS_VM_OBJ_TYPE_STRING) {
        stringLength = obj->value.wstring_v->len;

        if (stringLength != 0 && stringLength <= VM_STRING_SIZE) {
            charCount = stringLength / 2;

            if (CHANSVmStrCpyToU8FromU16((u8*)buf, (u8*)obj->value.wstring_v->spData, charCount) != vmNull) {
                bufEnd = &buf[charCount];
                *bufEnd = '\0';

                for (i = 0; i < 4; i++) {
                    if (strcmp(buf, scFloatConstantList[i].spName) == 0) {
                        number = *scFloatConstantList[i].pValue;
                        goto store;
                    }
                }

                {
                    u64 val = strtoull(buf, &endPtr, 0);
                    if (endPtr == bufEnd) {
                        number = VmIntToFloat(val);
                        goto store;
                    }
                }

                number = strtod(buf, &endPtr);
                if (endPtr == buf) {
                    number = VM_NAN;
                }

            store:
                if (out != vmNull) {
                    *out = number;
                }
                return 1;
            }
        }
    }
    return 0;
}

CHANSVmObjHdr* CHANSVmConvertToFloatFromStr(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* object) {
    // Convert string keyword into float value
    CHANSVmObjHdr* newObj = CHANSVmNewObject(vm, vmFalse, vmNull, CHANS_VM_OBJ_TYPE_FLOAT, 0);

    if (newObj != vmNull && !CHANSVmParseFloat(object, &newObj->value.float_v)) {
        newObj = vmNull;
    }
    return newObj;
}

CHANSVmObjHdr* CHANSVmConvertToStrFromUndefined(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* object) {
    return (CHANSVmObjHdr*)CHANSVmConstStringObjectUndefined_;
}

s32 CHANSVmFloatToWString(vmWString buf, u32 len, vmFloat val) NO_INLINE {
    s32 result = snprintf((char*)buf, len / 2, scFloatPrintfFmt, val);
    CHANSVmStrCpyToU16FromU8(buf, (vmString)buf, result);
    return VM_STR_LENGTH(result);
}

char VmIntegerFormat[] = "%lld";

static int VmToStrFromInt(vmWString output, vmSize length, vmInteger integer) {
    vmS32 len = snprintf((vmString)output, length, VmIntegerFormat, integer);
    CHANSVmStrCpyToU16FromU8(output, (vmString)output, len);
    return len;
}

CHANSVmObjHdr* CHANSVmConvertToStrFromInt(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* object) {
    CHANSVmObjHdr* newObject = CHANSVmNewObject(vm, vmFalse, vmNull, CHANS_VM_OBJ_TYPE_STRING, VM_STR_LENGTH(64));
    if (newObject) {
        vmS32 len = VmToStrFromInt(newObject->value.wstring_v->spData, 64, object->value.int_v);

        newObject->value.wstring_v->len = VM_STR_LENGTH(len);
        if (newObject->value.wstring_v->len == 0) {
            goto error;
        }
    }
    return newObject;

error:
    return vmNull;
}

CHANSVmObjHdr* CHANSVmConvertToStrFromFloat(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* value) {
    const CHANSVmObjHdr* base;
    CHANSVmObjHdr* newObj;
    s32 result;

    // TODO: This data access needs to be fixed
    // Accessing the CHANSVmConstStringObjectUndefined_ array properly breaks the match
    base = &CHANSVmConstStringObjectUndefined;  // .rodata@0x0
    if (VmIsNan(value->value.float_v)) {
        return (CHANSVmObjHdr*)&base[7];  // .rodata@0x70 (refers to CHANSVmConstStringObjectUndefined_[1])
    }
    if (value->value.float_v == VM_INF) {
        return (CHANSVmObjHdr*)&base[8];  // .rodata@0x80 (refers to CHANSVmConstStringObjectUndefined_[2])
    }
    if (value->value.float_v == VM_NEG_INF) {
        return (CHANSVmObjHdr*)&base[9];  // .rodata@0x90 (refers to CHANSVmConstStringObjectUndefined_[3])
    }

    newObj = CHANSVmNewObject(vm, vmFalse, vmNull, CHANS_VM_OBJ_TYPE_STRING, VM_STRING_SIZE);
    if (newObj != vmNull) {
        result = CHANSVmFloatToWString(newObj->value.wstring_v->spData, VM_STRING_SIZE, value->value.float_v);
        newObj->value.wstring_v->len = result;
        if (newObj->value.wstring_v->len == 0) {
            goto error;
        }
    }
    return newObj;
error:
    return vmNull;
}

static CHANSVmObjHdr* VmArrayJoinCommon(CHANSVm* vm, u32 retObjAddr, CHANSVmObjHdr* object, u32 separatorAddr, u32 separatorLen);

CHANSVmObjHdr* CHANSVmConvertToStrFromArray(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* object) {
    return VmArrayJoinCommon(vm, 0, object, 0, 0);
}

CHANSVmObjHdr* CHANSVmConvertObjectTypeError(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* object) {
    CHANS_VM_PRINTF(1176, ", type to %d from %d\n", type, object->type);
    return vmNull;
}

vmBoolInt CHANSVmGetEnumedType(CHANSVmObjType* eType, vmU32 iType) NO_INLINE {
    CHANSVmObjType type;
    switch (iType) {
        case CHANS_VM_OBJ_TYPE_BLANK: {
            type = CHANS_VM_OBJ_TYPE_BLANK;
            break;
        }
        case CHANS_VM_OBJ_TYPE_INTEGER: {
            type = CHANS_VM_OBJ_TYPE_INTEGER;
            break;
        }
        case CHANS_VM_OBJ_TYPE_FLOAT: {
            type = CHANS_VM_OBJ_TYPE_FLOAT;
            break;
        }
        case CHANS_VM_OBJ_TYPE_STRING: {
            type = CHANS_VM_OBJ_TYPE_STRING;
            break;
        }
        case CHANS_VM_TYPE_ARRAY: {
            type = CHANS_VM_TYPE_ARRAY;
            break;
        }
        case CHANS_VM_TYPE_OBJECT:
        case CHANS_VM_TYPE_CLASS_REF:
        case CHANS_VM_TYPE_METHOD_REF: {
            type = 5;
            break;
        }
        default: {
            return vmFalse;
        }
    }

    if (eType) {
        *eType = type;
    }

    return vmTrue;
}

// TODO: Here was a function defined that was inlined into VmStep.
char scVmGetResultType[] = "VmGetResultType";

// clang-format off
const VmConvertEntry VmTypeConvertFuncTbl[] = {
    {vmNull, CHANSVmConvertObjectTypeError, CHANSVmConvertObjectTypeError, CHANSVmConvertObjectTypeError, CHANSVmConvertObjectTypeError, CHANSVmConvertObjectTypeError},
    {CHANSVmConvertObjectTypeError, vmNull, CHANSVmConvertToIntFromFloat, CHANSVmConvertToIntFromStr, CHANSVmConvertToIntFromArray, CHANSVmConvertObjectTypeError},
    {CHANSVmConvertToFloatFromUndefined, CHANSVmConvertToFloatFromInt, vmNull, CHANSVmConvertToFloatFromStr, CHANSVmConvertObjectTypeError, CHANSVmConvertObjectTypeError},
    {CHANSVmConvertToStrFromUndefined, CHANSVmConvertToStrFromInt, CHANSVmConvertToStrFromFloat, vmNull, CHANSVmConvertToStrFromArray, CHANSVmConvertObjectTypeError},
    {CHANSVmConvertObjectTypeError, CHANSVmConvertObjectTypeError, CHANSVmConvertObjectTypeError, CHANSVmConvertObjectTypeError, vmNull, CHANSVmConvertObjectTypeError},
    {CHANSVmConvertObjectTypeError, CHANSVmConvertObjectTypeError, CHANSVmConvertObjectTypeError, CHANSVmConvertObjectTypeError, CHANSVmConvertObjectTypeError, vmNull},
};
// clang-format on

// Each table is a 6x6 u8 matrix indexed [left_enumed][right_enumed].
// left/right are CHANSVmObjType mapped to 0-5 by CHANSVmGetEnumedType.
// The table value determines to the type of the result of an operation with two operands.
typedef u8 VmResultTypeMatrix[6][6];

typedef struct {
    VmResultTypeMatrix add;       // 0x00
    VmResultTypeMatrix arith;     // 0x24
    VmResultTypeMatrix cmp;       // 0x48
    VmResultTypeMatrix eq;        // 0x6C
    VmResultTypeMatrix bitShift;  // 0x90
} VmResultTypeData;

// clang-format off
const VmResultTypeData VmResultTypeTbl = {
    /* add[6][6] = */ {
        0x00, 0x02, 0x02, 0x03, 0x00, 0x00,
        0x02, 0x01, 0x02, 0x03, 0x03, 0x00,
        0x02, 0x02, 0x02, 0x03, 0x03, 0x00,
        0x03, 0x03, 0x03, 0x03, 0x03, 0x00,
        0x00, 0x03, 0x03, 0x03, 0x03, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },
    /* arith[6][6] = */
    {
        0x00, 0x02, 0x02, 0x02, 0x00, 0x00,
        0x02, 0x01, 0x02, 0x02, 0x00, 0x00,
        0x02, 0x02, 0x02, 0x02, 0x00, 0x00,
        0x02, 0x02, 0x02, 0x02, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },
    /* cmp[6][6] = */
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x01, 0x02, 0x02, 0x00, 0x00,
        0x00, 0x02, 0x02, 0x02, 0x00, 0x00,
        0x00, 0x02, 0x02, 0x03, 0x03, 0x00,
        0x00, 0x00, 0x00, 0x03, 0x03, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },
    /* eq[6][6] = */
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x01, 0x02, 0x02, 0x00, 0x00,
        0x00, 0x02, 0x02, 0x02, 0x00, 0x00,
        0x00, 0x02, 0x02, 0x03, 0x03, 0x00,
        0x00, 0x00, 0x00, 0x03, 0x04, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },
    /* bitShift[6][6] = */
    {
        0x00, 0x01, 0x01, 0x01, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },
};
// clang-format on

CHANSVmObjHdr* CHANSVmConvertObjectType(CHANSVm* vm, vmU32 type, CHANSVmObjHdr* object) {
    CHANSVmObjType old, new;

    if (object == vmNull) {
        return vmNull;
    }

    if (type == object->type) {
        return object;
    }

    if (!CHANSVmGetEnumedType(&old, type) || !CHANSVmGetEnumedType(&new, object->type)) {
        return vmNull;
    }

    return ((const VmConvertEntry*)VmTypeConvertFuncTbl)[old].convFunc[new](vm, type, object);
}

CHANSVmErr CHANSVmSetInteger(CHANSVm* vm, CHANSVmObjHdr* object, vmInteger val) {
    CHANSVmErr ret = CHANSVmDeleteObject(vm, object);
    if (ret == CHANS_VM_OK) {
        object->type = CHANS_VM_OBJ_TYPE_INTEGER;
        object->value.int_v = val;
    }
    return ret;
}

CHANSVmErr CHANSVmSetFloat(CHANSVm* vm, CHANSVmObjHdr* object, vmFloat value) {
    CHANSVmErr ret = CHANSVmDeleteObject(vm, object);
    if (ret == CHANS_VM_OK) {
        object->type = CHANS_VM_OBJ_TYPE_FLOAT;
        if (value == VM_NEG_ZERO) {
            value = 0.0f;
        }
        object->value.float_v = value;
    }
    return ret;
}

CHANSVmErr CHANSVmSetU16String(CHANSVm* vm, CHANSVmObjHdr* object, vmWString str, vmSize strLen) {
    CHANSVmErr ret = CHANSVmDeleteObject(vm, object);
    if (ret == CHANS_VM_OK) {
        if (CHANSVmNewObject(vm, vmFalse, object, CHANS_VM_OBJ_TYPE_STRING, strLen) == vmNull) {
            return CHANS_VM_ERR_SET_STRING;
        }

        if (strLen != 0) {
            memcpy(object->value.wstring_v->spData, str, strLen);
        }
    }
    return ret;
}

CHANSVmErr CHANSVmSetU16StringFromU8(CHANSVm* vm, CHANSVmObjHdr* object, vmString str, vmSize strLen) {
    CHANSVmErr ret = CHANSVmDeleteObject(vm, object);
    if (ret == CHANS_VM_OK) {
        if (CHANSVmNewObject(vm, vmFalse, object, CHANS_VM_OBJ_TYPE_STRING, VM_STR_LENGTH(strLen)) == vmNull) {
            return CHANS_VM_ERR_SET_STRING;
        }

        if (strLen != 0) {
            CHANSVmStrCpyToU16FromU8(object->value.wstring_v->spData, str, strLen);
        }
    }
    return ret;
}

CHANSVmErr VmStore(CHANSVm* vm, CHANSVmObjHdr* dest, CHANSVmObjHdr* src);

CHANSVmErr VmAdd(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* ret, CHANSVmObjHdr* left, CHANSVmObjHdr* right) {
    CHANSVmObjHdr* obj;
    CHANSVmObjHdr concatHeader;
    CHANSVmErr err = CHANS_VM_ERR_ADD;

    switch (type) {
        case CHANS_VM_OBJ_TYPE_INTEGER: {
            err = CHANSVmSetInteger(vm, ret, left->value.int_v + right->value.int_v);
            break;
        }
        case CHANS_VM_OBJ_TYPE_FLOAT: {
            err = CHANSVmSetFloat(vm, ret, left->value.float_v + right->value.float_v);
            break;
        }
        case CHANS_VM_OBJ_TYPE_STRING: {
            err = CHANS_VM_ERR_STRCAT;
            obj = CHANSVmNewObject(vm, vmFalse, &concatHeader, CHANS_VM_OBJ_TYPE_STRING, left->value.string_v->len + right->value.string_v->len);
            if (obj != vmNull) {
                vmU32 len;

                len = left->value.string_v->len;
                if (len != 0) {
                    memcpy(*obj->value.ptr_v, *left->value.ptr_v, len);
                }
                len = right->value.string_v->len;
                if (len != 0) {
                    memcpy((void*)((vmU32)*obj->value.ptr_v + (left->value.string_v)->len), *right->value.ptr_v, len);
                }
                err = VmStore(vm, ret, obj);
                if (err == CHANS_VM_OK) {
                    err = CHANSVmDeleteObject(vm, obj);
                }
            }
            break;
        }
        default: {
            break;
        }
    }
    return err;
}

CHANSVmErr VmSub(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* ret, CHANSVmObjHdr* left, CHANSVmObjHdr* right) {
    CHANSVmErr err = CHANS_VM_ERR_SUB;

    switch (type) {
        case CHANS_VM_OBJ_TYPE_INTEGER: {
            err = CHANSVmSetInteger(vm, ret, left->value.int_v - right->value.int_v);
            break;
        }
        case CHANS_VM_OBJ_TYPE_FLOAT: {
            err = CHANSVmSetFloat(vm, ret, left->value.float_v - right->value.float_v);
            break;
        }
        default: {
            break;
        }
    }
    return err;
}

CHANSVmErr VmMul(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* ret, CHANSVmObjHdr* left, CHANSVmObjHdr* right) {
    CHANSVmErr err = CHANS_VM_ERR_MUL;

    switch (type) {
        case CHANS_VM_OBJ_TYPE_INTEGER: {
            err = CHANSVmSetInteger(vm, ret, left->value.int_v * right->value.int_v);
            break;
        }
        case CHANS_VM_OBJ_TYPE_FLOAT: {
            err = CHANSVmSetFloat(vm, ret, left->value.float_v * right->value.float_v);
            break;
        }
        default: {
            break;
        }
    }
    return err;
}

CHANSVmErr VmDiv(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* ret, CHANSVmObjHdr* left, CHANSVmObjHdr* right) {
    CHANSVmErr err = CHANS_VM_ERR_DIV;
    vmFloat rightFloat;
    vmFloat leftFloat;

    switch (type) {
        case CHANS_VM_OBJ_TYPE_INTEGER: {
            rightFloat = VmIntToFloat(right->value.int_v);
            leftFloat = VmIntToFloat(left->value.int_v);
            err = CHANSVmSetFloat(vm, ret, leftFloat / rightFloat);
            break;
        }
        case CHANS_VM_OBJ_TYPE_FLOAT: {
            err = CHANSVmSetFloat(vm, ret, left->value.float_v / right->value.float_v);
            break;
        }
        default: {
            break;
        }
    }
    return err;
}

CHANSVmErr VmMod(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* ret, CHANSVmObjHdr* left, CHANSVmObjHdr* right) {
    CHANSVmErr err = CHANS_VM_ERR_MOD;
    vmFloat rightFloat;
    vmFloat leftFloat;

    switch (type) {
        case CHANS_VM_OBJ_TYPE_INTEGER: {
            rightFloat = VmIntToFloat(right->value.int_v);
            leftFloat = VmIntToFloat(left->value.int_v);
            err = CHANSVmSetFloat(vm, ret, fmod(leftFloat, rightFloat));
            break;
        }
        case CHANS_VM_OBJ_TYPE_FLOAT: {
            err = CHANSVmSetFloat(vm, ret, fmod(left->value.float_v, right->value.float_v));
            break;
        }
        default: {
            break;
        }
    }
    return err;
}

CHANSVmErr VmULShift(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* ret, CHANSVmObjHdr* left, CHANSVmObjHdr* right) {
    CHANSVmErr err = CHANS_VM_ERR_ULSHIFT;
    u64 shiftValue;
    switch (type) {
        case CHANS_VM_OBJ_TYPE_INTEGER: {
            shiftValue = right->value.int_v;
            if (shiftValue < 0x40) {
                shiftValue = left->value.int_v << right->value.int_v;
            } else {
                shiftValue = 0;
            }
            err = CHANSVmSetInteger(vm, ret, shiftValue);
            break;
        }
        default: {
            break;
        }
    }
    return err;
}

CHANSVmErr VmARShift(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* ret, CHANSVmObjHdr* left, CHANSVmObjHdr* right) {
    CHANSVmErr err = CHANS_VM_ERR_ARSHIFT;

    switch (type) {
        case CHANS_VM_OBJ_TYPE_INTEGER: {
            u64 val = right->value.int_v;
            if (val < 0x40) {
                val = left->value.int_v >> right->value.int_v;
            } else {
                val = left->value.int_v >> 63;
            }
            err = CHANSVmSetInteger(vm, ret, val);
            break;
        }
        default: {
            break;
        }
    }
    return err;
}

CHANSVmErr VmBitAnd(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* ret, CHANSVmObjHdr* left, CHANSVmObjHdr* right) {
    CHANSVmErr err = CHANS_VM_ERR_BIT_AND;
    switch (type) {
        case CHANS_VM_OBJ_TYPE_INTEGER: {
            err = CHANSVmSetInteger(vm, ret, left->value.int_v & right->value.int_v);
            break;
        }
        default: {
            break;
        }
    }
    return err;
}

CHANSVmErr VmBitOr(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* ret, CHANSVmObjHdr* left, CHANSVmObjHdr* right) {
    CHANSVmErr err = CHANS_VM_ERR_BIT_OR;
    switch (type) {
        case CHANS_VM_OBJ_TYPE_INTEGER: {
            err = CHANSVmSetInteger(vm, ret, left->value.int_v | right->value.int_v);
            break;
        }
        default: {
            break;
        }
    }
    return err;
}

CHANSVmErr VmBitXor(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* ret, CHANSVmObjHdr* left, CHANSVmObjHdr* right) {
    CHANSVmErr err = CHANS_VM_ERR_BIT_XOR;
    switch (type) {
        case CHANS_VM_OBJ_TYPE_INTEGER: {
            err = CHANSVmSetInteger(vm, ret, left->value.int_v ^ right->value.int_v);
            break;
        }
        default: {
            break;
        }
    }
    return err;
}

CHANSVmErr VmCmpEq(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* ret, CHANSVmObjHdr* left, CHANSVmObjHdr* right) {
    vmBoolInt stringsMatch;
    vmBoolInt isEqual;
    CHANSVmErr err;

    switch (type) {
        case CHANS_VM_OBJ_TYPE_BLANK: {
            u8 leftType = left->type;
            if (leftType == right->type) {
                if (leftType == CHANS_VM_TYPE_CLASS_REF || leftType == CHANS_VM_TYPE_OBJECT)
                    goto handle_object_type;
                if (leftType == CHANS_VM_TYPE_METHOD_REF) {
                    isEqual = left->value.ptr_v == right->value.ptr_v;
                    break;
                }
                if (leftType == CHANS_VM_OBJ_TYPE_BLANK) {
                    isEqual = vmTrue;
                    break;
                }
            }
            isEqual = vmFalse;
            break;
        }
        case CHANS_VM_OBJ_TYPE_INTEGER: {
            isEqual = left->value.int_v == right->value.int_v;
            break;
        }
        case CHANS_VM_OBJ_TYPE_FLOAT: {
            isEqual = left->value.float_v == right->value.float_v;
            break;
        }
        case CHANS_VM_OBJ_TYPE_STRING: {
            isEqual = vmFalse;
            if (left->value.string_v->len == right->value.string_v->len) {
                stringsMatch = vmFalse;
                if (left->value.string_v->len == 0 || memcmp(*left->value.ptr_v, *right->value.ptr_v, left->value.string_v->len) == 0) {
                    stringsMatch = vmTrue;
                }
                if (stringsMatch) {
                    isEqual = vmTrue;
                }
            }
            break;
        }
        case CHANS_VM_TYPE_ARRAY: {
        handle_object_type:
            isEqual = vmFalse;
            if (left->parentCls == right->parentCls && left->hasData == right->hasData &&
                (left->hasData == vmFalse || left->value.ptr_v == right->value.ptr_v)) {
                isEqual = vmTrue;
            }
            break;
        }
        default:
            return CHANS_VM_ERR_CMP;
    }

    err = CHANSVmSetInteger(vm, ret, isEqual != 0);
    return err;
}

CHANSVmErr VmCmpNeq(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* ret, CHANSVmObjHdr* left, CHANSVmObjHdr* right) {
    CHANSVmErr err = VmCmpEq(vm, type, ret, left, right);
    if (err == CHANS_VM_OK) {
        ret->value.int_v = !ret->value.int_v;
    }
    return err;
}

CHANSVmErr VmCmpLt(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* ret, CHANSVmObjHdr* left, CHANSVmObjHdr* right) {
    int result;
    int match;
    u32 leftLen, rightLen, maxLen;
    switch (type) {
        case CHANS_VM_OBJ_TYPE_BLANK:
        case CHANS_VM_TYPE_ARRAY:
        case CHANS_VM_TYPE_OBJECT: {
            result = vmFalse;
            break;
        }
        case CHANS_VM_OBJ_TYPE_INTEGER: {
            result = left->value.int_v < right->value.int_v;
            break;
        }
        case CHANS_VM_OBJ_TYPE_FLOAT: {
            result = left->value.float_v < right->value.float_v;
            break;
        }
        case CHANS_VM_OBJ_TYPE_STRING: {
            rightLen = right->value.string_v->len;
            leftLen = left->value.string_v->len;
            maxLen = rightLen;
            if (leftLen < rightLen)
                maxLen = leftLen;
            if (maxLen != 0) {
                match = memcmp(left->value.string_v->spData, right->value.string_v->spData, maxLen);
            } else {
                match = 0;
            }
            result = vmFalse;
            if (match < 0 || (match == 0 && leftLen < rightLen))
                result = vmTrue;
            break;
        }
        default: {
            return CHANS_VM_ERR_CMP;
        }
    }
    return CHANSVmSetInteger(vm, ret, result != 0);
}

CHANSVmErr VmCmpGt(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* ret, CHANSVmObjHdr* left, CHANSVmObjHdr* right) {
    return VmCmpLt(vm, type, ret, right, left);
}

CHANSVmErr VmCmpLeq(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* ret, CHANSVmObjHdr* left, CHANSVmObjHdr* right) {
    vmBoolInt result;
    vmBoolInt match;
    u32 leftLen, rightLen, maxLen;
    switch (type) {
        case CHANS_VM_OBJ_TYPE_BLANK:
        case CHANS_VM_TYPE_ARRAY:
        case CHANS_VM_TYPE_OBJECT: {
            result = vmFalse;
            break;
        }
        case CHANS_VM_OBJ_TYPE_INTEGER: {
            result = left->value.int_v <= right->value.int_v;
            break;
        }
        case CHANS_VM_OBJ_TYPE_FLOAT: {
            result = left->value.float_v <= right->value.float_v;
            break;
        }
        case CHANS_VM_OBJ_TYPE_STRING: {
            rightLen = right->value.string_v->len;
            leftLen = left->value.string_v->len;
            maxLen = rightLen;
            if (leftLen < rightLen)
                maxLen = leftLen;
            if (maxLen != 0) {
                match = memcmp(left->value.string_v->spData, right->value.string_v->spData, maxLen);
            } else {
                match = 0;
            }
            result = vmFalse;
            if (match < 0 || (match == 0 && leftLen <= rightLen))
                result = vmTrue;
            break;
        }
        default: {
            return CHANS_VM_ERR_CMP;
        }
    }
    return CHANSVmSetInteger(vm, ret, result != 0);
}

CHANSVmErr VmCmpGeq(CHANSVm* vm, CHANSVmObjType type, CHANSVmObjHdr* ret, CHANSVmObjHdr* left, CHANSVmObjHdr* right) {
    return VmCmpLeq(vm, type, ret, right, left);
}

CHANSVmErr CHANSVmGetBoolean(vmBoolInt* ret, CHANSVmObjHdr* val) {
    vmBoolInt result;
    switch (val->type) {
        case CHANS_VM_OBJ_TYPE_BLANK: {
            result = vmFalse;
            break;
        }
        case CHANS_VM_OBJ_TYPE_INTEGER: {
            result = val->value.int_v != 0;
            break;
        }
        case CHANS_VM_OBJ_TYPE_FLOAT: {
            result = vmFalse;
            if (!VmIsNan(val->value.float_v) && (val->value.float_v != 0)) {
                result = vmTrue;
            }
            break;
        }
        case CHANS_VM_OBJ_TYPE_STRING: {
            result = val->value.string_v->len != 0;
            break;
        }
        case CHANS_VM_TYPE_ARRAY:
        case CHANS_VM_TYPE_CLASS_REF:
        case CHANS_VM_TYPE_OBJECT:
        case CHANS_VM_TYPE_METHOD_REF: {
            result = vmTrue;
            break;
        }
        default: {
            return CHANS_VM_ERR_GET_BOOLEAN;
        }
    }
    if (ret != vmNull) {
        *ret = result;
    }
    return CHANS_VM_OK;
}

vmU32 CHANSVmGetArgc(CHANSVm* vm) {
    return ((CHANSVmPrivate*)vm)->pActiveCtx->argc;
}

CHANSVmObjHdr* CHANSVmGetArg(CHANSVm* vm, vmU32 argIdx) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;

    if (argIdx >= pVm->pActiveCtx->argc) {
        return vmNull;
    }

    return (CHANSVmObjHdr*)pVm->pActiveCtx->pArgv + (pVm->pActiveCtx->argc - 1 - argIdx);
}

CHANSVmObjHdr* CHANSVmGetArgInteger(CHANSVm* vm, vmU32 argIdx) {
    return CHANSVmConvertObjectType(vm, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(vm, argIdx));
}

CHANSVmObjHdr* CHANSVmGetArgFloat(CHANSVm* vm, vmU32 argIdx) {
    return CHANSVmConvertObjectType(vm, CHANS_VM_OBJ_TYPE_FLOAT, CHANSVmGetArg(vm, argIdx));
}

CHANSVmObjHdr* CHANSVmGetArgString(CHANSVm* vm, vmU32 argIdx) {
    return CHANSVmConvertObjectType(vm, CHANS_VM_OBJ_TYPE_STRING, CHANSVmGetArg(vm, argIdx));
}

// === vmErrorList: maps error codes to strings ===
const char* vmErrorList[] = {
    "CHANS_VM_ERR_NO_1000",
    "CHANS_VM_ERR_EXIT",                            /* -999 */
    "CHANS_VM_ERR_NO_MEMORY",                       /* -998 */
    "CHANS_VM_ERR_INVALID_EXE_FORMAT",              /* -997 */
    "CHANS_VM_ERR_ARG",                             /* -996 */
    "CHANS_VM_ERR_CODE_RANGE",                      /* -995 */
    "CHANS_VM_ERR_HEAP_RANGE",                      /* -994 */
    "CHANS_VM_ERR_OBJECT_NOT_FOUND",                /* -993 */
    "CHANS_VM_ERR_ALIGNMENT",                       /* -992 */
    "CHANS_VM_ERR_RESULT_TYPE",                     /* -991 */
    "CHANS_VM_ERR_TOO_MANY_DEFINED",                /* -990 */
    "CHANS_VM_ERR_ALREADY_DEFINED",                 /* -989 */
    "CHANS_VM_ERR_LINK_FAILED",                     /* -988 */
    "CHANS_VM_ERR_IN_METHOD_OR_PROPERTY",           /* -987 */
    "CHANS_VM_ERR_NATIVE_METHOD_INIT",              /* -986 */
    "CHANS_VM_ERR_LOAD_OBJECT",                     /* -985 */
    "CHANS_VM_ERR_STORE_OBJECT",                    /* -984 */
    "CHANS_VM_ERR_DIVISION_BY_ZERO",                /* -983 */
    "CHANS_VM_ERR_DELETE_OBJECT",                   /* -982 */
    "CHANS_VM_ERR_DELETE_OBJHDR",                   /* -981 */
    "CHANS_VM_ERR_DELETE_OBJDATA",                  /* -980 */
    "CHANS_VM_ERR_POP_OBJECT",                      /* -979 */
    "CHANS_VM_ERR_STR_U8_TO_U16",                   /* -978 */
    "CHANS_VM_ERR_SET_INTEGER",                     /* -977 */
    "CHANS_VM_ERR_SET_FLOAT",                       /* -976 */
    "CHANS_VM_ERR_ADD",                             /* -975 */
    "CHANS_VM_ERR_SUB",                             /* -974 */
    "CHANS_VM_ERR_MUL",                             /* -973 */
    "CHANS_VM_ERR_DIV",                             /* -972 */
    "CHANS_VM_ERR_MOD",                             /* -971 */
    "CHANS_VM_ERR_ULSHIFT",                         /* -970 */
    "CHANS_VM_ERR_ARSHIFT",                         /* -969 */
    "CHANS_VM_ERR_BIT_AND",                         /* -968 */
    "CHANS_VM_ERR_BIT_OR",                          /* -967 */
    "CHANS_VM_ERR_BIT_XOR",                         /* -966 */
    "CHANS_VM_ERR_CMP",                             /* -965 */
    "CHANS_VM_ERR_ADD_NATIVE_METHOD",               /* -964 */
    "CHANS_VM_ERR_SET_LOCAL_FUNCTION",              /* -963 */
    "CHANS_VM_ERR_PUSH_FUNC_RETURN_INFO",           /* -962 */
    "CHANS_VM_ERR_LOAD_IMM",                        /* -961 */
    "CHANS_VM_ERR_LOAD_CONST",                      /* -960 */
    "CHANS_VM_ERR_RETURN",                          /* -959 */
    "CHANS_VM_ERR_STRCAT",                          /* -958 */
    "CHANS_VM_ERR_SET_OBJECT_NATIVE_CLASS",         /* -957 */
    "CHANS_VM_ERR_RESOLVE_NATIVE_METHOD_CALL",      /* -956 */
    "CHANS_VM_ERR_RESOLVE_GLOBAL_OBJECT_REFERENCE", /* -955 */
    "CHANS_VM_ERR_NEW",                             /* -954 */
    "CHANS_VM_ERR_ADD_NATIVE_PROPERTY",             /* -953 */
    "CHANS_VM_ERR_GET_BOOLEAN",                     /* -952 */
    "CHANS_VM_ERR_CASE",                            /* -951 */
    "CHANS_VM_ERR_CHECK_STRICT_EQUALITY",           /* -950 */
    "CHANS_VM_ERR_ADD_REFERENCE",                   /* -949 */
    "CHANS_VM_ERR_LOAD_INDIRECT",                   /* -948 */
    "CHANS_VM_ERR_CALL_METHOD",                     /* -947 */
    "CHANS_VM_ERR_STORE_INDIRECT",                  /* -946 */
    "CHANS_VM_ERR_LOAD_STRING_CONST",               /* -945 */
    "CHANS_VM_ERR_SIGNAL",                          /* -944 */
    "CHANS_VM_ERR_STORE_READONLY",                  /* -943 */
    "CHANS_VM_ERR_SET_INDEX",                       /* -942 */
    "CHANS_VM_ERR_GET_PROPERTY_NAME",               /* -941 */
    "CHANS_VM_ERR_SET_STRING",                      /* -940 */
    "CHANS_VM_ERR_CALL_NEW_ARRAY",                  /* -939 */
    "CHANS_VM_ERR_OPCODE_VERSION",                  /* -938 */
    "CHANS_VM_ERR_NOT_SUPPORTED_FLOAT",             /* -937 */
    "CHANS_VM_ERR_NOT_CONSTRUCTOR",                 /* -936 */
    "CHANS_VM_ERR_DELETE_INDIRECT",                 /* -935 */
    "CHANS_VM_ERR_FORBIDDEN_CLASS_PROPERTY",        /* -934 */
    "CHANS_VM_ERR_FORBIDDEN_CLASS_METHOD",          /* -933 */
    "CHANS_VM_ERR_NEED_NEW",                        /* -932 */
    "CHANS_VM_ERR_INVALID_OBJECT",                  /* -931 */
    "CHANS_VM_ERR_INVALID_OBJECT_TYPE",             /* -930 */
    "CHANS_VM_ERR_NO_SUCH_PROPERTY",                /* -929 */
    "CHANS_VM_ERR_NO_SUCH_METHOD",                  /* -928 */
    "CHANS_VM_ERR_NOT_READABLE_PROPERTY",           /* -927 */
    "CHANS_VM_ERR_NOT_WRITABLE_PROPERTY",           /* -926 */
    "CHANS_VM_ERR_INVALID_EXE_TYPE",                /* -925 */
    "CHANS_VM_ERR_NO_SUCH_FUNCTION",                /* -924 */
    "CHANS_VM_ERR_RESERVED_OPCODE",                 /* -923 */
};

char vmNoError[] = "CHANS_VM_OK";
char vmUnknownError[] = "(unknown)";

CHANSVmNativeClass* CHANSVmFindNativeClass(CHANSVm* vm, const char* clsName) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;

    CHANSVmNativeClass* cls;
    vmS32 clsNameLen = strlen(clsName);

    if (clsNameLen != 0) {
        for (cls = pVm->pNativeClasses; cls != vmNull; cls = cls->pNext) {
            if (clsNameLen == cls->nameLength && memcmp(clsName, &cls->sName, clsNameLen) == 0) {
                return cls;
            }
        }
    }

    return vmNull;
}

CHANSVmNativeClass* CHANSVmAddNativeClass2(CHANSVm* vm, const char* clsName, CHANSVmFunction clsCtor, CHANSVmFunction clsDtor,
                                           CHANSVmFunction clsInit) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;

    CHANSVmNativeClass* cls;
    vmS32 clsNameLen;

    if (CHANSVmFindNativeClass(vm, clsName) == vmNull) {
        clsNameLen = strlen(clsName);
        if (clsNameLen != 0) {
            cls = CHANSVmAlloc(vm, VM_ALIGN(clsNameLen + sizeof(CHANSVmNativeClass) - 0x20));
            if (cls != vmNull) {
                if (pVm->pNativeClasses == vmNull) {
                    pVm->pNativeClasses = cls;
                } else {
                    CHANSVmNativeClass* prev = pVm->pNativeClasses;
                    while (prev->pNext != vmNull) {
                        prev = prev->pNext;
                    }
                    prev->pNext = cls;
                }

                cls->ctor = clsCtor;
                cls->dtor = clsDtor;
                cls->init = clsInit;
                cls->nameLength = clsNameLen;
                memcpy(&cls->sName, clsName, clsNameLen);
                return cls;
            }
        }
    }
    return vmNull;
}

CHANSVmNativeClass* CHANSVmAddNativeClass(CHANSVm* vm, const char* clsName, CHANSVmFunction clsCtor, CHANSVmFunction clsDtor) {
    return CHANSVmAddNativeClass2(vm, clsName, clsCtor, clsDtor, vmNull);
}

vmU32 CHANSVmAddNativeMethodName(CHANSVm* vm, const char* methodName, vmSize nameLength) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;
    MethodListNode* listPtr;
    MethodListNode* allocPtr;
    u32 allocSize;
    vmU32 index = 1;

    if (nameLength == 0) {
        goto error;
    }

    listPtr = pVm->pMethodNameList;
    if (listPtr == vmNull) {
        listPtr = (MethodListNode*)&pVm->pMethodNameList;
    } else {
        while (vmTrue) {
            if (nameLength == listPtr->nameLength) {
                if (memcmp(methodName, listPtr->sName, nameLength) == 0) {
                    return index;
                }
            }
            if (index >= 0xFFFF) {
                goto error;
            }
            index++;
            if (listPtr->pNext != vmNull) {
                listPtr = listPtr->pNext;
            } else {
                break;
            }
        }
    }

    allocSize = VM_ALIGN(nameLength + sizeof(MethodListNode));
    allocPtr = CHANSVmAlloc(vm, allocSize);
    listPtr->pNext = allocPtr;
    if (allocPtr != vmNull) {
        allocPtr->nameLength = nameLength;
        memcpy(listPtr->pNext->sName, methodName, nameLength);
        return index;
    }

error:
    return 0;
}

CHANSVmErr CHANSVmFindAndAddNativeProperty(CHANSVmNativeClass* cls, void* property, u32 propIndex) {
    CHANSVmNativeProperty** head = &cls->pNativeProperties;
    CHANSVmNativeProperty* node = *head;

    if (node == vmNull) {
        if (property != vmNull) {
            *head = property;
        }
    } else {
        while (vmTrue) {
            if (propIndex == node->index) {
                return CHANS_VM_ERR_ALREADY_DEFINED;
            }
            if (node->pNext == vmNull) {
                break;
            }
            node = node->pNext;
        }

        if (property != vmNull) {
            node->pNext = property;
        }
    }

    return CHANS_VM_OK;
}

CHANSVmErr CHANSVmFindAndAddNativeMethod(CHANSVmNativeClass* cls, CHANSVmNativeMethod* method, u32 methodIndex) {
    CHANSVmNativeMethod** head = &cls->pNativeMethods;
    CHANSVmNativeMethod* node = *head;

    if (node == vmNull) {
        if (method != vmNull) {
            *head = method;
        }
    } else {
        while (vmTrue) {
            if (methodIndex == node->index) {
                return CHANS_VM_ERR_ALREADY_DEFINED;
            }
            if (node->pNext == vmNull) {
                break;
            }
            node = node->pNext;
        }

        if (method != vmNull) {
            node->pNext = method;
        }
    }

    return CHANS_VM_OK;
}

CHANSVmErr CHANSVmAddNativeMethodList(CHANSVm* vm, CHANSVmNativeClass* cls, const CHANSVmMethodList* methods, vmSize methodCount) {
    u32 methodIndex;
    const char* name;
    CHANSVmFunction methodFunc;

    CHANSVmErr result = CHANS_VM_OK;
    u32 hasStar;

    for (; methodCount != 0 && methods != vmNull && result == CHANS_VM_OK; methods++, methodCount--) {
        hasStar = 0;
        methodFunc = methods->method;
        name = methods->spName;

        if (cls != vmNull) {
            if (*name == '*') {
                hasStar = 1;
                name++;
            }

            methodIndex = CHANSVmAddNativeMethodName(vm, name, strlen(name));

            if (methodIndex != 0) {
                result = CHANSVmFindAndAddNativeProperty(cls, vmNull, methodIndex);
                if (result != CHANS_VM_OK) {
                    continue;
                }

                {
                    CHANSVmNativeMethod* node = CHANSVmAlloc(vm, VM_ALIGN(sizeof(CHANSVmNativeMethod)));
                    if (node == vmNull) {
                        result = CHANS_VM_ERR_NO_MEMORY;
                    } else {
                        node->index = methodIndex;
                        node->func = methodFunc;
                        node->hasStar = hasStar;
                        result = CHANSVmFindAndAddNativeMethod(cls, node, methodIndex);
                    }
                    continue;
                }
            }
        }
        result = CHANS_VM_ERR_ADD_NATIVE_METHOD;
    }
    return result;
}

CHANSVmErr CHANSVmAddNativePropertyAccessors(CHANSVm* vm, CHANSVmNativeClass* cls, const char* name, CHANSVmFunction getter, CHANSVmFunction setter) {
    u32 methodIndex;
    CHANSVmErr result;
    u8 flag = 0;

    if (cls == vmNull) {
        goto error;
    }

    if (*name == '*') {
        flag = 1;
        name++;
    }

    methodIndex = CHANSVmAddNativeMethodName(vm, name, strlen(name));
    if (methodIndex == 0) {
        goto error;
    }

    result = CHANSVmFindAndAddNativeMethod(cls, vmNull, methodIndex);
    if (result == CHANS_VM_OK) {
        CHANSVmNativeProperty* node = CHANSVmAlloc(vm, VM_ALIGN(sizeof(CHANSVmNativeProperty)));
        if (node == vmNull) {
            return CHANS_VM_ERR_NO_MEMORY;
        }
        node->index = methodIndex;
        node->getter = getter;
        node->setter = setter;
        node->flag = flag;
        return CHANSVmFindAndAddNativeProperty(cls, node, methodIndex);
    error:
        return CHANS_VM_ERR_ADD_NATIVE_PROPERTY;
    }
    return result;
}

CHANSVmErr CHANSVmAddNativePropertyAccessorsList(CHANSVm* vm, CHANSVmNativeClass* cls, const CHANSVmPropertyList* properties, vmSize propertyCount) {
    CHANSVmErr result = CHANS_VM_OK;
    vmSize count = propertyCount;
    while (count != 0 && properties != vmNull && result == CHANS_VM_OK) {
        result = CHANSVmAddNativePropertyAccessors(vm, cls, properties->spName, properties->get, properties->set);
        properties++;
        count--;
    }
    return result;
}

void* CHANSVmAddGlobalObject(CHANSVm* vm, const char* globalName, vmBool allocateNewNode) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;
    GlobalObjListNode* listPtr;
    GlobalObjListNode* newNode;
    vmSize nameLength = strlen(globalName);

    if (nameLength != 0) {
        listPtr = pVm->pGlobalObjList;

        while (listPtr != vmNull) {
            if (nameLength == listPtr->nameLength) {
                if (memcmp(globalName, listPtr->name, nameLength) == 0) {
                    return listPtr;
                }
            }
            if (listPtr->next == vmNull) {
                break;
            }
            listPtr = listPtr->next;
        }

        if (allocateNewNode) {
            u32 allocSize = VM_ALIGN(nameLength + sizeof(GlobalObjListNode));
            newNode = CHANSVmAlloc(vm, allocSize);
            if (newNode != vmNull) {
                newNode->nameLength = nameLength;
                memcpy(newNode->name, globalName, nameLength);
                memset(newNode, 0, sizeof(CHANSVmObjHdr));
                newNode->hdr.flags.raw = CHANSVM_OBJ_FLAG_READONLY;

                if (listPtr == vmNull) {
                    pVm->pGlobalObjList = newNode;
                } else {
                    listPtr->next = newNode;
                }
                return newNode;
            }
        }
    }
    return vmNull;
}

CHANSVmErr CHANSVmSetObjectAsNativeInstance(CHANSVm* vm, CHANSVmObjHdr* obj, CHANSVmNativeClass* cls, const char* className) {
    CHANSVmErr result = CHANS_VM_ERR_SET_OBJECT_NATIVE_CLASS;
    if (obj != vmNull) {
        if (cls == vmNull && className != vmNull) {
            cls = CHANSVmFindNativeClass(vm, className);
        }

        if (cls != vmNull) {
            if (obj->type == CHANS_VM_OBJ_TYPE_BLANK || obj->type == CHANS_VM_TYPE_OBJECT && (obj->parentCls == vmNull || obj->parentCls == cls)) {
                obj->type = CHANS_VM_TYPE_OBJECT;
                obj->parentCls = cls;
                result = CHANS_VM_OK;
            } else {
                result = CHANS_VM_ERR_ALREADY_DEFINED;
            }
        }
    }
    return result;
}

CHANSVmObjHdr* CHANSVmConstructGlobalObject(CHANSVm* vm, const char* name, CHANSVmNativeClass* cls, CHANSVmFunction ctor) {
    CHANSVmObjHdr* obj = vmNull;
    if (cls != vmNull) {
        obj = CHANSVmAddGlobalObject(vm, name, vmTrue);
        if (obj != vmNull) {
            if (CHANSVmSetObjectAsNativeInstance(vm, obj, cls, vmNull) != CHANS_VM_OK || ctor != vmNull && !ctor(vm, vmNull, obj)) {
                obj = vmNull;
            }
        }
    }
    return obj;
}

vmBoolInt CHANSVmNewBuiltinObject(CHANSVm* vm, const char* className, CHANSVmFunction clsCtor, CHANSVmFunction clsDtor, CHANSVmFunction clsInit,
                                  const char* globalName, CHANSVmFunction globalCtor, const CHANSVmPropertyList* propAccessors, vmU32 propCount,
                                  const CHANSVmMethodList* methods, vmU32 methodCount) {
    CHANSVmNativeClass* cls = CHANSVmAddNativeClass2(vm, className, clsCtor, clsDtor, clsInit);
    if (cls != vmNull &&
        (propAccessors == vmNull || propCount == 0 || CHANSVmAddNativePropertyAccessorsList(vm, cls, propAccessors, propCount) == CHANS_VM_OK) &&
        (methods == vmNull || methodCount == 0 || CHANSVmAddNativeMethodList(vm, cls, methods, methodCount) == CHANS_VM_OK) &&
        (globalName == vmNull || CHANSVmConstructGlobalObject(vm, globalName, cls, globalCtor) != vmNull)) {
        return vmTrue;
    }
    return vmFalse;
}

vmBoolInt CHANSVmCheckNativeInstance(CHANSVmObjHdr* obj, const char* className) {
    if (obj != vmNull && obj->type == CHANS_VM_TYPE_OBJECT) {
        CHANSVmNativeClass* nativeClass = obj->parentCls;
        if (nativeClass != vmNull && className != vmNull && nativeClass->nameLength == strlen(className) &&
            strncmp(nativeClass->sName, className, nativeClass->nameLength) == 0) {
            return vmTrue;
        }
    }
    return vmFalse;
}

static CHANSVmErr VmArrayExpandCommon(CHANSVm* vm, CHANSVmObjHdr* obj, u32 startCount, u32 endCount, u32 fillFromArgs) {
    u32 total;
    u32 allocSize;
    ArrayChunk* chunk;
    ArrayChunk* current;
    u32 i;

    total = startCount + endCount;

    if (total == 0) {
        return vmTrue;
    }

    allocSize = VM_ALIGN(total * sizeof(CHANSVmObjHdr) + sizeof(ArrayChunk));
    chunk = CHANSVmAlloc(vm, allocSize);
    if (chunk == vmNull) {
        goto error;
    }

    chunk->capacity = allocSize;
    chunk->count = total;

    current = *obj->value.ptr_v;
    if (startCount != 0) {
        while (current->pNext != vmNull) {
            current = current->pNext;
        }
        current->pNext = chunk;
        chunk->pPrev = current;
    } else {
        while (current->pPrev != vmNull) {
            current = current->pPrev;
        }
        current->pPrev = chunk;
        chunk->pNext = current;
    }

    for (i = 0; i < total; i++) {
        if (fillFromArgs != 0 && i < ((CHANSVmPrivate*)vm)->pActiveCtx->argc && CHANSVmGetArg(vm, i) != vmNull) {
            CHANSVmObjHdr* arg = CHANSVmGetArg(vm, i);
            if (CHANSVmCopyObject(vm, &chunk->elements[i], arg) == vmNull) {
                goto error;
            }
            continue;
        }
        memset(&chunk->elements[i], 0, sizeof(CHANSVmObjHdr));
    }

    return vmTrue;

error:
    return vmFalse;
}

static ArrayChunk* VmArraySeekTop(CHANSVmObjHdr* array) {
    ArrayChunk* cur = vmNull;
    if (array != vmNull) {
        cur = *array->value.ptr_v;
        while (cur->pNext != vmNull) {
            cur = cur->pNext;
        }
    }
    return cur;
}

static u32 VmArrayGetLengthInternal(CHANSVmObjHdr* array) {
    u32 len = 0;
    ArrayChunk* chunk = VmArraySeekTop(array);
    while (chunk != vmNull) {
        len += chunk->count;
        chunk = chunk->pPrev;
    }
    return len;
}

static CHANSVmObjHdr* VmGetArrayElement(CHANSVm* vm, CHANSVmObjHdr* array, u32 index, s32 autoExpand) {
    ArrayChunk* chunk;
    u32 total;

    while (vmTrue) {
        total = 0;
        chunk = VmArraySeekTop(array);
        while (chunk != vmNull) {
            u32 count = chunk->count;
            u32 chunkEndIndex = total + count;
            if (index < chunkEndIndex) {
                u32 offset = chunk->start + index - total;
                return &chunk->elements[offset];
            }
            total += count;
            chunk = chunk->pPrev;
        }
        if (autoExpand != 0) {
            if (VmArrayExpandCommon(vm, array, 0, index - total + 1, vmFalse)) {
                autoExpand = 0;
                continue;
            }
        }
        return vmNull;
    }
}

CHANSVmObjHdr* CHANSVmGetArrayElement(CHANSVm* vm, CHANSVmObjHdr* array, u32 index) {
    if (array != vmNull && array->type == CHANS_VM_TYPE_ARRAY) {
        CHANSVmObjHdr* result = VmGetArrayElement(vm, array, index, vmFalse);
        if (result != vmNull) {
            return result;
        }
    }

    return vmNull;
}

const static char VmArrayClassName[] = "Array";

VmCtorDefine(Array) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)VmInst;
    CHANSVmObjHdr* arg;
    u32 value = pVm->pActiveCtx->argc;
    vmBoolInt fillArgs = vmTrue;

    if (value == 1) {
        arg = CHANSVmGetArg(VmInst, 0);
        if (arg != vmNull && arg->type == CHANS_VM_OBJ_TYPE_INTEGER) {
            if (arg->value.int_v <= (u64)~1U) {
                value = (u32)arg->value.int_v;
                fillArgs = vmFalse;
            }
        }
    }

    VmReturnObj->type = CHANS_VM_TYPE_ARRAY;
    VmReturnObj->parentCls = pVm->pArrayCls;

    if (CHANSVmNewObjData(VmInst, VmReturnObj, sizeof(ArrayChunk)) != vmNull) {
        if (value == 0 || VmArrayExpandCommon(VmInst, VmReturnObj, value, 0, (u32)fillArgs)) {
            return vmTrue;
        }
    }
    return vmFalse;
}

VmDtorDefine(Array) {
    u32 len;
    u32 i;
    CHANSVmObjHdr* elem;

    len = VmArrayGetLengthInternal(VmParentObj);
    for (i = 0; i < len; i++) {
        elem = VmGetArrayElement(VmInst, VmParentObj, i, vmFalse);
        if (CHANSVmDeleteObject(VmInst, elem) != CHANS_VM_OK) {
            goto error;
        }
    }
    return vmTrue;
error:
    return vmFalse;
}

CHANSVmObjHdr* CHANSVmGetArrayElement2D(CHANSVm* vm, vmPtr array, vmS32 outerIndex, vmS32 innerIndex) {
    CHANSVmObjHdr* elem = CHANSVmGetArrayElement(vm, array, outerIndex);
    if (elem != vmNull) {
        elem = VmGetArrayElement(vm, elem, innerIndex, vmFalse);
        if (elem != vmNull) {
            return elem;
        }
    }
    return vmNull;
}

CHANSVmObjHdr* CHANSVmGetArrayElement2DFloat(CHANSVm* vm, vmFloat* array, vmS32 outerIndex, vmS32 innerIndex) {
    return CHANSVmConvertObjectType(vm, CHANS_VM_OBJ_TYPE_FLOAT, CHANSVmGetArrayElement2D(vm, array, outerIndex, innerIndex));
}

u32 CHANSVmGetArrayLength(CHANSVm* vm, CHANSVmObjHdr* array) {
    if (array != vmNull && array->type == CHANS_VM_TYPE_ARRAY) {
        return VmArrayGetLengthInternal(array);
    }
    return 0;
}

static u32 VmArrayJoinEstimateStrSize(CHANSVmObjHdr* object, u32 sepLen) {
    ArrayChunk* chunk;
    u32 total;
    u32 countInChunk;
    s32 type;

    total = 0;
    chunk = VmArraySeekTop(object);
    while (chunk != vmNull) {
        countInChunk = chunk->start;
        while (countInChunk < chunk->start + chunk->count) {
            type = (s32)chunk->elements[countInChunk].type;

            switch (type) {
                case CHANS_VM_OBJ_TYPE_STRING: {
                    u32 strLen = chunk->elements[countInChunk].value.string_v->len;
                    total += strLen;
                    break;
                }
                case CHANS_VM_OBJ_TYPE_INTEGER:
                case CHANS_VM_OBJ_TYPE_FLOAT: {
                    total += 0x80;
                    break;
                }
                case CHANS_VM_TYPE_ARRAY: {
                    u32 strLen = VmArrayJoinEstimateStrSize(&chunk->elements[countInChunk], sepLen);
                    total += strLen;
                    break;
                }
                case CHANS_VM_OBJ_TYPE_BLANK: {
                    break;
                }
                default: {
                    CHANS_VM_PRINTF(318, ": unsupported type 0x%x\n", type);
                    goto error;
                }
            }
            total += sepLen;
            countInChunk++;
        }
        chunk = chunk->pPrev;
    }
    return total;

error:
    return 0;
}

static u32 VmArrayJoinSub(CHANSVmObjHdr* obj, CHANSVmObjHdr* array, wchar_t* separator, u32 sepLen, u32 bufSize, u32 offset) {
    ArrayChunk* chunk;
    u32 countInChunk;
    u32 savedOffset;
    vmString strBuf;
    u32 elemLen;

    savedOffset = offset;
    chunk = VmArraySeekTop(array);

    while (chunk != vmNull) {
        countInChunk = chunk->start;
        while (countInChunk < chunk->start + chunk->count) {
            s32 type = chunk->elements[countInChunk].type;

            switch (type) {
                case CHANS_VM_OBJ_TYPE_BLANK: {
                    elemLen = 0;
                    break;
                }
                case CHANS_VM_OBJ_TYPE_STRING: {
                    vmStringObjVal* strObj = chunk->elements[countInChunk].value.string_v;
                    elemLen = strObj->len;
                    if (offset + elemLen > bufSize) {
                        goto error;
                    }
                    memcpy((u8*)*obj->value.ptr_v + offset, strObj->spData, elemLen);
                    break;
                }
                case CHANS_VM_OBJ_TYPE_INTEGER: {
                    if (offset + 0x80 > bufSize) {
                        goto error;
                    }
                    strBuf = (vmString)(*obj->value.ptr_v) + offset;
                    elemLen = snprintf(strBuf, 0x40, VmIntegerFormat, chunk->elements[countInChunk].value.int_v);
                    CHANSVmStrCpyToU16FromU8((vmWString)strBuf, strBuf, elemLen);
                    elemLen = elemLen << 1;
                    break;
                }
                case CHANS_VM_OBJ_TYPE_FLOAT: {
                    if (offset + 0x80 > bufSize) {
                        goto error;
                    }
                    elemLen = CHANSVmFloatToWString((vmWString)((u8*)(*obj->value.ptr_v) + offset), 0x80, chunk->elements[countInChunk].value.float_v);
                    break;
                }
                case CHANS_VM_TYPE_ARRAY: {
                    elemLen = 0;
                    offset = VmArrayJoinSub(obj, &chunk->elements[countInChunk], separator, sepLen, bufSize, offset);
                    break;
                }
                default: {
                    CHANS_VM_PRINTF(389, ": unsupported type 0x%x\n", type);
                    goto error;
                }
            }

            offset += elemLen;
            if (separator != vmNull) {
                if (offset + sepLen > bufSize) {
                    goto error;
                }
                memcpy((u8*)*obj->value.ptr_v + offset, separator, sepLen);
                offset += sepLen;
            }
            countInChunk++;
        }
        chunk = chunk->pPrev;
    }

    if (separator != vmNull && savedOffset < offset) {
        offset -= sepLen;
        memset((u8*)*obj->value.ptr_v + offset, 0, sepLen);
    }
    return offset;
error:
    return 0;
}

CHANSVmObjHdr* VmArrayJoinCommon(CHANSVm* vm, u32 retObjAddr, CHANSVmObjHdr* object, u32 separatorAddr, u32 separatorLen) {
    CHANSVmObjHdr* result;
    u32 estSize;
    u32 actualLen;

    if (separatorAddr == 0) {
        separatorAddr = (u32)CHANSVmConstStringObjectComma.value.data.ptr;
        separatorLen = 2;
    }

    estSize = VmArrayJoinEstimateStrSize(object, separatorLen);
    result = CHANSVmNewObject(vm, vmFalse, (CHANSVmObjHdr*)retObjAddr, CHANS_VM_OBJ_TYPE_STRING, estSize);
    if (result != vmNull && estSize != 0) {
        actualLen = VmArrayJoinSub(result, object, (wchar_t*)separatorAddr, separatorLen, estSize, 0);
        result->value.string_v->len = actualLen;
    }
    return result;
}

VmMethodDefine(Array, Join) {
    CHANSVmObjHdr* arg;
    CHANSVmObjHdr* sepObj;
    u32 sepLen;
    u32 separatorAddr;

    arg = CHANSVmGetArg(VmInst, 0);
    sepObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, arg);
    sepLen = sepObj != vmNull ? sepObj->value.string_v->len : 0;
    separatorAddr = sepObj != vmNull ? (u32)sepObj->value.string_v->spData : 0;
    return VmArrayJoinCommon(VmInst, (u32)VmReturnObj, VmParentObj, separatorAddr, sepLen) != 0;
}

VmMethodDefine(Array, Slice) {
    s64 pos;
    u32 start;
    u32 end;
    u32 i;
    u32 newLen;
    CHANSVmObjHdr* startOrDestObj;
    CHANSVmObjHdr* endOrSourceObj;

    startOrDestObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));
    endOrSourceObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 1));
    start = 0;
    end = VmArrayGetLengthInternal(VmParentObj);

    if (startOrDestObj != vmNull) {
        pos = startOrDestObj->value.int_v;
        if (pos > end) {
            pos = end;
        } else if (pos < 0) {
            pos += end;
            if (pos < 0) {
                pos = 0;
            }
        }
        start = pos;
    }

    if (endOrSourceObj != vmNull) {
        pos = endOrSourceObj->value.int_v;
        if (pos > end) {
            pos = end;
        } else if (pos < 0) {
            pos += end;
            if (pos < 0) {
                pos = 0;
            }
        }
        end = pos;
    }
    newLen = end <= start ? 0 : end - start;

    if (CHANSVmNewArrayObject(VmInst, VmReturnObj, 1, &newLen) != vmNull) {
        for (i = 0; i < newLen; i++) {
            startOrDestObj = CHANSVmGetArrayElement(VmInst, VmReturnObj, i);
            endOrSourceObj = CHANSVmGetArrayElement(VmInst, VmParentObj, start + i);
            if (startOrDestObj == vmNull || endOrSourceObj == vmNull || CHANSVmCopyObject(VmInst, startOrDestObj, endOrSourceObj) == vmNull) {
                goto error;
            }
        }
        return vmTrue;
    }
error:
    return vmFalse;
}

CHANSVmObjHdr* CHANSVmNewArrayObject(CHANSVm* vm, CHANSVmObjHdr* object, vmU32 dimensions, vmSize* sizeEachDimension) {
    if (dimensions == 0 || sizeEachDimension == vmNull) {
        goto error;
    }

    object = CHANSVmNewObject(vm, vmFalse, object, CHANS_VM_TYPE_ARRAY, sizeof(ArrayChunk));
    if (object == vmNull) {
        goto error;
    }

    object->parentCls = ((CHANSVmPrivate*)vm)->pArrayCls;
    if (object->parentCls == vmNull) {
        goto error;
    }
    if (sizeEachDimension[0] != 0 && VmArrayExpandCommon(vm, object, sizeEachDimension[0], 0, vmFalse) == 0) {
        goto error;
    }
    if (dimensions > 1) {
        u32 i;
        for (i = 0; i < sizeEachDimension[0]; i++) {
            CHANSVmObjHdr* elem = VmGetArrayElement(vm, object, i, vmFalse);
            if (elem == vmNull || CHANSVmNewArrayObject(vm, elem, dimensions - 1, sizeEachDimension + 1) == vmNull) {
                goto error;
            }
        }
    }

    return object;
error:
    return vmNull;
}

VmMethodDefine(Array, New2d) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)VmInst;
    u32 sizes[0x12];
    u32 i;

    if (VmReturnObj == vmNull || pVm->pActiveCtx->argc != 2) {
        goto error;
    }

    for (i = 0; i < 2; i++) {
        CHANSVmObjHdr* arg = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, i));
        if (arg == vmNull || arg->value.int_v > 0xFFFFFFFEULL) {
            goto error;
        }
        sizes[i] = (u32)arg->value.int_v;
    }

    return (vmS32)CHANSVmNewArrayObject(VmInst, VmReturnObj, 2, sizes) != 0;
error:
    return vmFalse;
}

VmMethodDefine(Array, Shift) {
    ArrayChunk* chunk;
    CHANSVmObjHdr* elemPtr;

    chunk = VmArraySeekTop(VmParentObj);
    while (chunk != vmNull && chunk->count == 0) {
        chunk = chunk->pPrev;
    }

    if (chunk != vmNull && chunk->count != 0) {
        elemPtr = (CHANSVmObjHdr*)((u8*)chunk + sizeof(ArrayChunk) + chunk->start * 16);

        if (CHANSVmCopyObject(VmInst, VmReturnObj, elemPtr) == vmNull || CHANSVmDeleteObject(VmInst, elemPtr) != CHANS_VM_OK) {
            goto error;
        }
        chunk->start++;
        chunk->count--;
    }
    return vmTrue;
error:
    return vmFalse;
}

VmMethodDefine(Array, Unshift) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)VmInst;
    u32 argc = pVm->pActiveCtx->argc;

    if (VmArrayExpandCommon(VmInst, VmParentObj, argc, 0, vmTrue)) {
        u32 len = VmArrayGetLengthInternal(VmParentObj);
        return CHANSVmSetInteger(VmInst, VmReturnObj, len) == CHANS_VM_OK;
    }
    return vmFalse;
}

VmMethodDefine(Array, Push) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)VmInst;
    u32 argc = pVm->pActiveCtx->argc;

    if (VmArrayExpandCommon(VmInst, VmParentObj, 0, argc, vmTrue)) {
        u32 len = VmArrayGetLengthInternal(VmParentObj);
        return CHANSVmSetInteger(VmInst, VmReturnObj, len) == CHANS_VM_OK;
    }
    return vmFalse;
}

VmMethodDefine(Array, Pop) {
    ArrayChunk* chunk = VmArraySeekTop(VmParentObj);
    ArrayChunk* lastChunk = vmNull;

    while (chunk != vmNull) {
        if (chunk->count != 0) {
            lastChunk = chunk;
        }
        chunk = chunk->pPrev;
    }

    if (lastChunk != vmNull) {
        CHANSVmObjHdr* elemPtr = &lastChunk->elements[lastChunk->start + lastChunk->count - 1];
        if (VmReturnObj != vmNull) {
            memcpy(VmReturnObj, elemPtr, sizeof(CHANSVmObjHdr));
            VmReturnObj->flags.raw &= ~CHANSVM_OBJ_FLAG_READONLY;
            memset(elemPtr, 0, sizeof(CHANSVmObjHdr));
        } else if (CHANSVmDeleteObject(VmInst, elemPtr) != CHANS_VM_OK) {
            goto error;
        }
        lastChunk->count--;
    }
    return vmTrue;
error:
    return vmFalse;
}

VmMethodDefine(Array, GetLength) {
    u32 len = VmArrayGetLengthInternal(VmParentObj);
    return CHANSVmSetInteger(VmInst, VmReturnObj, len) == CHANS_VM_OK;
}

VmMethodDefine(Array, SetLength) {
    BOOL result = vmFalse;
    u32 oldLen = VmArrayGetLengthInternal(VmParentObj);
    u32 newLen;
    CHANSVmObjHdr* arg = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));

    if (arg != vmNull) {
        if (arg->value.int_v <= 0xFFFFFFFEULL) {
            newLen = arg->value.int_v;
            if (newLen < oldLen) {
                do {
                    if (!VmArrayPop(VmInst, VmParentObj, vmNull)) {
                        goto error;
                    }
                    oldLen--;
                } while (oldLen > newLen);
            } else if (newLen > oldLen) {
                if (VmGetArrayElement(VmInst, VmParentObj, newLen - 1, vmTrue) == vmNull) {
                    goto error;
                }
            }
            result = vmTrue;
        }
    }
    return result;
error:
    return vmFalse;
}

const CHANSVmPropertyList VmArrayPropertyTbl[] = {
    {"length", VmArrayGetLength, VmArraySetLength},
};
const CHANSVmMethodList VmArrayMethodTbl[] = {
    {"join", VmArrayJoin},   {"new2d", VmArrayNew2d}, {"pop", VmArrayPop},         {"push", VmArrayPush},
    {"shift", VmArrayShift}, {"slice", VmArraySlice}, {"unshift", VmArrayUnshift},
};

const CHANSVmIntConstantList VmDateConstantTbl[] = {
    // Avoid L".." because it inserts two null terminator bytes, but the original only used one, despite it being a wide string.
    {(const char*)"\0U\0T\0C", 6},
    {vmNull, 0}};

vmBoolInt VmDateCommon(CHANSVm* vm, OSCalendarTime* out) {
    u32 argc;
    u32 i;
    OSCalendarTime nettime;
    u64 time;

    if (out != vmNull) {
        argc = ((CHANSVmPrivate*)vm)->pActiveCtx->argc;

        if (argc == 0) {
            goto osgettime;
        }
        if (argc == 1) {
            CHANSVmObjHdr* arg = CHANSVmGetArg(vm, 0);

            if (arg && arg->type == CHANS_VM_OBJ_TYPE_STRING) {
                if (arg->value.wstring_v->len == 6 && memcmp(arg->value.wstring_v->spData, VmDateConstantTbl[0].spName, 6) == 0) {
                    NETGetUniversalCalendar(&nettime);
                    time = OSCalendarTimeToTicks(&nettime);
                    time = (u64)((s64)time / (__OSBusClock / 4 / 1000));
                    goto finalize;
                }
            }

            arg = CHANSVmGetArg(vm, 0);
            arg = CHANSVmConvertObjectType(vm, CHANS_VM_OBJ_TYPE_INTEGER, arg);
            if (arg) {
                time = arg->value.int_v;
                goto finalize;
            }
        }

        memset(&nettime, 0, sizeof(nettime));

        if (argc > 7) {
            argc = 7;
        }

        for (i = 0; i < argc; i++) {
            int* dst;
            CHANSVmObjHdr* arg = CHANSVmGetArg(vm, i);
            arg = CHANSVmConvertObjectType(vm, CHANS_VM_OBJ_TYPE_INTEGER, arg);
            if (arg == vmNull) {
                break;
            }

            switch (i) {
                case 0:
                    dst = &nettime.year;
                    break;
                case 1:
                    dst = &nettime.mon;
                    break;
                case 2:
                    dst = &nettime.mday;
                    break;
                case 3:
                    dst = &nettime.hour;
                    break;
                case 4:
                    dst = &nettime.min;
                    break;
                case 5:
                    dst = &nettime.sec;
                    break;
                case 6:
                    dst = &nettime.msec;
                    break;
                default:
                    CHANS_VM_PRINTF_CUSTOM("internal error in %s line %d\n", __FUNCTION__, 211);
                    return vmFalse;
            }

            *dst = (s32)arg->value.int_v;
        }

        if (nettime.year < 2000) {
            nettime.year = 2000;
        }
        if (nettime.mday < 1) {
            nettime.mday = 1;
        }

        time = OSCalendarTimeToTicks(&nettime);
        time = (u64)((s64)time / (__OSBusClock / 4 / 1000));
        goto finalize;

    osgettime:
        time = OSGetTime();
        time = (u64)((s64)time / (__OSBusClock / 4 / 1000));

    finalize:
        time = time * (__OSBusClock / 4 / 1000);
        OSTicksToCalendarTime((s64)time, out);
        return vmTrue;
    }
    return vmFalse;
}

VmCtorDefine(Date) {
    return VmDateCommon(VmInst, CHANSVmNewObjData(VmInst, VmReturnObj, sizeof(OSCalendarTime)));
}

#define RANGE(val, min, max) ((val) >= (min) && (val) <= (max))

const char* VmDateDayTbl[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char* VmDateMonthTbl[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

VmDtorDefine(Date) {
    char buffer[32];
    unsigned int uv;
    OSCalendarTime date;
    OSCalendarTime* datePtr;

    datePtr = &date;
    memset(datePtr, 0, sizeof(OSCalendarTime));

    if (VmDateCommon(VmInst, datePtr) && RANGE(datePtr->sec, 0, 61) && RANGE(datePtr->min, 0, 59) && RANGE(datePtr->hour, 0, 23) &&
        RANGE(datePtr->mday, 1, 31) && RANGE(datePtr->mon, 0, 11) && RANGE(datePtr->year, 1900, 9999) && RANGE(datePtr->wday, 0, 6)) {
        uv = snprintf(buffer, sizeof(buffer), "%s %s %02d %02d:%02d:%02d %04d", VmDateDayTbl[datePtr->wday], VmDateMonthTbl[datePtr->mon], datePtr->mday,
                      datePtr->hour, datePtr->min, datePtr->sec, datePtr->year);

        if (uv <= sizeof(buffer)) {
            return CHANSVmSetU16StringFromU8(VmInst, VmReturnObj, buffer, uv) == CHANS_VM_OK;
        }
    }

    return (CHANSVmNewObject(VmInst, vmFalse, VmReturnObj, CHANS_VM_OBJ_TYPE_STRING, 0) != 0);
}

VmMethodDefine(Date, GetDate) {
    OSCalendarTime* cal = *VmParentObj->value.ptr_v;
    return CHANSVmSetInteger(VmInst, VmReturnObj, cal->mday) == CHANS_VM_OK;
}

VmMethodDefine(Date, GetDay) {
    OSCalendarTime* cal = *VmParentObj->value.ptr_v;
    return CHANSVmSetInteger(VmInst, VmReturnObj, cal->wday) == CHANS_VM_OK;
}

VmMethodDefine(Date, GetFullYear) {
    OSCalendarTime* cal = *VmParentObj->value.ptr_v;
    return CHANSVmSetInteger(VmInst, VmReturnObj, cal->year) == CHANS_VM_OK;
}

VmMethodDefine(Date, GetHours) {
    OSCalendarTime* cal = *VmParentObj->value.ptr_v;
    return CHANSVmSetInteger(VmInst, VmReturnObj, cal->hour) == CHANS_VM_OK;
}

VmMethodDefine(Date, GetMilliseconds) {
    OSCalendarTime* cal = *VmParentObj->value.ptr_v;
    return CHANSVmSetInteger(VmInst, VmReturnObj, cal->msec) == CHANS_VM_OK;
}

VmMethodDefine(Date, GetMinutes) {
    OSCalendarTime* cal = *VmParentObj->value.ptr_v;
    return CHANSVmSetInteger(VmInst, VmReturnObj, cal->min) == CHANS_VM_OK;
}

VmMethodDefine(Date, GetMonth) {
    OSCalendarTime* cal = *VmParentObj->value.ptr_v;
    return CHANSVmSetInteger(VmInst, VmReturnObj, cal->mon) == CHANS_VM_OK;
}

VmMethodDefine(Date, GetSeconds) {
    OSCalendarTime* cal = *VmParentObj->value.ptr_v;
    return CHANSVmSetInteger(VmInst, VmReturnObj, cal->sec) == CHANS_VM_OK;
}

VmMethodDefine(Date, GetTime) {
    s64 time = OSCalendarTimeToTicks(*VmParentObj->value.ptr_v);
    s64 t = time / (__OSBusClock / 4 / 1000);
    return CHANSVmSetInteger(VmInst, VmReturnObj, t) == CHANS_VM_OK;
}

VmMethodDefine(Date, GetRTC) {
    OSCalendarTime* cal = *VmParentObj->value.ptr_v;
    u32 bias = SCGetCounterBias();
    s64 ticks = OSCalendarTimeToTicks(cal);
    u64 t = ticks / (__OSBusClock / 4 / 1000);
    t /= 1000;
    return CHANSVmSetInteger(VmInst, VmReturnObj, (t - bias) & 0xFFFFFFFFULL) == CHANS_VM_OK;
}

const CHANSVmMethodList VmDateMethodTbl[] = {
    {"getDate", VmDateGetDate},
    {"getDay", VmDateGetDay},
    {"getFullYear", VmDateGetFullYear},
    {"getHours", VmDateGetHours},
    {"getMilliseconds", VmDateGetMilliseconds},
    {"getMinutes", VmDateGetMinutes},
    {"getMonth", VmDateGetMonth},
    {"getSeconds", VmDateGetSeconds},
    {"getTime", VmDateGetTime},
    {"getRTC", VmDateGetRTC},
};

VmMethodDefine(Math, E) {
    return CHANSVmSetFloat(VmInst, VmReturnObj, M_E) == CHANS_VM_OK;
}
VmMethodDefine(Math, LN10) {
    return CHANSVmSetFloat(VmInst, VmReturnObj, M_LN10) == CHANS_VM_OK;
}
VmMethodDefine(Math, LN2) {
    return CHANSVmSetFloat(VmInst, VmReturnObj, M_LN2) == CHANS_VM_OK;
}
VmMethodDefine(Math, LOG2E) {
    return CHANSVmSetFloat(VmInst, VmReturnObj, M_LOG2E) == CHANS_VM_OK;
}
VmMethodDefine(Math, LOG10E) {
    return CHANSVmSetFloat(VmInst, VmReturnObj, M_LOG10E) == CHANS_VM_OK;
}
VmMethodDefine(Math, PI) {
    return CHANSVmSetFloat(VmInst, VmReturnObj, M_PI) == CHANS_VM_OK;
}
VmMethodDefine(Math, SQRT1_2) {
    return CHANSVmSetFloat(VmInst, VmReturnObj, M_SQRT1_2) == CHANS_VM_OK;
}
VmMethodDefine(Math, SQRT2) {
    return CHANSVmSetFloat(VmInst, VmReturnObj, M_SQRT2) == CHANS_VM_OK;
}
VmMethodDefine(Math, abs) {
    // u32 cast needed to avoid extra neg-instruction.
    u32 arg = (u32)CHANSVmGetArgFloat(VmInst, 0);
    return (arg != 0 && CHANSVmSetFloat(VmInst, VmReturnObj, fabs(((CHANSVmObjHdr*)arg)->value.float_v)) == CHANS_VM_OK);
}
VmMethodDefine(Math, acos) {
    CHANSVmObjHdr* arg = CHANSVmGetArgFloat(VmInst, 0);
    if (arg != vmNull) {
        vmFloat val = arg->value.float_v;
        vmFloat newVal;

        if (-1.0 <= val && val <= 1.0) {
            newVal = acos(val);
        } else {
            newVal = VM_NAN;
        }
        return CHANSVmSetFloat(VmInst, VmReturnObj, newVal) == CHANS_VM_OK;
    }
    return vmFalse;
}
VmMethodDefine(Math, asin) {
    CHANSVmObjHdr* arg = CHANSVmGetArgFloat(VmInst, 0);
    if (arg != vmNull) {
        vmFloat val = arg->value.float_v;
        vmFloat newVal;

        if (-1.0 <= val && val <= 1.0) {
            newVal = asin(val);
        } else {
            newVal = VM_NAN;
        }
        return CHANSVmSetFloat(VmInst, VmReturnObj, newVal) == CHANS_VM_OK;
    }
    return vmFalse;
}
VmMethodDefine(Math, atan) {
    CHANSVmObjHdr* arg = CHANSVmGetArgFloat(VmInst, 0);
    return arg != vmNull && CHANSVmSetFloat(VmInst, VmReturnObj, atan(arg->value.float_v)) == CHANS_VM_OK;
}
VmMethodDefine(Math, atan2) {
    CHANSVmObjHdr* yObj = CHANSVmGetArgFloat(VmInst, 0);
    CHANSVmObjHdr* xObj = CHANSVmGetArgFloat(VmInst, 1);
    return yObj != vmNull && xObj != vmNull && CHANSVmSetFloat(VmInst, VmReturnObj, atan2(yObj->value.float_v, xObj->value.float_v)) == CHANS_VM_OK;
}
VmMethodDefine(Math, ceil) {
    CHANSVmObjHdr* arg = CHANSVmGetArgFloat(VmInst, 0);
    return arg != vmNull && CHANSVmSetFloat(VmInst, VmReturnObj, ceil(arg->value.float_v)) == CHANS_VM_OK;
}
VmMethodDefine(Math, cos) {
    CHANSVmObjHdr* arg = CHANSVmGetArgFloat(VmInst, 0);
    return arg != vmNull && CHANSVmSetFloat(VmInst, VmReturnObj, cos(arg->value.float_v)) == CHANS_VM_OK;
}
VmMethodDefine(Math, exp) {
    CHANSVmObjHdr* arg = CHANSVmGetArgFloat(VmInst, 0);
    return arg != vmNull && CHANSVmSetFloat(VmInst, VmReturnObj, exp(arg->value.float_v)) == CHANS_VM_OK;
}
VmMethodDefine(Math, floor) {
    CHANSVmObjHdr* arg = CHANSVmGetArgFloat(VmInst, 0);
    return arg != vmNull && CHANSVmSetFloat(VmInst, VmReturnObj, floor(arg->value.float_v)) == CHANS_VM_OK;
}
VmMethodDefine(Math, log) {
    CHANSVmObjHdr* arg = CHANSVmGetArgFloat(VmInst, 0);
    return arg != vmNull && CHANSVmSetFloat(VmInst, VmReturnObj, log(arg->value.float_v)) == CHANS_VM_OK;
}
inline VmMethodDefine(Math, fmax) {
    CHANSVmObjHdr* leftObj = CHANSVmGetArgFloat(VmInst, 0);
    CHANSVmObjHdr* rightObj = CHANSVmGetArgFloat(VmInst, 1);
    return leftObj != vmNull && rightObj != vmNull && CHANSVmSetFloat(VmInst, VmReturnObj, fmax(leftObj->value.float_v, rightObj->value.float_v)) == CHANS_VM_OK;
}
VmMethodDefine(Math, max) {
    CHANSVmObjHdr* leftObj = CHANSVmGetArg(VmInst, 0);
    CHANSVmObjHdr* rightObj = CHANSVmGetArg(VmInst, 1);
    if (leftObj != vmNull && rightObj != vmNull) {
        if (leftObj->type == rightObj->type && leftObj->type == CHANS_VM_OBJ_TYPE_INTEGER) {
            if (leftObj->value.int_v < rightObj->value.int_v) {
                leftObj = rightObj;
            }

            return CHANSVmSetInteger(VmInst, VmReturnObj, leftObj->value.int_v) == CHANS_VM_OK;
        } else {
            return (VmMethod(Math, fmax))(VmInst, VmParentObj, VmReturnObj);
        }
    } else {
        return vmFalse;
    }
}
inline VmMethodDefine(Math, fmin) {
    CHANSVmObjHdr* leftObj = CHANSVmGetArgFloat(VmInst, 0);
    CHANSVmObjHdr* rightObj = CHANSVmGetArgFloat(VmInst, 1);
    return leftObj != vmNull && rightObj != vmNull && CHANSVmSetFloat(VmInst, VmReturnObj, fmin(leftObj->value.float_v, rightObj->value.float_v)) == CHANS_VM_OK;
}
VmMethodDefine(Math, min) {
    CHANSVmObjHdr* leftObj = CHANSVmGetArg(VmInst, 0);
    CHANSVmObjHdr* rightObj = CHANSVmGetArg(VmInst, 1);
    if (leftObj != vmNull && rightObj != vmNull) {
        if (leftObj->type == rightObj->type && leftObj->type == CHANS_VM_OBJ_TYPE_INTEGER) {
            if (leftObj->value.int_v > rightObj->value.int_v) {
                leftObj = rightObj;
            }

            return CHANSVmSetInteger(VmInst, VmReturnObj, leftObj->value.int_v) == CHANS_VM_OK;
        } else {
            return (VmMethod(Math, fmin))(VmInst, VmParentObj, VmReturnObj);
        }
    } else {
        return vmFalse;
    }
}
VmMethodDefine(Math, pow) {
    CHANSVmObjHdr* baseObj = CHANSVmGetArgFloat(VmInst, 0);
    CHANSVmObjHdr* exponentObj = CHANSVmGetArgFloat(VmInst, 1);
    return baseObj != vmNull && exponentObj != vmNull && CHANSVmSetFloat(VmInst, VmReturnObj, pow(baseObj->value.float_v, exponentObj->value.float_v)) == CHANS_VM_OK;
}
VmMethodDefine(Math, random) {
    return CHANSVmSetFloat(VmInst, VmReturnObj, rand() / 32767.0) == CHANS_VM_OK;
}
VmMethodDefine(Math, round) {
    CHANSVmObjHdr* arg = CHANSVmGetArgFloat(VmInst, 0);
    if (arg != vmNull) {
        vmFloat val = arg->value.float_v;
        vmFloat newVal;

        if (val > 0.0) {
            newVal = floor(val + 0.5);
        } else {
            newVal = ceil(val - 0.5);
        }
        return CHANSVmSetFloat(VmInst, VmReturnObj, newVal) == CHANS_VM_OK;
    } else {
        return vmFalse;
    }
}
VmMethodDefine(Math, sin) {
    CHANSVmObjHdr* arg = CHANSVmGetArgFloat(VmInst, 0);
    return arg != vmNull && CHANSVmSetFloat(VmInst, VmReturnObj, sin(arg->value.float_v)) == CHANS_VM_OK;
}
VmMethodDefine(Math, sqrt) {
    CHANSVmObjHdr* arg = CHANSVmGetArgFloat(VmInst, 0);
    if (arg != vmNull) {
        vmFloat val = arg->value.float_v;
        vmFloat newVal;

        if (arg->value.float_v < 0.0) {
            newVal = VM_NAN;
        } else {
            newVal = sqrt(val);
        }
        return CHANSVmSetFloat(VmInst, VmReturnObj, newVal) == CHANS_VM_OK;
    } else {
        return vmFalse;
    }
}
VmMethodDefine(Math, tan) {
    CHANSVmObjHdr* arg = CHANSVmGetArgFloat(VmInst, 0);
    return arg != vmNull && CHANSVmSetFloat(VmInst, VmReturnObj, tan(arg->value.float_v)) == CHANS_VM_OK;
}

const CHANSVmPropertyList VmMathPropertyTbl[] = {
    {"E", VmMathE, vmNull},           {"LN10", VmMathLN10, vmNull}, {"LN2", VmMathLN2, vmNull},         {"LOG2E", VmMathLOG2E, vmNull},
    {"LOG10E", VmMathLOG10E, vmNull}, {"PI", VmMathPI, vmNull},     {"SQRT1_2", VmMathSQRT1_2, vmNull}, {"SQRT2", VmMathSQRT2, vmNull},
};
const CHANSVmMethodList VmMathMethodTbl[] = {
    {"abs", VmMathabs}, {"acos", VmMathacos},     {"asin", VmMathasin},   {"atan", VmMathatan}, {"atan2", VmMathatan2}, {"ceil", VmMathceil},
    {"cos", VmMathcos}, {"exp", VmMathexp},       {"floor", VmMathfloor}, {"log", VmMathlog},   {"max", VmMathmax},     {"min", VmMathmin},
    {"pow", VmMathpow}, {"random", VmMathrandom}, {"round", VmMathround}, {"sin", VmMathsin},   {"sqrt", VmMathsqrt},   {"tan", VmMathtan},
};

const static char VmStringClassName[] = "String";

VmCtorDefine(String) {
    vmBoolInt ok;
    CHANSVmObjHdr* obj;

    if (((CHANSVmPrivate*)VmInst)->pActiveCtx->argc != 0) {
        obj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, CHANSVmGetArg(VmInst, 0));
        ok = vmFalse;
        if (obj && CHANSVmCopyObject(VmInst, VmReturnObj, obj)) {
            ok = vmTrue;
        }
        return ok;
    }
    obj = CHANSVmNewObject(VmInst, vmFalse, VmReturnObj, CHANS_VM_OBJ_TYPE_STRING, 0);
    ok = !!obj;
    return ok;
}

VmMethodDefine(String, FromCharCode) {
    CHANSVmObjHdr* arg;
    u32 argc;
    u32 ch;
    u32 i;

    if (VmParentObj != vmNull && VmParentObj->type == CHANS_VM_TYPE_CLASS_REF) {
        argc = ((CHANSVmPrivate*)VmInst)->pActiveCtx->argc;
        if (CHANSVmNewObject(VmInst, vmFalse, VmReturnObj, CHANS_VM_OBJ_TYPE_STRING, argc * 2)) {
            i = 0;
            while (i < argc) {
                arg = CHANSVmGetArg(VmInst, i);
                arg = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, arg);
                ch = arg != vmNull ? (u32)(arg->value.int_v & 0xFFFF) : 0;
                VmReturnObj->value.string_v->spData[i * 2] = (u8)(ch >> 8);
                VmReturnObj->value.string_v->spData[i * 2 + 1] = (u8)ch;
                i++;
            }
            return vmTrue;
        }
    }
    return vmFalse;
}

VmMethodDefine(String, GetLength) {
    return CHANSVmSetInteger(VmInst, VmReturnObj, VmParentObj->value.string_v->len >> 1) == CHANS_VM_OK;
}

VmMethodDefine(String, CharAt) {
    CHANSVmObjHdr* arg;
    s64 charIndex;
    u32 size = 0;

    arg = CHANSVmGetArg(VmInst, 0);
    arg = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, arg);
    if (arg != vmNull) {
        charIndex = arg->value.int_v;

        if ((u64)(charIndex * 2) < VmParentObj->value.string_v->len) {
            size = 2;
        }

        if (CHANSVmNewObject(VmInst, vmFalse, VmReturnObj, CHANS_VM_OBJ_TYPE_STRING, size)) {
            if (size != 0) {
                memcpy(VmReturnObj->value.string_v->spData, VmParentObj->value.string_v->spData + (u32)charIndex * 2, size);
            }
            return vmTrue;
        }
    }
    return vmFalse;
}

VmMethodDefine(String, CharCodeAt) {
    u32 ch = 0;
    CHANSVmObjHdr* arg;
    s64 charIndex;
    vmStringObjVal* parentStr;

    arg = CHANSVmGetArg(VmInst, 0);
    arg = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, arg);
    if (arg == vmNull) {
        goto error;
    }

    parentStr = VmParentObj->value.string_v;
    charIndex = arg->value.int_v;
    if ((u64)(charIndex * 2) < (u64)(parentStr->len)) {
        u32 data = (u32)parentStr->spData;
        ch = *(u8*)(data + (u32)(charIndex * 2)) << 8 | *(u8*)(data + (u32)(charIndex * 2) + 1);
    }

    return CHANSVmSetInteger(VmInst, VmReturnObj, (vmInteger)(u64)ch) == CHANS_VM_OK;

error:
    return vmFalse;
}

static CHANSVmObjHdr* VmStringObjectDup(CHANSVm* VmInst, CHANSVmObjHdr* outObj, CHANSVmObjHdr* inObj) {
    CHANSVmObjHdr* result = vmNull;
    if (inObj != vmNull && inObj->type == CHANS_VM_OBJ_TYPE_STRING) {
        result = CHANSVmNewObject(VmInst, vmFalse, outObj, CHANS_VM_OBJ_TYPE_STRING, inObj->value.string_v->len);
        if (result != vmNull) {
            memcpy(result->value.string_v->spData, inObj->value.string_v->spData, result->value.string_v->len);
        }
    }
    return result;
}

static vmBoolInt VmStringObjectIndex(CHANSVm* VmInst, CHANSVmObjHdr* VmParentObj, CHANSVmObjHdr* VmReturnObj, u32 searchForward, u32 skipStartArg) {
    CHANSVmObjHdr* searchObj;
    CHANSVmObjHdr* startObj;
    vmStringObjVal* parentStrVal;
    vmStringObjVal* searchStrVal;
    u32 parentLen;
    u32 searchLen;
    vmString parentStr;
    vmString searchStr;
    u32 pos;
    s64 retVal;

    pos = 0;
    startObj = vmNull;
    searchObj = CHANSVmGetArg(VmInst, 0);
    searchObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, searchObj);

    if (searchObj != vmNull) {
        if (skipStartArg == 0) {
            startObj = CHANSVmGetArg(VmInst, 1);
            startObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, startObj);
        }

        parentStrVal = VmParentObj->value.string_v;
        parentLen = parentStrVal->len;
        pos = searchForward ? 0 : parentLen;

        if (startObj != vmNull) {
            if (startObj->value.int_v <= 0x7FFFFFFFULL) {
                pos = (u32)(startObj->value.int_v * 2);
                if (pos > parentLen) {
                    pos = parentLen;
                }
            } else {
                pos = 0;
            }
        }

        searchStrVal = searchObj->value.string_v;
        searchLen = searchStrVal->len;

        if (searchLen == 0) {
            goto found_result;
        }

        if (parentLen >= searchLen) {
            parentStr = parentStrVal->spData;
            searchStr = searchStrVal->spData;

            if (searchForward) {
                while (pos + searchLen <= parentLen) {
                    if (memcmp(parentStr + pos, searchStr, searchLen) == 0) {
                        goto found_result;
                    }
                    pos += 2;
                }
            } else {
                if (pos + searchLen > parentLen) {
                    pos = parentLen - searchLen;
                }
                do {
                    if (memcmp(parentStr + pos, searchStr, searchLen) == 0) {
                        goto found_result;
                    }
                    if (pos < 2) {
                        break;
                    }
                    pos -= 2;
                } while (vmTrue);
            }
        }
    }

    retVal = -1;
    goto exit;

found_result:
    retVal = pos / 2;

exit:
    return CHANSVmSetInteger(VmInst, VmReturnObj, retVal) == CHANS_VM_OK;
}

VmMethodDefine(String, IndexOf) {
    return VmStringObjectIndex(VmInst, VmParentObj, VmReturnObj, 1, 0);
}

VmMethodDefine(String, LastIndexOf) {
    return VmStringObjectIndex(VmInst, VmParentObj, VmReturnObj, 0, 0);
}

VmMethodDefine(String, Search) {
    return VmStringObjectIndex(VmInst, VmParentObj, VmReturnObj, 1, 1);
}

static inline vmBoolInt VmReplaceStringContents(CHANSVm *VmInst, const CHANSVmObjHdr *VmParentObj, CHANSVmObjHdr *VmReturnObj) {
    CHANSVmObjHdr* searchObj;
    vmString replaceStr;
    vmString searchStr;
    vmString parentStr;
    vmString newStr;
    u32 dstBufLen;
    u32 replaceLen;
    u32 dstOffs;
    CHANSVmObjHdr* replacementObj;
    u32 searchLen;
    u32 srcOffs;
    u32 parentLen;
    u32 segLen;
    const vmStringObjVal *parentValue;
    const vmStringObjVal *searchValue;

    if (((CHANSVmPrivate*)VmInst)->pActiveCtx->argc < 2) {
        goto return_input;
    }

    searchObj = CHANSVmGetArg(VmInst, 0);
    searchObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, searchObj);
    replacementObj = CHANSVmGetArg(VmInst, 1);
    replacementObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, replacementObj);

    if (searchObj == vmNull || replacementObj == vmNull) {
        goto return_input;
    }

    parentValue = VmParentObj->value.string_v;
    searchValue = searchObj->value.string_v;
    parentLen = parentValue->len;
    searchLen = searchValue->len;
    parentStr = parentValue->spData;
    searchStr = searchValue->spData;
    replaceStr = replacementObj->value.string_v->spData;
    replaceLen = replacementObj->value.string_v->len;

    if (parentLen < searchLen) {
        goto return_input;
    }

    newStr = vmNull;
    dstBufLen = 0;

    while (vmTrue) {
        dstOffs = 0;
        srcOffs = 0;

        while (srcOffs + searchLen <= parentLen) {
            if (searchLen == 0 || memcmp(parentStr + srcOffs, searchStr, searchLen) == 0) {
                if (replaceLen != 0) {
                    if (newStr != vmNull) {
                        if (dstOffs + replaceLen > dstBufLen) {
                            goto error;
                        }
                        memcpy(newStr + dstOffs, replaceStr, replaceLen);
                    }
                    dstOffs += replaceLen;
                }

                if (searchLen == 0) {
                    break;
                }
                srcOffs += searchLen;
            } else {
                if (newStr != vmNull) {
                    if (dstOffs + 2 > dstBufLen) {
                        goto error;
                    }
                    memcpy(newStr + dstOffs, parentStr + srcOffs, 2);
                }
                srcOffs += 2;
                dstOffs += 2;
            }
        }

        if (srcOffs < parentLen) {
            segLen = parentLen - srcOffs;
            if (newStr != vmNull) {
                if (dstOffs + segLen > dstBufLen) {
                    goto error;
                }
                memcpy(newStr + dstOffs, parentStr + srcOffs, segLen);
            }
            dstOffs += segLen;
        }

        if (newStr == vmNull) {
            dstBufLen = dstOffs;
            if (!CHANSVmNewObject(VmInst, vmFalse, VmReturnObj, CHANS_VM_OBJ_TYPE_STRING, dstBufLen)) {
                goto error;
            }
            newStr = VmReturnObj->value.string_v->spData;
        } else {
            break;
        }
    }

    return VmReturnObj->value.string_v->len == dstOffs ? vmTrue : vmFalse;

return_input:
    return VmStringObjectDup(VmInst, VmReturnObj, (CHANSVmObjHdr *)VmParentObj) ? vmTrue : vmFalse;

error:
    return 0;
}

VmMethodDefine(String, Replace) {
    return VmReplaceStringContents(VmInst, VmParentObj, VmReturnObj);
}

VmMethodDefine(String, Splice) {
    CHANSVmObjHdr* startObj;
    CHANSVmObjHdr* endObj;
    u32 length;
    u32 start;
    u32 newLen;

    startObj = CHANSVmGetArg(VmInst, 0);
    startObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, startObj);
    endObj = CHANSVmGetArg(VmInst, 1);
    endObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, endObj);

    start = 0;
    length = VmParentObj->value.string_v->len;

    if (startObj != vmNull) {
        s64 startByteOffset = startObj->value.int_v * 2;
        if (startByteOffset > length) {
            start = length;
        } else {
            start = startByteOffset;
            if (startByteOffset < 0) {
                s64 relativeStart = startByteOffset + length;
                start = relativeStart;
                if (relativeStart < 0) {
                    start = 0;
                }
            }
        }
    }

    if (endObj != vmNull) {
        u32 endOffset;
        s64 endByteOffset = endObj->value.int_v * 2;
        if (endByteOffset > length) {
            endOffset = length;
        } else {
            endOffset = endByteOffset;
            if (endByteOffset < 0) {
                s64 relativeEnd = endByteOffset + length;
                endOffset = relativeEnd;
                if (relativeEnd < 0) {
                    endOffset = 0;
                }
            }
        }
        length = endOffset;
    }

    newLen = start >= length ? 0 : length - start;

    if (CHANSVmNewObject(VmInst, vmFalse, VmReturnObj, CHANS_VM_OBJ_TYPE_STRING, newLen) != vmNull) {
        if (newLen != 0) {
            memcpy(VmReturnObj->value.string_v->spData, VmParentObj->value.string_v->spData + start, newLen);
        }
        return vmTrue;
    }
    return vmFalse;
}

VmMethodDefine(String, Split) {
    u32 remaining;
    CHANSVmObjHdr* tailElement;
    u32 parentLen;
    vmString parentStr;
    u32 segStart;
    u32 limit;
    u32 delimLen;
    u32 srcOffs;
    vmString delimStr;
    CHANSVmObjHdr* limitObj;
    CHANSVmObjHdr* elem;
    CHANSVmObjHdr* array;
    u32 count;
    CHANSVmObjHdr* delimiterObj;
    u32 segLen;
    u32 arrayCount;

    arrayCount = 0;
    delimiterObj = CHANSVmGetArg(VmInst, 0);
    delimiterObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, delimiterObj);
    if (delimiterObj == vmNull) {
        arrayCount = 1;
        goto create_array;
    }

    limit = -1;
    if (((CHANSVmPrivate*)VmInst)->pActiveCtx->argc > 1) {
        limitObj = CHANSVmGetArg(VmInst, 1);
        limitObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, limitObj);
        if (limitObj != vmNull) {
            if ((u64)limitObj->value.int_v < 0xFFFFFFFF) {
                limit = (u32)limitObj->value.int_v;
                if (limit == 0) {
                    goto create_array;
                }
            }
        }
    }

    parentStr = VmParentObj->value.string_v->spData;
    delimStr = delimiterObj->value.string_v->spData;
    delimLen = delimiterObj->value.string_v->len;
    parentLen = VmParentObj->value.string_v->len;

    if (delimLen == 0) {
        if (parentLen != 0) {
            goto zero_delim_loop;
        }
        goto create_array;
    }

    array = vmNull;

    while (vmTrue) {
        srcOffs = 0;
        segStart = 0;
        count = 0;
        while (srcOffs + delimLen <= parentLen) {
            if (memcmp(parentStr + srcOffs, delimStr, delimLen) == 0) {
                segLen = srcOffs - segStart;
                if (array != vmNull) {
                    elem = CHANSVmGetArrayElement(VmInst, array, count);
                    if (elem == vmNull || !CHANSVmNewObject(VmInst, vmFalse, elem, CHANS_VM_OBJ_TYPE_STRING, segLen)) {
                        goto error;
                    }
                    memcpy(elem->value.string_v->spData, parentStr + segStart, segLen);
                }
                count++;
                srcOffs += delimLen;
                segStart = srcOffs;
                if (count >= limit) {
                    break;
                }
            } else {
                srcOffs += 2;
            }
        }

        if (count < limit) {
            remaining = parentLen - segStart;
            if (array != vmNull) {
                tailElement = CHANSVmGetArrayElement(VmInst, array, count);
                if (tailElement == vmNull || !CHANSVmNewObject(VmInst, vmFalse, tailElement, CHANS_VM_OBJ_TYPE_STRING, remaining)) {
                    goto error;
                }
                memcpy(tailElement->value.string_v->spData, parentStr + segStart, remaining);
            }
            count++;
        }

        if (array == vmNull) {
            arrayCount = count;
            array = CHANSVmNewArrayObject(VmInst, VmReturnObj, 1, &arrayCount);
            if (array == vmNull) {
                goto error;
            }
        } else {
            return arrayCount == count;
        }
    }

create_array:
    array = CHANSVmNewArrayObject(VmInst, VmReturnObj, 1, &arrayCount);
    if (arrayCount != 0) {
        elem = CHANSVmGetArrayElement(VmInst, array, 0);
    } else {
        elem = vmNull;
    }
    return array != vmNull && (arrayCount == 0 || (elem != vmNull && VmStringObjectDup(VmInst, elem, VmParentObj) != vmNull));

zero_delim_loop:
    arrayCount = parentLen / 2;
    array = CHANSVmNewArrayObject(VmInst, VmReturnObj, 1, &arrayCount);
    count = 0;
    segStart = 0;
    while (count < arrayCount) {
        elem = CHANSVmGetArrayElement(VmInst, array, count);
        if (elem == vmNull || !CHANSVmNewObject(VmInst, vmFalse, elem, CHANS_VM_OBJ_TYPE_STRING, 2)) {
            goto error;
        }
        memcpy(elem->value.string_v->spData, parentStr + segStart, 2);
        count++;
        segStart += 2;
    }
    return vmTrue;

error:
    return vmFalse;
}

VmMethodDefine(String, ToLowerCase) {
    if (VmStringObjectDup(VmInst, VmReturnObj, VmParentObj) != vmNull) {
        u32 i = 0;
        while (i < VmReturnObj->value.string_v->len) {
            u32 ch = (u32)(u8)VmReturnObj->value.string_v->spData[i] << 8 | (u8)VmReturnObj->value.string_v->spData[i + 1];
            if (ch >= 'A' && ch <= 'Z') {
                VmReturnObj->value.string_v->spData[i + 1] = (u8)(ch | 0x20);
            } else if (ch >= (0xFF00 | '!') && ch <= (0xFF00 | ':')) {
                VmReturnObj->value.string_v->spData[i + 1] += 0x20;
            }
            i += 2;
        }
        return vmTrue;
    }
    return vmFalse;
}

VmMethodDefine(String, ToUpperCase) {
    if (VmStringObjectDup(VmInst, VmReturnObj, VmParentObj) != vmNull) {
        u32 i = 0;
        while (i < VmReturnObj->value.string_v->len) {
            u32 ch = (u32)(u8)VmReturnObj->value.string_v->spData[i] << 8 | (u8)VmReturnObj->value.string_v->spData[i + 1];
            if (ch >= 'a' && ch <= 'z') {
                VmReturnObj->value.string_v->spData[i + 1] = (u8)(ch & 0xDF);
            } else if (ch >= (0xFF00 | 'A') && ch <= (0xFF00 | 'Z')) {
                VmReturnObj->value.string_v->spData[i + 1] -= 0x20;
            }
            i += 2;
        }
        return vmTrue;
    }
    return vmFalse;
}

CHANSVmObjHdr* CHANSVmFormatString(CHANSVm* vm, CHANSVmObjHdr* obj, u32 arg) {
    u8 charBuffer[8];
    CHANSVmObjHdr* formattedObj;
    u8 stringHeaderBuffer[16];
    u8 fmtBufData[32];
    u8* fmtBuf;
    wchar_t wideFmt[32];
    u32 halfMaxSize;
    BOOL alternateForm;
    CHANSVmObjHdr* stringArg;
    u32 argIdxCounter;
    u32 totalLen;
    u8* str;
    u32 strLen;
    u32 strPos;
    u32 segStart;
    u32 fmtBufPos;
    u8* workBuffer;
    u32 maxSize;
    u8* outputBuf;
    u32 outputPos;
    u32 maxLitLen;
    u32 litLen;
    u32 isEscaped;
    CHANSVmObjHdr* valueObj;
    CHANSVmPrivate* pVm;
    CHANSVmObjHdr* argObj;

    pVm = (CHANSVmPrivate*)vm;
    memset(stringHeaderBuffer, 0, sizeof(stringHeaderBuffer));

    if (pVm->pActiveCtx->argc == 0) {
        goto empty_create;
    }

    argObj = CHANSVmGetArg(vm, arg);
    if (argObj == vmNull || argObj->type != CHANS_VM_OBJ_TYPE_STRING) {
        goto null_return;
    }

    fmtBuf = fmtBufData;
    maxSize = pVm->minWorkSize;
    outputBuf = vmNull;
    outputPos = 0;
    halfMaxSize = maxSize >> 1;
    str = (u8*)argObj->value.string_v->spData;
    strLen = argObj->value.string_v->len & ~1U;
    workBuffer = pVm->pBase;
    totalLen = 0;
    maxLitLen = 0;

    while (vmTrue) {
        strPos = 0;
        segStart = 0;
        argIdxCounter = 1;

        while (strPos < strLen) {
        // Label allows to continue without checking the condition
        format_continue:;
            if (str[strPos] != 0 || str[strPos + 1] != '%') {
                strPos += 2;
                if (strPos < strLen) {
                    continue;
                }
            }

            if (strPos + 2 < strLen && str[strPos + 2] == 0 && str[strPos + 3] == '%') {
                isEscaped = 1;
                strPos += 2;
            } else {
                isEscaped = 0;
            }

            litLen = strPos - segStart;

            if (outputBuf != vmNull) {
                if (outputPos + litLen > totalLen) {
                    goto null_return;
                }
                memcpy(outputBuf + outputPos, str + segStart, litLen);
                outputPos += litLen;
            } else {
                totalLen += litLen;
            }

            segStart = strPos;
            if (strPos >= strLen) {
                break;
            }

            if (isEscaped != 0) {
                strPos += 2;
            } else {
                fmtBuf[0] = '%';
                litLen = 0;
                fmtBufPos = 1;
                alternateForm = vmFalse;
                strPos += 2;

                while (strPos < strLen && str[strPos] == 0) {
                    switch (str[strPos + 1] - 32) {
                        case 32: {
                            goto format_continue;
                        }
                        case 3: {
                            alternateForm = vmTrue;
                        }
                        case 0:
                        case 11:
                        case 13:
                        case 16: {
                            if (fmtBufPos + 1 >= sizeof(fmtBufData))
                                goto format_continue;
                            fmtBuf[fmtBufPos++] = str[strPos + 1];
                            strPos += 2;
                            continue;
                        }
                    }
                    break;
                }

                while (strPos < strLen && str[strPos] == 0 && str[strPos + 1] >= '0' && str[strPos + 1] <= '9') {
                    if (fmtBufPos + 1 >= sizeof(fmtBufData)) {
                        goto format_continue;
                    }
                    fmtBuf[fmtBufPos++] = str[strPos + 1];
                    strPos += 2;
                }

                if (strPos < strLen && str[strPos] == 0 && str[strPos + 1] == '.') {
                    if (fmtBufPos + 1 >= sizeof(fmtBufData)) {
                        goto format_continue;
                    }
                    fmtBuf[fmtBufPos++] = str[strPos + 1];
                    strPos += 2;

                    while (strPos < strLen && str[strPos] == 0 && str[strPos + 1] >= '0' && str[strPos + 1] <= '9') {
                        if (fmtBufPos + 1 >= sizeof(fmtBufData)) {
                            goto format_continue;
                        }
                        fmtBuf[fmtBufPos++] = str[strPos + 1];
                        strPos += 2;
                    }
                }

                while (strPos < strLen && str[strPos] == 0 &&
                       (str[strPos + 1] == 'h' || str[strPos + 1] == 'l' || str[strPos + 1] == 'L' || str[strPos + 1] == 'v')) {
                    strPos += 2;
                }

                if (strPos >= strLen || str[strPos] != 0) {
                    continue;
                }

                {
                    void* stringData;
                    u8 conversionChar = str[strPos + 1];
                    switch (conversionChar) {
                        case 'A':
                        case 'B':
                        case 'C':
                        case 'D': {
                            continue;
                        }
                        case 'd':
                        case 'i':
                        case 'o':
                        case 'u':
                        case 'x':
                        case 'X': {
                            strPos += 2;
                            goto int_body;
                        }
                        case 'E':
                        case 'F':
                        case 'G':
                        case 'e':
                        case 'f':
                        case 'g': {
                            strPos += 2;
                            goto float_body;
                        }
                        case 'c': {
                            strPos += 2;
                            goto char_body;
                        }
                        case 's': {
                            strPos += 2;
                            goto string_body;
                        }
                        default: {
                            continue;
                        }
                    }

                int_body: {
                    if (fmtBufPos + 3 >= (s32)sizeof(fmtBufData)) {
                        goto format_continue;
                    }
                    fmtBuf[fmtBufPos++] = 'l';
                    fmtBuf[fmtBufPos++] = 'l';
                    fmtBuf[fmtBufPos++] = conversionChar;
                    fmtBuf[fmtBufPos] = 0;
                    valueObj = CHANSVmConvertObjectType(vm, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(vm, arg + argIdxCounter));
                }

                common_number_format: {
                    argIdxCounter++;
                    if (valueObj == vmNull) {
                        goto loop_hint;
                    }
                    if (litLen != 0) {
                        isEscaped = snprintf((char*)workBuffer, maxSize, (char*)fmtBufData, valueObj->value.float_v);
                    } else {
                        isEscaped = snprintf((char*)workBuffer, maxSize, (char*)fmtBufData, valueObj->value.int_v);
                    }

                    if ((s32)isEscaped < 0) {
                        goto format_continue;
                    }
                    litLen = isEscaped * 2;
                    if (outputBuf != vmNull) {
                        if (outputPos + litLen > totalLen) {
                            goto null_return;
                        }
                        CHANSVmStrCpyToU16FromU8((wchar_t*)(outputBuf + outputPos), (char*)workBuffer, litLen >> 1);
                        outputPos += litLen;
                    } else {
                        if (maxLitLen < litLen)
                            maxLitLen = litLen;
                        totalLen += litLen;
                    }
                    goto loop_hint;
                }

                float_body: {
                    if (fmtBufPos + 2 >= sizeof(fmtBufData))
                        goto format_continue;
                    fmtBuf[fmtBufPos++] = 'l';
                    fmtBuf[fmtBufPos++] = conversionChar;
                    fmtBuf[fmtBufPos] = 0;
                    valueObj = CHANSVmConvertObjectType(vm, CHANS_VM_OBJ_TYPE_FLOAT, CHANSVmGetArg(vm, arg + argIdxCounter));
                    litLen = 1;
                    goto common_number_format;
                }

                char_body: {
                    valueObj = CHANSVmConvertObjectType(vm, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(vm, arg + argIdxCounter));
                    argIdxCounter++;
                    if (valueObj == vmNull) {
                        goto loop_hint;
                    }
                    stringData = charBuffer;
                    *(u16*)charBuffer = valueObj->value.int_v;
                    *(u16*)(charBuffer + 2) = 0;
                    formattedObj = vmNull;
                    goto common_string_format;
                }

                string_body: {
                    u32 objLen;
                    stringArg = CHANSVmConvertObjectType(vm, CHANS_VM_OBJ_TYPE_STRING, CHANSVmGetArg(vm, arg + argIdxCounter));
                    argIdxCounter++;
                    if (stringArg == vmNull) {
                        goto loop_hint;
                    }

                    objLen = stringArg->value.string_v->len & ~1U;
                    {
                        formattedObj = CHANSVmNewObject(vm, vmFalse, (CHANSVmObjHdr*)stringHeaderBuffer, CHANS_VM_OBJ_TYPE_STRING, objLen + 2);
                        if (formattedObj == vmNull) {
                            goto null_return;
                        }
                        stringData = formattedObj->value.string_v->spData;
                        memcpy(stringData, stringArg->value.string_v->spData, objLen);
                    }
                }

                common_string_format:
                    if (alternateForm || fmtBufPos + 2 >= sizeof(fmtBufData)) {
                        goto format_continue;
                    }
                    fmtBuf[fmtBufPos++] = 'l';
                    fmtBuf[fmtBufPos++] = 's';
                    fmtBuf[fmtBufPos] = 0;

                    CHANSVmStrCpyToU16FromU8(wideFmt, (char*)fmtBuf, fmtBufPos);
                    wideFmt[fmtBufPos] = 0;

                    isEscaped = swprintf((wchar_t*)workBuffer, halfMaxSize, wideFmt, stringData);
                    if ((s32)isEscaped < 0) {
                        goto format_continue;
                    }

                    if (formattedObj != vmNull) {
                        if (CHANSVmDeleteObject(vm, formattedObj) != CHANS_VM_OK) {
                            goto null_return;
                        }
                    }

                    litLen = isEscaped * 2;
                    if (outputBuf != vmNull) {
                        if (outputPos + litLen > totalLen) {
                            goto null_return;
                        }
                        memcpy(outputBuf + outputPos, workBuffer, litLen);
                        outputPos += litLen;
                    } else {
                        if (maxLitLen < litLen) {
                            maxLitLen = litLen;
                        }
                        totalLen += litLen;
                    }
                }
            }

        loop_hint:
            segStart = strPos;
        }

        if (outputBuf == vmNull) {
            obj = CHANSVmNewObject(vm, vmFalse, obj, CHANS_VM_OBJ_TYPE_STRING, totalLen);
            if (obj == vmNull) {
                goto null_return;
            }
            outputBuf = (u8*)obj->value.string_v->spData;
        } else {
            break;
        }
    }

    if (outputPos != totalLen) {
        goto null_return;
    }
    return obj;

empty_create:
    return CHANSVmNewObject(vm, vmFalse, obj, CHANS_VM_OBJ_TYPE_STRING, 0);

null_return:
    return vmNull;
}

VmMethodDefine(String, Format) {
    u32 result;
    if (VmParentObj != vmNull && VmParentObj->type == CHANS_VM_TYPE_CLASS_REF) {
        result = (u32)CHANSVmFormatString(VmInst, VmReturnObj, 0);
        return result != 0;
    }
    return vmFalse;
}

const CHANSVmPropertyList VmStringPropertyTbl[] = {
    {"length", VmStringGetLength, vmNull},
};
const CHANSVmMethodList VmStringMethodTbl[] = {
    {"charAt", VmStringCharAt},   {"charCodeAt", VmStringCharCodeAt},   {"*fromCharCode", VmStringFromCharCode},
    {"*format", VmStringFormat},  {"indexOf", VmStringIndexOf},         {"lastIndexOf", VmStringLastIndexOf},
    {"replace", VmStringReplace}, {"search", VmStringSearch},           {"slice", VmStringSplice},
    {"split", VmStringSplit},     {"toLowerCase", VmStringToLowerCase}, {"toUpperCase", VmStringToUpperCase},
};

vmString VmGetStrFromObjHdr(CHANSVmObjHdr* object) {
    if (object != vmNull && object->value.string_v != vmNull) {
        return object->value.string_v->spData;
    }
    return vmNull;
}

int VmGetIntFromObjHdr(CHANSVmObjHdr* object) {
    if (object != vmNull && object->value.int32_v) {
        return object->value.int32_v->val;
    }
    return 0;
}

u32 CHANSVmBlobGetCount(BlobHeader* blob, CHANSVmObjHdr* ptr, u32 limit);
BOOL CHANSVmBlobHasSpace(BlobHeader* blob, s64 size);
CHANSVmObjHdr* CHANSVmNewBlobObject(CHANSVm* VmInst, CHANSVmObjHdr* obj, u32 size, void* src, u32 count);
static u64 CHANSVmMakeU64(u32 upper, u32 lower);

static void VmBlobInitValue(BlobHeader* blob, u32 size) {
    if (blob != vmNull) {
        blob->offset = 0;
        blob->size = size;
        blob->pData = (u8*)(blob + 1);
    }
}

static const char VmBlobClassName[] = "Blob";

char scHexDigits[] = "0123456789abcdef";
char* scHexDigitsPtr = scHexDigits;
char* scHexDigitsPtr2 = scHexDigits;

static CHANSVmObjHdr* VmBlobCreateDirect(CHANSVm* vm, CHANSVmObjHdr* obj, u32 size) NO_INLINE {
    CHANSVmNativeClass* cls;

    if (obj != vmNull && CHANSVmDeleteObject(vm, obj) != CHANS_VM_OK) {
        return vmNull;
    }

    obj = CHANSVmNewObject(vm, vmFalse, obj, CHANS_VM_TYPE_OBJECT, size + sizeof(BlobHeader));
    if (obj != vmNull) {
        cls = CHANSVmFindNativeClass(vm, VmBlobClassName);
        obj->parentCls = cls;
    } else {
        goto ret_null;
    }

    if (cls == vmNull) {
    ret_null:
        return vmNull;
    }

    VmBlobInitValue((BlobHeader*)VmGetStrFromObjHdr(obj), size);
    return obj;
}

static u8* VmBlobGetDataBufferDirect(CHANSVmObjHdr* obj) {
    BlobHeader* blob;

    if (CHANSVmCheckNativeInstance(obj, VmBlobClassName)) {
        blob = (BlobHeader*)VmGetStrFromObjHdr(obj);
    } else {
        blob = vmNull;
    }

    if (blob != vmNull) {
        return blob->pData;
    }

    return vmNull;
}

BOOL CHANSVmBlobResolveOffset(BlobHeader* blob, s64 val, u32* out) {
    s64 pos;

    if (blob == vmNull) {
        return vmFalse;
    }

    if (val >= 0 && val <= blob->size) {
        pos = val;
    } else if (val >= -(s64)blob->size && val < 0) {
        pos = blob->size + val;
    } else {
        return vmFalse;
    }

    if (out != vmNull) {
        *out = (u32)pos;
    }
    return vmTrue;
}

VmCtorDefine(Blob) {
    CHANSVmObjHdr* arg = CHANSVmGetArg(VmInst, 0);
    CHANSVmObjHdr* obj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, arg);
    u32 size = 0;
    BlobHeader* blob;

    if (obj != vmNull && obj->value.int_v != 0) {
        size = (u32)obj->value.int_v;
    }

    if (size == 0) {
        return vmFalse;
    }

    blob = CHANSVmNewObjData(VmInst, VmReturnObj, size + sizeof(BlobHeader));
    if (blob == vmNull) {
        return vmFalse;
    }

    VmBlobInitValue(blob, size);
    return vmTrue;
}

VmDtorDefine(Blob) {
    VmGetStrFromObjHdr(VmParentObj);
    return vmTrue;
}

VmMethodDefine(Blob, GetOffset) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    if (blob != vmNull) {
        return CHANSVmSetInteger(VmInst, VmReturnObj, blob->offset) == CHANS_VM_OK;
    }
    return vmFalse;
}

VmMethodDefine(Blob, Seek) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* arg = CHANSVmGetArg(VmInst, 0);
    CHANSVmObjHdr* val = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, arg);
    u32 resolvedOffset;

    if (blob == vmNull || val == vmNull) {
        return vmFalse;
    }

    if (CHANSVmBlobResolveOffset(blob, val->value.int_v, &resolvedOffset)) {
        blob->offset = resolvedOffset;
    } else {
        return vmFalse;
    }

    return (u32)CHANSVmCopyObject(VmInst, VmReturnObj, VmParentObj) != 0;
}

VmMethodDefine(Blob, Skip) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* arg = CHANSVmGetArg(VmInst, 0);
    CHANSVmObjHdr* val = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, arg);
    u32 offset;
    s64 newOff;

    if (blob == vmNull || val == vmNull) {
        return vmFalse;
    }

    offset = blob->offset;
    newOff = (s64)offset + val->value.int_v;

    if (newOff >= 0 && newOff <= (s64)(blob->size)) {
        blob->offset = (u32)newOff;
    } else {
        return vmFalse;
    }

    return (u32)CHANSVmCopyObject(VmInst, VmReturnObj, VmParentObj) != 0;
}

VmMethodDefine(Blob, GetLength) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    if (blob != vmNull) {
        return CHANSVmSetInteger(VmInst, VmReturnObj, blob->size) == CHANS_VM_OK;
    }

    return vmFalse;
}

VmMethodDefine(Blob, SetLength) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* arg = CHANSVmGetArg(VmInst, 0);
    CHANSVmObjHdr* val = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, arg);
    u32 newSize;
    int intVal;

    if (blob == vmNull || val == vmNull) {
        return vmFalse;
    }

    newSize = (u32)val->value.int_v;
    if (newSize <= blob->size) {
        if (CHANSVmCheckNativeInstance(VmParentObj, VmBlobClassName)) {
            blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
        } else {
            blob = vmNull;
        }

        intVal = VmGetIntFromObjHdr(VmParentObj);
        if (blob == vmNull) {
            return vmFalse;
        }

        if ((s32)newSize <= intVal - (s32)sizeof(BlobHeader)) {
            blob->size = newSize;
            if (newSize < blob->offset) {
                blob->offset = newSize;
            }
            return vmTrue;
        }
        return vmFalse;
    }
    return vmFalse;
}

VmMethodDefine(Blob, Fill) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* val = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));
    CHANSVmObjHdr* fill = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 1));
    u32 count;

    if (blob == vmNull || val == vmNull) {
        return vmFalse;
    }

    count = blob != vmNull ? CHANSVmBlobGetCount(blob, fill, blob->offset) : 0;

    if (CHANSVmBlobHasSpace(blob, count)) {
        memset(blob->pData + blob->offset, (u8)val->value.int_v, count);
        blob->offset += count;
        return vmTrue;
    }

    return vmFalse;
}

u32 CHANSVmBlobGetCount(BlobHeader* blob, CHANSVmObjHdr* ptr, u32 limit) {
    if (ptr != vmNull) {
        return ptr->value.data.len;
    }

    if (blob != vmNull) {
        if (blob->size >= limit) {
            return blob->size - limit;
        }
    }

    return 0;
}

BOOL CHANSVmBlobHasSpace(BlobHeader* blob, s64 size) {
    u32 curOff = blob->offset;
    return size >= 0 && (s64)(blob->size - curOff) >= size;
}

VmMethodDefine(Blob, GetString) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* arg = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));
    u32 size;

    if (blob == vmNull || arg == vmNull) {
        return vmFalse;
    }

    size = (u32)arg->value.int_v;
    if (CHANSVmBlobHasSpace(blob, size)) {
        CHANSVmErr err = CHANSVmSetU16StringFromU8(VmInst, VmReturnObj, (char*)(blob->pData + blob->offset), size);
        blob->offset += size;
        return err == CHANS_VM_OK;
    }

    return vmFalse;
}

VmMethodDefine(Blob, SetString) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* strObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, CHANSVmGetArg(VmInst, 0));
    u8* strData = (u8*)VmGetStrFromObjHdr(strObj);
    u32 charCount = (u32)VmGetIntFromObjHdr(strObj) / 2;
    CHANSVmObjHdr* sizeArg = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 1));
    u32 size;

    if (blob == vmNull || strObj == vmNull || strData == vmNull) {
        return vmFalse;
    }

    if (sizeArg == vmNull) {
        size = charCount;
    } else {
        size = (u32)sizeArg->value.int_v;
        if (size < charCount) {
            charCount = size;
        }
    }

    if (CHANSVmBlobHasSpace(blob, size)) {
        memset(blob->pData + blob->offset, 0, size);
        CHANSVmStrCpyToU8FromU16(blob->pData + blob->offset, strData, charCount);
        blob->offset += size;
        return vmTrue;
    }

    return vmFalse;
}

VmMethodDefine(Blob, GetWString) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* arg = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));

    if (blob == vmNull || arg == vmNull) {
        return vmFalse;
    }

    if (CHANSVmBlobHasSpace(blob, VM_STR_LENGTH(arg->value.int_v))) {
        CHANSVmErr err = CHANSVmSetU16String(VmInst, VmReturnObj, (wchar_t*)(blob->pData + blob->offset), (u32)arg->value.int_v << 1);
        u32 oldOffset = blob->offset;
        u64 length = VM_STR_LENGTH(arg->value.int_v);
        blob->offset = length + oldOffset;
        return err == CHANS_VM_OK;
    }

    return vmFalse;
}

VmMethodDefine(Blob, SetWString) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* strObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, CHANSVmGetArg(VmInst, 0));
    u8* strData = (u8*)VmGetStrFromObjHdr(strObj);
    u32 strLen = (u32)VmGetIntFromObjHdr(strObj);
    CHANSVmObjHdr* sizeArg = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 1));
    u32 size;

    if (blob == vmNull || strObj == vmNull || strData == vmNull) {
        return vmFalse;
    }

    if (sizeArg == vmNull) {
        size = strLen;
    } else {
        s64 charCount = VM_STR_LENGTH(sizeArg->value.int_v);
        if (sizeArg->value.int_v < 0 || charCount < 0) {
            return vmFalse;
        }

        size = (u32)charCount;
        if (charCount < (s64)strLen) {
            strLen = size;
        }
    }

    if (CHANSVmBlobHasSpace(blob, size)) {
        memcpy(blob->pData + blob->offset, strData, strLen);
        if (strLen < size) {
            memset(blob->pData + blob->offset + strLen, 0, size - strLen);
        }
        blob->offset += size;
        return vmTrue;
    }

    return vmFalse;
}

VmMethodDefine(Blob, IsEqual) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* arg = CHANSVmGetArg(VmInst, 0);
    BlobHeader* other;
    vmBoolInt result;

    if (CHANSVmCheckNativeInstance(arg, VmBlobClassName)) {
        other = (BlobHeader*)VmGetStrFromObjHdr(arg);
    } else {
        other = vmNull;
    }

    if (blob == vmNull || other == vmNull) {
        return vmFalse;
    }

    result = vmFalse;

    if (blob->size == other->size) {
        if (memcmp(blob->pData, other->pData, blob->size) == 0) {
            result = vmTrue;
        }
    }

    return CHANSVmSetInteger(VmInst, VmReturnObj, result) == CHANS_VM_OK;
}

VmMethodDefine(Blob, CopyRangeFrom) {
    BlobHeader* srcBlob;
    BlobHeader* destBlob;
    u32 srcOff;
    u32 destOff;
    u32 count;
    vmBoolInt okFlag;
    CHANSVmObjHdr* destOffObj;
    CHANSVmObjHdr* srcObj;
    CHANSVmObjHdr* srcOffObj;
    CHANSVmObjHdr* countObj;

    destBlob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    destOffObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));
    srcObj = CHANSVmGetArg(VmInst, 1);
    srcOffObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 2));
    countObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 3));

    if (CHANSVmCheckNativeInstance(srcObj, VmBlobClassName)) {
        srcBlob = (BlobHeader*)VmGetStrFromObjHdr(srcObj);
    } else {
        srcBlob = vmNull;
    }

    if (destBlob == vmNull || destOffObj == vmNull || srcBlob == vmNull || srcOffObj == vmNull) {
        return vmFalse;
    }

    okFlag = vmFalse;
    srcOff = 0;
    destOff = 0;

    if (CHANSVmBlobResolveOffset(destBlob, destOffObj->value.int_v, &destOff) && CHANSVmBlobResolveOffset(srcBlob, srcOffObj->value.int_v, &srcOff)) {
        count = CHANSVmBlobGetCount(srcBlob, countObj, srcOff);
        {
            u32 destinationOffset = destOff;
            okFlag = (s64)count >= 0 && (s64)(destBlob->size - destinationOffset) >= (s64)count;
        }

        if (okFlag) {
            vmBoolInt sourceValid = vmFalse;
            u32 sourceOffset = srcOff;
            sourceValid = (s64)count >= 0 && (s64)(srcBlob->size - sourceOffset) >= (s64)count;

            if (sourceValid) {
                memmove(destBlob->pData + destOff, srcBlob->pData + srcOff, count);
                return CHANSVmSetInteger(VmInst, VmReturnObj, (vmInteger)(u64)count) == CHANS_VM_OK;
            }
        }
    }
    return vmFalse;
}

VmMethodDefine(Blob, GetBlob) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* arg = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));
    u32 count;

    if (blob == vmNull)
        return vmFalse;

    count = blob != vmNull ? CHANSVmBlobGetCount(blob, arg, blob->offset) : 0;

    if (CHANSVmBlobHasSpace(blob, count)) {
        if (CHANSVmNewBlobObject(VmInst, VmReturnObj, count, blob->offset + blob->pData, count) != vmNull) {
            blob->offset += count;
            return vmTrue;
        }
    }

    return vmFalse;
}

VmMethodDefine(Blob, SetBlob) {
    BlobHeader* destBlob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    BlobHeader* srcBlob;
    CHANSVmObjHdr* srcObj = CHANSVmGetArg(VmInst, 0);
    CHANSVmObjHdr* countObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 1));
    u32 logicalSize;
    u32 copySize;
    u32 srcAvailable;

    if (CHANSVmCheckNativeInstance(srcObj, VmBlobClassName)) {
        srcObj = (CHANSVmObjHdr*)VmGetStrFromObjHdr(srcObj);
    } else {
        srcObj = vmNull;
    }

    if (destBlob == vmNull || srcObj == vmNull) {
        return vmFalse;
    }
    if (srcObj == vmNull) {
        return vmFalse;
    }

    srcBlob = (BlobHeader*)srcObj;
    srcAvailable = srcBlob->size - srcBlob->offset;

    if (countObj == vmNull) {
        logicalSize = srcAvailable;
        copySize = srcAvailable;
    } else {
        logicalSize = countObj->value.int_v;
        if (logicalSize < srcAvailable) {
            copySize = logicalSize;
        } else {
            copySize = srcAvailable;
        }
    }

    if (CHANSVmBlobHasSpace(destBlob, logicalSize)) {
        memmove(destBlob->pData + *(u32*)&destBlob->offset, srcBlob->pData + srcBlob->offset, copySize);
        if (copySize < logicalSize) {
            memset(destBlob->offset + destBlob->pData + copySize, 0, logicalSize - copySize);
        }

        destBlob->offset += logicalSize;
        return vmTrue;
    }

    return vmFalse;
}

VmMethodDefine(Blob, GetHexString) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* arg = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));
    u32 count;

    if (blob == vmNull) {
        return vmFalse;
    }

    count = blob != vmNull ? CHANSVmBlobGetCount(blob, arg, blob->offset) : 0;

    if (CHANSVmBlobHasSpace(blob, count) && CHANSVmNewObject(VmInst, vmFalse, VmReturnObj, CHANS_VM_OBJ_TYPE_STRING, count * 4) != vmNull) {
        wchar_t* dest = (wchar_t*)VmGetStrFromObjHdr(VmReturnObj);
        u8* src = blob->pData;
        u32 offset = blob->offset;
        u32 destOff = 0;
        u32 i = 0;
        char* hexTbl = scHexDigitsPtr;
        u32 byteIndex;

        src += offset;

        for (byteIndex = 0; byteIndex < count; byteIndex++) {
            u32 lowDigitIndex = i + 1;
            i += 2;
            dest[destOff] = (wchar_t)(s8)hexTbl[(u32)*src >> 4 & 0xF];
            destOff += 2;
            dest[lowDigitIndex] = (wchar_t)(s8)hexTbl[(u32)*src & 0xF];
            src++;
        }
        blob->offset += count;
        return vmTrue;
    }
    return vmFalse;
}

VmMethodDefine(Blob, CalcSHA1Digest) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    NETSHA1Context ctx;
    u32 len;
    u8* data;
    CHANSVmObjHdr* newObj;
    u8* digest;

    if (blob == vmNull) {
        return vmFalse;
    }

    newObj = VmBlobCreateDirect(VmInst, VmReturnObj, NET_SHA1_DIGEST_SIZE);
    digest = VmBlobGetDataBufferDirect(newObj);
    if (newObj == vmNull || digest == vmNull) {
        return vmFalse;
    }

    len = blob->size;
    data = blob->pData;
    NETSHA1Init(&ctx);
    NETSHA1Update(&ctx, data, len);
    NETSHA1GetDigest(&ctx, digest);
    return vmTrue;
}

VmMethodDefine(Blob, CalcRangeSHA1Digest) {
    u8* data;
    u8* digest;
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* offsetObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));
    CHANSVmObjHdr* countObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 1));
    u32 offset = 0;
    u32 size;
    NETSHA1Context ctx;
    CHANSVmObjHdr* newObj;

    if (blob == vmNull || offsetObj == vmNull) {
        return vmFalse;
    }

    if (CHANSVmBlobResolveOffset(blob, offsetObj->value.int_v, &offset)) {
        size = CHANSVmBlobGetCount(blob, countObj, offset);

        {
            u32 off = offset;
            if (((s64)size >= 0LL && (s64)(blob->size - off) >= (s64)size) != vmFalse) {
                newObj = VmBlobCreateDirect(VmInst, VmReturnObj, NET_SHA1_DIGEST_SIZE);
                digest = VmBlobGetDataBufferDirect(newObj);

                if (newObj == vmNull || digest == vmNull) {
                    return vmFalse;
                }

                data = blob->pData + offset;
                NETSHA1Init(&ctx);
                NETSHA1Update(&ctx, data, size);
                NETSHA1GetDigest(&ctx, digest);
                return vmTrue;
            }
        }
    }
    return vmFalse;
}

VmMethodDefine(Blob, CalcMD5Digest) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    NETMD5Context ctx;
    u32 len;
    u8* data;
    CHANSVmObjHdr* newObj;
    u8* digest;

    if (blob == vmNull) {
        return vmFalse;
    }

    newObj = VmBlobCreateDirect(VmInst, VmReturnObj, NET_MD5_DIGEST_SIZE);
    digest = VmBlobGetDataBufferDirect(newObj);
    if (newObj == vmNull || digest == vmNull) {
        return vmFalse;
    }

    len = blob->size;
    data = blob->pData;
    NETMD5Init(&ctx);
    NETMD5Update(&ctx, data, len);
    NETMD5GetDigest(&ctx, digest);
    return vmTrue;
}

VmMethodDefine(Blob, CalcRangeMD5Digest) {
    u8* data;
    u8* digest;
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* offsetObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));
    CHANSVmObjHdr* countObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 1));
    u32 offset = 0;
    u32 size;
    NETMD5Context ctx;
    CHANSVmObjHdr* newObj;

    if (blob == vmNull || offsetObj == vmNull) {
        return vmFalse;
    }

    if (CHANSVmBlobResolveOffset(blob, offsetObj->value.int_v, &offset)) {
        size = CHANSVmBlobGetCount(blob, countObj, offset);

        {
            u32 off = offset;
            if (((s64)size >= 0LL && (s64)(blob->size - off) >= (s64)size) != vmFalse) {
                newObj = VmBlobCreateDirect(VmInst, VmReturnObj, NET_MD5_DIGEST_SIZE);
                digest = VmBlobGetDataBufferDirect(newObj);

                if (newObj == vmNull || digest == vmNull) {
                    return vmFalse;
                }

                data = blob->pData + offset;
                NETMD5Init(&ctx);
                NETMD5Update(&ctx, data, size);
                NETMD5GetDigest(&ctx, digest);
                return vmTrue;
            }
        }
    }
    return vmFalse;
}

VmMethodDefine(Blob, CalcCRC16) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    u16 crc;

    if (blob == vmNull) {
        return vmFalse;
    }

    crc = NETCalcCRC16(blob->pData, blob->size);
    return CHANSVmSetInteger(VmInst, VmReturnObj, (vmInteger)(u64)crc) == CHANS_VM_OK;
}

VmMethodDefine(Blob, CalcRangeCRC16) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* offsetObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));
    CHANSVmObjHdr* countObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 1));
    u32 offset = 0;
    u32 size;

    if (blob == vmNull || offsetObj == vmNull) {
        return vmFalse;
    }

    if (CHANSVmBlobResolveOffset(blob, offsetObj->value.int_v, &offset)) {
        size = CHANSVmBlobGetCount(blob, countObj, offset);
        {
            u32 off = offset;
            if (((s64)size >= 0LL && (s64)(blob->size - off) >= (s64)size) != vmFalse) {
                u16 crc = NETCalcCRC16(blob->pData + off, size);
                return CHANSVmSetInteger(VmInst, VmReturnObj, (vmInteger)(u64)crc) == CHANS_VM_OK;
            }
        }
    }
    return vmFalse;
}

VmMethodDefine(Blob, CalcCRC32) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    u32 crc;

    if (blob == vmNull) {
        return vmFalse;
    }

    crc = NETCalcCRC32(blob->pData, blob->size);
    return CHANSVmSetInteger(VmInst, VmReturnObj, (vmInteger)(u64)crc) == CHANS_VM_OK;
}

VmMethodDefine(Blob, CalcRangeCRC32) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* offsetObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));
    CHANSVmObjHdr* countObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 1));
    u32 offset = 0;
    u32 size;

    if (blob == vmNull || offsetObj == vmNull) {
        return vmFalse;
    }

    if (CHANSVmBlobResolveOffset(blob, offsetObj->value.int_v, &offset)) {
        size = CHANSVmBlobGetCount(blob, countObj, offset);
        {
            u32 off = offset;

            if (((s64)size >= 0LL && (s64)(blob->size - off) >= (s64)size) != vmFalse) {
                u32 crc = NETCalcCRC32(blob->pData + off, size);
                return CHANSVmSetInteger(VmInst, VmReturnObj, (vmInteger)(u64)crc) == CHANS_VM_OK;
            }
        }
    }
    return vmFalse;
}

VmMethodDefine(Blob, CalcHMAC) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* obj = CHANSVmGetArg(VmInst, 0);
    BlobHeader* keyBlob;
    NETHMACContext ctx;
    u32 blobSize;
    u8* blobData;
    u8* digest;

    if (CHANSVmCheckNativeInstance(obj, VmBlobClassName)) {
        keyBlob = (BlobHeader*)VmGetStrFromObjHdr(obj);
    } else {
        keyBlob = vmNull;
    }

    if (blob == vmNull || keyBlob == vmNull) {
        return vmFalse;
    }

    obj = VmBlobCreateDirect(VmInst, VmReturnObj, NET_SHA1_DIGEST_SIZE);
    digest = VmBlobGetDataBufferDirect(obj);

    if (obj == vmNull || digest == vmNull) {
        return vmFalse;
    }

    blobSize = blob->size;
    blobData = blob->pData;

    NETHMACInit(&ctx, NETGetSHA1Interface(), keyBlob->pData, keyBlob->size);
    NETHMACUpdate(&ctx, blobData, blobSize);
    NETHMACGetDigest(&ctx, digest);
    return vmTrue;
}

VmMethodDefine(Blob, CalcRangeHMAC) {
    u8* blobData;
    u8* digest;
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* argKey = CHANSVmGetArg(VmInst, 0);
    BlobHeader* keyBlob;
    CHANSVmObjHdr* offsetObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 1));
    CHANSVmObjHdr* countObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 2));

    if (CHANSVmCheckNativeInstance(argKey, VmBlobClassName)) {
        keyBlob = (BlobHeader*)VmGetStrFromObjHdr(argKey);
    } else {
        keyBlob = vmNull;
    }

    {
        u32 offset = 0;
        u32 size;
        u32 off;

        if (blob == vmNull || keyBlob == vmNull || offsetObj == vmNull) {
            return vmFalse;
        }

        if (CHANSVmBlobResolveOffset(blob, offsetObj->value.int_v, &offset)) {
            size = CHANSVmBlobGetCount(blob, countObj, offset);
            off = offset;
            if (((s64)size >= 0LL && (s64)(blob->size - off) >= (s64)size) != vmFalse) {
                NETHMACContext ctx;
                CHANSVmObjHdr* newObj;

                newObj = VmBlobCreateDirect(VmInst, VmReturnObj, NET_SHA1_DIGEST_SIZE);
                digest = VmBlobGetDataBufferDirect(newObj);

                if (keyBlob == vmNull || newObj == vmNull || digest == vmNull) {
                    return vmFalse;
                }

                blobData = blob->pData + offset;
                NETHMACInit(&ctx, NETGetSHA1Interface(), keyBlob->pData, keyBlob->size);
                NETHMACUpdate(&ctx, blobData, size);
                NETHMACGetDigest(&ctx, digest);
                return vmTrue;
            }
        }
        return vmFalse;
    }
}

VmMethodDefine(Blob, GetU8) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    if (blob == vmNull) {
        return vmFalse;
    }

    if ((s64)(blob->size - blob->offset) >= 1) {
        u8 val;
        memcpy(&val, blob->pData + blob->offset, 1);

        blob->offset += 1;
        return CHANSVmSetInteger(VmInst, VmReturnObj, (vmInteger)(u64)val) == CHANS_VM_OK;
    }

    return vmFalse;
}

VmMethodDefine(Blob, GetU16) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    u16 val;
    if (blob == vmNull) {
        return vmFalse;
    }

    if ((s64)(blob->size - blob->offset) >= 2) {
        memcpy(&val, blob->pData + blob->offset, 2);
        blob->offset += 2;
        return CHANSVmSetInteger(VmInst, VmReturnObj, (vmInteger)(u64)val) == CHANS_VM_OK;
    }
    return vmFalse;
}

VmMethodDefine(Blob, GetU32) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    u32 val;
    if (blob == vmNull) {
        return vmFalse;
    }

    if ((s64)(blob->size - blob->offset) >= 4) {
        memcpy(&val, blob->pData + blob->offset, 4);
        blob->offset += 4;
        return CHANSVmSetInteger(VmInst, VmReturnObj, (vmInteger)(u64)val) == CHANS_VM_OK;
    }
    return vmFalse;
}

VmMethodDefine(Blob, GetS8) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    s8 val;
    if (blob == vmNull) {
        return vmFalse;
    }

    if ((s64)(blob->size - blob->offset) >= 1) {
        memcpy(&val, blob->pData + blob->offset, 1);
        blob->offset += 1;
        return CHANSVmSetInteger(VmInst, VmReturnObj, val) == CHANS_VM_OK;
    }
    return vmFalse;
}

VmMethodDefine(Blob, GetS16) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    s16 val;
    if (blob == vmNull) {
        return vmFalse;
    }

    if ((s64)(blob->size - blob->offset) >= 2) {
        memcpy(&val, blob->pData + blob->offset, 2);
        blob->offset += 2;
        return CHANSVmSetInteger(VmInst, VmReturnObj, val) == CHANS_VM_OK;
    }
    return vmFalse;
}

VmMethodDefine(Blob, GetS32) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    s32 val;
    if (blob == vmNull) {
        return vmFalse;
    }

    if ((s64)(blob->size - blob->offset) >= 4) {
        memcpy(&val, blob->pData + blob->offset, 4);
        blob->offset += 4;
        return CHANSVmSetInteger(VmInst, VmReturnObj, val) == CHANS_VM_OK;
    }
    return vmFalse;
}

VmMethodDefine(Blob, GetS64) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    s64 val;
    if (blob == vmNull) {
        return vmFalse;
    }

    if ((s64)(blob->size - blob->offset) >= 8) {
        memcpy(&val, blob->pData + blob->offset, 8);
        blob->offset += 8;
        return CHANSVmSetInteger(VmInst, VmReturnObj, val) == CHANS_VM_OK;
    }
    return vmFalse;
}

VmMethodDefine(Blob, SetU8) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* arg = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));
    u8 val = 0;

    if (blob == vmNull || arg == vmNull) {
        return vmFalse;
    }

    if ((s64)(blob->size - blob->offset) >= 1) {
        val = (u8)arg->value.int_v;
        memcpy(blob->pData + blob->offset, &val, 1);
        blob->offset += 1;
        return vmTrue;
    }
    return vmFalse;
}

VmMethodDefine(Blob, SetU16) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* arg = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));
    u16 val = 0;

    if (blob == vmNull || arg == vmNull) {
        return vmFalse;
    }

    if ((s64)(blob->size - blob->offset) >= 2) {
        val = (u16)arg->value.int_v;
        memcpy(blob->pData + blob->offset, &val, 2);
        blob->offset += 2;
        return vmTrue;
    }
    return vmFalse;
}

VmMethodDefine(Blob, SetU32) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* arg = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));
    u32 val = 0;

    if (blob == vmNull || arg == vmNull) {
        return vmFalse;
    }

    if ((s64)(blob->size - blob->offset) >= 4) {
        val = (u32)arg->value.int_v;
        memcpy(blob->pData + blob->offset, &val, 4);
        blob->offset += 4;
        return vmTrue;
    }
    return vmFalse;
}

VmMethodDefine(Blob, SetS8) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* arg = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));
    s8 val = 0;

    if (blob == vmNull || arg == vmNull) {
        return vmFalse;
    }

    if ((s64)(blob->size - blob->offset) >= 1) {
        val = (s8)arg->value.int_v;
        memcpy(blob->pData + blob->offset, &val, 1);
        blob->offset += 1;
        return vmTrue;
    }
    return vmFalse;
}

VmMethodDefine(Blob, SetS16) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* arg = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));
    s16 val = 0;

    if (blob == vmNull || arg == vmNull) {
        return vmFalse;
    }

    if ((s64)(blob->size - blob->offset) >= 2) {
        val = (s16)arg->value.int_v;
        memcpy(blob->pData + blob->offset, &val, 2);
        blob->offset += 2;
        return vmTrue;
    }
    return vmFalse;
}

VmMethodDefine(Blob, SetS32) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* arg = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));
    s32 val = 0;

    if (blob == vmNull || arg == vmNull) {
        return vmFalse;
    }

    if ((s64)(blob->size - blob->offset) >= 4) {
        val = (s32)arg->value.int_v;
        memcpy(blob->pData + blob->offset, &val, 4);
        blob->offset += 4;
        return vmTrue;
    }
    return vmFalse;
}

VmMethodDefine(Blob, SetS64) {
    BlobHeader* blob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    CHANSVmObjHdr* arg = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, CHANSVmGetArg(VmInst, 0));
    s64 val = 0;

    if (blob == vmNull || arg == vmNull) {
        return vmFalse;
    }

    if ((s64)(blob->size - blob->offset) >= 8) {
        val = arg->value.int_v;
        memcpy(blob->pData + blob->offset, &val, 8);
        blob->offset += 8;
        return vmTrue;
    }
    return vmFalse;
}

static CHANSVmBlobPackFormatList vmBlobPackFormatList[25] = {
    {0x44, 1, 4, 1},   // 'D'
    {0x78, 1, 5, 0},   // 'x'
    {0x63, 1, 6, 1},   // 'c'
    {0x43, 1, 7, 1},   // 'C'
    {0x73, 2, 6, 1},   // 's'
    {0x53, 2, 7, 1},   // 'S'
    {0x69, 4, 6, 1},   // 'i'
    {0x49, 4, 7, 1},   // 'I'
    {0x6C, 4, 6, 1},   // 'l'
    {0x4C, 4, 7, 1},   // 'L'
    {0x71, 8, 6, 1},   // 'q'
    {0x6E, 2, 7, 1},   // 'n'
    {0x4E, 4, 7, 1},   // 'N'
    {0x76, 2, 9, 1},   // 'v'
    {0x56, 4, 9, 1},   // 'V'
    {0x61, 1, 10, 1},  // 'a'
    {0x77, 2, 12, 1},  // 'w'
    {0x5A, 1, 11, 1},  // 'Z'
    {0x57, 2, 13, 1},  // 'W'
    {0x48, 1, 14, 1},  // 'H'
    {0x23, 1, 3, 0},   // '#'
    {0x20, 1, 2, 0},   // ' '
    {0x09, 1, 2, 0},   // '\t'
    {0x0D, 1, 2, 0},   // '\r'
    {0x0A, 1, 2, 0},   // '\n'
};

static u32 vmBlobParsePackFormatString(u32* out_nextPos, u32* out_elemType, u32* out_elemSize, u32* out_paramValue, const wchar_t* fmtStr, u32 fmtLen,
                                       u32 curPos) {
    wchar_t curChar;
    u32 elemType;
    u32 elemSize;
    u32 hasStar;
    s32 paramValue;
    u32 hasParam;
    u32 i;
    const CHANSVmBlobPackFormatList* p;

    elemSize = 1;
    hasStar = 0;
    paramValue = 0;

    while (curPos < fmtLen) {
        curChar = fmtStr[curPos];
        p = vmBlobPackFormatList;

        for (i = 0; i < 25; i++, p++) {
            if (curChar == p->charCode) {
                elemType = p->type;
                elemSize = p->size;
                hasStar = p->flags;
                break;
            }
        }

        if (i >= 25) {
            elemSize = 1;
            elemType = 0;
            goto exit;
        }

        if (elemType != 2 && elemType != 3) {
            goto param_processing;
        }
        if (elemType == 3) {
            for (; curPos < fmtLen; curPos++) {
                u32 c = fmtStr[curPos];
                if (c == L'\r' || c == L'\n')
                    break;
            }
        }
        curPos++;
    }

    elemType = 1;
    curChar = 0;
    goto exit;

param_processing:
    curPos++;
    hasParam = 0;

    for (paramValue = 0; curPos < fmtLen; curPos++) {
        u32 digit = fmtStr[curPos];

        if (!hasParam) {
            if (digit == '*') {
                if (hasStar & 1) {
                    paramValue = -1;
                    curPos++;
                    goto exit;
                } else {
                    elemSize = 1;
                    elemType = 0;
                    paramValue = 0;
                    goto exit;
                }
            }
        }

        if (digit >= 0x30 && digit <= 0x39) {
            hasParam = 1;
            paramValue *= 10;
            paramValue += (u32)(digit - 0x30);
            if (paramValue < 0) {
                elemSize = 1;
                elemType = 0;
                paramValue = 0;
                goto exit;
            }
        } else {
            break;
        }
    }

    if (hasParam == 0) {
        paramValue = 1;
    }

exit:
    if (out_nextPos != vmNull) {
        *out_nextPos = curChar;
    }
    if (out_elemType != vmNull) {
        *out_elemType = elemType;
    }
    if (out_elemSize != vmNull) {
        *out_elemSize = elemSize;
    }
    if (out_paramValue != vmNull) {
        *out_paramValue = paramValue;
    }

    return curPos;
}

static inline void VmBlobCopyPadded(BlobHeader* parentBlob, const BlobHeader* srcBlob, s32 copySize) {
    u32 srcOff;
    u32 dataSize;
    u8* dest;

    srcOff = srcBlob->offset;
    dataSize = srcBlob->size - srcOff;
    dest = parentBlob->pData + parentBlob->offset;
    if (dataSize > copySize) {
        dataSize = copySize;
    }
    memmove(dest, srcBlob->pData + srcOff, dataSize);
    if (dataSize < copySize) {
        memset(dest + dataSize, 0, copySize - dataSize);
    }
    parentBlob->offset += copySize;
}

static vmBoolInt VmBlobPackCommon(CHANSVm* VmInst, CHANSVmObjHdr* VmParentObj, CHANSVmObjHdr* VmReturnObj, vmU32 flag) {
    u32 packBuf[2];
    BlobHeader* parentBlob;
    CHANSVmObjHdr* argStr;
    const wchar_t* fmtStr;
    u32 fmtLen;
    CHANSVmObjHdr* argArr;
    u32 fmtPos;
    u32 argCount;
    u32 totalSize;
    s32 count;
    u32 i;
    CHANSVmObjHdr* obj;
    BlobHeader* srcBlob;
    s32 copySize;
    CHANSVmObjHdr* strObj;
    u8* srcData;
    u32 charCount;
    u32 strLen;
    CHANSVmObjHdr* intObj;
    u32 valLow;
    u32 valHigh;
    s32 bufSize;
    u8* dest;
    u32 ch;
    CHANSVmExecutionCtx* execCtx;

    parentBlob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    argStr = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, CHANSVmGetArg(VmInst, 0));
    fmtStr = (const wchar_t*)VmGetStrFromObjHdr(argStr);
    fmtLen = (u32)VmGetIntFromObjHdr(argStr) / 2;
    argArr = CHANSVmConvertObjectType(VmInst, CHANS_VM_TYPE_ARRAY, CHANSVmGetArg(VmInst, 1));

    if (fmtStr == vmNull) {
        return vmFalse;
    }

    if (flag == 0 && parentBlob == vmNull) {
        goto error;
    }

    argCount = 0;
    fmtPos = 0;
    totalSize = flag != 0 ? 0 : parentBlob->offset;

    while (vmTrue) {
        u32 nextPos = 0;
        u32 elemType = 0;
        u32 elemSize = 1;
        s32 paramValue = 1;

        fmtPos = vmBlobParsePackFormatString(&nextPos, &elemType, &elemSize, (void*)&paramValue, fmtStr, fmtLen, fmtPos);

        if (elemType == 1) {
            break;
        }

        if (elemType == 0) {
            goto error;
        }

        switch (elemType) {
            case 4: {
                if (paramValue < 0) {
                    if (argArr != vmNull) {
                        obj = CHANSVmGetArrayElement(VmInst, argArr, argCount);
                    } else {
                        obj = CHANSVmGetArg(VmInst, argCount + 1);
                    }
                    if (CHANSVmCheckNativeInstance(obj, VmBlobClassName)) {
                        srcBlob = (BlobHeader*)VmGetStrFromObjHdr(obj);
                    } else {
                        srcBlob = vmNull;
                    }
                    if (srcBlob == vmNull) {
                        goto error;
                    }
                    count = srcBlob->size - srcBlob->offset;
                } else {
                    count = paramValue;
                }
                if (count < 0) {
                    goto error;
                }
                totalSize += count;
                argCount++;
                break;
            }
            case 5: {
                if (paramValue < 0) {
                    goto error;
                }
                totalSize += paramValue;
                break;
            }
            case 6:
            case 7:
            case 8:
            case 9: {
                if (paramValue < 0) {
                    if (argArr != vmNull) {
                        count = CHANSVmGetArrayLength(VmInst, argArr);
                        count = count - argCount;
                    } else {
                        execCtx = ((CHANSVmPrivate*)VmInst)->pActiveCtx;
                        count = execCtx->argc - argCount - 1;
                    }
                } else {
                    count = paramValue;
                }
                if (count < 0) {
                    goto error;
                }
                argCount += count;
                totalSize += elemSize * count;
                break;
            }
            case 10:
            case 11:
            case 12:
            case 13: {
                if (paramValue < 0) {
                    if (argArr != vmNull) {
                        obj = CHANSVmGetArrayElement(VmInst, argArr, argCount);
                        obj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, obj);
                    } else {
                        obj = CHANSVmGetArg(VmInst, argCount + 1);
                        obj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, obj);
                    }
                    if (obj == vmNull) {
                        goto error;
                    }
                    count = (u32)obj->value.int32_v->val >> 1;
                } else {
                    count = paramValue;
                }
                if (count < 0) {
                    goto error;
                }
                argCount++;
                totalSize += elemSize * count;
                break;
            }
            case 14: {
                if (paramValue < 0) {
                    if (argArr != vmNull) {
                        obj = CHANSVmGetArrayElement(VmInst, argArr, argCount);
                        obj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, obj);
                    } else {
                        obj = CHANSVmGetArg(VmInst, argCount + 1);
                        obj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, obj);
                    }
                    if (obj == vmNull) {
                        goto error;
                    }
                    count = (u32)obj->value.int32_v->val >> 1;
                } else {
                    count = paramValue;
                }
                if (count < 0) {
                    goto error;
                }
                argCount++;
                totalSize += (s32)((u32)count + 1U) / 2;
                break;
            }
        }

        if (flag != 0) {
            continue;
        }
        if (totalSize > parentBlob->size) {
            goto error;
        }
    }

    if (flag != 0) {
        VmReturnObj = VmBlobCreateDirect(VmInst, VmReturnObj, totalSize);
        if (CHANSVmCheckNativeInstance(VmReturnObj, VmBlobClassName)) {
            parentBlob = (BlobHeader*)VmGetStrFromObjHdr(VmReturnObj);
        } else {
            parentBlob = vmNull;
        }
        if (parentBlob == vmNull) {
            goto error;
        }
    }

    argCount = 0;
    fmtPos = 0;

    while (vmTrue) {
        u32 nextPos = 0;
        u32 elemType = 0;
        u32 elemSize = 1;
        s32 paramValue = 1;

        fmtPos = vmBlobParsePackFormatString(&nextPos, &elemType, &elemSize, (void*)&paramValue, fmtStr, fmtLen, fmtPos);

        if (elemType == 1) {
            break;
        }

        if (elemType == 0) {
            goto error;
        }

        switch (elemType) {
            case 4: {
                if (argArr != vmNull) {
                    obj = CHANSVmGetArrayElement(VmInst, argArr, argCount);
                } else {
                    obj = CHANSVmGetArg(VmInst, argCount + 1);
                }

                if (CHANSVmCheckNativeInstance(obj, VmBlobClassName)) {
                    srcBlob = (BlobHeader*)VmGetStrFromObjHdr(obj);
                } else {
                    srcBlob = vmNull;
                }
                argCount++;

                if (srcBlob == vmNull) {
                    goto error;
                }

                if (paramValue < 0) {
                    copySize = srcBlob->size - srcBlob->offset;
                } else {
                    copySize = paramValue;
                }

                if (copySize < 0 || !CHANSVmBlobHasSpace(parentBlob, copySize)) {
                    goto error;
                }

                VmBlobCopyPadded(parentBlob, srcBlob, copySize);
                break;
            }
            case 5: {
                if (paramValue < 0 || !CHANSVmBlobHasSpace(parentBlob, paramValue)) {
                    goto error;
                }
                if (paramValue > 0) {
                    memset(parentBlob->pData + parentBlob->offset, 0, paramValue);
                    parentBlob->offset += paramValue;
                }
                break;
            }
            case 6:
            case 7:
            case 8:
            case 9: {
                if (paramValue < 0) {
                    if (argArr != vmNull) {
                        count = CHANSVmGetArrayLength(VmInst, argArr) - argCount;
                    } else {
                        execCtx = ((CHANSVmPrivate*)VmInst)->pActiveCtx;
                        count = execCtx->argc - argCount - 1;
                    }
                } else {
                    count = paramValue;
                }
                if (count < 0) {
                    goto error;
                }

                if (!CHANSVmBlobHasSpace(parentBlob, elemSize * count)) {
                    goto error;
                }

                for (i = 0; i < count; i++) {
                    packBuf[1] = 0;
                    packBuf[0] = 0;
                    if (argArr != vmNull) {
                        intObj = CHANSVmGetArrayElement(VmInst, argArr, argCount);
                        intObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, intObj);
                    } else {
                        intObj = CHANSVmGetArg(VmInst, argCount + 1);
                        intObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, intObj);
                    }
                    argCount++;
                    if (intObj == vmNull) {
                        goto error;
                    }
                    valLow = (u32)intObj->value.int_v;
                    valHigh = (u32)((u64)intObj->value.int_v >> 32);

                    switch ((s32)elemType) {
                        case 6:
                        case 8: {
                            // signed
                            switch (elemSize) {
                                case 1: {
                                    *(s8*)packBuf = (s8)valLow;
                                    break;
                                }
                                case 2: {
                                    *(s16*)packBuf = (s16)valLow;
                                    break;
                                }
                                case 4: {
                                    packBuf[0] = valLow;
                                    break;
                                }
                                case 8: {
                                    packBuf[1] = valLow;
                                    packBuf[0] = valHigh;
                                    break;
                                }
                                default: {
                                    goto error;
                                }
                            }
                            break;
                        }
                        case 7:
                        case 9: {
                            // unsigned
                            switch (elemSize) {
                                case 1: {
                                    *(u8*)packBuf = (u8)valLow;
                                    break;
                                }
                                case 2: {
                                    *(u16*)packBuf = (u16)valLow;
                                    break;
                                }
                                case 4: {
                                    packBuf[0] = valLow;
                                    break;
                                }
                                default: {
                                    goto error;
                                }
                            }
                            break;
                        }
                        default: {
                            goto error;
                        }
                    }

                    switch ((s32)elemType) {
                        case 6:
                        case 7: {
                            // little endian
                            break;
                        }
                        case 8:
                        case 9: {
                            // big endian
                            switch (elemSize) {
                                case 2: {
                                    __sthbrx(*(u16*)packBuf, packBuf, 0);
                                    break;
                                }
                                case 4: {
                                    __stwbrx(packBuf[0], packBuf, 0);
                                    break;
                                }
                                case 8: {
                                    *(u64*)packBuf = CHANSVmMakeU64(packBuf[0], packBuf[1]);
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    memcpy(parentBlob->pData + parentBlob->offset, packBuf, elemSize);
                    parentBlob->offset += elemSize;
                }
                break;
            }
            case 10:
            case 11:
            case 12:
            case 13: {
                if (argArr != vmNull) {
                    strObj = CHANSVmGetArrayElement(VmInst, argArr, argCount);
                    strObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, strObj);
                } else {
                    strObj = CHANSVmGetArg(VmInst, argCount + 1);
                    strObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, strObj);
                }
                argCount++;
                if (strObj == vmNull) {
                    goto error;
                }

                if (paramValue < 0) {
                    count = (u32)strObj->value.int32_v->val >> 1;
                } else {
                    count = paramValue;
                }
                if (count < 0) {
                    goto error;
                }

                if (!CHANSVmBlobHasSpace(parentBlob, elemSize * count)) {
                    goto error;
                }

                srcData = (u8*)VmGetStrFromObjHdr(strObj);
                strLen = (u32)VmGetIntFromObjHdr(strObj) >> 1;
                charCount = strLen;
                dest = parentBlob->pData + parentBlob->offset;

                if (charCount > count) {
                    charCount = count;
                }

                memset(dest, 0, elemSize * count);
                if (elemSize == 1) {
                    CHANSVmStrCpyToU8FromU16(dest, srcData, charCount);
                } else {
                    memcpy(dest, srcData, elemSize * charCount);
                }
                parentBlob->offset += elemSize * count;
                break;
            }
            case 14: {
                if (argArr != vmNull) {
                    strObj = CHANSVmGetArrayElement(VmInst, argArr, argCount);
                    strObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, strObj);
                } else {
                    strObj = CHANSVmGetArg(VmInst, argCount + 1);
                    strObj = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, strObj);
                }
                argCount++;
                if (strObj == vmNull) {
                    goto error;
                }

                if (paramValue < 0) {
                    count = (u32)strObj->value.int32_v->val >> 1;
                } else {
                    count = paramValue;
                }
                if (count < 0) {
                    goto error;
                }

                bufSize = (s32)((u32)count + 1U) / 2;
                if (!CHANSVmBlobHasSpace(parentBlob, bufSize)) {
                    goto error;
                }

                srcData = (u8*)VmGetStrFromObjHdr(strObj);
                strLen = (u32)VmGetIntFromObjHdr(strObj) >> 1;
                dest = parentBlob->pData + parentBlob->offset;
                memset(dest, 0, bufSize);

                for (i = 0; (s32)i < count; i++) {
                    ch = ((const u16*)srcData)[i];
                    if (ch >= 0x30 && ch <= 0x39) {
                        ch -= 0x30;
                    } else if (ch >= 0x61 && ch <= 0x66) {
                        ch -= 0x57;
                    } else if (ch >= 0x41 && ch <= 0x46) {
                        ch -= 0x37;
                    } else {
                        ch = 0;
                    }
                    if ((i & 1) == 0) {
                        ch *= 16;
                    }
                    *dest |= ch & 0xFF;
                    if (i & 1) {
                        dest++;
                    }
                }
                parentBlob->offset += bufSize;
                break;
            }
            default: {
                goto error;
            }
        }
    }

    if (flag != 0) {
        parentBlob->offset = 0;
    }
    return vmTrue;

error:
    return vmFalse;
}

static u64 CHANSVmMakeU64(u32 upper, u32 lower) {
    // Read U64 and byte-swap
    u64 x = (u64)upper << 32 | lower;
    return x >> 56 & 0x00000000000000ffULL | x >> 40 & 0x000000000000ff00ULL | x >> 24 & 0x0000000000ff0000ULL | x >> 8 & 0x00000000ff000000ULL |
           x << 8 & 0x000000ff00000000ULL | x << 24 & 0x0000ff0000000000ULL | x << 40 & 0x00ff000000000000ULL | x << 56 & 0xff00000000000000ULL;
}

VmMethodDefine(Blob, Create) {
    return VmBlobPackCommon(VmInst, VmParentObj, VmReturnObj, vmTrue);
}

VmMethodDefine(Blob, Pack) {
    return VmBlobPackCommon(VmInst, VmParentObj, VmReturnObj, vmFalse);
}

VmMethodDefine(Blob, Unpack) {
    union {
        u64 value;
        u32 words[2];
    } unpackBuf;
    s32 hexByteCount;
    u8* hexDigits;
    CHANSVmObjHdr* argStr;
    BlobHeader* srcBlob;
    u32 stringLength;
    u32 elemIdx;
    CHANSVmObjHdr* stringElement;
    s32 hexIndex;
    CHANSVmObjHdr* integerElement;
    u32 fmtPos;
    u8* hexSource;
    CHANSVmObjHdr* blobElement;
    u32 unpackPos;
    u32 iterIdx;
    u32 stringIndex;
    u8* stringData;
    u8* hexSourceData;
    u32 argCount;
    wchar_t* fmtStr;
    u8 hexByte;
    wchar_t* hexDestination;
    wchar_t* hexString;
    s32 elementCount;
    u32 remainingChars;
    CHANSVmObjHdr* hexElement;
    u32 fmtLen;
    s32 blobCount;
    u32 blobOff;
    s32 count;
    u32 valueHigh;
    u32 valueLow;
    u8* stringSource;
    s32 digitCount;
    s32 charCount;
    u8* blobData;
    u8 hexNibble;

    srcBlob = (BlobHeader*)VmGetStrFromObjHdr(VmParentObj);
    argStr = CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, CHANSVmGetArg(VmInst, 0));
    fmtStr = (wchar_t*)VmGetStrFromObjHdr(argStr);
    fmtLen = (u32)VmGetIntFromObjHdr(argStr) >> 1;

    if (srcBlob == vmNull || fmtStr == vmNull) {
        return vmFalse;
    }

    blobOff = srcBlob->offset;
    argCount = 0;
    fmtPos = 0;

    while (vmTrue) {
        u32 nextPos = 0;
        u32 elemType = 0;
        u32 elemSize = 1;
        s32 paramValue = 1;

        fmtPos = vmBlobParsePackFormatString(&nextPos, &elemType, &elemSize, (u32*)&paramValue, fmtStr, fmtLen, fmtPos);

        if (elemType == 1) {
            break;
        }

        if (elemType == 0) {
            goto error;
        }

        switch (elemType) {
            case 4: {
                if (paramValue < 0) {
                    count = srcBlob->size - blobOff;
                } else {
                    count = paramValue;
                }
                if (count < 0) {
                    goto error;
                }
                blobOff += count;
                argCount++;
                break;
            }
            case 5: {
                if (paramValue < 0) {
                    goto error;
                }
                blobOff += paramValue;
                break;
            }
            case 6:
            case 7:
            case 8:
            case 9: {
                if (paramValue < 0) {
                    if (elemSize == 0) {
                        goto error;
                    }
                    count = (srcBlob->size - blobOff) / elemSize;
                } else {
                    count = paramValue;
                }
                if (count < 0) {
                    goto error;
                }
                argCount += count;
                blobOff += elemSize * count;
                break;
            }
            case 10:
            case 11:
            case 12:
            case 13: {
                if (paramValue < 0) {
                    if (elemSize == 0) {
                        goto error;
                    }
                    count = (srcBlob->size - blobOff) / elemSize;
                } else {
                    count = paramValue;
                }
                if (count < 0) {
                    goto error;
                }
                argCount++;
                blobOff += elemSize * count;
                break;
            }
            case 14: {
                if (paramValue < 0) {
                    count = (srcBlob->size - blobOff) * 2;
                } else {
                    count = paramValue;
                }
                if (count < 0) {
                    goto error;
                }
                argCount++;
                blobOff += (count + 1) / 2;
                break;
            }
        }

        if (blobOff > srcBlob->size) {
            goto error;
        }
    }

    {
        u32 elemCount = argCount;
        if (CHANSVmNewArrayObject(VmInst, VmReturnObj, 1, &elemCount) == vmNull) {
            goto error;
        }
    }

    elemIdx = 0;
    unpackPos = 0;

    while (vmTrue) {
        u32 outPos;
        u32 outSize = 1;
        u32 outType = 0;
        s32 outVal = 1;

        unpackPos = vmBlobParsePackFormatString(&outPos, &outType, &outSize, (u32*)&outVal, fmtStr, fmtLen, unpackPos);

        if (outType == 1) {
            break;
        }

        if (outType == 0) {
            goto error;
        }

        switch (outType) {
            case 4: {
                if (outVal < 0) {
                    blobCount = srcBlob->size - srcBlob->offset;
                } else {
                    blobCount = outVal;
                }
                if (blobCount < 0 || !CHANSVmBlobHasSpace(srcBlob, blobCount)) {
                    goto error;
                }

                blobData = srcBlob->pData + srcBlob->offset;
                blobElement = CHANSVmGetArrayElement(VmInst, VmReturnObj, elemIdx);
                elemIdx++;
                if (blobElement == vmNull || CHANSVmNewBlobObject(VmInst, blobElement, blobCount, blobData, blobCount) == vmNull) {
                    goto error;
                }

                srcBlob->offset += blobCount;
                break;
            }
            case 5: {
                if (outVal < 0 || !CHANSVmBlobHasSpace(srcBlob, outVal)) {
                    goto error;
                }

                srcBlob->offset += outVal;
                break;
            }
            case 6:
            case 7:
            case 8:
            case 9: {
                if (outVal < 0) {
                    if (outSize == 0) {
                        goto error;
                    }
                    elementCount = (srcBlob->size - srcBlob->offset) / outSize;
                } else {
                    elementCount = outVal;
                }
                if (elementCount < 0 || !CHANSVmBlobHasSpace(srcBlob, outSize * elementCount)) {
                    goto error;
                }

                for (iterIdx = 0; iterIdx < elementCount; iterIdx++) {
                    unpackBuf.words[1] = 0;
                    unpackBuf.words[0] = 0;
                    memcpy(unpackBuf.words, srcBlob->pData + srcBlob->offset, outSize);

                    switch ((s32)outType) {
                        case 6:
                        case 7: {
                            // little endian
                            break;
                        }
                        case 8:
                        case 9: {
                            // big endian
                            switch (outSize) {
                                case 2: {
                                    __sthbrx(*(u16*)unpackBuf.words, unpackBuf.words, 0);
                                    break;
                                }
                                case 4: {
                                    __stwbrx(unpackBuf.words[0], unpackBuf.words, 0);
                                    break;
                                }
                                case 8: {
                                    unpackBuf.value = CHANSVmMakeU64(unpackBuf.words[0], unpackBuf.words[1]);
                                    break;
                                }
                            }
                            break;
                        }
                    }

                    switch ((s32)outType) {
                        case 6:
                        case 8: {
                            // signed
                            switch (outSize) {
                                case 1: {
                                    valueLow = *(s8*)unpackBuf.words;
                                    valueHigh = (s32)valueLow >> 31;
                                    break;
                                }
                                case 2: {
                                    valueLow = *(s16*)unpackBuf.words;
                                    valueHigh = (s32)valueLow >> 31;
                                    break;
                                }
                                case 4: {
                                    valueLow = *(s32*)unpackBuf.words;
                                    valueHigh = (s32)valueLow >> 31;
                                    break;
                                }
                                case 8: {
                                    valueHigh = unpackBuf.words[0];
                                    valueLow = unpackBuf.words[1];
                                    break;
                                }
                                default: {
                                    goto error;
                                }
                            }
                            break;
                        }
                        case 7:
                        case 9: {
                            // unsigned
                            switch (outSize) {
                                case 1: {
                                    valueLow = *(u8*)unpackBuf.words;
                                    valueHigh = 0;
                                    break;
                                }
                                case 2: {
                                    valueLow = *(u16*)unpackBuf.words;
                                    valueHigh = 0;
                                    break;
                                }
                                case 4: {
                                    valueLow = unpackBuf.words[0];
                                    valueHigh = 0;
                                    break;
                                }
                                default: {
                                    goto error;
                                }
                            }
                            break;
                        }
                        default: {
                            goto error;
                        }
                    }

                    integerElement = CHANSVmGetArrayElement(VmInst, VmReturnObj, elemIdx);
                    elemIdx++;
                    if (integerElement == vmNull || CHANSVmSetInteger(VmInst, integerElement, (s64)(((u64)valueHigh << 32) | valueLow)) != CHANS_VM_OK) {
                        goto error;
                    }

                    srcBlob->offset += outSize;
                }
                break;
            }
            case 10:
            case 11:
            case 12:
            case 13: {
                charCount = outVal;
                if (charCount < 0) {
                    if (outSize == 0) {
                        goto error;
                    }
                    charCount = (srcBlob->size - srcBlob->offset) / outSize;
                }
                if (charCount < 0 || !CHANSVmBlobHasSpace(srcBlob, outSize * charCount)) {
                    goto error;
                }

                stringSource = srcBlob->pData + srcBlob->offset;
                stringElement = CHANSVmGetArrayElement(VmInst, VmReturnObj, elemIdx);
                elemIdx++;
                if (stringElement == vmNull) {
                    goto error;
                }

                if (outSize == 1) {
                    if (CHANSVmSetU16StringFromU8(VmInst, stringElement, (char*)stringSource, charCount) != CHANS_VM_OK) {
                        goto error;
                    }
                } else if (CHANSVmSetU16String(VmInst, stringElement, (wchar_t*)stringSource, outSize * charCount) != CHANS_VM_OK) {
                    goto error;
                }

                if (outType == 0xB || outType == 0xD) {
                    stringData = (u8*)VmGetStrFromObjHdr(stringElement);
                    stringLength = (u32)VmGetIntFromObjHdr(stringElement);
                    if (stringData != vmNull && stringLength != 0 && stringElement->type == CHANS_VM_OBJ_TYPE_STRING) {
                        remainingChars = stringLength / 2;
                        stringIndex = 0;
                        while (remainingChars-- != 0 && VM_READ_BE_U16(stringData, 0) != 0) {
                            stringData += 2;
                            stringIndex++;
                        }
                        stringElement->value.string_v->len = stringIndex * 2;
                    }
                }

                srcBlob->offset += outSize * charCount;
                continue;
            }
            case 14: {
                digitCount = outVal;
                if (digitCount < 0) {
                    digitCount = (srcBlob->size - srcBlob->offset) * 2;
                }
                if (digitCount < 0) {
                    goto error;
                }

                hexByteCount = (digitCount + 1) / 2;
                if (!CHANSVmBlobHasSpace(srcBlob, hexByteCount)) {
                    goto error;
                }

                hexSourceData = srcBlob->pData + srcBlob->offset;
                hexElement = CHANSVmGetArrayElement(VmInst, VmReturnObj, elemIdx);
                elemIdx++;
                if (hexElement == vmNull || CHANSVmNewObject(VmInst, vmFalse, hexElement, CHANS_VM_OBJ_TYPE_STRING, digitCount * 2) == vmNull) {
                    goto error;
                }

                {
                    hexString = (wchar_t*)VmGetStrFromObjHdr(hexElement);

                    hexDigits = (u8*)scHexDigitsPtr2;
                    hexSource = hexSourceData;
                    hexDestination = hexString;

                    for (hexIndex = 0; hexIndex < digitCount / 2; hexSource++, hexIndex++) {
                        hexByte = *hexSource;
                        hexNibble = (hexByte / 16) & 0xF;
                        hexByte &= 0xF;
                        hexDestination[0] = (wchar_t)(s8)hexDigits[hexNibble];
                        hexDestination[1] = (wchar_t)(s8)hexDigits[hexByte];
                        hexDestination += 2;
                    }
                    if (hexIndex * 2 < digitCount) {
                        hexByte = *hexSource;
                        *hexDestination = (wchar_t)(s8)hexDigits[(hexByte >> 4) & 0xF];
                    }
                }

                srcBlob->offset += hexByteCount;
                continue;
            }
            default: {
                goto error;
            }
        }
    }
    return vmTrue;

error:
    return vmFalse;
}

CHANSVmObjHdr* CHANSVmNewBlobObject(CHANSVm* VmInst, CHANSVmObjHdr* obj, u32 size, void* src, u32 count) {
    BlobHeader* blob;

    if (count > size) {
        count = size;
    }

    obj = VmBlobCreateDirect(VmInst, obj, size);
    if (obj == vmNull) {
        return vmNull;
    }

    if (src != vmNull && count != 0) {
        if (CHANSVmCheckNativeInstance(obj, VmBlobClassName)) {
            blob = (BlobHeader*)VmGetStrFromObjHdr(obj);
        } else {
            blob = vmNull;
        }

        if (blob == vmNull) {
            return vmNull;
        }

        memcpy(blob->pData, src, count);
    }

    return obj;
}

const CHANSVmPropertyList VmBlobPropertyTbl[] = {
    {"offset", VmBlobGetOffset, VmBlobSeek},
    {"length", VmBlobGetLength, VmBlobSetLength},
};
const CHANSVmMethodList VmBlobMethodTbl[] = {
    {"*create", VmBlobCreate},
    {"seek", VmBlobSeek},
    {"skip", VmBlobSkip},
    {"isEqual", VmBlobIsEqual},
    {"getLength", VmBlobGetLength},
    {"setLength", VmBlobSetLength},
    {"fill", VmBlobFill},
    {"getU8", VmBlobGetU8},
    {"getU16", VmBlobGetU16},
    {"getU32", VmBlobGetU32},
    {"getS8", VmBlobGetS8},
    {"getS16", VmBlobGetS16},
    {"getS32", VmBlobGetS32},
    {"getS64", VmBlobGetS64},
    {"setU8", VmBlobSetU8},
    {"setU16", VmBlobSetU16},
    {"setU32", VmBlobSetU32},
    {"setS8", VmBlobSetS8},
    {"setS16", VmBlobSetS16},
    {"setS32", VmBlobSetS32},
    {"setS64", VmBlobSetS64},
    {"getString", VmBlobGetString},
    {"getWString", VmBlobGetWString},
    {"setString", VmBlobSetString},
    {"setWString", VmBlobSetWString},
    {"getBlob", VmBlobGetBlob},
    {"setBlob", VmBlobSetBlob},
    {"getHexString", VmBlobGetHexString},
    {"copyRangeFrom", VmBlobCopyRangeFrom},
    {"calcSHA1Digest", VmBlobCalcSHA1Digest},
    {"calcMD5Digest", VmBlobCalcMD5Digest},
    {"calcCRC16", VmBlobCalcCRC16},
    {"calcCRC32", VmBlobCalcCRC32},
    {"calcHMAC", VmBlobCalcHMAC},
    {"calcRangeSHA1Digest", VmBlobCalcRangeSHA1Digest},
    {"calcRangeMD5Digest", VmBlobCalcRangeMD5Digest},
    {"calcRangeCRC16", VmBlobCalcRangeCRC16},
    {"calcRangeCRC32", VmBlobCalcRangeCRC32},
    {"calcRangeHMAC", VmBlobCalcRangeHMAC},
    {"pack", VmBlobPack},
    {"unpack", VmBlobUnpack},
};

VmMethodDefine(Image, Width) {
    CHANSVmImage* image = *VmParentObj->value.ptr_v;
    return CHANSVmSetInteger(VmInst, VmReturnObj, image->width) == CHANS_VM_OK;
}
VmMethodDefine(Image, Height) {
    CHANSVmImage* image = *VmParentObj->value.ptr_v;
    return CHANSVmSetInteger(VmInst, VmReturnObj, image->height) == CHANS_VM_OK;
}
VmMethodDefine(Image, Format) {
    CHANSVmImage* image = *VmParentObj->value.ptr_v;
    return CHANSVmSetInteger(VmInst, VmReturnObj, image->format) == CHANS_VM_OK;
}

void CHANSVmImageRegisterAllocator(CHANSVmImageAllocatorCallback allocCb, CHANSVmImageCtorCallback ctorCb) {
    VmImageAllocCallback = allocCb;
    VmImageCtorCallback = ctorCb;
}

char scImageClassName[] = "Image";

CHANSVmObjHdr* CHANSVmNewImageObject(CHANSVm* vm, CHANSVmObjHdr* object, vmPtr srcData, vmU16 width, vmU16 height, s32 format) {
    u32 bpp;
    CHANSVmImage* image;
    u32 dataSize;
    u32 allocSize;

    if ((width & 7) != 0 || (height & 7) != 0) {
        goto error;
    }

    switch (format) {
        case GX_TF_I8:
        case GX_TF_IA4: {
            bpp = 8;
            break;
        }
        case GX_TF_IA8:
        case GX_TF_RGB565:
        case GX_TF_RGB5A3: {
            bpp = 16;
            break;
        }
        case GX_TF_RGBA8:
        default: {
            bpp = 32;
            break;
        }
    }

    dataSize = (u32)((u32)width * (u32)height) * bpp / 8;
    allocSize = (dataSize & ~(-(VmImageAllocCallback != vmNull))) + 0x20;

    object = CHANSVmNewObject(vm, vmFalse, object, CHANS_VM_TYPE_OBJECT, allocSize);
    if (object == vmNull) {
        goto ret;
    }
    if (CHANSVmSetObjectAsNativeInstance(vm, object, vmNull, scImageClassName) != CHANS_VM_OK) {
        goto error;
    }
    image = *object->value.ptr_v;
    image->width = width;
    image->height = height;
    image->format = (u8)format;
    image->bpp = (u8)bpp;

    if (dataSize != 0) {
        if (VmImageAllocCallback != vmNull) {
            image->pData = VmImageAllocCallback(vm, dataSize);
        } else {
            image->pData = (u8*)image + 0x20;
        }
        if (image->pData == 0) {
            goto error;
        }
        image->size = dataSize;
        if (srcData != vmNull) {
            memcpy(image->pData, srcData, dataSize);
            DCStoreRange(image->pData, dataSize);
        }
    }
ret:
    return object;

error:
    return vmNull;
}

VmCtorDefine(Image) {
    vmBoolInt result = vmFalse;
    CHANSVmImage* image = *VmParentObj->value.ptr_v;

    if (VmImageCtorCallback != vmNull) {
        if (image->pData != 0 && image->size != 0) {
            result = VmImageCtorCallback(VmInst, image->pData);
        }
    } else {
        result = vmTrue;
    }

    return result;
}

const CHANSVmPropertyList VmImagePropertyTbl[] = {
    {"width", VmImageWidth, vmNull},
    {"height", VmImageHeight, vmNull},
    {"format", VmImageFormat, vmNull},
};

static vmBoolInt VmWinEmuWrite(CHANSVm* vm, CHANSVmObjHdr* parent, CHANSVmObjHdr* ret) {
    CHANSVmObjHdr* strObj;
    u32 offset;
    u32 totalLength;
    u8 buf[VM_STRING_SIZE];
    s32 outLen;
    s32 inLen;
    s32 result;
    u32 remaining;

    strObj = CHANSVmConvertObjectType(vm, CHANS_VM_OBJ_TYPE_STRING, CHANSVmGetArg(vm, 0));
    if (strObj != vmNull && strObj->type == CHANS_VM_OBJ_TYPE_STRING) {
        offset = 0;
        totalLength = strObj->value.wstring_v->len & ~1;

        while (offset < totalLength) {
            remaining = totalLength - offset;
            outLen = VM_STRING_SIZE;
            inLen = (remaining < VM_STRING_SIZE ? remaining : VM_STRING_SIZE) / 2;

            result = ENCConvertStringUnicodeToSjis(buf, &outLen, (u16*)((u8*)strObj->value.wstring_v->spData + offset), &inLen);
            if (result == ENC_OK) {
                buf[outLen] = 0;
                buf[outLen + 1] = 0;
                OSReport(VmReportFormat, buf);
            } else {
                OSReport("document.write(): conversion error (%d)\n", result);
                break;
            }

            offset += VM_STRING_SIZE;
        }
    }
    return vmTrue;
}

const CHANSVmMethodList VmWinEmuMethodTbl[] = {"write", VmWinEmuWrite};

char scDateClassName[] = "Date";
char scMathInternalName[] = "@Math";
char scMathClassName[] = "Math";
char scWinEmuInternalName[] = "@WinEmu";

static CHANSVmErr VmPushFuncReturnInfo(CHANSVm* vm, u32 argCount, u32 totalSlots, u32 headerCount);

CHANSVmErr CHANSVmInit(CHANSVm* vm, vmPtr work, vmU32 size) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;
    u32 alignedBase;
    u32 alignedSize;
    u32 exeSize;
    u32 exeStart;
    vmS32 result;
    CHANSVmNativeClass* cls;

    memset(vm, 0, sizeof(CHANSVm));

    alignedBase = VM_ALIGN((u32)work);
    alignedSize = VM_ALIGN_DOWN((u32)((u8*)work + size)) - alignedBase;

    pVm->exeStart = alignedBase;
    pVm->exeSize = alignedSize;
    pVm->minWorkSize = 0x820;
    if (alignedSize < pVm->minWorkSize) {
        return CHANS_VM_ERR_NO_MEMORY;
    }

    exeStart = alignedBase + 0x820;
    exeSize = alignedSize - 0x820;

    pVm->pBase = (vmU8*)alignedBase;
    pVm->exeStart = exeStart;
    pVm->exeSize = exeSize;
    pVm->pHeapStart = (vmU8*)exeStart;
    pVm->pHeapEnd = (vmU8*)exeStart + exeSize;
    pVm->pFreeExeBuf = (vmU8*)exeStart;
    pVm->pObjStackTopBuf = (vmU8*)(exeStart + exeSize);

    result = VmPushFuncReturnInfo(vm, 0, 0, 0);
    if (result == CHANS_VM_OK) {
        CHANSVmErr ok;
        CHANSVmErr ret;

        // TODO: this could use some cleanup
        /* Array class */
        cls = CHANSVmAddNativeClass2(vm, VmArrayClassName, VmArrayCtor, VmArrayDtor, VmArrayCtor);
        if (cls != vmNull &&
            (VmArrayPropertyTbl == vmNull ||
             CHANSVmAddNativePropertyAccessorsList(vm, cls, VmArrayPropertyTbl, CHANSVmPropertyCount(VmArrayPropertyTbl)) == CHANS_VM_OK) &&
            (VmArrayMethodTbl == vmNull ||
             CHANSVmAddNativeMethodList(vm, cls, VmArrayMethodTbl, CHANSVmMethodCount(VmArrayMethodTbl)) == CHANS_VM_OK)) {
            ok = vmTrue;
        } else {
            ok = vmFalse;
        }
        if (ok && (cls = CHANSVmFindNativeClass(vm, VmArrayClassName)) != vmNull) {
            pVm->pArrayCls = cls;
            ok = vmTrue;
        } else {
            ok = vmFalse;
        }
        if (!ok)
            goto class_fail;

        /* Date class */
        cls = CHANSVmAddNativeClass2(vm, scDateClassName, VmDateCtor, 0, VmDateDtor);
        if (cls == vmNull) {
            ok = vmFalse;
        } else {
            ok = (CHANSVmAddNativeMethodList(vm, cls, VmDateMethodTbl, CHANSVmMethodCount(VmDateMethodTbl)) == CHANS_VM_OK);
        }
        if (!ok)
            goto class_fail;

        /* Math class */
        if (CHANSVmNewBuiltinObject(vm, scMathInternalName, vmNull, vmNull, vmNull, scMathClassName, vmNull, VmMathPropertyTbl, CHANSVmPropertyCount(VmMathPropertyTbl),
                                    VmMathMethodTbl, CHANSVmMethodCount(VmMathMethodTbl)) == 0) {
            goto class_fail;
        }

        /* String class */
        if (CHANSVmNewBuiltinObject(vm, VmStringClassName, VmStringCtor, vmNull, VmStringCtor, vmNull, vmNull, VmStringPropertyTbl,
                                    CHANSVmPropertyCount(VmStringPropertyTbl), VmStringMethodTbl, CHANSVmMethodCount(VmStringMethodTbl)) == 0) {
            goto class_string_fail;
        }
        cls = CHANSVmFindNativeClass(vm, VmStringClassName);
        if (cls != vmNull) {
            pVm->pStringCls = cls;
            ok = vmTrue;
        } else {
        class_string_fail:
            ok = vmFalse;
        }
        if (!ok)
            goto class_fail;

        /* Blob class */
        cls = CHANSVmAddNativeClass2(vm, VmBlobClassName, VmBlobCtor, VmBlobDtor, vmNull);
        if (cls == vmNull) {
            ok = vmFalse;
        } else {
            ret = CHANSVmAddNativePropertyAccessorsList(vm, cls, VmBlobPropertyTbl, CHANSVmPropertyCount(VmBlobPropertyTbl));
            if (ret == CHANS_VM_OK) {
                ret = CHANSVmAddNativeMethodList(vm, cls, VmBlobMethodTbl, CHANSVmMethodCount(VmBlobMethodTbl));
            }
            ok = (ret == CHANS_VM_OK);
        }
        if (!ok) {
            goto class_fail;
        }

        /* Image class */
        VmImageAllocCallback = vmNull;
        VmImageCtorCallback = vmNull;
        if (CHANSVmNewBuiltinObject(vm, scImageClassName, vmNull, VmImageCtor, vmNull, vmNull, vmNull, VmImagePropertyTbl, CHANSVmPropertyCount(VmImagePropertyTbl),
                                    vmNull, 0) == 0) {
            goto class_fail;
        }

        /* Screen (@WinEmu) class */
        if (CHANSVmNewBuiltinObject(vm, scWinEmuInternalName, vmNull, vmNull, vmNull, "document", vmNull, vmNull, 0, (CHANSVmMethodList*)&VmWinEmuMethodTbl,
                                    CHANSVmMethodCount(VmWinEmuMethodTbl)) == 0) {
        class_fail:
            result = CHANS_VM_ERR_NATIVE_METHOD_INIT;
        }

    }

    memset(&pVm->accumulator, 0, sizeof(CHANSVmObjHdr));
    return result;
}

vmPtr CHANSVmGetFreeExeBufp(CHANSVm* vm) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;

    if (pVm->bAllocBlocked != vmFalse || pVm->pFreeExeBuf >= pVm->pObjStackTopBuf) {
        return vmNull;
    }
    return pVm->pFreeExeBuf;
}

vmU32 CHANSVmGetFreeExeSize(CHANSVm* vm) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;

    vmS32 size = (vmU32)pVm->pObjStackTopBuf - (vmU32)pVm->pFreeExeBuf;
    if (pVm->bAllocBlocked != vmFalse || size < 0) {
        return 0;
    }
    return size;
}

void CHANSConvertModuleOfsToPtr(CHANSVmModule* ptr);

static inline int VmFixMethodTable(CHANSVmModule* header, CHANSVm* vm) {
    u32 i;
    DispatchEntry* methodTable = header->pMethodRefTbl;

    for (i = 1; i < header->methodCount; i++) {
        if (methodTable[i].nameLength) {
            if ((u8*)(methodTable[i].offset + (methodTable[i].nameLength + (vmU32)methodTable)) <=
                (u8*)((vmU32)header + header->regionSize)) {
                CHANSVmObjHdr* method = (CHANSVmObjHdr*)CHANSVmAddNativeMethodName(vm, (const char*)(methodTable[i].offset + (vmU32)methodTable),
                                                                                   methodTable[i].nameLength);
                if (method) {
                    header->pMethodTbl[i] = (vmU32)method;
                    continue;
                }
            }
        }
        return 0;
    }
    return 1;
}

CHANSVmErr CHANSVmAddExe(CHANSVm* vm, vmS32 reserved, CHANSVm* execCtx) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;
    ModuleHeader* mod;
    CHANSVmModule* header;
    u32 maxEnd;
    u32 size;
    u32 cnt;
    u32 ofs;

    mod = (ModuleHeader*)pVm->pFreeExeBuf;
    size = mod->size;
    if (memcmp(&mod->magic, "RCHE", 4) != 0 || size < 0x80 || size & 0x1F) {
    fail_format:
        return CHANS_VM_ERR_INVALID_EXE_FORMAT;
    }
    if (mod->type != (u32)execCtx) {
        return CHANS_VM_ERR_INVALID_EXE_TYPE;
    }
    if (mod->opcodeVersion != 3) {
        return CHANS_VM_ERR_OPCODE_VERSION;
    }
    if (CHANSVmGetFreeExeSize(vm) < size) {
        return CHANS_VM_ERR_NO_MEMORY;
    }

    pVm->pFreeExeBuf = pVm->pFreeExeBuf + size;
    // Struct access using 'header = mod->module' breaks the match
    header = (CHANSVmModule*)(mod + 1);
    header->pNext = vmNull;
    header->regionSize = size - sizeof(ModuleHeader);
    header->pModule = mod;

    if ((u32)header->pData < 0x60 || header->regionSize < (u32)header->pData || header->regionSize < header->codeSize) {
        goto fail_format;
    }
    maxEnd = (u32)header->pData + header->codeSize;
    if (header->regionSize < maxEnd) {
        goto fail_format;
    }

#define CHECK_TABLE_REGION(countField, offsField, entrySize)                                                                                         \
    cnt = countField;                                                                                                                                \
    if (cnt) {                                                                                                                                       \
        ofs = (u32)offsField;                                                                                                                        \
        if (ofs < maxEnd || header->regionSize < ofs) {                                                                                              \
            goto fail_format;                                                                                                                        \
        }                                                                                                                                            \
        maxEnd = ofs + cnt * entrySize;                                                                                                              \
        if (header->regionSize < maxEnd) {                                                                                                           \
            goto fail_format;                                                                                                                        \
        }                                                                                                                                            \
    }

    CHECK_TABLE_REGION(header->nameCount, header->pNameTbl, sizeof(NameTblEntry))
    CHECK_TABLE_REGION(header->methodCount, header->pMethodRefTbl, sizeof(u32))
    CHECK_TABLE_REGION(header->stringCount, header->pStringDataTbl, sizeof(u16))
    if (header->pLineTbl) {
        u32 clsSize = (header->codeSize + 255) / 256;
        if ((u32)header->pLineTbl >= maxEnd && header->regionSize >= (u32)header->pLineTbl) {
            // TODO: 0x24 should be sizeof(...)
            clsSize = (u32)header->pLineTbl + clsSize * 0x24;
            if (header->regionSize < clsSize) {
                goto fail_format;
            }
        } else {
            goto fail_format;
        }
    }

    {
        CHANSVmExecutionCtx* ctx = pVm->pContextListHead;
        u32 depth = 1;

        if (ctx == vmNull) {
            pVm->pContextListHead = (CHANSVmExecutionCtx*)header;
        } else {
            while (ctx->pNext != vmNull) {
                ctx = ctx->pNext;
                depth++;
            }
            ctx->pNext = (CHANSVmExecutionCtx*)header;
        }
        pVm->depth = depth;
    }

    if (header->moduleCount) {
        header->pModuleTbl = CHANSVmAlloc(vm, VM_ALIGN(header->moduleCount * sizeof(ModuleEntry)));
    }

    if (header->methodCount) {
        header->pMethodTbl = CHANSVmAlloc(vm, VM_ALIGN(header->methodCount * sizeof(u32)));
    }

    if (header->stringCount) {
        header->pStringTbl = CHANSVmAlloc(vm, VM_ALIGN(header->stringCount * sizeof(StringTblEntry)));
    }

    if (header->moduleCount && header->pModuleTbl == vmNull || header->methodCount && header->pMethodTbl == vmNull ||
        header->stringCount != 0 && header->pStringTbl == vmNull) {
        return CHANS_VM_ERR_NO_MEMORY;
    }

    {
        u32 i;
        for (i = 0; i < header->moduleCount; i++) {
            memset(&header->pModuleTbl[i], 0, sizeof(ModuleEntry));
        }
    }

    CHANSConvertModuleOfsToPtr(header);

    if (!VmFixMethodTable(header, vm)) {
        goto fail_format;
    }
    {
        u8* strPtr = header->pStringDataTbl;
        u32 i;
        int ok;

        for (i = 0; i < header->stringCount; i++) {
            u32 len = VM_READ_BE_U16(strPtr, 0);
            strPtr += 2;

            if ((len & 1) == 0) {
                if (strPtr + len <= (u8*)((vmU32)header + header->regionSize)) {
                    header->pStringTbl[i].pStringData = strPtr;
                    header->pStringTbl[i].length = len;
                    strPtr += len;
                    continue;
                }
            }
            ok = 0;
            goto check_str;
        }
        ok = 1;
    check_str:
        if (ok == 0) {
            goto fail_format;
        }
    }

    return CHANS_VM_OK;
}

static void VmOffs00U32ToPtr(vmPtr ptr) {
    if (*(vmU32*)ptr != 0) {
        *(vmU32*)ptr += (vmU32)ptr;
    }
}

static void VmOffsU32ToPtr(vmPtr ptr, vmPtr offset) NO_INLINE {
    if (*(vmU32*)ptr != 0) {
        *(vmU32*)ptr += (vmU32)offset;
    }
}

void CHANSConvertModuleOfsToPtr(CHANSVmModule* ptr) {
    VmOffs00U32ToPtr(ptr);
    VmOffsU32ToPtr(&ptr->pData, ptr);
    VmOffsU32ToPtr(&ptr->pNameTbl, ptr);
    VmOffsU32ToPtr(&ptr->pMethodRefTbl, ptr);
    VmOffsU32ToPtr(&ptr->pStringDataTbl, ptr);
    VmOffsU32ToPtr(&ptr->pDispatchTbl, ptr);
    VmOffsU32ToPtr(&ptr->pLineTbl, ptr);
}

static CHANSVmObjHdr* CHANSVmLookupScopedObject(CHANSVm* vm, s32 id) {
    CHANSVmObjHdr* data = vmNull;
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;
    CHANSVmExecutionCtx* ctx = pVm->pActiveCtx;
    s32 idx;

    if (id < ctx->pDbg->moduleCount) {
        data = (CHANSVmObjHdr*)ctx->pDbg->pModuleTbl + id;
        if (data->type == CHANS_VM_TYPE_GLOBAL_REF) {
            data = data->value.data.ptr;
        }
    } else {
        id -= ctx->frameBase;
        if (id >= 0) {
            if (id >= ctx->headerCount) {
                id -= ctx->headerCount;
                idx = ctx->argc - 1 - id;
                if (idx < 0) {
                    goto notFound;
                }
                data = (CHANSVmObjHdr*)ctx->pArgv + idx;
            } else {
                data = &ctx->headers[id];
            }
        }
    }

    return data;

notFound:
    return vmNull;
}

static inline vmU32 VmStackSpace(CHANSVmPrivate* pVm) {
    vmU32 space = (vmU32)pVm->pFreeExeBuf;
    space = (vmU32)pVm->pObjStackTopBuf - space;
    return space;
}

static CHANSVmErr VmPushFuncReturnInfo(CHANSVm* vm, u32 argCount, u32 totalSlots, u32 headerCount) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;
    CHANSVmExecutionCtx* block;
    CHANSVmErr result;
    vmU8* objStackTopBuf;
    u32 size;
    u32 i;

    result = CHANS_VM_ERR_PUSH_FUNC_RETURN_INFO;
    if (pVm->pActiveCtx != vmNull && pVm->pActiveCtx->stackDepth < argCount) {
        return result;
    }

    if (headerCount <= 0xFF) {
        objStackTopBuf = pVm->pObjStackTopBuf;

        while (argCount < totalSlots) {
            objStackTopBuf -= sizeof(CHANSVmObjHdr);
            if (pVm->pFreeExeBuf > objStackTopBuf) {
                return CHANS_VM_ERR_NO_MEMORY;
            }
            memset(objStackTopBuf, 0, sizeof(CHANSVmObjHdr));

            argCount++;
            if ((u32)pVm->pActiveCtx->stackDepth < -1) {
                pVm->pActiveCtx->stackDepth++;
            } else {
                return CHANS_VM_ERR_PUSH_FUNC_RETURN_INFO;
            }
        }

        pVm->pObjStackTopBuf = objStackTopBuf;
        CHANSVmUpdateSmallestFreeHeapSize(vm);

        size = headerCount * sizeof(CHANSVmObjHdr) + sizeof(CHANSVmExecutionCtx);
        block = vmNull;

        if (size != 0 && (size & 7) == 0) {
            if (VmStackSpace(pVm) >= size) {
                block = (CHANSVmExecutionCtx*)(pVm->pObjStackTopBuf - size);
                pVm->pObjStackTopBuf = (vmU8*)block;
                CHANSVmUpdateSmallestFreeHeapSize(vm);
                memset(block, 0, size);
            }
        }

        if (block == vmNull) {
            goto return_result;
        }

        if (pVm->pActiveCtx != vmNull) {
            block->pDbg = pVm->pActiveCtx->pDbg;
            block->pc = pVm->pActiveCtx->pc;
            block->pNext = pVm->pActiveCtx;
        }

        pVm->pActiveCtx = block;
        block->pArgv = (vmWString*)objStackTopBuf;
        block->argc = argCount;
        block->totalSlots = totalSlots;
        block->headerCount = headerCount;
        block->frameBase = (vmU16)(VM_FRAME_ARENA_SIZE - (headerCount + totalSlots));

        for (i = 0; i < headerCount; i++) {
            memset(&block->headers[i], 0, sizeof(CHANSVmObjHdr));
        }

        result = 0;
    }
return_result:
    return result;
}

static CHANSVmErr VmReturnWithValue(CHANSVm* vm, u32 val) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;
    u32 i;
    CHANSVmObjHdr* obj = vmNull;
    GlobalObjListNode* node;
    CHANSVmErr ret;

    for (i = 0; i < pVm->pActiveCtx->headerCount; i++) {
        ret = CHANSVmDeleteObject(vm, &pVm->pActiveCtx->headers[i]);
        if (ret != CHANS_VM_OK) {
            return ret;
        }
    }

    while (pVm->pActiveCtx->stackDepth != 0) {
        ret = CHANSVmPopObject(vm, vmNull);
        if (ret != CHANS_VM_OK) {
            return ret;
        }
    }

    pVm->pObjStackTopBuf = (vmU8*)pVm->pActiveCtx->pArgv;

    if (val != 0) {
        obj = &pVm->accumulator;
    }

    pVm->pActiveCtx->stackDepth = pVm->pActiveCtx->argc;
    while (pVm->pActiveCtx->stackDepth != 0) {
        ret = CHANSVmPopObject(vm, obj);
        if (ret != CHANS_VM_OK) {
            return ret;
        }
    }

    if (pVm->pActiveCtx->pNext != vmNull) {
        if (pVm->pActiveCtx->pNext->stackDepth < (vmU32)pVm->pActiveCtx->argc) {
            ret = CHANS_VM_ERR_RETURN;
        } else {
            pVm->pActiveCtx->pNext->stackDepth -= pVm->pActiveCtx->argc;
            ret = CHANS_VM_OK;
        }
    } else {
        for (i = 0; i < pVm->pActiveCtx->pDbg->moduleCount; i++) {
            if (CHANSVmDeleteObject(vm, CHANSVmLookupScopedObject(vm, i)) != CHANS_VM_OK) {
                return CHANS_VM_ERR_RETURN;
            }
        }

        node = pVm->pGlobalObjList;
        while (node != vmNull) {
            node->hdr.flags.raw &= ~CHANSVM_OBJ_FLAG_READONLY;
            if (CHANSVmDeleteObject(vm, (CHANSVmObjHdr*)node) != CHANS_VM_OK) {
                return CHANS_VM_ERR_RETURN;
            }

            CHANSVmFree(vm, node, VM_ALIGN(node->nameLength + sizeof(GlobalObjListNode)));
            node = node->next;
            pVm->pGlobalObjList = node;
        }

        ret = CHANS_VM_ERR_EXIT;
    }

    pVm->pActiveCtx = pVm->pActiveCtx->pNext;
    return ret;
}

static inline CHANSVmErr VmResolveGlobalModules(CHANSVmModule* module, GlobalObjListNode* head) {
    DispatchEntry* dispatchTable;
    GlobalObjListNode* gIter;
    u32 i;
    dispatchTable = module->pDispatchTbl;

    for (gIter = head; gIter != vmNull; gIter = gIter->next) {
        for (i = 0; i < module->moduleCount; i++) {
            DispatchEntry entry = dispatchTable[i];
            u8* addr;

            if (!gIter->nameLength) {
                continue;
            }

            addr = (u8*)dispatchTable + entry.offset;
            if (addr + gIter->nameLength > (u8*)module + module->regionSize || gIter->nameLength != entry.nameLength) {
                continue;
            }

            if (memcmp(gIter->name, addr, gIter->nameLength) != 0) {
                continue;
            }

            if (module->pModuleTbl[i].type) {
                return CHANS_VM_ERR_RESOLVE_GLOBAL_OBJECT_REFERENCE;
            }
            module->pModuleTbl[i].type = CHANS_VM_TYPE_GLOBAL_REF;
            module->pModuleTbl[i].pGlobalObj = gIter;
            module->pModuleTbl[i].flags = CHANSVM_OBJ_FLAG_READONLY;
        }
    }
    return 0;
}

static inline CHANSVmErr VmResolveNativeModules(CHANSVmModule* module, CHANSVmNativeClass* head) {
    DispatchEntry* dispatchTable;
    CHANSVmNativeClass* nIter;
    u32 i;
    dispatchTable = module->pDispatchTbl;
    for (nIter = head; nIter != vmNull; nIter = nIter->pNext) {
        for (i = 0; i < module->moduleCount; i++) {
            DispatchEntry entry = dispatchTable[i];
            u8* addr;

            if (!nIter->nameLength) {
                continue;
            }

            addr = (u8*)dispatchTable + entry.offset;
            if (addr + nIter->nameLength > (u8*)module + module->regionSize || nIter->nameLength != entry.nameLength) {
                continue;
            }

            if (memcmp(nIter->sName, addr, nIter->nameLength) != 0) {
                continue;
            }

            if (module->pModuleTbl[i].type) {
                return CHANS_VM_ERR_RESOLVE_NATIVE_METHOD_CALL;
            }
            module->pModuleTbl[i].type = CHANS_VM_TYPE_CLASS_REF;
            module->pModuleTbl[i].pNativeClass = nIter;
            module->pModuleTbl[i].flags = CHANSVM_OBJ_FLAG_READONLY;
        }
    }
    return 0;
}

CHANSVmErr CHANSVmLinkModules(CHANSVm* vm, vmS32 reserved) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;
    u32 modIdx;
    CHANSVmModule* module;
    u32 i;

    (void)reserved;

    if (!pVm->bAllocBlocked && pVm->depth != 0) {
        pVm->bAllocBlocked = vmTrue;
        module = (CHANSVmModule*)pVm->pContextListHead;
        modIdx = 0;

        while (modIdx < (u32)pVm->depth) {
            CHANSVmErr result;

            pVm->pActiveCtx->pDbg = module;
            result = VmResolveGlobalModules(module, pVm->pGlobalObjList);
            if (result) {
                return result;
            }

            result = VmResolveNativeModules(module, pVm->pNativeClasses);
            if (result) {
                return result;
            }

            for (i = 0; i < module->nameCount; i++) {
                u16 idx = module->pNameTbl[i].moduleIdx;
                CHANSVmObjHdr* obj;
                if (idx >= module->moduleCount) {
                    goto pass3_idx_err;
                } else if (obj = CHANSVmLookupScopedObject(vm, idx), obj == vmNull) {
                    goto pass3_obj_err;
                } else if (obj->type == CHANS_VM_OBJ_TYPE_BLANK) {
                    goto pass3_success;
                }

            pass3_obj_err:
                result = CHANS_VM_ERR_SET_LOCAL_FUNCTION;
                goto post_pass3;

            pass3_success:
                obj->type = CHANS_VM_TYPE_METHOD_REF;
                obj->value.bool_v = (vmBoolInt)i;
                obj->flags.raw = CHANSVM_OBJ_FLAG_READONLY;
                continue;

            pass3_idx_err:
                result = CHANS_VM_ERR_SET_LOCAL_FUNCTION;
                goto post_pass3;
            }
            result = CHANS_VM_OK;
        post_pass3:
            if (result) {
                return result;
            }

            module = module->pNext;
            modIdx++;
        }

        pVm->pHeapStart = pVm->pFreeExeBuf;
        pVm->pHeapEnd = pVm->pObjStackTopBuf;
        pVm->minFreeHeapSize = (vmU32)pVm->pObjStackTopBuf - (vmU32)pVm->pFreeExeBuf;
        memset(&pVm->accumulator, 0, sizeof(CHANSVmObjHdr));
        pVm->pActiveCtx->pDbg = (CHANSVmModule*)pVm->pContextListHead;
        pVm->pActiveCtx->pc = 1;
        return CHANS_VM_OK;
    }
    return CHANS_VM_ERR_LINK_FAILED;
}

static u8* VmGetOperand(CHANSVm* vm, u32 num, u32 offset) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;
    u32 pc = pVm->pActiveCtx->pc;
    CHANSVmModule* dbg = pVm->pActiveCtx->pDbg;
    u32 addr;

    if (pc + offset >= dbg->codeSize) {
        return vmNull;
    }

    addr = pc + num;
    return dbg->pData + addr;
}

static CHANSVmErr VmLoadImmInteger(CHANSVm* vm, CHANSVmObjHdr* obj, u8* buf, s32 count) {
    u64 acc = 0;
    u8* p = buf;

    while (count != 0) {
        s32 val = (s8)*p;
        acc = (acc << 8) | (val & 0xFF);
        p++;
        count--;
    }

    return CHANSVmSetInteger(vm, obj, (vmInteger)acc);
}

CHANSVmErr VmStore(CHANSVm* vm, CHANSVmObjHdr* dest, CHANSVmObjHdr* src) {
    CHANSVmErr ret;
    if (dest == vmNull || src == vmNull) {
        return CHANS_VM_ERR_OBJECT_NOT_FOUND;
    }
    if ((dest->flags.raw & CHANSVM_OBJ_FLAG_READONLY) != 0) {
        return CHANS_VM_ERR_STORE_READONLY;
    }
    ret = CHANSVmDeleteObject(vm, dest);
    if (ret == CHANS_VM_OK) {
        if (CHANSVmCopyObject(vm, dest, src) == vmNull) {
            ret = CHANS_VM_ERR_STORE_OBJECT;
        }
    }
    return ret;
}

CHANSVmErr VmDeleteCommon(CHANSVm* vm, CHANSVmObjHdr* object) {
    CHANSVmErr result = CHANS_VM_ERR_DELETE_OBJECT;
    if (object != vmNull) {
        CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;
        result = CHANSVmDeleteObject(vm, object);
        if (result == CHANS_VM_OK) {
            if (object->type == CHANS_VM_OBJ_TYPE_BLANK) {
                result = CHANSVmSetInteger(vm, &pVm->accumulator, 1);
            } else {
                result = CHANS_VM_ERR_DELETE_OBJECT;
            }
        }
    }
    return result;
}

static CHANSVmErr VmCallMethod(CHANSVm* vm, u32 instructionSize, u32 callType, u32 ctorFlag) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;
    CHANSVmObjHdr* acc;
    u32 retVal;
    u32 methodRef;
    const u8* instruction;
    u32 newPc;
    CHANSVmFunction funcPtr;
    CHANSVmNativeClass* target;
    u32 pushEnd, headerCount;
    CHANSVmObjHdr localBuf;
    u32 pushDepth;

    acc = &pVm->accumulator;
    funcPtr = vmNull;
    target = vmNull;
    pushEnd = 0;
    headerCount = 0;

    switch (acc->type) {
        case CHANS_VM_TYPE_ARRAY: {
            target = pVm->pArrayCls;
            if (target == 0) {
                return CHANS_VM_ERR_INVALID_OBJECT;
            }
            break;
        }
        case CHANS_VM_TYPE_CLASS_REF:
        case CHANS_VM_TYPE_OBJECT: {
            target = acc->parentCls;
            if (target == vmNull) {
                return CHANS_VM_ERR_INVALID_OBJECT;
            }
            break;
        }
        case CHANS_VM_TYPE_METHOD_REF: {
            CHANSVmExecutionCtx* ec = pVm->pActiveCtx;
            CHANSVmModule* dbg = ec->pDbg;
            u32 idx = (u32)acc->value.int32_v;

            if (idx >= dbg->nameCount) {
                return CHANS_VM_ERR_INVALID_OBJECT;
            }
            pushEnd = dbg->pNameTbl[idx].pushCount;
            headerCount = dbg->pNameTbl[idx].headerCount;
            break;
        }
        case CHANS_VM_OBJ_TYPE_STRING: {
            target = pVm->pStringCls;
            if (target == vmNull) {
                return CHANS_VM_ERR_INVALID_OBJECT;
            }
            break;
        }
        default: {
        error_check:
            if (callType == CHANS_VM_CALL_TYPE_FUNCTION) {
                return CHANS_VM_ERR_NO_SUCH_FUNCTION;
            }
            return callType == CHANS_VM_CALL_TYPE_METHOD ? CHANS_VM_ERR_NO_SUCH_METHOD : CHANS_VM_ERR_NO_SUCH_PROPERTY;
            break;
        }
    }

    {
        CHANSVmExecutionCtx* ctx = pVm->pActiveCtx;
        u32 pc = ctx->pc;
        CHANSVmModule* module = ctx->pDbg;

        newPc = pc + instructionSize;
        instruction = module->pData + pc;

        if (newPc < pc || newPc > module->codeSize) {
            return CHANS_VM_ERR_CODE_RANGE;
        }
        if (target == 0) {
            ctx->pc = newPc;
        }
    }

    memset(&localBuf, 0, sizeof(CHANSVmObjHdr));

    if (callType == CHANS_VM_CALL_TYPE_FUNCTION) {
        methodRef = 0;
    } else {
        CHANSVmExecutionCtx* ec = pVm->pActiveCtx;
        u32 methodId = VM_READ_BE_U16(instruction, 1);
        u32 methodCount;

        if (ec->pDbg->pMethodTbl == vmNull) {
            goto error_check;
        }

        methodCount = ec->pDbg->methodCount;
        if (methodId >= methodCount || methodId != 0 && target == 0) {
            goto error_check;
        }

        methodRef = methodId;
        if (methodId != 0) {
            methodRef = ec->pDbg->pMethodTbl[methodId];
        }
    }

    // If callType == PROP_GET or PROP_SET
    if (callType - CHANS_VM_CALL_TYPE_PROP_GET <= 1) {
        CHANSVmNativeProperty* entry;
        u32 isSet = callType == CHANS_VM_CALL_TYPE_PROP_SET;
        u32 isMethodNull;
        entry = target->pNativeProperties;
        pushDepth = isSet;
        isMethodNull = methodRef == 0;

        while (vmTrue) {
            if (isMethodNull != 0 || entry == 0) {
                return CHANS_VM_ERR_NO_SUCH_PROPERTY;
            }
            if (methodRef == entry->index) {
                if (acc->type == CHANS_VM_TYPE_CLASS_REF) {
                    if (entry->flag == 0) {
                        return CHANS_VM_ERR_FORBIDDEN_CLASS_PROPERTY;
                    }
                }
                if (callType == CHANS_VM_CALL_TYPE_PROP_GET) {
                    funcPtr = entry->getter;
                    if (funcPtr == vmNull) {
                        return CHANS_VM_ERR_NOT_READABLE_PROPERTY;
                    }
                } else {
                    funcPtr = entry->setter;
                    if (funcPtr == vmNull) {
                        return CHANS_VM_ERR_NOT_WRITABLE_PROPERTY;
                    }
                }
                break;
            }
            entry = entry->pNext;
        }
    } else {
        pushDepth = instruction[instructionSize - 1];
        if (methodRef != 0) {
            CHANSVmNativeMethod* node = target->pNativeMethods;

            while (vmTrue) {
                if (node == vmNull) {
                    return CHANS_VM_ERR_NO_SUCH_METHOD;
                }
                if (methodRef == node->index) {
                    if (acc->type == CHANS_VM_TYPE_CLASS_REF && node->hasStar == vmFalse) {
                        return CHANS_VM_ERR_FORBIDDEN_CLASS_METHOD;
                    }
                    funcPtr = node->func;
                    break;
                }
                node = node->pNext;
            }
        } else if (target != vmNull) {
            if (acc->type != CHANS_VM_TYPE_CLASS_REF) {
                if (callType == CHANS_VM_CALL_TYPE_METHOD) {
                    return CHANS_VM_ERR_NO_SUCH_METHOD;
                }
                return CHANS_VM_ERR_NO_SUCH_FUNCTION;
            }
            if (ctorFlag != vmFalse) {
                localBuf.parentCls = target;
                localBuf.type = CHANS_VM_TYPE_OBJECT;
                funcPtr = target->ctor;
                if (funcPtr == vmNull) {
                    return CHANS_VM_ERR_NOT_CONSTRUCTOR;
                }
            } else {
                funcPtr = target->init;
                if (funcPtr == vmNull) {
                    return CHANS_VM_ERR_NEED_NEW;
                }
            }
        }
    }

    retVal = VmPushFuncReturnInfo(vm, pushDepth, target != vmNull ? pushDepth : pushEnd, headerCount);
    if (retVal == CHANS_VM_OK) {
        if (target != vmNull) {
            if (funcPtr != vmNull && funcPtr(vm, acc, &localBuf) == CHANS_VM_OK) {
                retVal = CHANS_VM_ERR_IN_METHOD_OR_PROPERTY;
                if (ctorFlag != vmFalse) {
                    retVal = CHANS_VM_ERR_NEW;
                }
            } else {
                retVal = VmReturnWithValue(vm, callType == CHANS_VM_CALL_TYPE_PROP_SET ? 1 : 0);
                if (retVal == CHANS_VM_OK && callType != CHANS_VM_CALL_TYPE_PROP_SET) {
                    retVal = CHANSVmDeleteObject(vm, acc);
                    if (retVal == CHANS_VM_OK) {
                        memcpy(acc, &localBuf, sizeof(CHANSVmObjHdr));
                        acc->flags.raw &= ~CHANSVM_OBJ_FLAG_READONLY;
                        memset(&localBuf, 0, sizeof(CHANSVmObjHdr));
                    }
                }
            }

            if (retVal == CHANS_VM_OK) {
                pVm->pActiveCtx->pc = newPc;
            }
        } else {
            u32 codeAddr = pVm->pActiveCtx->pDbg->pNameTbl[(u32)acc->value.int32_v].codeAddr;

            if (codeAddr < 1 || codeAddr >= pVm->pActiveCtx->pDbg->codeSize) {
                return CHANS_VM_ERR_CODE_RANGE;
            }

            pVm->pActiveCtx->pc = codeAddr;
            retVal = CHANSVmDeleteObject(vm, acc);
        }
    }

return_label:
    return retVal;
}

void CHANSVmSetSignal(CHANSVm* vm, vmBool* signal) {
    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;

    pVm->bpSignalPending = signal;
    pVm->bSignalUpdated = vmTrue;
}

CHANSVmErr CHANSVmStep(CHANSVm* vm, int stepCount) {
    CHANSVmObjHdr* stackPtr;
    CHANSVmPrivate* pVm;
    s32 cmpHigh;
    u32 cmpLow;
    struct {
        CHANSVmObjType operandTypes[2];
        double floatLiteral;
        CHANSVmObjHdr copies[2];
        CHANSVmObjHdr load;
        CHANSVmObjHdr operand;
    } scratch;
    const VmResultTypeData* resultTypes = &VmResultTypeTbl;

    pVm = (CHANSVmPrivate*)vm;

    stepCount += (stepCount == 0);
    memset(&scratch.operand, 0, sizeof(scratch.operand));
    stackPtr = scratch.copies;
    cmpHigh = 0;
    cmpLow = -2;

    do {
        s32 opSize;
        u32 opcodeVal;
        u8* operandBuf;
        u32 arrayIdx;
        u32 imm16Val;
        u32 computedAddr;
        CHANSVmObjHdr* copyResult;
        CHANSVmObjHdr* foundObj;
        CHANSVmErr result;
        u32 newPos;
        u32 isTypeMatch;
        vmBoolInt shouldBranch;

        if (pVm->bSignalUpdated != vmFalse && pVm->bSignalBlocked == vmFalse) {
            pVm->bSignalUpdated = vmFalse;
            return CHANS_VM_ERR_SIGNAL;
        }

        if (pVm->pActiveCtx == vmNull || pVm->pActiveCtx->pDbg == vmNull || pVm->pActiveCtx->pc < 1 ||
            pVm->pActiveCtx->pc >= pVm->pActiveCtx->pDbg->codeSize) {
            return CHANS_VM_ERR_CODE_RANGE;
        }

        if (pVm->pFreeExeBuf < pVm->pHeapStart || pVm->pHeapEnd < pVm->pObjStackTopBuf) {
            return CHANS_VM_ERR_HEAP_RANGE;
        }

        opcodeVal = pVm->pActiveCtx->pDbg->pData[pVm->pActiveCtx->pc];
        if (pVm->bSuspendStep != vmFalse) {
            opcodeVal = 0;
        }

        if (VM_OPCLASS(opcodeVal) == VM_OPCLASS_BASE) {
            u32 convTypeIdx;
            CHANSVmObjHdr* leftOp;
            u32 opKind;
            CHANSVmObjHdr* rightOp;
            CHANSVmOpFunction opFunc;
            u32 leftTypeByte;
            u32 rightTypeByte;
            u32 typeIdx;
            CHANSVmObjType* enumedType;
            opSize = 1;
            switch (opcodeVal) {
                case CHANS_VM_OP_LOAD_IMM_1: {
                    result = 1;
                    goto shared_load_imm;
                }
                case CHANS_VM_OP_LOAD_IMM_2: {
                    result = 2;
                    goto shared_load_imm;
                }
                case CHANS_VM_OP_LOAD_IMM_4: {
                    result = 4;
                    goto shared_load_imm;
                }
                case CHANS_VM_OP_LOAD_IMM_8: {
                    result = 8;
                }
                shared_load_imm:
                    opSize = result + 1;
                    operandBuf = VmGetOperand(vm, 1, opSize);
                    result = VmLoadImmInteger(vm, &pVm->accumulator, operandBuf, result);
                    break;

                case CHANS_VM_OP_LOAD_FLOAT: {
                    opSize = 9;
                    operandBuf = VmGetOperand(vm, 1, 9);
                    memcpy(&scratch.floatLiteral, operandBuf, 8);
                    result = CHANSVmSetFloat(vm, &pVm->accumulator, scratch.floatLiteral);
                    break;
                }

                case CHANS_VM_OP_ADD_IMM: {
                    opKind = VM_OPKIND_ADD;
                    opFunc = VmAdd;
                    goto binary_imm;
                }
                case CHANS_VM_OP_SUB_IMM: {
                    opKind = VM_OPKIND_SUB;
                    opFunc = VmSub;
                    goto binary_imm;
                }
                case CHANS_VM_OP_MUL_IMM: {
                    opKind = VM_OPKIND_MUL;
                    opFunc = VmMul;
                    goto binary_imm;
                }
                case CHANS_VM_OP_DIV_IMM: {
                    opKind = VM_OPKIND_DIV;
                    opFunc = VmDiv;
                    goto binary_imm;
                }
                case CHANS_VM_OP_MOD_IMM: {
                    opKind = VM_OPKIND_MOD;
                    opFunc = VmMod;
                    goto binary_imm;
                }
                case CHANS_VM_OP_AND_IMM: {
                    opKind = VM_OPKIND_BIT;
                    opFunc = VmBitAnd;
                    goto binary_imm;
                }
                case CHANS_VM_OP_OR_IMM: {
                    opKind = VM_OPKIND_BIT;
                    opFunc = VmBitOr;
                    goto binary_imm;
                }
                case CHANS_VM_OP_XOR_IMM: {
                    opKind = VM_OPKIND_BIT;
                    opFunc = VmBitXor;
                    goto binary_imm;
                }
                case CHANS_VM_OP_CMP_EQ_IMM: {
                    opKind = VM_OPKIND_EQ;
                    opFunc = VmCmpEq;
                    goto binary_imm;
                }
                case CHANS_VM_OP_CMP_NEQ_IMM: {
                    opKind = VM_OPKIND_EQ;
                    opFunc = VmCmpNeq;
                    goto binary_imm;
                }
                case CHANS_VM_OP_CMP_LT_IMM: {
                    opKind = VM_OPKIND_CMP;
                    opFunc = VmCmpLt;
                    goto binary_imm;
                }
                case CHANS_VM_OP_CMP_GT_IMM: {
                    opKind = VM_OPKIND_CMP;
                    opFunc = VmCmpGt;
                    goto binary_imm;
                }
                case CHANS_VM_OP_CMP_LEQ_IMM: {
                    opKind = VM_OPKIND_CMP;
                    opFunc = VmCmpLeq;
                    goto binary_imm;
                }
                case CHANS_VM_OP_CMP_GEQ_IMM: {
                    opKind = VM_OPKIND_CMP;
                    opFunc = VmCmpGeq;
                }

                binary_imm:
                    leftOp = &pVm->accumulator;
                    rightOp = &scratch.operand;
                    opSize = 2;
                    operandBuf = VmGetOperand(vm, 1, 2);
                    result = VmLoadImmInteger(vm, &scratch.operand, operandBuf, 1);
                binary_typecheck:
                    if (result != CHANS_VM_OK) {
                        break;
                    }

                    rightTypeByte = rightOp->type;
                    typeIdx = 0;
                    leftTypeByte = leftOp->type;
                    enumedType = scratch.operandTypes;
                    for (; typeIdx < 2; typeIdx++, enumedType++) {
                        if (CHANSVmGetEnumedType(enumedType, (s32)(typeIdx == 0 ? leftTypeByte : rightTypeByte)) ==
                            0) {
                            goto error_setter;
                        }
                    }

                    {
                        const u8* convTbl;
                        switch (opKind) {
                            case VM_OPKIND_ADD: {
                                convTbl = (const u8*)resultTypes->add;
                                break;
                            }
                            case VM_OPKIND_MOD:
                            case VM_OPKIND_MUL:
                            case VM_OPKIND_SUB:
                            case VM_OPKIND_DIV: {
                                convTbl = (const u8*)resultTypes->arith;
                                break;
                            }
                            case VM_OPKIND_CMP: {
                                convTbl = (const u8*)resultTypes->cmp;
                                break;
                            }
                            case VM_OPKIND_EQ: {
                                convTbl = (const u8*)resultTypes->eq;
                                break;
                            }
                            case VM_OPKIND_BIT:
                            case VM_OPKIND_SHIFT: {
                                convTbl = (const u8*)resultTypes->bitShift;
                                break;
                            }
                            default: {
                                // TODO: This is an inlined function called "VmGetResultType"
                                CHANS_VM_PRINTF_CUSTOM("%s: no table for op '%c'\n", scVmGetResultType, opKind);
                                goto error_setter;
                            }
                        }

                        result = CHANS_VM_OK;
                        convTypeIdx = convTbl[scratch.operandTypes[0] * 6 + scratch.operandTypes[1]];
                        goto result_check;
                    }

                error_setter:
                    result = CHANS_VM_ERR_RESULT_TYPE;

                result_check:
                    if (result != CHANS_VM_OK) {
                        break;
                    }

                    if ((opKind != VM_OPKIND_CMP && opKind != VM_OPKIND_EQ) || convTypeIdx != 0) {
                        leftOp = CHANSVmConvertObjectType(vm, convTypeIdx, leftOp);
                        rightOp = CHANSVmConvertObjectType(vm, convTypeIdx, rightOp);
                    }

                    if (leftOp == vmNull || rightOp == vmNull) {
                        return CHANS_VM_ERR_RESULT_TYPE;
                    }

                    result = opFunc(vm, convTypeIdx, &pVm->accumulator, leftOp, rightOp);

                    if (result == CHANS_VM_OK) {
                        result = CHANSVmDeleteObject(vm, &scratch.operand);
                        if (result == CHANS_VM_OK && leftOp != &pVm->accumulator && leftOp != &scratch.operand && (leftOp->flags.raw & CHANSVM_OBJ_FLAG_READONLY) == 0 &&
                            (result = CHANSVmDeleteObject(vm, leftOp), result == CHANS_VM_OK)) {
                            // TODO: find the correct sizeof(...) expression
                            CHANSVmFree(vm, leftOp, 0x20);
                        }
                        if (result == CHANS_VM_OK && rightOp != &pVm->accumulator && rightOp != &scratch.operand && (rightOp->flags.raw & CHANSVM_OBJ_FLAG_READONLY) == 0 &&
                            (result = CHANSVmDeleteObject(vm, rightOp), result == CHANS_VM_OK)) {
                            // TODO: find the correct sizeof(...) expression
                            CHANSVmFree(vm, rightOp, 0x20);
                        }
                    }

                    break;

                case CHANS_VM_OP_PUSH: {
                    CHANSVmObjHdr* resultObj;
                    resultObj = vmNull;
                    // This comparison is odd... it does improve the match though
                    if (pVm->pActiveCtx->stackDepth < (u32)-1) {
                        CHANSVmObjHdr* hdr = CHANSVmNewObjHdr(vm, vmTrue);
                        if (hdr != vmNull) {
                            resultObj = CHANSVmCopyObject(vm, hdr, &pVm->accumulator);
                            if (resultObj != vmNull) {
                                pVm->pActiveCtx->stackDepth++;
                            }
                        }
                    }
                    if (resultObj == vmNull) {
                        result = CHANS_VM_ERR_NO_MEMORY;
                    } else {
                        result = CHANS_VM_OK;
                    }
                    break;
                }

                case CHANS_VM_OP_POP: {
                    result = CHANSVmPopObject(vm, &pVm->accumulator);
                    break;
                }

                case CHANS_VM_OP_ADD: {
                    opKind = VM_OPKIND_ADD;
                    opFunc = VmAdd;
                    goto binary_pop;
                }
                case CHANS_VM_OP_SUB: {
                    opKind = VM_OPKIND_SUB;
                    opFunc = VmSub;
                    goto binary_pop;
                }
                case CHANS_VM_OP_MUL: {
                    opKind = VM_OPKIND_MUL;
                    opFunc = VmMul;
                    goto binary_pop;
                }
                case CHANS_VM_OP_DIV: {
                    opKind = VM_OPKIND_DIV;
                    opFunc = VmDiv;
                    goto binary_pop;
                }
                case CHANS_VM_OP_MOD: {
                    opKind = VM_OPKIND_MOD;
                    opFunc = VmMod;
                    goto binary_pop;
                }
                case CHANS_VM_OP_BIT_AND: {
                    opKind = VM_OPKIND_BIT;
                    opFunc = VmBitAnd;
                    goto binary_pop;
                }
                case CHANS_VM_OP_BIT_OR: {
                    opKind = VM_OPKIND_BIT;
                    opFunc = VmBitOr;
                    goto binary_pop;
                }
                case CHANS_VM_OP_BIT_XOR: {
                    opKind = VM_OPKIND_BIT;
                    opFunc = VmBitXor;
                    goto binary_pop;
                }
                case CHANS_VM_OP_ULSHIFT: {
                    opKind = VM_OPKIND_SHIFT;
                    opFunc = VmULShift;
                    goto binary_pop;
                }
                case CHANS_VM_OP_ARSHIFT: {
                    opKind = VM_OPKIND_SHIFT;
                    opFunc = VmARShift;
                    goto binary_pop;
                }
                case CHANS_VM_OP_CMP_EQ: {
                    opKind = VM_OPKIND_CMP;
                    opFunc = VmCmpEq;
                    goto binary_pop;
                }
                case CHANS_VM_OP_CMP_NEQ: {
                    opKind = VM_OPKIND_CMP;
                    opFunc = VmCmpNeq;
                    goto binary_pop;
                }
                case CHANS_VM_OP_CMP_LT: {
                    opKind = VM_OPKIND_CMP;
                    opFunc = VmCmpLt;
                    goto binary_pop;
                }
                case CHANS_VM_OP_CMP_GT: {
                    opKind = VM_OPKIND_CMP;
                    opFunc = VmCmpGt;
                    goto binary_pop;
                }
                case CHANS_VM_OP_CMP_LEQ: {
                    opKind = VM_OPKIND_CMP;
                    opFunc = VmCmpLeq;
                    goto binary_pop;
                }
                case CHANS_VM_OP_CMP_GEQ: {
                    opKind = VM_OPKIND_CMP;
                    opFunc = VmCmpGeq;
                }

                binary_pop:
                    leftOp = &scratch.operand;
                    rightOp = &pVm->accumulator;
                    result = CHANSVmPopObject(vm, &scratch.operand);
                    if (result != CHANS_VM_OK) {
                        break;
                    }
                    goto binary_typecheck;

                case CHANS_VM_OP_RETURN: {
                    result = CHANSVmDeleteObject(vm, &pVm->accumulator);
                    if (result == CHANS_VM_OK) {
                        result = VmReturnWithValue(vm, 0);
                    }
                    opSize = 0;
                    break;
                }

                case CHANS_VM_OP_RETURN_VALUE: {
                    result = VmReturnWithValue(vm, 0);
                    opSize = 0;
                    break;
                }

                case CHANS_VM_OP_BIT_NOT: {
                    CHANSVmObjHdr* pAcc = &pVm->accumulator;
                    u64 invertedVal;
                    switch (pAcc->type) {
                        case CHANS_VM_OBJ_TYPE_INTEGER: {
                            invertedVal = pAcc->value.int_v;
                            break;
                        }
                        case CHANS_VM_OBJ_TYPE_FLOAT: {
                            invertedVal = (s64)(CHANSVmFloatSign(pAcc->value.float_v) * floor(fabs(pAcc->value.float_v)));
                            break;
                        }
                        case CHANS_VM_OBJ_TYPE_STRING: {
                            s32 parseOk = CHANSVmParseInt(pAcc, 0, &invertedVal);
                            if (parseOk == 0) {
                                invertedVal = 0;
                            }
                            break;
                        }
                        case CHANS_VM_OBJ_TYPE_BLANK:
                        default: {
                            invertedVal = 0;
                            break;
                        }
                    }
                    result = CHANSVmSetInteger(vm, pAcc, (vmInteger)~invertedVal);
                    break;
                }

                case CHANS_VM_OP_LOG_NOT: {
                    CHANSVmObjHdr* pAcc = &pVm->accumulator;
                    vmBoolInt bResult;
                    CHANSVmErr booleanResult = CHANSVmGetBoolean(&bResult, pAcc);
                    if (booleanResult == CHANS_VM_OK) {
                        s32 boolVal = bResult ? 0 : 1;
                        booleanResult = CHANSVmSetInteger(vm, pAcc, boolVal);
                    }
                    result = booleanResult;
                    break;
                }

                case CHANS_VM_OP_LOAD_INDIRECT: {
                    CHANSVmObjHdr* pAcc = &pVm->accumulator;
                    result = CHANS_VM_ERR_LOAD_INDIRECT;
                    if (pAcc->type == CHANS_VM_TYPE_INDEX_REF) {
                        copyResult = CHANSVmCopyObject(vm, &scratch.load, pAcc);
                        if (copyResult != vmNull) {
                            foundObj = VmGetArrayElement(vm, &scratch.load, scratch.load.value.data.len, vmFalse);
                            result = VmStore(vm, pAcc, foundObj);
                            if (result == CHANS_VM_OK) {
                                result = CHANSVmDeleteObject(vm, &scratch.load);
                            }
                        }
                    }
                    break;
                }

                case CHANS_VM_OP_CALL_METHOD: {
                    operandBuf = VmGetOperand(vm, 1, 4);
                    if (operandBuf == vmNull) {
                        return CHANS_VM_ERR_CODE_RANGE;
                    }
                    result = VmCallMethod(vm, 4, CHANS_VM_CALL_TYPE_METHOD, vmFalse);
                    opSize = 0;
                    break;
                }

                case CHANS_VM_OP_IS_CLASS: {
                    if (pVm->accumulator.type == CHANS_VM_TYPE_CLASS_REF) {
                        result = 1;
                        goto call_function_common;
                    } else {
                        result = CHANS_VM_ERR_INVALID_OBJECT_TYPE;
                        break;
                    }
                }
                case CHANS_VM_OP_CALL_FUNCTION: {
                    result = CHANS_VM_OK;
                call_function_common:
                    operandBuf = VmGetOperand(vm, 1, 2);
                    if (operandBuf == vmNull) {
                        return CHANS_VM_ERR_CODE_RANGE;
                    }
                    result = VmCallMethod(vm, 2, CHANS_VM_CALL_TYPE_FUNCTION, result);
                    opSize = 0;
                    break;
                }

                case CHANS_VM_OP_PROP_GET:
                case CHANS_VM_OP_PROP_SET: {
                    u32 callMode;
                    operandBuf = VmGetOperand(vm, 1, 3);
                    if (operandBuf == vmNull) {
                        return CHANS_VM_ERR_CODE_RANGE;
                    }
                    callMode = opcodeVal == CHANS_VM_OP_PROP_GET ? CHANS_VM_CALL_TYPE_PROP_GET : CHANS_VM_CALL_TYPE_PROP_SET;
                    result = VmCallMethod(vm, 3, callMode, vmFalse);
                    opSize = 0;
                    break;
                }

                case CHANS_VM_OP_STORE_INDIRECT: {
                    CHANSVmObjHdr* pAcc = &pVm->accumulator;
                    result = CHANS_VM_ERR_STORE_INDIRECT;
                    if (pAcc->type == CHANS_VM_TYPE_INDEX_REF) {
                        copyResult = CHANSVmCopyObject(vm, stackPtr + 1, pAcc);
                        if (copyResult != 0) {
                            result = CHANSVmPopObject(vm, pAcc);
                            if (result == CHANS_VM_OK) {
                                foundObj = VmGetArrayElement(vm, stackPtr + 1, (stackPtr + 1)->value.data.len, vmTrue);
                                result = VmStore(vm, foundObj, pAcc);
                                if (result == CHANS_VM_OK) {
                                    result = CHANSVmDeleteObject(vm, stackPtr + 1);
                                }
                            }
                        }
                    }
                    break;
                }

                case CHANS_VM_OP_LOAD_STRING_CONST: {
                    CHANSVmObjHdr* pAcc;
                    CHANSVmExecutionCtx* ctx;
                    CHANSVmModule* dbg;
                    CHANSVmErr loadResult;
                    opSize = 3;
                    operandBuf = VmGetOperand(vm, 1, 3);
                    if (operandBuf == vmNull) {
                        return CHANS_VM_ERR_CODE_RANGE;
                    }
                    pAcc = &pVm->accumulator;
                    loadResult = CHANSVmDeleteObject(vm, pAcc);
                    if (loadResult == CHANS_VM_OK) {
                        imm16Val = VM_READ_BE_U16(operandBuf, 0);
                        ctx = pVm->pActiveCtx;
                        dbg = ctx->pDbg;
                        if (imm16Val >= dbg->stringCount || dbg->pStringTbl[imm16Val].pStringData == vmNull) {
                            loadResult = CHANS_VM_ERR_LOAD_STRING_CONST;
                        } else {
                            pAcc->type = CHANS_VM_OBJ_TYPE_STRING;
                            pAcc->hasData = vmTrue;
                            pAcc->value.wstring_v = (vmWStringObjVal*)&ctx->pDbg->pStringTbl[imm16Val];
                        }
                    }
                    result = loadResult;
                    break;
                }

                case CHANS_VM_OP_SET_INDEX: {
                    CHANSVmObjHdr* accumulator = &pVm->accumulator;
                    u64 cmpVal;
                    s64 fullVal;
                    u64 parsedIndex;
                    result = CHANS_VM_ERR_SET_INDEX;
                    copyResult = CHANSVmCopyObject(vm, stackPtr, accumulator);
                    if (copyResult == 0) {
                        goto set_index_ok;
                    }
                    result = CHANSVmPopObject(vm, accumulator);
                    if (result != CHANS_VM_OK) {
                        goto set_index_ok;
                    }

                    if (accumulator->type == CHANS_VM_TYPE_ARRAY) {
                        int typeByte = stackPtr->type;
                        switch (typeByte) {
                            case CHANS_VM_OBJ_TYPE_INTEGER:
                                cmpHigh = 0;
                                cmpLow = -2;
                                cmpVal = VM_MAKE_U64(cmpHigh, cmpLow);
                                fullVal = stackPtr->value.int_v;
                                if ((u64)fullVal > cmpVal) {
                                    goto set_index_error;
                                }
                                arrayIdx = (u32)stackPtr->value.int_v;
                                goto set_index_ok;
                            case CHANS_VM_OBJ_TYPE_FLOAT: {
                                double stackFloat = stackPtr->value.float_v;
                                if (stackFloat >= 0.0 && stackFloat <= 4294967294.0) {
                                    arrayIdx = (u32)stackFloat;
                                    goto set_index_ok;
                                }
                                goto set_index_error;
                            }
                            case CHANS_VM_OBJ_TYPE_STRING:
                                if (CHANSVmParseInt(stackPtr, 10, &parsedIndex)) {
                                    cmpHigh = 0;
                                    cmpLow = -2;
                                    cmpVal = VM_MAKE_U64(cmpHigh, cmpLow);
                                    if (parsedIndex <= cmpVal) {
                                        arrayIdx = (u32)parsedIndex;
                                        goto set_index_ok;
                                    }
                                }
                                goto set_index_error;
                        }
                    }
                set_index_error:
                    result = CHANS_VM_ERR_SET_INDEX;

                set_index_ok:
                    if (result != CHANS_VM_OK) {
                        break;
                    }
                    accumulator->value.data.len = arrayIdx;
                    accumulator->type = CHANS_VM_TYPE_INDEX_REF;
                    result = CHANSVmDeleteObject(vm, stackPtr);
                    break;
                }

                case CHANS_VM_OP_GET_PROPERTY_NAME: {
                    u32 foundEntry;
                    CHANSVmObjHdr* accumulator;
                    opSize = 5;
                    operandBuf = VmGetOperand(vm, 1, 5);
                    if (operandBuf == vmNull) {
                        return CHANS_VM_ERR_CODE_RANGE;
                    }
                    result = CHANS_VM_ERR_GET_PROPERTY_NAME;
                    arrayIdx = 0;
                    imm16Val = VM_READ_BE_U16(operandBuf, 0);
                    foundObj = CHANSVmLookupScopedObject(vm, imm16Val);
                    accumulator = &pVm->accumulator;
                    if (foundObj != vmNull && accumulator->type == CHANS_VM_OBJ_TYPE_INTEGER &&
                        (computedAddr = accumulator->value.data.len, (u64)accumulator->value.int_v <= ~1U)) {
                        if ((s32)foundObj->type != CHANS_VM_TYPE_ARRAY) {
                            foundEntry = 0;
                        } else {
                            u32 idx;
                            u32 remaining;
                            u32 len = VmArrayGetLengthInternal(foundObj);
                            remaining = computedAddr;
                            idx = 0;
                            while (idx < len) {
                                copyResult = CHANSVmGetArrayElement(vm, foundObj, idx);
                                if (copyResult == vmNull) {
                                    break;
                                }
                                if (copyResult->type != CHANS_VM_OBJ_TYPE_BLANK) {
                                    if (remaining == 0) {
                                        computedAddr = idx;
                                        goto found_entry;
                                    } else {
                                        remaining--;
                                    }
                                }
                                idx++;
                            }
                            copyResult = vmNull;
                        found_entry:
                            if (copyResult != vmNull) {
                                foundEntry = 1;
                                if (CHANSVmDeleteObject(vm, accumulator) == CHANS_VM_OK) {
                                    CHANSVmObjHdr* hdr = CHANSVmNewObject(vm, vmFalse, accumulator, CHANS_VM_OBJ_TYPE_STRING, VM_STRING_SIZE);
                                    if (hdr != vmNull) {
                                        char* s = accumulator->value.string_v->spData;
                                        s32 snpLen = snprintf(s, 0x40, VmIntegerFormat, (u64)computedAddr);
                                        CHANSVmStrCpyToU16FromU8((wchar_t*)s, s, snpLen);
                                        accumulator->value.string_v->len = VM_STR_LENGTH(snpLen);
                                        if (accumulator->value.string_v->len == 0) {
                                            goto property_error;
                                        }
                                    } else {
                                        goto property_error;
                                    }
                                } else {
                                    goto property_error;
                                }
                            } else {
                                foundEntry = 0;
                            }
                        }
                        result = CHANS_VM_OK;
                        arrayIdx = 0;
                    }
                    goto property_done;
                property_error:
                    result = CHANS_VM_ERR_GET_PROPERTY_NAME;
                property_done:
                    if (result == CHANS_VM_OK && foundEntry == 0) {
                        u8* pOpData = operandBuf;
                        computedAddr = (VM_READ_BE_U16(pOpData, 2)) & CHANS_VM_OP_BRANCH_OFFSET_BIAS;
                        if ((VM_READ_BE_U16(pOpData, 2)) & CHANS_VM_OP_BRANCH_OFFSET_SIGN) {
                            computedAddr = computedAddr + pVm->pActiveCtx->pc - CHANS_VM_OP_BRANCH_OFFSET_BIAS_5;
                        } else {
                            computedAddr += pVm->pActiveCtx->pc + 5;
                        }
                        if (computedAddr < 1 || computedAddr >= pVm->pActiveCtx->pDbg->codeSize) {
                            return CHANS_VM_ERR_CODE_RANGE;
                        }
                        pVm->pActiveCtx->pc = computedAddr;
                        opSize = 0;
                    }
                    break;
                }

                case CHANS_VM_OP_NEW_ARRAY: {
                    CHANSVmObjHdr* accumulator;
                    CHANSVmErr arrayResult;
                    opSize = 3;
                    operandBuf = VmGetOperand(vm, 1, 3);
                    if (operandBuf == vmNull) {
                        return CHANS_VM_ERR_CODE_RANGE;
                    }
                    imm16Val = VM_READ_BE_U16(operandBuf, 0);
                    accumulator = &pVm->accumulator;
                    arrayResult = CHANSVmDeleteObject(vm, accumulator);
                    if (arrayResult == CHANS_VM_OK) {
                        arrayResult = VmPushFuncReturnInfo(vm, imm16Val, imm16Val, 0);
                        if (arrayResult == CHANS_VM_OK) {
                            accumulator->type = CHANS_VM_TYPE_ARRAY;
                            accumulator->parentCls = pVm->pArrayCls;
                            if (CHANSVmNewObjData(vm, accumulator, sizeof(ArrayChunk)) == vmNull ||
                                (imm16Val != 0 && VmArrayExpandCommon(vm, accumulator, imm16Val, 0, vmTrue) == 0)) {
                                arrayResult = CHANS_VM_ERR_CALL_NEW_ARRAY;
                            } else {
                                arrayResult = VmReturnWithValue(vm, 0);
                            }
                        }
                    }
                    result = arrayResult;
                    break;
                }

                case CHANS_VM_OP_JUMP: {
                    operandBuf = VmGetOperand(vm, 1, 4);
                    if (operandBuf == vmNull) {
                        return CHANS_VM_ERR_CODE_RANGE;
                    }
                    computedAddr = VM_READ_BE_U24(operandBuf, 0);
                    if (computedAddr & CHANS_VM_OP_JUMP_OFFSET_SIGN) {
                        computedAddr = computedAddr + pVm->pActiveCtx->pc - CHANS_VM_OP_JUMP_OFFSET_BIAS;
                    } else {
                        computedAddr += pVm->pActiveCtx->pc + 4;
                    }
                    if (computedAddr < 1 || computedAddr >= pVm->pActiveCtx->pDbg->codeSize) {
                        return CHANS_VM_ERR_CODE_RANGE;
                    }
                    pVm->pActiveCtx->pc = computedAddr;
                    opSize = 0;
                    result = CHANS_VM_OK;
                    break;
                }

                case CHANS_VM_OP_STORE_UNDEFINED: {
                    result = VmStore(vm, &pVm->accumulator, (CHANSVmObjHdr*)&CHANSVmConstStringObjectUndefined_[4]);
                    break;
                }

                case CHANS_VM_OP_DELETE_SYMBOL: {
                    opSize = 3;
                    operandBuf = VmGetOperand(vm, 1, 3);
                    if (operandBuf == vmNull) {
                        return CHANS_VM_ERR_CODE_RANGE;
                    }
                    foundObj = CHANSVmLookupScopedObject(vm, (VM_READ_BE_U16(operandBuf, 0)) & 0x1FFF);
                    result = VmDeleteCommon(vm, foundObj);
                    break;
                }

                case CHANS_VM_OP_DELETE_INDIRECT: {
                    CHANSVmObjHdr* accumulator = &pVm->accumulator;
                    CHANSVmErr deleteResult = CHANS_VM_ERR_DELETE_INDIRECT;
                    if (accumulator->type == CHANS_VM_TYPE_INDEX_REF) {
                        foundObj = VmGetArrayElement(vm, accumulator, accumulator->value.data.len, vmFalse);
                        deleteResult = VmDeleteCommon(vm, foundObj);
                    }
                    result = deleteResult;
                    break;
                }

                default: {
                    result = CHANS_VM_ERR_RESERVED_OPCODE;
                    break;
                }
            }
        } else if (VM_OPCLASS(opcodeVal) == VM_OPCLASS_SYMBOL) {
            opSize = 2;
            operandBuf = VmGetOperand(vm, 0, 2);
            if (operandBuf == vmNull) {
                return CHANS_VM_ERR_CODE_RANGE;
            }
            imm16Val = (opcodeVal << 8 | operandBuf[1]) & 0x1FFF;
            switch (opcodeVal & CHANS_VM_OP_SYMBOL_STORE) {
                case 0: {
                    foundObj = CHANSVmLookupScopedObject(vm, imm16Val);
                    result = VmStore(vm, &pVm->accumulator, foundObj);
                    break;
                }
                case CHANS_VM_OP_SYMBOL_STORE: {
                    foundObj = CHANSVmLookupScopedObject(vm, imm16Val);
                    result = VmStore(vm, foundObj, &pVm->accumulator);
                    break;
                }
                default: {
                    return 0x1162;
                    break;
                }
            }
        } else {  // VM_OPCLASS_BRANCH (0x80-0xFF)
            opSize = 2;
            operandBuf = VmGetOperand(vm, 0, 2);
            if (operandBuf == vmNull) {
                return CHANS_VM_ERR_CODE_RANGE;
            }
            switch ((int)opcodeVal & CHANS_VM_OP_BRANCH_COND_MASK) {
                case CHANS_VM_OP_BRANCH_CASE: {
                    result = CHANS_VM_ERR_CASE;
                    if (pVm->pActiveCtx->stackDepth != 0 && pVm->pObjStackTopBuf + sizeof(CHANSVmObjHdr) <= pVm->pHeapEnd) {
                        CHANSVmObjHdr* stackTop = (CHANSVmObjHdr*)pVm->pObjStackTopBuf;
                        isTypeMatch = 0;
                        if (stackTop->type == pVm->accumulator.type) {
                            switch (stackTop->type) {
                                case CHANS_VM_OBJ_TYPE_INTEGER: {
                                    isTypeMatch = stackTop->value.int_v == pVm->accumulator.value.int_v;
                                    goto end_branch_check;
                                }
                                case CHANS_VM_OBJ_TYPE_FLOAT: {
                                    isTypeMatch = stackTop->value.float_v == pVm->accumulator.value.float_v;
                                    goto end_branch_check;
                                }
                                case CHANS_VM_OBJ_TYPE_STRING: {
                                    u32 stackStringLen, accumulatorStringLen;
                                    const vmWStringObjVal* accumulatorString = pVm->accumulator.value.wstring_v;
                                    const vmWStringObjVal* stackString = stackTop->value.wstring_v;
                                    u32 strEqual;
                                    isTypeMatch = 0;
                                    stackStringLen = stackString->len;
                                    accumulatorStringLen = accumulatorString->len;
                                    if (stackStringLen == accumulatorStringLen) {
                                        strEqual = 0;
                                        if (stackStringLen == 0 || memcmp(stackString->spData, accumulatorString->spData, stackStringLen) == 0) {
                                            strEqual = 1;
                                        }
                                        if (strEqual) {
                                            isTypeMatch = 1;
                                        }
                                    }
                                    goto end_branch_check;
                                }
                                case CHANS_VM_OBJ_TYPE_BLANK: {
                                    isTypeMatch = 1;
                                    goto end_branch_check;
                                }
                                case CHANS_VM_TYPE_ARRAY:
                                case CHANS_VM_TYPE_CLASS_REF:
                                case CHANS_VM_TYPE_OBJECT:
                                case CHANS_VM_TYPE_METHOD_REF: {
                                    isTypeMatch = 0;
                                    if (stackTop->parentCls == pVm->accumulator.parentCls && stackTop->hasData == pVm->accumulator.hasData &&
                                        (stackTop->hasData == 0 || stackTop->value.data.ptr == pVm->accumulator.value.data.ptr)) {
                                        isTypeMatch = 1;
                                    }
                                    goto end_branch_check;
                                }
                                default: {
                                    result = CHANS_VM_ERR_CHECK_STRICT_EQUALITY;
                                    goto done_with_switch;
                                }
                            }
                        }
                    end_branch_check:
                        shouldBranch = isTypeMatch;
                        result = CHANS_VM_OK;
                    done_with_switch:
                        if (result == CHANS_VM_OK && shouldBranch != 0) {
                            result = CHANSVmPopObject(vm, vmNull);
                        }
                    }
                    break;
                }
                case CHANS_VM_OP_BRANCH_FALSE: {
                    result = CHANSVmGetBoolean(&shouldBranch, &pVm->accumulator);
                    if (result == CHANS_VM_OK) {
                        shouldBranch = !shouldBranch;
                    }
                    break;
                }
                case CHANS_VM_OP_BRANCH_TRUE: {
                    result = CHANSVmGetBoolean(&shouldBranch, &pVm->accumulator);
                    break;
                }
                case CHANS_VM_OP_BRANCH_ALWAYS: {
                    result = CHANS_VM_OK;
                    shouldBranch = 1;
                    break;
                }
                default: {
                    return 0x1182;
                }
            }

            if (result == CHANS_VM_OK && shouldBranch != 0) {
                computedAddr = (opcodeVal << 8 | operandBuf[1]) & CHANS_VM_OP_BRANCH_OFFSET_BIAS;
                if ((opcodeVal << 8 | operandBuf[1]) & CHANS_VM_OP_BRANCH_OFFSET_SIGN) {
                    computedAddr = computedAddr + pVm->pActiveCtx->pc - CHANS_VM_OP_BRANCH_OFFSET_BIAS;
                } else {
                    computedAddr += pVm->pActiveCtx->pc + 2;
                }
                if (computedAddr < 1 || computedAddr >= pVm->pActiveCtx->pDbg->codeSize) {
                    return CHANS_VM_ERR_CODE_RANGE;
                }
                pVm->pActiveCtx->pc = computedAddr;
                opSize = 0;
            }
        }

        if (result != CHANS_VM_OK) {
            return result;
        }
        if (opSize == -1) {
            return 0x11a0;
        }
        if (pVm->pActiveCtx == vmNull || pVm->pActiveCtx->pDbg == vmNull || (newPos = pVm->pActiveCtx->pc + opSize) >= pVm->pActiveCtx->pDbg->codeSize) {
            return CHANS_VM_ERR_CODE_RANGE;
        }
        pVm->pActiveCtx->pc = newPos;
    } while (stepCount-- != 1);

    return CHANS_VM_OK;
}
