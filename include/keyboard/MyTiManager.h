#ifndef TEXTINPUT_MY_MANAGER_H
#define TEXTINPUT_MY_MANAGER_H

#include "tiManager.h"

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
#ifdef MYTIMANAGER_IMPLEMENTATION
                        CT_PredictBigText,
#endif

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

#ifdef MYTIMANAGER_IMPLEMENTATION
                    virtual textinput::InputForm*   createInputForm();
#else
                    virtual InputForm*              createInputForm();
#endif

                    virtual void                    memoDraw();

                    virtual void setSaveData(savedata::MemoSetting memoSetting) {
                        mMemoSetting = memoSetting;
                    }
                    virtual savedata::MemoSetting   getSaveData()   { return mMemoSetting; }

                    virtual void                    changeState(StateTimeLine stateTimeLine);
                    virtual State*                  getState()      { return mpCurrentState; }
                    virtual void                    setState(StateType stateType);

                    virtual ConfigType              getConfigType() { return meConfigType; }

#ifdef MYTIMANAGER_IMPLEMENTATION
                    virtual void                    setSaveData();
#else
                    virtual void                    setSaveData_();
#endif
                    virtual void                    reflectSaveData();
#ifdef MYTIMANAGER_IMPLEMENTATION
                    void reflectSaveDataRev1();
                    void reflectSaveDataDefault();
#endif

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
#ifdef MYTIMANAGER_IMPLEMENTATION
                    virtual textinput::MemoInputForm* createMemoInputForm();
                    virtual textinput::LetterInputForm* createLetterInputForm();
                    virtual textinput::InputForm* createBigTextInputForm();
                    virtual void* createBG();
#else
                    virtual void                    createMemoInputForm();
                    virtual void                    createLetterInputForm();
                    virtual void                    createBigTextInputForm();
                    virtual void                    createBG();
#endif

#ifdef MYTIMANAGER_IMPLEMENTATION
                    void* getBackGround() const { return mpBackGround; }
#endif

                private:
                    State*                  mpCurrentState;                 // 0x40
                    ConfigType              meConfigType;                   // 0x44
                    savedata::MemoSetting   mMemoSetting;                   // 0x48
                    MemoInputForm*          mpMemoInputForm;                // 0x50
                    LetterInputForm*        mpLetterInputForm;              // 0x54
                    textinput::InputForm*   mpBigTextInputForm;             // 0x58
                    void*                   mpDefaultPCKeyboard;            // 0x5C
                    void*                   mpDefaultCellPhoneKeyboard;     // 0x60
                    textinput::InputForm*   mpDefaultInputForm;             // 0x64
                    void*                   mpDefaultCandidateBox;          // 0x68
                    void*                   mpDefaultToolBar;               // 0x6C
                    void*                   mpDefaultPredictLanguageDialog; // 0x70
                    void*                   mpDefaultSignWindow;            // 0x74
                    void*                   mpBackGround;                   // 0x78
            };

            class State {
                public:
#ifdef MYTIMANAGER_IMPLEMENTATION
                    State() : mpManager(NULL) {}
                    Manager* getManager() const { return mpManager; }
                    void setManager(Manager* manager) { mpManager = manager; }
#endif
                    virtual ~State();
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

#ifdef MYTIMANAGER_IMPLEMENTATION
                    virtual InputForm* InputForm();
                    virtual keyboard::hwkey::HWKeyboard* HWKeyboard();
                    virtual keyboard::pctype::LayoutByNW4R* PCKeyboard();
                    virtual keyboard::cellphonetype::LayoutByNW4R* CellPhoneKeyboard();
                    virtual void* SignKeyboard();
                    virtual candidatebox::LayoutByNW4R* CandidateBox();
                    virtual toolbar::LayoutByNW4R* ToolBar();
                    virtual void* PredictLanguageSelectDialog();
                    virtual void* BG();
#endif

                private:
                    Manager*    mpManager;  // 0x04
            };
        }
    }
    typedef extend::memo::Manager MemoManager;
}

#endif // TEXTINPUT_MY_MANAGER_H
