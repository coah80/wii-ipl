#include "iplSound.h"
#include "sound/iplSound.h"

#include <revolution/ai.h>

namespace ipl {
    namespace snd {
        BOOL m_isLocked;

        void System::shutup(BOOL shutUpDMA) {
            if (m_isLocked == shutUpDMA) {
                return;
            }

            m_isLocked = shutUpDMA;
            if (shutUpDMA) {
                AIStopDMA();
            } else {
                AIStartDMA();
            }
        }
    }  // namespace snd
}  // namespace ipl
