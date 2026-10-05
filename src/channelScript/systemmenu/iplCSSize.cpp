#include "channelScript/iplCSLibrary.h"

#include "iplSystem.h"

namespace ipl {
    namespace cs {
        namespace size {
#define PROPERTY_COUNT 2
            extern const CHANSVmPropertyList cPropertyList[PROPERTY_COUNT];

            DEFINE_CS_IPL_CTOR_ARG(f32 width, f32 height) {
                BOOL result = FALSE;
                nw4r::lyt::Size* data = static_cast<nw4r::lyt::Size*>(CHANSVmNewObjData(VmInst, VmObj, sizeof(*data)));
                if (data != NULL) {
                    data->width = width;
                    data->height = height;
                    VmObj->type = CHANS_VM_TYPE_OBJECT;
                    VmObj->parentCls = CHANSVmFindNativeClass(VmInst, "Size");
                    result = VmObj->parentCls != NULL;
                }
                return result;
            }

            CHANSVmDefineMethod(ctor) {
                BOOL result = FALSE;

                nw4r::lyt::Size* data = (nw4r::lyt::Size*)CHANSVmNewObjData(VmInst, VmReturnObj, sizeof(*data));
                if (data != NULL) {
                    CHANSVmObjHdr* widthArg = CHANSVmGetArgFloat(VmInst, 0);
                    CHANSVmObjHdr* heightArg = CHANSVmGetArgFloat(VmInst, 1);

                    f32 width, height;

                    if (widthArg != NULL) {
                        width = widthArg->value.float_v;
                    } else {
                        width = 0.0;
                    }

                    if (heightArg != NULL) {
                        height = heightArg->value.float_v;
                    } else {
                        height = 0.0;
                    }

                    data->width = width;
                    data->height = height;

                    result = TRUE;
                }

                return result;
            }

            BOOL init(CHANSVm* vm) {
                BOOL result = FALSE;
                // Create class
                CHANSVmNativeClass* cls = CHANSVmAddNativeClass(vm, "Size", ctor, NULL);
                if (cls != NULL) {
                    // Add properties
                    result = CHANSVmAddNativePropertyAccessorsList(vm, cls, cPropertyList, PROPERTY_COUNT) == CHANS_VM_OK;
                }
                return result;
            }

            template <int I>
            CHANSVmDefineMethod(set) {
                BOOL result = FALSE;
                CHANSVmObjHdr* dimensionArg = CHANSVmGetArgFloat(VmInst, 0);
                if (util::is_valid_datap(VmParentObj) && dimensionArg != NULL) {
                    f32* data = static_cast<f32*>(*VmParentObj->value.ptr_v);

                    result = TRUE;
                    data[I] = dimensionArg->value.float_v;
                }
                return result;
            }

            template <int I>
            CHANSVmDefineMethod(get) {
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    f32* data = static_cast<f32*>(*VmParentObj->value.ptr_v);
                    result = CHANSVmSetFloat(VmInst, VmReturnObj, data[I]) == CHANS_VM_OK;
                }
                return result;
            }

            // clang-format off
            const CHANSVmPropertyList cPropertyList[PROPERTY_COUNT] = {
                { "width",  get<0>, set<0> },
                { "height", get<1>, set<1> },
            };
            // clang-format on
        }  // namespace size
    }  // namespace cs
}  // namespace ipl
