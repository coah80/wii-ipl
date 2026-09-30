#ifndef TEXTINPUT_KEYBOARD_H
#define TEXTINPUT_KEYBOARD_H

#include "tiTextInputBase.h"

namespace textinput {
    namespace keyboard {

        class KeyboardBase : public CommandSender {
        public:
            KeyboardBase() : meLanguage(JP) {}

            virtual ~KeyboardBase() {}
            virtual void create(MEMAllocator* alloc) override;
            virtual void init() override;
            virtual void onKey(u32, void*);
            virtual int getType();
            virtual void setLanguage(Language language);
            virtual Language getLanguage() const;
            virtual void update();
            virtual void onActive();

        protected:
            Language meLanguage;  // 0x10
        };

    }  // namespace keyboard
}  // namespace textinput

#endif  // TEXTINPUT_KEYBOARD_H
