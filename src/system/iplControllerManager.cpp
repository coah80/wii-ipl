#include <decomp/ide.h>
#include <math/iplMathTypes.h>
#define IPL_SOUND_RECT_OUT_OF_LINE
#include <nw4r/ut/Rect.h>
#undef IPL_SOUND_RECT_OUT_OF_LINE
#include <revolution/kpad.h>
#include <revolution/mtx/GeoTypes.h>
#include <revolution/os.h>
#include <revolution/os/OSTime.h>
#include <revolution/sc.h>
#include <revolution/wpad.h>

#define IPL_CONTROLLER_NATIVE_HIERARCHY
#include "system/iplController.h"
#undef IPL_CONTROLLER_NATIVE_HIERARCHY
#include "system/iplSystem.h"

extern "C" void* mpAllocator__Q33ipl10controller7Manager;
extern "C" void _savegpr_16();
extern "C" void _restgpr_16();
extern "C" void _savegpr_29();
extern "C" void _restgpr_29();
extern "C" void _savegpr_27();
extern "C" void _restgpr_27();
extern "C" void _savegpr_28();
extern "C" void _restgpr_28();
extern "C" void __ct__Q33ipl10controller10RevolutionFiiR10KPADStatus();
extern "C" void __ct__Q33ipl10controller7ClassicFiR10KPADStatus();
extern "C" void __ct__Q23EGG9AllocatorFPQ23EGG4Heapl();
extern "C" void create__Q23EGG7ExpHeapFPvUlUs();
extern "C" void __nw__FUlPQ23EGG4Heapi();
extern "C" void __dl__FPv();
extern "C" void __ptmf_scall();
extern "C" void alloc__Q33ipl10controller7ManagerFUl();
extern "C" void free__Q33ipl10controller7ManagerFPv();
extern "C" void read__Q33ipl10controller7ManagerFv();

namespace ipl {
    namespace controller {
        void* Manager::mpBuf;
        EGG::Heap* Manager::mpParentHeap;
        EGG::ExpHeap* Manager::mpHeap;
        EGG::Allocator* Manager::mpAllocator;

        void* Manager::alloc(u32 size) {
            return mpAllocator->alloc(size);
        }

        int Manager::free(void* ptr) {
            mpAllocator->free(ptr);
            return TRUE;
        }

        Manager::Manager(EGG::Heap* heap) : mMaster(mControllers) {
            memset(mKPADStatus, 0, sizeof(mKPADStatus));
            memset(mControllers, 0, sizeof(mControllers));

            u32 workSize = WPADGetWorkMemorySize() + 0x400;
            if (mpBuf != NULL && mpParentHeap != NULL) {
                mpParentHeap->free(mpBuf);
            }

            mpParentHeap = heap;
            mpBuf = heap->alloc(workSize, 0x20);
            if (mpHeap != NULL) {
                mpHeap->destroy();
            }

            mpHeap = EGG::ExpHeap::create(mpBuf, workSize, 2);
            if (mpAllocator != NULL) {
                delete mpAllocator;
            }

            mpAllocator = new (heap, 4) EGG::Allocator(mpHeap, 4);
            WPADRegisterAllocator(alloc, free);
            KPADInit();

            u32 sensitivity = SCGetBtDpdSensibility();
            for (int i = 0; i < 4; i++) {
                WPADSetDpdSensitivity(sensitivity);
                KPADSetBtnRepeat(i, 0.5f, 0.1f);
            }

            read();
        }

        void Manager::read() {
            for (int chan = 0; chan < 4; chan++) {
                if (SCGetWpadSensorBarPosition() == 1) {
                    KPADSetSensorHeight(chan, 0.2f);
                } else {
                    KPADSetSensorHeight(chan, -0.2f);
                }

                u32 deviceType;
                s32 probe = WPADProbe(chan, &deviceType);
                if (probe == -1) {
                    goto probe_invalid;
                }
                if (probe < -1) {
                    if (probe < -3) {
                        goto probe_invalid;
                    }
                } else if (probe >= 1) {
                    goto probe_invalid;
                }

                {
                    s32 read = KPADRead(chan, &mKPADStatus[chan], 1);
                    if (read > 0) {
                        if (mKPADStatus[chan].wpad_err == -4 || deviceType == 0xfd) {
                            goto store_null;
                        }

                        mInvalidCount[chan] = 0;
                        if (mKPADStatus[chan].wpad_err == -7 || deviceType == 0 || deviceType == 0xfb ||
                            deviceType == 0xfc || deviceType == 0xff) {
                            if (mControllers[chan] == NULL || mControllers[chan]->getType() != 0) {
                                mControllers[chan] = new (mControllerStorage[chan]) Core(chan, 0, mKPADStatus[chan]);
                            }
                        } else if (deviceType == 1) {
                            if (mControllers[chan] == NULL || mControllers[chan]->getType() != 1) {
                                mControllers[chan] = new (mControllerStorage[chan]) FreeStyle(chan, 1, mKPADStatus[chan]);
                            }
                        } else if (deviceType == 2) {
                            if (mControllers[chan] == NULL || mControllers[chan]->getType() != 2) {
                                mControllers[chan] = new (mControllerStorage[chan]) Classic(chan, mKPADStatus[chan]);
                            }
                        } else {
                            mControllers[chan] = NULL;
                        }
                    } else if (read == 0) {
                        mInvalidCount[chan]++;
                        if (mInvalidCount[chan] > 0x3c) {
                            mInvalidCount[chan] = 0x3c;
                            if (mControllers[chan] != NULL) {
                                WPADControlMotor(chan, 0);
                            }
                            mControllers[chan] = NULL;
                        }
                    } else {
                        goto store_null;
                    }
                }
                goto channel_done;

            store_null:
                mControllers[chan] = NULL;
                goto channel_done;

            probe_invalid:
                KPADRead(chan, &mKPADStatus[chan], 1);
                mControllers[chan] = NULL;

            channel_done:
                KPADSetPosParam(chan, 0.05f, 1.0f);
            }

            for (int chan = 0; chan < 4; chan++) {
                if (mControllers[chan] != NULL) {
                    mControllers[chan]->read();
                }
            }
        }

        Revolution::Revolution(int chan, int type, KPADStatus& status) : Base(chan, type, status) {
            unk_0x1D = 0;
            unk_0x1E = 0;
            unk_0x20 = &status;
        }

        Interface* Manager::getMasterController() {
            return (Interface*)((u8*)this + 0xd0);
        }

        Interface* Manager::getController(int chan) {
            return ((Interface**)this)[chan];
        }

        Interface* Manager::getYoungController() {
            Interface* ret = NULL;
            for (int i = 0; i < 4; i++) {
                Interface* controller = ((Interface**)this)[i];
                if (controller != NULL) {
                    ret = controller;
                    break;
                }
            }
            return ret;
        }

        Core::~Core() {}

        FreeStyle::~FreeStyle() {}
    }
}
