#ifndef TEXTINPUT_STRING_BASE_H
#define TEXTINPUT_STRING_BASE_H

#include <revolution/types.h>
#include <revolution/mem/allocator.h>

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

                virtual wchar_t*    getWCString() const             { return mpszString; }

                virtual void        setCandidate(wchar_t candidate) { mwcCandidate = candidate; }
                #ifdef TIINPUTFORM_IMPLEMENTATION
                virtual wchar_t     getCandidate() const            { return mwcCandidate; }
#else
                virtual wchar_t     getCandidate()                  { return mwcCandidate; }
#endif
                virtual bool        hasCandidate() const;

                virtual wchar_t     getLastWChar();

            private:
                u16             muMaxLength;    // 0x04
                u16             muLength;       // 0x06

                wchar_t*        mpszString;     // 0x08
                wchar_t*        mpszTmpString;  // 0x0C

                wchar_t         mwcCandidate;   // 0x10

                MEMAllocator*   mpAllocator;    // 0x14
        };

        class KanaStream {
        private:
            u8 field_0x00[0x24];
        };

        class Decolated : public StringBase {
        public:
#ifdef TIINPUTFORM_IMPLEMENTATION
            Decolated(u16 maxLen) : StringBase(maxLen), mCursorStart(0), mCursorEnd(0), mbSustain(false), mTranslateMode(0) { initKanaConverter(); }
#else
            Decolated(u16 maxLen) : StringBase(maxLen), field_0x18(0), field_0x1C(0), field_0x20(0), field_0x24(0) { initKanaConverter(); }
#endif

#ifdef TIINPUTFORM_IMPLEMENTATION
            enum TranslateMode { TM_Direct, TM_Kana, TM_Roman, TM_Hangul };
            void setTranslateMode(TranslateMode mode);
            TranslateMode getTranslateMode() const { return static_cast<TranslateMode>(mTranslateMode); }
            void inputString(const wchar_t* string, TranslateMode mode);
            virtual void inputChar(wchar_t ch);
            virtual void inputString(const wchar_t* string);
            virtual void deleteChar();
            virtual void backSpace();
            virtual void confirm(const wchar_t* string);
            virtual bool moveCursorRight();
            virtual bool moveCursorLeft();
            virtual void setCursorPos(u32 pos);
            virtual void onSustain();
            virtual void offSustain();
            virtual bool isOnSustain();
            virtual u32 getCursorPos() const;
            virtual void getCursorPos(u32* start, u32* end);
            virtual bool canBackSpace();
#ifdef TIINPUTFORM_IMPLEMENTATION
            virtual bool deleteForward();
#else
            virtual void deleteForward();
#endif
            virtual void getSelected(u32& start, u32& end);
            virtual wchar_t getWCharAtCursor();
            virtual void replaceAtCursor(wchar_t ch);
            virtual bool isDakuten();
            virtual void converDakuten();
            virtual bool isHandaku();
            virtual void converHandaku();
            virtual void convertAll();
            virtual bool isSmall();
            virtual void converSmall();
            virtual bool atTheBeginningOfASentence();
            virtual void initKanaConverter();
            virtual wchar_t* getKanaBuffer();
            virtual bool isKanaFix() const;
            virtual void confirmKana();
            virtual void clearKana();
            virtual void EnableKSXFilter(bool enable);
#else
            virtual void inputChar();
            virtual void inputString();
            virtual void deleteChar();
            virtual void backSpace();
            virtual void confirm();
            virtual void moveCursorRight();
            virtual void moveCursorLeft();
            virtual void setCursorPos();
            virtual void onSustain();
            virtual void offSustain();
            virtual void isOnSustain();
            virtual void getCursorPos();
            virtual void getCursorPos(u32*, u32*);
            virtual void canBackSpace();
            virtual void deleteForward();
            virtual void getSelected();
            virtual void getWCharAtCursor();
            virtual void replaceAtCursor();
            virtual void isDakuten();
            virtual void converDakuten();
            virtual void isHandaku();
            virtual void converHandaku();
            virtual void convertAll();
            virtual void isSmall();
            virtual void converSmall();
            virtual bool atTheBeginningOfASentence();
            virtual void initKanaConverter();
            virtual void getKanaBuffer();
            virtual void isKanaFix();
            virtual void confirmKana();
            virtual void clearKana();
            virtual void EnableKSXFilter();

#endif

        private:
#ifdef TIINPUTFORM_IMPLEMENTATION
            u32 mCursorStart;
            u32 mCursorEnd;
            bool mbSustain;
            u32 mTranslateMode;
#else
            u32 field_0x18;          // 0x18
            u32 field_0x1C;          // 0x1C
            u8 field_0x20;           // 0x20
            u32 field_0x24;          // 0x24
#endif
            KanaStream mKanaStream;  // 0x28
        };

#ifdef TIINPUTFORM_IMPLEMENTATION
        class WithAtok : public Decolated {
        public:
            virtual void pushBack(wchar_t ch);
            virtual void popBack();
            virtual void inputChar(wchar_t ch);
            virtual void backSpace();
            virtual void confirm(const wchar_t* string);
            virtual bool moveCursorRight();
            virtual bool moveCursorLeft();
            virtual void getCursorPos(u32* start, u32* end);
            struct DrawInfo {
                const wchar_t* string;
                u32 start;
                u32 end;
                u32 selectedStart;
                u32 selectedEnd;
            };
            virtual bool isFix();
            virtual void setFix(bool fix);
            virtual void initConverting();
            virtual bool isConverting();
            virtual wchar_t* getConfirmedWCString() const;
            virtual int getCurrentNumPredicted();
            virtual void getPredicted(int index, wchar_t* string);
            virtual void commitPredicted(int index);
            virtual void setSelectedCandidate(s32 index);
            virtual bool isCandidateSelected();
            virtual s32 getSelectedCandidate();
            virtual void init();
            virtual void setInputting(wchar_t ch);
            virtual void getDrawString(DrawInfo& info);
            virtual void openDictionary(void* atok, int atokSize, void* apot, int apotSize, void* nintendo, int nintendoSize);
            virtual void closeDictionary();
            virtual bool hasConfirmedString();
            virtual void enableConfirmedString(bool enable);
            virtual void startConverting();
            virtual bool isDictionaryOpened();
            virtual void changeKanaMode(bool kana);
            virtual wchar_t getInputStringLength();
            virtual void resetRelation();
            virtual void setFixMode(bool fixed);
            virtual void setFixPrediction(int count, const char** predictions);
            virtual void setDefaultPrediction(int count, const char** predictions);
            virtual s16 getSelectedConverting();
            virtual s16 getFixedPredictionNum();
        };
#else
        class WithAtok : public StringBase {};
#endif
    }
}

#endif // TEXTINPUT_STRING_BASE_H
