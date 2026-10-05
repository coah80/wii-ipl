#include "channelScript/iplCSLibrary.h"

#include "iplSystem.h"

namespace ipl {
    namespace cs {
        namespace rect {
            CHANSVmDefineMethod(get_width) {
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    nw4r::ut::Rect* data = static_cast<nw4r::ut::Rect*>(*VmParentObj->value.ptr_v);
                    result = CHANSVmSetFloat(VmInst, VmReturnObj, data->GetWidth()) == CHANS_VM_OK;
                }
                return result;
            }

            CHANSVmDefineMethod(get_height) {
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    nw4r::ut::Rect* data = static_cast<nw4r::ut::Rect*>(*VmParentObj->value.ptr_v);
                    result = CHANSVmSetFloat(VmInst, VmReturnObj, data->GetHeight()) == CHANS_VM_OK;
                }
                return result;
            }

            CHANSVmDefineMethod(set_width) {
                BOOL result = FALSE;
                CHANSVmObjHdr* widthArg = CHANSVmGetArgFloat(VmInst, 0);
                if (util::is_valid_datap(VmParentObj) && widthArg != NULL) {
                    nw4r::ut::Rect* data = static_cast<nw4r::ut::Rect*>(*VmParentObj->value.ptr_v);

                    result = TRUE;
                    data->SetWidth(widthArg->value.float_v);
                }
                return result;
            }

            CHANSVmDefineMethod(set_height) {
                BOOL result = FALSE;
                CHANSVmObjHdr* heightArg = CHANSVmGetArgFloat(VmInst, 0);
                if (util::is_valid_datap(VmParentObj) && heightArg != NULL) {
                    nw4r::ut::Rect* data = static_cast<nw4r::ut::Rect*>(*VmParentObj->value.ptr_v);

                    result = TRUE;
                    data->SetHeight(heightArg->value.float_v);
                }
                return result;
            }

            DEFINE_CS_IPL_CTOR() {
                BOOL result = FALSE;

                VmObj->type = CHANS_VM_TYPE_OBJECT;
                VmObj->parentCls = CHANSVmFindNativeClass(VmInst, "Rect");
                if (VmObj->parentCls != NULL) {
                    result = TRUE;
                }

                return result;
            }

            CHANSVmDefineMethod(ctor) {
                BOOL result = FALSE;

                nw4r::ut::Rect* data = static_cast<nw4r::ut::Rect*>(CHANSVmNewObjData(VmInst, VmReturnObj, sizeof(*data)));
                if (data != NULL) {
                    CHANSVmObjHdr* leftArg = CHANSVmGetArgFloat(VmInst, 0);
                    CHANSVmObjHdr* topArg = CHANSVmGetArgFloat(VmInst, 1);
                    CHANSVmObjHdr* rightArg = CHANSVmGetArgFloat(VmInst, 2);
                    CHANSVmObjHdr* bottomArg = CHANSVmGetArgFloat(VmInst, 3);

                    f32 left, top, right, bottom;

                    if (leftArg != NULL) {
                        left = leftArg->value.float_v;
                    } else {
                        left = 0.0;
                    }

                    if (topArg != NULL) {
                        top = topArg->value.float_v;
                    } else {
                        top = 0.0;
                    }

                    if (rightArg != NULL) {
                        right = rightArg->value.float_v;
                    } else {
                        right = 0.0;
                    }

                    if (bottomArg != NULL) {
                        bottom = bottomArg->value.float_v;
                    } else {
                        bottom = 0.0;
                    }

                    result = TRUE;

                    nw4r::ut::Rect newData(left, top, right, bottom);
                    *data = newData;
                }

                return result;
            }

            // clang-format off
            const CHANSVmMethodList cMethodList[] = {
                {"GetWidth", get_width },
                {"GetHeight", get_height },
                {"SetWidth", set_width },
                {"SetHeight", set_height },
            };
            // clang-format on

            BOOL init(CHANSVm* vm) {
                BOOL result = FALSE;
                // Create class
                CHANSVmNativeClass* cls = CHANSVmAddNativeClass(vm, "Rect", ctor, NULL);
                if (cls != NULL) {
                    // Add properties
                    result = CHANSVmAddNativeMethodList(vm, cls, cMethodList, CHANSVmMethodCount(cMethodList)) == CHANS_VM_OK;
                }
                return result;
            }
        }  // namespace rect
    }  // namespace cs
}  // namespace ipl
