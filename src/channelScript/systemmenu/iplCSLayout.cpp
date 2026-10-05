#include "channelScript/iplCSLibrary.h"

#include "iplSystem.h"

#define LAYOUT_PROPERTY_COUNT 6

namespace ipl {
    namespace cs {
        namespace layout {
            CHANSVmDefineMethod(find_pane) {
                BOOL ok;
                BOOL result = FALSE;

                CHANSVmObjHdr* paneNameArg = CHANSVmGetArgString(VmInst, 0);
                if (util::is_valid_datap(paneNameArg)) {
                    char name[18];
                    wchar_t wide[18];
                    memset(name, 0, sizeof(name));
                    memset(wide, 0, sizeof(wide));
                    util::utf16_to_ascii(name, wide, 16, paneNameArg);

                    ok = FALSE;
                    name[16] = '\0';
                    ipl::layout::Object* layout = System::getCSManager()->getData().layout;
                    if (layout != NULL) {
                        nw4r::lyt::Pane* pane = layout->GetRootPane()->FindPaneByName(name, TRUE);
                        if (pane == NULL || pane::_ctor(VmInst, VmReturnObj, (u32)pane)) {
                            ok = TRUE;
                        }
                        result = ok;
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(start_anm) {
                ipl::layout::Animator** anims = System::getCSManager()->getData().anims;
                BOOL result = FALSE;
                CHANSVmObjHdr* animationIndexArg = CHANSVmGetArgInteger(VmInst, 0);
                if (animationIndexArg != NULL && animationIndexArg->value.int_v < 16ULL) {
                    if (anims != NULL) {
                        ipl::layout::Animator* anim = anims[animationIndexArg->value.data.len];
                        if (anim != NULL) {
                            anim->initFrame();
                            anim->restart();
                            result = TRUE;
                        }
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(get_anm) {
                ipl::layout::Animator** anims = System::getCSManager()->getData().anims;
                BOOL result = FALSE;
                CHANSVmObjHdr* animationIndexArg = CHANSVmGetArgInteger(VmInst, 0);
                if (animationIndexArg != NULL && animationIndexArg->value.int_v < 16ULL) {
                    if (anims != NULL) {
                        result = TRUE;
                        ipl::layout::Animator* anim = anims[animationIndexArg->value.int_v];
                        if (anim != NULL) {
                            if (!anim::_ctor(VmInst, VmReturnObj, (u32)anim)) {
                                result = FALSE;
                            }
                        }
                    }
                }
                return result;
            }

            CHANSVmDefineMethod(ctor) {
                return TRUE;
            }

            const CHANSVmMethodList cMethodList[] = {
                {"FindPaneByName", find_pane},
                {"startAnim", start_anm},
                {"getAnim", get_anm},
            };

            extern const CHANSVmPropertyList cPropertyList[LAYOUT_PROPERTY_COUNT];

            BOOL init(CHANSVm* vm) {
                BOOL result = FALSE;
                CHANSVmNativeClass* cls = CHANSVmAddNativeClass(vm, "Layout", ctor, NULL);
                if (cls != NULL) {
                    result = CHANSVmAddNativeMethodList(vm, cls, cMethodList, CHANSVmMethodCount(cMethodList)) == CHANS_VM_OK;
                    result =
                        result & (CHANSVmAddNativePropertyAccessorsList(vm, cls, cPropertyList, CHANSVmPropertyCount(cPropertyList)) == CHANS_VM_OK);
                }
                return result;
            }

            // clang-format off
            const CHANSVmPropertyList cPropertyList[LAYOUT_PROPERTY_COUNT] = {
                {"*VERTEXCOLOR_LT", util::get_int<nw4r::lyt::VERTEXCOLOR_LT>, NULL},
                {"*VERTEXCOLOR_RT", util::get_int<nw4r::lyt::VERTEXCOLOR_RT>, NULL},
                {"*VERTEXCOLOR_LB", util::get_int<nw4r::lyt::VERTEXCOLOR_LB>, NULL},
                {"*VERTEXCOLOR_RB", util::get_int<nw4r::lyt::VERTEXCOLOR_RB>, NULL},
                {"*TEXTCOLOR_TOP", util::get_int<nw4r::lyt::TEXTCOLOR_TOP>, NULL},
                {"*TEXTCOLOR_BOTTOM", util::get_int<nw4r::lyt::TEXTCOLOR_BOTTOM>, NULL},
            };
            // clang-format on
        }  // namespace layout
    }  // namespace cs
}  // namespace ipl
