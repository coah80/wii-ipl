#include "channelScript/iplCSLibrary.h"

#include "iplSystem.h"

namespace ipl {
    namespace cs {

        /*** GX COLOR 8 BIT ***/

        namespace color {
#define COLOR_PROPERTY_COUNT 4

            extern const CHANSVmPropertyList cPropertyList[COLOR_PROPERTY_COUNT];

            typedef union CS_Color {
                u32 packedRgba;
                GXColor gxColor;
                u8 components[4];
            } CS_Color;

            typedef struct _CS_Struct {
                CS_Color color;
                CS_Color argumentColor;
                CS_Color reserved;
            } CS_Struct;

            CHANSVmDefineMethod(ctor) {
                BOOL result = FALSE;

                nw4r::ut::Color* data = static_cast<nw4r::ut::Color*>(CHANSVmNewObjData(VmInst, VmReturnObj, sizeof(*data)));
                if (data != NULL) {
                    // new Color(GXColor)
                    if (CHANSVmGetArgc(VmInst) == 1) {
                        CHANSVmObjHdr* packedColorArg = CHANSVmGetArgInteger(VmInst, 0);
                        if (packedColorArg != NULL) {
                            *data = reinterpret_cast<CS_Struct*>(&packedColorArg->value.ptr_v)->argumentColor.gxColor;
                        }
                    }
                    // new Color(u8 r, u8 g, u8 b, u8 a)
                    else {
                        CHANSVmObjHdr* redArg = CHANSVmGetArgInteger(VmInst, 0);
                        CHANSVmObjHdr* greenArg = CHANSVmGetArgInteger(VmInst, 1);
                        CHANSVmObjHdr* blueArg = CHANSVmGetArgInteger(VmInst, 2);
                        CHANSVmObjHdr* alphaArg = CHANSVmGetArgInteger(VmInst, 3);

                        u8 componentValue;

                        data->r = redArg != NULL ? redArg->value.int_v : 0;
                        data->g = greenArg != NULL ? greenArg->value.int_v : 0;
                        data->b = blueArg != NULL ? blueArg->value.int_v : 0;
                        data->a = alphaArg != NULL ? alphaArg->value.int_v : 0;
                    }
                    result = TRUE;
                }

                return result;
            }

            DEFINE_CS_IPL_CTOR_ARG(nw4r::ut::Color color) {
                BOOL result = FALSE;
                nw4r::ut::Color* data = static_cast<nw4r::ut::Color*>(CHANSVmNewObjData(VmInst, VmObj, sizeof(*data)));
                if (data != NULL) {
                    *data = color;
                    VmObj->type = CHANS_VM_TYPE_OBJECT;
                    VmObj->parentCls = CHANSVmFindNativeClass(VmInst, "Color");
                    result = VmObj->parentCls != NULL;
                }
                return result;
            }

            BOOL init(CHANSVm* vm) {
                BOOL result = FALSE;
                // Create class
                CHANSVmNativeClass* cls = CHANSVmAddNativeClass(vm, "Color", ctor, NULL);
                if (cls != NULL) {
                    // Add properties
                    result = CHANSVmAddNativePropertyAccessorsList(vm, cls, cPropertyList, COLOR_PROPERTY_COUNT) == CHANS_VM_OK;
                }
                return result;
            }

            template <int I>
            CHANSVmDefineMethod(set) {
                BOOL result = FALSE;
                CHANSVmObjHdr* componentArg = CHANSVmGetArgInteger(VmInst, 0);
                if (util::is_valid_datap(VmParentObj) && componentArg != NULL) {
                    CS_Struct* data = static_cast<CS_Struct*>(*VmParentObj->value.ptr_v);
                    if (data != NULL) {
                        result = TRUE;
                        CS_Color updatedColor = data->color;
                        updatedColor.components[I] = componentArg->value.int_v;
                        data->color = updatedColor;
                    }
                }
                return result;
            }

            template <int I>
            CHANSVmDefineMethod(get) {
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    CS_Struct* data = static_cast<CS_Struct*>(*VmParentObj->value.ptr_v);
                    if (data != NULL) {
                        CS_Color colorValue = data->color;
                        result = CHANSVmSetInteger(VmInst, VmReturnObj, colorValue.components[I]) == CHANS_VM_OK;
                    }
                }
                return result;
            }

            const CHANSVmPropertyList cPropertyList[COLOR_PROPERTY_COUNT] = {
                {"r", get<0>, set<0>},
                {"g", get<1>, set<1>},
                {"b", get<2>, set<2>},
                {"a", get<3>, set<3>},
            };
        }  // namespace color

        /*** GX COLOR 16 BIT ***/

        namespace color_s10 {
#define COLORS10_PROPERTY_COUNT 4
            extern const CHANSVmPropertyList cPropertyList[COLORS10_PROPERTY_COUNT];

            CHANSVmDefineMethod(ctor) {
                BOOL result = FALSE;

                GXColorS10* data = static_cast<GXColorS10*>(CHANSVmNewObjData(VmInst, VmReturnObj, sizeof(*data)));
                if (data != NULL) {
                    CHANSVmObjHdr* redArg = CHANSVmGetArgInteger(VmInst, 0);
                    CHANSVmObjHdr* greenArg = CHANSVmGetArgInteger(VmInst, 1);
                    CHANSVmObjHdr* blueArg = CHANSVmGetArgInteger(VmInst, 2);
                    CHANSVmObjHdr* alphaArg = CHANSVmGetArgInteger(VmInst, 3);

                    u16 componentValue;

                    data->r = redArg != NULL ? redArg->value.int_v : 0;
                    data->g = greenArg != NULL ? greenArg->value.int_v : 0;
                    data->b = blueArg != NULL ? blueArg->value.int_v : 0;
                    data->a = alphaArg != NULL ? alphaArg->value.int_v : 0;

                    result = TRUE;
                }

                return result;
            }

            DEFINE_CS_IPL_CTOR_ARG(GXColorS10 color) {
                BOOL result = FALSE;
                GXColorS10* data = static_cast<GXColorS10*>(CHANSVmNewObjData(VmInst, VmObj, sizeof(*data)));
                if (data != NULL) {
                    *data = color;
                    VmObj->type = CHANS_VM_TYPE_OBJECT;
                    VmObj->parentCls = CHANSVmFindNativeClass(VmInst, "GXColorS10");
                    result = VmObj->parentCls != NULL;
                }
                return result;
            }

            BOOL init(CHANSVm* vm) {
                BOOL result = FALSE;
                // Create class
                CHANSVmNativeClass* cls = CHANSVmAddNativeClass(vm, "GXColorS10", ctor, NULL);
                if (cls != NULL) {
                    // Add properties
                    result = CHANSVmAddNativePropertyAccessorsList(vm, cls, cPropertyList, COLORS10_PROPERTY_COUNT) == CHANS_VM_OK;
                }
                return result;
            }

            template <int I>
            CHANSVmDefineMethod(set) {
                BOOL result = FALSE;
                CHANSVmObjHdr* componentArg = CHANSVmGetArgInteger(VmInst, 0);
                if (util::is_valid_datap(VmParentObj) && componentArg != NULL) {
                    s16* data = static_cast<s16*>(*VmParentObj->value.ptr_v);
                    if (*VmParentObj->value.ptr_v != NULL) {
                        result = TRUE;
                        data[I] = componentArg->value.int_v;
                    }
                }
                return result;
            }

            template <int I>
            CHANSVmDefineMethod(get) {
                BOOL result = FALSE;
                if (util::is_valid_datap(VmParentObj)) {
                    s16* data = static_cast<s16*>(*VmParentObj->value.ptr_v);
                    if (data != NULL) {
                        result = CHANSVmSetInteger(VmInst, VmReturnObj, data[I]) == CHANS_VM_OK;
                    }
                }
                return result;
            }

            const CHANSVmPropertyList cPropertyList[COLORS10_PROPERTY_COUNT] = {
                {"r", get<0>, set<0>},
                {"g", get<1>, set<1>},
                {"b", get<2>, set<2>},
                {"a", get<3>, set<3>},
            };
        }  // namespace color_s10
    }  // namespace cs
}  // namespace ipl
