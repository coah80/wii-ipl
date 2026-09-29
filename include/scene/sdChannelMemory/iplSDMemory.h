#ifndef IPL_SCENE_SD_MEMORY_H
#define IPL_SCENE_SD_MEMORY_H

#include <revolution.h>

#include "layout/iplLayout.h"
#include "layout/iplGuiManager.h"
#include "scene/board/iplFocusObject.h"
#include "scene/channelEdit/iplNandSDCardManager.h"

namespace ipl {
    namespace scene {
        class SDChannelSelect;

        class SDMemory {
        public:
            struct TitleRange {
                s32 mByteSize;
                u32 mCount;
            };

            SDMemory();
            ~SDMemory();

            void create(EGG::Heap* heap, nand::LayoutFile* layoutFile, SDChannelSelect* channelSelect);
            void setTitleLists(const TitleRange& nandTitles, const TitleRange& sdTitles);
            bool calc();
            void draw();
            void setScrollLimit();
            void updateSideArrows();
            void resetScrollArrows();
            void updateScrollArrows(u32 previousDownEnd, u32 previousUpEnd, u32 downEnd, u32 upEnd);
            void showDownArrow();
            void showUpArrow();
            void hideDownArrow();
            void hideUpArrow();
            void showLeftArrow();
            void showRightArrow();
            void hideLeftArrow();
            void hideRightArrow();

        private:
            s32 updateState();
            void drawTransferTitles();
            void onDialogState0();
            void onDialogState2();
            bool onDialogState3();
            void onDialogState4();
            void onDialogState6();
            void onDialogState7();
            void onDialogState8();
            void onDialogState9();
            void onDialogState10();
            void onDialogState11();
            void onDialogState12();
            void onDialogState13();
            void onDialogState14();
            void onDialogState15();
            void onDialogState16();
            void onDialogState17();
            void onDialogState18();
            void onDialogState19();
            bool onDialogState20();
            void onDialogState21();
            bool onDialogState22();
            void onDialogState23();
            bool onDialogState24();
            void resetDialogPaneAnimations();
            s32 getControlPaneIndex(const char* paneName);
            void activateControlPane(const char* paneName, ::gui::Component* component);
            void deactivateControlPane(const char* paneName);
            void cancelControlPane(const char* paneName);
            s32 getTitlePaneIndex(const char* paneName);
            void activateTitlePane(const char* paneName, ::gui::Component* component);
            void deactivateTitlePane(const char* paneName);
            void selectTitlePane(const char* paneName);
            s32 getDialogPaneIndex(const char* paneName);
            void activateDialogPane(const char* paneName, ::gui::Component* component);
            void deactivateDialogPane(const char* paneName);
            void selectDialogPane(const char* paneName);

            class ControlPaneEventHandler : public ::gui::EventHandler {
            public:
                ControlPaneEventHandler(SDMemory* instance) : ::gui::EventHandler(), mpInstance(instance) {}
                virtual void onEvent(u32 compId, u32 event, void* data);

            private:
                SDMemory* mpInstance;
            };

            class TitlePaneEventHandler : public ::gui::EventHandler {
            public:
                TitlePaneEventHandler(SDMemory* instance) : ::gui::EventHandler(), mpInstance(instance) {}
                virtual void onEvent(u32 compId, u32 event, void* data);

            private:
                SDMemory* mpInstance;
            };

            class DialogPaneEventHandler : public ::gui::EventHandler {
            public:
                DialogPaneEventHandler(SDMemory* instance) : ::gui::EventHandler(), mpInstance(instance) {}
                virtual void onEvent(u32 compId, u32 event, void* data);

            private:
                SDMemory* mpInstance;
            };

            layout::Object* mpMainLayout;
            layout::Object* mpTitleLayout;
            layout::Object* mpDialogLayout;
            layout::Object* mpProgressLayout;
            gui::PaneManager* mpPaneManagers[3];
            s32 mDialogState;
            s32 mProcessState;
            s32 mDisplayMode;
            s32 mMessageId;
            u32 mErrorCode;
            u32 mPanelStates[3];
            u32 mTitlePanelStates[5];
            u32 mPanelAnimationStates[4];
            SDChannelSelect* mpSDChannelSelect;
            TitleRange mNandTitleRange;
            TitleRange mSDTitleRange;
            u32 mTitleCount;
            u32 mCurrentTitle;
            u32 mTitleFlags;
            ESTitleId mTitleIds[96];
            wchar_t mTitleNames[96][21];
            u32 mTitleNameCount;
            u32 mSDTitleCount;
            ESTitleId mSDTitleIds[96];
            u32 mNandTitleCount;
            u32 mNandTitleNameCount;
            ESTitleId mNandTitleIds[96];
            wchar_t mCurrentTitleName[0x840];
            u8 mTransferFlags[4];
            u32 mTransferStatus;
            u64 mTransferStartTime;
            s32 mTransferFrame;
            struct TitleListState {
                ESTitleId* mpTitles;
                u32 mCount;
                ESTitleId* mpSecondaryTitles;
                u32 mSecondaryCount;
                ESTitleId* mpNames;
                u32 mNameCount;
            } mTitleListState;
            scroller mScroller;
            s32 mButtonState;
            u8 mControllerFlags[4];
            u32 mFinalState[3];
            u8 mFinalFlags[4];
        };
    }  // namespace scene
}  // namespace ipl

#endif
