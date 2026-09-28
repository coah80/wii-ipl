#ifndef IPL_SCENE_SD_MEMORY_H
#define IPL_SCENE_SD_MEMORY_H

#include <egg/core.h>

#include "layout/iplGuiManager.h"
#include "layout/iplLayout.h"

#include "scene/board/iplFocusObject.h"

#include "system/iplNandSDWorker.h"

namespace ipl {
    namespace controller {
        class Interface;
    }

    namespace nand {
        class LayoutFile;
    }

    namespace scene {
        class SDChannelSelect;

        class SDMemory {
        public:
            SDMemory();
            ~SDMemory();

            void create(EGG::Heap* heap, nand::LayoutFile* layoutFile, SDChannelSelect* chanSel);

            void startCheck(NandSDWorker::AppBlocksInfo* freeArea, NandSDWorker::AppBlocksInfo* needed);
            void initScroller();
            void resetEdgeAnims();
            void updateEdgeAnims(u32 p1, u32 p2, u32 p3, u32 p4);
            void playEdgeAnim0();
            void playEdgeAnim1();
            void stopEdgeAnim0();
            void stopEdgeAnim1();
            void updateEdgeArrows();
            void playEdgeAnim2();
            void playEdgeAnim3();
            void stopEdgeAnim2();
            void stopEdgeAnim3();
            void initArwAnims();
            int checkProgress();
            void state0();
            void state2();
            int state3();
            void state4();
            void state6();
            void state7();
            void state8();
            void state9();
            void state10();
            void state11();
            void state12();
            BOOL findId(u64 id, const u64* list, u32 n);
            void state13();
            void state14();
            void state15();
            void state16();
            void state17();
            void state18();
            void state19();
            int state20();
            void state21();
            int state22();
            void state23();
            int state24();
            BOOL waitEnd();
            void draw();
            void drawProgress();

            int findDialogAPane(const char* name);
            void onPointDialogA(const char* name, controller::Interface* con);
            void onLeftDialogA(const char* name);
            void onTrigDialogA(const char* name);

            int findDialogBPane(const char* name);
            void onPointDialogB(const char* name, controller::Interface* con);
            void onLeftDialogB(const char* name);
            void onTrigDialogB(const char* name);

            int findDialogCPane(const char* name);
            void onPointDialogC(const char* name, controller::Interface* con);
            void onLeftDialogC(const char* name);
            void onTrigDialogC(const char* name);

            layout::Object* mpDialogA;        // 0x00
            layout::Object* mpDialogB;        // 0x04
            layout::Object* mpDialogC;        // 0x08
            layout::Object* mpDialogBg;       // 0x0C

            gui::PaneManager* mpPaneMgrA;     // 0x10
            gui::PaneManager* mpPaneMgrB;     // 0x14
            gui::PaneManager* mpPaneMgrC;     // 0x18

            int mCheckProgress;             // 0x1C
            int mDialogBtnType;             // 0x20
            int mDialogResult;              // 0x24
            int mNextProgress;              // 0x28
            int mState;                     // 0x2C
            int mUnk30[3];
            int mUnk3C[5];                  // 0x3C
            s32 mScrFlags[4];                 // 0x50
            SDChannelSelect* mpChanSelect;    // 0x60
            NandSDWorker::AppBlocksInfo mFreeArea;    // 0x64
            NandSDWorker::AppBlocksInfo mNeededArea;  // 0x6C
            u32 mMsgCount;                      // 0x74
            u32 unk_0x78;                       // 0x78
            u32 unk_0x7C;                       // 0x7C
            u64 unk_0x80[0x60];                 // 0x80
            u8 unk_0x380[0xFC0];                // 0x380
            u32 mField1340;                     // 0x1340
            u32 unk_0x1344;                     // 0x1344
            u64 mIdListA[0x60];                 // 0x1348
            u32 mField1648;                     // 0x1648
            u32 unk_0x164C;                     // 0x164C
            u64 mEntryList[0x60];               // 0x1650
            wchar_t mDialogText[0x840];         // 0x1950
            bool mbDialogOpen;                // 0x29D0
            bool mbChecking;                  // 0x29D1
            u8 unk_0x29D2[0x2];               // 0x29D2
            u8 unk_0x29D4[0x4];               // 0x29D4
            long long mCheckTime;               // 0x29D8
            int mUnk29E0;                       // 0x29E0
            struct {
                u64* ids;                       // +0x0
                u32 count;                      // +0x4
            } mCheckLists[3];                   // 0x29E4
            scroller mScroller;               // 0x29FC
            int mLineCount;                   // 0x2A6C
            bool mbEdgePlayed[4];             // 0x2A70
            u8 unk_0x2A74[0x4];               // 0x2A74
        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_SD_MEMORY_H
