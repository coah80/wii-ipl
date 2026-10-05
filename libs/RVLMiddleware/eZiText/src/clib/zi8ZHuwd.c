#include <zi8clib/zierror.h>
#include <zi8clib/zitypes.h>

ziU32 Zi8GetZHuwdPtr(ziU32* entriesAddress, ziU16* entryCount ZI_NEED_WORK) {
    if (ZI_WORK->uwdPtrCount == 0) {
        *entriesAddress = 0;
        *entryCount = 0;
        Zi8LogError(0x1A5, ZI_WORK);
        return 0;
    } else {
        *entryCount = ZI_WORK->zhUwdPointers[ZI_WORK->uwdPtrCount - 1][1] / 3;
        *entriesAddress = (ziU32)ZI_WORK->zhUwdPointers[ZI_WORK->uwdPtrCount - 1];
        *entriesAddress += 8;
        Zi8LogError(0x64, ZI_WORK);
        return 1;
    }
}
