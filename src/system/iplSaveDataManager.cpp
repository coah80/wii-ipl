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

        int Manager::getNumValidChannel() const {
            const ChannelSlot* q;
            int dens = MAX_CHANNEL_INDEX;
            const ChannelPage* p;
            int slot;
            int count = 0;
            int page;
            u8 flag;
            s32 val;
            for (page = 0; page < MAX_CHANNEL_PAGE; page++) {
                p = (const ChannelPage*)((const u8*)this + page * 0xc0);
                for (slot = 0; slot < dens; slot++) {
                    q = &p->slots[slot];
                    flag = q->valid;
                    if (flag != 0) {
                        val = q->titleId;
                        if (val != 0) {
                            count++;
                        }
                    }
                }
            }
            return count;
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
            bool bNeedFlush = false;

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

                                            u8* data = (u8*)manager;
                                            u32* loopFileLen = &fileLen;
                                            volatile NETMD5Sum& md5Ref = md5;
                                            u32 i = 0;
                                            while (i < NET_MD5_DIGEST_SIZE) {
                                                u8 md5Byte = md5Ref[i];
                                                u32 offset = i;
                                                offset += *loopFileLen;
                                                u32 fileByte = *(u8*)(offset + (u32)data + NET_MD5_DIGEST_SIZE);
                                                if (md5Byte != fileByte) {
                                                    // Invalid MD5 sum, create new
                                                    bCreateNew = TRUE;
                                                    break;
                                                }
                                                i++;
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

            bool flush = bNeedFlush | manager->updateChanInfos();
            if (flush) {
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

            ESTitleId prioritizedTitleIds[MAX_CHANNEL_TOTAL] = {0};

            makePriorTitleIDList(prioritizedTitleIds, titleIds, titleCount);
            integrateTitleIDList(prioritizedTitleIds, titleIds, titleCount);

            delete[] titleIds;

            return doUpdateChanInfos(prioritizedTitleIds);
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

#pragma push
#pragma ppc_iro_level 0
        void Manager::makePriorTitleIDList(ESTitleId* titleIdsOut, ESTitleId* titleIdsIn, u32 titleCount) {
            int outputIndex;
            for (int page = 0; page < MAX_CHANNEL_PAGE; page++) {
                for (int index = 0; index < MAX_CHANNEL_INDEX; index++) {
                    if (mData.chanInfo[page][index].primaryType == channel::PRIMARY_TYPE_CHANNEL) {
                        outputIndex = index + page * MAX_CHANNEL_INDEX;
                        ESTitleId titleId = ES_TITLE_ID(mData.chanInfo[page][index].titleType, mData.chanInfo[page][index].titleCode);
                        for (u32 inputIndex = 0; inputIndex < titleCount; inputIndex++) {
                            if (titleIdsIn[inputIndex] == TITLE_NULL) {
                                continue;
                            }
                            if (titleIdsOut[outputIndex] != TITLE_NULL) {
                                titleId = titleIdsOut[outputIndex];
                            } else {
                                ESTitleId titleCode = TITLE_NO_REGION(titleId);
                                if (titleCode == TITLE_PHOTO || titleCode == TITLE_PHOTO_2 || titleCode == TITLE_PHOTO_2_CHECK) {
                                    if (titleCode != mPhotoId) {
                                        titleId = mPhotoId | TITLE_REGION_ALL;
                                    }
                                }
                            }
                            int match = isEqualChannel(titleId, titleIdsIn[inputIndex]);
                            if (match == -2 || match == 0) {
                                if (checkValidApp(titleId)) {
                                    titleIdsOut[outputIndex] = titleId;
                                }
                                titleIdsIn[inputIndex] = TITLE_NULL;
                            } else if (match == 1) {
                                if (checkValidApp(titleIdsIn[inputIndex])) {
                                    titleIdsOut[outputIndex] = titleIdsIn[inputIndex];
                                }
                                titleIdsIn[inputIndex] = TITLE_NULL;
                            }
                        }
                    }
                }
            }
        }
#pragma pop

        void Manager::integrateTitleIDList(ESTitleId* titleIdsOut, ESTitleId* titleIdsIn, u32 titleCount) {
            ESTitleId temporaryTitleIds[0x36] = {0};
            int availableCount = getAvailableNumInList(titleIdsOut, 0x30);
            if (availableCount != 0) {
                makeTmpList(temporaryTitleIds, availableCount, titleIdsIn, titleCount);
                moveTitleTmpToPrior(titleIdsOut, temporaryTitleIds);
            }
        }

        void Manager::makeTmpList(ESTitleId* titleIdsOut, u32 availableCount, ESTitleId* titleIdsIn, u32 titleCount) {
            int appendIndex = DEFAULT_CHANNEL_COUNT;
            u32 addedCount = 0;
            for (int inputIndex = 0; inputIndex < titleCount; inputIndex++) {
                if (titleIdsIn[inputIndex] != TITLE_NULL) {
                    if (checkValidApp(titleIdsIn[inputIndex])) {
                        int match = -1;
                        for (int outputIndex = 0; outputIndex < appendIndex; outputIndex++) {
                            match = isEqualChannel(titleIdsOut[outputIndex], titleIdsIn[inputIndex]);
                            if (match == -2 || match == 0) {
                                break;
                            }
                            if (match == 1) {
                                titleIdsOut[outputIndex] = titleIdsIn[inputIndex];
                                break;
                            }
                        }
                        if (match != -1) {
                            titleIdsIn[inputIndex] = TITLE_NULL;
                            continue;
                        }
                        int defaultIndex = isDefaultChannel(ES_TITLE_TYPE(titleIdsIn[inputIndex]), ES_TITLE_CODE(titleIdsIn[inputIndex]));
                        if (defaultIndex == -1) {
                            titleIdsOut[appendIndex++] = titleIdsIn[inputIndex];
                        } else {
                            titleIdsOut[defaultIndex] = titleIdsIn[inputIndex];
                        }
                        addedCount++;
                    }
                    titleIdsIn[inputIndex] = TITLE_NULL;
                    if (addedCount >= availableCount) {
                        break;
                    }
                }
            }
        }

        void Manager::moveTitleTmpToPrior(ESTitleId* titleIdsOut, const ESTitleId* titleIdsIn) {
            for (int titleIndex = 0; titleIndex < 0x36; titleIndex++) {
                if (titleIdsIn[titleIndex] != TITLE_NULL) {
                    int availableIndex = getAvailableInList(titleIdsOut, 0x30);
                    if (availableIndex == -1) {
                        return;
                    }
                    titleIdsOut[availableIndex] = titleIdsIn[titleIndex];
                }
            }
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

        int Manager::getAvailableInList(const ESTitleId* titleIds, u32 titleCount) {
            int dens = MAX_CHANNEL_INDEX;
            u32 i;
            for (i = 0; i < titleCount; i++) {
                if (titleIds[i] == 0) {
                    int page = (int)i / dens;
                    int slot = (int)i % dens;
                    u8* p = (u8*)this + page * 0xc0;
                    p += slot * 16;
                    if (*(p + 0x30) != 1) {
                        return (int)i;
                    }
                }
            }
            return -1;
        }

        int Manager::isEqualChannel(ESTitleId titleId0, ESTitleId titleId1) {
            if (titleId0 == titleId1) {
                return -2;
            }

            if (TITLE_NO_REGION(titleId0) == TITLE_NO_REGION(titleId1)) {
                if (TITLE_REGION(titleId0) != TITLE_REGION_ALL) {
                    if (TITLE_REGION(titleId1) == TITLE_REGION_ALL) {
                        return 0;
                    }
                }

                if (TITLE_REGION(titleId0) == TITLE_REGION_ALL) {
                    if (TITLE_REGION(titleId1) != TITLE_REGION_ALL) {
                        return 1;
                    }
                }

                return -1;
            }

            return -1;
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
                OSHalt("\0\0\0", 1344);
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

#ifdef __MWERKS__
        void Manager::pushTitleCache(ESTitleId titleId) {
            if (titleId == ES_TITLE_ID(TITLE_TYPE_CHANNEL, 'HATE') || titleId == ES_TITLE_ID(TITLE_TYPE_CHANNEL, 'HADE')) {
                return;
            }
            u32 titleType = ES_TITLE_TYPE_NOMASK(titleId);
            if (titleType != TITLE_TYPE_CHANNEL && titleType != TITLE_TYPE_UNK3 &&
                titleType != TITLE_TYPE_DISC_CHANNEL && titleType != TITLE_TYPE_UNK6) {
                return;
            }
            int index = 0;
            for (; index < MAX_CHANNEL_TOTAL; index++) {
                if ((&mData.titleCache[0][0])[index] == titleId) {
                    break;
                }
            }
            if (index == MAX_CHANNEL_TOTAL) {
                index = MAX_CHANNEL_TOTAL - 1;
            }
            for (; index > 0; index--) {
                u32 previousIndex = index - 1;
                (&mData.titleCache[0][0])[index] = (&mData.titleCache[0][0])[previousIndex];
            }
            mData.titleCache[0][0] = titleId;
        }

        extern "C" BOOL isTitleCached(void* manager, ESTitleId titleId) {
            Manager* savedataManager = static_cast<Manager*>(manager);
            for (int index = 0; index < MAX_CHANNEL_TOTAL; index++) {
                if (savedataManager->mData.titleCache[0][index] == titleId) {
                    return TRUE;
                }
            }
            return FALSE;
        }
#endif

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
