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
            for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
                WPADSetDpdSensitivity(sensitivity);
                KPADSetBtnRepeat(i, 0.5f, 0.1f);
            }

            read();
        }

        void Manager::read() {
            for (int chan = 0; chan < WPAD_MAX_CONTROLLERS; chan++) {
                if (SCGetWpadSensorBarPosition() == SC_WPAD_SENSOR_BAR_POSITION_TOP) {
                    KPADSetSensorHeight(chan, 0.2f);
                } else {
                    KPADSetSensorHeight(chan, -0.2f);
                }

                u32 deviceType;
                s32 probe = WPADProbe(chan, &deviceType);
                // MWCC needs this probe dispatch to preserve the branch layout.
                if (probe == WPAD_ERR_NO_CONTROLLER) {
                    goto probe_invalid;
                }
                if (probe < WPAD_ERR_NO_CONTROLLER) {
                    if (probe >= WPAD_ERR_TRANSFER) {
                        goto probe_valid;
                    }
                    goto probe_invalid;
                } else if (probe >= 1) {
                    goto probe_invalid;
                }

            probe_valid:
                {
                    s32 read = KPADRead(chan, &mKPADStatus[chan], 1);
                    if (read > 0 && mKPADStatus[chan].wpad_err != WPAD_ERR_INVALID && deviceType != WPAD_DEV_NOT_FOUND) {
                        mInvalidCount[chan] = 0;
                        if (mKPADStatus[chan].wpad_err == WPAD_ERR_CORRUPTED || deviceType == WPAD_DEV_CORE || deviceType == WPAD_DEV_FUTURE ||
                            deviceType == WPAD_DEV_NOT_SUPPORTED || deviceType == WPAD_DEV_UNKNOWN) {
                            if (mControllers[chan] == NULL || mControllers[chan]->getType() != WPAD_DEV_CORE) {
                                mControllers[chan] = new (mControllerStorage[chan]) Core(chan, WPAD_DEV_CORE, mKPADStatus[chan]);
                            }
                        } else if (deviceType == WPAD_DEV_FREESTYLE) {
                            if (mControllers[chan] == NULL || mControllers[chan]->getType() != WPAD_DEV_FREESTYLE) {
                                mControllers[chan] = new (mControllerStorage[chan]) FreeStyle(chan, WPAD_DEV_FREESTYLE, mKPADStatus[chan]);
                            }
                        } else if (deviceType == WPAD_DEV_CLASSIC) {
                            if (mControllers[chan] == NULL || mControllers[chan]->getType() != WPAD_DEV_CLASSIC) {
                                mControllers[chan] = new (mControllerStorage[chan]) Classic(chan, mKPADStatus[chan]);
                            }
                        } else {
                            mControllers[chan] = NULL;
                        }
                    } else {
                        if (read == 0) {
                            mInvalidCount[chan]++;
                            if (mInvalidCount[chan] > 0x3c) {
                                mInvalidCount[chan] = 0x3c;
                                if (mControllers[chan] != NULL) {
                                    WPADControlMotor(chan, WPAD_MOTOR_STOP);
                                }
                                mControllers[chan] = NULL;
                            }
                        } else {
                            mControllers[chan] = NULL;
                        }
                    }
                }
                goto channel_done;

            probe_invalid:
                KPADRead(chan, &mKPADStatus[chan], 1);
                mControllers[chan] = NULL;

            channel_done:
                KPADSetPosParam(chan, 0.05f, 1.0f);
            }

            for (int chan = 0; chan < WPAD_MAX_CONTROLLERS; chan++) {
                if (mControllers[chan] != NULL) {
                    mControllers[chan]->read();
                }
            }
        }

        Revolution::Revolution(int chan, int type, KPADStatus& status) : Base(chan, type, status) {
            mbPinching = 0;
            mbWasPinching = 0;
            mpKpadStatus = &status;
        }

        Interface* Manager::getMasterController() {
            return &mMaster;
        }

        Interface* Manager::getController(int chan) {
            return mControllers[chan];
        }

        Interface* Manager::getYoungController() {
            Interface* ret = NULL;
            for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
                Interface* controller = mControllers[i];
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
