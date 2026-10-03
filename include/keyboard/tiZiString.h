#ifndef TEXTINPUT_ZI_STRING_H
#define TEXTINPUT_ZI_STRING_H

#if defined(TIZISTRING_IMPLEMENTATION)
#include "tiString.h"
extern "C" {
#include <eztx.h>
}
#elif defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
#include "tiString.h"
#include <eztx.h>
#endif

namespace textinput {
    namespace tistring {
#if defined(TIZISTRING_IMPLEMENTATION)
class WithZi : public Decolated {
public:
    enum PredictLanguage {
        PL_0,
        PL_1,
        PL_2,
        PL_3,
        PL_4,
        PL_5,
        PL_6,
        PL_7,
        PL_8,
        PL_9,
        PL_10,
        PL_11
    };

    enum LetterMode {
        LM_0,
        LM_1,
        LM_2,
        LM_3
    };

    static u16 ElementBuffer[0x100];
    static u16 CandidatesBuffer[0x100];
    static u16 ElementWorkBuffer[0x100];
    static u16 PredictionBuffer[0x100];
    static u16 CandidatedWord[0xa00];
    static u16 LatestWord[0x40];

    virtual ~WithZi();
    virtual void create(MEMAllocator*);
    virtual void pushBack(wchar_t);
    virtual void popBack();
    virtual void clear();
    virtual void inputChar(wchar_t);
    virtual void backSpace();
    virtual void confirm(const wchar_t*);
    virtual bool moveCursorRight();
    virtual bool moveCursorLeft();
    virtual bool canBackSpace();
    virtual void EnableKSXFilter(bool);
    virtual void init();
    virtual void setInputting(wchar_t);
    virtual u32 getCurrentNumPredicted();
    virtual void getPredicted(int, wchar_t*);
    virtual wchar_t* getCurrentSelected();
    virtual u16 getInputStringLength();
    virtual void setSelectedCandidate(s32);
    virtual bool isFix();
    virtual void setPredictLaunguage(PredictLanguage);
    virtual void changeLetterMode(LetterMode);
    virtual void ChangeDictionaryLanguage(u8);
    virtual void setCellPhoneHoldingkey(void*);
    virtual u32 setElementBuffer();
    virtual u8 getPredictLanguage();
    void openDictionary(void*, void*);
    void clearCandidates();
    void partialConfirmForKR();
    void update();
    u32 complementsCandidates_(s32);
    void setCurrentWord(const wchar_t*);
    u32 getCurrentInput(wchar_t*, u32);
    wchar_t* getCurrentInput();

private:
    EZTXGetParam mSearch;
    u32 mSearchState;
    u8 mbDictionaryOpen;
    u8 mbContextChanged;
    u32 mCurrentWordLength;
    EZTXLanguageEntry* mpDictionaries;
    void* mpDictionaryWork;
    u16 mInputLength;
    u32 mCandidateCount;
    u32 mOemDictionaryId;
    u8 mDictionaryLanguage;
    s32 mSelectedCandidate;
    PredictLanguage mPredictLanguage;
    LetterMode mLetterMode;
    void* mpHoldingKey;
    u8 mbKoreanPartialConfirm;
};
#elif defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
        class WithZi : public Decolated {
        public:
            enum PredictLanguage { PL_Default };
            enum LetterMode { LM_Lower, LM_Normal, LM_Upper };
            WithZi(u16 maxLength) : Decolated(maxLength), mbDictionaryOpen(false), mbContextChanged(false),
                mCurrentWordLength(0), mpDictionaries(NULL), mpDictionaryWork(NULL), mInputLength(0),
                mCandidateCount(0), mOemDictionaryId(0), mDictionaryLanguage(0xff), mSelectedCandidate(0),
                mPredictLanguage(0), mLetterMode(2), mpHoldingKey(NULL), mbKoreanPartialConfirm(false) {}
            virtual ~WithZi();
            virtual void init();
            virtual void setInputting(wchar_t ch);
            virtual int getCurrentNumPredicted();
            virtual void getPredicted(int index, wchar_t* string);
            virtual const wchar_t* getCurrentSelected();
            virtual u16 getInputStringLength();
            virtual void setSelectedCandidate(s32 index);
            virtual bool isFix();
            virtual void setPredictLaunguage(PredictLanguage language);
            virtual void changeLetterMode(LetterMode mode);
            virtual void ChangeDictionaryLanguage(u8 language);
            virtual void setCellPhoneHoldingkey(void* key);
            virtual void setElementBuffer();
            virtual u8 getPredictLanguage();
            s32 getSelectedCandidateIndex() const { return mSelectedCandidate; }
            void openDictionary(void* ziDict, void* ziOemDict);
            void setCurrentWord(const wchar_t* string);
            void update();
            const wchar_t* getCurrentInput();
            s32 getCurrentInput(wchar_t* buffer, u32 length);
            void clearCandidates();
            void partialConfirmForKR();
        private:
            EZTXGetParam mSearch;
            u32 mSearchState;
            bool mbDictionaryOpen;
            bool mbContextChanged;
            u32 mCurrentWordLength;
            EZTXLanguageEntry* mpDictionaries;
            void* mpDictionaryWork;
            u16 mInputLength;
            s32 mCandidateCount;
            u32 mOemDictionaryId;
            u8 mDictionaryLanguage;
            s32 mSelectedCandidate;
            u32 mPredictLanguage;
            u32 mLetterMode;
            void* mpHoldingKey;
            bool mbKoreanPartialConfirm;
        };
#else
        class WithZi {
            public:
                virtual ~WithZi();

                void    openDictionary(void* ziDict, void* ziOemDict);
        };
#endif
    }
}

#endif // TEXTINPUT_ZI_STRING_H
