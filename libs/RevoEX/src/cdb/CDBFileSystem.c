#include <private/cdb.h>
#include <revolution/cdb.h>

#include <private/nand.h>
#include <revolution/vf.h>

#include <string.h>

char CDB_WIIID_DAT_PATH[NAND_MAX_PATH];

char CDB_VFF_FILE_NAME[NAND_MAX_PATH];
u32 CDB_VFF_FILE_SIZE;

s32 CDBFSCreateDirNAND(const char* path, u8 perm, u8 attr) {
    s32 result;

    CDBReportInfo("NANDCreateDir %s\n", path);
    result = NANDCreateDir(path, perm, attr);
    if (result != NAND_RESULT_OK) {
        CDBReportInfo("NANDCreateDir() error = %d\n", result);
    }
    return result;
}

void CDBFSReportNANDPermission(u8 permission);

void CDBFSReportNANDStatus(const char* path) {
    NANDStatus status;
    s32 result;

    result = NANDPrivateGetStatus(path, &status);
    CDBReportInfo("NANDPrivateGetStatus %s = %d\n", path, result);
    if (result != NAND_RESULT_OK) {
        return;
    }

    CDBReportInfo("ownerId=%u, groupId=%u, attribute=%u, permission=", status.ownerId, status.groupId, status.attribute);
    CDBFSReportNANDPermission(status.permission);
}

void CDBFSReportNANDPermission(u8 permission) {
    char text[7];

    text[0] = (permission & NAND_PERM_BOTH_READ) ? 'r' : '-';
    text[1] = (permission & NAND_PERM_BOTH_WRITE) ? 'w' : '-';
    text[2] = (permission & NAND_PERM_GROUP_READ) ? 'r' : '-';
    text[3] = (permission & NAND_PERM_GROUP_WRITE) ? 'w' : '-';
    text[4] = (permission & NAND_PERM_USER_READ) ? 'r' : '-';
    text[5] = (permission & NAND_PERM_USER_WRITE) ? 'w' : '-';
    text[6] = '\0';
    CDBReportInfo(text);
    CDBReportInfo("(other-group-owner)\n");
}

void CDBFSReportWiiIdDat(void) {
    CDBFSReportNANDStatus("nocopy/cdbwiiid.dat");
}

// These ones are used but they are pooled somewhere else
static char mountError[] = "VFMountDriveNANDFlashEx VFErr=%d(%s)\n";
static char homeDirectory[] = "home=%s\n";
static char createFileError[] = "VFCreateSystemFileNANDFlashEx DEVErr=%d\n";
static char retryMountError[] = "VFMountDriveNANDFlashEx VFErr=%d\n";
static char formatError[] = "VFFormatDrive VFErr=%d\n";
static char mountSuccess[] = "VFMountDriveNANDFlashEx %s->%s succeeded\n";
static char changeDirectoryError[] = "VFChangeDir %s %s\n";

static inline CDBErr CDBFSInitVFFile(void* cacheBuffer, u32 cacheSize) {
    VFErr vfErr;
    s32 nandErr;

    vfErr = VFMountDriveNANDFlashCacheEx(CDB_CFG_VF_DRIVE_LETTER, CDB_VFF_FILE_NAME, cacheBuffer, cacheSize);
    if (vfErr != VF_ERR_SUCCESS) {
        CDBReportInfo(mountError, vfErr, VFGetApiErrorString(vfErr));

        if (vfErr == VF_ERR_NOT_EXIST_FILE) {
            u32 nandCheck;

            nandErr = NANDCheck(0x500, 1, &nandCheck);
            if (nandErr != NAND_RESULT_OK) {
                CDBReportFatal("failed NANDCheck\n");
                return CDBOnNANDErrorOccured(nandErr);
            }

            if (nandCheck != NAND_CHECK_SUCCESS) {
                if (nandCheck & NAND_CHECK_HOME_INSSPACE) {
                    CDBReportFatal("NANDCheck : NAND_CHECK_HOME_INSSPACE\n");
                }
                if (nandCheck & NAND_CHECK_HOME_INSINODE) {
                    CDBReportFatal("NANDCheck : NAND_CHECK_HOME_INSINODE\n");
                }
                if (nandCheck & NAND_CHECK_SYS_INSSPACE) {
                    CDBReportFatal("NANDCheck : NAND_CHECK_SYS_INSSPACE\n");
                }
                if (nandCheck & NAND_CHECK_SYS_INSINODE) {
                    CDBReportFatal("NANDCheck : NAND_CHECK_SYS_INSINODE\n");
                }
                return CDB_ERROR_OUT_OF_SPACE;
            }

            vfErr = VFCreateSystemFileNANDFlashEx(CDB_VFF_FILE_NAME, CDB_VFF_FILE_SIZE);
            if (vfErr != VF_ERR_SUCCESS) {
                char nandHomeDir[64];
                NANDGetHomeDir(nandHomeDir);

                CDBReportFatal(homeDirectory, nandHomeDir);
                CDBReportFatal(createFileError, vfErr);
                return CDBOnNANDErrorOccured(vfErr);
            }

            vfErr = VFMountDriveNANDFlashCacheEx(CDB_CFG_VF_DRIVE_LETTER, CDB_VFF_FILE_NAME, cacheBuffer, cacheSize);
            if (vfErr != VF_ERR_SUCCESS) {
                CDBReportFatal(retryMountError, vfErr);
                return CDBOnVFErrorOccured(vfErr);
            }

            vfErr = VFFormatDrive(CDB_CFG_VF_DRIVE_LETTER);
            if (vfErr != VF_ERR_SUCCESS) {
                CDBReportFatal(formatError, vfErr);
                return CDBOnVFErrorOccured(vfErr);
            }
        } else {
            CDBReportFatal(mountError, vfErr, VFGetApiErrorString(vfErr));
            return CDBOnVFErrorOccured(vfErr);
        }
    }

    CDBReportInfo(mountSuccess, CDB_VFF_FILE_NAME, CDB_CFG_VF_DRIVE_LETTER);

    vfErr = VFChangeDir(CDB_CFG_VF_DRIVE_ROOT "/");
    if (vfErr != VF_ERR_SUCCESS) {
        CDBReportFatal(changeDirectoryError, CDB_CFG_VF_DRIVE_ROOT "/", VFGetApiErrorString(vfErr));
        return CDBOnVFErrorOccured(vfErr);
    }

    return CDBSetVFSyncMode(0);
}

s32 CDBFSDeleteNAND(const char* path) {
    s32 result;

    CDBReportInfo("NANDPrivateDelete %s-->\n", path);
    result = NANDPrivateDelete(path);
    CDBReportInfo("NANDPrivateDelete=%d\n", result);
    CDBReportInfo("<--NANDPrivateDelete\n");
    return result;
}

CDBErr CDBFSInit(void* cacheBuffer, u32 cacheSize) {
    VFErr vfErr;
    s32 nandErr;

    strcpy(CDB_VFF_FILE_NAME, "/title/00000001/00000002/data/cdb.vff");
    CDB_VFF_FILE_SIZE = 0x1400000;

    strcpy(CDB_WIIID_DAT_PATH, "/title/00000001/00000002/data/nocopy/cdbwiiid.dat");

    return CDBFSInitVFFile(cacheBuffer, cacheSize);
}

CDBErr CDBFSUninit() {
    VFErr vfErr;

    vfErr = VFUnmountDriveForce(CDB_CFG_VF_DRIVE_LETTER);
    if (vfErr != VF_ERR_SUCCESS) {
        CDBReportFatal("VFUnmoutDrive err=%d:%s\n", vfErr, VFGetApiErrorString(vfErr));
        return CDBOnVFErrorOccured(vfErr);
    }

    return CDB_ERROR_OK;
}

char* CDBFindDataGetName(CDBFindData* findData) {
    if (findData->loc == CDB_FS_LOCATION_NAND) {
        return CDBFindDataGetNameVF(&findData->vf);
    } else {
        return CDBFindDataGetNameSD(&findData->sd);
    }
}

BOOL CDBFindDataIsDirectory(CDBFindData* findData) {
    if (findData->loc == CDB_FS_LOCATION_NAND) {
        return CDBFindDataIsDirectoryVF(&findData->vf);
    } else {
        return CDBFindDataIsDirectorySD(&findData->sd);
    }
}

BOOL CDBFindDataIsEnd(CDBFindData* findData) {
    if (findData->loc == CDB_FS_LOCATION_NAND) {
        return CDBFindDataIsEndVF(&findData->vf);
    } else {
        return CDBFindDataIsEndSD(&findData->sd);
    }
}

BOOL CDBFSIsExistFile(const char* fileName, CDBLocation location) {
    if (location == CDB_FS_LOCATION_NAND) {
        return CDBFSIsExistFileVF(fileName);
    } else {
        return CDBFSIsExistFileSD(fileName);
    }
}

void CDBFSFindFirstRoot(CDBFindData* findData, CDBLocation location) {
    CDBFSFindFirstRootEx(findData, location, NULL);
}

void CDBFSFindFirstRootEx(CDBFindData* findData, CDBLocation location, u64* wiiId) {
    char rootPath[256];

    findData->loc = location;
    CDBGenRootPath(rootPath, location, wiiId);
    findData->loc = location;

    CDBFSFindFirst(findData, rootPath, location);
}

void CDBFSFindFirst(CDBFindData* findData, const char* fileName, CDBLocation location) {
    findData->loc = location;
    if (findData->loc == CDB_FS_LOCATION_NAND) {
        CDBFSFindFirstVF(&findData->vf, fileName);
    } else {
        CDBFSFindFirstSD(&findData->sd, fileName);
    }
}

void CDBFSFindNext(CDBFindData* findData) {
    if (findData->loc == CDB_FS_LOCATION_NAND) {
        CDBFSFindNextVF(&findData->vf);
    } else {
        CDBFSFindNextSD(&findData->sd);
    }
}

void CDBFSFindClose(CDBFindData* findData) {
    if (findData->loc == CDB_FS_LOCATION_NAND) {
        CDBFSFindCloseVF(&findData->vf);
    } else {
        CDBFSFindCloseSD(&findData->sd);
    }
}

void CDBFSDeleteDir(char* dirName, CDBLocation location) {
    CDBReportInfo("CDBFSDeleteDir() %s\n", dirName);
    if (location == CDB_FS_LOCATION_NAND) {
        CDBFSDeleteDirVF(dirName);
    } else {
        CDBFSDeleteDirSD(dirName);
    }
}
