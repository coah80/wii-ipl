#ifndef TEXTINPUT_ZI_STRING_H
#define TEXTINPUT_ZI_STRING_H

#ifdef TIINPUTFORM_IMPLEMENTATION
#include "tiString.h"
#include <eztx.h>
#endif

namespace textinput {
    namespace tistring {
        #ifdef TIINPUTFORM_IMPLEMENTATION
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
