#include <revolution/gx/GXStruct.h>
#include <revolution/os/OSError.h>

extern "C" char scCsFatalMsg[];
extern "C" GXColor scCsFatalColor;

#define NW4R_DB_ASSERT_H
#define NW4R_ASSERT(x) \
    { \
        if (!(x)) { \
            GXColor front = scCsFatalColor; \
            GXColor back = {0, 0, 0, 0}; \
            OSFatal(front, back, scCsFatalMsg); \
        } \
    }

#include "channelScript/iplCSLibrary.h"

#include "iplSystem.h"

#include <nw4r/lyt/material.h>
#include <nw4r/lyt/pane.h>
#include <nw4r/lyt/textBox.h>
#include <nw4r/math/types.h>
#include <nw4r/ut/Color.h>

#include "math/iplMathTypes.h"

extern "C" const f32 scCsZeroF = 0.0f;

extern "C" nw4r::ut::Color GetTextColor__Q34nw4r3lyt7TextBoxCFUl(const nw4r::lyt::TextBox*, u32);

namespace ipl {
    namespace cs {
        namespace pane {
            nw4r::math::VEC3 get_vec_(CHANSVm* vm);
            nw4r::lyt::Size get_size_(CHANSVm* vm);

            CHANSVmDefineMethod(show) {
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    nw4r::lyt::Pane* pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        result = TRUE;
                        pane->SetVisible(TRUE);
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(hide) {
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    nw4r::lyt::Pane* pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        result = TRUE;
                        pane->SetVisible(FALSE);
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(get_material) {
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    nw4r::lyt::Pane* pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        nw4r::lyt::Material* mat = pane->GetMaterial();
                        result = (mat == NULL || material::_ctor(VmInst, VmReturnObj, (u32)mat));
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(get_string) {
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    nw4r::lyt::Pane* pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        nw4r::lyt::TextBox* box = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
                        if (box != NULL) {
                            const wchar_t* str = box->GetString();
                            int len = wcslen(str);
                            CHANSVmObjHdr* newStr = CHANSVmNewStringObject(VmInst, VmReturnObj, len * 2);
                            if (newStr != NULL) {
                                wcsncpy(static_cast<wchar_t*>(*newStr->value.ptr_v), str, len);
                                result = TRUE;
                            }
                        }
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(set_string) {
                BOOL result = FALSE;
                CHANSVmObjHdr* stringObj = CHANSVmGetArgString(VmInst, 0);
                if (util::is_valid_datap(stringObj)) {
                    u32 strLen = stringObj->value.wstring_v->len;
                    u32 halfLen = strLen >> 1;
                    u32 wcount = halfLen + 1;
                    wchar_t* buf = (wchar_t*)new (System::getCSManager()->getHeap(), 4) u8[wcount << 1];
                    if (buf != NULL) {
                        memset(buf, 0, wcount * 2);
                        wcsncpy(buf, stringObj->value.wstring_v->spData, wcount - 1);

                        nw4r::lyt::Pane* pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                        if (pane != NULL) {
                            nw4r::lyt::TextBox* box = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
                            if (box != NULL) {
                                box->SetString(buf, 0);
                                result = TRUE;
                            }
                        }
                        delete[] buf;
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(get_scale) {
                nw4r::lyt::Pane* pane;
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        nw4r::math::VEC2 scale;
                        scale.x = pane->GetScale().x;
                        scale.y = pane->GetScale().y;
                        result = vec3::_ctor(VmInst, VmReturnObj, scale.x, scale.y, scCsZeroF) == TRUE;
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(set_scale) {
                nw4r::lyt::Pane* pane;
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        nw4r::math::VEC3 vec = get_vec_(VmInst);
                        result = TRUE;
                        pane->SetScale(nw4r::math::VEC2(vec.x, vec.y));
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(get_translate) {
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    nw4r::lyt::Pane* pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        math::VEC3 vec = pane->GetTranslate();
                        result = vec3::_ctor(VmInst, VmReturnObj, vec.x, vec.y, vec.z) == TRUE;
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(set_translate) {
                nw4r::lyt::Pane* pane;
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        nw4r::math::VEC3 vec = get_vec_(VmInst);
                        pane->SetTranslate(vec);
                        result = TRUE;
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(get_rotate) {
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    nw4r::lyt::Pane* pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        math::VEC3 vec = pane->GetRotate();
                        result = vec3::_ctor(VmInst, VmReturnObj, vec.x, vec.y, vec.z) == TRUE;
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(set_rotate) {
                nw4r::lyt::Pane* pane;
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        nw4r::math::VEC3 vec = get_vec_(VmInst);
                        pane->SetRotate(vec);
                        result = TRUE;
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(get_size) {
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    nw4r::lyt::Pane* pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        nw4r::lyt::Size paneSize = pane->GetSize();
                        result = size::_ctor(VmInst, VmReturnObj, paneSize.width, paneSize.height) == TRUE;
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(set_size) {
                nw4r::lyt::Pane* pane;
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        nw4r::lyt::Size sz = get_size_(VmInst);
                        pane->SetSize(sz);
                        result = TRUE;
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(get_alpha) {
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    nw4r::lyt::Pane* pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        u8 alpha = pane->GetAlpha();
                        result = CHANSVmSetInteger(VmInst, VmReturnObj, alpha) == CHANS_VM_OK;
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(set_alpha) {
                nw4r::lyt::Pane* pane;
                CHANSVmObjHdr* alphaArg;
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    alphaArg = CHANSVmGetArgInteger(VmInst, 0);
                    if (pane != NULL && alphaArg != NULL) {
                        result = TRUE;
                        pane->SetAlpha(alphaArg->value.int_v);
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(become_youngest_pane) {
                nw4r::lyt::Pane* pane;
                nw4r::lyt::Pane* parent;
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        // MWCC needs the direct parent load to preserve instruction order.
                        parent = *reinterpret_cast<nw4r::lyt::Pane**>(reinterpret_cast<u8*>(pane) + 0xc);
                        if (parent != NULL) {
                            parent->RemoveChild(pane);
                            parent->AppendChild(pane);
                            result = TRUE;
                        }
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(get_userdata) {
                nw4r::lyt::Pane* pane;
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        char buf[NW4R_LYT_PANE_USERDATA_SIZE + sizeof(wchar_t)];
                        memset(buf, 0, NW4R_LYT_PANE_USERDATA_SIZE + sizeof(wchar_t));
                        strncpy(buf, pane->GetUserData(), NW4R_LYT_PANE_USERDATA_SIZE);
                        result = CHANSVmSetU16StringFromU8(VmInst, VmReturnObj, buf, strlen(buf)) == CHANS_VM_OK;
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(set_userdata) {
                nw4r::lyt::Pane* pane;
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    CHANSVmObjHdr* stringObj = CHANSVmGetArgString(VmInst, 0);
                    if (pane != NULL && util::is_valid_datap(stringObj)) {
                        char buf[NW4R_LYT_PANE_USERDATA_SIZE + sizeof(wchar_t)];
                        memset(buf, 0, NW4R_LYT_PANE_USERDATA_SIZE + sizeof(wchar_t));
                        CHANSVmStrCpyToU8FromStringObject((u8*)buf, stringObj, NW4R_LYT_PANE_USERDATA_SIZE);
                        pane->SetUserData(buf);
                        result = TRUE;
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(get_line_space) {
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    nw4r::lyt::Pane* pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        nw4r::lyt::TextBox* box = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
                        if (box != NULL) {
                            result = CHANSVmSetFloat(VmInst, VmReturnObj, box->GetLineSpace()) == CHANS_VM_OK;
                        }
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(set_line_space) {
                nw4r::lyt::Pane* pane;
                CHANSVmObjHdr* lineSpaceArg;
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    lineSpaceArg = CHANSVmGetArgFloat(VmInst, 0);
                    if (pane != NULL) {
                        nw4r::lyt::TextBox* box = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
                        if (box != NULL && lineSpaceArg != NULL) {
                            result = TRUE;
                            box->SetLineSpace(lineSpaceArg->value.float_v);
                        }
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(get_char_space) {
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    nw4r::lyt::Pane* pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        nw4r::lyt::TextBox* box = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
                        if (box != NULL) {
                            result = CHANSVmSetFloat(VmInst, VmReturnObj, box->GetCharSpace()) == CHANS_VM_OK;
                        }
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(set_char_space) {
                nw4r::lyt::Pane* pane;
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    CHANSVmObjHdr* charSpaceArg = CHANSVmGetArgFloat(VmInst, 0);
                    if (pane != NULL) {
                        nw4r::lyt::TextBox* box = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
                        if (box != NULL && charSpaceArg != NULL) {
                            result = TRUE;
                            box->SetCharSpace(charSpaceArg->value.float_v);
                        }
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(get_vtx_color) {
                nw4r::lyt::Pane* pane;
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    u32 argc = CHANSVmGetArgc(VmInst);
                    CHANSVmObjHdr* vertexIndexArg = CHANSVmGetArgInteger(VmInst, 0);
                    if (pane != NULL && argc == 1 && vertexIndexArg != NULL) {
                        if (vertexIndexArg->value.int_v < static_cast<u64>(nw4r::lyt::VERTEXCOLOR_MAX)) {
                            result = color::_ctor(VmInst, VmReturnObj, (nw4r::ut::Color) static_cast<u32>(pane->GetVtxColor(vertexIndexArg->value.int_v))) == TRUE;
                        }
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(set_vtx_color) {
                nw4r::lyt::Pane* pane;
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    u32 argc = CHANSVmGetArgc(VmInst);
                    CHANSVmObjHdr* vertexIndexArg = CHANSVmGetArgInteger(VmInst, 0);
                    CHANSVmObjHdr* colorArg = CHANSVmGetArg(VmInst, 1);
                    if (pane != NULL && argc == 2 && vertexIndexArg != NULL && util::is_valid_class(colorArg, "Color")) {
                        u64 vertexIndex = vertexIndexArg->value.int_v;
                        if (vertexIndex < 4) {
                            u8* src = static_cast<u8*>(*colorArg->value.ptr_v);
                            pane->SetVtxColor(vertexIndexArg->value.int_v, *(nw4r::ut::Color*)src);
                            result = TRUE;
                        }
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(get_text_color) {
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    nw4r::lyt::Pane* pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        nw4r::lyt::TextBox* box = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
                        u32 argc = CHANSVmGetArgc(VmInst);
                        CHANSVmObjHdr* colorIndexArg = CHANSVmGetArgInteger(VmInst, 0);
                        if (box != NULL && argc == 1 && colorIndexArg != NULL) {
                            if (colorIndexArg->value.int_v < 4ULL) {
                                result = color::_ctor(VmInst, VmReturnObj, (nw4r::ut::Color) static_cast<u32>(GetTextColor__Q34nw4r3lyt7TextBoxCFUl(box, colorIndexArg->value.int_v))) == TRUE;
                            }
                        }
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(set_text_color) {
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    nw4r::lyt::Pane* pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        nw4r::lyt::TextBox* box = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
                        u32 argc = CHANSVmGetArgc(VmInst);
                        CHANSVmObjHdr* colorIndexArg = CHANSVmGetArgInteger(VmInst, 0);
                        CHANSVmObjHdr* colorArg = CHANSVmGetArg(VmInst, 1);
                        if (box != NULL && argc == 2 && colorIndexArg != NULL && util::is_valid_class(colorArg, "Color")) {
                            if (colorIndexArg->value.int_v < static_cast<u64>(nw4r::lyt::TEXTCOLOR_MAX)) {
                                u8* src = static_cast<u8*>(*colorArg->value.ptr_v);
                                box->SetTextColor(static_cast<s32>(colorIndexArg->value.int_v), *(nw4r::ut::Color*)src);
                                result = TRUE;
                            }
                        }
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(get_font_size) {
                nw4r::lyt::Pane* pane;
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
                    if (pane != NULL) {
                        nw4r::lyt::TextBox* box = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
                        if (box != NULL) {
                            nw4r::lyt::Size size = box->GetFontSize();
                            result = size::_ctor(VmInst, VmReturnObj, size.width, size.height) == TRUE;
                        }
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(set_font_size) {
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    nw4r::lyt::Pane* pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    if (pane != NULL) {
                        nw4r::lyt::TextBox* box = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
                        if (box != NULL) {
                            box->SetFontSize(get_size_(VmInst));
                            result = TRUE;
                        }
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(get_font) {
                nw4r::lyt::Pane* pane;
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
                    if (pane != NULL) {
                        nw4r::lyt::TextBox* box = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
                        if (box != NULL) {
                            result = font::_ctor(VmInst, VmReturnObj, (u32)box->GetFont()) == TRUE;
                        }
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(set_font) {
                nw4r::lyt::Pane* pane;
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    pane = *static_cast<nw4r::lyt::Pane**>(*VmParentObj->value.ptr_v);
                    CHANSVmObjHdr* fontArg = CHANSVmGetArg(VmInst, 0);
                    if (pane != NULL) {
                        nw4r::lyt::TextBox* box = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
                        if (box != NULL && util::is_valid_class(fontArg, "Font")) {
                            const nw4r::ut::Font* font = *static_cast<const nw4r::ut::Font**>(*fontArg->value.ptr_v);
                            if (font != NULL) {
                                box->SetFont(font);
                                result = TRUE;
                            }
                        }
                    }
                }
                return result;
            }

            nw4r::math::VEC3 get_vec_(CHANSVm* vm) {
                u32 argc = CHANSVmGetArgc(vm);
                CHANSVmObjHdr* vectorArg = CHANSVmGetArg(vm, 0);
                nw4r::math::VEC3 out(scCsZeroF, scCsZeroF, scCsZeroF);
                if (argc == 1 && util::is_valid_class(vectorArg, "VEC3")) {
                    f32* src = static_cast<f32*>(*vectorArg->value.ptr_v);
                    out.x = src[0];
                    out.y = src[1];
                    out.z = src[2];
                } else {
                    CHANSVmObjHdr* xArg = CHANSVmGetArgFloat(vm, 0);
                    CHANSVmObjHdr* yArg = CHANSVmGetArgFloat(vm, 1);
                    CHANSVmObjHdr* zArg = CHANSVmGetArgFloat(vm, 2);
                    if (xArg != NULL) {
                        out.x = (f32)xArg->value.float_v;
                    }
                    if (yArg != NULL) {
                        out.y = (f32)yArg->value.float_v;
                    }
                    if (zArg != NULL) {
                        out.z = (f32)zArg->value.float_v;
                    }
                }
                return out;
            }

            nw4r::lyt::Size get_size_(CHANSVm* vm) {
                u32 argc = CHANSVmGetArgc(vm);
                CHANSVmObjHdr* sizeArg = CHANSVmGetArg(vm, 0);
                nw4r::lyt::Size out(scCsZeroF, scCsZeroF);
                if (argc == 1 && util::is_valid_class(sizeArg, "Size")) {
                    f32* src = static_cast<f32*>(*sizeArg->value.ptr_v);
                    out.width = src[0];
                    out.height = src[1];
                } else {
                    CHANSVmObjHdr* widthArg = CHANSVmGetArgFloat(vm, 0);
                    CHANSVmObjHdr* heightArg = CHANSVmGetArgFloat(vm, 1);
                    if (widthArg != NULL) {
                        out.width = static_cast<f32>(widthArg->value.float_v);
                    }
                    if (heightArg != NULL) {
                        out.height = static_cast<f32>(heightArg->value.float_v);
                    }
                }
                return out;
            }

            BOOL _ctor(CHANSVm* VmInst, CHANSVmObjHdr* VmObj, u32 paneAddress) {
                BOOL result = FALSE;
                u32* data = static_cast<u32*>(CHANSVmNewObjData(VmInst, VmObj, sizeof(u32)));
                if (data != NULL) {
                    *data = paneAddress;
                    VmObj->type = CHANS_VM_TYPE_OBJECT;
                    CHANSVmNativeClass* ncls = CHANSVmFindNativeClass(VmInst, "Pane");
                    VmObj->parentCls = ncls;
                    result = ncls != NULL;
                }
                return result;
            }

            const CHANSVmMethodList cMethodList[] = {
                {"show", show},
                {"hide", hide},
                {"GetMaterial", get_material},
                {"GetString", get_string},
                {"SetString", set_string},
                {"SetScale", set_scale},
                {"GetScale", get_scale},
                {"SetTranslate", set_translate},
                {"GetTranslate", get_translate},
                {"SetRotate", set_rotate},
                {"GetRotate", get_rotate},
                {"SetSize", set_size},
                {"GetSize", get_size},
                {"GetAlpha", get_alpha},
                {"SetAlpha", set_alpha},
                {"GetVtxColor", get_vtx_color},
                {"SetVtxColor", set_vtx_color},
                {"GetTextColor", get_text_color},
                {"SetTextColor", set_text_color},
                {"becomeYoungestPane", become_youngest_pane},
                {"GetUserData", get_userdata},
                {"SetUserData", set_userdata},
                {"GetLineSpace", get_line_space},
                {"SetLineSpace", set_line_space},
                {"GetCharSpace", get_char_space},
                {"SetCharSpace", set_char_space},
                {"GetFontSize", get_font_size},
                {"SetFontSize", set_font_size},
                {"GetFont", get_font},
                {"SetFont", set_font},
            };

            BOOL init(CHANSVm* vm) {
                BOOL result = FALSE;
                CHANSVmNativeClass* cls = CHANSVmAddNativeClass(vm, "Pane", NULL, NULL);
                if (cls != NULL) {
                    result = CHANSVmAddNativeMethodList(vm, cls, cMethodList, 30) == CHANS_VM_OK;
                }
                return result;
            }

        }  // namespace pane
    }  // namespace cs
}  // namespace ipl

namespace ipl {
    namespace cs {
        namespace pane {
            extern "C" char scCsFatalMsg[] = "Error#004\nAn error has occurred.\nThe system files are corrupted.";

            extern "C" GXColor scCsFatalColor = {0xff, 0xff, 0xff, 0};
        }
    }
}
