#ifndef IPL_MESSAGE_MANAGER_H
#define IPL_MESSAGE_MANAGER_H

#include <egg/core.h>

#include "system/iplMessage.h"

namespace ipl {
#ifdef IPL_SETTING_IMPLEMENTATION
    namespace scene { class Setting; }
#endif
    namespace message {
        class Manager {
        public:
            Manager(EGG::Heap* heap);

            /** @return The message data in use. */
            wchar_t* getMessage(u32 id) const { return mpMessage->getMessage(id); }
            void setResource(u8* msgData) const { mpMessage->setResource(msgData); }

        private:
#ifdef IPL_SETTING_IMPLEMENTATION
            friend class scene::Setting;
#endif
            void initMessage();

            Message* mpMessage;  // 0x00
        };
    }  // namespace message
}  // namespace ipl

#endif  // IPL_MESSAGE_MANAGER_H
