// opus-sdm best C for src/system/iplSaveDataManager.cpp (not exact; the asm placeholders stay in the source).
// Drop each body in place of its asm block.

// Manager::hasChannel: odiff 12 differing / 71, objdiff 99.014084%, 71/71 instructions, pool identical.
// Remaining: the full mask gets r9/r0 (target r10/r9), the 0xFFFFFFFFFFFFFF00 halves get r10/r4 (target r4/r0),
// and the row base gets r10 (target r0). Code-only mask in r12/r11 matches.
        ESTitleId Manager::hasChannel(ESTitleId titleId, int* outIndex, int* outPage) const {
            ESTitleId titleCodeRegion = ES_TITLE_TYPE(titleId) != 0 ? 0xFFFFFFFFFFFFFFFF : 0x00000000FFFFFFFF;
            
            int page = 0;
            do {
                for (int index = 0; index < MAX_CHANNEL_INDEX; index++) {
                    if (mData.chanInfo[page][index].primaryType == channel::PRIMARY_TYPE_CHANNEL) {
                        ESTitleId titleCode = TITLE_NO_REGION(titleCodeRegion);
                        ESTitleId tId = ES_TITLE_ID(mData.chanInfo[page][index].titleType, mData.chanInfo[page][index].titleCode);
                        if (titleId == (tId & titleCodeRegion) ||
                            (tId & titleCode) == (titleId & titleCode) && (ESTitleId)(u8)titleId == TITLE_REGION_ALL) {
                            if (outIndex) {
                                *outIndex = page;
                            }
                            if (outPage) {
                                *outPage = index;
                            }
                            return tId;
                        }
                    }
                }
                page++;
            } while (page < MAX_CHANNEL_PAGE);
            return 0;
        }

// Manager::makePriorTitleIDList: odiff 96 differing / 133, objdiff 75.53384%, 122/133 instructions, pool identical.
// The da1 prior-search candidate keeps the higher objdiff score (80.22556%, 124/133) but 118 differing.
// Blocker: the target recomputes &titleIdsIn[i] and &titleIdsOut[outputIndex] (slwi/add) at every use and
// reloads titleIdsIn[i] for isEqualChannel; MWCC CSEs/hoists both addresses here and keeps -0x100 unhoisted.
        void Manager::makePriorTitleIDList(ESTitleId* titleIdsOut, ESTitleId* titleIdsIn, u32 titleCount) {
            for (int page = 0; page < MAX_CHANNEL_PAGE; page++) {
                for (int index = 0; index < MAX_CHANNEL_INDEX; index++) {
                    if (mData.chanInfo[page][index].primaryType == channel::PRIMARY_TYPE_CHANNEL) {
                        ESTitleId titleId = ES_TITLE_ID(mData.chanInfo[page][index].titleType, mData.chanInfo[page][index].titleCode);
                        int outputIndex = index + page * MAX_CHANNEL_INDEX;
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
