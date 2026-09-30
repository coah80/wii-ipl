#ifndef PRIVATE_NWC24_MAIL_BOX_H
#define PRIVATE_NWC24_MAIL_BOX_H

#include <revolution/types.h>

#include <revolution/nwc24/NWC24Err.h>

#ifdef __cplusplus
extern "C" {
#endif

NWC24Err NWC24iOpenMBox();

NWC24Err NWC24iMBoxSetLastUIDL(u32 ctrlId, const char* uidl);

#ifdef __cplusplus
}
#endif

#endif  // PRIVATE_NWC24_MAIL_BOX_H
