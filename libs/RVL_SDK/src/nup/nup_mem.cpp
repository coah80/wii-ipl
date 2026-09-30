#include <revolution/mem.h>

namespace nup {
static MEMAllocator* __mem;

void* __nupMallocAlign(unsigned long size, unsigned long alignment) {
    if (__mem == NULL) {
        return NULL;
    }
    MEMHeapHandle heap = (MEMHeapHandle)__mem->heap;
    if (heap->magic != 0x45585048) {
        return NULL;
    }
    return MEMAllocFromExpHeapEx(heap, size, alignment);
}

void* __nupMalloc(unsigned long size) {
    if (__mem == NULL) {
        return NULL;
    }
    MEMHeapHandle heap = (MEMHeapHandle)__mem->heap;
    if (heap->magic != 0x45585048) {
        return NULL;
    }
    return MEMAllocFromExpHeapEx(heap, size, 32);
}

void __nupFree(void* block) {
    if (__mem != NULL) {
        MEMHeapHandle heap = (MEMHeapHandle)__mem->heap;
        if (heap->magic == 0x45585048 && block != NULL) {
            MEMFreeToExpHeap(heap, block);
        }
    }
}

int __nupRegisterAllocator(MEMAllocator* allocator) {
    int result = 0;
    if (allocator == NULL) {
        result = -5011;
    } else {
        if (((MEMHeapHandle)allocator->heap)->magic != 0x45585048) {
            result = -5011;
        }
        if (((MEMHeapHandle)allocator->heap)->magic == 0x45585048) {
            __mem = allocator;
        }
    }
    return result;
}
}
