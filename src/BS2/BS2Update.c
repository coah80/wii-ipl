#include "BS2/BS2Update.h"

#include <string.h>

static BS2UpdateEntry* pEntries;
static u32 EntriesCount;
static u32* pFlags;
static void* MemAllocator;
int State;
BS2UpdateEntry* CurrentEntry;
static u32 lbl_81698B10;
static BOOL lbl_81698B14;
static u32 lbl_81698B18;
static u32 lbl_81698B1C;
u32 StartUpdate;
u32 CancelUpdate;
static f32 UpdateProgress;
static s32 rc;
static u64 VersionIOS;
static u32 VersionMEM2;
static u32 VersionES;
static u32 ConsoleType;
static void* FatalFunc;

#pragma force_active on
char* getSuffix(const char* path) {
    char* suffix = strrchr(path, '.');
    if (suffix != NULL) {
        suffix++;
    }
    return suffix;
}
#pragma force_active off

int BS2UpdateState() {
    return State;
}

void BS2StartUpdate() {
    StartUpdate = 1;
}

void BS2CancelUpdate() {
    CancelUpdate = 1;
}

BS2UpdateEntry* BS2GetUpdateEntry() {
    return pEntries;
}

u32 BS2GetUpdateEntryNum() {
    return EntriesCount;
}

BS2UpdateEntry* BS2GetCurrentEntry() {
    return CurrentEntry;
}

BOOL BS2ContainsSeatTitles() {
    return lbl_81698B14;
}
