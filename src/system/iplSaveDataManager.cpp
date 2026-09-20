#include "system/iplSaveDataManager.h"

#include "system/iplChannelManager.h"

#include "iplSystem.h"

#include "iplUtility.h"

#include <revolution.h>
#include <revolution/sc.h>

#include <cstring>

#include "titledb.h"

#include "config.h"

extern "C" void _savegpr_14();
extern "C" void _restgpr_14();
extern "C" void _savegpr_26();
extern "C" void _restgpr_26();
extern "C" void _savegpr_16();
extern "C" void _restgpr_16();
extern "C" void _savegpr_28();
extern "C" void _restgpr_28();
extern "C" void _savegpr_20();
extern "C" void _restgpr_20();
extern "C" void _savegpr_22();
extern "C" void _restgpr_22();

namespace ipl {
    // clang-format off
    #define DISK_CHANNEL        CHANNEL_INFO(channel::PRIMARY_TYPE_DISK,    channel::SECONARY_TYPE_SYSTEM, SCENE_DISK_CHANNEL,   0)
    #define NIGAOE_CHANNEL      CHANNEL_INFO(channel::PRIMARY_TYPE_CHANNEL, channel::SECONARY_TYPE_SYSTEM, SCENE_NORMAL_CHANNEL, TITLE_NIGAOE_ALL)
    #define PHOTO_CHANNEL       CHANNEL_INFO(channel::PRIMARY_TYPE_CHANNEL, channel::SECONARY_TYPE_SYSTEM, SCENE_NORMAL_CHANNEL, TITLE_PHOTO_ALL)
    #define SHOPPING_CHANNEL    CHANNEL_INFO(channel::PRIMARY_TYPE_CHANNEL, channel::SECONARY_TYPE_SYSTEM, SCENE_NORMAL_CHANNEL, TITLE_SHOPPING_ALL)
    #define WEATHER_CHANNEL     CHANNEL_INFO(channel::PRIMARY_TYPE_CHANNEL, channel::SECONARY_TYPE_SYSTEM, SCENE_NORMAL_CHANNEL, TITLE_WEATHER_ALL)
    #define NEWS_CHANNEL        CHANNEL_INFO(channel::PRIMARY_TYPE_CHANNEL, channel::SECONARY_TYPE_SYSTEM, SCENE_NORMAL_CHANNEL, TITLE_NEWS_ALL)
    #define NO_CHANNEL          CHANNEL_INFO_NULL

    #define DEFAULT_CHANNEL_COUNT 6
    static const channel::SInfo cDefaultChanList/*[MAX_CHANNEL_PAGE][MAX_CHANNEL_INDEX]*/[MAX_CHANNEL_TOTAL] = {
        // Page 1
        //{
            /* =============================================================*/
            DISK_CHANNEL,   NIGAOE_CHANNEL, PHOTO_CHANNEL, SHOPPING_CHANNEL,
            /* =============================================================*/
            WEATHER_CHANNEL, NEWS_CHANNEL,   NO_CHANNEL,    NO_CHANNEL,
            /* =============================================================*/
            NO_CHANNEL,      NO_CHANNEL,     NO_CHANNEL,    NO_CHANNEL,
            /* =============================================================*/
        //},
        // Page 2
        //{
            /* =============================================================*/
            NO_CHANNEL,      NO_CHANNEL,     NO_CHANNEL,    NO_CHANNEL,
            /* =============================================================*/
            NO_CHANNEL,      NO_CHANNEL,     NO_CHANNEL,    NO_CHANNEL,
            /* =============================================================*/
            NO_CHANNEL,      NO_CHANNEL,     NO_CHANNEL,    NO_CHANNEL,
            /* =============================================================*/
        //},
        // Page 3
        //{
            /* =============================================================*/
            NO_CHANNEL,      NO_CHANNEL,     NO_CHANNEL,    NO_CHANNEL,
            /* =============================================================*/
            NO_CHANNEL,      NO_CHANNEL,     NO_CHANNEL,    NO_CHANNEL,
            /* =============================================================*/
            NO_CHANNEL,      NO_CHANNEL,     NO_CHANNEL,    NO_CHANNEL,
            /* =============================================================*/
        //},
        // Page 4
        //{
            /* =============================================================*/
            NO_CHANNEL,      NO_CHANNEL,     NO_CHANNEL,    NO_CHANNEL,
            /* =============================================================*/
            NO_CHANNEL,      NO_CHANNEL,     NO_CHANNEL,    NO_CHANNEL,
            /* =============================================================*/
            NO_CHANNEL,      NO_CHANNEL,     NO_CHANNEL,    NO_CHANNEL,
            /* =============================================================*/
        //},
    };
    // clang-format on

    static const char* csSavePath = "/title/00000001/00000002/data/iplsave.bin";

    namespace savedata {
        Manager::Manager(EGG::Heap* heap) {
            mpHeap = heap;
            mLastPrevPage = 0;
            mLastSDPrevPage = 0;
            mbBadSDPrevPage = true;

            mpFile = NULL;

            mpUpdatedFile = NULL;

            mbInit = false;

            mLastError = 0;
        }

        Manager::~Manager() {
            if (mpUpdatedFile) {
                delete mpUpdatedFile;
            }
        }

        void Manager::initManager() {
            mbInit = false;
            System::getTask3()->request(initManagerTask, this, NULL);
        }

        void Manager::setPrevPage(int prevPage) {
            mData.prevPage = prevPage;
        }

        void Manager::setChanInfo(int page, int index, const channel::SInfo& chanInfo) {
            mData.chanInfo[page][index] = chanInfo;
        }

        void Manager::setMemoSetting(const textinput::extend::savedata::MemoSetting& memoSetting) {
            mData.memoSetting = memoSetting;
        }

        nand::File* Manager::flushAsync(EGG::Heap* flushHeap) {
            int old = OSDisableInterrupts();

            NETMD5Sum md5;
            NETCalcMD5(md5, &mData, sizeof(mData) - NET_MD5_DIGEST_SIZE);
            memcpy(mData.MD5Sum, md5, NET_MD5_DIGEST_SIZE);

            nand::File* result = System::getNandManager()->writeAsync(flushHeap, csSavePath, &mData, sizeof(mData), NAND_PERM_USER);
            mpFile = result;

            OSRestoreInterrupts(old);

            return result;
        }

        BOOL Manager::isFinished(nand::File* file) {
            if (file->isFinished() || file->isFatalError()) {
                mpFile = NULL;
            }
            return file->isFinished();
        }

        asm ESTitleId Manager::hasChannel(register ESTitleId titleId, register int* outIndex, register int* outPage) const {
            nofralloc
            stwu r1, -0x30(r1)
            mflr r0
            stw r0, 0x34(r1)
            addi r11, r1, 0x30
            bl _savegpr_22
            li r0, -1
            and. r0, r5, r0
            beq hasChannel_L1
            li r10, -1
            li r9, -1
            b hasChannel_L2
        hasChannel_L1:
            li r10, -1
            li r9, 0
        hasChannel_L2:
            li r4, -0x100
            li r0, -1
            and r12, r10, r4
            li r31, 0
            and r11, r9, r0
            li r27, 0
            li r28, 0xc
        hasChannel_L3:
            add r0, r3, r27
            li r30, 0
            li r26, 0
            mtctr r28
        hasChannel_L4:
            add r22, r0, r26
            lbz r4, 0x30(r22)
            cmplwi r4, 3
            bne hasChannel_L5
            lwz r4, 0x3c(r22)
            lwz r29, 0x38(r22)
            and r23, r4, r10
            and r22, r29, r9
            xor r23, r6, r23
            xor r22, r5, r22
            or. r22, r23, r22
            beq hasChannel_L6
            and r22, r4, r12
            and r24, r6, r12
            and r23, r29, r11
            and r25, r5, r11
            xor r24, r22, r24
            xor r25, r23, r25
            or. r25, r24, r25
            bne hasChannel_L5
            clrlwi r25, r6, 0x18
            xori r25, r25, 0x41
            cmpwi r25, 0
            bne hasChannel_L5
        hasChannel_L6:
            cmpwi r7, 0
            beq hasChannel_L7
            stw r31, 0(r7)
        hasChannel_L7:
            cmpwi r8, 0
            beq hasChannel_L8
            stw r30, 0(r8)
        hasChannel_L8:
            mr r3, r29
            b hasChannel_L9
        hasChannel_L5:
            addi r30, r30, 1
            addi r26, r26, 0x10
            bdnz hasChannel_L4
            addi r31, r31, 1
            addi r27, r27, 0xc0
            cmpwi r31, 4
            blt hasChannel_L3
            li r4, 0
            li r3, 0
        hasChannel_L9:
            addi r11, r1, 0x30
            bl _restgpr_22
            lwz r0, 0x34(r1)
            mtlr r0
            addi r1, r1, 0x30
            blr
        }

        asm int Manager::getNumValidChannel() const {
            nofralloc
            li r9, 0
            li r10, 0
            li r4, 0
            li r0, 0xc
        getNumValidChannel_L1:
            add r8, r3, r4
            li r5, 0
            mtctr r0
        getNumValidChannel_L2:
            add r7, r8, r5
            lbz r6, 0x30(r7)
            cmpwi r6, 0
            beq getNumValidChannel_L3
            lwz r6, 0x34(r7)
            cmpwi r6, 0
            beq getNumValidChannel_L3
            addi r9, r9, 1
        getNumValidChannel_L3:
            addi r5, r5, 0x10
            bdnz getNumValidChannel_L2
            addi r10, r10, 1
            addi r4, r4, 0xc0
            cmpwi r10, 4
            blt getNumValidChannel_L1
            mr r3, r9
            blr
        }

        BOOL Manager::isResetAcceptable() {
            if (mpFile == NULL || mpFile->isFinished() || mpFile->isFatalError()) {
                return TRUE;
            } else {
                return FALSE;
            }
        }

        void Manager::initManagerTask(void* work) {
            Manager* manager = static_cast<Manager*>(work);
            s32 ret;

            u32 fileLen = sizeof(Data);
            BOOL bCreateNew = FALSE;
            BOOL bNeedFlush = FALSE;

            ES_SetUid(SYSMENU_TITLE_ID);

            if (manager->mpUpdatedFile == NULL) {
                NANDFileInfo fileInfo;
                ret = nand::wrapper::Open(csSavePath, &fileInfo, NAND_ACCESS_RW);

                if (manager->nand_error_handling(ret)) {
                    u32 fileLenCheck;
                    ret = nand::wrapper::GetLength(&fileInfo, &fileLenCheck);
                    manager->nand_error_handling(ret);

                    if (fileLenCheck == 0) {
                        // Create a new file if blank
                        bCreateNew = TRUE;
                    } else {
                        // Read header
                        ret = nand::wrapper::Read(&fileInfo, &manager->mData, 0x20);
                        manager->nand_error_handling(ret);

                        if (manager->mLastError == NAND_RESULT_AUTHENTICATION || manager->mLastError == NAND_RESULT_ECC_CRIT) {
                            // Access to file is broken, create new
                            ret = nand::wrapper::Delete(csSavePath);
                            manager->nand_error_handling(ret);
                            bCreateNew = TRUE;
                        } else {
                            if (manager->mData.version > SAVEDATA_VERSION) {
                                // Save data too high, create new
                                bCreateNew = TRUE;
                            } else {
                                if (!NAND_CHECK_MAGIC4(manager->mData.sig, 'R', 'I', 'P', 'L')) {
                                    // Signature incorrect, create new
                                    bCreateNew = TRUE;
                                } else {
                                    ret = nand::wrapper::GetLength(&fileInfo, &fileLen);
                                    if (ret != NAND_RESULT_OK || manager->mData.fileSize < 0x20 || manager->mData.fileSize > fileLen) {
                                        // Invalid filesize, create new
                                        bCreateNew = TRUE;
                                    } else {
                                        fileLen = manager->mData.fileSize;

                                        ret = nand::wrapper::Seek(&fileInfo, 0, NAND_SEEK_BEG);
                                        manager->nand_error_handling(ret);
                                        ret = nand::wrapper::Read(&fileInfo, &manager->mData, fileLen);
                                        manager->nand_error_handling(ret);

                                        if (manager->mLastError == NAND_RESULT_AUTHENTICATION || manager->mLastError == NAND_RESULT_ECC_CRIT) {
                                            // Access to file is broken, create new
                                            ret = nand::wrapper::Delete(csSavePath);
                                            manager->nand_error_handling(ret);
                                            bCreateNew = TRUE;
                                        } else {
                                            NETMD5Sum md5;
                                            NETCalcMD5(md5, &manager->mData, fileLen - NET_MD5_DIGEST_SIZE);

                                            for (int i = 0; i < NET_MD5_DIGEST_SIZE; i++) {
                                                if (md5[i] != manager->mData.MD5Sum[i]) {
                                                    // Invalid MD5 sum, create new
                                                    bCreateNew = TRUE;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    ret = nand::wrapper::Close(&fileInfo);
                    manager->nand_error_handling(ret);
                } else {
                    if (manager->mLastError == NAND_RESULT_NOEXISTS) {
                        // Create a new file if it does not exist
                        bCreateNew = TRUE;
                    } else {
                        // Otherwise something is wrong
                        IPLErrorLogAndDisplay(MESG_ERR_FILE, "NAND", manager->mLastError, 450);
                    }
                }

                if (bCreateNew) {
                    manager->setDefaultSaveData();
                    bNeedFlush = TRUE;
                } else {
                    u32 oldVersion = manager->mData.version;
                    if (oldVersion < SAVEDATA_VERSION) {
                        manager->updateVersion(SAVEDATA_VERSION, oldVersion);
                        bNeedFlush = TRUE;
                    }
                }

                // Previous page of ChannelSelect
                if (manager->mData.prevPage != 0) {
                    manager->mLastPrevPage = manager->mData.prevPage;
                    bNeedFlush = TRUE;
                    manager->mData.prevPage = 0;
                }

                // Prevous page on SDChannelSelect
                if (manager->mData.prevSDPage >= 0 && manager->mData.prevSDPage < 20) {
                    if (manager->mbBadSDPrevPage) {
                        manager->mLastSDPrevPage = manager->mData.prevSDPage;
                        manager->mbBadSDPrevPage = false;
                    }
                }
            }

            if (bNeedFlush | manager->updateChanInfos()) {
                if (manager->mpUpdatedFile) {
                    delete manager->mpUpdatedFile;
                }

                manager->mpUpdatedFile = manager->flushAsync(manager->mpHeap);
                manager->mpFile = NULL;
            }

            manager->mbInit = true;
        }

        void Manager::setDefaultSaveData() {
            setDefaultHeader();
            memcpy(mData.chanInfo, cDefaultChanList, MAX_CHANNEL_INFO_SIZE);
            setDefaultKeyboard();
            setDefaultTVRC();
            setDefaultSDMenu();

            for (int i = 0; i < 0x0C; i++) {
                mData.padding[i] = 0;
            }
        }

        void Manager::setDefaultHeader() {
            mData.sig[0] = 'R';
            mData.sig[1] = 'I';
            mData.sig[2] = 'P';
            mData.sig[3] = 'L';
            mData.fileSize = sizeof(mData);
            mData.version = SAVEDATA_VERSION;
            mData.prevPage = 0;
        }

        void Manager::setDefaultKeyboard() {
            mData.memoSetting.uRevisionAndType = 0x11;

            mData.memoSetting.uDictionary = 0xFA;
            mData.memoSetting.uPredictOnOff = 0x00;
            mData.memoSetting.uSignPage = 0x00;

            mData.memoSetting.uKeitaiUpperCaseJP = TRUE;
            mData.memoSetting.uKeitaiInputMode = 0x02;

            mData.memoSetting.uQwertyABC = FALSE;

            mData.memoSetting.uABCInputMode = 0x01;
            mData.memoSetting.uAIUInputMode = 0x00;

            mData.memoSetting.uNumLockOff = FALSE;

            mData.memoSetting.uReserve2 = 0x00;
            mData.memoSetting.uReserve3 = 0x00;
            mData.memoSetting.uReserve4 = 0x00;
        }

        void Manager::setDefaultTVRC() {
            mData.tvrcData[0] = 0;
            mData.tvrcData[1] = 0;
            mData.tvrcData[2] = 0;
            mData.tvrcData[3] = 0;
        }

        BOOL Manager::updateChanInfos() {
            u32 titleCount;
            ES_ListTitlesOnCard(NULL, &titleCount);

            u64* titleIds = new (mpHeap, -DEFAULT_ALIGN) u64[titleCount];

            s32 ret = ES_ListTitlesOnCard(titleIds, &titleCount);
            if (ret != ES_ERR_OK) {
                IPLErrorLogAndDisplay(MESG_ERR_FILE, "ES", ret, 637);
            }

            mbPhoto2 = false;
            mbPhoto2Check = false;
            mbPhotoMP3 = false;

            mPhotoId = TITLE_PHOTO;

            deleteInvalidTitle(titleIds, titleCount);
            checkSpecialTitles(titleIds, titleCount);
            checkTmpTitle(titleIds, titleCount);

            ESTitleId unk[MAX_CHANNEL_TOTAL] = {0};

            makePriorTitleIDList(unk, titleIds, titleCount);
            integrateTitleIDList(unk, titleIds, titleCount);

            delete[] titleIds;

            return doUpdateChanInfos(unk);
        }

        void Manager::deleteInvalidTitle(ESTitleId* titleIds, u32 titleCount) {
            for (int i = 0; i < titleCount; i++) {
                s32 ret;
                if ((ESTitleId32)ES_TITLE_TYPE(titleIds[i]) != TITLE_TYPE_CHANNEL &&
                    (ESTitleId32)ES_TITLE_TYPE(titleIds[i]) != TITLE_TYPE_SYSTEM_CHANNEL &&
                    (ESTitleId32)ES_TITLE_TYPE(titleIds[i]) != TITLE_TYPE_DISC &&
                    (ESTitleId32)ES_TITLE_TYPE(titleIds[i]) != TITLE_TYPE_DISC_CHANNEL &&
                    (ESTitleId32)ES_TITLE_TYPE(titleIds[i]) != TITLE_TYPE_UNK6 && (ESTitleId32)ES_TITLE_TYPE(titleIds[i]) != TITLE_TYPE_UNK3) {
                    titleIds[i] = TITLE_NULL;
                } else {
                    ESTmdView* tmd = NULL;
                    ret = utility::ESMisc::GetTmdView(mpHeap, titleIds[i], &tmd);
                    if (ret == ES_ERR_OK) {
                        if (tmd->contents[0].size == 0x40 && TITLE_NO_REGION(titleIds[i]) != TITLE_PHOTO) {
                            titleIds[i] = TITLE_NULL;
                        }
                    }
                    if (tmd) {
                        mpHeap->free(tmd);
                    }

                    if (TITLE_NO_REGION(titleIds[i]) == TITLE_PHOTO) {
                        ESTmdView* tmd = NULL;
                        ret = utility::ESMisc::GetTmdView(mpHeap, titleIds[i], &tmd);
                        if (ret == ES_ERR_OK && tmd->head.titleVersion == 65280) {
                            mbPhotoMP3 = true;
                        }
                        if (tmd) {
                            mpHeap->free(tmd);
                        }
                    } else if (TITLE_NO_REGION(titleIds[i]) == TITLE_PHOTO_2) {
                        if (checkValidApp(titleIds[i])) {
                            mbPhoto2 = true;
                        }
                    } else if (TITLE_NO_REGION(titleIds[i]) == TITLE_PHOTO_2_CHECK) {
                        if (checkValidApp(titleIds[i])) {
                            mbPhoto2Check = true;
                        }
                    }
                }
            }
        }

        void Manager::checkSpecialTitles(ESTitleId* titleIds, u32 titleCount) {
            if (mbPhoto2 || mbPhoto2Check) {
                for (int i = 0; i < titleCount; i++) {
                    if (titleIds[i]) {
                        ESTitleId titleIdNoRegion = TITLE_NO_REGION(titleIds[i]);
                        if (mbPhoto2 && mbPhoto2Check) {
                            if (titleIdNoRegion == TITLE_PHOTO) {
                                titleIds[i] = 0;
                            } else if (titleIdNoRegion == TITLE_PHOTO_2_CHECK) {
                                titleIds[i] = 0;
                            }
                        } else if (!mbPhoto2 && mbPhoto2Check) {
                            if (titleIdNoRegion == TITLE_PHOTO) {
                                titleIds[i] = 0;
                            }
                        } else if (mbPhoto2 && !mbPhoto2Check && mbPhotoMP3) {
                            if (titleIdNoRegion == TITLE_PHOTO) {
                                titleIds[i] = 0;
                            }
                        } else if (mbPhoto2 && !mbPhoto2Check && !mbPhotoMP3) {
                            if (titleIdNoRegion == TITLE_PHOTO_2) {
                                titleIds[i] = 0;
                            }
                        }
                    }
                }

                if (mbPhoto2 && mbPhoto2Check) {
                    mPhotoId = TITLE_PHOTO_2;
                } else if (!mbPhoto2 && mbPhoto2Check) {
                    mPhotoId = TITLE_PHOTO_2_CHECK;
                } else if (mbPhoto2 && !mbPhoto2Check && mbPhotoMP3) {
                    mPhotoId = TITLE_PHOTO_2;
                } else if (mbPhoto2 && !mbPhoto2Check && !mbPhotoMP3) {
                    mPhotoId = TITLE_PHOTO;
                }
            }
        }

        void Manager::checkTmpTitle(ESTitleId* titleIds, u32 titleCount) {
            bool foundTmp = false;

            ESTitleId tmpId = SCGetTmpTitleID();
            if (tmpId) {
                for (int i = 0; i < titleCount; i++) {
                    if (titleIds[i] == tmpId) {
                        titleIds[i] = 0;
                        foundTmp = true;
                    }
                }

                if (foundTmp) {
                    if (!checkValidApp(tmpId)) {
                        SCSetTmpTitleID(TITLE_NULL);
                        SCFlush();
                    }
                } else {
                    SCSetTmpTitleID(TITLE_NULL);
                    SCFlush();
                }
            }
        }

#ifdef __MWERKS__
        extern "C" int isEqualChannel__Q33ipl8savedata7ManagerFUxUx();
        extern "C" int checkValidApp__Q33ipl8savedata7ManagerFUx();
        extern "C" int getAvailableInList__Q33ipl8savedata7ManagerFPCUxUl();
        extern "C" int getAvailableNumInList__Q33ipl8savedata7ManagerFPCUxUl();
        extern "C" int isDefaultChannel__Q33ipl8savedata7ManagerFUlUl();
        extern "C" void makeTmpList__Q33ipl8savedata7ManagerFPUxUlPUxUl();
        extern "C" void moveTitleTmpToPrior__Q33ipl8savedata7ManagerFPUxPCUx();

        asm void Manager::makePriorTitleIDList(register ESTitleId* titleIdsOut, register ESTitleId* titleIdsIn, register u32 titleCount) {
            nofralloc
            stwu r1, -0x50(r1)
            mflr r0
            stw r0, 0x54(r1)
            addi r11, r1, 0x50
            bl _savegpr_14
            mr r15, r3
            mr r16, r4
            mr r17, r5
            mr r18, r6
            li r23, 0
            li r31, 0
            li r30, 0
            lis r26, 0x4841
            li r14, -0x100
            li r27, 0
        makePriorTitleIDList_L1:
            add r25, r15, r31
            li r22, 0
            li r29, 0
        makePriorTitleIDList_L2:
            add r3, r25, r29
            lbz r0, 0x30(r3)
            cmplwi r0, 3
            bne makePriorTitleIDList_L8
            lwz r21, 0x38(r3)
            add r24, r22, r30
            lwz r20, 0x3c(r3)
            li r19, 0
            li r28, 0
            b makePriorTitleIDList_L7C
        makePriorTitleIDList_L3:
            add r3, r17, r28
            lwzx r0, r17, r28
            lwz r3, 4(r3)
            or. r0, r3, r0
            beq makePriorTitleIDList_L7
            slwi r0, r24, 3
            add r4, r16, r0
            lwzx r3, r16, r0
            lwz r4, 4(r4)
            or. r0, r4, r3
            beq makePriorTitleIDList_L4
            mr r21, r3
            mr r20, r4
            b makePriorTitleIDList_L6
        makePriorTitleIDList_L4:
            li r0, -1
            lis r4, 1
            and r3, r20, r14
            addi r5, r26, 0x4100
            and r0, r21, r0
            addi r6, r4, 2
            xor r5, r3, r5
            xor r4, r0, r6
            or. r4, r5, r4
            beq makePriorTitleIDList_L5
            addi r5, r26, 0x5900
            xor r4, r0, r6
            xor r5, r3, r5
            or. r4, r5, r4
            beq makePriorTitleIDList_L5
            addi r5, r26, 0x5a00
            xoris r4, r0, 1
            xor r5, r3, r5
            or. r4, r5, r4
            bne makePriorTitleIDList_L6
        makePriorTitleIDList_L5:
            lwz r4, 0x4f8(r15)
            lwz r5, 0x4fc(r15)
            xor r0, r0, r4
            xor r3, r3, r5
            or. r0, r3, r0
            beq makePriorTitleIDList_L6
            ori r20, r5, 0x41
            mr r21, r4
        makePriorTitleIDList_L6:
            add r4, r17, r28
            lwzx r7, r17, r28
            lwz r8, 4(r4)
            mr r3, r15
            mr r6, r20
            mr r5, r21
            bl isEqualChannel__Q33ipl8savedata7ManagerFUxUx
            cmpwi r3, -2
            beq makePriorTitleIDList_L6A
            cmpwi r3, 0
            bne makePriorTitleIDList_L6B
        makePriorTitleIDList_L6A:
            mr r3, r15
            mr r6, r20
            mr r5, r21
            bl checkValidApp__Q33ipl8savedata7ManagerFUx
            cmpwi r3, 0
            beq makePriorTitleIDList_L6C
            slwi r0, r24, 3
            add r3, r16, r0
            stw r20, 4(r3)
            stwx r21, r16, r0
        makePriorTitleIDList_L6C:
            add r3, r17, r28
            stw r27, 4(r3)
            stwx r27, r17, r28
            b makePriorTitleIDList_L7
        makePriorTitleIDList_L6B:
            cmpwi r3, 1
            bne makePriorTitleIDList_L7
            add r4, r17, r28
            lwzx r5, r17, r28
            lwz r6, 4(r4)
            mr r3, r15
            bl checkValidApp__Q33ipl8savedata7ManagerFUx
            cmpwi r3, 0
            beq makePriorTitleIDList_L6D
            slwi r0, r24, 3
            add r5, r17, r28
            add r3, r16, r0
            lwzx r4, r17, r28
            lwz r0, 4(r5)
            stw r0, 4(r3)
            stw r4, 0(r3)
        makePriorTitleIDList_L6D:
            add r3, r17, r28
            stw r27, 4(r3)
            stwx r27, r17, r28
        makePriorTitleIDList_L7:
            addi r19, r19, 1
            addi r28, r28, 8
        makePriorTitleIDList_L7C:
            cmplw r19, r18
            blt makePriorTitleIDList_L3
        makePriorTitleIDList_L8:
            addi r22, r22, 1
            addi r29, r29, 0x10
            cmpwi r22, 0xc
            blt makePriorTitleIDList_L2
            addi r23, r23, 1
            addi r30, r30, 0xc
            cmpwi r23, 4
            addi r31, r31, 0xc0
            blt makePriorTitleIDList_L1
            addi r11, r1, 0x50
            bl _restgpr_14
            lwz r0, 0x54(r1)
            mtlr r0
            addi r1, r1, 0x50
            blr
        }

        asm void Manager::integrateTitleIDList(register ESTitleId* titleIdsOut, register ESTitleId* titleIdsIn, register u32 titleCount) {
            nofralloc
            stwu r1, -0x1d0(r1)
            mflr r0
            stw r0, 0x1d4(r1)
            addi r11, r1, 0x1d0
            bl _savegpr_28
            li r0, 0x36
            mr r28, r3
            mr r29, r4
            mr r30, r5
            mr r31, r6
            addi r4, r1, 4
            li r3, 0
            mtctr r0
        integrateTitleIDList_L1:
            stw r3, 4(r4)
            stwu r3, 8(r4)
            bdnz integrateTitleIDList_L1
            mr r3, r28
            mr r4, r29
            li r5, 0x30
            bl getAvailableNumInList__Q33ipl8savedata7ManagerFPCUxUl
            cmpwi r3, 0
            mr r5, r3
            beq integrateTitleIDList_L2
            mr r3, r28
            mr r6, r30
            mr r7, r31
            addi r4, r1, 8
            bl makeTmpList__Q33ipl8savedata7ManagerFPUxUlPUxUl
            mr r3, r28
            mr r4, r29
            addi r5, r1, 8
            bl moveTitleTmpToPrior__Q33ipl8savedata7ManagerFPUxPCUx
        integrateTitleIDList_L2:
            addi r11, r1, 0x1d0
            bl _restgpr_28
            lwz r0, 0x1d4(r1)
            mtlr r0
            addi r1, r1, 0x1d0
            blr
        }

        asm BOOL Manager::doUpdateChanInfos(register ESTitleId* titleIds) {
            nofralloc
            stwu r1, -0x40(r1)
            mflr r0
            stw r0, 0x44(r1)
            addi r11, r1, 0x40
            bl _savegpr_20
            mr r27, r3
            mr r28, r4
            li r3, 0
            li r30, 0
            li r26, 0
            li r25, 0
            li r20, 3
            li r21, 0
            li r22, 0xe
            li r23, -1
        doUpdateChanInfos_L1:
            add r31, r27, r26
            li r29, 0
            li r24, 0
        doUpdateChanInfos_L2:
            add r4, r31, r24
            lbz r0, 0x30(r4)
            cmplwi r0, 1
            beq doUpdateChanInfos_L5
            add r0, r29, r25
            lwz r9, 0x38(r4)
            slwi r0, r0, 3
            lwz r5, 0x3c(r4)
            add r8, r28, r0
            lwzx r6, r28, r0
            lwz r7, 4(r8)
            xor r0, r9, r6
            xor r5, r5, r7
            or. r0, r5, r0
            beq doUpdateChanInfos_L5
            or. r0, r7, r6
            bne doUpdateChanInfos_L4
            addi r3, r4, 0x30
            li r4, 0
            li r5, 0x10
            bl memset
            b doUpdateChanInfos_L6
        doUpdateChanInfos_L4:
            stb r20, 0x30(r4)
            stb r21, 0x31(r4)
            stb r21, 0x32(r4)
            stb r21, 0x33(r4)
            stw r22, 0x34(r4)
            lwz r0, 0(r8)
            and r0, r0, r23
            stw r0, 0x38(r4)
            lwz r0, 4(r8)
            and r0, r0, r23
            stw r0, 0x3c(r4)
        doUpdateChanInfos_L6:
            li r3, 1
        doUpdateChanInfos_L5:
            addi r29, r29, 1
            addi r24, r24, 0x10
            cmpwi r29, 0xc
            blt doUpdateChanInfos_L2
            addi r30, r30, 1
            addi r25, r25, 0xc
            cmpwi r30, 4
            addi r26, r26, 0xc0
            blt doUpdateChanInfos_L1
            addi r11, r1, 0x40
            bl _restgpr_20
            lwz r0, 0x44(r1)
            mtlr r0
            addi r1, r1, 0x40
            blr
        }

        asm void Manager::iplSavedata_813596B8(register ESTitleId titleId) {
            nofralloc
            lis r7, 0x4841
            lis r4, 1
            addi r0, r7, 0x5445
            addi r8, r4, 1
            xor r4, r6, r0
            xor r0, r5, r8
            or. r0, r4, r0
            beqlr
            addi r4, r7, 0x4445
            xor r0, r5, r8
            xor r4, r6, r4
            or. r0, r4, r0
            bne iplSavedata_813596B8_L1
            blr
        iplSavedata_813596B8_L1:
            addis r0, r5, -1
            cmplwi r0, 1
            beq iplSavedata_813596B8_L2
            cmplwi r0, 3
            beq iplSavedata_813596B8_L2
            cmplwi r0, 4
            beq iplSavedata_813596B8_L2
            cmplwi r0, 6
            bnelr
        iplSavedata_813596B8_L2:
            li r0, 0x30
            li r9, 0
            li r4, 0
            mtctr r0
        iplSavedata_813596B8_L3:
            add r7, r3, r4
            lwz r0, 0x340(r7)
            lwz r7, 0x344(r7)
            xor r0, r5, r0
            xor r7, r6, r7
            or. r0, r7, r0
            beq iplSavedata_813596B8_L4
            addi r9, r9, 1
            addi r4, r4, 8
            bdnz iplSavedata_813596B8_L3
        iplSavedata_813596B8_L4:
            cmpwi r9, 0x30
            bne iplSavedata_813596B8_L5
            li r9, 0x2f
        iplSavedata_813596B8_L5:
            slwi r4, r9, 3
            mtctr r9
            cmpwi r9, 0
            ble iplSavedata_813596B8_L6
        iplSavedata_813596B8_L7:
            addi r0, r9, -1
            add r7, r3, r4
            slwi r0, r0, 3
            addi r9, r9, -1
            add r8, r3, r0
            addi r4, r4, -8
            lwz r0, 0x340(r8)
            lwz r8, 0x344(r8)
            stw r8, 0x344(r7)
            stw r0, 0x340(r7)
            bdnz iplSavedata_813596B8_L7
        iplSavedata_813596B8_L6:
            stw r6, 0x344(r3)
            stw r5, 0x340(r3)
            blr
        }

        extern "C" asm BOOL iplSavedata_813597A0(register void* manager, register ESTitleId titleId) {
            nofralloc
            li r0, 0x30
            li r4, 0
            mtctr r0
        iplSavedata_813597A0_L1:
            add r7, r3, r4
            lwz r0, 0x340(r7)
            lwz r7, 0x344(r7)
            xor r0, r5, r0
            xor r7, r6, r7
            or. r0, r7, r0
            bne iplSavedata_813597A0_L2
            li r3, 1
            blr
        iplSavedata_813597A0_L2:
            addi r4, r4, 8
            bdnz iplSavedata_813597A0_L1
            li r3, 0
            blr
        }

        asm void Manager::makeTmpList(register ESTitleId* titleIdsOut, register u32 availableCount, register ESTitleId* titleIdsIn, register u32 titleCount) {
            nofralloc
            stwu r1, -0x50(r1)
            mflr r0
            stw r0, 0x54(r1)
            addi r11, r1, 0x50
            bl _savegpr_16
            mr r22, r3
            mr r23, r4
            mr r24, r5
            mr r25, r6
            mr r26, r7
            li r29, 6
            li r21, 0x30
            li r28, 0
            li r27, 0
            li r20, 0
            li r31, -1
            li r18, 0
            b makeTmpList_L8
        makeTmpList_L1:
            add r30, r25, r20
            lwzx r5, r25, r20
            lwz r6, 4(r30)
            or. r0, r6, r5
            beq makeTmpList_L7
            mr r3, r22
            bl checkValidApp__Q33ipl8savedata7ManagerFUx
            cmpwi r3, 0
            beq makeTmpList_L6
            li r3, -1
            li r16, 0
            li r19, 0
            b makeTmpList_L3
        makeTmpList_L2:
            add r17, r23, r19
            lwz r7, 0(r30)
            lwzx r5, r23, r19
            mr r3, r22
            lwz r6, 4(r17)
            lwz r8, 4(r30)
            bl isEqualChannel__Q33ipl8savedata7ManagerFUxUx
            cmpwi r3, -2
            beq makeTmpList_L5
            cmpwi r3, 0
            beq makeTmpList_L5
            cmpwi r3, 1
            bne makeTmpList_L4
            lwz r0, 0(r30)
            lwz r4, 4(r30)
            stw r4, 4(r17)
            stw r0, 0(r17)
            b makeTmpList_L5
        makeTmpList_L4:
            addi r16, r16, 1
            addi r19, r19, 8
        makeTmpList_L3:
            cmpw r16, r29
            blt makeTmpList_L2
        makeTmpList_L5:
            cmpwi r3, -1
            beq makeTmpList_L5B
            stw r18, 4(r30)
            stw r18, 0(r30)
            b makeTmpList_L7
        makeTmpList_L5B:
            lwz r0, 0(r30)
            mr r3, r22
            lwz r5, 4(r30)
            and r4, r0, r31
            and r5, r5, r31
            bl isDefaultChannel__Q33ipl8savedata7ManagerFUlUl
            cmpwi r3, -1
            bne makeTmpList_L5C
            lwz r0, 0(r30)
            add r3, r23, r21
            lwz r4, 4(r30)
            addi r29, r29, 1
            stw r4, 4(r3)
            stwx r0, r23, r21
            addi r21, r21, 8
            b makeTmpList_L5D
        makeTmpList_L5C:
            slwi r0, r3, 3
            lwz r4, 0(r30)
            lwz r5, 4(r30)
            add r3, r23, r0
            stw r5, 4(r3)
            stwx r4, r23, r0
        makeTmpList_L5D:
            addi r28, r28, 1
        makeTmpList_L6:
            stw r18, 4(r30)
            cmplw r28, r24
            stw r18, 0(r30)
            bge makeTmpList_L9
        makeTmpList_L7:
            addi r27, r27, 1
            addi r20, r20, 8
        makeTmpList_L8:
            cmplw r27, r26
            blt makeTmpList_L1
        makeTmpList_L9:
            addi r11, r1, 0x50
            bl _restgpr_16
            lwz r0, 0x54(r1)
            mtlr r0
            addi r1, r1, 0x50
            blr
        }

        asm void Manager::moveTitleTmpToPrior(register ESTitleId* titleIdsOut, register const ESTitleId* titleIdsIn) {
            nofralloc
            stwu r1, -0x20(r1)
            mflr r0
            stw r0, 0x24(r1)
            addi r11, r1, 0x20
            bl _savegpr_26
            mr r26, r3
            mr r27, r4
            mr r28, r5
            li r29, 0
            li r31, 0
        moveTitleTmpToPrior_L1:
            add r30, r28, r31
            lwzx r0, r28, r31
            lwz r3, 4(r30)
            or. r0, r3, r0
            beq moveTitleTmpToPrior_L2
            mr r3, r26
            mr r4, r27
            li r5, 0x30
            bl getAvailableInList__Q33ipl8savedata7ManagerFPCUxUl
            cmpwi r3, -1
            beq moveTitleTmpToPrior_L3
            slwi r0, r3, 3
            lwz r4, 4(r30)
            add r3, r27, r0
            lwz r0, 0(r30)
            stw r4, 4(r3)
            stw r0, 0(r3)
        moveTitleTmpToPrior_L2:
            addi r29, r29, 1
            addi r31, r31, 8
            cmpwi r29, 0x36
            blt moveTitleTmpToPrior_L1
        moveTitleTmpToPrior_L3:
            addi r11, r1, 0x20
            bl _restgpr_26
            lwz r0, 0x24(r1)
            mtlr r0
            addi r1, r1, 0x20
            blr
        }
#endif

        BOOL Manager::checkValidApp(ESTitleId titleId) {
            BOOL result = TRUE;

            u32 tikCount = 0;
            s32 ret = ES_GetTicketViews(titleId, NULL, &tikCount);
            if (ret < ES_ERR_OK || tikCount == 0) {
                return FALSE;
            }

            if (!utility::ESMisc::PrivateContentsExist(titleId)) {
                return FALSE;
            }

            ESTmdView* tmd = NULL;
            ret = utility::ESMisc::GetTmdView(mpHeap, titleId, &tmd);
            if (ret != ES_ERR_OK && ret != ES_ERR_NO_TMD_FILE_FOUND) {
                IPLErrorLogAndDisplay(MESG_ERR_FILE, "ES", ret, 1138);
            }

            if (ret == ES_ERR_NO_TMD_FILE_FOUND || utility::ESMisc::checkContentsNum(titleId, tmd)) {
                if (ret != ES_ERR_OK && ret != ES_ERR_NO_TMD_FILE_FOUND) {
                    IPLErrorLogAndDisplay(MESG_ERR_FILE, "ES", ret, 1149);
                }
                result = FALSE;
            }

            if (tmd) {
                mpHeap->free(tmd);
            }

            return result;
        }

        int Manager::getAvailableNumInList(const ESTitleId* titleIds, u32 titleCount) {
            int count = 0;
            for (int i = 0; i < titleCount; i++) {
                if (titleIds[i] == 0) {
                    count++;
                }
            }
            return count - 1;
        }

        asm int Manager::getAvailableInList(register const ESTitleId* titleIds, register u32 titleCount) {
            nofralloc
            li r8, 0
            li r6, 0
            li r7, 0xc
            mtctr r5
            cmplwi r5, 0
            ble getAvailableInList_L3
        getAvailableInList_L1:
            add r5, r4, r6
            lwzx r0, r4, r6
            lwz r5, 4(r5)
            or. r0, r5, r0
            bne getAvailableInList_L2
            divw r5, r8, r7
            mullw r0, r5, r7
            mulli r5, r5, 0xc0
            subf r0, r0, r8
            add r5, r3, r5
            slwi r0, r0, 4
            add r5, r5, r0
            lbz r0, 0x30(r5)
            cmplwi r0, 1
            beq getAvailableInList_L2
            mr r3, r8
            blr
        getAvailableInList_L2:
            addi r8, r8, 1
            addi r6, r6, 8
            bdnz getAvailableInList_L1
        getAvailableInList_L3:
            li r3, -1
            blr
        }

        asm int Manager::isEqualChannel(register ESTitleId titleId0, register ESTitleId titleId1) {
            nofralloc
            xor r3, r6, r8
            xor r0, r5, r7
            or. r0, r3, r0
            bne isEqualChannel_L1
            li r3, -2
            blr
        isEqualChannel_L1:
            li r3, -0x100
            li r0, -1
            and r9, r6, r3
            and r3, r8, r3
            and r4, r5, r0
            and r0, r7, r0
            xor r3, r9, r3
            xor r0, r4, r0
            or. r0, r3, r0
            bne isEqualChannel_L4
            clrlwi r3, r6, 0x18
            xori r0, r3, 0x41
            cmpwi r0, 0
            beq isEqualChannel_L2
            clrlwi r0, r8, 0x18
            xori r0, r0, 0x41
            cmpwi r0, 0
            bne isEqualChannel_L2
            li r3, 0
            blr
        isEqualChannel_L2:
            xori r0, r3, 0x41
            cmpwi r0, 0
            bne isEqualChannel_L3
            clrlwi r0, r8, 0x18
            xori r0, r0, 0x41
            cmpwi r0, 0
            beq isEqualChannel_L3
            li r3, 1
            blr
        isEqualChannel_L3:
            li r3, -1
            blr
        isEqualChannel_L4:
            li r3, -1
            blr
        }

        int Manager::isDefaultChannel(ESTitleId32 titleType, ESTitleId32 titleCode) {
            for (int i = 0; i < DEFAULT_CHANNEL_COUNT; i++) {
                if (cDefaultChanList[i].titleType == titleType && (cDefaultChanList[i].titleCode & 0xFFFFFF00) == (titleCode & 0xFFFFFF00)) {
                    return i;
                }
            }
            return -1;
        }

        void Manager::updateVersion(u32 newVersion, u32 oldVersion) {
            if ((newVersion & 0xFFFF0000) != (oldVersion & 0xFFFF0000)) {
                OSReport("[SaveDataManager] Invalid major version change %d -> %d\n", oldVersion >> 16, newVersion >> 16);
                OSHalt("", 1344);
            }
            mData.fileSize = sizeof(Data);
            mData.version = newVersion;

            switch (newVersion) {
                case 2: {
                    setDefaultKeyboard();
                    break;
                }
                case 3: {
                    switch ((u16)oldVersion) {
                        case 0:
                        case 1: {
                            setDefaultKeyboard();
                        }
                        case 2: {
                            setDefaultSDMenu();
                        }
                        default: {
                            break;
                        }
                    }
                    break;
                }
            }
        }

        void Manager::setDefaultSDMenu() {
            mData.didntGotoSDMenu = TRUE;
            memset(mData.titleCache, 0, sizeof(mData.titleCache));
            mData.prevSDPage = 0;
        }

        BOOL Manager::nand_error_handling(int code) {
            BOOL result = FALSE;

            mLastError = code;
            if (code >= NAND_RESULT_OK) {
                return TRUE;
            } else {
                switch (code) {
                    case NAND_RESULT_AUTHENTICATION:
                    case NAND_RESULT_NOEXISTS:
                    case NAND_RESULT_ECC_CRIT: {
                        break;
                    }
                    case NAND_RESULT_EXISTS: {
                        result = TRUE;
                        break;
                    }
                    case NAND_RESULT_CORRUPT: {
                        IPLErrorDisplay(MESG_ERR_NAND);
                        break;
                    }
                    case NAND_RESULT_OPENFD:
                    case NAND_RESULT_NOTEMPTY:
                    case NAND_RESULT_MAXFILES:
                    case NAND_RESULT_MAXFD:
                    case NAND_RESULT_MAXBLOCKS:
                    case NAND_RESULT_INVALID:
                    case NAND_RESULT_UNUSED_7:
                    default: {
                        IPLErrorLogAndDisplay(MESG_ERR_FILE, "NAND", code, 1503);
                        break;
                    }
                }
            }

            return result;
        }
    }  // namespace savedata
}  // namespace ipl
