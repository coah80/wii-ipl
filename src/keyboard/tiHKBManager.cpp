#include "keyboard/tiHKBManager.h"

namespace textinput {
    namespace input {

        HKBManager HKBManager::sInstance;

        void HKBManager::SetLedCB(KBDEc result, void* arg) {
            if (result == KBD_EC_OK) {
                u8 packet[8];
                void* data = arg;
                *(u32*)(packet + 4) = 0;
                packet[0] = *(u8*)&data;

                u32 intr = OSDisableInterrupts();
                u32 bit = 1 << *(u8*)&data;
                sInstance.mPendingLeds &= ~bit;
                OSRestoreInterrupts(intr);

                if (KBDSetLedsAsync(*(u8*)&data, 0, SetLedCB, (void*)*(u32*)packet) == KBD_EC_OK) {
                    intr = OSDisableInterrupts();
                    sInstance.mPendingLeds |= bit;
                    OSRestoreInterrupts(intr);
                }
            }
        }

        void HKBManager::KBDListenerOwn::OnAttach(KBDDevEvent* event) {
            if (event->chan >= 2) {
                KBDSetLockProcessing(event->chan, 0);
                u8 chan = event->chan;
                u8 packet[8];
                *(u32*)(packet + 4) = 0;
                HKBManager* mgr = mpManager;
                packet[0] = chan;

                u32 intr = OSDisableInterrupts();
                mgr->mPendingLeds &= ~(1 << chan);
                OSRestoreInterrupts(intr);

                if (KBDSetLedsAsync(chan, 0, SetLedCB, (void*)*(u32*)packet) == KBD_EC_OK) {
                    intr = OSDisableInterrupts();
                    mgr->mPendingLeds |= (1 << chan);
                    OSRestoreInterrupts(intr);
                }
            }
            else {
                mpManager->mAttached[event->chan] = 1;
                KBDSetLockProcessing(event->chan, 0);
                mpManager->mKeyStates[event->chan].mLedOK = 1;
            }
        }

        void HKBManager::KBDListenerOwn::OnDetach(KBDDevEvent* event) {
            if (event->chan >= 2) {
                return;
            }
            u8 chan = event->chan;
            KeyState_* state = &mpManager->mKeyStates[chan];
            mpManager->mAttached[chan] = 0;
            state->mMaskWork = 0;
            state->mTrigMask = 0;
            state->mRelMask = 0;
            state->mRepMask = 0;
            state->mCurMask = 0;
            state->mInputMask = 0;
            state->mModState &= 0x700;
            state->mForceMask = 0;
            state->mForceMod = 0;
            state->mLedOK = 0;
        }

        void HKBManager::KBDListenerOwn::OnKeyEvent(KBDKeyEvent* event) {
            u8 chan = event->chan;
            if (chan >= 2) {
                return;
            }
            if (event->mods & 0x2) {
                return;
            }
            mpManager->mKeyStates[chan].NotifyEvent(event->mods & 1, event->key);
        }

        void HKBManager::AttachCB(KBDDevEvent* event) {
            KBDListener* head;
            KBDListener* listener = &sInstance.mListener;
            head = listener;
            while (listener != NULL) {
                listener->OnAttach(event);
                listener = listener->mpNext;
                if (listener == head) {
                    break;
                }
            }
        }

        void HKBManager::DetachCB(KBDDevEvent* event) {
            KBDListener* head;
            KBDListener* listener = &sInstance.mListener;
            head = listener;
            while (listener != NULL) {
                listener->OnDetach(event);
                listener = listener->mpNext;
                if (listener == head) {
                    break;
                }
            }
        }

        void HKBManager::KeyEventCB(KBDKeyEvent* event) {
            KBDListener* head;
            KBDListener* listener = &sInstance.mListener;
            head = listener;
            while (listener != NULL) {
                listener->OnKeyEvent(event);
                listener = listener->mpNext;
                if (listener == head) {
                    break;
                }
            }
        }

        HKBManager::~HKBManager() {}

        HKBManager::HKBManager() :
            mInitialized(0), mModState(0), mPendingLeds(0),
            mpKeyTable(NULL), mKeyTableNum(0), mListener(this) {
            for (u8 i = 0; i < 2; i++) {
                mAttached[i] = 0;
                mKeyStates[i].mMaskWork = 0;
                mKeyStates[i].mTrigMask = 0;
                mKeyStates[i].mRelMask = 0;
                mKeyStates[i].mRepMask = 0;
                mKeyStates[i].mCurMask = 0;
                mKeyStates[i].mInputMask = 0;
                mKeyStates[i].mForceMask = 0;
                mKeyStates[i].mForceMod = 0;
                mKeyStates[i].mLedOK = 0;
                mKeyStates[i].mKbdChan = i;
                mKeyStates[i].mCountry = 0xF;
                mKeyStates[i].mModState = 0;
            }
        }

        void HKBManager::Initialize() {
            if (mInitialized != 0) {
                return;
            }
            mInitialized = 1;
            KBDInitRegionUS();
            KBDInit();
            if (mListener.unk_0x04 == 0) {
                KBDSetAttachCallback(AttachCB);
                KBDSetDetachCallback(DetachCB);
                KBDSetKeyCallback(KeyEventCB);
            }
            for (u8 i = 0; i < 2; i++) {
                KBDSetCountry(i, mKeyStates[i].mCountry);
            }
        }

        void HKBManager::ClearState() {
            for (u8 i = 0; i < 2; i++) {
                mKeyStates[i].mMaskWork = 0;
                mKeyStates[i].mTrigMask = 0;
                mKeyStates[i].mRelMask = 0;
                mKeyStates[i].mRepMask = 0;
                mKeyStates[i].mCurMask = 0;
                mKeyStates[i].mInputMask = 0;
                mKeyStates[i].mModState &= 0x700;
                mKeyStates[i].mForceMask = 0;
                mKeyStates[i].mForceMod = 0;
                mKeyStates[i].mLedOK = 0;
            }
        }

        u32 HKBManager::GetModifierState() const {
            u32 modState = (mKeyStates[0].mModState & ~mKeyStates[0].mForceMask) |
                           (mKeyStates[0].mForceMod & mKeyStates[0].mForceMask);
            u32 modState1 = (mKeyStates[1].mModState & ~mKeyStates[1].mForceMask) |
                            (mKeyStates[1].mForceMod & mKeyStates[1].mForceMask);
            modState |= modState1;
            return modState;
        }

        void HKBManager::SetCountry(u8 country) {
            for (u8 i = 0; i < 2; i++) {
                mKeyStates[i].mCountry = country;
                KBDSetCountry(i, country);
                KBDSetModState(mKeyStates[i].mKbdChan, mKeyStates[i].mModState);

                u8 leds = 0;
                if (mKeyStates[i].mModState & 0x100) {
                    leds |= 1;
                }
                if (mKeyStates[i].mModState & 0x200) {
                    leds |= 2;
                }
                if (mKeyStates[i].mModState & 0x400) {
                    leds |= 4;
                }
                if (KBDSetLeds(mKeyStates[i].mKbdChan, leds) == KBD_EC_OK) {
                    mKeyStates[i].mLedOK = 1;
                }
            }
        }

        void HKBManager::SetModifierState(u32 state, u32 mask) {
            mModState = (mModState & ~mask) | (state & mask);
            for (u8 i = 0; i < 2; i++) {
                u32 newLeds = mModState & 0x700;
                u32 tmp = mKeyStates[i].mModState & ~0x700;
                u32 oldLeds = mKeyStates[i].mModState & 0x700;
                mKeyStates[i].mModState = tmp;
                mKeyStates[i].mModState = tmp | mModState;
                if ((((oldLeds - newLeds) | (newLeds - oldLeds)) >> 31) != 0 && mAttached[i]) {
                    KBDSetModState(mKeyStates[i].mKbdChan, mKeyStates[i].mModState);

                    u8 leds = 0;
                    if (mKeyStates[i].mModState & 0x100) {
                        leds |= 1;
                    }
                    if (mKeyStates[i].mModState & 0x200) {
                        leds |= 2;
                    }
                    if (mKeyStates[i].mModState & 0x400) {
                        leds |= 4;
                    }
                    if (KBDSetLeds(mKeyStates[i].mKbdChan, leds) == KBD_EC_OK) {
                        mKeyStates[i].mLedOK = 1;
                    }
                }
            }
        }

        void HKBManager::SetForceModifierState(u32 state, u32 mask) {
            mKeyStates[0].mForceMod = state;
            mKeyStates[0].mForceMask = mask;
            mKeyStates[1].mForceMod = state;
            mKeyStates[1].mForceMask = mask;
        }

        void HKBManager::Update() {
            if (mInitialized == 0) {
                return;
            }
            for (u8 chan = 2; chan < 4; chan++) {
                u32 bit = 1 << chan;
                if (mPendingLeds & bit) {
                    u8 packet[8];
                    packet[0] = chan;
                    *(u32*)(packet + 4) = 0;

                    u32 intr = OSDisableInterrupts();
                    mPendingLeds &= ~bit;
                    OSRestoreInterrupts(intr);

                    if (KBDSetLedsAsync(chan, 0, SetLedCB, (void*)*(u32*)packet) == KBD_EC_OK) {
                        intr = OSDisableInterrupts();
                        mPendingLeds |= bit;
                        OSRestoreInterrupts(intr);
                    }
                }
            }
            for (u8 i = 0; i < 2; i++) {
                mKeyStates[i].Update();
            }
        }

        HKBManager::KeySet HKBManager::GetTriggeredKeySet() const {
            KeySet keySet(this, 1);
            return keySet.GetNext();
        }

        HKBManager::KeySet HKBManager::GetReleasedKeySet() const {
            KeySet keySet(this, 2);
            return keySet.GetNext();
        }

        HKBManager::KeySet HKBManager::GetRepeatedKeySet() const {
            KeySet keySet(this, 3);
            return keySet.GetNext();
        }

        void HKBManager::KeyState_::NotifyEvent(u8 type, u8 key) {
            int i;
            int index = -1;
            if (type == 1) {
                for (i = 0; i < 8; i++) {
                    if ((mInputMask & (1 << i)) != 0) {
                        if (mCurKeys[i] == key) {
                            index = i;
                            break;
                        }
                    }
                    else {
                        index = i;
                        break;
                    }
                }
                if (index < 0) {
                    return;
                }
                mCurKeys[index] = key;
                mInputMask |= (1 << index);
            }
            else {
                for (i = 0; i < 8; i++) {
                    if ((mInputMask & (1 << i)) != 0 && mCurKeys[i] == key) {
                        index = i;
                        break;
                    }
                }
                if (index < 0) {
                    return;
                }
                mInputMask &= ~(1 << index);
            }
        }

        void HKBManager::KeyState_::Update() {
            u32 intr = OSDisableInterrupts();
            mPrevMask = mCurMask;
            mCurMask = mInputMask;
            for (int i = 0; i < 8; i++) {
                mReleasedKeys[i] = mPrevKeys[i];
                mPrevKeys[i] = mCurKeys[i];
            }
            OSRestoreInterrupts(intr);

            UpdateModState_();

            u32 bit;
            mMaskWork = mCurMask;
            mTrigMask = 0;
            for (int i = 0; i < 8; i++) {
                bit = 1 << i;
                if ((mCurMask & bit) &&
                    (!(mPrevMask & bit) || mReleasedKeys[i] != mPrevKeys[i])) {
                    mTrigMask |= bit;
                }
            }

            mRelMask = 0;
            for (int i = 0; i < 8; i++) {
                bit = 1 << i;
                if ((mPrevMask & bit) &&
                    (!(mCurMask & bit) || mReleasedKeys[i] != mPrevKeys[i])) {
                    mRelMask |= bit;
                }
            }

            mRepMask = 0;
            for (int i = 0; i < 8; i++) {
                bit = 1 << i;
                if (mCurMask & bit) {
                    if (mTrigMask & bit) {
                        mRepeatCtr[i] = 30;
                        mRepMask |= bit;
                    }
                    if (--mRepeatCtr[i] == 0) {
                        mRepeatCtr[i] = 8;
                        mRepMask |= bit;
                    }
                }
            }
        }

        void HKBManager::KeyState_::UpdateModState_() {
            u32 oldMod = mModState;
            mModState &= ~0x2F;
            for (u8 i = 0; i < 8; i++) {
                if ((mCurMask & (1 << i)) == 0) {
                    continue;
                }
                u8 key = mPrevKeys[i];
                if (key == 0xE5 || key == 0xE1) {
                    mModState |= 2;
                }
                else if (key == 0xE4 || key == 0xE0) {
                    mModState |= 1;
                }
                else if (key == 0xE7 || key == 0xE3) {
                    mModState |= 8;
                }
                else if (key == 0xE2) {
                    mModState |= 4;
                }
                else if (key == 0xE6) {
                    if (mCountry == 0xF || mCountry == 0x21) {
                        mModState |= 4;
                    }
                    else {
                        mModState |= 0x20;
                    }
                }
            }

            if ((oldMod & 0x700) != (mModState & 0x700) || mLedOK != 0) {
                mLedOK = 0;
                KBDSetModState(mKbdChan, mModState);

                u8 leds = 0;
                if (mModState & 0x100) {
                    leds |= 1;
                }
                if (mModState & 0x200) {
                    leds |= 2;
                }
                if (mModState & 0x400) {
                    leds |= 4;
                }
                if (KBDSetLeds(mKbdChan, leds) == KBD_EC_OK) {
                    mLedOK = 1;
                }
            }
        }

        u8 HKBManager::KeySet::GetKey() const {
            if (!IsValid()) {
                return 0;
            }
            switch (mType) {
                case 0: return mpManager->mKeyStates[mSubIndex].mPrevKeys[mIndex];
                case 1: return mpManager->mKeyStates[mSubIndex].mPrevKeys[mIndex];
                case 2: return mpManager->mKeyStates[mSubIndex].mReleasedKeys[mIndex];
                case 3: return mpManager->mKeyStates[mSubIndex].mPrevKeys[mIndex];
            }
            return 0;
        }

        wchar_t HKBManager::KeySet::GetWChar() const {
            wchar_t vcode = GetVCode();
            if (vcode >= 0xF130 && vcode <= 0xF139) {
                vcode = vcode - 0xF100;
            }
            else if (vcode == 0xF10D) {
                vcode = 0x10000 - 0xE33;
            }
            else if (vcode >= 0xF100 && vcode <= 0xF13F) {
                vcode = vcode - 0xF100;
            }
            else if (vcode >= 0xF140 && vcode <= 0xF17F) {
                vcode = vcode + 0x40;
            }
            if ((vcode & 0xF000) == 0xF000) {
                return 0;
            }
            if (vcode == 0xEEEE) {
                return 0;
            }
            if (vcode < 0x20) {
                return 0;
            }
            if (mpManager->mpKeyTable == NULL) {
                return vcode;
            }
            if (mpManager->mKeyTableNum == 0) {
                return vcode;
            }
            for (u32 i = 0; i < mpManager->mKeyTableNum; i++) {
                if (mpManager->mpKeyTable[i] == vcode) {
                    return vcode;
                }
            }
            return 0;
        }

        wchar_t HKBManager::KeySet::GetVCode() const {
            if (!IsValid()) {
                return 0;
            }
            if (mVCode != 0) {
                return mVCode;
            }

            u32 mods = mpManager->GetModifierState();
            if ((mods & 0xD) != 0 && (mods & 5) != 5) {
                return 0;
            }

            switch (mType) {
                case 0:
                case 1:
                case 3:
                    if ((mpManager->mKeyStates[mSubIndex].mCurMask & (1 << mIndex)) != 0) {
                        mVCode = KBDTranslateHidCode(
                            mpManager->mKeyStates[mSubIndex].mPrevKeys[mIndex],
                            mpManager->mKeyStates[mSubIndex].mCountry);
                    }
                    break;
                case 2:
                    if ((mpManager->mKeyStates[mSubIndex].mPrevMask & (1 << mIndex)) != 0) {
                        mVCode = KBDTranslateHidCode(
                            mpManager->mKeyStates[mSubIndex].mReleasedKeys[mIndex],
                            mpManager->mKeyStates[mSubIndex].mCountry);
                    }
                    break;
            }
            return mVCode;
        }

        bool HKBManager::KeySet::IsValid() const {
            if (mpManager == NULL) {
                return false;
            }
            s8 index = mIndex;
            if (index < 0 || index >= 8) {
                return false;
            }
            u8 subIndex = mSubIndex;
            if (subIndex >= 2) {
                return false;
            }
            switch (mType) {
                case 0: return (mpManager->mKeyStates[subIndex].mMaskWork & (1 << index)) != 0;
                case 1: return (mpManager->mKeyStates[subIndex].mTrigMask & (1 << index)) != 0;
                case 2: return (mpManager->mKeyStates[subIndex].mRelMask & (1 << index)) != 0;
                case 3: return (mpManager->mKeyStates[subIndex].mRepMask & (1 << index)) != 0;
            }
            return false;
        }

        HKBManager::KeySet HKBManager::KeySet::GetNext() const {
            KeySet next(mpManager, mType);
            if (mpManager == NULL) {
                return next;
            }
            next.mSubIndex = mSubIndex;
            while (next.mSubIndex < 2) {
                u32 mask = 0;
                switch (mType) {
                    case 0: mask = mpManager->mKeyStates[next.mSubIndex].mMaskWork; break;
                    case 1: mask = mpManager->mKeyStates[next.mSubIndex].mTrigMask; break;
                    case 2: mask = mpManager->mKeyStates[next.mSubIndex].mRelMask; break;
                    case 3: mask = mpManager->mKeyStates[next.mSubIndex].mRepMask; break;
                }
                next.mIndex = mIndex + 1;
                while (next.mIndex < 8) {
                    if (mask & (1 << next.mIndex)) {
                        return next;
                    }
                    next.mIndex++;
                }
                next.mIndex = -1;
                next.mSubIndex++;
            }
            return next;
        }

    }  // namespace input
}  // namespace textinput
