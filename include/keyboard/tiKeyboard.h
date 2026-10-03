#ifndef TEXTINPUT_KEYBOARD_H
#define TEXTINPUT_KEYBOARD_H

#include "tiTextInputBase.h"

namespace textinput {
    namespace keyboard {

        class KeyboardBase : public CommandSender {
        public:
#ifdef TIMANAGER_IMPLEMENTATION
            KeyboardBase() : meLanguage(JP) {}
#endif
            virtual ~KeyboardBase() {}
#if !(defined(TI_PC_KEYBOARD_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION)) && !defined(TIMANAGER_IMPLEMENTATION) && !defined(TISIGNWINDOW_IMPLEMENTATION)
            virtual void create(MEMAllocator* alloc) override;
            virtual void init() override;

#ifndef TI_CELLPHONE_MATCH_LAYOUT
            virtual void setCommandReceiver(CommandReceiver* receiver) override;
            virtual void sendCommand(u32 command, void*) override;
#endif
#endif
#if !defined(TIMANAGER_IMPLEMENTATION) && !defined(TISIGNWINDOW_IMPLEMENTATION)
            virtual void updateFromReceiver(u32, void*) override;
#endif
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || (defined(TI_PC_KEYBOARD_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION)) || defined(TIMANAGER_IMPLEMENTATION) || defined(TISIGNWINDOW_IMPLEMENTATION)
            virtual void onKey(u32, void*);
#else
            virtual void onKey(u32);
#endif
#ifdef TI_CELLPHONE_IMPLEMENTATION
            virtual u32 getType();
#elif (defined(TI_PC_KEYBOARD_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION)) || defined(TIMANAGER_IMPLEMENTATION) || defined(TISIGNWINDOW_IMPLEMENTATION)
            virtual int getType();
#else
            virtual void getType();
#endif
#ifdef TI_CELLPHONE_IMPLEMENTATION
            virtual void setLanguage(Language language) { meLanguage = language; }
#else
            virtual void setLanguage(Language language);
#endif
#if (defined(TI_PC_KEYBOARD_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION)) || defined(TIMANAGER_IMPLEMENTATION) || defined(TISIGNWINDOW_IMPLEMENTATION)
#if defined(TISIGNWINDOW_IMPLEMENTATION) || defined(TI_PC_KEYBOARD_IMPLEMENTATION)
            virtual Language getLanguage() const;
#else
            virtual Language getLanguage() const { return meLanguage; }
#endif
#ifdef TI_PC_KEYBOARD_IMPLEMENTATION
            virtual void update();
#else
            virtual void update() {}
#endif
#else
            virtual Language getLanguage() const;
            virtual void update();
#endif
            virtual void onActive();

        protected:
            Language meLanguage;  // 0x10
        };

    }  // namespace keyboard
}  // namespace textinput

#endif  // TEXTINPUT_KEYBOARD_H
