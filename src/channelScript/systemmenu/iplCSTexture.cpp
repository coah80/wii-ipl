#include "channelScript/iplCSLibrary.h"

#include "iplSystem.h"

#include <revolution/gx/GXTexture.h>
#include <utility/iplTPLValidity.h>

extern "C" BOOL CHANSVmCheckNativeInstance(CHANSVmObjHdr* obj, const char* className);

namespace ipl {
    namespace cs {
        namespace texture {
            BOOL is_valid_fmt(const CHANSVmObjHdr* obj) {
                BOOL result = FALSE;
                if (obj != NULL) {
                    BOOL found;
                    u64 formatValue = (u64)obj->value.int_v;
                    u32 formatIndex = (u32)formatValue;

                    found = FALSE;
                    // Cleaning this part breaks the match...
                    if (!(formatValue > 14)) {
                        if (1 << formatIndex & 0x407F) {
                            found = TRUE;
                        }
                    }
                    if (found) {
                        result = TRUE;
                    }
                }
                return result;
            }

            BOOL is_valid_wrap(const CHANSVmObjHdr* obj) {
                BOOL result = FALSE;
                if (obj != NULL && obj->value.int_v <= 2ULL) {
                    result = TRUE;
                }
                return result;
            }

            BOOL init_tpl(CHANSVm* vm, CHANSVmObjHdr* returnObj) {
                BOOL result = FALSE;

                CHANSVmObjHdr* paletteArg = CHANSVmGetArgInteger(vm, 0);
                CHANSVmObjHdr* tplSizeArg = CHANSVmGetArgInteger(vm, 1);
                u32 palette = paletteArg != NULL ? paletteArg->value.int_v : 0;
                u32 tplSize = tplSizeArg != NULL ? tplSizeArg->value.int_v : 0;

                utility::tpl_validity tpl(reinterpret_cast<TPLPalette*>(palette), tplSize);

                channel::ChannelScriptManager* mgr = System::getCSManager();
                if (mgr->isValidAddr((void*)palette) && (palette & 0x1F) == 0 && tpl.is_valid()) {
                    // TODO:
                    u32* data = static_cast<u32*>(CHANSVmNewObjData(vm, returnObj, 0x24));
                    if (data != NULL) {
                        result = TRUE;
                        data[0] = 0;
                        data[1] = palette;
                    }
                }

                return result;
            }

            BOOL init_texobj(CHANSVm* vm, CHANSVmObjHdr* returnObj, u32 addr) {
                BOOL result = FALSE;

                CHANSVmObjHdr* widthArg = CHANSVmGetArgInteger(vm, 1);
                CHANSVmObjHdr* heightArg = CHANSVmGetArgInteger(vm, 2);
                CHANSVmObjHdr* formatArg = CHANSVmGetArgInteger(vm, 3);
                CHANSVmObjHdr* wrapSArg = CHANSVmGetArgInteger(vm, 4);
                CHANSVmObjHdr* wrapTArg = CHANSVmGetArgInteger(vm, 5);

                if (System::getCSManager()->isValidAddr((void*)addr) && (addr & 0x1F) == 0) {
                    // TODO: This was an inlined function but I wasn't able to get it to match after extracting it
                    BOOL widthValid = FALSE;
                    if (widthArg != NULL) {
                        BOOL isValid = FALSE;
                        u64 widthValue = (u64)widthArg->value.int_v;
                        if (widthValue != 0 && widthValue < 0x400) {
                            isValid = TRUE;
                        }
                        if (isValid) {
                            widthValid = TRUE;
                        }
                    }
                    if (widthValid) {
                        BOOL heightValid = FALSE;
                        if (heightArg != NULL) {
                            BOOL isValid = FALSE;
                            u64 heightValue = (u64)heightArg->value.int_v;
                            if (heightValue != 0 && heightValue < 0x400) {
                                isValid = TRUE;
                            }
                            if (isValid) {
                                heightValid = TRUE;
                            }
                        }
                        if (heightValid && is_valid_fmt(formatArg) && is_valid_wrap(wrapSArg) && is_valid_wrap(wrapTArg)) {
                            u32* data = static_cast<u32*>(CHANSVmNewObjData(vm, returnObj, sizeof(GXTexObj) + sizeof(u32)));

                            if (data != NULL) {
                                // What is this value?
                                data[0] = 1;
                                u16 width = (u16)widthArg->value.int_v;
                                u16 height = (u16)heightArg->value.int_v;
                                // Access the GXTexObj area in the newly allocated objdata with a 4byte offset. Using struct member access does not match
                                GXInitTexObj((GXTexObj*)(data + 1), (void*)addr, width, height, (GXTexFmt)formatArg->value.int_v,
                                             (GXTexWrapMode)wrapSArg->value.int_v, (GXTexWrapMode)wrapTArg->value.int_v, GX_FALSE);
                                result = TRUE;
                            }
                        }
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(ctor) {
                BOOL result = FALSE;

                u32 argc = CHANSVmGetArgc(VmInst);
                if (argc == 2) {
                    result = init_tpl(VmInst, VmReturnObj);
                } else if (argc == 6) {
                    CHANSVmObjHdr* imageArg = CHANSVmGetArg(VmInst, 0);
                    if (CHANSVmCheckNativeInstance(imageArg, "Image")) {
                        if (util::is_valid_datap(imageArg)) {
                            u32 addr = *(u32*)*imageArg->value.ptr_v;
                            result = init_texobj(VmInst, VmReturnObj, addr);
                        }
                    } else {
                        CHANSVmObjHdr* intArg = CHANSVmGetArgInteger(VmInst, 0);
                        u32 addr;
                        if (intArg != NULL) {
                            addr = intArg->value.data.len;
                        } else {
                            addr = 0;
                        }
                        result = init_texobj(VmInst, VmReturnObj, addr);
                    }
                }

                return result;
            }

            BOOL init(CHANSVm* vm) {
                return CHANSVmAddNativeClass(vm, "Texture", ctor, NULL) != NULL;
            }
        }  // namespace texture
    }  // namespace cs
}  // namespace ipl
