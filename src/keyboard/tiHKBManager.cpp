#define TIHKBMANAGER_IMPLEMENTATION
#include "keyboard/tiHKBManager.h"
#include <revolution/os.h>

extern "C" {
_KBDEc KBDSetLedsAsync(u8, u8, void (*)(_KBDEc, void*), void*);
void KBDSetLockProcessing(u8, int);
int KBDSetCountry(u8, u32);
int KBDSetModState(u8, u32);
_KBDEc KBDSetLeds(u8, u8);
u16 KBDTranslateHidCode(u8, u32, u32);
void KBDInitRegionUS();
void KBDInit();
void KBDSetAttachCallback(void (*)(KBDDevEvent*));
void KBDSetDetachCallback(void (*)(KBDDevEvent*));
void KBDSetKeyCallback(void (*)(KBDKeyEvent*));
}

namespace textinput {
namespace input {

HKBManager HKBManager::sInstance;

// KBD callbacks encode the device in the first byte of the opaque pointer value.
union LedCallbackData {
    void* pointer;
    u8 device;
    struct {
        u8 device;
        u32 leds;
    } request;
};

void HKBManager::SetLedCB(_KBDEc result, void* userData) {
    if (result == KBD_EC_BUSY) {
        LedCallbackData received;
        received.pointer = userData;
        LedCallbackData callback;
        callback.request.device = received.device;
        callback.request.leds = 0;
        const u8 leds = callback.request.leds;
        u32 interrupts = OSDisableInterrupts();
        u32 mask = 1 << received.device;
        sInstance.retryDevices &= ~mask;
        OSRestoreInterrupts(interrupts);
        if (KBDSetLedsAsync(received.device, leds, SetLedCB, callback.pointer) == KBD_EC_BUSY) {
            interrupts = OSDisableInterrupts();
            sInstance.retryDevices |= mask;
            OSRestoreInterrupts(interrupts);
        }
    }
}

void HKBManager::KBDListenerOwn::OnAttach(KBDDevEvent* event) {
    HKBManager* owner;
    u8 device;
    if (event->device >= 2) {
        KBDSetLockProcessing(event->device, 0);
        device = event->device;
        owner = manager;
        LedCallbackData callback;
        callback.request.device = device;
        callback.request.leds = 0;
        const u8 leds = callback.request.leds;
        u32 interrupts = OSDisableInterrupts();
        u32 mask = 1 << device;
        owner->retryDevices &= ~mask;
        OSRestoreInterrupts(interrupts);
        if (KBDSetLedsAsync(device, leds, SetLedCB, callback.pointer) == KBD_EC_BUSY) {
            interrupts = OSDisableInterrupts();
            owner->retryDevices |= mask;
            OSRestoreInterrupts(interrupts);
        }
    } else {
        manager->attached[event->device] = 1;
        KBDSetLockProcessing(event->device, 0);
        manager->states[event->device].retryLeds = 1;
    }
}

void HKBManager::KBDListenerOwn::OnDetach(KBDDevEvent* event) {
    u8 device = event->device;
    if (device >= 2) return;
    HKBManager* owner = manager;
    owner->attached[device] = 0;
    owner->states[device].Clear();
}

void HKBManager::KBDListenerOwn::OnKeyEvent(KBDKeyEvent* event) {
    if (event->device >= 2) return;
    if (event->flags & 2) return;
    manager->states[event->device].NotifyEvent(event->flags & 1, event->key);
}

void HKBManager::AttachCB(KBDDevEvent* event) {
    KBDListenerOwn* current = &sInstance.listener;
    while (current != 0) {
        current->OnAttach(event);
        current = current->next;
        if (current == &sInstance.listener) break;
    }
}

void HKBManager::DetachCB(KBDDevEvent* event) {
    KBDListenerOwn* current = &sInstance.listener;
    while (current != 0) {
        current->OnDetach(event);
        current = current->next;
        if (current == &sInstance.listener) break;
    }
}

void HKBManager::KeyEventCB(KBDKeyEvent* event) {
    KBDListenerOwn* current = &sInstance.listener;
    while (current != 0) {
        current->OnKeyEvent(event);
        current = current->next;
        if (current == &sInstance.listener) break;
    }
}

HKBManager::HKBManager()
    : initialized(0), lockState(0), retryDevices(0), allowedCharacters(0),
      allowedCharacterCount(0), listener(this) {
    for (u32 device = 0; device < 2; device++) {
        attached[device] = 0;
        states[static_cast<u8>(device)].Initialize(static_cast<u8>(device));
    }
}

HKBManager::KBDListenerOwn::~KBDListenerOwn() {}

void HKBManager::Initialize() {
    if (initialized == 0) {
        initialized = 1;
        KBDInitRegionUS();
        KBDInit();
        if (listener.previous == 0) {
            KBDSetAttachCallback(AttachCB);
            KBDSetDetachCallback(DetachCB);
            KBDSetKeyCallback(KeyEventCB);
        }
        u32 device = 0;
        do {
            KBDSetCountry(static_cast<u8>(device), states[static_cast<u8>(device)].country);
            device++;
        } while (device < 2);
    }
}

void HKBManager::ClearState() {
    for (u32 device = 0; device < 2; device++) {
        states[static_cast<u8>(device)].Clear();
    }
}

u32 HKBManager::GetModifierState() const {
    u32 modifiers = states[0].modifiers;
    u32 mask = states[0].forceMask;
    modifiers &= ~mask;
    modifiers |= states[0].forceState & mask;
    u32 forceMask;
    u32 force;
    force = states[1].modifiers;
    forceMask = states[1].forceMask;
    force &= ~forceMask;
    force |= states[1].forceState & forceMask;
    return modifiers | force;
}
void HKBManager::SetCountry(u8 country) {
    KeyState_* state;
    u32 device = 0;
    do {
        state = &states[static_cast<u8>(device)];
        state->country = country;
        KBDSetCountry(device & 0xff, country);
        KBDSetModState(state->device, state->modifiers);
        u32 modifiers = state->modifiers;
        u8 leds = 0;
        if ((modifiers & 0x100) != 0) {
            leds |= 1;
        }
        if ((modifiers & 0x200) != 0) {
            leds |= 2;
        }
        if ((modifiers & 0x400) != 0) {
            leds |= 4;
        }
        if (KBDSetLeds(state->device, leds) == 7) {
            state->retryLeds = 1;
        }
        device++;
    } while (device < 2);
}

void HKBManager::SetModifierState(u32 state, u32 mask) {
    lockState = lockState & ~mask | state & mask;
    KeyState_* slot;
    u32 modifiers;
    u32 global;
    u32 device = 0;
    do {
        slot = &states[static_cast<u8>(device)];
        modifiers = slot->modifiers;
        global = lockState & 0x700;
        bool changed = global != (modifiers & 0x700);
        slot->modifiers &= ~0x700;
        slot->modifiers |= lockState;
        if (changed &&
            attached[static_cast<u8>(device)] != 0) {
            KBDSetModState(slot->device, slot->modifiers);
            modifiers = slot->modifiers;
            u8 leds = 0;
            if ((modifiers & 0x100) != 0) {
                leds |= 1;
            }
            if ((modifiers & 0x200) != 0) {
                leds |= 2;
            }
            if ((modifiers & 0x400) != 0) {
                leds |= 4;
            }
            if (KBDSetLeds(slot->device, leds) == 7) {
                slot->retryLeds = 1;
            }
        }
        device++;
    } while (device < 2);
}

void HKBManager::SetForceModifierState(u32 state, u32 mask) {
    states[0].forceState = state;
    states[0].forceMask = mask;
    states[1].forceState = state;
    states[1].forceMask = mask;
}

void HKBManager::Update() {
    if (initialized != 0) {
        u32 mask;
        u32 device = 2;
        do {
            u8 shiftIndex = static_cast<u8>(device);
            mask = 1 << shiftIndex;
            if ((retryDevices & mask) != 0) {
                LedCallbackData callback;
                callback.request.device = static_cast<u8>(device);
                callback.request.leds = 0;
                const u8 leds = callback.request.leds;
                u32 interrupts = OSDisableInterrupts();
                retryDevices &= ~mask;
                OSRestoreInterrupts(interrupts);
                if (KBDSetLedsAsync(device & 0xff, leds,
                                    SetLedCB,
                                    callback.pointer) == 7) {
                    interrupts = OSDisableInterrupts();
                    retryDevices |= mask;
                    OSRestoreInterrupts(interrupts);
                }
            }
            device++;
        } while (device < 4);
        u32 updateIndex = 0;
        do {
            states[updateIndex & 0xff].Update();
            updateIndex++;
        } while (updateIndex < 2);
    }
}

HKBManager::KeySet HKBManager::GetTriggeredKeySet() const {
    KeySet keys;
    keys.manager = this;
    keys.type = 1;
    keys.index = -1;
    keys.device = 0;
    keys.vcode = 0;
    return keys.GetNext();
}

HKBManager::KeySet HKBManager::GetReleasedKeySet() const {
    KeySet keys;
    keys.manager = this;
    keys.type = 2;
    keys.index = -1;
    keys.device = 0;
    keys.vcode = 0;
    return keys.GetNext();
}

HKBManager::KeySet HKBManager::GetRepeatedKeySet() const {
    KeySet keys;
    keys.manager = this;
    keys.type = 3;
    keys.index = -1;
    keys.device = 0;
    keys.vcode = 0;
    return keys.GetNext();
}

void HKBManager::KeyState_::NotifyEvent(u8 down, u8 code) {
    u32 index;
    s32 found = -1;
    if (down == 1) {
        for (index = 0; index < 8; index++) {
            if ((pending & (1 << index)) != 0) {
                if (code == pendingKeys[index]) { found = index; break; }
            } else {
                found = index;
                break;
            }
        }
        if (found >= 0) {
            pendingKeys[found] = code;
            pending |= 1 << found;
        }
    } else {
        for (index = 0; index < 8; index++) {
            if ((pending & (1 << index)) && code == pendingKeys[index]) {
                found = index;
                break;
            }
        }
        if (found >= 0) pending &= ~(1 << found);
    }
}

void HKBManager::KeyState_::Update() {
    u32 interrupts = OSDisableInterrupts();
    previous = current;
    current = pending;
    previousKeys[0] = currentKeys[0];
    currentKeys[0] = pendingKeys[0];
    previousKeys[1] = currentKeys[1];
    currentKeys[1] = pendingKeys[1];
    previousKeys[2] = currentKeys[2];
    currentKeys[2] = pendingKeys[2];
    previousKeys[3] = currentKeys[3];
    currentKeys[3] = pendingKeys[3];
    previousKeys[4] = currentKeys[4];
    currentKeys[4] = pendingKeys[4];
    previousKeys[5] = currentKeys[5];
    currentKeys[5] = pendingKeys[5];
    previousKeys[6] = currentKeys[6];
    currentKeys[6] = pendingKeys[6];
    previousKeys[7] = currentKeys[7];
    currentKeys[7] = pendingKeys[7];
    OSRestoreInterrupts(interrupts);
    UpdateModState_();
    u32 bit;
    u32 index;
    u32 heldKeys = current;
    triggered = 0;
    held = heldKeys;
    for (index = 0; index < 8; index++) {
        bit = 1 << index;
        if ((current & bit) != 0) {
            if ((previous & bit) == 0 || previousKeys[index] != currentKeys[index]) {
                triggered |= bit;
            }
        }
    }
    released = 0;
    for (index = 0; index < 8; index++) {
        bit = 1 << index;
        if ((previous & bit) != 0) {
            if ((current & bit) == 0 || previousKeys[index] != currentKeys[index]) {
                released |= bit;
            }
        }
    }
    repeated = 0;
    for (index = 0; index < 8; index++) {
        bit = 1 << index;
        if ((current & bit) != 0) {
            if ((triggered & bit) != 0) {
                repeatDelay[index] = 30;
                repeated |= bit;
            }
            repeatDelay[index]--;
            if (repeatDelay[index] == 0) {
                repeatDelay[index] = 8;
                repeated |= bit;
            }
        }
    }
}

void HKBManager::KeyState_::UpdateModState_() {
    u32 index;
    u32 oldModifiers = modifiers;
    modifiers = oldModifiers & 0xffffffd0;
    index = 0;
    for (; index < 8; index++) {
        u32 keySet;
        u8 slot;
        keySet = current;
        slot = index;
        if ((keySet & (1 << slot)) != 0) {
            u8 code = currentKeys[slot];
            if (code == 0xe5 || code == 0xe1) {
                modifiers |= 2;
            } else if (code == 0xe4 || code == 0xe0) {
                modifiers |= 1;
            } else if (code == 0xe7 || code == 0xe3) {
                modifiers |= 8;
            } else if (code == 0xe2) {
                modifiers |= 4;
            } else if (code == 0xe6) {
                if (static_cast<s32>(country) == 0xf ||
                    static_cast<s32>(country) == 0x21) {
                    modifiers |= 4;
                } else {
                    modifiers |= 0x20;
                }
            }
        }
    }
    if ((oldModifiers & 0x700) != (modifiers & 0x700) || retryLeds != 0) {
        retryLeds = 0;
        KBDSetModState(device, modifiers);
        u32 modifiers = this->modifiers;
        u8 leds = 0;
        if ((modifiers & 0x100) != 0) {
            leds |= 1;
        }
        if ((modifiers & 0x200) != 0) {
            leds |= 2;
        }
        if ((modifiers & 0x400) != 0) {
            leds |= 4;
        }
        if (KBDSetLeds(device, leds) == 7) {
            retryLeds = 1;
        }
    }
}

u8 HKBManager::KeySet::GetKey() const {
    if (!CheckValidity()) return 0;
    switch (type) {
    case 0: return manager->states[device].currentKeys[index];
    case 1: return manager->states[device].currentKeys[index];
    case 2: return manager->states[device].previousKeys[index];
    case 3: return manager->states[device].currentKeys[index];
    }
    return 0;
}

u32 HKBManager::KeySet::GetWChar() const {
    u32 code = GetVCode();
    if ((code & 0xffff) >= 0xf130 && (code & 0xffff) <= 0xf139) {
        code = code - 0xf100 & 0xffff;
    } else {
        u32 lowCode = code & 0xffff;
        if (lowCode == 0xf10d) {
            code = 0xf1cd;
        } else if (lowCode >= 0xf100 && lowCode <= 0xf13f) {
            code = code - 0xf100 & 0xffff;
        } else if ((code & 0xffff) >= 0xf140 && (code & 0xffff) <= 0xf17f) {
            code = code + 0x40 & 0xffff;
        }
    }
    u16 character = code;
    if ((character & 0xf000) == 0xf000) {
        code = 0;
    } else if ((code & 0xffff) == 0xeeee) {
        code = 0;
    } else if ((code & 0xffff) < 0x20) {
        code = 0;
    }
    const HKBManager* owner = manager;
    if (owner->allowedCharacters == 0) return code;
    u32 count = owner->allowedCharacterCount;
    if (count == 0) return code;
    for (u32 index = 0; index < count; index++) {
        if ((code & 0xffff) == owner->allowedCharacters[index]) return code;
    }
    return 0;
}

u32 HKBManager::KeySet::GetVCode() const {
    u32 modifiers;
    if (!CheckValidity()) return 0;
    if (vcode) return vcode;
    u32 first = manager->states[0].modifiers;
    u32 mask = manager->states[0].forceMask;
    first &= ~mask;
    first |= manager->states[0].forceState & mask;
    u32 secondMask;
    u32 second;
    second = manager->states[1].modifiers;
    secondMask = manager->states[1].forceMask;
    second &= ~secondMask;
    second |= manager->states[1].forceState & secondMask;
    modifiers = first | second;
    if ((modifiers & 0xd) != 0 && (modifiers & 5) != 5) return 0;
    switch (type) {
    case 0:
    case 1:
    case 3:
        if ((manager->states[device].current & (1 << index)) != 0) {
            vcode = KBDTranslateHidCode(manager->states[device].currentKeys[index], modifiers,
                                      manager->states[device].country);
        }
        break;
    case 2:
        if ((manager->states[device].previous & (1 << index)) != 0) {
            vcode = KBDTranslateHidCode(manager->states[device].previousKeys[index], modifiers,
                                      manager->states[device].country);
        }
        break;
    }
    return vcode;
}

u32 HKBManager::KeySet::IsValid() const {
    return CheckValidity();
}

HKBManager::KeySet HKBManager::KeySet::GetNext() const {
    KeySet next(manager, type);
    if (manager != 0) {
        next.device = device;
        while (next.device < 2) {
            u32 keyFlags = 0;
            switch (type) {
            case 0: keyFlags = manager->states[next.device].held; break;
            case 1: keyFlags = manager->states[next.device].triggered; break;
            case 2: keyFlags = manager->states[next.device].released; break;
            case 3: keyFlags = manager->states[next.device].repeated; break;
            }
            next.index = index + 1;
            while (next.index < 8) {
                if ((keyFlags & (1 << next.index)) != 0) return next;
                next.index++;
            }
            next.index = -1;
            next.device++;
        }
    }
    return next;
}


HKBManager::~HKBManager() {}

}
}
