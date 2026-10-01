#ifndef TEXTINPUT_STRING_BASE_H
#define TEXTINPUT_STRING_BASE_H

#include <revolution/types.h>
#include <revolution/mem/allocator.h>
#include <revolution/kpr.h>

namespace textinput {
    namespace tistring {
        class StringBase {
            public:
                StringBase(u16 maxLength) :
                muMaxLength(maxLength),
                muLength(0),
                mpszString(NULL),
                mpszTmpString(NULL),
                mwcCandidate(0),
                mpAllocator(NULL) {}

                virtual ~StringBase();

                virtual void        create(MEMAllocator* allocator);
                virtual void        pushBack(wchar_t ch);
                virtual void        popBack();
                virtual void        clear();
                virtual u16         getLength() const               { return muLength; }
                virtual bool        append(const wchar_t* string);
                virtual bool        insert(u16, const wchar_t* string);
                virtual void        remove(u16, u16);
                virtual void        replace(u16, u16, const wchar_t* string);

                virtual void        set(const wchar_t* string);
                virtual void        setAt(u16 index, wchar_t ch);

                virtual void        setLength(u16);

                virtual wchar_t*    getWCString() const;

                virtual void        setCandidate(wchar_t candidate) { mwcCandidate = candidate; }
                virtual wchar_t     getCandidate() const            { return mwcCandidate; }
                virtual bool        hasCandidate() const;

                virtual wchar_t     getLastWChar();

            protected:
                u16             muMaxLength;    // 0x04
                u16             muLength;       // 0x06

                wchar_t*        mpszString;     // 0x08
                wchar_t*        mpszTmpString;  // 0x0C

                wchar_t         mwcCandidate;   // 0x10

                MEMAllocator*   mpAllocator;    // 0x14
        };

        class KanaStream {
        public:
            KPRQueue mQueue;
            wchar_t mPending;
            wchar_t mOutput[5];
        };

        class Decolated : public StringBase {
        public:
            enum TranslateMode { TM_Direct, TM_Kana, TM_Roman, TM_Hangul };

            Decolated(u16 maxLen) : StringBase(maxLen), mCursorStart(0), mCursorEnd(0), mbSustain(false), mTranslateMode(0) { initKanaConverter(); }
            virtual ~Decolated();

            virtual void clear();
            virtual void set(const wchar_t* string);
            virtual void setLength(u16);

            virtual void inputChar(wchar_t);
            virtual void inputString(const wchar_t*);
            virtual void deleteChar();
            virtual void backSpace();
            virtual void confirm(const wchar_t*);
            virtual bool moveCursorRight();
            virtual bool moveCursorLeft();
            virtual void setCursorPos(u32);
            virtual void onSustain();
            virtual void offSustain();
            virtual bool isOnSustain();
            virtual u32 getCursorPos() const;
            virtual void getCursorPos(u32*, u32*);
            virtual bool canBackSpace();
            virtual bool deleteForward();
            virtual void getSelected(u32&, u32&);
            virtual wchar_t getWCharAtCursor();
            virtual void replaceAtCursor(wchar_t);
            virtual bool isDakuten();
            virtual void converDakuten();
            virtual bool isHandaku();
            virtual void converHandaku();
            virtual void convertAll();
            virtual bool isSmall();
            virtual void converSmall();
            virtual bool atTheBeginningOfASentence();
            virtual void initKanaConverter();
            virtual void* getKanaBuffer();
            virtual bool isKanaFix() const;
            virtual void confirmKana();
            virtual void clearKana();
            virtual void EnableKSXFilter(bool);

            void setTranslateMode(TranslateMode mode);
            TranslateMode getTranslateMode() const { return static_cast<TranslateMode>(mTranslateMode); }
            void inputString(const wchar_t* string, TranslateMode mode);

        private:
            u32 mCursorStart;        // 0x18
            u32 mCursorEnd;          // 0x1C
            u8  mbSustain;           // 0x20
            s32 mTranslateMode;      // 0x24
            KanaStream mKanaStream;  // 0x28
        };

        class WithAtok : public Decolated {
        public:
            struct DrawInfo;

            ~WithAtok();

            virtual void pushBack(wchar_t ch);
            virtual void popBack();
            virtual void inputChar(wchar_t);
            virtual void backSpace();
            virtual void confirm(const wchar_t*);
            virtual bool moveCursorRight();
            virtual bool moveCursorLeft();
            virtual void getCursorPos(u32*, u32*);

            virtual bool isFix();
            virtual void setFix(bool);
            virtual void initConverting();
            virtual bool isConverting();
            virtual wchar_t* getConfirmedWCString() const;
            virtual int getCurrentNumPredicted();
            virtual bool getPredicted(int, wchar_t*);
            virtual void commitPredicted(int);
            virtual void setSelectedCandidate(long);
            virtual bool isCandidateSelected();
            virtual int getSelectedCandidate();
            virtual void init();
            virtual void setInputting(wchar_t);
            virtual void getDrawString(DrawInfo&);
            virtual void openDictionary(void*, int, void*, int, void*, int);
            virtual void closeDictionary();
            virtual bool hasConfirmedString();
            virtual void enableConfirmedString(bool);
            virtual void startConverting();
            virtual bool isDictionaryOpened();
            virtual void changeKanaMode(bool);
            virtual int getInputStringLength();
            virtual void resetRelation();
            virtual void setFixMode(bool);
            virtual void setFixPrediction(int, const char* const*);
            virtual void setDefaultPrediction(int, const char* const*);
            virtual int getSelectedConverting();
            virtual int getFixedPredictionNum();
        };
    }
}

#endif // TEXTINPUT_STRING_BASE_H
