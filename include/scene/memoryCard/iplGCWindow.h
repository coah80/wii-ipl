#ifndef IPL_SCENE_GC_WINDOW_H
#define IPL_SCENE_GC_WINDOW_H

#include "scene/memoryCard/iplMemoryCardBase.h"
#include "scene/memoryCard/iplMemoryCardManager.h"
#include "math/iplMathTypes.h"
#include "math/iplInterporation.h"

namespace ipl {
namespace scene {
class GCWindow : public MemoryBase, public MemCardEventListener {
#ifdef IPL_MEMORY_CARD_CPP
    friend class MemoryCard;
#endif
public:
    GCWindow(EGG::Heap*, nand::LayoutFile*, const char*, const char*);
    virtual ~GCWindow();
    void init(const math::VEC3&, MemoryCardManager*, u8, short);
    void calc();
    void draw();
    void destroy();
    void onPoint(const char*, controller::Interface*);
    void onLeft(const char*);
    void onTrig(const char*);
private:
    void on_wait();
    void on_fadein();
    void on_normal();
    void on_fadeout1st();
    void on_fadeout_yes1st();
    void on_focus_move();
    void on_focus_copy();
    void on_focus_del();
    void on_select_out();
    void on_dialog();
    void on_error_message();
    void on_process();
    void on_error_message1st();
    void on_error_message2nd();
    void on_error_message3rd();
    void on_format1st();
    void on_format2nd();
    void on_format3rd();
    void on_format4th();
    void on_format_error();
    void change_textbox_doing();
    void change_textbox_done();
    void set_texture(const char*, const GXTexObj&);
public:
    virtual void onMemEvent(long, u8);
#ifdef IPL_GC_WINDOW_CPP
    virtual void on_wait_anim() = 0;
    virtual void on_exit() = 0;
    virtual void on_error() = 0;
    virtual void on_format() = 0;
    virtual void on_dialog_result() = 0;
    virtual void on_select_in() = 0;
    virtual void on_message_done() = 0;
    virtual void on_button_trig() = 0;
#else
    virtual void on_wait_anim();
    virtual void on_exit();
    virtual void on_error();
    virtual void on_format();
    virtual void on_dialog_result();
    virtual void on_select_in();
    virtual void on_message_done();
    virtual void on_button_trig();
#endif
    bool isProcess();
    void stop_wait_anim();

private:
    int mState;
    MemoryBaseEvent* mpEvent;
    MemoryCardManager* mpMemoryCardManager;
    math::LinearIntp<math::VEC3> mLinearInterp;
    math::VEC3 mTranslate;
    u8 mCardState;
    short mCardIndex;
    int mOperation;
    bool mActive;
    bool mWaiting;
    u8 mFlags0[2];
    u8 mFlags1[2];
};

class SavedataEditWindow : public MemoryBase {
public:
    SavedataEditWindow(EGG::Heap* heap, nand::LayoutFile* layoutFile, const char* directory, const char* fileName);
    virtual void init();
    virtual void calc();
    virtual void draw();
    virtual void destroy();

private:
    void add_animation(const char* fileName, const char* groupName) {
        AnmName animation = {fileName, groupName};
        MemoryBase::add_animation(&animation, 1);
    }
    void on_normal();
    void on_fadein();
    void on_fadeout1st();
    void on_focus_del();
    void on_select_out();
    void on_fadeout_yes1st();

    int mState;
    MemoryBaseEvent* mpEvent;
    math::LinearIntp<math::VEC3> mLinearInterp;
    math::VEC3 mTranslate;
    bool mActive;
};

}
}

#endif
