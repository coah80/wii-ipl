#ifndef TEXTINPUT_HKB_MANAGER_H
#define TEXTINPUT_HKB_MANAGER_H

#include <revolution/types.h>

#include <revolution/mem/allocator.h>
#include <revolution/os.h>

#include "keyboard/tiCpData.h"

typedef enum _KBDEc {
    KBD_EC_0 = 0,
    KBD_EC_1,
    KBD_EC_2,
    KBD_EC_3,
    KBD_EC_4,
    KBD_EC_5,
    KBD_EC_6,
    KBD_EC_OK,
} KBDEc;

typedef struct _KBDDevEvent {
    u8 chan;
    u8 unk_0x01[0x1F];
} KBDDevEvent;

typedef struct _KBDKeyEvent {
    u8  chan;
    u8  key;
    u8  unk_0x02[2];
    u32 mods;
} KBDKeyEvent;

extern "C" {
void    KBDInitRegionUS(void);
void    KBDInit(void);
void    KBDSetAttachCallback(void (*cb)(KBDDevEvent*));
void    KBDSetDetachCallback(void (*cb)(KBDDevEvent*));
void    KBDSetKeyCallback(void (*cb)(KBDKeyEvent*));
int     KBDSetLedsAsync(u8 chan, u8 leds, void (*cb)(KBDEc, void*), void* arg);
int     KBDSetLeds(u8 chan, u8 leds);
int     KBDSetModState(u8 chan, u32 mods);
int     KBDSetCountry(u8 chan, u32 country);
int     KBDSetLockProcessing(u8 chan, int lock);
u16     KBDTranslateHidCode(u8 key, u32 country);
}

namespace textinput {
    namespace input {

        class HKBManager {
        public:
            HKBManager();
            ~HKBManager();

            static HKBManager& getInstance() { return sInstance; }

            void Initialize();
            void Update();

            u32  GetModifierState() const;
            void SetModifierState(u32 state, u32 mask);
            void SetForceModifierState(u32 state, u32 mask);
            void SetCountry(u8 country);
            void ClearState();

            class KeySet {
            public:
                KeySet(const HKBManager* manager, u8 type) :
                    mpManager(manager), mType(type),
                    mIndex(-1), mSubIndex(0), mVCode(0) {}

                u8      GetKey() const;
                wchar_t GetWChar() const;
                wchar_t GetVCode() const;
                bool    IsValid() const;
                KeySet  GetNext() const;

                const HKBManager* mpManager;    // 0x00
                u8                mType;        // 0x04
                s8                mIndex;       // 0x05
                u8                mSubIndex;    // 0x06
                mutable u16       mVCode;       // 0x08
            };

            KeySet GetTriggeredKeySet() const;
            KeySet GetReleasedKeySet() const;
            KeySet GetRepeatedKeySet() const;

        private:
            class KeyState_ {
            public:
                void NotifyEvent(u8 type, u8 key);
                void Update();
                void UpdateModState_();

                u8  mKbdChan;           // 0x00
                u8  pad_0x01[3];
                u32 mMaskWork;          // 0x04
                u32 mTrigMask;          // 0x08
                u32 mRelMask;           // 0x0C
                u32 mRepMask;           // 0x10
                u32 mPrevMask;          // 0x14
                u32 mCurMask;           // 0x18
                u32 mInputMask;         // 0x1C
                u32 mModState;          // 0x20
                u32 mForceMod;          // 0x24
                u32 mForceMask;         // 0x28
                s32 mCountry;           // 0x2C
                u8  mLedOK;             // 0x30
                u8  mReleasedKeys[8];   // 0x31
                u8  mPrevKeys[8];       // 0x39
                u8  mCurKeys[8];        // 0x41
                u8  pad_0x49[3];
                u32 mRepeatCtr[8];      // 0x4C
            };

            class KBDListener {
            public:
                KBDListener() : unk_0x04(0), mpNext(NULL) {}
                virtual ~KBDListener() {}
                virtual void OnAttach(KBDDevEvent* event);
                virtual void OnDetach(KBDDevEvent* event);
                virtual void OnKeyEvent(KBDKeyEvent* event);

                u32          unk_0x04;
                KBDListener* mpNext;
            };

            class KBDListenerOwn : public KBDListener {
            public:
                KBDListenerOwn(HKBManager* manager) : mpManager(manager) {}

                virtual void OnAttach(KBDDevEvent* event);
                virtual void OnDetach(KBDDevEvent* event);
                virtual void OnKeyEvent(KBDKeyEvent* event);

                HKBManager* mpManager;   // 0x0C
            };

            static void SetLedCB(KBDEc result, void* arg);
            static void AttachCB(KBDDevEvent* event);
            static void DetachCB(KBDDevEvent* event);
            static void KeyEventCB(KBDKeyEvent* event);

            u8            mInitialized;         // 0x00
            u8            mAttached[2];         // 0x01
            u8            pad_0x03;
            u32           mModState;            // 0x04
            u32           mPendingLeds;         // 0x08
            const wchar_t* mpKeyTable;          // 0x0C
            u32           mKeyTableNum;         // 0x10
            KeyState_     mKeyStates[2];        // 0x14
            KBDListenerOwn mListener;           // 0xEC

            static HKBManager sInstance;
        };

    }  // namespace input
}  // namespace textinput

#endif  // TEXTINPUT_HKB_MANAGER_H
