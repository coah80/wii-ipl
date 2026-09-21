#include "utility/iplESMisc.h"
#include "BS2/BS2.h"

#include "system/iplSystem.h"
#include "system/iplErrorHandler.h"

#include <private/es.h>

#include <revolution/sc.h>

#include <private/nand.h>
#include <revolution/nand.h>

#include <private/os.h>

#include <revolution/nwc24/NWC24Dl.h>
#include <revolution/nwc24/NWC24Manage.h>

#include <cstring>

#include "config.h"

#define TMD_FILE "/title/00000001/00000002/data/tmds.sys"

namespace ipl {
    namespace utility {
// meh
#define ES_ERR_REPORT(msg, ...) OSReport("%s::%s: " msg "\n", __FILE__, __FUNCTION__, __VA_ARGS__);

        BOOL checkForNullTermination(char* str, u32 len);

        ESError ESMisc::GetTmdView(EGG::Heap* heap, ESTitleId titleId, ESTmdView** outTmdView) {
            ESTmdView* tmdView;
            u32 tmdViewSize = 0;

            ESError ret;

            ret = ES_GetTmdView(titleId, NULL, &tmdViewSize);
            if (ret < ES_ERR_OK) {
                OSReport("ESMisc::GetTmdView: ES_GetTmdView1 err %d\n", ret);
                *outTmdView = NULL;
                goto out;
            }

            tmdView = (ESTmdView*)heap->alloc(OSRoundUp32B(tmdViewSize), -DEFAULT_ALIGN);
            *outTmdView = tmdView;
            memset(tmdView, 0, OSRoundUp32B(tmdViewSize));

            ret = ES_GetTmdView(titleId, *outTmdView, &tmdViewSize);
            if (ret < ES_ERR_OK) {
                OSReport("ESMisc::GetTmdView: ES_GetTmdView2 err %d\n", ret);
                heap->free(*outTmdView);
                *outTmdView = NULL;
                goto out;
            }

        out:
            return ret;
        }

        ESError ESMisc::GetTicketViewList(EGG::Heap* heap, ESTitleId titleId, ESTicketView** outTicketViews, u32* outNumTicketViews) {
            ESTicketView* ticketViews;
            u32 numTicketViews = 0;

            ESError ret;

            ret = ES_GetTicketViews(titleId, NULL, &numTicketViews);
            if (ret < ES_ERR_OK) {
                OSReport("ESMisc::GetTicketViewList: ES_GetTicketViews1 err %d\n", ret);
                *outTicketViews = NULL;
                return ret;
            }

            if (outNumTicketViews) {
                *outNumTicketViews = numTicketViews;
            }

            if (numTicketViews == 0) {
                return ES_ERR_TICKET_NOT_FOUND;
            }

            ticketViews = (ESTicketView*)heap->alloc(OSRoundUp32B(numTicketViews * sizeof(ESTicketView)), -DEFAULT_ALIGN);
            *outTicketViews = ticketViews;

            ret = ES_GetTicketViews(titleId, ticketViews, &numTicketViews);
            if (ret < ES_ERR_OK) {
                OSReport("ESMisc::GetTicketViewList: ES_GetTicketViews2 err %d\n", ret);
                heap->free(*outTicketViews);
                *outTicketViews = NULL;
                return ret;
            }

            return ES_ERR_OK;
        }

        ESError ESMisc::GetTicketView(EGG::Heap* heap, ESTitleId titleId, ESTicketView* ticketView, int numTicketViews) {
            u32 inNumTicketViews = 0;
            ESTicketView* inTicketView = NULL;

            ESError ret;

            ret = GetTicketViewList(heap, titleId, &inTicketView, &inNumTicketViews);
            if (numTicketViews >= inNumTicketViews) {
                OSReport("ESMisc::GetTicketView: Invalid index %d\n", numTicketViews);
                ret = ES_ERR_TICKET_NOT_FOUND;
                goto out;
            }

            if (ret == ES_ERR_OK) {
                memcpy(ticketView, inTicketView + numTicketViews, sizeof(ESTicketView));
            }
        out:
            if (inTicketView != NULL) {
                heap->free(inTicketView);
            }
            return ret;
        }

        s32 ESMisc::PrivateContentsExist(ESTitleId titleId) {
            char path[96] ALIGN32;

            u32 usedBlocks = 0;
            u32 usedINodes = 0;

            ESError ret;

            sprintf(path, "/title/%08x/%08x/content", NANDTitleIdHi(titleId), NANDTitleIdLo(titleId));
            ret = NANDSecretGetUsage(path, &usedBlocks, &usedINodes);
            if (ret != NAND_RESULT_OK || usedINodes <= 2) {
                if (ret != NAND_RESULT_OK && ret != NAND_RESULT_NOEXISTS) {
                    OSReport("ESMisc::PrivateContentsExist: err %d\n", ret);
                }
                return 0;
            }

            return usedINodes - 2;
        }

        BOOL ESMisc::ContentExist(ESTmdView* tmdView, u32 contentIndex, s32* result) {
            u32 numContents;
            u32 contents[512] ALIGN32;

            ESTitleId titleId = tmdView->head.titleId;

            u32 i, cid;

            for (i = 0; i < tmdView->head.numContents; i++) {
                // Find CID of index
                if (contentIndex == tmdView->contents[i].index) {
                    cid = tmdView->contents[i].cid;
                    break;
                }
            }

            // Check if we have overflown.
            if (i == tmdView->head.numContents) {
                *result = 0;
                return FALSE;
            }

            // Get number of contents
            s32 ret = ES_ListTitleContentsOnCard(titleId, NULL, &numContents);
            if (ret != ES_ERR_OK) {
                OSReport("ESMisc::ContentExist: ES_ListTitleContentsOnCard1 err %d\n", ret);
                if (result) {
                    *result = ret;
                }
                return FALSE;
            }

            // Get list of CIDs
            ret = ES_ListTitleContentsOnCard(titleId, contents, &numContents);
            if (ret != ES_ERR_OK) {
                OSReport("ESMisc::ContentExist: ES_ListTitleContentsOnCard2 err %d\n", ret);
                if (result) {
                    *result = ret;
                }
                return FALSE;
            }

            // For each CID
            for (int j = 0; j < numContents; j++) {
                // Compare...
                if (cid == contents[j]) {
                    // We got it!
                    if (result) {
                        *result = 0;
                    }
                    return TRUE;
                }
            }

            // We don't got it...
            if (result) {
                *result = 0;
            }
            return FALSE;
        }

        ESError ESMisc::checkContentsNum(ESTitleId titleId, ESTmdView* tmdView) {
            u32 numContents = 0;
            ESContentId contentIds[ES_MAX_CONTENT] ALIGN32;

            s32 privateCount = PrivateContentsExist(titleId);

            if (privateCount == 0) {
                OSReport("ESMisc::checkContentsNum: no TMD or content for 0x%016llx.\n", titleId);
                return 1;
            } else {
                u16 num = tmdView->head.numContents;
                u32 count = 0;

                for (u32 i = 0; i < num; i++) {
                    if ((tmdView->contents[i].type & 0x8000) == 0) {
                        count++;
                    }
                }

                if (privateCount == count) {
                    return 0;
                } else {
                    ESError err = ES_ListTitleContentsOnCard(titleId, NULL, &numContents);

                    if (err != ES_ERR_OK) {
                        OSReport("ESMisc::checkContentsNum: ES_ListTitleContentsOnCard err %d\n", err);
                        return err;
                    } else if (numContents == 0) {
                        OSReport("ESMisc::checkContentsNum: no content for 0x%016llx.\n", titleId);
                        return 1;
                    } else {
                        err = ES_ListTitleContentsOnCard(titleId, contentIds, &numContents);

                        if (err == ES_ERR_OK) {
                            bool found = false;

                            for (u32 i = 0; i < numContents && !found; i++) {
                                u32 j = 0;
                                while (j < tmdView->head.numContents) {
                                    if (contentIds[i] == tmdView->contents[j].cid && (tmdView->contents[j].type & 0x8000) == 0) {
                                        found = true;
                                        break;
                                    }
                                    j++;
                                }
                            }

                            if (!found) {
                                OSReport("ESMisc::checkContentsNum: 0x%016llx is already deleted.\n", titleId);
                                return 1;
                            } else {
                                u32 k;
                                for (u32 j = 0; j < num; j++) {
                                    k = 0;
                                    for (u32 i = 0; i < numContents; i++) {
                                        if (contentIds[i] == tmdView->contents[j].cid) {
                                            break;
                                        }
                                        k++;
                                    }
                                    if (k == numContents && (tmdView->contents[j].type & 0x4000) == 0) {
                                        OSReport("ESMisc::checkContentsNum: not complete: non-optional cidx %d missing for 0x%016llx.\n",
                                                 tmdView->contents[j].index, titleId);
                                        return 2;
                                    }
                                }
                                OSReport("ESMisc::checkContentsNum: complete: only missing non-optional contents for 0x%016llx.\n", titleId);
                                return 0;
                            }
                        } else {
                            OSReport("ESMisc::checkContentsNum: ES_ListTitleContentsOnCard failed.[%d]\n", err);
                            return err;
                        }
                    }
                }
            }
        }

        ESError ESMisc::GetValidTicketIndex(EGG::Heap* heap, ESTitleId titleId, ESTicketView* ticket, u32 ticketLength) {
            s32 index;
            bool allocated = false;
            bool found = false;
            ESTicketView* ticketView;

            if (ticket == NULL) {
                if (GetTicketViewList(heap, titleId, &ticket, &ticketLength) < 0) {
                    if (ticket != NULL) {
                        heap->free(ticket);
                    }
                    return 0;
                }
                allocated = true;
            }

            ticketView = (ESTicketView*)heap->alloc(0xe0, -32);

            if (ESP_InitLib() < 0) {
                goto error;
            }

            index = __OSGetValidTicketIndex(ticket, ticketLength);

            if (index < -1) {
                goto error;
            }

            if (index == -1) {
                index = 0;
            }

            memcpy(ticketView, (u8*)ticket + index * 0xd8, 0xd8);

            {
                ESFd fd = ES_OpenTitleContentFile(titleId, ticketView, 0);

                if (fd < 0) {
                    OSReport("ESMisc::GetValidTicketIndex: ES_OpenTitleContentFile fd %d\n", fd);
                } else {
                    char* buf = (char*)heap->alloc(0x40, -32);
                    u32 numRead = ES_ReadContentFile(fd, buf, 0x40);

                    if (numRead != 0x40) {
                        OSReport("ESMisc::GetValidTicketIndex: ES_ReadContentFile err %d\n", numRead);
                        heap->free(buf);

                        if (ES_CloseContentFile(fd) < 0) {
                            goto error;
                        }
                    } else {
                        if (ES_CloseContentFile(fd) < 0) {
                            heap->free(buf);
                            goto error;
                        }

                        if (buf[0] == 0) {
                            OSReport("ESMisc::GetValidTicketIndex: No name\n");
                            heap->free(buf);
                        } else {
                            heap->free(buf);
                            found = true;
                        }
                    }
                }
            }

            heap->free(ticketView);

            if (allocated && ticket != NULL) {
                heap->free(ticket);
            }

            return found ? index : -1;

        error:
            heap->free(ticketView);

            if (allocated && ticket != NULL) {
                heap->free(ticket);
            }

            System::getErrorHandler()->set(ErrorHandler::DEFAULT, MESG_ERR_FILE);
            return 0;
        }

        // DeleteSharedContent did not survive
        DECOMP_FORCE_ACTIVE(iplESMisc_cpp, "DeleteSharedContent: MEMAllocate for TMD err\n");
        DECOMP_FORCE_ACTIVE(iplESMisc_cpp, "DeleteSharedContent: ES_ListSharedContents1 err %d\n");
        DECOMP_FORCE_ACTIVE(iplESMisc_cpp, "DeleteSharedContent: MEMAllocate for SHA-1 hash err\n");
        DECOMP_FORCE_ACTIVE(iplESMisc_cpp, "DeleteSharedContent: ES_ListSharedContents2 err %d\n");
        DECOMP_FORCE_ACTIVE(iplESMisc_cpp, "DeleteSharedContent: ES_ListTitlesOnCard1 err %d\n");
        DECOMP_FORCE_ACTIVE(iplESMisc_cpp, "DeleteSharedContent: MEMAllocate for Title List err\n");
        DECOMP_FORCE_ACTIVE(iplESMisc_cpp, "DeleteSharedContent: MEMAllocate for Title List err\n");
        DECOMP_FORCE_ACTIVE(iplESMisc_cpp, "DeleteSharedContent: ES_ListTitlesOnCard2 err %d\n");
        DECOMP_FORCE_ACTIVE(iplESMisc_cpp, "DeleteSharedContent: ES_GetTmd1 err %d\n");
        DECOMP_FORCE_ACTIVE(iplESMisc_cpp, "DeleteSharedContent: ES_GetTmd2 err %d\n");
        DECOMP_FORCE_ACTIVE(iplESMisc_cpp, "DeleteSharedContent: ES_DeleteSharedContent err %d\n");

        BOOL ESMisc::IsLastTicketExpired(ESTitleId* titleId) {
            s32 ret;
            NANDFileInfo file;
            ESTitleId readTitleId ALIGN32;

            if (BS2GetBootType() != 1) {
                DeleteExpiredFlagFile();
                return FALSE;
            }

            ret = NANDPrivateOpen("/shared2/expired", &file, NAND_ACCESS_READ);
            if (ret == NAND_RESULT_NOEXISTS) {
                return FALSE;
            }

            if (ret != NAND_RESULT_OK) {
                return FALSE;
            }

            s32 read = NANDRead(&file, &readTitleId, OSRoundUp32B(sizeof(readTitleId)));
            NANDClose(&file);
            if (read != (s32)OSRoundUp32B(sizeof(readTitleId))) {
                return FALSE;
            }

            if (titleId) {
                *titleId = readTitleId;
            }
            return TRUE;
        }

        void ESMisc::DeleteExpiredFlagFile() {
            NANDPrivateDelete("/shared2/expired");
        }

        u32 ESMisc::CheckTmdCountryCode(ESTmdView* tmdView) {
            return __OSCheckTmdCountryCode(tmdView);
        }

        // Copied from BS2
        BOOL ESMisc::__IsPCEnable() {
            switch (SCGetProductArea()) {
                case SC_PRODUCT_AREA_JPN:
                case SC_PRODUCT_AREA_USA:
                case SC_PRODUCT_AREA_EUR:
                case SC_PRODUCT_AREA_AUS:
                case SC_PRODUCT_AREA_TWN:
                case SC_PRODUCT_AREA_KOR: {
                    return TRUE;
                }
                default: {
                    return FALSE;
                }
            }
        }

        u32 ESMisc::CheckTmdParentalControl(ESTmdView* tmdView) {
            if (!__IsPCEnable()) {
                return TRUE;
            }

            u8 ratings[16];
            memcpy(ratings, tmdView->head.reserved.ratings, 16);

            SCParentalControlsInfo pcInfo;
            if (!SCGetParentalControl(&pcInfo)) {
                return TRUE;
            }

            if (pcInfo.enable & SC_PARENTAL_FLAG_ENABLED) {
                u8 rating = ratings[pcInfo.org];

                if (rating & SC_PARENTAL_FLAG_ENABLED) {
                    return FALSE;
                }

                if (rating & 0x40) {
                    return FALSE;
                }

                if ((rating & SC_PARENTAL_RATING_ENABLED) > pcInfo.rating) {
                    return FALSE;
                }
            }

            return TRUE;
        }

        ESError ESMisc::NumPrivateContents(EGG::Heap* heap, ESTitleId titleId) {
            ESError ret;
            ESContentId* contentIds = NULL;
            ESTmdView* tmdView = NULL;
            u32 numContents;
            u32 tmdViewSize;

            ret = ES_GetTmdView(titleId, NULL, &tmdViewSize);
            if (ret == ES_ERR_DONT_EXISTS) {
                return ES_ERR_OK;
            }

            if (ret < ES_ERR_OK) {
                ES_ERR_REPORT("ES_GetTmdView1 failed: %d", ret);
                goto out;
            }

            ret = ES_ListTitleContentsOnCard(titleId, NULL, &numContents);
            if (ret != ES_ERR_OK) {
                ES_ERR_REPORT("ES_ListTitleContentsOnCard1 failed: %d for %016llx", ret, titleId);
                goto out;
            }

            if (numContents == 0) {
                return ES_ERR_OK;
            }

            tmdView = (ESTmdView*)heap->alloc(OSRoundUp32B(tmdViewSize), -DEFAULT_ALIGN);
            contentIds = (ESContentId*)heap->alloc(OSRoundUp32B(numContents * sizeof(ESContentId)), -DEFAULT_ALIGN);

            ret = ES_ListTitleContentsOnCard(titleId, contentIds, &numContents);
            if (ret != ES_ERR_OK) {
                ES_ERR_REPORT("ES_ListTitleContentsOnCard2 failed: %d for %016llx", ret, titleId);
                goto out;
            }

            ret = ES_GetTmdView(titleId, tmdView, &tmdViewSize);
            if (ret < ES_ERR_OK) {
                ES_ERR_REPORT("ES_GetTmdView2 failed: %d", ret);
                goto out;
            }

            ret = 0;
            u32 i = 0;
            u32 j = 0;
            ESCmdView* content = tmdView->contents;
            for (; i < tmdView->head.numContents && j < numContents; i++, content++) {
                if (content->cid == contentIds[j]) {
                    if (!(content->type & 0x8000)) {
                        ret++;
                    }
                    j++;
                }
            }

        out:
            if (contentIds != NULL) {
                heap->free(contentIds);
            }
            if (tmdView != NULL) {
                heap->free(tmdView);
            }

            return ret;
        }

        BOOL ESMisc::ChangeUid(ESTitleId titleId) {
            s32 ret = ES_SetUid(titleId);
            if (ret != ES_ERR_OK) {
                OSReport("ES_SetUid failed[%d]: 0x%016llx\n", ret, titleId);
                return FALSE;
            }

            // Reinitialize FS library
            ISFS_CloseLib();
            ISFS_OpenLib();

            return TRUE;
        }

        u32 ESMisc::NumInodesSaveDirRoot(ESTitleId titleId) {
            s32 ret;
            s32 result = -1;
            bool changedUid = false;

            if (ChangeUid(titleId)) {
                changedUid = true;

                char path[64] ALIGN32;
                snprintf(path, sizeof(path), "/title/%08x/%08x/data", NANDTitleIdHi(titleId), NANDTitleIdLo(titleId));

                u32 nodes;
                ret = NANDPrivateReadDir(path, NULL, &nodes);

                if (ret != NAND_RESULT_OK) {
                    ES_ERR_REPORT("NANDReadDir failed: %d", ret);
                    result = ret;
                    goto out;
                }

                result = nodes;
            }
        out:
            if (changedUid) {
                ChangeUid(SYSMENU_TITLE_ID);
            }
            return result;
        }

        s32 ESMisc::CheckSafeDeleteTitle(EGG::Heap* heap, ESTitleId titleId) {
            s32 result;
            ESTmdView* tmdView = NULL;
            u32 tmdViewSize;

            if (PrivateContentsExist(titleId) != 0) {
                ES_ERR_REPORT("%016llx is not empry", titleId);
                result = 0;
            } else {
                result = NumPrivateContents(heap, titleId);

                if (result < 0) {
                    ES_ERR_REPORT("NumPrivateContents failed: %d", result);
                } else if (result > 0) {
                    result = 0;
                } else {
                    result = ES_GetTmdView(titleId, NULL, &tmdViewSize);

                    if (result == ES_ERR_DONT_EXISTS) {
                        result = ES_ERR_OK;
                    } else if (result != ES_ERR_OK) {
                        ES_ERR_REPORT("ES_GetTmdView1 failed: %d", result);
                    } else {
                        tmdView = (ESTmdView*)heap->alloc(OSRoundUp32B(tmdViewSize), -DEFAULT_ALIGN);
                        result = ES_GetTmdView(titleId, tmdView, &tmdViewSize);

                        if (result != ES_ERR_OK) {
                            ES_ERR_REPORT("ES_GetTmdView2 failed: %d", result);
                        } else if ((tmdView->head.titleVersion >> 8) != 0) {
                            result = 0;
                        } else {
                            result = NumInodesSaveDirRoot(titleId);

                            if (result < 0) {
                                ES_ERR_REPORT("NumInodesSaveDirRoot failed: %d", result);
                            } else {
                                result = __rlwnm(1, __cntlzw(result), 31, 31);
                            }
                        }
                    }
                }
            }

            if (tmdView != NULL) {
                heap->free(tmdView);
            }

            return result;
        }

        s32 ESMisc::DeleteTitle(EGG::Heap* heap, ESTitleId titleId) {
            TMDFile tmdFile(heap);

            s32 ret = tmdFile.Open((char*)TMD_FILE);
            if (ret != ES_ERR_OK) {
                ES_ERR_REPORT("Open TMD Backup file failed: %d", ret);
                goto do_proc;
            }

            ret = tmdFile.Backup(titleId);
            if (ret != ES_ERR_OK) {
                ES_ERR_REPORT("Backup TMD failed: %d", ret);
                goto do_proc;
            }
        do_proc:
            ret = ES_DeleteTitle(titleId);
            if (ret != ES_ERR_OK) {
                ES_ERR_REPORT("ES_DeleteTitle failed: %d for %016llx", ret, titleId);
            }
            tmdFile.Close();
            return ret;
        }

        s32 ESMisc::DeleteEmptyTitles(EGG::Heap* heap) {
            u32 titleCount;
            ESTitleId* titleIds = NULL;
            s32 ret = ES_ListTitlesOnCard(NULL, &titleCount);

            if (ret != ES_ERR_OK) {
                ES_ERR_REPORT("ES_ListTitlesOnCard1 failed: %d", ret);
            } else if (titleCount != 0) {
                titleIds = (ESTitleId*)heap->alloc(OSRoundUp32B(titleCount * sizeof(ESTitleId)), -DEFAULT_ALIGN);
                ret = ES_ListTitlesOnCard(titleIds, &titleCount);

                if (ret != ES_ERR_OK) {
                    ES_ERR_REPORT("ES_ListTitlesOnCard2 failed: %d", ret);
                } else {
                    ESTitleId titleId;
                    for (u32 i = 0; i < titleCount; i++) {
                        titleId = titleIds[i];

                        if (NANDTitleIdHi(titleId) != 1) {
                            ret = CheckSafeDeleteTitle(heap, titleId);
                            if (ret < 0) {
                                ES_ERR_REPORT("CheckSafeDeleteTitle failed: %d", ret);
                            }

                            if (ret > 0) {
                                ret = DeleteTitle(heap, titleId);
                                if (ret < 0) {
                                    ES_ERR_REPORT("DeleteTitle failed: %d", ret);
                                }
                            }
                        }
                    }
                }
            }

            if (titleIds != NULL) {
                heap->free(titleIds);
            }

            TMDFile tmdFile(heap);
            ret = tmdFile.Open((char*)TMD_FILE);
            if (ret != ES_ERR_OK) {
                ES_ERR_REPORT("TMDFile::Open failed: %d", ret);
            }
            tmdFile.Close();
            tmdFile.Close();
            return ret;
        }

        s32 ESMisc::DeleteMetaContent(ESTitleId titleId) {
            char metaPath[64] = "";
            snprintf(metaPath, sizeof(metaPath), "/meta/%08x/%08x/title.met", NANDTitleIdHi(titleId), NANDTitleIdLo(titleId));
            return NANDPrivateDelete(metaPath);
        }

        static s32 DeleteDownloadTask(EGG::Heap* heap, u32 titleId) {
            void* nwc24Work = heap->alloc(NWC24_LIB_WORK_SIZE, 0x20);
            OSTick startTick = OSGetTick();
            s32 ret;
            NWC24DlId dlId;
            NWC24DlTask dlTask;
            u32 dlAppId;
            NWC24Err err;

            goto open_lib;
            while (true) {
                OSReport("%s::%s waiting NWC24Open.\n", __FILE__, __FUNCTION__);
                OSSleepTicks(OSMillisecondsToTicks((OSTime)30));
                if (OSTicksToMilliseconds(OSGetTick() - startTick) > 3000) {
                    ret = -0x1a;
                    OSReport("%s::%s NWC24Open failed with time out.\n", __FILE__, __FUNCTION__);
                    goto cleanup;
                }

            open_lib:
                if (NWC24OpenLib(nwc24Work) != NWC24_OK) {
                    continue;
                }

                dlId = 0;
                err = NWC24IterateDlTask(&dlId, TRUE);
                while (err >= NWC24_OK) {
                    err = NWC24GetDlTask(&dlTask, dlId);
                    if (err != NWC24_OK) {
                        OSReport("%s::%s NWC24GetDlTask failed - [%d]  -> continue\n", __FILE__, __FUNCTION__, err);
                    } else {
                        err = NWC24GetDlAppId(&dlTask, &dlAppId);
                        if (err != NWC24_OK) {
                            OSReport("%s::%s NWC24GetDlAppId failed - [%d]  -> continue\n", __FILE__, __FUNCTION__, err);
                        } else if (dlAppId == titleId) {
                            OSReport("%s::%s found dl task owned same titleid [%p]\n", __FILE__, __FUNCTION__, &dlTask);
                            err = NWC24DeleteDlTask(&dlTask);
                            if (err != NWC24_OK) {
                                OSReport("%s::%s NWC24GetDlAppId failed - [%d]  -> continue\n", __FILE__, __FUNCTION__, err);
                            } else {
                                OSReport("%s::%s delete download task for index : %d\n", __FILE__, __FUNCTION__, dlId);
                            }
                        } else {
                            OSReport("%s::%s ignore title id %d: %08x \n", __FILE__, __FUNCTION__, dlId, dlAppId);
                        }
                    }
                    err = NWC24IterateDlTask(&dlId, FALSE);
                }

                ret = NWC24CloseLib();
                if (ret != NWC24_OK) {
                    OSReport("%s::%s NWC24CloseLib failed - [%d]  -> continue\n", __FILE__, __FUNCTION__, ret);
                }
                goto cleanup;
            }

        cleanup:
            if (nwc24Work != NULL) {
                heap->free(nwc24Work);
            }

            OSReport("%s::%s delete download task for %08x\n", __FILE__, __FUNCTION__, titleId);
            return ret;
        }

        extern "C" s32 DeleteDownloadTask__Q33ipl7utility6ESMiscFv(EGG::Heap* heap, u32 titleId) {
            return DeleteDownloadTask(heap, titleId);
        }

        s32 ESMisc::DeleteTitleContent(EGG::Heap* heap, ESTitleId titleId) {
            s32 result;
            s32 safe;
            s32 ret = DeleteMetaContent(titleId);

            if (ret != ES_ERR_OK && ret != NAND_RESULT_NOEXISTS) {
                OSReport("%s::%s failed to delete meta for %016llx: %d\n", __FILE__, __FUNCTION__, titleId, ret);
                return ret;
            }

            result = (titleId & 0xffffff00ULL) == 0x48414f00ULL;
            safe = CheckSafeDeleteTitle(heap, titleId);
            if (safe == 1 || result) {
                result = DeleteTitle(heap, titleId);
                if (result != ES_ERR_OK) {
                    OSReport("%s::%s failed to delete title for %016llx: %d\n", __FILE__, __FUNCTION__, titleId, result);
                    return result;
                }
            } else {
                if (safe == ES_ERR_OK) {
                    result = ES_DeleteTitleContent(titleId);
                    if (result != ES_ERR_OK) {
                        OSReport("%s::%s failed to delete contents for %016llx: %d\n", __FILE__, __FUNCTION__, titleId, result);
                        return result;
                    }
                } else {
                    OSReport("%s::%s failed to check safety for %016llx: %d\n", __FILE__, __FUNCTION__, titleId, safe);
                    return safe;
                }
            }

            result = DeleteDownloadTask__Q33ipl7utility6ESMiscFv(heap, NANDTitleIdLo(titleId));
            if (result != ES_ERR_OK) {
                OSReport("%s::%s failed to delete DL task for %016llx: %d\n", __FILE__, __FUNCTION__, titleId, result);
            }
            return result;
        }

        ESError ESMisc::PrepareTitleDir(ESTitleId titleId, EGG::Heap* heap) {
            TMDFile tmdFile(heap);
            s32 ret = tmdFile.Open((char*)TMD_FILE);

            if (ret != ES_ERR_OK) {
                ES_ERR_REPORT("Open backup TMD file failed: %d", ret);
                tmdFile.Close();
                return ret;
            }

            ret = tmdFile.Restore(titleId);
            if (ret == -0x401) {
                ES_ERR_REPORT("No backup of %016llx: %d", titleId, ret);
            } else if (ret != ES_ERR_OK) {
                ES_ERR_REPORT("Restore failed: %d", ret);
            }

            s32 closeRet = tmdFile.Close();
            if (closeRet != ES_ERR_OK) {
                ES_ERR_REPORT("Failed to close TMD system file: %d", closeRet);
                ret = closeRet;
            }
            tmdFile.Close();

            return ret;
        }

        ESError ESMisc::DeleteSavedata(ESTitleId titleId, EGG::Heap* heap) {
            s32 ret;
            char dirPath[0x80] ALIGN32;
            char filePath[0x41];
            char* entries = NULL;
            u32 entryCount = 0;
            char* entry;
            u32 i;

            sprintf(dirPath + 0x20, "/title/%08x/%08x/data/", NANDTitleIdHi(titleId), NANDTitleIdLo(titleId));
            ret = NANDReadDir(dirPath + 0x20, NULL, &entryCount);

            if (ret != ES_ERR_OK || entryCount == 0) {
                ES_ERR_REPORT("Could not read1 %s: %d", dirPath + 0x20, ret);
                goto cleanup;
            }

            entries = (char*)heap->alloc(OSRoundUp32B(entryCount * 0x41), -DEFAULT_ALIGN);
            if (entries == NULL) {
                ret = -2;
                ES_ERR_REPORT("Could not alloc: %d", -2);
                goto cleanup;
            }

            ret = NANDReadDir(dirPath + 0x20, entries, &entryCount);
            if (ret != ES_ERR_OK) {
                ES_ERR_REPORT("Could not read2 %s: %d", dirPath + 0x20, ret);
                goto cleanup;
            }

            entry = entries;
            for (i = 0; i < entryCount; i++) {
                snprintf(filePath + 0x1c, 0x40, "%s%s", dirPath + 0x20, entry);
                (filePath + 0x1c)[0x40] = 0;
                ret = NANDPrivateDelete(filePath + 0x1c);
                if (ret != ES_ERR_OK) {
                    ES_ERR_REPORT("Failed to delete %s: %d", filePath + 0x1c, ret);
                }
                entry += strlen(entry) + 1;
            }

        cleanup:
            if (entries != NULL) {
                heap->free(entries);
            }
            return ret;
        }

        void ESMisc::DeleteUnauthorizedData(EGG::Heap* heap) {
            u32 titleCount = 0;
            ESTitleId* titleIds = NULL;
            s32 ret = ES_ListTitlesOnCard(NULL, &titleCount);

            if (ret != ES_ERR_OK) {
                OSReport("%s::%s: Failed to ES_ListTitlesOnCard1: %d\n", __FILE__, "InitSavedata", ret);
                return;
            }

            titleIds = (ESTitleId*)heap->alloc(OSRoundUp32B(titleCount * sizeof(ESTitleId)), -DEFAULT_ALIGN);
            if (titleIds == NULL) {
                OSReport("%s::%s: Unable to allocate\n", __FILE__, "InitSavedata");
                return;
            }

            ret = ES_ListTitlesOnCard(titleIds, &titleCount);
            if (ret != ES_ERR_OK) {
                OSReport("%s::%s: Failed to ES_ListTitlesOnCard2: %d\n", __FILE__, "InitSavedata", ret);
                heap->free(titleIds);
                return;
            }

            for (u32 i = 0; i < titleCount; i++) {
                u32 titleIdHi = ((u32*)titleIds)[i * 2];
                u32 titleIdLo = ((u32*)titleIds)[i * 2 + 1];
                ESTitleId titleId = ((ESTitleId)titleIdHi << 32) | titleIdLo;

                if (titleIdHi == 0x10000 && (titleIdLo & 0xffffff00) == 0x525a4400) {
                    char path[88];
                    NANDFileInfo fileInfo ALIGN32;
                    u8* saveData = NULL;
                    BOOL fileOpen = FALSE;
                    BOOL deleteSaveData = FALSE;

                    sprintf(path - 8, "/title/%08x/%08x/data/%s", titleIdHi & 0xffffff, titleIdLo, "zeldaTp.dat");
                    if (!ChangeUid(titleId)) {
                        OSReport("%s::%s: ChangeUid failed\n", __FILE__, "verifySavedataZD");
                        DeleteTitle(heap, titleId);
                    } else {
                        ret = NANDPrivateOpen(path - 8, (NANDFileInfo*)((u8*)&fileInfo - 0x20), NAND_ACCESS_READ);
                        if (ret == NAND_RESULT_NOEXISTS) {
                            OSReport("%s::%s: Does not exist %s: %d\n", __FILE__, "verifySavedataZD", path - 8, ret);
                        } else if (ret != NAND_RESULT_OK) {
                            OSReport("%s::%s: Open save data file failed: %d\n", __FILE__, "verifySavedataZD", ret);
                        } else {
                            fileOpen = TRUE;
                            saveData = (u8*)heap->alloc(0x4000, -DEFAULT_ALIGN);
                            if (saveData == NULL) {
                                OSReport("%s::%s: Alloc failed: %d\n", __FILE__, "verifySavedataZD", -2);
                            } else {
                                memset(saveData, 0, 0x4000);
                                ret = NANDRead((NANDFileInfo*)((u8*)&fileInfo - 0x20), saveData, 0x4000);
                                if (ret < 0) {
                                    OSReport("%s::%s: Read file failed: %d\n", __FILE__, "verifySavedataZD", ret);
                                } else if (ret != 0x4000) {
                                    OSReport("%s::%s: File size is not correct: %d\n", __FILE__, "verifySavedataZD", ret);
                                    deleteSaveData = TRUE;
                                } else {
                                    u32 offset = 8;
                                    u32 j = 0;
                                    BOOL valid = FALSE;
                                    while (j < 3) {
                                        u8* block = saveData + offset;
                                        if (!checkForNullTermination((char*)block + 0x4e, 8) ||
                                            !checkForNullTermination((char*)block + 0x58, 8) ||
                                            !checkForNullTermination((char*)block + 0x72, 8) ||
                                            !checkForNullTermination((char*)block + 0x8e, 8) ||
                                            !checkForNullTermination((char*)block + 0x1b4, 0x11) ||
                                            !checkForNullTermination((char*)block + 0x1c5, 0x11)) {
                                            goto verify_failed;
                                        }
                                        j++;
                                        offset += 0xa94;
                                    }

                                    offset = 0x2008;
                                    j = 0;
                                    while (j < 3) {
                                        u8* block = saveData + offset;
                                        if (!checkForNullTermination((char*)block + 0x4e, 8) ||
                                            !checkForNullTermination((char*)block + 0x58, 8) ||
                                            !checkForNullTermination((char*)block + 0x72, 8) ||
                                            !checkForNullTermination((char*)block + 0x8e, 8) ||
                                            !checkForNullTermination((char*)block + 0x1b4, 0x11) ||
                                            !checkForNullTermination((char*)block + 0x1c5, 0x11)) {
                                            goto verify_failed;
                                        }
                                        j++;
                                        offset += 0xa94;
                                    }
                                    valid = TRUE;

                                verify_failed:

                                    if (!valid) {
                                        OSReport("%s::%s: Verify failed for %016llx\n", __FILE__, "verifySavedataZD", titleId);
                                        deleteSaveData = TRUE;
                                    }
                                }

                                NANDClose((NANDFileInfo*)((u8*)&fileInfo - 0x20));
                                fileOpen = FALSE;
                                if (deleteSaveData) {
                                    DeleteSavedata(titleId, heap);
                                }
                            }
                        }
                    }

                    if (saveData != NULL) {
                        heap->free(saveData);
                    }
                    if (fileOpen) {
                        NANDClose((NANDFileInfo*)((u8*)&fileInfo - 0x20));
                    }
                    ChangeUid(SYSMENU_TITLE_ID);
                } else if (titleId == 0x0001000844495343ULL ||
                           (titleId < 0x0001000844495343ULL &&
                            (titleId == 0x000100014a4f4449ULL ||
                             (titleId > 0x000100014a4f4449ULL && titleId == 0x0001000148415858ULL))) ||
                           (titleId > 0x0001000844495343ULL &&
                            (titleId == 0x0001000844564458ULL ||
                             (titleId > 0x0001000844564458ULL && titleId == 0x000100084449534bULL)))) {
                    ES_DeleteTitle(titleId);

                    u8 ticketViews[0xe0];
                    u32 ticketViewCount = 0;
                    ESTicketView* ticketViewList = NULL;
                    memset(ticketViews - 8, 0, sizeof(ticketViews));
                    ret = ES_GetTicketViews(titleId, NULL, &ticketViewCount);
                    if (ret != ES_ERR_OK) {
                        OSReport("%s::%s: ES_GetTicketViews failed: %d for %016llx\n", __FILE__, "DeleteTicketsForce", ret, titleId);
                    } else if (ticketViewCount != 0) {
                        ticketViewList = (ESTicketView*)heap->alloc(ticketViewCount * sizeof(ESTicketView), -DEFAULT_ALIGN);
                        ret = ES_GetTicketViews(titleId, ticketViewList, &ticketViewCount);
                        if (ret != ES_ERR_OK) {
                            OSReport("%s::%s: ES_GetTicketViews failed: %d for %016llx\n", __FILE__, "DeleteTicketsForce", ret, titleId);
                        } else {
                            for (u32 j = 0; j < ticketViewCount; j++) {
                                memcpy(ticketViews - 8, (u8*)ticketViewList + j * sizeof(ESTicketView), 0xd8);
                                ret = ES_DeleteTicket((ESTicketView*)(ticketViews - 8));
                                if (ret != ES_ERR_OK) {
                                    ESTitleId ticketTitleId;
                                    memcpy(&ticketTitleId, (u8*)(ticketViews - 8) + 4, sizeof(ESTitleId));
                                    OSReport("%s::%s: ES_DeleteTicket failed: %d for %016llx\n", __FILE__, "DeleteTicketsForce", ret, ticketTitleId);
                                }
                            }
                        }
                    }

                    if (ticketViewList != NULL) {
                        heap->free(ticketViewList);
                    }
                }
            }

            heap->free(titleIds);
        }

        BOOL checkForNullTermination(char* str, u32 len) {
            for (u32 i = 0; i < len; i++) {
                if (*str == 0) {
                    return TRUE;
                }
                str++;
            }
            return FALSE;
        }

        TMDFile::TMDFile(EGG::Heap* heap) : mpHeap(heap), mbFileOpen(FALSE), mFileLength(0) {
            memset(&mFile, 0, sizeof(mFile));
        }

        s32 TMDFile::Open(char* fileName) {
            s32 ret;

            if (mbFileOpen) {
                return NAND_RESULT_OK;
            }

            ret = NANDPrivateOpen(fileName, &mFile, NAND_ACCESS_RW);
            if (ret == NAND_RESULT_NOEXISTS) {
                ret = NANDPrivateCreate(fileName, NAND_PERM_ALL_RW, 0);
                if (ret != NAND_RESULT_OK) {
                    ES_ERR_REPORT("NANDCreate %s err: %d", fileName, ret);
                    return ret;
                }
                ret = NANDPrivateOpen(fileName, &mFile, NAND_ACCESS_RW);
            }

            if (ret != NAND_RESULT_OK) {
                ES_ERR_REPORT("NANDOpen %s err: %d", fileName, ret);
                return ret;
            }

            mbFileOpen = TRUE;
            ret = NANDGetLength(&mFile, &mFileLength);
            if (ret != NAND_RESULT_OK) {
                ES_ERR_REPORT("NANDGetLength %s err: %d", fileName, ret);
                return ret;
            }
            return ret;
        }

        s32 TMDFile::Close() {
            s32 ret = ES_ERR_OK;
            if (mbFileOpen) {
                ret = NANDClose(&mFile);
                mbFileOpen = FALSE;
            }
            return ret;
        }

        BOOL TMDFile::Exist(ESTitleId titleId, u32* tmdOffset, u32* tmdSize) {
            u32 offset = 0;
            EntryHead entry ALIGN32;

            if (!mbFileOpen) {
                return FALSE;
            }

            for (; offset < mFileLength; offset += OSRoundUp32B(entry.tmdSize)) {
                s32 ret = NANDSeek(&mFile, offset, NAND_SEEK_BEG);
                if (ret != offset) {
                    ES_ERR_REPORT("NANDSeek err: %d!=%d", ret, offset);
                    return FALSE;
                }

                u32 readSize = NANDRead(&mFile, &entry, OSRoundUp32B(sizeof(EntryHead)));
                if (readSize != OSRoundUp32B(sizeof(EntryHead))) {
                    ES_ERR_REPORT("NANDRead err: %d!=%d", readSize, OSRoundUp32B(sizeof(EntryHead)));
                    return FALSE;
                }

                offset += OSRoundUp32B(sizeof(EntryHead));
                if (entry.titleId == titleId) {
                    if (tmdOffset) {
                        *tmdOffset = offset;
                    }
                    if (tmdSize) {
                        *tmdSize = entry.tmdSize;
                    }
                    return TRUE;
                }
            }
            return FALSE;
        }

        s32 TMDFile::Backup(ESTitleId titleId) {
            s32 ret = NAND_RESULT_OK;
            u32 entryLen;
            EntryHead* entry = NULL;

            if (!mbFileOpen) {
                return -1;
            }

            u32 fileLen;
            u32 tmdSize;

            // Is the TMD already in the backup database?
            if (!Exist(titleId, NULL, NULL)) {
                // If not, let's back you up!

                // Get file length. (...without NANDGetLength?)
                ret = NANDSeek(&mFile, 0, NAND_SEEK_END);
                if (ret != mFileLength) {
                    ES_ERR_REPORT("NANDSeek err: %d!=%d", ret, mFileLength);
                    goto out;
                }
                ret = NANDTell(&mFile, &fileLen);
                if (ret != NAND_RESULT_OK) {
                    ES_ERR_REPORT("NANDTell err: %d", ret);
                    goto out;
                }

                // Verify the file length.
                if (fileLen != mFileLength || (fileLen & 31)) {
                    ES_ERR_REPORT("Internal error: %d!=%d || 0x%x not 32B", fileLen, mFileLength, fileLen);
                    ret = -1;
                    goto out;
                }

                // The title metadata
                ret = ES_GetTmd(titleId, NULL, &tmdSize);
                if (ret != ES_ERR_OK) {
                    ES_ERR_REPORT("ES_GetTmd err: %d", ret);
                    goto out;
                }

                // Prepare TMD backup entry.
                entryLen = OSRoundUp32B(tmdSize) + OSRoundUp32B(sizeof(EntryHead));
                entry = (EntryHead*)mpHeap->alloc(entryLen, -DEFAULT_ALIGN);
                memset(entry, 0, entryLen);
                entry->titleId = titleId;
                entry->tmdSize = tmdSize;

                // Export TMD contents to entry
                ret = ES_ExportTitleInit(titleId, 0, 0, NULL, 0, NULL, 0, 2, NULL, entry->getTmdPtr(), tmdSize);
                if (ret != ES_ERR_OK) {
                    ES_ERR_REPORT("ES_ExportTitleInit err: %d", ret);
                    ES_ExportTitleDone();
                    goto out;
                }
                ret = ES_ExportTitleDone();
                if (ret != ES_ERR_OK) {
                    ES_ERR_REPORT("ES_ExportTitleDone err: %d", ret);
                    goto out;
                }

                // Write the entry to the backup file
                ret = NANDWrite(&mFile, entry, entryLen);
                if (ret != entryLen) {
                    ES_ERR_REPORT("NANDWrite err: %d!=%d", ret, entryLen);
                    goto out;
                }

                // We are done!!!
                ret = NAND_RESULT_OK;
                mFileLength += entryLen;
                goto out;
            }
        out:
            if (entry != NULL) {
                mpHeap->free(entry);
            }
            return ret;
        }

        s32 TMDFile::Restore(ESTitleId titleId) {
            s32 ret = NAND_RESULT_OK;

            u32 fileLen;
            u32 tmdOffset = 0;
            u32 tmdSize = 0;
            void* tmdBuffer = NULL;

            if (!mbFileOpen) {
                return -1;
            }

            ret = ES_GetTmdView(titleId, NULL, &tmdSize);

            if (ret != ES_ERR_OK) {
                if (ret != ES_ERR_DONT_EXISTS) {
                    ES_ERR_REPORT("ES_GetTmdView err: %d", ret);
                    goto out;
                }
                tmdSize = 0;

                ret = Exist(titleId, &tmdOffset, &tmdSize);
                if (ret == FALSE) {
                    ret = ES_ERR_NO_TMD_FILE_FOUND;
                    goto out;
                }

                ret = NANDSeek(&mFile, tmdOffset, NAND_SEEK_BEG);
                if (ret != tmdOffset) {
                    ES_ERR_REPORT("NANDSeek err: %d!=%d", ret, tmdOffset);
                    goto out;
                }

                fileLen = OSRoundUp32B(tmdSize);
                tmdBuffer = mpHeap->alloc(fileLen, -DEFAULT_ALIGN);
                memset(tmdBuffer, 0, fileLen);

                ret = NANDRead(&mFile, tmdBuffer, fileLen);
                if (ret != fileLen) {
                    ES_ERR_REPORT("NANDRead err: %d!=%d", ret, fileLen);
                    goto out;
                }

                ret = ES_ImportTitleInit(tmdBuffer, tmdSize, NULL, 0, NULL, 0, 2, 1);
                if (ret != ES_ERR_OK) {
                    ES_ERR_REPORT("ES_ImportTitleInit err: %d", ret);
                    ES_ImportTitleCancel();
                }

                ret = ES_ImportTitleDone();
                if (ret != ES_ERR_OK) {
                    ES_ERR_REPORT("ES_ImportTitleDone err: %d", ret);
                    goto out;
                }
            }
        out:
            if (tmdBuffer != NULL) {
                mpHeap->free(tmdBuffer);
            }
            return ret;
        }
    }  // namespace utility
}  // namespace ipl
