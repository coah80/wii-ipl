#ifndef TEXTINPUT_MY_MANAGER_H
#define TEXTINPUT_MY_MANAGER_H

#include "tiManager.h"

#include "MyTiBg.h"
#include "MyTiInputForm.h"
#include "MyTiLetterForm.h"

namespace textinput {
    namespace extend {
        namespace memo {
            class State;

            class Manager : public textinput::Manager {
                public:
                    typedef enum ConfigType {
                        CT_Default = 0,
                        CT_Letter,
                        CT_PhotoLetter,
                        CT_Numeric,
                        CT_NormalWithoutLineFeed,
                        CT_NormalBigTextWithoutLineFeed,
                        CT_OnlyQwertyWithoutLineFeedAndSign,
                        CT_OnlyQwertyBigTextWithoutLineFeedAndSign,
                        CT_NumericWithDot,
                        CT_NumericBigTextWithDot,
                        CT_NormalBigTextWithoutLineFeedWithSign,
                        CT_NumericWithSeparator,
                        CT_NormalWithoutLineFeedWithSign,
                        CT_PredictWithoutLineFeed,
                        CT_PredictBigText,

                        CT_Last
                    } ConfigType;

                    typedef enum StateType {
                        ST_Hidden = 0,
                        ST_Appearing,
                        ST_Visible,
                        ST_Disappearing,

                        ST_Last,
                    } StateType;

                    typedef enum StateTimeLine {
                        STL_Still = 0,
                        STL_Transition,
                        STL_Last
                    } StateTimeLine;

                    Manager(MEMAllocator* allocator, nw4r::lyt::MultiArcResourceAccessor* multiArc, textinput::EventObserver* event) : textinput::Manager(allocator, multiArc, event),
                    mpCurrentState(NULL),
                    meConfigType(CT_Letter),
                    mpMemoInputForm(NULL),
                    mpLetterInputForm(NULL),
                    mpBigTextInputForm(NULL),
                    mpDefaultPCKeyboard(NULL),
                    mpDefaultCellPhoneKeyboard(NULL),
                    mpDefaultInputForm(NULL),
                    mpDefaultCandidateBox(NULL),
                    mpDefaultToolBar(NULL),
                    mpDefaultPredictLanguageDialog(NULL),
                    mpDefaultSignWindow(NULL),
                    mpBackGround(NULL) {}

                    virtual ~Manager();

                    virtual void                    create(MEMAllocator* allocator);
                    virtual void                    init();

                    virtual void                    calc();
                    virtual void                    draw();

                    virtual bool                    updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release);
                    virtual bool                    updateInput(input::HKBManager& hkbManager);

                    virtual void                    SetFont(nw4r::lyt::FontRefLink* fontLink);

                    virtual void                    start();
                    virtual void                    end();

                    virtual textinput::InputForm*    createInputForm();

                    virtual void                    memoDraw();

                    virtual void setSaveData(savedata::MemoSetting memoSetting) {
                        mMemoSetting = memoSetting;
                    }
                    virtual savedata::MemoSetting   getSaveData()   { return mMemoSetting; }

                    virtual void                    changeState(StateTimeLine stateTimeLine);
                    virtual State*                  getState()      { return mpCurrentState; }
                    virtual void                    setState(StateType stateType);

                    virtual ConfigType              getConfigType() { return meConfigType; }

                    virtual void                    setSaveData_();
                    virtual void                    reflectSaveData();

                    virtual void                    configDefault();
                    virtual void                    configLetter();
                    virtual void                    configPhotoLetter();
                    virtual void                    configNumeric();
                    virtual void                    configNormalWithoutLineFeed();
                    virtual void                    configNormalBigTextWithoutLineFeed();
                    virtual void                    configOnlyQwertyWithoutLineFeedAndSign();
                    virtual void                    configOnlyQwertyBigTextWithoutLineFeedAndSign();
                    virtual void                    configNumericWithDot();
                    virtual void                    configNumericBigTextWithDot();
                    virtual void                    configNormalBigTextWithoutLineFeedWithSign();
                    virtual void                    configNumericWithSeparator();
                    virtual void                    configNormalWithoutLineFeedWithSign();
                    virtual void                    configPredictWithoutLineFeed();
                    virtual void                    configPredictBigText();
                    virtual InputForm*              createMemoInputForm();
                    virtual letter::InputForm*      createLetterInputForm();
                    virtual textinput::InputForm*    createBigTextInputForm();
                    virtual bg::LayoutByNW4R*       createBG();

                    void                            reflectSaveDataRev1();
                    void                            reflectSaveDataDefault();

                private:
                    State*                  mpCurrentState;                 // 0x40
                    ConfigType              meConfigType;                   // 0x44
                    savedata::MemoSetting   mMemoSetting;                   // 0x48
                    MemoInputForm*          mpMemoInputForm;                // 0x50
                    LetterInputForm*        mpLetterInputForm;              // 0x54
                    textinput::InputForm*   mpBigTextInputForm;             // 0x58
                    keyboard::pctype::LayoutByNW4R*        mpDefaultPCKeyboard;            // 0x5C
                    keyboard::cellphonetype::LayoutByNW4R* mpDefaultCellPhoneKeyboard;     // 0x60
                    textinput::InputForm*   mpDefaultInputForm;             // 0x64
                    candidatebox::LayoutByNW4R*   mpDefaultCandidateBox;          // 0x68
                    toolbar::LayoutByNW4R*        mpDefaultToolBar;               // 0x6C
                    predictlang::LayoutByNW4R*    mpDefaultPredictLanguageDialog; // 0x70
                    keyboard::signwindow::LayoutByNW4R*  mpDefaultSignWindow;       // 0x74
                    bg::LayoutByNW4R*         mpBackGround;                   // 0x78

                    friend class State;
            };

            class State {
                public:
                    State() : mpManager(NULL) {}
                    virtual ~State();
                    virtual Manager::StateType  getStateType() = 0;

                    virtual void                create() = 0;

                    virtual void                init() = 0;

                    virtual void                draw() = 0;
                    virtual void                memoDraw() = 0;

                    virtual void                calc() = 0;

                    virtual bool                updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release) = 0;
                    virtual bool                updateInput(input::HKBManager& hkbManager) = 0;

                    virtual void                start() = 0;
                    virtual void                end() = 0;

                    virtual InputForm*                          InputForm();
                    virtual keyboard::hwkey::HWKeyboard*        HWKeyboard();
                    virtual keyboard::pctype::LayoutByNW4R*     PCKeyboard();
                    virtual keyboard::cellphonetype::LayoutByNW4R* CellPhoneKeyboard();
                    virtual keyboard::signwindow::LayoutByNW4R* SignKeyboard();
                    virtual candidatebox::LayoutByNW4R*         CandidateBox();
                    virtual toolbar::LayoutByNW4R*              ToolBar();
                    virtual predictlang::LayoutByNW4R*          PredictLanguageSelectDialog();
                    virtual bg::LayoutByNW4R*                   BG();

                protected:
                    Manager*    mpManager;  // 0x04

                    friend class Manager;
            };

            class DispMemoState : public State {
                public:
                    virtual ~DispMemoState();
                    virtual Manager::StateType  getStateType();

                    virtual void                create();
                    virtual void                init();

                    virtual void                draw();
                    virtual void                memoDraw();

                    virtual void                calc();

                    virtual bool                updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release);
                    virtual bool                updateInput(input::HKBManager& hkbManager);

                    virtual void                start();
                    virtual void                end();
            };

            class AppearMemoState : public State {
                public:
                    AppearMemoState() : mfAnim(0.0f) {}
                    virtual ~AppearMemoState();
                    virtual Manager::StateType  getStateType();

                    virtual void                create();
                    virtual void                init();

                    virtual void                draw();
                    virtual void                memoDraw();

                    virtual void                calc();

                    virtual bool                updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release);
                    virtual bool                updateInput(input::HKBManager& hkbManager);

                    virtual void                start();
                    virtual void                end();

                protected:
                    f32     mfAnim;     // 0x08
            };

            class EditMemoState : public State {
                public:
                    virtual ~EditMemoState();
                    virtual Manager::StateType  getStateType();

                    virtual void                create();
                    virtual void                init();

                    virtual void                draw();
                    virtual void                memoDraw();

                    virtual void                calc();

                    virtual bool                updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release);
                    virtual bool                updateInput(input::HKBManager& hkbManager);

                    virtual void                start();
                    virtual void                end();
            };

            class DisappearMemoState : public AppearMemoState {
                public:
                    virtual ~DisappearMemoState();
                    virtual Manager::StateType  getStateType();

                    virtual void                calc();

                    virtual void                start();
            };
        }
    }
    typedef extend::memo::Manager MemoManager;
}

#endif // TEXTINPUT_MY_MANAGER_H
