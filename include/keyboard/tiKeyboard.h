#ifndef TEXTINPUT_KEYBOARD_H
#define TEXTINPUT_KEYBOARD_H

#include "tiTextInputBase.h"

namespace textinput {
    namespace keyboard {

        class KeyboardBase : public CommandSender {
        public:
            virtual ~KeyboardBase() {}
#ifndef TI_PC_KEYBOARD_IMPLEMENTATION
            virtual void create(MEMAllocator* alloc) override;
            virtual void init() override;
            virtual void setCommandReceiver(CommandReceiver* receiver) override;
            virtual void sendCommand(u32 command, void*) override;
#endif
            virtual void updateFromReceiver(u32, void*) override;
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TI_PC_KEYBOARD_IMPLEMENTATION)
            virtual void onKey(u32, void*);
#else
            virtual void onKey(u32);
#endif
#ifdef TI_PC_KEYBOARD_IMPLEMENTATION
            virtual int getType();
#else
            virtual void getType();
#endif
            virtual void setLanguage(Language language);
            #ifdef TI_PC_KEYBOARD_IMPLEMENTATION
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
