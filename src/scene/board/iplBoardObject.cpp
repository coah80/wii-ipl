#define IPL_CHANNEL_TITLE_NOVTABLE

#define SCENE_HEADER_FOR_UI_H
#define IPL_NIGAOE_H
#define IPL_CAPTURE_H

#include "layout/GUIManager.h"
#include "system/RIPL_BoardRecord.h"
#include "utility/iplCalendar.h"
#include "iplMath.h"
#include <nw4r/ut/list.h>
#include <revolution/arc.h>
#include <revolution/cdb.h>
#include <revolution/nwc24.h>
#include <revolution/tpl.h>

namespace ipl {
    namespace layout {
        class Object;
    }
    namespace controller {
        class Interface;
    }
    namespace nand {
        class LayoutFile;
    }
    namespace nigaoe {
        class Object;
    }
    namespace utility {
        class Capture;
    }
    namespace gui {
        class PaneManager;
    }
}  // namespace ipl
namespace EGG {
    class Heap;
    class Allocator;
}  // namespace EGG

// Reproduce the anonymous-type ordinal the original TU reached before
// iplBoardObject.h's anonymous classes: its include chain defined more
// types than our reconstructed headers, so without this the compiler
// numbers them differently (@class$ symbols). These member functions are
// parsed and counted but never emitted.
struct AnonOrdinalPad {
    void f0() {} void f1() {} void f2() {} void f3() {} void f4() {} void f5() {} void f6() {} void f7() {} void f8() {} void f9() {} void f10() {} void f11() {} void f12() {} void f13() {} void f14() {} void f15() {} void f16() {} void f17() {} void f18() {} void f19() {} void f20() {} void f21() {} void f22() {} void f23() {} void f24() {} void f25() {} void f26() {} void f27() {} void f28() {} void f29() {} void f30() {} void f31() {} void f32() {} void f33() {} void f34() {} void f35() {} void f36() {} void f37() {} void f38() {} void f39() {} void f40() {} void f41() {} void f42() {} void f43() {} void f44() {} void f45() {} void f46() {} void f47() {} void f48() {} void f49() {} void f50() {} void f51() {} void f52() {} void f53() {} void f54() {} void f55() {} void f56() {} void f57() {} void f58() {} void f59() {} void f60() {} void f61() {} void f62() {} void f63() {} void f64() {} void f65() {} void f66() {} void f67() {} void f68() {} void f69() {} void f70() {} void f71() {} void f72() {} void f73() {} void f74() {} void f75() {} void f76() {} void f77() {} void f78() {} void f79() {} void f80() {} void f81() {} void f82() {} void f83() {} void f84() {} void f85() {} void f86() {} void f87() {} void f88() {} void f89() {} void f90() {} void f91() {} void f92() {} void f93() {} void f94() {} void f95() {} void f96() {} void f97() {} void f98() {} void f99() {} void f100() {} void f101() {} void f102() {} void f103() {} void f104() {} void f105() {} void f106() {} void f107() {} void f108() {} void f109() {} void f110() {} void f111() {} void f112() {} void f113() {} void f114() {} void f115() {} void f116() {} void f117() {} void f118() {} void f119() {} void f120() {} void f121() {} void f122() {} void f123() {} void f124() {} void f125() {} void f126() {} void f127() {} void f128() {} void f129() {} void f130() {} void f131() {} void f132() {} void f133() {} void f134() {} void f135() {} void f136() {} void f137() {} void f138() {} void f139() {} void f140() {} void f141() {} void f142() {} void f143() {} void f144() {} void f145() {} void f146() {} void f147() {} void f148() {} void f149() {} void f150() {} void f151() {} void f152() {} void f153() {} void f154() {} void f155() {} void f156() {} void f157() {} void f158() {} void f159() {} void f160() {} void f161() {} void f162() {} void f163() {} void f164() {} void f165() {} void f166() {} void f167() {} void f168() {} void f169() {} void f170() {} void f171() {} void f172() {} void f173() {} void f174() {} void f175() {} void f176() {} void f177() {} void f178() {} void f179() {} void f180() {} void f181() {} void f182() {} void f183() {} void f184() {} void f185() {} void f186() {} void f187() {} void f188() {} void f189() {} void f190() {} void f191() {} void f192() {} void f193() {} void f194() {} void f195() {} void f196() {} void f197() {} void f198() {} void f199() {} void f200() {} void f201() {} void f202() {} void f203() {} void f204() {} void f205() {} void f206() {} void f207() {} void f208() {} void f209() {} void f210() {} void f211() {} void f212() {} void f213() {} void f214() {} void f215() {} void f216() {} void f217() {} void f218() {} void f219() {} void f220() {} void f221() {} void f222() {} void f223() {} void f224() {} void f225() {} void f226() {} void f227() {} void f228() {} void f229() {} void f230() {} void f231() {} void f232() {} void f233() {} void f234() {} void f235() {} void f236() {} void f237() {} void f238() {} void f239() {} void f240() {} void f241() {} void f242() {} void f243() {} void f244() {} void f245() {} void f246() {} void f247() {} void f248() {} void f249() {} void f250() {} void f251() {} void f252() {} void f253() {} void f254() {} void f255() {} void f256() {} void f257() {} void f258() {} void f259() {} void f260() {} void f261() {} void f262() {} void f263() {} void f264() {} void f265() {} void f266() {} void f267() {} void f268() {} void f269() {} void f270() {} void f271() {} void f272() {} void f273() {} void f274() {} void f275() {} void f276() {} void f277() {} void f278() {} void f279() {} void f280() {} void f281() {} void f282() {} void f283() {} void f284() {} void f285() {} void f286() {} void f287() {} void f288() {} void f289() {} void f290() {} void f291() {} void f292() {} void f293() {} void f294() {} void f295() {} void f296() {} void f297() {} void f298() {} void f299() {} void f300() {} void f301() {} void f302() {} void f303() {} void f304() {} void f305() {} void f306() {} void f307() {} void f308() {} void f309() {} void f310() {} void f311() {} void f312() {} void f313() {} void f314() {} void f315() {} void f316() {} void f317() {} void f318() {} void f319() {} void f320() {} void f321() {} void f322() {} void f323() {} void f324() {} void f325() {} void f326() {} void f327() {} void f328() {} void f329() {} void f330() {} void f331() {} void f332() {} void f333() {} void f334() {} void f335() {} void f336() {} void f337() {} void f338() {} void f339() {} void f340() {} void f341() {} void f342() {} void f343() {} void f344() {} void f345() {} void f346() {} void f347() {} void f348() {} void f349() {} void f350() {} void f351() {} void f352() {} void f353() {} void f354() {} void f355() {} void f356() {} void f357() {} void f358() {} void f359() {} void f360() {} void f361() {} void f362() {} void f363() {} void f364() {} void f365() {} void f366() {} void f367() {} void f368() {} void f369() {} void f370() {} void f371() {} void f372() {} void f373() {} void f374() {} void f375() {} void f376() {} void f377() {} void f378() {} void f379() {} void f380() {} void f381() {} void f382() {} void f383() {} void f384() {} void f385() {} void f386() {} void f387() {} void f388() {} void f389() {} void f390() {} void f391() {} void f392() {} void f393() {} void f394() {} void f395() {} void f396() {} void f397() {} void f398() {} void f399() {} void f400() {} void f401() {} void f402() {} void f403() {} void f404() {} void f405() {} void f406() {} void f407() {} void f408() {} void f409() {} void f410() {} void f411() {} void f412() {} void f413() {} void f414() {} void f415() {} void f416() {} void f417() {} void f418() {} void f419() {} void f420() {} void f421() {} void f422() {} void f423() {} void f424() {} void f425() {} void f426() {} void f427() {} void f428() {} void f429() {} void f430() {} void f431() {} void f432() {} void f433() {} void f434() {} void f435() {} void f436() {} void f437() {} void f438() {} void f439() {} void f440() {} void f441() {} void f442() {} void f443() {} void f444() {} void f445() {} void f446() {} void f447() {} void f448() {} void f449() {} void f450() {} void f451() {} void f452() {} void f453() {} void f454() {} void f455() {} void f456() {} void f457() {} void f458() {} void f459() {} void f460() {} void f461() {} void f462() {} void f463() {} void f464() {} void f465() {} void f466() {} void f467() {} void f468() {} void f469() {} void f470() {}
};
struct { int pad; } sAnonOrdinalPad1;
struct { int pad; } sAnonOrdinalPad2;
struct { int pad; } sAnonOrdinalPad3;

#include "scene/board/iplBoardObject.h"

#undef SCENE_HEADER_FOR_UI_H
#undef IPL_NIGAOE_H
#undef IPL_CAPTURE_H

#include "iplSceneUI.h"

#include "system/iplNigaoe.h"
#include "utility/iplCapture.h"

#include "scene/board/iplBoard.h"

#include "scene/button/iplButton.h"

#include "iplSystem.h"

#include "sound/iplSound.h"

#include <revolution/cx.h>
#include <revolution/vf.h>

#include "utility/iplRBRUtility.h"
#include "utility/iplTPLValidity.h"

#undef IPL_CHANNEL_TITLE_NOVTABLE

extern "C" void __ct__Q33ipl4math4VEC2Fff(ipl::math::VEC2*, f32, f32);

// I don't want to keep typing this out lol
#define DELETE_PTR_FORCE(x)                                                                                                                          \
    {                                                                                                                                                \
        delete x;                                                                                                                                    \
        x = NULL;                                                                                                                                    \
    }
#define DELETE_PTR_ARRAY_FORCE(x)                                                                                                                    \
    {                                                                                                                                                \
        delete[] x;                                                                                                                                  \
        x = NULL;                                                                                                                                    \
    }
#define DELETE_PTR(x)                                                                                                                                \
    if (x) {                                                                                                                                         \
        delete x;                                                                                                                                    \
        x = NULL;                                                                                                                                    \
    }
#define DELETE_PTR_ARRAY(x)                                                                                                                          \
    if (x) {                                                                                                                                         \
        delete[] x;                                                                                                                                  \
        x = NULL;                                                                                                                                    \
    }

#define PICTURE_THUMB_WIDTH 64
#define PICTURE_THUMB_HEIGHT 48

namespace ipl {
    namespace scene {
        // clang-format off
        const char* BoardObject::mAnimNames[BoardObject::TYPE_MAX][1+BoardObject::ANIM_MAX] = {
            {
                "LetterS_a.brlyt",
                "LetterS_a_PasteLetter.brlan",
                "LetterS_a_FocusIn.brlan",
                "LetterS_a_FocusOut.brlan",
                "LetterS_a_SelectLetter.brlan",
                "LetterS_a_ExitLetter.brlan",
                "LetterS_a_NextPage.brlan",
                "LetterS_a_NewAnim.brlan",
                "LetterS_a_DefAnim.brlan",
                "LetterS_a_SDAnim.brlan"
            },
            {
                "LetterS_b.brlyt",
                "LetterS_b_PasteLetter.brlan",
                "LetterS_b_FocusIn.brlan",
                "LetterS_b_FocusOut.brlan",
                "LetterS_b_SelectLetter.brlan",
                "LetterS_b_ExitLetter.brlan",
                "LetterS_b_NextPage.brlan",
                "LetterS_b_NewAnim.brlan",
                "LetterS_b_DefAnim.brlan",
               "LetterS_b_SDAnim.brlan"
            },
            {
                "LetterS_c.brlyt",
                "LetterS_c_PasteLetter.brlan",
                "LetterS_c_FocusIn.brlan",
                "LetterS_c_FocusOut.brlan",
                "LetterS_c_SelectLetter.brlan",
                "LetterS_c_ExitLetter.brlan",
                "LetterS_c_NextPage.brlan",
                "LetterS_c_NewAnim.brlan",
                "LetterS_c_DefAnim.brlan",
                "LetterS_c_SDAnim.brlan"
            }
        };
        // clang-format on

        static const struct {
            const char* file;
            const char* s_pane;
            const char* pane;
        } scThumbChangeTexFile = {
            "img/my_LetterS_b.tpl",
            "Letter0_s",
            "Letter0",
        };

        BoardObject::BoardObject()
            : ::gui::EventHandler(), mpLayout(NULL), mpGui(NULL), mpNigaoe(NULL), mpRecordData(NULL), mpUncompThumb(NULL), mBoardPos(0.0f, 0.0f),
              mMoveSpeed(0.0f, 0.0f), mMoveAnim(), mBoardDate(), mbModifiedPos(false), mbCleaned(false), mbCreatedPic(false), mbLeftWay(false),
              mbRightWay(false), mOptOutFlag(0), mPicture(), mpCapture(NULL), mbCaptured(false), mState(STATE_NORMAL), mConPos(0.0f, 0.0f),
              mConChan(0) {
            // Setup memory allocators
            mpHeapArena = (u8*)System::getMem2App()->alloc(0x46000, 4);
            mpHeap = EGG::ExpHeap::create(mpHeapArena, 0x46000, 0);
            mpAllocator = new (mpHeap, 4) EGG::Allocator(mpHeap, 4);

            mStandData.init();
        }

        void make_icon_cb_(nigaoe::Object* obj, void* work) {
            BoardObject* boardObject = static_cast<BoardObject*>(work);

            // Make the icon appear when the Mii has been created
            nw4r::lyt::Pane* pane = boardObject->getLayout()->FindPaneByName("Nigaoe");
            nw4r::lyt::Material* material = pane->GetMaterial();
            pane->SetVisible(true);
            material->SetTexture(GX_TEXMAP0, obj->getIconTexture());
        }

        void BoardObject::create(nand::LayoutFile* file, u8* recordData, u32 gameCode, const CDBId& cdbId, const CDBRecordKey& recordKey,
                                 const utility::Date& date) {
            mpRecordData = recordData;
            mpLayoutFile = file;

            mCDBGameCode = gameCode;
            mCDBId = cdbId;

            memcpy(&mCDBRecordKey, &recordKey, sizeof(CDBRecordKey));

            mBoardDate = date;

            init();
        }

        void BoardObject::init() {
            mbCreatedPic = false;
            mbModifiedPos = false;
            mbHovered = 0;
            mState = STATE_CREATE;
            mpThumbPtr = NULL;
            mpUncompThumb = NULL;
            mpThumbLength = 0;

            mMoveAnim.init(0, 8.0f, 0.0f, math::VEC2(0.0f, 0.0f), math::VEC2(0.0f, 0.0f));

            mPicture.mpWork = 0;
            mPicture.mpRGB565 = NULL;

            mpCapture = NULL;

            mbCaptured = false;
        }

        void BoardObject::calc(const math::VEC2& offsetPos) {
            switch (mState) {
                case STATE_CREATE: {
                    stt_create();
                    break;
                }
                case STATE_MAKE_THUMB: {
                    stt_make_thm();
                    break;
                }
                case STATE_FADE_IN: {
                    stt_fadein();
                    break;
                }
                case STATE_PINCH: {
                    stt_pinch();
                    break;
                }
                case STATE_STAND: {
                    stt_stand();
                    break;
                }
            }

            if (mpLayout != NULL) {
                // Next batch of 10 messages to the left
                if (mbLeftWay) {
                    mbLeftWay = false;

                    nw4r::ut::Rect rect;
                    System::getProjectionRect4x3(&rect);

                    math::VEC2 end(rect.left - mBoardPos.x - mMoveSpeed.x, 53.0f + (-mBoardPos.y - mMoveSpeed.y));
                    f32 maxFrame = mpLayout->getAnim(ANIM_NEXT_PAGE)->getMaxFrame();
                    mMoveAnim.init(ANIM_TYPE_FORWARD, maxFrame, 0.0f, math::VEC2(0.0f, 0.0f), end);

                    mMoveAnim.setAnmType(ANIM_TYPE_FORWARD);
                    mMoveAnim.play();

                    mpLayout->getAnim(ANIM_NEXT_PAGE)->play();
                }

                // Next batch of 10 messages to the right
                if (mbRightWay) {
                    mbRightWay = false;

                    nw4r::ut::Rect rect;
                    System::getProjectionRect4x3(&rect);

                    math::VEC2 end(rect.right - mBoardPos.x - mMoveSpeed.x, 53.0f + (-mBoardPos.y - mMoveSpeed.y));
                    f32 maxFrame = mpLayout->getAnim(ANIM_NEXT_PAGE)->getMaxFrame();
                    mMoveAnim.init(ANIM_TYPE_FORWARD, maxFrame, 0.0f, math::VEC2(0.0f, 0.0f), end);

                    mMoveAnim.setAnmType(ANIM_TYPE_FORWARD);
                    mMoveAnim.play();

                    mpLayout->getAnim(ANIM_NEXT_PAGE)->play();
                }

                nw4r::ut::Rect projRect;
                System::getProjectionRect(&projRect);

                nw4r::ut::Rect projRect4x3;
                System::getProjectionRect4x3(&projRect4x3);

                f32 locationAdjust = projRect.GetWidth() / projRect4x3.GetWidth();

                mMoveAnim.calc();

                ipl::math::VEC2 finalPos = offsetPos + mBoardPos + mMoveSpeed + mMoveAnim.get2();
                finalPos.x *= locationAdjust;
                mpLayout->GetRootPane()->SetTranslate(finalPos);
                mpLayout->calc();
            }
        }

        void BoardObject::stt_create() {
            RBRHeader* recordHdr = (RBRHeader*)mpRecordData;

            f32 xPos;
            f32 yPos;
            yPos = recordHdr->yPos;
            xPos = recordHdr->xPos;
            mBoardPos.x = xPos;
            mBoardPos.y = yPos;

            mRecordType = (RBRRecordType)recordHdr->flags.type;

            if (mRecordType == RBRRecordType_Memo) {
                mLetterType = TYPE_MEMO;
            } else if (mRecordType == RBRRecordType_PlayTimeLog) {
                mLetterType = TYPE_PLAYTIME;
            } else {
                mLetterType = TYPE_LETTER;
            }

            const char** btnAnims = mAnimNames[mLetterType];
            mOptOutFlag = recordHdr->flags.optOut & 1;

            mpLayout = new (mpHeap, 4) layout::Object(mpHeap, mpLayoutFile, "arc", btnAnims[0]);
            mpLayout->bind(btnAnims[ANIM_PASTE + 1]);
            mpLayout->bind(btnAnims[ANIM_FOCUS_IN + 1], false);
            mpLayout->bind(btnAnims[ANIM_FOCUS_OUT + 1], false);
            mpLayout->bind(btnAnims[ANIM_FOCUS + 1], false);
            mpLayout->bind(btnAnims[ANIM_EXIT + 1], false);
            mpLayout->bind(btnAnims[ANIM_NEXT_PAGE + 1], false);
            mpLayout->bindToGroup(btnAnims[ANIM_NEW + 1], "G_New", false, false);
            mpLayout->bindToGroup(btnAnims[ANIM_DEFAULT + 1], "G_New", false, false);
            mpLayout->bindToGroup(btnAnims[ANIM_SD + 1], "G_New", false, false);
            mpLayout->finishBinding();

            mpGui = new (mpHeap, 4) gui::PaneManager(this, mpLayout->getDrawInfo(), NULL, mpAllocator);

            mpGui->setupScene(mpLayout);
            mpGui->setAllComponentTriggerTarget(false);
            mpGui->setTriggerTarget(mpLayout->FindPaneByName("B_Letter"), true);

            layout::Wrapper::SetVisibleSafe(mpLayout->FindPaneByName("N_Pic"), false);

            wchar_t* thumbText = NULL;
            if (mLetterType == TYPE_MEMO) {
                if (recordHdr->bodyOffset != 0) {
                    thumbText = (wchar_t*)((u8*)mpRecordData + recordHdr->bodyOffset);
                }
            } else {
                if (recordHdr->titleOffset != 0) {
                    thumbText = (wchar_t*)((u8*)mpRecordData + recordHdr->titleOffset);
                }
            }

            set_thumb_text("T_Letter", thumbText);

            mpLayout->hide("Nigaoe");

            if (recordHdr->faceOffset != 0) {
                RFLiCharData* charData = (RFLiCharData*)((u8*)mpRecordData + recordHdr->faceOffset);
                if (System::getMiiManager()->isValid(charData)) {
                    mpNigaoe = System::getMiiManager()->create(mpHeap, 76, 76, charData, make_icon_cb_, this);
                }
            }

            for (int i = 0; i < RBR_ATTACHMENT_MAX; i++) {
                if (recordHdr->attach[i].type == RBRAttachmentType_MsgBoard) {
                    ARCHandle arc;
                    u8* off = ((u8*)mpRecordData + recordHdr->attach[i].offset);

                    if (arc_init_handle(off, &arc)) {
                        ARCFileInfo file;
                        if (ARCOpen(&arc, "./thumbnail_LZ.bin", &file)) {
                            mpThumbPtr = (off + ARCGetStartOffset(&file));
                            mpThumbLength = ARCGetLength(&file);
                            ARCClose(&file);
                        }
                    }

                    if (mpThumbPtr != NULL) {
                        if (CXGetCompressionType(mpThumbPtr) == CX_COMPRESSION_TYPE_LZ) {
                            u32 uncompSize = CXGetUncompressedSize(mpThumbPtr);
                            if (uncompSize != 0 && uncompSize < 0x7800) {
                                mpUncompThumb = new (mpHeap, DEFAULT_ALIGN) u8[uncompSize];
                                if (mpUncompThumb != NULL) {
                                    if (CXSecureUncompressLZ(mpThumbPtr, mpThumbLength, mpUncompThumb) == CX_SECURE_ERR_OK) {
                                        DCStoreRange(mpUncompThumb, uncompSize);
                                        change_ltrtex(mpLayout, mpUncompThumb);
                                    } else {
                                        DELETE_PTR_ARRAY_FORCE(mpUncompThumb);
                                    }
                                }
                            }
                        }
                    }
                }
                else if (recordHdr->attach[i].type == RBRAttachmentType_Picture) {
                    if (create_picture(&mPicture, System::getMem2App(), System::getMem2App(), ((u8*)mpRecordData + recordHdr->attach[i].offset),
                                       4 + recordHdr->attach[i].size)) {
                        mpCapture = new (mpHeap, 4) utility::Capture(mpHeap, 0, 0, PICTURE_THUMB_WIDTH, PICTURE_THUMB_HEIGHT, GX_TF_RGB565);
                        mbCaptured = false;
                        mbCreatedPic = true;

                        layout::Wrapper::SetVisibleSafe(mpLayout->FindPaneByName("N_Pic"), true);
                        layout::Wrapper::SetVisibleSafe(mpLayout->FindPaneByName("B_Pic"), true);
                    }
                }
            }

            if (mCDBRecordKey.location == CDB_FS_LOCATION_NAND) {
                OSTime recordTime, currTime;

                currTime = OSGetTime();
                recordTime = recordHdr->time;
                if (recordTime < currTime) {
                    if (OSSecondsToTicks(NEW_MESSAGE_DURATION_SECONDS) > (OSTime)(currTime - recordTime)) {
                        mpLayout->getAnim(ANIM_NEW)->play();
                    } else {
                        mpLayout->getAnim(ANIM_DEFAULT)->play();
                    }
                }
            } else {
                mpLayout->getAnim(ANIM_SD)->play();
            }

            Board* board = static_cast<Board*>(System::getScene(SCENE_BOARD));
            if (board->canPlayDispSound()) {
                snd::getSystem()->startSEwithPos("WIPL_SE_MSG_DISP", mBoardPos.x);
            }

            if (mbCreatedPic) {
                mState = STATE_MAKE_THUMB;
            } else {
                mpLayout->getAnim(ANIM_PASTE)->play();
                mState = STATE_FADE_IN;
            }
        }

        void BoardObject::stt_make_thm() {
            if (mbCaptured) {
                DELETE_PTR_ARRAY(mPicture.mpRGB565);

                if (mpCapture != NULL) {
                    nw4r::lyt::Pane* pane = mpLayout->FindPaneByName("LetterPic");
                    pane->GetMaterial()->SetTexture(GX_TEXMAP0, mpCapture->getGXTex());
                }

                mpLayout->getAnim(ANIM_PASTE)->play();

                mState = STATE_FADE_IN;
            }
        }

        void BoardObject::stt_fadein() {
            if (!mpLayout->getAnim(ANIM_PASTE)->isPlaying()) {
                mState = STATE_NORMAL;
            }
        }

        void clean_task_(void* work);

        void BoardObject::stt_pinch() {
            controller::Interface* con = System::getController(mConChan);
            if (con != NULL) {
                nw4r::ut::Rect projRect;
                System::getProjectionRect(&projRect);
                nw4r::ut::Rect projRect4x3;
                System::getProjectionRect4x3(&projRect4x3);

                f32 locationAdjust = projRect4x3.GetWidth() / projRect.GetWidth();

                if (con->pinch() && con->isValidDpd()) {
                    nw4r::math::VEC2 oldMoveSpeed(mMoveSpeed);
                    nw4r::math::VEC2 conPos(con->getDpdProjectionPos());
                    conPos.x *= locationAdjust;

                    mMoveSpeed.x = conPos.x - mConPos.x;
                    mMoveSpeed.y = mConPos.y - conPos.y;

                    f32 speed = 0.0f;

                    f32 newX = oldMoveSpeed.x - mMoveSpeed.x;
                    f32 newY = oldMoveSpeed.y - mMoveSpeed.y;

                    f32 val = (newX * newX) + (newY * newY);

                    if (val <= 0.0f) {
                        speed = 0.0f;
                    } else {
                        speed = (val * nw4r::math::FrSqrt(val));
                    }

                    snd::getSystem()->holdSEwithPosDis("WIPL_SE_BOARD_DRAG", mBoardPos.x + mMoveSpeed.x, speed);
                } else {
                    if (con->isValidDpd()) {
                        nw4r::ut::Rect rbrPos;
                        RBRUtility::getPosRect(&rbrPos);

                        math::VEC2 newPos(mBoardPos);
                        math::VEC2 conPos(con->getDpdProjectionPos());
                        conPos.x *= locationAdjust;

                        newPos.x += (conPos.x - mConPos.x);
                        newPos.y += mConPos.y - conPos.y;

                        if (newPos.x < rbrPos.left) {
                            newPos.x = rbrPos.left;
                        } else if (newPos.x > rbrPos.right) {
                            newPos.x = rbrPos.right;
                        }

                        if (newPos.y < rbrPos.bottom) {
                            newPos.y = rbrPos.bottom;
                        } else if (newPos.y > rbrPos.top) {
                            newPos.y = rbrPos.top;
                        }

                        if (newPos.x != mBoardPos.x || newPos.y != mBoardPos.y) {
                            mBoardPos = newPos;
                            if (mCDBRecordKey.location == CDB_FS_LOCATION_NAND) {
                                mbModifiedPos = true;
                            }
                        }
                    }

                    System::getPointer()->changeType(mConChan, Pointer::TYPE_POINT);
                    mMoveSpeed.clear();
                    mConPos.clear();

                    static_cast<Board*>(System::getScene(SCENE_BOARD))->pinchOff(this);

                    if (mbModifiedPos && !mbCleaned) {
                        mbCleaned = true;
                        System::getTask1()->request(clean_task_, this, NULL);
                    }

                    mState = STATE_NORMAL;
                }
            } else {
                System::getPointer()->changeType(mConChan, Pointer::TYPE_POINT);
                mMoveSpeed.clear();
                mConPos.clear();

                static_cast<Board*>(System::getScene(SCENE_BOARD))->pinchOff(this);

                mState = STATE_NORMAL;
            }
        }

        void BoardObject::stt_stand() {
            f32 dVar2 = nw4r::math::CosDeg(mStandData.unk_0x0C * 30.0f + 30.0f);
            f32 dVar3 = nw4r::math::SinDeg(mStandData.unk_0x0C * 30.0f + 30.0f);

            math::VEC2 standPos;
            __ct__Q33ipl4math4VEC2Fff(&standPos, dVar3 * 160.0f, dVar2 * 160.0f);
            mBoardPos = (((mStandData.pos * (f32)(10 - mStandData.unk_0x08)) + (standPos * mStandData.unk_0x08)) / 10.0f);

            if ((mStandData.unk_0x08 += 1) > 10) {
                mStandData.init();
                mState = STATE_NORMAL;
            }
        }

        void BoardObject::draw() {
            if (mpLayout == NULL) {
                return;
            }

            if (mState == STATE_MAKE_THUMB) {
                return;
            }

            mpLayout->draw();
        }

        void BoardObject::capture() {
            if (mState == STATE_MAKE_THUMB && !mbCaptured) {
                nw4r::ut::Rect projRect4x3;
                System::getProjectionRect4x3(&projRect4x3);

                nw4r::math::MTX44 mtx;
                MTXOrtho(mtx, 0.0f, projRect4x3.GetHeight(), 0.0f, projRect4x3.GetWidth(), -100.0f, 100.0f);

                GXSetProjection(mtx, GX_ORTHOGRAPHIC);

                utility::Graphics::calcOrthoCamera();
                utility::Graphics::setCamera();

                utility::Graphics::drawTexture(nw4r::ut::Rect(0.0f, 0.0f, PICTURE_THUMB_WIDTH, PICTURE_THUMB_HEIGHT), mPicture.texObj,
                                               (GXColor){255, 255, 255, 255}, 1);
                if (mpCapture != NULL) {
                    mpCapture->capture(TRUE);
                }

                mbCaptured = true;
            }
        }

        void BoardObject::destroy() {
            mbModifiedPos = false;
            mbCleaned = false;

            DELETE_PTR(mpLayout);
            DELETE_PTR(mpGui);
            DELETE_PTR_ARRAY(mpRecordData)
            DELETE_PTR_ARRAY(mpUncompThumb);
            DELETE_PTR_ARRAY(mPicture.mpRGB565);
            DELETE_PTR_ARRAY(mPicture.mpWork);
            DELETE_PTR(mpCapture);

            if (mpNigaoe != NULL) {
                if (!mpNigaoe->created()) {
                    System::getMiiManager()->detach(mpNigaoe);
                }
                DELETE_PTR_FORCE(mpNigaoe);
            }
        }

        void BoardObject::destroy_heap() {
            DELETE_PTR(mpAllocator);
            if (mpHeap != NULL) {
                mpHeap->destroy();
                mpHeap = NULL;
            }

            if (mpHeapArena != NULL) {
                System::getMem2App()->free(mpHeapArena);
            }
        }

        BOOL BoardObject::create_picture(picture* picture, EGG::Heap* picHeap, EGG::Heap* workHeap, u8* src, u32 srcSize) {
            u32 pictureSize;
            u32 rgb565Size;
            BOOL result = FALSE;

            picture->width = ODHGetWidth(src);
            picture->height = ODHGetHeight(src);

            pictureSize = picture->width * picture->height;

            if (picture->width > 0 && picture->width <= 512 && picture->height > 0 && picture->height <= 456) {
                rgb565Size = pictureSize * 2;
                picture->mpRGB565 = new (picHeap, DEFAULT_ALIGN) u8[rgb565Size];

                u32 workSize = ODHGetWorkSize(pictureSize);
                picture->mpWork = new (workHeap, -DEFAULT_ALIGN) u8[workSize];

                if (picture->mpRGB565 != NULL && picture->mpWork != NULL) {
                    if (ODHDecodeRGB565(src, srcSize, picture->mpRGB565, rgb565Size, picture->mpWork, workSize)) {
                        DCStoreRange(picture->mpRGB565, rgb565Size);
                        GXInitTexObj(&picture->texObj, picture->mpRGB565, picture->width, picture->height, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, 0);

                        result = TRUE;

                        DELETE_PTR_ARRAY_FORCE(picture->mpWork);
                    } else {
                        DELETE_PTR_ARRAY_FORCE(picture->mpRGB565);
                        DELETE_PTR_ARRAY_FORCE(picture->mpWork);
                    }
                } else {
                    DELETE_PTR_ARRAY(picture->mpRGB565);
                    DELETE_PTR_ARRAY(picture->mpWork);
                }
            }

            return result;
        }

        void BoardObject::reset_gui() {
            if (mpGui != NULL) {
                mpGui->init();
            }

            if (mbHovered) {
                if (mpLayout != NULL) {
                    mpLayout->getAnim(ANIM_FOCUS_OUT)->play();
                }
                mbHovered = 0;
            }
        }

        void BoardObject::set_thumb_text(const char* paneName, const wchar_t* thumbText) {
            nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpLayout->FindPaneByName(paneName));

            wchar_t local_28[THUMB_TEXT_LENGTH + 3 /* "..." */ + 1 /* NULL */] = L"";
            memset(local_28, 0, sizeof(local_28));

            if (thumbText != NULL) {
                for (int i = 0; i < THUMB_TEXT_LENGTH + 1 && thumbText[i] != (u16)'\n'; i++) {
                    local_28[i] = thumbText[i];
                }
            }

            if (System::getRegion() == SC_PRODUCT_AREA_JPN) {
                if (local_28[THUMB_TEXT_LENGTH] != 0) {
                    local_28[THUMB_TEXT_LENGTH + 0] = L'…';
                }
            } else {
                if (local_28[THUMB_TEXT_LENGTH] != 0) {
                    local_28[THUMB_TEXT_LENGTH + 2] = '.';
                    local_28[THUMB_TEXT_LENGTH + 1] = '.';
                    local_28[THUMB_TEXT_LENGTH + 0] = '.';
                }
            }

            textBox->SetString(local_28);
        }

        void BoardObject::update(int chan) {
            if (mpGui != NULL) {
                mpGui->update(chan);
            }
        }

        void BoardObject::start_point_event(int index, controller::Interface* con) {
            if (mbHovered == FALSE) {
                mpLayout->getAnim(ANIM_FOCUS_IN)->play();
                snd::getSystem()->startSE("WIPL_SE_BOARD_FOCUS");
                if (con != NULL) {
                    con->rumble();
                }
            }

            mbHovered++;

            static_cast<Board*>(System::getScene(SCENE_BOARD))->setHoveredObj(index, this);
            static_cast<Board*>(System::getScene(SCENE_BOARD))->reappend(this);
        }

        void BoardObject::start_left_event(int index) {
            if (mbHovered == TRUE) {
                if (mpLayout->getAnim(ANIM_FOCUS_IN)->isPlaying()) {
                    mpLayout->getAnim(ANIM_FOCUS_IN)->stop();
                }
                mpLayout->getAnim(ANIM_FOCUS_OUT)->play();
            }

            mbHovered--;

            static_cast<Board*>(System::getScene(SCENE_BOARD))->setHoveredObj(index, NULL);
        }

        void BoardObject::change_ltrtex(layout::Object* layout, void* arcData) {
            ARCHandle arc;
            ARCFileInfo file;

            if (arc_init_handle(arcData, &arc)) {
                const char** pFile = (const char**)&scThumbChangeTexFile.file;

                if (ARCOpen(&arc, pFile[0], &file)) {
                    TPLPalette* ptr = (TPLPalette*)((u8*)arcData + ARCGetStartOffset(&file));
                    u32 length = ARCGetLength(&file);

                    change_tex(layout, pFile[1], ptr, length);
                    change_tex(layout, pFile[2], ptr, length);

                    ARCClose(&file);
                }
            }
        }

        void BoardObject::change_tex(layout::Object* layout, const char* paneName, TPLPalette* tplData, u32 tplSize) {
            if (utility::tpl_validity::isValidForLTX(tplData, tplSize)) {
                nw4r::lyt::Pane* pane = layout->FindPaneByName(paneName);
                pane->GetMaterial()->SetTexture(GX_TEXMAP0, tplData);
            }
        }

        void BoardObject::onEvent(u32 compId, u32 event, void* data) {
            gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId));
            const char* paneName = component->getPane()->GetName();

            controller::Interface* con = static_cast<controller::Interface*>(data);

            int num = getLatestEventCtrlNo();

            switch (event) {
                case ON_POINT: {
                    if (strcmp(paneName, "B_Letter") == 0) {
                        start_point_event(num, con);
                    }
                    break;
                }
                case ON_LEFT: {
                    if (strcmp(paneName, "B_Letter") == 0) {
                        start_left_event(num);
                    }
                    break;
                }
                // Drag and trig events are swapped, but still act as intended?
                case ON_DRAG: {
                    if (con != NULL && con->decide()) {
                        if (static_cast<Board*>(System::getScene(SCENE_BOARD))->getHoveredObj(num) == this) {
                            if (static_cast<Button*>(System::getScene(SCENE_BUTTON))->isActive() &&
                                !static_cast<Button*>(System::getScene(SCENE_BUTTON))->hasReservedAnim()) {
                                static_cast<Board*>(System::getScene(SCENE_BOARD))->focus(this);
                            }
                        }
                    }
                    break;
                }
                case ON_TRIG: {
                    if (con != NULL && con->pinchTrg()) {
                        if (mState != STATE_PINCH && static_cast<Board*>(System::getScene(SCENE_BOARD))->pinch(this)) {
                            System::getPointer()->changeType(num, Pointer::TYPE_GRAB);

                            nw4r::ut::Rect projRect;
                            System::getProjectionRect(&projRect);
                            nw4r::ut::Rect projRect4x3;
                            System::getProjectionRect4x3(&projRect4x3);

                            f32 locationAdjust = projRect4x3.GetWidth() / projRect.GetWidth();

                            mConPos = con->getDpdProjectionPos();

                            mConChan = num;
                            mState = STATE_PINCH;

                            mConPos.x *= locationAdjust;
                        }
                    }
                    break;
                }
            }
        }

        void clean_task_(void* work) {
            if (System::getScene(SCENE_BOARD) != NULL) {
                BoardObject* boardObject = static_cast<BoardObject*>(work);
                boardObject->startClean();
            }
        }

        void BoardObject::left_away() {
            mbLeftWay = true;
        }

        void BoardObject::right_away() {
            mbRightWay = true;
        }

        BOOL BoardObject::get_nigaoe_name(wchar_t* name, int nameLen) {
            BOOL result = FALSE;

            memset(name, 0, nameLen * sizeof(wchar_t));

            RBRHeader* recordHdr = (RBRHeader*)mpRecordData;

            if (recordHdr->faceOffset != 0) {
                if (mpNigaoe != NULL && mpNigaoe->created()) {
                    RFLiCharData* charData = (RFLiCharData*)((u8*)mpRecordData + recordHdr->faceOffset);
                    if (System::getMiiManager()->isValid(charData)) {
                        wcsncpy(name, (wchar_t*)charData->name, RFL_NAME_LENGTH);
                        result = TRUE;
                    }
                }
            }

            return result;
        }

        BOOL BoardObject::permit_reply() const {
            RBRHeader* recordHdr = (RBRHeader*)mpRecordData;
            BOOL result = FALSE;
            if (recordHdr->addrType != NWC24_FRIENDTYPE_NONE && !recordHdr->noReplyFlag) {
                result = TRUE;
            }
            return result;
        }

        u16 BoardObject::get_addr_type() const {
            RBRHeader* recordHdr = (RBRHeader*)mpRecordData;
            return recordHdr->addrType;
        }

        NWC24FriendAddr BoardObject::get_addr() const {
            RBRHeader* recordHdr = (RBRHeader*)mpRecordData;
            return recordHdr->addr;
        }

        void BoardObject::delete_record() {
            System::getCdbManager()->deleteRecord(&mCDBRecordKey);
        }

        void BoardObject::clean() {
            if (mbModifiedPos && mpRecordData != NULL) {
                cdb::Manager* cdbManager = System::getCdbManager();

                CDBRecord cdbRecord;
                RBRHeader header = *(RBRHeader*)mpRecordData;

                header.xPos = mBoardPos.x;
                header.yPos = mBoardPos.y;
                header.crc32 = cdbManager->calcCRC(&header);
                if (cdbManager->findByKey(&cdbRecord, &mCDBRecordKey)) {
                    cdbManager->unused();  // does nothing but got that auto mutex lock

                    if (cdbManager->open(&cdbRecord)) {
                        if (cdbManager->seek(&cdbRecord, 0, CDB_SEEK_BEGIN)) {
                            cdbManager->write(&cdbRecord, &header, sizeof(RBRHeader));
                        }
                        cdbManager->close(&cdbRecord);
                    }
                }

                mbModifiedPos = false;
            }
        }

        BOOL BoardObject::is_protected() const {
            BOOL result = FALSE;
            u32 status[VF_SD_SLOT_MAX];

            status[VF_SD_SLOT_0] = 0;

            VFErr vfErr = VFGetSDDirectStatus("SD", status);
            if (mCDBRecordKey.location == CDB_FS_LOCATION_SD) {
                if (vfErr == VF_ERR_SUCCESS && (status[VF_SD_SLOT_0] & VF_STATUS_PROTECTED)) {
                    result = TRUE;
                }
            }

            return result;
        }

        BOOL BoardObject::arc_init_handle(void* buffer, ARCHandle* handle) {
            BOOL result = FALSE;
            ARCHeader* header = ((ARCHeader*)buffer);

            if (buffer == NULL) {
                goto out;
            }

            if (handle == NULL) {
                goto out;
            }

            if (header->magic != ARC_MAGIC) {
                goto out;
            }

            if (((u8*)buffer + header->fstStart) == 0) {
                goto out;
            }

            result = ARCInitHandle(buffer, handle);

        out:
            return result;
        }

#ifndef NON_MATCHING
        void forceWeakFunc(nw4r::math::VEC2& vec) {
            nw4r::math::VEC2 end(vec / 10.0f);
        }
#endif

        void GenerateWEAK() {
            nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(((nw4r::lyt::Pane*)NULL)->FindPaneByName(NULL));

            static const f32 pad_data0 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data1 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data2 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data3 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data4 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data5 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data6 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data7 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data8 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data9 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data10 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data11 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data12 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data13 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data14 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data15 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data16 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data17 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data18 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data19 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data20 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data21 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data22 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data23 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data24 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data25 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data26 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data27 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data28 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data29 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data30 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data31 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data32 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data33 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data34 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data35 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data36 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_data37 __attribute__((section(".data"), aligned(1), used)) = 0.0f;
            static const f32 pad_rodata __attribute__((section(".rodata"), aligned(1), used)) = 0.0f;
            static const f32 pad_sdata2 __attribute__((section(".sdata2"), aligned(1), used)) = 0.0f;
        }
    }  // namespace scene
}  // namespace ipl
