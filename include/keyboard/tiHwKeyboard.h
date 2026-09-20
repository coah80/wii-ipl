#ifndef TEXTINPUT_HW_KEYBOARD_H
#define TEXTINPUT_HW_KEYBOARD_H

#include "tiTextInputBase.h"
#include "tiHKBManager.h"

namespace textinput {
    class Manager;
    namespace keyboard {
        namespace hwkey {
            class HWKeyboard : CommandSender {
                public:
                    HWKeyboard(Manager *);
                    ~HWKeyboard();

                    virtual void    init();

                    virtual void    updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data);
                    virtual bool    updateInput(input::HKBManager& hkbManager);
                        
                private:
                    void            updateShift(input::HKBManager& hkbManager);
                    void controlKeyTriggeredHandler(input::HKBManager);

                    Manager *mgr() { return mpManager; }

                    Manager*    mpManager;  // 0x10
                    u8          field_0x14; // 0x14
                    u8          field_0x15; // 0x15
                    u8          field_0x16; // 0x16
            };

            
        }
    }
}

#endif // TEXTINPUT_HW_KEYBOARD_H
