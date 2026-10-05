#ifndef REVOLUTION_KBD_H
#define REVOLUTION_KBD_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _KBDCountryCode {
    KBD_CC_INTERNATIONAL = 0,
    KBD_CC_CANADIAN_BI,
    KBD_CC_CANADIAN_FR,
    KBD_CC_DANISH,
    KBD_CC_FINNISH,
    KBD_CC_FRENCH,
    KBD_CC_GERMAN,
    KBD_CC_GREEK,
    KBD_CC_ITALIAN,
    KBD_CC_JAPANESE,
    KBD_CC_LATIN_AMERICAN,
    KBD_CC_NETHERLANDS_DUTCH,
    KBD_CC_NORWEGIAN,
    KBD_CC_PORTUGUESE,
    KBD_CC_SPANISH,
    KBD_CC_SWEDISH,
    KBD_CC_UNITED_KINGDOM,
    KBD_CC_UNITED_STATES,
    KBD_CC_RESERVED
} KBDCountryCode;

typedef struct _KBDKeyEvent {
#ifdef TIHKBMANAGER_IMPLEMENTATION
    u8 device;
    u8 key;
    u32 flags;
#else
    u8 eventData[32];
#endif
} KBDKeyEvent;

typedef struct _KBDDevEvent {
#ifdef TIHKBMANAGER_IMPLEMENTATION
    u8 device;
#else
    u8 eventData[32];
#endif
} KBDDevEvent;

#ifdef __cplusplus
}
#endif

#endif  // REVOLUTION_KBD_H
