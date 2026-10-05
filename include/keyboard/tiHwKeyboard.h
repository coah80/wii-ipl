#ifndef TEXTINPUT_HW_KEYBOARD_H
#define TEXTINPUT_HW_KEYBOARD_H

#include "tiTextInputBase.h"
#include "tiHKBManager.h"

namespace textinput {
    class Manager;
    namespace keyboard {
        namespace hwkey {
            #ifdef TIMANAGER_IMPLEMENTATION
            class HWKeyboard : public CommandSender {
#else
            class HWKeyboard : CommandSender {
#endif
                public:
                    HWKeyboard(Manager *);
#if defined(TIMANAGER_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION)
                    inline ~HWKeyboard();
#else
                    ~HWKeyboard();
#endif
#if defined(TIMANAGER_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION)
                    void setLanguage(Destination destination, Language language);
#endif

                    virtual void    init();
#if defined(TI_PC_KEYBOARD_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION)
                    wchar_t convertWCCode(wchar_t code) const;
#endif

#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION)
                    void            updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data);
#else
                    virtual void    updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data);
#endif
                    virtual bool    updateInput(input::HKBManager& hkbManager);
                        
#ifdef TIINPUTFORM_IMPLEMENTATION
                    void resetQuoteState() { mbSingleQuoteClosing = 0; mbDoubleQuoteClosing = 0; }
#endif
                private:
#ifdef TIHWKEYBOARD_IMPLEMENTATION
                    bool updateRepeatKey_(input::HKBManager&);
                    bool updateTriggerKey_(input::HKBManager&);
                    bool updateTappingShift_(input::HKBManager&);
#endif
                    void            updateShift(input::HKBManager& hkbManager);
                    bool controlKeyTriggeredHandler(input::HKBManager&);

                    Manager *mgr() { return mpManager; }
                    const Manager *mgr() const { return mpManager; }

                    Manager*    mpManager;  // 0x10
                    u8          mbShiftTapPending; // 0x14
#ifdef TIINPUTFORM_IMPLEMENTATION
                    u8 mbSingleQuoteClosing;
                    u8 mbDoubleQuoteClosing;
#else
#ifdef TIHWKEYBOARD_IMPLEMENTATION
                    bool mbSingleQuoteClosing;
                    bool mbDoubleQuoteClosing;
#else
                    u8          mbSingleQuoteClosing; // 0x15
                    u8          mbDoubleQuoteClosing; // 0x16
#endif
#endif
            };

            
        }
    }
}

#endif // TEXTINPUT_HW_KEYBOARD_H
