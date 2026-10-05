#include "channelScript/iplCSLibrary.h"

#include "iplSystem.h"

namespace ipl {
    namespace cs {
        namespace anim {
            BOOL start(CHANSVm* vm, CHANSVmObjHdr* parentObj, CHANSVmObjHdr* returnObj) {
                ipl::layout::Animator* anim;
                BOOL ret = FALSE;
                if (util::is_valid_datap(parentObj)) {
                    anim = *static_cast<ipl::layout::Animator**>(*parentObj->value.ptr_v);
                    if (anim != NULL) {
                        anim->initFrame();
                        anim->restart();
                        ret = TRUE;
                    }
                }
                return ret;
            }

            BOOL restart(CHANSVm* vm, CHANSVmObjHdr* parentObj, CHANSVmObjHdr* returnObj) {
                BOOL ret = FALSE;
                if (util::is_valid_datap(parentObj)) {
                    ipl::layout::Animator* anim = *static_cast<ipl::layout::Animator**>(*parentObj->value.ptr_v);
                    if (anim != NULL) {
                        anim->restart();
                        ret = TRUE;
                    }
                }
                return ret;
            }

            BOOL stop(CHANSVm* vm, CHANSVmObjHdr* parentObj, CHANSVmObjHdr* returnObj) {
                BOOL ret = FALSE;
                if (util::is_valid_datap(parentObj)) {
                    ipl::layout::Animator* anim = *static_cast<ipl::layout::Animator**>(*parentObj->value.ptr_v);
                    if (anim != NULL) {
                        anim->stop();
                        ret = TRUE;
                    }
                }
                return ret;
            }

            BOOL is_playing(CHANSVm* vm, CHANSVmObjHdr* parentObj, CHANSVmObjHdr* returnObj) {
                BOOL ret = FALSE;
                if (util::is_valid_datap(parentObj)) {
                    ipl::layout::Animator* anim = *static_cast<ipl::layout::Animator**>(*parentObj->value.ptr_v);
                    if (anim != NULL) {
                        ret = CHANSVmSetInteger(vm, returnObj, anim->isPlaying()) == CHANS_VM_OK;
                    }
                }
                return ret;
            }

            BOOL init_frame(CHANSVm* vm, CHANSVmObjHdr* parentObj, CHANSVmObjHdr* returnObj) {
                BOOL ret = FALSE;
                CHANSVmObjHdr* frameArg = CHANSVmGetArgFloat(vm, 0);
                if (util::is_valid_datap(parentObj) && frameArg != NULL) {
                    f32 frame = static_cast<f32>(frameArg->value.float_v);
                    ipl::layout::Animator* anim = *static_cast<ipl::layout::Animator**>(*parentObj->value.ptr_v);
                    if (anim != NULL) {
                        if (frame >= 0.0f) {
                            anim->initAnmFrame(frame);
                            ret = TRUE;
                        }
                    }
                }
                return ret;
            }

            BOOL set_max_frame(CHANSVm* vm, CHANSVmObjHdr* parentObj, CHANSVmObjHdr* returnObj) {
                BOOL ret = FALSE;
                CHANSVmObjHdr* maxFrameArg = CHANSVmGetArgFloat(vm, 0);
                if (util::is_valid_datap(parentObj) && maxFrameArg != NULL) {
                    ipl::layout::Animator* anim = *static_cast<ipl::layout::Animator**>(*parentObj->value.ptr_v);
                    if (anim != NULL) {
                        f32 maxFrame = static_cast<f32>(maxFrameArg->value.float_v);
                        f32 minFrame = anim->getMinFrame();
                        if (maxFrame >= 0.0f && minFrame < maxFrame) {
                            anim->setMaxFrame(maxFrame);
                            ret = TRUE;
                        }
                    }
                }
                return ret;
            }

            BOOL set_min_frame(CHANSVm* vm, CHANSVmObjHdr* parentObj, CHANSVmObjHdr* returnObj) {
                BOOL ret = FALSE;
                CHANSVmObjHdr* minFrameArg = CHANSVmGetArgFloat(vm, 0);
                if (util::is_valid_datap(parentObj) && minFrameArg != NULL) {
                    ipl::layout::Animator* anim = *static_cast<ipl::layout::Animator**>(*parentObj->value.ptr_v);
                    if (anim != NULL) {
                        f32 minFrame = static_cast<f32>(minFrameArg->value.float_v);
                        f32 maxFrame = anim->getMaxFrame();
                        if (minFrame >= 0.0f && minFrame < maxFrame) {
                            anim->setMinFrame(minFrame);
                            ret = TRUE;
                        }
                    }
                }
                return ret;
            }

            BOOL set_current_frame(CHANSVm* vm, CHANSVmObjHdr* parentObj, CHANSVmObjHdr* returnObj) {
                BOOL ret = FALSE;
                CHANSVmObjHdr* currentFrameArg = CHANSVmGetArgFloat(vm, 0);
                if (util::is_valid_datap(parentObj) && currentFrameArg != NULL) {
                    f32 currentFrame = static_cast<f32>(currentFrameArg->value.float_v);
                    ipl::layout::Animator* anim = *static_cast<ipl::layout::Animator**>(*parentObj->value.ptr_v);
                    if (anim != NULL) {
                        anim->setCurrentFrame(currentFrame);
                        ret = TRUE;
                    }
                }
                return ret;
            }

            BOOL set_type(CHANSVm* vm, CHANSVmObjHdr* parentObj, CHANSVmObjHdr* returnObj) {
                BOOL ret = FALSE;
                CHANSVmObjHdr* typeArg = CHANSVmGetArgInteger(vm, 0);
                if (util::is_valid_datap(parentObj) && typeArg != NULL) {
                    s32 type = typeArg->value.int_v;
                    ipl::layout::Animator* anim = *static_cast<ipl::layout::Animator**>(*parentObj->value.ptr_v);
                    if (anim != NULL) {
                        if (type >= ANIM_TYPE_FORWARD && type < ANIM_TYPE_ALTERNATE + 1) {
                            anim->setAnmType(type);
                            ret = TRUE;
                        }
                    }
                }
                return ret;
            }

            BOOL set_delta(CHANSVm* vm, CHANSVmObjHdr* parentObj, CHANSVmObjHdr* returnObj) {
                BOOL ret = FALSE;
                CHANSVmObjHdr* speedArg = CHANSVmGetArgFloat(vm, 0);
                if (util::is_valid_datap(parentObj) && speedArg != NULL) {
                    f32 speed = static_cast<f32>(speedArg->value.float_v);
                    ipl::layout::Animator* anim = *static_cast<ipl::layout::Animator**>(*parentObj->value.ptr_v);
                    if (anim != NULL) {
                        anim->setSpeed(speed);
                        ret = TRUE;
                    }
                }
                return ret;
            }

            BOOL get_max_frame(CHANSVm* vm, CHANSVmObjHdr* parentObj, CHANSVmObjHdr* returnObj) {
                BOOL ret = FALSE;
                if (util::is_valid_datap(parentObj)) {
                    ipl::layout::Animator* anim = *static_cast<ipl::layout::Animator**>(*parentObj->value.ptr_v);
                    if (anim != NULL) {
                        ret = CHANSVmSetFloat(vm, returnObj, anim->getMaxFrame()) == CHANS_VM_OK;
                    }
                }
                return ret;
            }

            BOOL get_min_frame(CHANSVm* vm, CHANSVmObjHdr* parentObj, CHANSVmObjHdr* returnObj) {
                BOOL ret = FALSE;
                if (util::is_valid_datap(parentObj)) {
                    ipl::layout::Animator* anim = *static_cast<ipl::layout::Animator**>(*parentObj->value.ptr_v);
                    if (anim != NULL) {
                        ret = CHANSVmSetFloat(vm, returnObj, anim->getMinFrame()) == CHANS_VM_OK;
                    }
                }
                return ret;
            }

            BOOL get_current_frame(CHANSVm* vm, CHANSVmObjHdr* parentObj, CHANSVmObjHdr* returnObj) {
                BOOL ret = FALSE;
                if (util::is_valid_datap(parentObj)) {
                    ipl::layout::Animator* anim = *static_cast<ipl::layout::Animator**>(*parentObj->value.ptr_v);
                    if (anim != NULL) {
                        ret = CHANSVmSetFloat(vm, returnObj, anim->getCurrentFrame()) == CHANS_VM_OK;
                    }
                }
                return ret;
            }

            BOOL get_type(CHANSVm* vm, CHANSVmObjHdr* parentObj, CHANSVmObjHdr* returnObj) {
                BOOL ret = FALSE;
                if (util::is_valid_datap(parentObj)) {
                    ipl::layout::Animator* anim = *static_cast<ipl::layout::Animator**>(*parentObj->value.ptr_v);
                    if (anim != NULL) {
                        ret = CHANSVmSetInteger(vm, returnObj, anim->getAnmType()) == CHANS_VM_OK;
                    }
                }
                return ret;
            }

            BOOL get_delta(CHANSVm* vm, CHANSVmObjHdr* parentObj, CHANSVmObjHdr* returnObj) {
                BOOL ret = FALSE;
                if (util::is_valid_datap(parentObj)) {
                    ipl::layout::Animator* anim = *static_cast<ipl::layout::Animator**>(*parentObj->value.ptr_v);
                    if (anim != NULL) {
                        ret = CHANSVmSetFloat(vm, returnObj, anim->getSpeed()) == CHANS_VM_OK;
                    }
                }
                return ret;
            }

            BOOL _ctor(CHANSVm* VmInst, CHANSVmObjHdr* VmObj, u32 anim) {
                BOOL ret = FALSE;
                u32* data = static_cast<u32*>(CHANSVmNewObjData(VmInst, VmObj, sizeof(u32)));
                if (data != NULL) {
                    *data = anim;
                    VmObj->type = CHANS_VM_TYPE_OBJECT;
                    CHANSVmNativeClass* ncls = CHANSVmFindNativeClass(VmInst, "Anim");
                    VmObj->parentCls = ncls;
                    ret = ncls != NULL;
                }
                return ret;
            }

            const CHANSVmMethodList cMethodList[] = {
                {"start", start},
                {"restart", restart},
                {"stop", stop},
                {"isPlaying", is_playing},
                {"initFrame", init_frame},
                {"setMaxFrame", set_max_frame},
                {"setMinFrame", set_min_frame},
                {"setCurrentFrame", set_current_frame},
                {"setType", set_type},
                {"setDelta", set_delta},
                {"getMaxFrame", get_max_frame},
                {"getMinFrame", get_min_frame},
                {"getCurrentFrame", get_current_frame},
                {"getType", get_type},
                {"getDelta", get_delta},
            };

            const CHANSVmPropertyList cPropertyList[] = {
                {"*TYPE_FORWARD", util::get_int<ANIM_TYPE_FORWARD>, NULL},
                {"*TYPE_BACKWARD", util::get_int<ANIM_TYPE_BACKWARD>, NULL},
                {"*TYPE_LOOP", util::get_int<ANIM_TYPE_LOOP>, NULL},
                {"*TYPE_ALTERNATE", util::get_int<ANIM_TYPE_ALTERNATE>, NULL},
            };

            BOOL init(CHANSVm* vm) {
                BOOL result = FALSE;
                CHANSVmNativeClass* cls = CHANSVmAddNativeClass(vm, "Anim", NULL, NULL);
                if (cls != NULL) {
                    result = CHANSVmAddNativeMethodList(vm, cls, cMethodList, CHANSVmMethodCount(cMethodList)) == CHANS_VM_OK;
                    result =
                        result & (CHANSVmAddNativePropertyAccessorsList(vm, cls, cPropertyList, CHANSVmPropertyCount(cPropertyList)) == CHANS_VM_OK);
                }
                return result;
            }
        }  // namespace anim
    }  // namespace cs
}  // namespace ipl
