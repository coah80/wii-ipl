#define IPL_SD_CHANNEL_OBJ_CPP
#include "scene/sdChannelSelect/iplSDChannelSelect.h"

#include "iplSound.h"
#include "iplSystem.h"
#include <private/es.h>
#include <revolution/sc.h>

namespace ipl {
    namespace scene {
        static const wchar_t scUnknownName[] = L"???";
        static const char* scCursur = "Cursur_a";
        static const char* scCursorAnims[] = {
            "my_IplTop_d_FocusOff.brlan",
            "my_IplTop_d_FocusOn.brlan",
            "my_IplTop_d_Select.brlan",
        };
        static const char* scBalloon = "T_Balloon";
        static const char* scBase = "W_Base";
        static const char* scShade = "W_Shade";
        static const char* scLangGroups[] = {"JPN", "ENG", "GER", "FRA", "SPA", "ITA", "NED", "CHN", "ENG", "KOR"};
        static const char* scRegionGroups[SC_PRODUCT_AREA_MAX][16] = {
            {"JPN"},
            {"ENG", "FRA", "SPA"},
            {"ENG", "FRA", "GER", "SPA", "ITA", "NED"},
            {NULL},
            {NULL},
            {NULL},
            {"KOR"},
            {NULL},
            {NULL},
            {NULL},
            {NULL},
            {"CHN"},
        };
        static const u32 scLangLookup[SC_PRODUCT_AREA_MAX][16] = {
            {SC_LANG_JAPANESE, -1},
            {SC_LANG_ENGLISH, SC_LANG_FRENCH, SC_LANG_SPANISH, -1},
            {SC_LANG_ENGLISH, SC_LANG_FRENCH, SC_LANG_GERMAN, SC_LANG_SPANISH, SC_LANG_ITALIAN, SC_LANG_DUTCH, -1},
            {-1},
            {-1},
            {-1},
            {SC_LANG_KOREAN, -1},
            {-1},
            {-1},
            {-1},
            {-1},
            {SC_PRODUCT_AREA_HKG, -1},
        };

        static const f32 scThumbnailOffsets[][2] = {{64.0f, 48.0f}, {85.0f, 48.0f}};
        extern "C" void iplSDChannelObj_activateIfIdle(SDChannelObj* channel) NO_INLINE;
        extern "C" void iplSDChannelObj_setHeaps(SDChannelObj* channel, EGG::ExpHeap* firstHeap,
                                                 EGG::ExpHeap* secondHeap) NO_INLINE;
        extern "C" void* iplSDChannelObj_getOrAllocThumbnailData(SDChannelObj* channel) NO_INLINE;
        extern "C" void iplSDChannelObj_setPane(SDChannelObj* channel, nw4r::lyt::Pane* pane) NO_INLINE;
        extern "C" void iplSDChannelObj_setLayoutFile(SDChannelObj* channel, nand::LayoutFile* layoutFile) NO_INLINE;
        extern "C" void iplSDChannelObj_calc(SDChannelObj* channel) NO_INLINE;
        extern "C" void iplSDChannelObj_drawBase(SDChannelObj* channel) NO_INLINE;
        extern "C" void iplSDChannelObj_drawPage(SDChannelObj* channel) NO_INLINE;
        extern "C" void iplSDChannelObj_drawDialog(SDChannelObj* channel) NO_INLINE;
        extern "C" bool iplSDChannelObj_hasAppMeta(SDChannelObj* channel) NO_INLINE;
        extern "C" void iplSDChannelObj_startAppear(SDChannelObj* channel, int request) NO_INLINE;
        extern "C" void iplSDChannelObj_startDisappear(SDChannelObj* channel, int request) NO_INLINE;
        extern "C" void iplSDChannelObj_setSelected(SDChannelObj* channel, bool request) NO_INLINE;
        extern "C" void iplSDChannelObj_playPageHide(SDChannelObj* channel) NO_INLINE;
        extern "C" void iplSDChannelObj_resetPageAnim(SDChannelObj* channel, int request) NO_INLINE;
        extern "C" void iplSDChannelObj_resetDialogAnim(SDChannelObj* channel, bool request) NO_INLINE;
        extern "C" void iplSDChannelObj_applyLanguageGroups(layout::Object* layout) NO_INLINE;
        extern "C" void iplSDChannelObj_createBaseLayout(SDChannelObj* channel) NO_INLINE;
        extern "C" f32 iplSDChannelObj_createIconLayout(SDChannelObj* channel) NO_INLINE;
        extern "C" f32 iplSDChannelObj_createMenuLayout(SDChannelObj* channel) NO_INLINE;
        extern "C" void iplSDChannelObj_syncLayoutsToPane(SDChannelObj* channel) NO_INLINE;
        extern "C" void iplSDChannelObj_createPageLayout(SDChannelObj* channel) NO_INLINE;
        extern "C" void iplSDChannelObj_setPageTranslate(SDChannelObj* channel, const nw4r::math::VEC3& vec) NO_INLINE;
        extern "C" void iplSDChannelObj_setPageAnim(SDChannelObj* channel, int request) NO_INLINE;
        extern "C" void iplSDChannelObj_updatePageAnim(SDChannelObj* channel) NO_INLINE;
        extern "C" void iplSDChannelObj_playPageAnimator(SDChannelObj* channel, int request) NO_INLINE;
        extern "C" void iplSDChannelObj_createDialogLayout(SDChannelObj* channel) NO_INLINE;
        extern "C" const wchar_t* iplSDChannelObj_getLocalizedName(SDChannelObj* channel, int index) NO_INLINE;
        extern "C" void iplSDChannelObj_setBalloonText(SDChannelObj* channel, const wchar_t* text) NO_INLINE;
        extern "C" void iplSDChannelObj_positionDialog(SDChannelObj* channel, const nw4r::math::VEC3& vec) NO_INLINE;
        extern "C" void iplSDChannelObj_setDialogAnim(SDChannelObj* channel, int request) NO_INLINE;
        extern "C" void iplSDChannelObj_updateDialogAnim(SDChannelObj* channel) NO_INLINE;
        extern "C" void iplSDChannelObj_findNewMessageGroup(SDChannelObj* channel, layout::Object* layout) NO_INLINE;
        extern "C" void iplSDChannelObj_updateNewMessage(SDChannelObj* channel) NO_INLINE;
        extern "C" BOOL iplSDChannelObj_checkNewMessage(SDChannelObj* channel) NO_INLINE;

        SDChannelObj::SDChannelObj(EGG::Heap* heap, int page, int index)
            : mpHeap(heap), mpDialogHeap(NULL), mpChannelHeap(NULL), mState(0), mPage(page), mIndex(index),
              mpPane(NULL), mpBaseLayout(NULL), mpPageLayout(NULL), mPageAnimation(0), mPageAnimationFrame(0),
              mpDialogLayout(NULL), mDialogState(0), mDialogFrame(0), mDialogTimer(0), mAnimationState(0),
              mpNewMessageGroup(NULL), mpNewMessageAnimator(NULL), mbNewMessageGroupActive(false), mNewMessageState(0),
              mNewMessageFrame(0), mOffsetX(scThumbnailOffsets[SCGetAspectRatio()][0]),
              mOffsetY(scThumbnailOffsets[SCGetAspectRatio()][1]), mStateFlags(1), mpThumbnailData(NULL) {
            if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
                nw4r::ut::Rect projection4x3;
                System::getProjectionRect4x3(&projection4x3);
                nw4r::ut::Rect projection16x9;
                System::getProjectionRect16x9(&projection16x9);
                mAspectRatioScale = projection16x9.GetWidth() / projection4x3.GetWidth();
            } else {
                mAspectRatioScale = 1.0f;
            }
            memset(&mAppMeta, 0, sizeof(mAppMeta));
        }
        SDChannelObj::~SDChannelObj() {
            if (mpBaseLayout != NULL)
                mpBaseLayout->destroyHeap();
            if (mpPageLayout != NULL)
                delete mpPageLayout;
            if (mpDialogLayout != NULL)
                delete mpDialogLayout;
        }
        extern "C" void iplSDChannelObj_activateIfIdle(SDChannelObj* channel) {
            if (channel->mState == 0)
                channel->mState = 2;
        }

        extern "C" void iplSDChannelObj_setHeaps(SDChannelObj* channel, EGG::ExpHeap* firstHeap,
                                                 EGG::ExpHeap* secondHeap) {
            channel->mpDialogHeap = firstHeap;
            channel->mpChannelHeap = secondHeap;
        }

        extern "C" void* iplSDChannelObj_getOrAllocThumbnailData(SDChannelObj* channel) {
            if (channel->mpThumbnailData == NULL)
                channel->mpThumbnailData = new (channel->mpHeap, 32) u8[0x19000];
            return channel->mpThumbnailData;
        }

        extern "C" void iplSDChannelObj_setPane(SDChannelObj* channel, nw4r::lyt::Pane* pane) {
            channel->mpPane = pane;
        }

        extern "C" void iplSDChannelObj_setLayoutFile(SDChannelObj* channel, nand::LayoutFile* layoutFile) {
            if (!SDChannelSelect::isChannelReady(channel)) {
                channel->mpLayoutFile = layoutFile;
                if (channel->mpPageLayout == NULL)
                    iplSDChannelObj_createPageLayout(channel);
                if (channel->mpDialogLayout == NULL)
                    iplSDChannelObj_createDialogLayout(channel);
                if (channel->mState == 2 || channel->mState == 1 && channel->mpPaneAnimator->isFinished()) {
                    iplSDChannelObj_createBaseLayout(channel);
                    channel->mState = 3;
                }
            }
        }

        extern "C" void iplSDChannelObj_calc(SDChannelObj* channel) {
            switch (channel->mState) {
            case 0:
                channel->mState = 2;
                break;
            case 1:
                if (!channel->mpPaneAnimator->isFinished())
                    break;
                channel->mState = 2;
            case 2:
                iplSDChannelObj_createBaseLayout(channel);
                channel->mState = 3;
                break;
            case 3:
                iplSDChannelObj_syncLayoutsToPane(channel);
                break;
            }
        }

        extern "C" void iplSDChannelObj_drawBase(SDChannelObj* channel) {
            if (SDChannelSelect::isChannelReady(channel))
                channel->mpBaseLayout->draw();
        }

        extern "C" void iplSDChannelObj_drawPage(SDChannelObj* channel) {
            channel->mpPageLayout->draw();
        }

        extern "C" void iplSDChannelObj_drawDialog(SDChannelObj* channel) {
            if (channel->mpDialogLayout != NULL)
                channel->mpDialogLayout->draw();
        }

        nw4r::math::VEC3& SDChannelObj::getTranslate() const {
            return (nw4r::math::VEC3&)mpBaseLayout->GetRootPane()->GetTranslate();
        }

        extern "C" bool iplSDChannelObj_hasAppMeta(SDChannelObj* channel) {
            if (channel->mStateFlags == 0 || channel->mStateFlags == 3)
                return true;
            else
                return false;
        }

        extern "C" void iplSDChannelObj_startAppear(SDChannelObj* channel, int request) {
            if (request & 0x10000U) {
                channel->mAnimationState = 0;
            } else if (request & 0x20000U) {
                channel->mAnimationState = 1;
            } else if ((channel->mAnimationState += 1) > 1) {
                return;
            }

            if (!(request & 1)) {
                iplSDChannelObj_setPageAnim(channel, 1);
            }
            if (!(request & 2)) {
                iplSDChannelObj_setDialogAnim(channel, 1);
            }
        }

        extern "C" void iplSDChannelObj_startDisappear(SDChannelObj* channel, int request) {
            if (request & 0x10000U) {
                channel->mAnimationState = 0;
            } else if (request & 0x20000U) {
                channel->mAnimationState = 1;
            } else if ((channel->mAnimationState -= 1) > 0) {
                return;
            }

            if (!(request & 1)) {
                iplSDChannelObj_setPageAnim(channel, 3);
            }
            if (!(request & 2)) {
                iplSDChannelObj_setDialogAnim(channel, 4);
            }
        }

        extern "C" void iplSDChannelObj_setSelected(SDChannelObj* channel, bool request) {
            if (request) {
                iplSDChannelObj_setPageAnim(channel, 1);
                channel->mAnimationState = 1;
            } else {
                iplSDChannelObj_setPageAnim(channel, 0);
                channel->mAnimationState = 0;
            }

            iplSDChannelObj_setDialogAnim(channel, 0);
        }

        extern "C" void iplSDChannelObj_playPageHide(SDChannelObj* channel) {
            iplSDChannelObj_setPageAnim(channel, 4);
        }

        extern "C" void iplSDChannelObj_resetPageAnim(SDChannelObj* channel, int request) {
            iplSDChannelObj_setPageAnim(channel, 0);
            if (request) {
                channel->mAnimationState = 0;
            }
        }

        extern "C" void iplSDChannelObj_resetDialogAnim(SDChannelObj* channel, bool request) {
            iplSDChannelObj_setDialogAnim(channel, 0);
            if (request) {
                channel->mAnimationState = 0;
            }
        }

        extern "C" void iplSDChannelObj_applyLanguageGroups(layout::Object* layout) {
            int lang = System::getLanguage();
            const char* langGroup = scLangGroups[lang];
            char availableLanguages[10][4] = {};

            bool languageFound = false;

            for (nw4r::lyt::GroupList::Iterator it = layout->getNW4RLyt()->GetGroupContainer()->GetGroupList().GetBeginIter();
                 it != layout->getNW4RLyt()->GetGroupContainer()->GetGroupList().GetEndIter(); it++) {
                if (strcmp(it->GetName(), langGroup) == 0) {
                    languageFound = true;
                } else {
                    bool languageGroup = true;
                    for (int i = 0; i < channel::MAX_ANIMS; i++) {
                        char name[8];
                        sprintf(name, "Rso%d", i);
                        if (strncmp(it->GetName(), name, 5) == 0) {
                            languageGroup = false;
                            break;
                        }
                    }

                    if (languageGroup) {
                        for (nw4r::lyt::PaneLinkList::Iterator it2 = it->GetPaneList().GetBeginIter();
                             it2 != it->GetPaneList().GetEndIter(); it2++) {
                            it2->mTarget->SetVisible(false);
                        }

                        for (int i = 0; i < 10; i++) {
                            if (strncmp(it->GetName(), scLangGroups[i], 3) == 0) {
                                memcpy(availableLanguages[i], it->GetName(), 3);
                                availableLanguages[i][3] = 0;
                                break;
                            }
                        }
                    }
                }
            }

            if (languageFound) {
                nw4r::lyt::Group* group = layout->getNW4RLyt()->GetGroupContainer()->FindGroupByName(langGroup);
                for (nw4r::lyt::PaneLinkList::Iterator it = group->GetPaneList().GetBeginIter();
                     it != group->GetPaneList().GetEndIter(); it++) {
                    it->mTarget->SetVisible(true);
                }
            } else {
                s32 region = System::getRegion();
                for (int i = 0; i < channel::MAX_ANIMS; i++) {
                    if (scRegionGroups[region][i] != NULL) {
                        if (strcmp(scRegionGroups[region][i], availableLanguages[scLangLookup[region][i]]) == 0) {
                            nw4r::lyt::Group* group = layout->getNW4RLyt()->GetGroupContainer()->FindGroupByName(scRegionGroups[region][i]);
                            for (nw4r::lyt::PaneLinkList::Iterator it = group->GetPaneList().GetBeginIter();
                                 it != group->GetPaneList().GetEndIter(); it++) {
                                it->mTarget->SetVisible(true);
                            }
                            break;
                        }
                    } else {
                        break;
                    }
                }
            }
        }

        extern "C" void iplSDChannelObj_createBaseLayout(SDChannelObj* channel) {
            bool adjust = false;
            if (channel->mpDialogLayout == NULL)
                iplSDChannelObj_createDialogLayout(channel);
            f32 frame;
            if (iplSDChannelObj_hasAppMeta(channel))
                frame = iplSDChannelObj_createIconLayout(channel);
            else {
                frame = iplSDChannelObj_createMenuLayout(channel);
                adjust = true;
            }
            iplSDChannelObj_syncLayoutsToPane(channel);
            if (channel->mpBaseAnimator != NULL)
                channel->mpBaseAnimator->play();
            channel->mpBaseLayout->finishBinding();
            if (channel->mpBaseAnimator != NULL)
                channel->mpBaseAnimator->setCurrentFrame(frame);
            if (adjust)
                channel->mpBaseLayout->adjustHeap();
        }

        extern "C" f32 iplSDChannelObj_createIconLayout(SDChannelObj* channel) {
            f32 frame = 0.0f;
            channel->mpBaseLayout =
                layout::Object::create(channel->mpHeap, 0x8000, channel->mpThumbnailData, "arc", "icon.brlyt");
            iplSDChannelObj_applyLanguageGroups(channel->mpBaseLayout);
            if (channel->mpBaseLayout->searchFile("icon.brlan"))
                channel->mpBaseAnimator = channel->mpBaseLayout->bind("icon.brlan");
            else if (channel->mpBaseLayout->searchFile("icon_Whole.brlan"))
                channel->mpBaseAnimator = channel->mpBaseLayout->bind("icon_Whole.brlan");
            else
                channel->mpBaseAnimator = NULL;
            if (channel->mpBaseAnimator != NULL) {
                f32 minimum = channel->mpBaseAnimator->getMinFrame();
                f32 maximum = channel->mpBaseAnimator->getMaxFrame();
                frame = minimum + (System::getRndm()->get_u16() % (u16)(maximum - minimum));
            }
            if (channel->mStateFlags == 0) {
                iplSDChannelObj_findNewMessageGroup(channel, channel->mpBaseLayout);
                channel->mNewMessageState = 1;
            }
            return frame;
        }

        extern "C" f32 iplSDChannelObj_createMenuLayout(SDChannelObj* channel) {
            channel->mpBaseLayout =
                layout::Object::create(channel->mpHeap, 0x8000, channel->mpLayoutFile, "arc", "mn_SdcardMenu_d.brlyt");
            channel->mpBaseAnimator = channel->mpBaseLayout->bind("mn_SdcardMenu_d.brlan");
            return System::getRndm()->get_u16() % 2000;
        }

        extern "C" void iplSDChannelObj_syncLayoutsToPane(SDChannelObj* channel) {
            iplSDChannelObj_updateNewMessage(channel);
            nw4r::math::VEC3 position(0, 0, 0);
            MTXMultVec(channel->mpPane->GetGlobalMtx(), position, position);
            channel->mpBaseLayout->GetRootPane()->SetTranslate(position);
            channel->mpBaseLayout->calc();
            iplSDChannelObj_setPageTranslate(channel, position);
            iplSDChannelObj_positionDialog(channel, position);
        }

        extern "C" void iplSDChannelObj_createPageLayout(SDChannelObj* channel) {
            channel->mpPageLayout = new (channel->mpDialogHeap, 4)
                layout::Object(channel->mpDialogHeap, channel->mpLayoutFile, "arc", "my_IplTop_d.brlyt");

            for (int i = 0; i < 3; i++) {
                channel->mpPageAnimators[i] = channel->mpPageLayout->bind(scCursorAnims[i], scCursur, false);
            }

            iplSDChannelObj_setPageAnim(channel, 0);
            channel->mpPageLayout->finishBinding();
        }

        extern "C" void iplSDChannelObj_setPageTranslate(SDChannelObj* channel, const nw4r::math::VEC3& vec) {
            channel->mpPageLayout->GetRootPane()->SetTranslate(vec);
            iplSDChannelObj_updatePageAnim(channel);
            channel->mpPageLayout->calc();
        }

        extern "C" void iplSDChannelObj_setPageAnim(SDChannelObj* channel, int request) {
            if (request == 0) {
                channel->mPageAnimation = 0;
                channel->mPageAnimationFrame = 0;

                for (int i = 0; i < 3; i++) {
                    channel->mpPageAnimators[i]->initFrame();
                }

                channel->mpPageLayout->getAnim(1)->initAnmFrame();
                channel->mpPageLayout->GetRootPane()->SetVisible(false);
            } else if (request == 4) {
                channel->mPageAnimation = 4;
                channel->mPageAnimationFrame = 0;
                channel->mpPageLayout->GetRootPane()->SetVisible(true);
                iplSDChannelObj_playPageAnimator(channel, 2);
            } else {
                switch (channel->mPageAnimation) {
                case 0: {
                    if (request == 1) {
                        channel->mPageAnimation = 1;
                        channel->mpPageLayout->GetRootPane()->SetVisible(true);
                        iplSDChannelObj_playPageAnimator(channel, 1);
                    }
                    break;
                }
                case 1: {
                    if (request == 2) {
                        channel->mPageAnimation = 2;
                    } else if (request == 3) {
                        channel->mPageAnimationFrame = 3;
                    } else if (request == 1) {
                        channel->mPageAnimationFrame = 0;
                    }
                    break;
                }
                case 2: {
                    if (request == 3) {
                        channel->mPageAnimation = 3;
                        iplSDChannelObj_playPageAnimator(channel, 0);
                    }
                    break;
                }
                case 3: {
                    if (request == 1) {
                        channel->mPageAnimationFrame = 1;
                    } else if (request == 3) {
                        channel->mPageAnimationFrame = 0;
                    }
                    break;
                }
                }
            }
        }

        extern "C" void iplSDChannelObj_updatePageAnim(SDChannelObj* channel) {
            switch (channel->mPageAnimation) {
            case 1: {
                if (!channel->mpPageAnimators[1]->isPlaying()) {
                    int prev = channel->mPageAnimationFrame;
                    switch (channel->mPageAnimation) {
                    case 0:
                        break;
                    case 1:
                        channel->mPageAnimation = 2;
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    default:
                        break;
                    }
                    if (prev == 3) {
                        iplSDChannelObj_setPageAnim(channel, 3);
                        channel->mPageAnimationFrame = 0;
                    }
                }
                break;
            }
            case 3: {
                if (!channel->mpPageAnimators[0]->isPlaying()) {
                    int prev = channel->mPageAnimationFrame;
                    iplSDChannelObj_setPageAnim(channel, 0);
                    if (prev == 1) {
                        iplSDChannelObj_setPageAnim(channel, 1);
                    }
                }
                break;
            }
            case 4: {
                if (!channel->mpPageAnimators[2]->isPlaying()) {
                    iplSDChannelObj_setPageAnim(channel, 0);
                }
                break;
            }
            }
        }

        extern "C" void iplSDChannelObj_playPageAnimator(SDChannelObj* channel, int request) {
            channel->mpPageAnimators[request]->setAnmType(ANIM_TYPE_FORWARD);
            channel->mpPageAnimators[request]->play();
        }

        extern "C" void iplSDChannelObj_createDialogLayout(SDChannelObj* channel) {
            if (!iplSDChannelObj_hasAppMeta(channel)) {
                channel->mpDialogLayout = NULL;
                return;
            }
            channel->mpDialogLayout = new (channel->mpChannelHeap, 4)
                layout::Object(channel->mpChannelHeap, channel->mpLayoutFile, "arc", "my_IplTopBalloon_a.brlyt");
            if (channel->mStateFlags == 0)
                iplSDChannelObj_setBalloonText(channel, iplSDChannelObj_getLocalizedName(channel, 0));
            else if (channel->mStateFlags == 3)
                iplSDChannelObj_setBalloonText(channel, scUnknownName);
            else
                iplSDChannelObj_setBalloonText(channel, L"");
            channel->mpDialogAnimator = channel->mpDialogLayout->bind("my_IplTopBalloon_a_BalloonInOut.brlan");
            iplSDChannelObj_setDialogAnim(channel, 0);
            channel->mpDialogLayout->finishBinding();
        }

        extern "C" const wchar_t* iplSDChannelObj_getLocalizedName(SDChannelObj* channel, int index) {
            if (channel->mAppMeta.metaHdr.names[System::getLanguage()][index][0] != 0)
                return channel->mAppMeta.metaHdr.names[System::getLanguage()][index];
            const u32* languages = scLangLookup[System::getRegion()];
            for (int i = 0; i < 16; ++i) {
                if (channel->mAppMeta.metaHdr.names[languages[i]][index][0] != 0)
                    return channel->mAppMeta.metaHdr.names[languages[i]][index];
                if (languages[i] == -1)
                    break;
            }
            return channel->mAppMeta.metaHdr.names[languages[0]][index];
        }

        extern "C" void iplSDChannelObj_setBalloonText(SDChannelObj* channel, const wchar_t* text) {
            nw4r::lyt::TextBox* textPane =
                nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(channel->mpDialogLayout->FindPaneByName(scBalloon));

            wchar_t titleText[channel::META_CHANNEL_NAME_LENGTH + 3] = L"";
            u32 titleLength;

            wcsncpy(titleText, text, channel::META_CHANNEL_NAME_LENGTH);
            titleLength = wcslen(titleText);

            f32 ellipsisWidth = 0.0f;
            int ellipsisLength = 0;

            if (titleLength == 0) {
                textPane->SetString(titleText, 0, 1);
            } else {
                for (u32 i = titleLength; i != 0; i--) {
                    textPane->SetString(titleText, 0, i + ellipsisLength);
                    textPane->CalculateMtx(*channel->mpDialogLayout->getDrawInfo());

                    nw4r::ut::Rect textRect = textPane->GetTextDrawRect(*channel->mpDialogLayout->getDrawInfo());
                    if (textRect.GetWidth() <= ellipsisWidth + 391.5f) {
                        break;
                    }

                    if (System::getRegion() == SC_PRODUCT_AREA_JPN) {
                        titleText[i - 1] = NULL;
                        titleText[i - 2] = L'…';
                    } else {
                        ellipsisWidth = -1.179962f;
                        ellipsisLength = 2;
                        titleText[i + 1] = NULL;
                        titleText[i] = '.';
                        titleText[i - 1] = '.';
                        titleText[i - 2] = '.';
                    }
                }
            }

            nw4r::ut::Rect textRect = textPane->GetTextDrawRect(*channel->mpDialogLayout->getDrawInfo());

            nw4r::lyt::Size newSize(channel->mpDialogLayout->FindPaneByName(scBase)->GetSize());
            newSize.width = textRect.right - textRect.left + 40.0f;

            if (newSize.width < channel->mAspectRatioScale * 160.0f) {
                newSize.width = channel->mAspectRatioScale * 160.0f;
            }

            channel->mpDialogLayout->FindPaneByName(scShade)->SetSize(newSize);
            channel->mpDialogLayout->FindPaneByName(scBase)->SetSize(newSize);
        }

        extern "C" void iplSDChannelObj_positionDialog(SDChannelObj* channel, const nw4r::math::VEC3& vec) {
            if (channel->mpDialogLayout != NULL) {
                nw4r::lyt::Size size;

                size = channel->mpDialogLayout->FindPaneByName(scBase)->GetSize();

                f32 verticalOffset = -2.0f + ((size.height / 2) + channel->mOffsetY);
                verticalOffset *= -1.0f;

                nw4r::ut::Rect projRect;
                System::getProjectionRect(&projRect);

                f32 centerX = vec.x;
                f32 halfWidth = size.width / 2;
                f32 horizontalOffset = 0.0f;
                f32 leftMargin = (centerX - halfWidth) - projRect.left;
                f32 rightMargin = projRect.right - (centerX + halfWidth);
                if (leftMargin < 60.0f) {
                    horizontalOffset = 60.0f - leftMargin;
                } else if (rightMargin < 60.0f) {
                    horizontalOffset = rightMargin - 60.0f;
                }

                const nw4r::math::VEC3 pos(vec.x + horizontalOffset, vec.y + verticalOffset, 0.0f);
                channel->mpDialogLayout->GetRootPane()->SetTranslate(pos);

                iplSDChannelObj_updateDialogAnim(channel);
                channel->mpDialogLayout->calc();
            }
        }

        extern "C" void iplSDChannelObj_setDialogAnim(SDChannelObj* channel, int request) {
            if (channel->mpDialogLayout != NULL) {
                if (request == 0) {
                    channel->mDialogState = 0;
                    channel->mDialogFrame = 0;

                    channel->mpDialogLayout->setMinFrame(0.0f);
                    channel->mpDialogLayout->GetRootPane()->SetVisible(false);
                } else {
                    switch (channel->mDialogState) {
                    case 0: {
                        if (request == 1) {
                            channel->mDialogTimer = 0;
                            channel->mDialogState = 1;
                        }
                        break;
                    }
                    case 1: {
                        if (request == 2) {
                            channel->mDialogState = 2;
                            channel->mpDialogLayout->GetRootPane()->SetVisible(true);
                            channel->mpDialogLayout->setAnmType(ANIM_TYPE_FORWARD);
                            channel->mpDialogLayout->start();
                            snd::getSystem()->startSE("WIPL_SE_BALLOON");
                        } else if (request == 4) {
                            channel->mDialogState = 0;
                        }
                        break;
                    }
                    case 2: {
                        if (request == 3) {
                            channel->mDialogState = 3;
                        } else if (request == 4) {
                            channel->mDialogFrame = 4;
                        } else if (request == 1) {
                            channel->mDialogFrame = 0;
                        }
                        break;
                    }
                    case 3: {
                        if (request == 4) {
                            channel->mDialogState = 4;
                            channel->mpDialogLayout->setAnmType(ANIM_TYPE_BACKWARD);
                            channel->mpDialogLayout->start();
                        }
                        break;
                    }
                    case 4: {
                        if (request == 1) {
                            channel->mDialogFrame = 1;
                        } else if (request == 4) {
                            channel->mDialogFrame = 0;
                        }
                        break;
                    }
                    }
                }
            }
        }

        extern "C" void iplSDChannelObj_updateDialogAnim(SDChannelObj* channel) {
            switch (channel->mDialogState) {
            case 1: {
                if ((reinterpret_cast<u32&>(channel->mDialogTimer) += 1) >= 20.0f) {
                    iplSDChannelObj_setDialogAnim(channel, 2);
                    break;
                }
            }
            case 3: {
                break;
            }
            case 2: {
                if (!channel->mpDialogLayout->isPlaying(0)) {
                    int prev = channel->mDialogFrame;
                    iplSDChannelObj_setDialogAnim(channel, 3);
                    if (prev == 4) {
                        iplSDChannelObj_setDialogAnim(channel, 4);
                        channel->mDialogFrame = 0;
                    }
                }
                break;
            }
            case 4: {
                if (!channel->mpDialogLayout->isPlaying(0)) {
                    int prev = channel->mDialogFrame;
                    iplSDChannelObj_setDialogAnim(channel, 0);
                    if (prev == 1) {
                        iplSDChannelObj_setDialogAnim(channel, 1);
                    }
                }
                break;
            }
            }
        }

        extern "C" void iplSDChannelObj_findNewMessageGroup(SDChannelObj* channel, layout::Object* layout) {
            char groupName[20];
            char** lookup;
            nw4r::lyt::Group* group;

            group = layout->FindGroupByName("New");
            if (group != NULL) {
                channel->mpNewMessageGroup = group;
            } else {
                sprintf(groupName, "New_%s", scLangGroups[System::getLanguage()]);

                group = layout->FindGroupByName(groupName);
                if (group != NULL) {
                    channel->mpNewMessageGroup = group;
                } else {
                    lookup = (char**)scRegionGroups[System::getRegion()];

                    for (int i = 0; lookup[i] != NULL; i++) {
                        sprintf(groupName, "New_%s", lookup[i]);

                        group = layout->FindGroupByName(groupName);
                        if (group != NULL) {
                            channel->mpNewMessageGroup = group;
                            break;
                        }
                    }
                }
            }

            if (group != NULL) {
                for (nw4r::lyt::PaneLinkList::Iterator it = group->GetPaneList().GetBeginIter();
                     it != group->GetPaneList().GetEndIter(); it++) {
                    it->mTarget->UnbindAllAnimation();
                }

                if (layout->searchFile("icon_New.brlan")) {
                    channel->mpNewMessageAnimator = layout->bindToGroup("icon_New.brlan", group);
                }
            }
        }

        extern "C" void iplSDChannelObj_updateNewMessage(SDChannelObj* channel) {
            if (System::getNwc24Manager() != NULL) {
                switch (channel->mNewMessageState) {
                case 1: {
                    if (iplSDChannelObj_checkNewMessage(channel)) {
                        channel->mNewMessageState = 2;
                        channel->mNewMessageFrame = 0;
                    }
                    break;
                }
                case 2: {
                    if (++reinterpret_cast<u32&>(channel->mNewMessageFrame) >= 4200) {
                        channel->mNewMessageState = 1;
                    }
                    break;
                }
                }
            }
        }

        extern "C" BOOL iplSDChannelObj_checkNewMessage(SDChannelObj* channel) {
            if (System::getNwc24Manager() == NULL || !System::getNwc24Manager()->getNewTitleTbl(NULL)) {
                return FALSE;
            }

            u32 titleCode = ES_TITLE_CODE(channel->mAppMeta.titleId);
            if (!System::getNwc24Manager()->isNewMessageThere(titleCode)) {
                return TRUE;
            }

            if (!channel->mbNewMessageGroupActive) {
                if (channel->mpNewMessageGroup != NULL) {
                    for (nw4r::lyt::PaneLinkList::Iterator it =
                             channel->mpNewMessageGroup->GetPaneList().GetBeginIter();
                         it != channel->mpNewMessageGroup->GetPaneList().GetEndIter(); it++) {
                        it->mTarget->SetVisible(true);
                    }

                    if (channel->mpNewMessageAnimator != NULL) {
                        channel->mpNewMessageAnimator->play();
                    }
                }

                channel->mbNewMessageGroupActive = true;
            }

            return TRUE;
        }
    } // namespace scene
} // namespace ipl
