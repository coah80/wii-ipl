#ifndef IPL_SCENE_SD_CHANNEL_OBJECT_H
#define IPL_SCENE_SD_CHANNEL_OBJECT_H

#include "layout/iplLayout.h"
#include "system/iplNand.h"
#include "system/iplNandShared.h"

#include <egg/core.h>

namespace ipl {
    namespace scene {
        class SDChannelObj {
        public:
            enum {
                STATE_LOAD_THUMBNAIL = 0,
                STATE_WAIT_LOAD_THUMBNAIL,
                STATE_CREATE_THUMBNAIL,
                STATE_NORMAL,
            };

            SDChannelObj(EGG::Heap* heap, int page, int index);
            ~SDChannelObj();

            void prepare();
            void create(nand::LayoutFile* sysLayoutFile);
            void calc();

            void* allocThumbBuffer();
            void calcNormal();

            void setHeaps(EGG::Heap* cursorHeap, EGG::Heap* balloonHeap);
            void setBasePane(const nw4r::lyt::Pane* basePane);

            void drawThumbnail();
            void drawCursor();
            void drawBalloon();

            nw4r::math::VEC3& getTranslate() const;

            BOOL isLayoutCreated() const NO_INLINE { return mState == STATE_NORMAL; }
            BOOL isValid() const;

            void onPoint(int unk);
            void onLeft(int unk);
            void onPinch(bool unk);

            void setCursorDecideAnim();

            void initCursorAnim(bool unk);
            void initBalloonAnim(bool unk);

            static void setLangPane(const layout::Object* layout);

            void createThumbnail();

            f32 createSDThumbnail();
            f32 createEmptyThumbnail();

            void initCursor();
            void calcCursor(const nw4r::math::VEC3& vec);

            void setCursorAnim(int unk) NO_INLINE;
            void calcCursorAnim();
            void startCursorAnim(int unk);

            void initBalloon();
            const wchar_t* getTitleName(int index);
            void setBalloonText(const wchar_t* text);
            void calcBalloon(const nw4r::math::VEC3& vec);

            void setBalloonAnim(int unk) NO_INLINE;
            void calcBalloonAnim();

            void bindNewAnm(layout::Object* layout);

            BOOL setupNew();
            void updateNew();

            void setPageIndex(int page, int index) {
                mChanPage = page;
                mChanIndex = index;
            }

            u64 getTitleID() const { return mTitleID; }
            int getChanType() const { return mChanType; }
            u8* getThumbBuffer() const { return mpThumbBuffer; }
            BOOL isBannerLoaded() const;

        private:
            u8 unk_0x00[8];

            EGG::Heap* mpCursorHeap;   // 0x08
            EGG::Heap* mpBalloonHeap;  // 0x0C
            EGG::Heap* mpMainHeap;     // 0x10

            int mState;  // 0x14

            int mChanPage;   // 0x18
            int mChanIndex;  // 0x1C

            nand::LayoutFile* mpSysLayoutFile;  // 0x20

            nw4r::lyt::Pane* mpBasePane;  // 0x24

            nand::File* mpThumbFile;        // 0x28
            layout::Object* mpThumbLayout;  // 0x2C
            layout::Animator* mpThumbAnim;  // 0x30

            enum {
                ANIM_CURSOR_FOCUS_OFF = 0,
                ANIM_CURSOR_FOCUS_ON,
                ANIM_CURSOR_SELECT,
                ANIM_CURSOR_MAX,
            };

            layout::Object* mpCursorLayout;                    // 0x34
            layout::Animator* mpCursorAnims[ANIM_CURSOR_MAX];  // 0x38
            int unk_0x44;
            int unk_0x48;

            layout::Object* mpBalloonLayout;  // 0x4C
            layout::Animator* mpBalloonAnim;  // 0x50
            int unk_0x54;
            int unk_0x58;
            int unk_0x5C;

            int unk_0x60;

            nw4r::lyt::Group* mpNwc24NewGroup;      // 0x64
            layout::GroupAnimator* mpNwc24NewAnim;  // 0x68
            bool mbNwc24NewPlayAnim;                // 0x6C
            int unk_0x70;
            u32 unk_0x74;

            f32 mThumbWidth;      // 0x78
            f32 mThumbHeight;     // 0x7C
            f32 mLocationAdjust;  // 0x80

            int mChanType;      // 0x84
            u8* mpThumbBuffer;  // 0x88

            u32 unk_0x8C;

            enum {
                TITLE_NAME_LENGTH = 0x15,
                NUM_TITLE_NAMES = 2,
                NUM_LANGUAGES = 12,
            };

            u64 mTitleID;    // 0x90
            u8 unk_0x98[0x5C];  // 0x98
            wchar_t mTitleNames[NUM_LANGUAGES][NUM_TITLE_NAMES][TITLE_NAME_LENGTH];  // 0xF4
            u8 unk_0x4E4[0x698 - 0x4E4];                       // 0x4E4

            friend class SDChannelSelect;
            friend class SDChannelSelectEvent;
        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_SD_CHANNEL_OBJECT_H
