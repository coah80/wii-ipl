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
#if !defined(TI_PC_KEYBOARD_IMPLEMENTATION) && !defined(TIMANAGER_IMPLEMENTATION)
            virtual void create(MEMAllocator* alloc) override;
            virtual void init() override;
            virtual void setCommandReceiver(CommandReceiver* receiver) override;
            virtual void sendCommand(u32 command, void*) override;
#endif
#ifndef TIMANAGER_IMPLEMENTATION
            virtual void updateFromReceiver(u32, void*) override;
#endif
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TI_PC_KEYBOARD_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
            virtual void onKey(u32, void*);
#else
            virtual void onKey(u32);
#endif
#if defined(TI_PC_KEYBOARD_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
            virtual int getType();
#else
            virtual void getType();
#endif
            virtual void setLanguage(Language language);
            #if defined(TI_PC_KEYBOARD_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
            virtual Language getLanguage() const { return meLanguage; }
            virtual void update() {}
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
