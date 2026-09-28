#include "scene/sdChannelSelect/iplSDChannelObj.h"

#include <private/es.h>
#include <revolution/os.h>
#include <revolution/sc.h>

#include "iplSound.h"
#include "iplSystem.h"

namespace ipl {
    namespace scene {
        // clang-format off
        extern "C" const wchar_t scInvalidTitleName[] = L"???";

        extern "C" char lbl_81654B38[] = "Cursur_a";

        static const char* scCursur = lbl_81654B38;

        static const char* scCursorAnims[] = {
            "my_IplTop_d_FocusOff.brlan",
            "my_IplTop_d_FocusOn.brlan",
            "my_IplTop_d_Select.brlan",
        };

        extern "C" const char* lbl_81654B9C = "T_Balloon";

        extern "C" const char* lbl_81696DD8 = "W_Base";
        extern "C" const char* lbl_81696DE4 = "W_Shade";

        static const char* scLangGroups[] = {
            "JPN",
            "ENG",
            "GER",
            "FRA",
            "SPA",
            "ITA",
            "NED",
            "CHN",
            "ENG",
            "KOR",
        };

        static const char* scLangGroupLookup[SC_PRODUCT_AREA_MAX][16] = {
            // Japan
            {
                "JPN",
                NULL,
            },
            // USA
            {
                "ENG",
                "FRA",
                "SPA",
                NULL,
            },
            // Europe
            {
                "ENG",
                "FRA",
                "GER",
                "SPA",
                "ITA",
                "NED",
                NULL,
            },
            {
                NULL,
            },
            {
                NULL,
            },
            {
                NULL,
            },
            // Korean
            {
                "KOR",
                NULL,
            },
            {
                NULL,
            },
            {
                NULL,
            },
            {
                NULL,
            },
            {
                NULL,
            },
            // China
            {
                "CHN",
                NULL,
            },
        };

        static const u32 scLangLookup[SC_PRODUCT_AREA_MAX][16] = {
            // Japan
            {
                SC_LANG_JAPANESE,
                -1
            },
            // USA
            {
                SC_LANG_ENGLISH,
                SC_LANG_FRENCH,
                SC_LANG_SPANISH,
                -1
            },
            // Europe
            {
                SC_LANG_ENGLISH,
                SC_LANG_FRENCH,
                SC_LANG_GERMAN,
                SC_LANG_SPANISH,
                SC_LANG_ITALIAN,
                SC_LANG_DUTCH,
                -1
            },
            {
                -1
            },
            {
                -1
            },
            {
                -1
            },
            // Korean
            {
                SC_LANG_KOREAN,
                -1
            },
            {
                -1
            },
            {
                -1
            },
            {
                -1
            },
            {
                -1
            },
            // China
            {
                SC_LANG_SIMP_CHINESE,
                -1
            },
        };

        const float cfChanThumbOfss[][2] = {
            {
                64.0f, 48.0f
            },
            {
                85.0f, 48.0f
            }
        };
        // clang-format on

        SDChannelObj::SDChannelObj(EGG::Heap* heap, int page, int index)
            : mpCursorHeap(NULL), mpBalloonHeap(NULL), mpMainHeap(heap), mState(STATE_LOAD_THUMBNAIL), mChanPage(page),
              mChanIndex(index), mpBasePane(NULL), mpThumbLayout(NULL), mpCursorLayout(NULL), unk_0x44(0), unk_0x48(0),
              mpBalloonLayout(NULL), unk_0x54(0), unk_0x58(0), unk_0x5C(0), unk_0x60(0), mpNwc24NewGroup(NULL),
              mpNwc24NewAnim(NULL), mbNwc24NewPlayAnim(false), unk_0x70(0), unk_0x74(0),
              mThumbWidth(cfChanThumbOfss[SCGetAspectRatio()][0]), mThumbHeight(cfChanThumbOfss[SCGetAspectRatio()][1]),
              mChanType(1), mpThumbBuffer(NULL) {
            if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
                nw4r::ut::Rect projRect4x3;
                System::getProjectionRect4x3(&projRect4x3);
                nw4r::ut::Rect projRect16x9;
                System::getProjectionRect16x9(&projRect16x9);

                mLocationAdjust = projRect16x9.GetWidth() / projRect4x3.GetWidth();
            } else {
                mLocationAdjust = 1.0f;
            }

            memset(&mTitleID, 0, 0x608);
        }

        SDChannelObj::~SDChannelObj() {
            if (mpThumbLayout != NULL) {
                mpThumbLayout->destroyHeap();
            }

            if (mpCursorLayout != NULL) {
                delete mpCursorLayout;
            }

            if (mpBalloonLayout != NULL) {
                delete mpBalloonLayout;
            }
        }

        void SDChannelObj::prepare() {
            if (mState == STATE_LOAD_THUMBNAIL) {
                mState = STATE_CREATE_THUMBNAIL;
            }
        }

        void SDChannelObj::setHeaps(EGG::Heap* cursorHeap, EGG::Heap* balloonHeap) {
            mpCursorHeap = cursorHeap;
            mpBalloonHeap = balloonHeap;
        }

        void* SDChannelObj::allocThumbBuffer() {
            if (mpThumbBuffer == NULL) {
                mpThumbBuffer = new (mpMainHeap, 0x20) u8[0x19000];
            }
            return mpThumbBuffer;
        }

        void SDChannelObj::setBasePane(const nw4r::lyt::Pane* basePane) {
            mpBasePane = (nw4r::lyt::Pane*)basePane;
        }

        void SDChannelObj::create(nand::LayoutFile* sysLayoutFile) {
            if (!isLayoutCreated()) {
                mpSysLayoutFile = sysLayoutFile;

                if (mpCursorLayout == NULL) {
                    initCursor();
                }

                if (mpBalloonLayout == NULL) {
                    initBalloon();
                }

                if (mState == STATE_CREATE_THUMBNAIL || mState == STATE_WAIT_LOAD_THUMBNAIL && mpThumbFile->isFinished()) {
                    createThumbnail();
                    mState = STATE_NORMAL;
                }
            }
        }

        void SDChannelObj::calc() {
            switch (mState) {
                case STATE_LOAD_THUMBNAIL: {
                    mState = STATE_CREATE_THUMBNAIL;
                    break;
                }
                case STATE_WAIT_LOAD_THUMBNAIL: {
                    if (!mpThumbFile->isFinished()) {
                        break;
                    }
                    mState = STATE_CREATE_THUMBNAIL;
                }
                case STATE_CREATE_THUMBNAIL: {
                    createThumbnail();
                    mState = STATE_NORMAL;
                    break;
                }
                case STATE_NORMAL: {
                    calcNormal();
                    break;
                }
            }
        }

        void SDChannelObj::drawThumbnail() {
            if (isLayoutCreated()) {
                mpThumbLayout->draw();
            }
        }

        void SDChannelObj::drawCursor() {
            mpCursorLayout->draw();
        }

        void SDChannelObj::drawBalloon() {
            if (mpBalloonLayout != NULL) {
                mpBalloonLayout->draw();
            }
        }

        nw4r::math::VEC3& SDChannelObj::getTranslate() const {
            return (nw4r::math::VEC3&)mpThumbLayout->GetRootPane()->GetTranslate();
        }

        BOOL SDChannelObj::isValid() const {
            if (mChanType == 0 || mChanType == 3) {
                return TRUE;
            } else {
                return FALSE;
            }
        }

        void SDChannelObj::onPoint(int unk) {
            if (unk & 0x10000U) {
                unk_0x60 = 0;
            } else if (unk & 0x20000U) {
                unk_0x60 = 1;
            } else if ((unk_0x60 += 1) > 1) {
                return;
            }

            if (!(unk & 1)) {
                setCursorAnim(1);
            }
            if (!(unk & 2)) {
                setBalloonAnim(1);
            }
        }

        void SDChannelObj::onLeft(int unk) {
            if (unk & 0x10000U) {
                unk_0x60 = 0;
            } else if (unk & 0x20000U) {
                unk_0x60 = 1;
            } else if ((unk_0x60 -= 1) > 0) {
                return;
            }

            if (!(unk & 1)) {
                setCursorAnim(3);
            }
            if (!(unk & 2)) {
                setBalloonAnim(4);
            }
        }

        void SDChannelObj::onPinch(bool unk) {
            if (unk) {
                setCursorAnim(1);
                unk_0x60 = 1;
            } else {
                setCursorAnim(0);
                unk_0x60 = 0;
            }

            setBalloonAnim(0);
        }

        void SDChannelObj::setCursorDecideAnim() {
            setCursorAnim(4);
        }

        void SDChannelObj::initCursorAnim(bool unk) {
            setCursorAnim(0);
            if (unk) {
                unk_0x60 = 0;
            }
        }

        void SDChannelObj::initBalloonAnim(bool unk) {
            setBalloonAnim(0);
            if (unk) {
                unk_0x60 = 0;
            }
        }

        void SDChannelObj::setLangPane(const layout::Object* layout) {
            int lang = System::getLanguage();
            const char* langGroup = scLangGroups[lang];
            char local_50[10][4] = {""};

            bool bVar4 = false;

            for (nw4r::lyt::GroupList::Iterator it = layout->GetGroupList().GetBeginIter(); it != layout->GetGroupList().GetEndIter(); it++) {
                if (strcmp(it->GetName(), langGroup) == 0) {
                    bVar4 = true;
                } else {
                    bool bVar3 = true;
                    for (int i = 0; i < 16; i++) {
                        char name[8];
                        sprintf(name, "Rso%d", i);
                        if (strncmp(it->GetName(), name, 5) == 0) {
                            bVar3 = false;
                            break;
                        }
                    }

                    if (bVar3) {
                        for (nw4r::lyt::PaneLinkList::Iterator it2 = it->GetPaneList().GetBeginIter(); it2 != it->GetPaneList().GetEndIter(); it2++) {
                            it2->mTarget->SetVisible(false);
                        }

                        for (int i = 0; i < 10; i++) {
                            if (strncmp(it->GetName(), scLangGroups[i], 3) == 0) {
                                memcpy(local_50[i], it->GetName(), 3);
                                local_50[i][3] = 0;
                                break;
                            }
                        }
                    }
                }
            }

            if (bVar4) {
                nw4r::lyt::Group* group = layout->FindGroupByName(langGroup);
                for (nw4r::lyt::PaneLinkList::Iterator it = group->GetPaneList().GetBeginIter(); it != group->GetPaneList().GetEndIter(); it++) {
                    it->mTarget->SetVisible(true);
                }
            } else {
                s32 region = System::getRegion();
                for (int i = 0; i < 16; i++) {
                    if (scLangGroupLookup[region][i] == NULL) {
                        break;
                    }

                    if (strcmp(scLangGroupLookup[region][i], local_50[scLangLookup[region][i]]) == 0) {
                        nw4r::lyt::Group* group = layout->FindGroupByName(scLangGroupLookup[region][i]);
                        for (nw4r::lyt::PaneLinkList::Iterator it = group->GetPaneList().GetBeginIter();
                             it != group->GetPaneList().GetEndIter(); it++) {
                            it->mTarget->SetVisible(true);
                        }
                        break;
                    }
                }
            }
        }

        void SDChannelObj::createThumbnail() {
            bool bVar1 = false;

            if (mpBalloonLayout == NULL) {
                initBalloon();
            }

            f32 frame;

            if (isValid()) {
                frame = createSDThumbnail();
            } else {
                frame = createEmptyThumbnail();
                bVar1 = true;
            }

            calcNormal();

            if (mpThumbAnim != NULL) {
                mpThumbAnim->play();
            }
            mpThumbLayout->finishBinding();
            if (mpThumbAnim != NULL) {
                mpThumbAnim->setCurrentFrame(frame);
            }

            if (bVar1) {
                mpThumbLayout->adjustHeap();
            }
        }

        extern "C" char lbl_81654BB8[] = "icon.brlyt";

        f32 SDChannelObj::createSDThumbnail() {
            f32 frame = 0.0f;

            mpThumbLayout = layout::Object::create(mpMainHeap, 0x18000, mpThumbBuffer, "arc", lbl_81654BB8);
            setLangPane(mpThumbLayout);

            if (mpThumbLayout->searchFile("icon.brlan")) {
                mpThumbAnim = mpThumbLayout->bind("icon.brlan");
            } else if (mpThumbLayout->searchFile("icon_Whole.brlan")) {
                mpThumbAnim = mpThumbLayout->bind("icon_Whole.brlan");
            } else {
                mpThumbAnim = NULL;
            }

            if (mpThumbAnim != NULL) {
                f32 minFrame = mpThumbAnim->getMinFrame();
                f32 maxFrame = mpThumbAnim->getMaxFrame();
                frame = minFrame + (System::getRndm()->get_u16() % (u16)(maxFrame - minFrame));
            }

            if (mChanType == 0) {
                bindNewAnm(mpThumbLayout);
                unk_0x70 = 1;
            }

            return frame;
        }

        extern "C" char lbl_81654BC4[] = "mn_SdcardMenu_d.brlyt";
        extern "C" char lbl_81654BDA[] = "mn_SdcardMenu_d.brlan";

        f32 SDChannelObj::createEmptyThumbnail() {
            mpThumbLayout = layout::Object::create(mpMainHeap, 0x8000, mpSysLayoutFile, "arc", lbl_81654BC4);
            mpThumbAnim = mpThumbLayout->bind(lbl_81654BDA);

            return System::getRndm()->get_u16() % 2000;
        }

        void SDChannelObj::calcNormal() {
            updateNew();

            nw4r::math::VEC3 pos(0, 0, 0);

            MTXMultVec(mpBasePane->GetGlobalMtx(), pos, pos);
            mpThumbLayout->GetRootPane()->SetTranslate(pos);

            mpThumbLayout->calc();

            calcCursor(pos);
            calcBalloon(pos);
        }

        extern "C" char lbl_81654BF0[] = "my_IplTop_d.brlyt";
        extern "C" char lbl_81654C02[] = "my_IplTopBalloon_a.brlyt";
        extern "C" char lbl_81654C1B[] = "my_IplTopBalloon_a_BalloonInOut.brlan";

        void SDChannelObj::initCursor() {
            mpCursorLayout = new (mpCursorHeap, 4) layout::Object(mpCursorHeap, mpSysLayoutFile, "arc", lbl_81654BF0);

            for (int i = 0; i < ANIM_CURSOR_MAX; i++) {
                mpCursorAnims[i] = mpCursorLayout->bind(scCursorAnims[i], scCursur, false);
            }

            setCursorAnim(0);
            mpCursorLayout->finishBinding();
        }

        void SDChannelObj::calcCursor(const nw4r::math::VEC3& vec) {
            mpCursorLayout->GetRootPane()->SetTranslate(vec);
            calcCursorAnim();
            mpCursorLayout->calc();
        }

        void SDChannelObj::setCursorAnim(int unk) {
            if (unk == 0) {
                unk_0x44 = 0;
                unk_0x48 = 0;

                for (int i = 0; i < ANIM_CURSOR_MAX; i++) {
                    mpCursorAnims[i]->initFrame();
                }

                mpCursorLayout->getAnim(1)->initAnmFrame();
                mpCursorLayout->GetRootPane()->SetVisible(false);
            } else if (unk == 4) {
                unk_0x44 = 4;
                unk_0x48 = 0;
                mpCursorLayout->GetRootPane()->SetVisible(true);
                startCursorAnim(2);
            } else {
                switch (unk_0x44) {
                    case 0: {
                        if (unk == 1) {
                            unk_0x44 = 1;
                            mpCursorLayout->GetRootPane()->SetVisible(true);
                            startCursorAnim(1);
                        }
                        break;
                    }
                    case 1: {
                        if (unk == 2) {
                            unk_0x44 = 2;
                        } else if (unk == 3) {
                            unk_0x48 = 3;
                        } else if (unk == 1) {
                            unk_0x48 = 0;
                        }
                        break;
                    }
                    case 2: {
                        if (unk == 3) {
                            unk_0x44 = 3;
                            startCursorAnim(0);
                        }
                        break;
                    }
                    case 3: {
                        if (unk == 1) {
                            unk_0x48 = 1;
                        } else if (unk == 3) {
                            unk_0x48 = 0;
                        }
                        break;
                    }
                }
            }
        }

        void SDChannelObj::calcCursorAnim() {
            switch (unk_0x44) {
                case 1: {
                    if (!mpCursorAnims[ANIM_CURSOR_FOCUS_ON]->isPlaying()) {
                        int prev = unk_0x48;
                        switch (unk_0x44) {
                            case 0:
                                break;
                            case 1:
                                unk_0x44 = 2;
                                break;
                            case 2:
                                break;
                            case 3:
                                break;
                            default:
                                break;
                        }
                        if (prev == 3) {
                            setCursorAnim(3);
                            unk_0x48 = 0;
                        }
                    }
                    break;
                }
                case 3: {
                    if (!mpCursorAnims[ANIM_CURSOR_FOCUS_OFF]->isPlaying()) {
                        int prev = unk_0x48;
                        setCursorAnim(0);
                        if (prev == 1) {
                            setCursorAnim(1);
                        }
                    }
                    break;
                }
                case 4: {
                    if (!mpCursorAnims[ANIM_CURSOR_SELECT]->isPlaying()) {
                        setCursorAnim(0);
                    }
                    break;
                }
            }
        }

        void SDChannelObj::startCursorAnim(int unk) {
            mpCursorAnims[unk]->setAnmType(ANIM_TYPE_FORWARD);
            mpCursorAnims[unk]->play();
        }

        void SDChannelObj::initBalloon() {
            if (!isValid()) {
                mpBalloonLayout = NULL;
                return;
            }
            mpBalloonLayout = new (mpBalloonHeap, 4) layout::Object(mpBalloonHeap, mpSysLayoutFile, "arc", lbl_81654C02);

            if (mChanType == 0) {
                setBalloonText(getTitleName(0));
            } else if (mChanType == 3) {
                setBalloonText(scInvalidTitleName);
            } else {
                setBalloonText(L"");
            }

            mpBalloonAnim = mpBalloonLayout->bind(lbl_81654C1B);
            setBalloonAnim(0);
            mpBalloonLayout->finishBinding();
        }

        const wchar_t* SDChannelObj::getTitleName(int index) {
            if (mTitleNames[System::getLanguage()][index][0] != 0) {
                return mTitleNames[System::getLanguage()][index];
            }

            const u32* lookup = scLangLookup[System::getRegion()];
            for (int i = 0; i < 16; i++) {
                if (mTitleNames[lookup[i]][index][0] != 0) {
                    return mTitleNames[lookup[i]][index];
                }
                if (lookup[i] == -1) {
                    break;
                }
            }

            return mTitleNames[lookup[0]][index];
        }

        void SDChannelObj::setBalloonText(const wchar_t* text) {
            nw4r::lyt::TextBox* textPane = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpBalloonLayout->FindPaneByName(lbl_81654B9C));

            wchar_t fullStr[0x14 + 3] = L"";
            u32 strLen;

            wcsncpy(fullStr, text, 0x14);
            strLen = wcslen(fullStr);

            f32 temp1 = 0.0f;
            int extraLen = 0;

            if (strLen == 0) {
                textPane->SetString(fullStr, 0, 1);
            } else {
                for (u32 i = strLen; i != 0; i--) {
                    textPane->SetString(fullStr, 0, i + extraLen);
                    textPane->CalculateMtx(*mpBalloonLayout->getDrawInfo());

                    nw4r::ut::Rect textRect = textPane->GetTextDrawRect(*mpBalloonLayout->getDrawInfo());
                    if (textRect.GetWidth() <= temp1 + 391.5f) {
                        break;
                    }

                    if (System::getRegion() == SC_PRODUCT_AREA_JPN) {
                        fullStr[i - 1] = NULL;
                        fullStr[i - 2] = L'…';
                    } else {
                        temp1 = -1.179962f;
                        extraLen = 2;
                        fullStr[i + 1] = NULL;
                        fullStr[i] = '.';
                        fullStr[i - 1] = '.';
                        fullStr[i - 2] = '.';
                    }
                }
            }

            nw4r::ut::Rect textRect = textPane->GetTextDrawRect(*mpBalloonLayout->getDrawInfo());

            nw4r::lyt::Size newSize(mpBalloonLayout->FindPaneByName(lbl_81696DD8)->GetSize());
            newSize.width = textRect.right - textRect.left + 40.0f;

            if (newSize.width < mLocationAdjust * 160.0f) {
                newSize.width = mLocationAdjust * 160.0f;
            }

            mpBalloonLayout->FindPaneByName(lbl_81696DE4)->SetSize(newSize);
            mpBalloonLayout->FindPaneByName(lbl_81696DD8)->SetSize(newSize);
        }

        void SDChannelObj::calcBalloon(const nw4r::math::VEC3& vec) {
            if (mpBalloonLayout != NULL) {
                nw4r::lyt::Size size;

                size = mpBalloonLayout->FindPaneByName(lbl_81696DD8)->GetSize();

                f32 val = -2.0f + ((size.height / 2) + mThumbHeight);
                val *= -1.0f;

                nw4r::ut::Rect projRect;
                System::getProjectionRect(&projRect);

                f32 temp_f2 = vec.x;
                f32 temp_f5 = size.width / 2;
                f32 val2 = 0.0f;
                f32 val3 = (temp_f2 - temp_f5) - projRect.left;
                f32 val1 = projRect.right - (temp_f2 + temp_f5);
                if (val3 < 60.0f) {
                    val2 = 60.0f - val3;
                } else if (val1 < 60.0f) {
                    val2 = val1 - 60.0f;
                }

                const nw4r::math::VEC3 pos(vec.x + val2, vec.y + val, 0.0f);
                mpBalloonLayout->GetRootPane()->SetTranslate(pos);

                calcBalloonAnim();
                mpBalloonLayout->calc();
            }
        }

        extern "C" char lbl_81654C58[] = "WIPL_SE_BALLOON";

        void SDChannelObj::setBalloonAnim(int unk) {
            if (mpBalloonLayout != NULL) {
                if (unk == 0) {
                    unk_0x54 = 0;
                    unk_0x58 = 0;

                    mpBalloonLayout->setMinFrame(0.0f);
                    mpBalloonLayout->GetRootPane()->SetVisible(false);
                } else {
                    switch (unk_0x54) {
                        case 0: {
                            if (unk == 1) {
                                unk_0x5C = 0;
                                unk_0x54 = 1;
                            }
                            break;
                        }
                        case 1: {
                            if (unk == 2) {
                                unk_0x54 = 2;
                                mpBalloonLayout->GetRootPane()->SetVisible(true);
                                mpBalloonLayout->setAnmType(ANIM_TYPE_FORWARD);
                                mpBalloonLayout->start();
                                snd::getSystem()->startSE(lbl_81654C58);
                            } else if (unk == 4) {
                                unk_0x54 = 0;
                            }
                            break;
                        }
                        case 2: {
                            if (unk == 3) {
                                unk_0x54 = 3;
                            } else if (unk == 4) {
                                unk_0x58 = 4;
                            } else if (unk == 1) {
                                unk_0x58 = 0;
                            }
                            break;
                        }
                        case 3: {
                            if (unk == 4) {
                                unk_0x54 = 4;
                                mpBalloonLayout->setAnmType(ANIM_TYPE_BACKWARD);
                                mpBalloonLayout->start();
                            }
                            break;
                        }
                        case 4: {
                            if (unk == 1) {
                                unk_0x58 = 1;
                            } else if (unk == 4) {
                                unk_0x58 = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }

        void SDChannelObj::calcBalloonAnim() {
            switch (unk_0x54) {
                case 1: {
                    if ((reinterpret_cast<u32&>(unk_0x5C) += 1) >= 20.0f) {
                        setBalloonAnim(2);
                        break;
                    }
                }
                case 3: {
                    break;
                }
                case 2: {
                    if (!mpBalloonLayout->isPlaying(0)) {
                        int prev = unk_0x58;
                        setBalloonAnim(3);
                        if (prev == 4) {
                            setBalloonAnim(4);
                            unk_0x58 = 0;
                        }
                    }
                    break;
                }
                case 4: {
                    if (!mpBalloonLayout->isPlaying(0)) {
                        int prev = unk_0x58;
                        setBalloonAnim(0);
                        if (prev == 1) {
                            setBalloonAnim(1);
                        }
                    }
                    break;
                }
            }
        }

        void SDChannelObj::bindNewAnm(layout::Object* layout) {
            char grpName[20];
            const char** lookup;
            nw4r::lyt::Group* group;

            // Look for "New" group first.
            // If that doesn't exist, look for "New_%d" group based on the System language.
            // If That doesn't exist, look for "New_%d" group based on the System region.
            // If THAT doesn't exist, uhhh oh well.
            group = layout->FindGroupByName("New");
            if (group != NULL) {
                mpNwc24NewGroup = group;
            } else {
                sprintf(grpName, "New_%s", scLangGroups[System::getLanguage()]);

                group = layout->FindGroupByName(grpName);
                if (group != NULL) {
                    mpNwc24NewGroup = group;
                } else {
                    lookup = scLangGroupLookup[System::getRegion()];

                    for (int i = 0; lookup[i] != NULL; i++) {
                        sprintf(grpName, "New_%s", lookup[i]);

                        group = layout->FindGroupByName(grpName);
                        if (group != NULL) {
                            mpNwc24NewGroup = group;
                            break;
                        }
                    }
                }
            }

            if (group != NULL) {
                for (nw4r::lyt::PaneLinkList::Iterator it = group->GetPaneList().GetBeginIter(); it != group->GetPaneList().GetEndIter(); it++) {
                    it->mTarget->UnbindAllAnimation();
                }

                if (layout->searchFile("icon_New.brlan")) {
                    mpNwc24NewAnim = layout->bindToGroup("icon_New.brlan", group);
                }
            }
        }

        void SDChannelObj::updateNew() {
            if (System::getNwc24Manager() != NULL) {
                switch (unk_0x70) {
                    case 1: {
                        if (setupNew()) {
                            unk_0x70 = 2;
                            unk_0x74 = 0;
                        }
                        break;
                    }
                    case 2: {
                        if (++unk_0x74 >= 4200) {
                            unk_0x70 = 1;
                        }
                        break;
                    }
                }
            }
        }

        BOOL SDChannelObj::setupNew() {
            if (System::getNwc24Manager() == NULL || !System::getNwc24Manager()->getNewTitleTbl(NULL)) {
                return FALSE;
            }

            const u32 titleCode = ES_TITLE_CODE(mTitleID);
            if (!System::getNwc24Manager()->isNewMessageThere(titleCode)) {
                return TRUE;
            }

            if (!mbNwc24NewPlayAnim) {
                if (mpNwc24NewGroup != NULL) {
                    for (nw4r::lyt::PaneLinkList::Iterator it = mpNwc24NewGroup->GetPaneList().GetBeginIter();
                         it != mpNwc24NewGroup->GetPaneList().GetEndIter(); it++) {
                        it->mTarget->SetVisible(true);
                    }

                    if (mpNwc24NewAnim != NULL) {
                        mpNwc24NewAnim->play();
                    }
                }

                mbNwc24NewPlayAnim = true;
            }

            return TRUE;
        }

        // clang-format off
        extern "C" __declspec(align(8)) char lbl_81696E30[] = "B_BtnA";
        extern "C" char lbl_81696E37[] = "B_BtnB";
        // clang-format on
    }  // namespace scene
}  // namespace ipl
