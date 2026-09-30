#define TISTRING_IMPLEMENTATION
#include "keyboard/tiString.h"
#include "keyboard/tiUtil.h"
#include <revolution/kpr.h>
#include <wchar.h>

extern "C" {
u8 KPRLookAhead(KPRQueue*, wchar_t*, u32);
u32 KPRPutChar(KPRQueue*, wchar_t);
wchar_t KPRGetChar(KPRQueue*);
void KPRClearQueue(KPRQueue*);
void KPRInitQueue(KPRQueue*);
void KPRSetMode(KPRQueue*, u32);
}

namespace textinput {
namespace tistring {
Decolated::~Decolated() {}
void StringBase::create(MEMAllocator* allocator) {
    mpAllocator = allocator;
    mpszString = static_cast<wchar_t*>(MEMAllocFromAllocator(allocator, muMaxLength << 1));
    wmemset(mpszString, 0, muMaxLength);
    muLength = 0;
    mpszTmpString = static_cast<wchar_t*>(MEMAllocFromAllocator(allocator, muMaxLength << 1));
    wmemset(mpszTmpString, 0, muMaxLength);
}

StringBase::~StringBase() {
    MEMFreeToAllocator(mpAllocator, mpszString);
    MEMFreeToAllocator(mpAllocator, mpszTmpString);
}

void StringBase::pushBack(wchar_t ch) {
    wchar_t buffer[10];
    buffer[0] = ch;
    buffer[1] = 0;
    u32 length = wcslen(buffer);
    wcsncat(mpszString, buffer, length);
    muLength++;
}

void StringBase::popBack() {
    if (muLength != 0) {
        muLength--;
    }
    mpszString[muLength] = 0;
}

bool StringBase::append(const wchar_t* string) {
    u32 inputLength = wcslen(string);
    u16 length = getLength();
    if (inputLength + length > muMaxLength) {
        return false;
    }
    if (string == 0) {
        return false;
    }
    while (*string != 0) {
        mpszString[muLength] = *string;
        muLength++;
        string++;
    }
    mpszString[muLength] = 0;
    return true;
}

bool StringBase::insert(u16 position, const wchar_t* string) {
    u32 inputLength = wcslen(string);
    u32 length = getLength();
    s32 total = (inputLength & 0xffff) + (length & 0xffff);
    bool success;
    if (total > muMaxLength) {
        success = false;
    } else if (string == 0 || static_cast<u32>(position) > static_cast<u32>(getLength() & 0xffff)) {
        success = false;
    } else {
        wmemset(mpszTmpString, 0, muMaxLength);
        wcsncpy(mpszTmpString, mpszString + position, (getLength() & 0xffff) - position);
        muLength = position;
        mpszString[position] = 0;
        append(string);
        append(mpszTmpString);
        success = true;
    }
    return success;
}

void StringBase::remove(u16 position, u16 count) {
    u16 length = getLength();
    if (length != 0 && position <= getLength()) {
        s32 currentLength = getLength() & 0xffff;
        s32 end = position + count;
        if (end >= currentLength) {
            count = getLength() - position;
        }
        wmemset(mpszTmpString, 0, muMaxLength);
        wcsncpy(mpszTmpString, mpszString + position + count, (getLength() & 0xffff) - (position + count));
        muLength = position;
        mpszString[position] = 0;
        append(mpszTmpString);
    }
}

void StringBase::replace(u16 position, u16 count, const wchar_t* value) {
    s32 length = getLength();
    if (position + count >= length) {
        count = getLength() - position;
    }
    remove(position, count);
    insert(position, value);
}

void StringBase::set(const wchar_t* string) {
    clear();
    append(string);
}

void StringBase::setAt(u16 index, wchar_t ch) {
    if (muMaxLength <= index) {
        return;
    }
    mpszString[index] = ch;
}

void StringBase::setLength(u16 length) {
    for (u16 index = length; index < muLength; index++) {
        setAt(index, 0);
    }
    muLength = length;
}

void StringBase::clear() {
    wmemset(mpszString, 0, muMaxLength);
    muLength = 0;
}

wchar_t StringBase::getLastWChar() {
    s32 index = muLength - 1;
    if (index >= 0) {
        return mpszString[index];
    }
    return 0;
}

void Decolated::inputChar(wchar_t ch) {
    if (ch != 0xfffe) {
        wchar_t input[8];
        input[4] = 0;
        input[3] = 0;
        input[2] = 0;
        input[1] = 0;
        input[0] = 0;
        u16 count;
        if (static_cast<u32>(mTranslateMode) - 1 > 1) {
            goto nonKana;
        }
        {
            mKanaStream.mOutput[4] = 0;
            mKanaStream.mOutput[3] = 0;
            mKanaStream.mOutput[2] = 0;
            mKanaStream.mOutput[1] = 0;
            mKanaStream.mOutput[0] = 0;
            if (ch == 10 && KPRLookAhead(&mKanaStream.mQueue, 0, 0)) {
                count = KPRPutChar(&mKanaStream.mQueue, 0xffff) & 0xff;
            } else {
                ch = util::toWLower(ch);
                count = KPRPutChar(&mKanaStream.mQueue, ch) & 0xff;
            }
            for (u32 inputIndex = 0; (inputIndex & 0xff) < count; inputIndex++) {
                input[static_cast<u8>(inputIndex)] = KPRGetChar(&mKanaStream.mQueue);
            }
            KPRLookAhead(&mKanaStream.mQueue, mKanaStream.mOutput, 5);
            goto inputReady;
        }
nonKana:
        if (mTranslateMode == 3) {
            input[0] = ch;
            input[1] = 0;
            count = 1;
            mKanaStream.mOutput[0] = 0;
        } else {
            count = 1;
            input[0] = ch;
            input[1] = 0;
        }
inputReady:
        setCandidate(0);
        u32 start;
        u32 end;
        getSelected(start, end);
        if (start == end) {
            insert(mCursorStart, input);
            u32 currentCursor = mCursorStart;
            mCursorStart = currentCursor + static_cast<u16>(count);
        } else {
            replace(start, end - start, input);
            mCursorStart = start + static_cast<u16>(count);
        }
        mCursorEnd = mCursorStart;
    }
}

void Decolated::confirmKana() {
    inputChar(10);
}

void Decolated::clearKana() {
    KPRClearQueue(&mKanaStream.mQueue);
    mKanaStream.mOutput[0] = 0;
}

void Decolated::inputString(const wchar_t* string) {
    if (string != 0) {
        const wchar_t* current = string;
        for (; *current != 0; current++) {
            inputChar(*current);
        }
    }
}

void Decolated::inputString(const wchar_t* string, TranslateMode mode) {
    TranslateMode oldMode = static_cast<TranslateMode>(mTranslateMode);
    if (oldMode != mode) {
        if (!isKanaFix() && mode == 0) {
            confirmKana();
        }
        mTranslateMode = mode;
        switch (mode) {
        case 1:
            mKanaStream.mQueue.mode = static_cast<KPRMode>(4);
            break;
        case 2:
            mKanaStream.mQueue.mode = static_cast<KPRMode>(8);
            break;
        default:
            break;
        }
    }
    inputString(string);
    if (mTranslateMode != oldMode) {
        if (!isKanaFix() && oldMode == 0) {
            confirmKana();
        }
        mTranslateMode = oldMode;
        switch (oldMode) {
        case 1:
            mKanaStream.mQueue.mode = static_cast<KPRMode>(4);
            break;
        case 2:
            mKanaStream.mQueue.mode = static_cast<KPRMode>(8);
            break;
        default:
            break;
        }
    }
}

void Decolated::backSpace() {
    if (static_cast<u32>(mTranslateMode) - 1 <= 1 && KPRLookAhead(&mKanaStream.mQueue, 0, 0)) {
        mKanaStream.mQueue.iCount--;
        u32 count = KPRLookAhead(&mKanaStream.mQueue, 0, 0);
        mKanaStream.mOutput[count] = 0;
    } else {
        wchar_t empty[1];
        u32 start;
        u32 end;
        getSelected(start, end);
        if (start != end || start != 0) {
            if (start == end) {
                if (hasCandidate()) {
                    setCandidate(0);
                } else {
                    if (mCursorStart != 0) {
                        mCursorStart--;
                    }
                    remove(mCursorStart, 1);
                }
            } else {
                empty[0] = 0;
                replace(start, end - start, empty);
                mCursorStart = start;
            }
            mCursorEnd = mCursorStart;
        }
    }
}

void Decolated::confirm(const wchar_t* string) {
    if (string != 0) {
        insert(mCursorStart, string);
        u32 length = wcslen(string);
        mCursorStart += length;
        mCursorEnd = mCursorStart;
    }
}

bool Decolated::moveCursorRight() {
    if (mCursorStart < getLength()) goto moveRight;
    return mbSustain == 0;
moveRight:
    mCursorStart++;
    if (mbSustain == 0) {
        mCursorEnd = mCursorStart;
    }
    return false;
}

bool Decolated::moveCursorLeft() {
    if (mCursorStart == 0) {
        return false;
    }
    mCursorStart--;
    if (mbSustain == 0) {
        mCursorEnd = mCursorStart;
    }
    return true;
}

void Decolated::setCursorPos(u32 position) {
    u8 sustain = mbSustain;
    mCursorStart = position;
    if (sustain == 0) {
        mCursorEnd = position;
    }
}

void Decolated::onSustain() {
    mbSustain = 1;
    mCursorEnd = mCursorStart;
}

void Decolated::offSustain() {
    mbSustain = 0;
}

void Decolated::getCursorPos(u32* start, u32* end) {
    *start = mCursorStart;
    *end = mCursorEnd;
}

bool Decolated::canBackSpace() {
    if (mCursorStart != 0) goto canBackSpaceTrue;
    if (mCursorStart != 0) goto checkKanaFix;
    if (mCursorStart == mCursorEnd) goto checkKanaFix;
canBackSpaceTrue:
    return true;
checkKanaFix:
    if (isKanaFix() == 0) {
        return true;
    }
    return false;
}

bool Decolated::deleteForward() {
    u32 cursor = mCursorStart;
    if (cursor < getLength()) goto removeChar;
    return false;
removeChar:
    remove(cursor, 1);
    return true;
}

void Decolated::getSelected(u32& start, u32& end) {
    if (mCursorStart > mCursorEnd) {
        start = mCursorEnd;
        end = mCursorStart;
    } else {
        start = mCursorStart;
        end = mCursorEnd;
    }
}

wchar_t Decolated::getWCharAtCursor() {
    u32 start;
    u32 end;
    getSelected(start, end);
    if (end == 0) {
        return 0;
    }
    return mpszString[end - 1];
}

void Decolated::replaceAtCursor(wchar_t ch) {
    u32 start;
    u32 end;
    getSelected(start, end);
    if (end != 0) {
        mpszString[end - 1] = ch;
    }
}

bool Decolated::isDakuten() {
    return util::KBD_IsDakuten(getWCharAtCursor());
}

void Decolated::converDakuten() {
    wchar_t ch = getWCharAtCursor();
    replaceAtCursor(util::KBD_ConvertDakuten(ch));
}

bool Decolated::isHandaku() {
    return util::KBD_IsHandaku(getWCharAtCursor());
}

void Decolated::converHandaku() {
    wchar_t ch = getWCharAtCursor();
    replaceAtCursor(util::KBD_ConvertHandaku(ch));
}

void Decolated::convertAll() {
    wchar_t ch = getWCharAtCursor();
    replaceAtCursor(util::KBD_ConvertAll(ch));
}

bool Decolated::isSmall() {
    return util::KBD_IsSmall(getWCharAtCursor());
}

void Decolated::converSmall() {
    wchar_t ch = getWCharAtCursor();
    replaceAtCursor(util::KBD_ConvertSmall(ch));
}

bool Decolated::atTheBeginningOfASentence() {
    if (mCursorStart == 0) {
        return false;
    }
    if (getLength() < 1) {
        return false;
    }
    u32 start;
    u32 end;
    getSelected(start, end);
    if (start != end) {
        return false;
    }
    s32 ch = getWCharAtCursor();
    switch (ch) {
    case 0x2e:
    case 0x21:
    case 0x3f:
        return true;
    default:
        return false;
    }
}

void Decolated::setTranslateMode(TranslateMode mode) {
    if (mTranslateMode != mode) {
        if (!isKanaFix() && mode == 0) {
            confirmKana();
        }
        mTranslateMode = mode;
        switch (mode) {
        case 1:
            mKanaStream.mQueue.mode = static_cast<KPRMode>(4);
            break;
        case 2:
            mKanaStream.mQueue.mode = static_cast<KPRMode>(8);
            break;
        default:
            break;
        }
    }
}

void Decolated::initKanaConverter() {
    KPRInitQueue(&mKanaStream.mQueue);
    KPRSetMode(&mKanaStream.mQueue, 0);
    mKanaStream.mOutput[0] = 0;
    s32 mode = mTranslateMode;
    switch (mode) {
    case 1:
        mKanaStream.mQueue.mode = static_cast<KPRMode>(4);
        break;
    case 2:
        mKanaStream.mQueue.mode = static_cast<KPRMode>(8);
        break;
    default:
        break;
    }
}

void Decolated::setLength(u16 length) {
    for (u32 index = length; (index & 0xffff) < muLength; index++) {
        setAt(static_cast<u16>(index), 0);
    }
    muLength = length;
    if (mCursorStart > length) {
        mCursorEnd = length;
        mCursorStart = length;
    }
}

}
}
