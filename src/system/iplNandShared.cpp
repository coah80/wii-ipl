#include "system/iplNandShared.h"

#include "iplSystem.h"
#include "iplUtility.h"

#include <cstring>

namespace ipl {
    namespace nand {
        SharedFile::SharedFile(EGG::Heap* heap, const char* fileName, u32 index, int offset, u32 length, ESTitleId titleId, int ticketIdx)
            : File(heap, fileName, NULL, NULL, offset, length, false), mContentIdx(index), mDescriptor(-1), mTitleId(titleId), mTicket(NULL),
              mTicketIdx(ticketIdx), mpFSTBuffer(NULL) {
        }

        SharedFile::~SharedFile() {
        }

        BOOL SharedFile::openTicketFile_() {
            int errorStage = 0;
            int errorCode = 0;
            ESTitleId titleId = 0;
            ESTicketId ticketId = 0;
            int contentIndex = 0;
            mTicket = (ESTicketView*)System::getSharedHeap()->alloc(OSRoundUp32B(sizeof(ESTicketView)), -DEFAULT_ALIGN);

            if (mTicketIdx >= 0) {
                if (utility::ESMisc::GetTicketView(System::getSharedHeap(), mTitleId, mTicket, mTicketIdx) < ES_ERR_OK) {
                    errorStage = 100;
                    goto err;
                }
            } else {
                u32 ticketCount;
                ESTicketView* ticketViews;

                if (utility::ESMisc::GetTicketViewList(System::getSharedHeap(), mTitleId, &ticketViews, &ticketCount) != ES_ERR_OK) {
                    // MWCC needs these self-copies to preserve the error branches.
                    errorStage = errorStage;
                    goto err;
                } else {
                    int ticketIndex = utility::ESMisc::GetValidTicketIndex(System::getSharedHeap(), mTitleId, ticketViews, ticketCount);
                    if (ticketIndex < 0) {
                        goto err;
                    }
                    if (ticketIndex >= ticketCount) {
                        errorStage = errorStage;
                        goto err;
                    }
                    mTicketIdx = ticketIndex;
                    memcpy(mTicket, &ticketViews[ticketIndex], sizeof(ESTicketView));
                    System::getSharedHeap()->free(ticketViews);
                }
            }

            s32 contentDescriptor = ES_OpenTitleContentFile(mTitleId, mTicket, mContentIdx);
            mDescriptor = contentDescriptor;

            if (contentDescriptor < ES_ERR_OK) {
                errorCode = contentDescriptor;
                titleId = mTitleId;
                if (mTicket) {
                    ticketId = mTicket->ticketId;
                }
                contentIndex = mContentIdx;
                errorStage = 400;
                goto err;
            }

            ARCHeader header ALIGN32;
            if (ES_ReadContentFile(mDescriptor, &header, sizeof(ARCHeader)) < ES_ERR_OK) {
                errorStage = 500;
                goto err;
            }

            u32 bufSize = OSRoundUp32B(header.fileStart);
            mpFSTBuffer = System::getSharedHeap()->alloc(bufSize, -DEFAULT_ALIGN);

            if (ES_SeekContentFile(mDescriptor, 0, NAND_SEEK_BEG) < ES_ERR_OK || ES_ReadContentFile(mDescriptor, mpFSTBuffer, bufSize) < ES_ERR_OK ||
                !ARCInitHandle(mpFSTBuffer, &mArc)) {
                errorStage = 600;
                goto err;
            }

            BOOL result = ARCOpen(&mArc, msFileName, &mArcFile);
            if (!result) {
                if (ES_CloseContentFile(mDescriptor) < ES_ERR_OK) {
                    goto err;
                }
            }
            return result == TRUE;
        err:
            char errString[128];
            sprintf(errString, "ES %d, %llx, %llx, %x", errorCode, titleId, ticketId, contentIndex);

            IPLErrorLogAndDisplay(MESG_ERR_FILE, errString, errorStage, 158);

            return FALSE;
        }

        BOOL SharedFile::closeTicketFile_() {
            if (ES_CloseContentFile(mDescriptor) >= ES_ERR_OK) {
                if (mTicket) {
                    System::getSharedHeap()->free(mTicket);
                }
                if (mpFSTBuffer) {
                    System::getSharedHeap()->free(mpFSTBuffer);
                    ARCClose(&mArcFile);
                }

                return TRUE;
            } else {
                IPLErrorLogAndDisplay(MESG_ERR_FILE, "ES", 0, 189);

                return FALSE;
            }
        }

        BOOL SharedFile::open_(u8 attr) {
            return openTicketFile_();
        }

        BOOL SharedFile::close_() {
            return closeTicketFile_();
        }

        u32 SharedFile::getRawSize_() {
            return ARCGetLength(&mArcFile);
        }

        void SharedFile::readBlock_(void* buffer, int length, int offset) {
            int arcOffset = ARCGetStartOffset(&mArcFile);

            if (ES_SeekContentFile(mDescriptor, arcOffset + offset, NAND_SEEK_BEG) < ES_ERR_OK ||
                ES_ReadContentFile(mDescriptor, buffer, length) < ES_ERR_OK) {
                IPLErrorLogAndDisplay(MESG_ERR_FILE, "ES", 0, 358);
            }
        }
    }  // namespace nand
}  // namespace ipl
