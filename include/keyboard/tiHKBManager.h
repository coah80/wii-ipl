#ifndef TEXTINPUT_HKB_MANAGER_H
#define TEXTINPUT_HKB_MANAGER_H

#include <revolution/types.h>

#include <revolution/mem/allocator.h>

#include "keyboard/tiCpData.h"
#ifdef TIHKBMANAGER_IMPLEMENTATION
#include <revolution/kbd.h>
enum _KBDEc { KBD_EC_BUSY = 7 };
#endif

namespace textinput {
    namespace input {
#ifdef TIHKBMANAGER_IMPLEMENTATION
        class HKBManager {
        public:
            class KeyState_ {
            public:
                void NotifyEvent(u8 down, u8 code);
                void Update();
                bool HasCurrentKey(u32 slot) const { return (current & (1 << slot)) != 0; }
                bool HadPreviousKey(u32 slot) const { return (previous & (1 << slot)) != 0; }
                void UpdateModState_();
                void Clear() {
                    held = 0;
                    triggered = 0;
                    released = 0;
                    repeated = 0;
                    current = 0;
                    pending = 0;
                    modifiers &= 0x700;
                    forceMask = 0;
                    forceState = 0;
                    retryLeds = 0;
                }
                void Initialize(u8 channel) {
                    held = 0;
                    triggered = 0;
                    released = 0;
                    repeated = 0;
                    current = 0;
                    pending = 0;
                    forceMask = 0;
                    forceState = 0;
                    retryLeds = 0;
                    device = channel;
                    country = 0xf;
                    modifiers = 0;
                }
                u8 device;
                u32 held, triggered, released, repeated;
                u32 previous, current, pending;
                u32 modifiers, forceState, forceMask;
                s32 country;
                u8 retryLeds;
                u8 previousKeys[8], currentKeys[8], pendingKeys[8];
                u32 repeatDelay[8];
            };
            class KeySet {
            public:
                KeySet() {}
                KeySet(const HKBManager* owner, u8 kind)
                    : manager(owner), type(kind), index(-1), device(0), vcode(0) {}
                u8 GetKey() const;
                u32 GetWChar() const;
                u32 GetVCode() const;
                u32 IsValid() const;
                bool CheckValidity() const {
                    if (!manager) return false;
                    s8 keyIndex = index;
                    if (keyIndex < 0 || keyIndex >= 8) return false;
                    u8 keyDevice = device;
                    if (keyDevice >= 2) return false;
                    switch (type) {
                    case 0: return (manager->states[keyDevice].held & (1 << keyIndex)) != 0;
                    case 1: return (manager->states[keyDevice].triggered & (1 << keyIndex)) != 0;
                    case 2: return (manager->states[keyDevice].released & (1 << keyIndex)) != 0;
                    case 3: return (manager->states[keyDevice].repeated & (1 << keyIndex)) != 0;
                    }
                    return false;
                }
                KeySet GetNext() const;
                const HKBManager* manager;
                u8 type;
                s8 index;
                u8 device;
                mutable u16 vcode;
            };
            class KBDListenerOwn;
            class KBDListenerLinks {
            public:
                KBDListenerLinks() : previous(0), next(0) {}
                virtual ~KBDListenerLinks() {}
                virtual void OnAttach(KBDDevEvent*) = 0;
                virtual void OnDetach(KBDDevEvent*) = 0;
                virtual void OnKeyEvent(KBDKeyEvent*) = 0;
                KBDListenerOwn* previous;
                KBDListenerOwn* next;
            };
            class KBDListenerOwn : public KBDListenerLinks {
            public:
                KBDListenerOwn(HKBManager* owner) : manager(owner) {}
                virtual ~KBDListenerOwn();
                virtual void OnAttach(KBDDevEvent* event);
                virtual void OnDetach(KBDDevEvent* event);
                virtual void OnKeyEvent(KBDKeyEvent* event);
                HKBManager* manager;
            };
            HKBManager() __attribute__((never_inline));
            static HKBManager& getInstance() { return sInstance; }
            void Initialize();
            void ClearState();
            u32 FilterCharacter(u32 code) const {
                if (allowedCharacters == 0) return code;
                u32 count = allowedCharacterCount;
                if (count == 0) return code;
                for (u32 index = 0; index < count; index++) {
                    if (static_cast<u16>(code) == allowedCharacters[index]) return code;
                }
                return 0;
            }
            void DetachDevice(KBDDevEvent* event) {
                u8 device = event->device;
                attached[device] = 0;
                states[device].Clear();
            }
            u32 GetModifierState() const;
            void SetCountry(u8 country);
            void SetModifierState(u32 state, u32 mask);
            void SetForceModifierState(u32 state, u32 mask);
            void Update();
            KeySet GetTriggeredKeySet() const;
            KeySet GetReleasedKeySet() const;
            KeySet GetRepeatedKeySet() const;
#ifdef TIHWKEYBOARD_IMPLEMENTATION
            KeySet GetReleasedKeySet() const;
#endif
            static void SetLedCB(_KBDEc result, void* userData);
            static void AttachCB(KBDDevEvent* event);
            static void DetachCB(KBDDevEvent* event);
            static void KeyEventCB(KBDKeyEvent* event);
        private:
            u8 initialized;
            u8 attached[2];
            u32 lockState;
            u32 retryDevices;
            const wchar_t* allowedCharacters;
            u32 allowedCharacterCount;
            KeyState_ states[2];
            KBDListenerOwn listener;
            static HKBManager sInstance;
        };
#else
        class HKBManager {
        public:
#ifdef TIMANAGER_IMPLEMENTATION
                void ClearState();
#endif
            static HKBManager& getInstance() { return sInstance; }

            void Initialize();
            void Update();

            u32 GetModifierState() const;
            void SetCountry(u8 country);
            void SetModifierState(u32, u32);

#if defined(TI_CELLPHONE_HKB_KEYSET)
            class KeySet {
            public:
                u8 GetKey() const;
                u32 GetWChar() const;
                bool IsValid() const;
                KeySet GetNext() const;
                KeySet(const KeySet& other)
                    : mpManager(other.mpManager), mKind(other.mKind), mIndex(other.mIndex),
                      mDevice(other.mDevice), mCharacter(other.mCharacter) {}
            private:
                const HKBManager* mpManager;
                u8 mKind;
                s8 mIndex;
                u8 mDevice;
                u16 mCharacter;
            };
            KeySet GetTriggeredKeySet() const;
            KeySet GetRepeatedKeySet() const;
#else
#if defined(TI_PC_KEYBOARD_IMPLEMENTATION) || defined(TISIGNWINDOW_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION)
            class KeySet {
            public:
                u8 GetKey() const;
#ifdef TIHWKEYBOARD_IMPLEMENTATION
                u32 GetWChar() const;
#else
                wchar_t GetWChar() const;
#endif
                bool IsValid() const;
                KeySet GetNext() const;
                KeySet(const KeySet& other)
                    : mpManager(other.mpManager), mKind(other.mKind), mIndex(other.mIndex), mDevice(other.mDevice), mCharacter(other.mCharacter) {}
#ifdef TIHWKEYBOARD_IMPLEMENTATION
                KeySet() : mpManager(NULL), mKind(0), mIndex(-1), mDevice(0), mCharacter(0) {}
#endif
            private:
                const HKBManager* mpManager;
                u8 mKind;
                s8 mIndex;
                u8 mDevice;
                u16 mCharacter;
            };
            KeySet GetTriggeredKeySet() const;
            KeySet GetRepeatedKeySet() const;
#ifdef TIHWKEYBOARD_IMPLEMENTATION
            KeySet GetReleasedKeySet() const;
#endif
            void SetForceModifierState(u32 mask, u32 state);
#else
            class KeySet {
            private:
                keyboard::cellphonetype::PaneNameToCharCode* pPaneNameToCharCode;  // 0x00
                wchar_t szKeySetName[17];                                          // 0x04
                u16 uNum;                                                          // 0x26
                u16 uType;                                                         // 0x28

#ifdef TI_CELLPHONE_IMPLEMENTATION
            public:
                bool IsValid() const;
                u32 GetKey() const;
                wchar_t GetWChar() const;
                KeySet GetNext() const;
#endif
            };

#ifdef TI_CELLPHONE_IMPLEMENTATION
            KeySet GetTriggeredKeySet() const;
            KeySet GetRepeatedKeySet() const;
#endif

#endif
#endif
        private:
            u8 mKeyboardStateStorage[0xFC];

            static HKBManager sInstance;
        };
#endif
    }  // namespace input
}  // namespace textinput

#endif  // TEXTINPUT_HKB_MANAGER_H
