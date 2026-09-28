#ifndef IPL_SCENE_SD_CHANNEL_TITLE_H
#define IPL_SCENE_SD_CHANNEL_TITLE_H

#include "iplSceneHeader.h"

#include "scene/sdChannelSelect/iplSDChannelSelect.h"
#include "scene/sdChannelSelect/iplSDChannelObj.h"
#include "scene/sdChannelMemory/iplSDMemory.h"

#include "utility/iplCapture.h"

namespace ipl {
    namespace channel {
        class RsoThread;
    }
    namespace gui {
        class PaneManager;
    }
    namespace scene {
        class SDChannelTitleEvent;
        class SDChannelTitleBtnEvent;

        FADER_SCENE_CLASS(SDChannelTitle) {
        public:
            SDChannelTitle(EGG::Heap * heap, SDChannelSelect * chanSel);
            virtual ~SDChannelTitle();

            void prepare();
            void create();

            void calcCommon();
            FaderSceneCommand calcFadein();
            FaderSceneCommand calcNormal();
            void initCalcFadeout();
            FaderSceneCommand calcFadeout();

            void draw();
            void destroy();

            BOOL isResetAcceptable();
            void startResetting();

            SDChannelObj* getChanObj() {
                return mpChanSelect->getChanObj();
            }

            bool isChanState(int state) const {
                return mChanState == state;
            }

        private:
            enum {
                STATE_FADEIN_WAIT = 0,
                STATE_NORMAL,
                STATE_FADEIN_INTRO,
                STATE_INTP,
                STATE_SELECT_CHAN,
                STATE_NORMAL_2,
                STATE_6,
                STATE_7,
                STATE_8,
                STATE_9,
                STATE_10,
                STATE_11,
                STATE_12,
                STATE_13,
                STATE_14,
                STATE_15,
                STATE_SET_TMP_TITLE,
                STATE_17,
                STATE_FLUSH_WAIT,
                STATE_19,
                STATE_20,
                STATE_21,
                STATE_22,
                STATE_23,
                STATE_24,
                STATE_25,
                STATE_26,
                STATE_27,
                STATE_28,
                STATE_29,
                STATE_30,
                STATE_MAX,
            };

            int mChanState;                          // 0x58
            EGG::ExpHeap* mpBannerHeap;              // 0x5C
            EGG::ExpHeap* mpCaptureHeap;             // 0x60
            int mChanPage;                           // 0x64
            int mChanIndex;                          // 0x68
            int mChanCount;                          // 0x6C
            int mLaunchKind;                         // 0x70
            int mChildSceneState;                    // 0x74
            f32 mChanPosX;                           // 0x78
            f32 mChanPosY;                           // 0x7C
            f32 mChanPosZ;                           // 0x80
            int mWaitCounter;                        // 0x84
            int mGuiState;                           // 0x88
            bool mbEnableStart;                      // 0x8C
            struct FocusAnims {
                layout::Animator* off;
                layout::Animator* on;
                u8 unk_0x8[0x10];
            } mFocusAnims[2];                        // 0x90
            int unk_0xC0[2];                         // 0xC0
            layout::Animator* mpSelectAnimA;         // 0xC8
            int unk_0xCC[5];                         // 0xCC
            layout::Animator* mpSelectAnimB;         // 0xE0
            int unk_0xE4[6];                         // 0xE4
            layout::Animator* mpOffAnimA;            // 0xFC
            layout::Animator* mpOnAnimA;             // 0x100
            int unk_0x104[4];                        // 0x104
            layout::Animator* mpOffAnimB;            // 0x114
            layout::Animator* mpOnAnimB;             // 0x118
            int unk_0x11C[6];                        // 0x11C
            layout::Animator* mpOutAnim;             // 0x134
            math::HermiteIntp<f32>* mpIntp;          // 0x138
            SDChannelSelect* mpChanSelect;           // 0x13C
            nand::LayoutFile* mpLayoutFile;          // 0x140
            layout::Object* mpLayout;                // 0x144
            gui::PaneManager* mpPaneManager;         // 0x148
            layout::Object* mpThumbLayout;           // 0x14C
            EGG::ExpHeap* mpThumbHeap;               // 0x150
            layout::Object* mpSubLayout;             // 0x154
            int mBannerSel;                          // 0x158
            nand::LayoutFile* mpBannerFiles[2];      // 0x15C
            nand::File* mpBannerTasks[2];            // 0x164
            layout::Object* mpBannerLayout;          // 0x16C
            layout::Animator* mpBannerAnims[3];      // 0x170
            nw4r::snd::SoundHandle* mpSeHandle;      // 0x17C
            nand::File* mpSaveFile;                  // 0x180
            u32 mFadeoutTick;                        // 0x184
            int mBtnFocusCount[2];                   // 0x188
            SDChannelTitleEvent* mpEvent;            // 0x190
            utility::Capture* mpCapture;             // 0x194
            utility::Capture* mpCapture2;            // 0x198
            ESTmdView* mpTmdView;                    // 0x19C
            bool mbTmdLoaded;                        // 0x1A0
            u16 mTitleVersion;                       // 0x1A2
            bool unk_0x1A4;                          // 0x1A4
            int mCsState;                            // 0x1A8
            int mCsCalcFlag;                         // 0x1AC
            bool mbLaunching;                        // 0x1B0
            u32 mCsFrame;                            // 0x1B4
            u32 mCsFrameMax;                         // 0x1B8
            nand::File* mpCsFile;                    // 0x1BC
            EGG::ExpHeap* mpCsHeaps[2];              // 0x1C0
            int mCsHeapSel;                          // 0x1C8
            channel::RsoThread* mpRsoThread;         // 0x1CC
            EGG::Heap* mpCsWorkHeap;                 // 0x1D0
            layout::Animator* mCsAnims[0x10];        // 0x1D4
            bool mbCsThreadTerminated;               // 0x214
            EGG::ExpHeap* mpCsHeap;                  // 0x218
            int unk_0x21C;                           // 0x21C
            u64 mTitleID;                            // 0x220
            NandSDWorker::AppBlocksInfo mNandFree;   // 0x228
            u8 unk_0x230[0x800];                     // 0x230
            SDMemory mSDMemory;                      // 0xA30
            int mErrMsgId;                           // 0x34A8
            int mBannerTimer;                        // 0x34AC
            bool mbSDWorkDone;                       // 0x34B0
            bool mbHbmEnable;                        // 0x34B1
            nw4r::snd::SoundHandle* mpSeHandle2;     // 0x34B4

            void calcNormalNormal();
            void calcNormalChanRelease();
            void calcNormalWait20();
            void calcNormalButtonWait();
            void calcNormalChildScene();
            void calcNormalDialogResult();
            void calcNormalCheckTmd();
            void calcNormalSelectDialog();
            void calcNormalSetTitleId();
            void calcNormalCheckStart();
            void calcNormalStartChannel();
            void calcNormalMemory();
            void calcNormalMemoryWait();
            void calcNormalLoadMeta();
            void calcNormalBanner();
            void calcNormalBannerEnd();
            void calcNormalDialog();
            void calcNormalFlushWait();
            void calcNormalChanCheck();
            void calcNormalWaitAnim();
            void calcNormalResetGui();

            BOOL resetTitleAnim();
            void restartTitleAnim();
            void startChanSelectWork(int kind);
            void releaseChannel(u64 titleId);
            void calcChannelScript();
            void initChannelScript();
            void createChannelScript();
            void destroyChannelScript();
            void startBannerSound();
            void bindLanguageAnims();
            void bindRsoAnims(layout::Object* layout, layout::Animator** anims, const char* prefix);
            void bindBannerAnims();
            void createBannerLayout();
            void createThumbnailLayout();
            void createBanner();
            bool isNetEnable(u64 titleId);
            bool isParentalSet();
            void startDialog(int kind);
            void selectChannel(int page, int index);
            void setTitleID(SDChannelObj* chanObj);
            void launchChannel();
            void startDialog2(int kind);
            void stopControllers(int kind);
            void doReboot();
            u32 checkWaitEnd();
            void resetBtnPane();
            void drawBorder(const nw4r::ut::Rect& rect, GXColor color);
            void setMessage(nw4r::lyt::Pane* pane, u32 msgId, bool alloc);
            nand::LayoutFile* createNandTask(u64 titleId, nand::File** taskOut);
            static void getTmdView(void* arg);
            u32 checkParentalControl(ESTmdView* tmdView);

            friend class SDChannelTitleEvent;
            friend class SDChannelTitleBtnEvent;
        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_SD_CHANNEL_TITLE_H
