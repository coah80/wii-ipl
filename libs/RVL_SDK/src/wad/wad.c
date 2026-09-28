#include <private/es.h>
#include <private/os.h>
#include <revolution/wad.h>

typedef struct __attribute__((aligned(32))) WADStream {
    u32 words[0x30];
} WADStream;

typedef union WADVersionBuffer {
    WADHeader header;
    struct {
        u32 headerSize;
        union {
            ESTmdViewHeader tmd;
            ESTitleId backupTitleId;
            u8 bytes[0x80];
        } version;
    } data;
    u8 bytes[0x84];
} WADVersionBuffer;

static s32 WADOpenStream(WADLocation location, const char* path, WADStream* stream, u32, u32);
static s32 WADReadStream(WADStream* stream, void* buffer, u32 size, u32 offset);
static s32 WADCloseStream(WADStream* stream);
static s32 WAD_815C2F44(u32 headerSize, u32* headerInfo);
static s32 _WADGetTitleVer(WADHeader* header, u32, u32, u32 type, u32 headerInfo);

extern s32 ES_GetBoot2Version(u32* version);

s32 WADGetTitleVersionEx(char* path, ESTitleId* titleId, u16* titleVersion, WADLocation location, u32 offset) {
    WADStream stream ALIGN32;
    WADVersionBuffer versionBuffer;
    ESTitleId* backupTitleId;
    u32 headerInfo;
    u32 titleDataSize;
    s32 result;
    u32 titleDataOffset;
    BOOL streamOpened;
    u32 type;

    streamOpened = FALSE;
    titleDataOffset = 0;
    if (path == 0) {
        result = -3000;
    } else if ((offset & 0x3F) != 0) {
        result = -3007;
    } else {
        result = WADOpenStream(location, path, &stream, 0, 0);
        streamOpened = TRUE;
        if (result == 0) {
            result = WADReadStream(&stream, &versionBuffer.header, sizeof(WADHeader), offset);
            if (result == sizeof(WADHeader)) {
                type = WAD_815C2F44(versionBuffer.header.hdrSize, &versionBuffer.header.certSize);
                if (type == 0) {
                    result = -3001;
                } else if (((type == 2) && (versionBuffer.header.tmdSize == 0)) ||
                           ((type == 1) && (versionBuffer.header.ticketSize == 0))) {
                    result = -3002;
                    if (versionBuffer.header.certSize == 2) {
                        titleDataOffset = 0x60;
                    } else {
                        goto done;
                    }
                }

                if (titleDataOffset == 0) {
                    result = _WADGetTitleVer(&versionBuffer.header, 0, 0, type,
                                             versionBuffer.header.certSize);
                    if (result == 0) {
                        result = -3002;
                    } else {
                        titleDataOffset = result + 0x180;
                            result = WADReadStream(&stream, &versionBuffer.data.version.tmd,
                                               0x80, offset + titleDataOffset);
                        if (result == 0x80) {
                            result = 0;
                            if (titleId != 0) {
                                titleId[0] = versionBuffer.data.version.tmd.titleId;
                            }
                            if (titleVersion != 0) {
                                *titleVersion = versionBuffer.data.version.tmd.titleVersion;
                            }
                        } else {
                            result = -3005;
                        }
                    }
                } else {
                    result = WADReadStream(&stream, &versionBuffer.data.version.backupTitleId,
                                           0x20, offset + titleDataOffset);
                    if (result == 0x20) {
                        result = 0;
                        if (titleId != 0) {
                            *titleId = versionBuffer.data.version.backupTitleId;
                        }
                    } else {
                        result = -3005;
                    }
                }
            } else {
                result = -3005;
            }
        }
    }

done:
    if (streamOpened) {
        WADCloseStream(&stream);
    }
    return result;
}

s32 WADCheckImport(ESTitleId titleId, u32 titleVersion) {
    u16 installedVersion;
    s32 result;

    if (__OSInIPL && (titleId == 0x0001000248414141ULL) && (titleVersion == 0xFF00)) {
        return 0;
    }

    result = WADGetInstalledVersion(titleId, &installedVersion);
    if (result == -3002) {
        return 1;
    }
    if (result == 0) {
        if (__OSInIPL) {
            if (titleVersion > installedVersion) {
                return 1;
            }
        } else if (titleVersion >= installedVersion) {
            return 1;
        }
    }
    return 0;
}

s32 WADGetInstalledVersion(ESTitleId titleId, u16* version) {
    u32 installedVersion;
    u32 tmdSize;
    ESTmdView tmdView __attribute__((aligned(32)));
    s32 result;

    if (version == 0) {
        return -3000;
    }
    if (titleId == 1) {
        result = ES_GetBoot2Version(&installedVersion);
        if (result == 0) {
            *version = installedVersion;
        }
        return result;
    }

    result = ES_GetTmdView(titleId, 0, &tmdSize);
    if (result == -106) {
        return -3002;
    }
    if (result != 0) {
        return result;
    }
    if (tmdSize > sizeof(ESTmdView)) {
        return -3000;
    }
    result = ES_GetTmdView(titleId, &tmdView, &tmdSize);
    if (result == 0) {
        *version = tmdView.head.titleVersion;
    }
    return result;
}
