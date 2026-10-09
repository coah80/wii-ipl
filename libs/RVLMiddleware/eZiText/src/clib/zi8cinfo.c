#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>

struct ZiInfoWork;
ziU32 Zi8GetCharInfo2(ziWChar, ziWChar*, ziU8, ziU8, ziWChar*, ziU8, struct ZiInfoWork*);

extern ziU8 Zi8GetFormatVersion(ziU8, ziPtr);
extern ziU16 Zi8GetTableCount(ziU8, ziU8, ziPtr);
extern ziU32 Zi8GetTableAddress(ziU8, ziU8, ziPtr);
extern ziU16 Zi8Uni2Ptr(ziWChar, ziU8*, ziPtr);
extern ziU16 Zi8GetPCode(ziU32, ziU8*);

typedef struct ZiInfoWork {
    ziU8 language;
    ziLanguageEntry* languageEntries;
    ziU32 dictionaryState[3];
    ziU16 errorCode;
    ziU8 cangjieEnabled;
    ziU8 options;
    ziU8 inputState;
} ZiInfoWork;

const ziU8 zi8CangjieCodes[32] = {
    1, 2, 3, 5, 6, 7, 9, 10, 11, 13, 14, 15, 17, 18, 19, 20,
    21, 22, 23, 25, 26, 27, 29, 30, 31
};

ziU32 Zi8GetCJInfo(ziU8* input, ziWChar* output, ziU8 outputSize, ziPtr __zi8_work_data)
{
    ziS32 packedCodes;
    ziS32 code;
    ziS32 outputCount;
    ziS32 codeCount;
    ziS32 index;

    ZI_WORK->cangjieEnabled = Zi8GetFormatVersion(ZI8_LANG_ZH, __zi8_work_data) & 2;
    if (ZI_WORK->cangjieEnabled == 0) {
        Zi8LogError(0x8fc, __zi8_work_data);
        return 0;
    }
    if (outputSize < 6) {
        Zi8LogError(0x322, __zi8_work_data);
        return 0;
    }

    codeCount = input[0] & 7;
    packedCodes = (packedCodes = (ziS32)(((ziU32)input[3] << 24) |
        (((ziU32)input[2] << 16) |
         (input[0] | ((ziU32)input[1] << 8))))) >> 3;
    outputCount = 0;
    while (outputCount < codeCount) {
        code = packedCodes & 0x1f;
        packedCodes >>= 5;
        for (index = 0; index < 0x19; index++) {
            if (zi8CangjieCodes[index] == code) {
                break;
            }
        }
        if (index >= 0x19) {
            Zi8LogError(0x26d, __zi8_work_data);
            return 0;
        }
        output[outputCount] = index + 0x41;
        outputCount++;
    }
    output[outputCount] = 0;
    Zi8LogError(100, __zi8_work_data);
    return (ziU8)outputCount;
}

ziU32 Zi8GetPInfo(ziU32 phoneticCode,ziU16 *output,ziU8 outputSize,ziPtr work)

{
    ziU16 initial;
    ziU16 final;
    ziU16 tone;
    int count;

    count = 0;
    if (outputSize < 8) {
        Zi8LogError(0x322,work);
        return 0;
    }
    else if ((phoneticCode & 0xffff) == 0) {
        Zi8LogError(0x276,work);
        return 0;
    }
    else {
        initial = ((phoneticCode & 0xffff) >> 9) & 0x3f;
        final = ((phoneticCode & 0xffff) >> 3) & 0x3f;
        tone = phoneticCode & 7;
        if (initial != 1) {
            switch(initial) {
            case 0x3c:
                output[(ziU8)count] = 0xf362;
                break;
            case 0x3f:
                output[(ziU8)count] = 0xf370;
                break;
            case 2:
                output[(ziU8)count] = 0xf364;
                break;
            case 5:
                output[(ziU8)count] = 0xf374;
                break;
            case 0x34:
                output[(ziU8)count] = 0xf367;
                break;
            case 0x37:
                output[(ziU8)count] = 0xf36b;
                break;
            case 6:
                output[(ziU8)count] = 0xf36a;
                break;
            case 9:
                output[(ziU8)count] = 0xf371;
                break;
            case 0x1c:
                output[(ziU8)count] = 0xf37a;
                break;
            case 0x18:
                output[(ziU8)count] = 0xf363;
                break;
            case 10:
                output[(ziU8)count] = 0xf378;
                break;
            case 0xc:
                output[(ziU8)count] = 0xf36d;
                break;
            case 0x38:
                output[(ziU8)count] = 0xf366;
                break;
            case 0x26:
                output[(ziU8)count] = 0xf36e;
                break;
            case 0x2b:
                output[(ziU8)count] = 0xf36c;
                break;
            case 0x3b:
                output[(ziU8)count] = 0xf368;
                break;
            case 0x1a:
                output[(ziU8)count] = 0xf373;
                break;
            case 0x2c:
                output[(ziU8)count] = 0xf372;
                break;
            case 0x11:
                output[(ziU8)count] = 0xf377;
                break;
            case 0xd:
                output[(ziU8)count] = 0xf379;
                break;
            case 0x1d:
                output[(ziU8)count++] = 0xf37a;
                output[(ziU8)count] = 0xf368;
                break;
            case 0x19:
                output[(ziU8)count++] = 0xf363;
                output[(ziU8)count] = 0xf368;
                break;
            case 0x1b:
                output[(ziU8)count++] = 0xf373;
                output[(ziU8)count] = 0xf368;
                break;
            default:
                Zi8LogError(0x277,work);
                return 0;
            }
            count = count + 1;
        }
        if (final != 0) {
            switch(final) {
            case 1:
                output[(ziU8)count++] = 0xf369;
                output[(ziU8)count++] = 0xf361;
                output[(ziU8)count] = 0xf36f;
                break;
            case 2:
                output[(ziU8)count++] = 0xf369;
                output[(ziU8)count++] = 0xf361;
                output[(ziU8)count] = 0xf36e;
                break;
            case 3:
                output[(ziU8)count++] = 0xf369;
                output[(ziU8)count++] = 0xf361;
                output[(ziU8)count++] = 0xf36e;
                output[(ziU8)count] = 0xf367;
                break;
            case 4:
                output[(ziU8)count++] = 0xf369;
                output[(ziU8)count] = 0xf361;
                break;
            case 8:
                output[(ziU8)count] = 0xf369;
                break;
            case 9:
                output[(ziU8)count++] = 0xf369;
                output[(ziU8)count] = 0xf365;
                break;
            case 0xb:
                output[(ziU8)count++] = 0xf369;
                output[(ziU8)count] = 0xf375;
                break;
            case 0xc:
                output[(ziU8)count++] = 0xf369;
                output[(ziU8)count] = 0xf36e;
                break;
            case 0xd:
                output[(ziU8)count++] = 0xf369;
                output[(ziU8)count++] = 0xf36e;
                output[(ziU8)count] = 0xf367;
                break;
            case 0xf:
                output[(ziU8)count++] = 0xf369;
                output[(ziU8)count++] = 0xf36f;
                output[(ziU8)count++] = 0xf36e;
                output[(ziU8)count] = 0xf367;
                break;
            case 0x10:
                output[(ziU8)count++] = 0xf375;
                output[(ziU8)count++] = 0xf361;
                output[(ziU8)count] = 0xf36e;
                break;
            case 0x11:
                output[(ziU8)count++] = 0xf375;
                output[(ziU8)count++] = 0xf361;
                output[(ziU8)count++] = 0xf36e;
                output[(ziU8)count] = 0xf367;
                break;
            case 0x13:
                output[(ziU8)count++] = 0xf375;
                output[(ziU8)count++] = 0xf361;
                output[(ziU8)count] = 0xf369;
                break;
            case 0x17:
                output[(ziU8)count++] = 0xf375;
                output[(ziU8)count] = 0xf361;
                break;
            case 0x18:
                output[(ziU8)count] = 0xf375;
                break;
            case 0x1c:
                output[(ziU8)count++] = 0xf375;
                output[(ziU8)count] = 0xf36e;
                break;
            case 0x1d:
                output[(ziU8)count++] = 0xf375;
                output[(ziU8)count] = 0xf369;
                break;
            case 0x1e:
                output[(ziU8)count++] = 0xf375;
                output[(ziU8)count] = 0xf36f;
                break;
            case 0x1f:
                if ((initial == 0x26) || (initial == 0x2b)) {
                    output[(ziU8)count++] = 0xf376;
                    output[(ziU8)count] = 0xf365;
                }
                else {
                    output[(ziU8)count++] = 0xf375;
                    output[(ziU8)count] = 0xf365;
                }
                break;
            case 0x20:
                output[(ziU8)count++] = 0xf361;
                output[(ziU8)count] = 0xf36e;
                break;
            case 0x21:
                output[(ziU8)count++] = 0xf361;
                output[(ziU8)count++] = 0xf36e;
                output[(ziU8)count] = 0xf367;
                break;
            case 0x23:
                output[(ziU8)count] = 0xf361;
                break;
            case 0x25:
                output[(ziU8)count++] = 0xf361;
                output[(ziU8)count] = 0xf369;
                break;
            case 0x26:
                output[(ziU8)count++] = 0xf361;
                output[(ziU8)count] = 0xf36f;
                break;
            case 0x28:
                output[(ziU8)count++] = 0xf36f;
                output[(ziU8)count++] = 0xf36e;
                output[(ziU8)count] = 0xf367;
                break;
            case 0x2a:
                output[(ziU8)count++] = 0xf36f;
                output[(ziU8)count] = 0xf375;
                break;
            case 0x2b:
                output[(ziU8)count] = 0xf36f;
                break;
            case 0x30:
                output[(ziU8)count++] = 0xf365;
                output[(ziU8)count] = 0xf36e;
                break;
            case 0x31:
                output[(ziU8)count++] = 0xf365;
                output[(ziU8)count++] = 0xf36e;
                output[(ziU8)count] = 0xf367;
                break;
            case 0x33:
                output[(ziU8)count++] = 0xf365;
                output[(ziU8)count] = 0xf372;
                break;
            case 0x34:
                output[(ziU8)count] = 0xf365;
                break;
            case 0x35:
                output[(ziU8)count++] = 0xf365;
                output[(ziU8)count] = 0xf369;
                break;
            case 0x38:
                output[(ziU8)count] = 0xf376;
                break;
            case 0x39:
                output[(ziU8)count++] = 0xf376;
                output[(ziU8)count++] = 0xf361;
                output[(ziU8)count] = 0xf36e;
                break;
            default:
                Zi8LogError(0x278,work);
                return 0;
            }
            count++;
        }
        switch (tone) {
        case 1:
            output[(ziU8)count++] = 0xf331;
            break;
        case 2:
            output[(ziU8)count++] = 0xf332;
            break;
        case 3:
            output[(ziU8)count++] = 0xf333;
            break;
        case 4:
            output[(ziU8)count++] = 0xf334;
            break;
        case 5:
            output[(ziU8)count++] = 0xf335;
            break;
        }
        output[(ziU8)count] = 0;
        Zi8LogError(100,work);
        return count;
    }
}

ziU32 Zi8GetZInfo(ziU32 phoneticCode,ziU16 *output,ziU8 outputSize,ziPtr work)

{
    ziU16 initial;
    ziU16 final;
    ziU16 tone;
    int count;

    count = 0;
    if (outputSize < 5) {
        Zi8LogError(0x322,work);
        return 0;
    }
    else if ((phoneticCode & 0xffff) == 0) {
        Zi8LogError(0x280,work);
        return 0;
    }
    else {
        initial = ((phoneticCode & 0xffff) >> 9) & 0x3f;
        final = ((phoneticCode & 0xffff) >> 3) & 0x3f;
        tone = phoneticCode & 7;
        switch(initial) {
        case 1:
            break;
        case 0x3c:
            output[(ziU8)count++] = 0xf305;
            break;
        case 0x19:
            output[(ziU8)count++] = 0xf314;
            break;
        case 0x18:
            output[(ziU8)count++] = 0xf318;
            break;
        case 2:
            output[(ziU8)count++] = 0xf309;
            break;
        case 0x38:
            output[(ziU8)count++] = 0xf308;
            break;
        case 0x34:
            output[(ziU8)count++] = 0xf30d;
            break;
        case 0x3b:
            output[(ziU8)count++] = 0xf30f;
            break;
        case 6:
            output[(ziU8)count++] = 0xf310;
            break;
        case 0x37:
            output[(ziU8)count++] = 0xf30e;
            break;
        case 0x2b:
            output[(ziU8)count++] = 0xf30c;
            break;
        case 0xc:
            output[(ziU8)count++] = 0xf307;
            break;
        case 0x26:
            output[(ziU8)count++] = 0xf30b;
            break;
        case 0x3f:
            output[(ziU8)count++] = 0xf306;
            break;
        case 9:
            output[(ziU8)count++] = 0xf311;
            break;
        case 0x2c:
            output[(ziU8)count++] = 0xf316;
            break;
        case 0x1b:
            output[(ziU8)count++] = 0xf315;
            break;
        case 0x1a:
            output[(ziU8)count++] = 0xf319;
            break;
        case 5:
            output[(ziU8)count++] = 0xf30a;
            break;
        case 10:
            output[(ziU8)count++] = 0xf312;
            break;
        case 0x1d:
            output[(ziU8)count++] = 0xf313;
            break;
        case 0x1c:
            output[(ziU8)count++] = 0xf317;
            break;
        default:
            Zi8LogError(0x281,work);
            return 0;
        }
        switch(final) {
        case 0:
            if ((initial != 0xc) && (initial != 0x26)) {
                return 0;
            }
            break;
        case 7:
            break;
        case 0x11:
            output[(ziU8)count++] = 0xf327;
            output[(ziU8)count++] = 0xf31a;
            break;
        case 0x17:
            output[(ziU8)count++] = 0xf327;
            break;
        case 0x12:
            output[(ziU8)count++] = 0xf327;
            output[(ziU8)count++] = 0xf31b;
            break;
        case 0x1a:
            output[(ziU8)count++] = 0xf327;
            output[(ziU8)count++] = 0xf320;
            break;
        case 0x15:
            output[(ziU8)count++] = 0xf327;
            output[(ziU8)count++] = 0xf31d;
            break;
        case 0x1b:
            output[(ziU8)count++] = 0xf327;
            output[(ziU8)count++] = 0xf321;
            break;
        case 0x1c:
            output[(ziU8)count++] = 0xf327;
            output[(ziU8)count++] = 0xf322;
            break;
        case 0x1e:
            output[(ziU8)count++] = 0xf327;
            output[(ziU8)count++] = 0xf323;
            break;
        case 0x1d:
            output[(ziU8)count++] = 0xf327;
            output[(ziU8)count++] = 0xf324;
            break;
        case 0x1f:
            output[(ziU8)count++] = 0xf327;
            output[(ziU8)count++] = 0xf325;
            break;
        case 0x3f:
            output[(ziU8)count++] = 0xf329;
            output[(ziU8)count++] = 0xf325;
            break;
        case 0x37:
            output[(ziU8)count++] = 0xf329;
            break;
        case 0x27:
            output[(ziU8)count++] = 0xf328;
            break;
        case 0x25:
        case 0x35:
            output[(ziU8)count++] = 0xf329;
            output[(ziU8)count++] = 0xf31d;
            break;
        case 0x3c:
            output[(ziU8)count++] = 0xf329;
            output[(ziU8)count++] = 0xf322;
            break;
        case 0x2c:
            output[(ziU8)count++] = 0xf328;
            output[(ziU8)count++] = 0xf322;
            break;
        case 0x3e:
            output[(ziU8)count++] = 0xf329;
            output[(ziU8)count++] = 0xf323;
            break;
        case 0x2e:
            output[(ziU8)count++] = 0xf328;
            output[(ziU8)count++] = 0xf323;
            break;
        case 0x21:
            output[(ziU8)count++] = 0xf328;
            output[(ziU8)count++] = 0xf31a;
            break;
        case 0x22:
            output[(ziU8)count++] = 0xf328;
            output[(ziU8)count++] = 0xf31b;
            break;
        case 0x28:
            output[(ziU8)count++] = 0xf328;
            output[(ziU8)count++] = 0xf31e;
            break;
        case 0x29:
            output[(ziU8)count++] = 0xf328;
            output[(ziU8)count++] = 0xf31f;
            break;
        case 0x2d:
            output[(ziU8)count++] = 0xf328;
            output[(ziU8)count++] = 0xf324;
            break;
        case 0x2f:
            output[(ziU8)count++] = 0xf328;
            output[(ziU8)count++] = 0xf325;
            break;
        case 1:
            output[(ziU8)count++] = 0xf31a;
            break;
        case 2:
            output[(ziU8)count++] = 0xf31b;
            break;
        case 3:
            output[(ziU8)count++] = 0xf31c;
            break;
        case 4:
            output[(ziU8)count++] = 0xf326;
            break;
        case 8:
            output[(ziU8)count++] = 0xf31e;
            break;
        case 0x18:
            output[(ziU8)count++] = 0xf327;
            output[(ziU8)count++] = 0xf31e;
            break;
        case 9:
            output[(ziU8)count++] = 0xf31f;
            break;
        case 10:
            output[(ziU8)count++] = 0xf320;
            break;
        case 0xb:
            output[(ziU8)count++] = 0xf321;
            break;
        case 0xc:
            output[(ziU8)count++] = 0xf322;
            break;
        case 0xe:
            output[(ziU8)count++] = 0xf323;
            break;
        case 0xd:
            output[(ziU8)count++] = 0xf324;
            break;
        case 0xf:
            output[(ziU8)count++] = 0xf325;
            break;
        default:
            Zi8LogError(0x282,work);
            return 0;
        }
        switch (tone) {
        case 1:
            output[(ziU8)count++] = 0xf331;
            break;
        case 2:
            output[(ziU8)count++] = 0xf332;
            break;
        case 3:
            output[(ziU8)count++] = 0xf333;
            break;
        case 4:
            output[(ziU8)count++] = 0xf334;
            break;
        case 5:
            output[(ziU8)count++] = 0xf335;
            break;
        }
        output[(ziU8)count] = 0;
        Zi8LogError(100,work);
        return count;
    }
}

ziU16 zi8StrokeCode(ziU32 stroke, ziPtr work) {
    switch (stroke) {
    case 0:
        return 0xef02;
    case 1:
        return 0xef04;
    case 2:
        return 0xef01;
    case 3:
        return 0xef07;
    case 4:
        return 0xef06;
    case 5:
        return 0xef03;
    case 6:
        return 0xef05;
    case 7:
        return 0xef08;
    case 8:
        return 0xef02;
    case 0xb:
        return 0xef07;
    default:
        Zi8LogError(0x14a, work);
        return 0;
    }
}

ziU32 Zi8GetSInfo(ziU8* strokes, ziU8* extraStrokes, ziWChar* outputBuffer, ziU8 outputSize, ziPtr work)
{
    int strokeIndex;
    int outputCount;
    int extraCount;

    outputCount = 0;
    Zi8LogError(100, work);
    if (outputSize <= 0x17) {
        Zi8ReplaceLastError(0x322, work);
        return 0;
    }
    for (strokeIndex = 0; strokeIndex < 4; strokeIndex++) {
        if (strokeIndex != 0) {
            outputBuffer[(ziU8)outputCount] = zi8StrokeCode((strokes[strokeIndex] & 0xf0) >> 4, work);
            if (outputBuffer[(ziU8)outputCount++] == 0) {
    badStroke:
                outputBuffer[(ziU8)--outputCount] = 0;
                return outputCount;
            }
        }
        outputBuffer[(ziU8)outputCount] = zi8StrokeCode(strokes[strokeIndex] & 0xf, work);
        if (outputBuffer[(ziU8)outputCount++] == 0) {
            goto badStroke;
        }
    }

    outputBuffer[(ziU8)outputCount] = zi8StrokeCode(extraStrokes[0] & 0xf, work);
    if (outputBuffer[(ziU8)outputCount++] == 0) {
        goto badStroke;
    }
    extraCount = (*extraStrokes++ & 0x70) >> 4;
    for (strokeIndex = 0; strokeIndex < extraCount; strokeIndex++) {
        outputBuffer[(ziU8)outputCount] = zi8StrokeCode((extraStrokes[strokeIndex] & 0xf0) >> 4, work);
        if (outputBuffer[(ziU8)outputCount++] == 0) {
            goto badStroke;
        }
        outputBuffer[(ziU8)outputCount] = zi8StrokeCode(extraStrokes[strokeIndex] & 0xf, work);
        if (outputBuffer[(ziU8)outputCount++] == 0) {
            goto badStroke;
        }
    }
    outputBuffer[(ziU8)outputCount] = 0;
    return outputCount;
}

ziU32 Zi81KeyPYinfo(ziU32 phoneticChar, ziPtr work) {
    switch (phoneticChar & 0xffff) {
    case 0xf361:
        return 0xeff2;
    case 0xf362:
        return 0xeff2;
    case 0xf363:
        return 0xeff2;
    case 0xf364:
        return 0xeff3;
    case 0xf365:
        return 0xeff3;
    case 0xf366:
        return 0xeff3;
    case 0xf367:
        return 0xeff4;
    case 0xf368:
        return 0xeff4;
    case 0xf369:
        return 0xeff4;
    case 0xf36a:
        return 0xeff5;
    case 0xf36b:
        return 0xeff5;
    case 0xf36c:
        return 0xeff5;
    case 0xf36d:
        return 0xeff6;
    case 0xf36e:
        return 0xeff6;
    case 0xf36f:
        return 0xeff6;
    case 0xf370:
        return 0xeff7;
    case 0xf371:
        return 0xeff7;
    case 0xf372:
        return 0xeff7;
    case 0xf373:
        return 0xeff7;
    case 0xf374:
        return 0xeff8;
    case 0xf375:
        return 0xeff8;
    case 0xf376:
        return 0xeff8;
    case 0xf377:
        return 0xeff9;
    case 0xf378:
        return 0xeff9;
    case 0xf379:
        return 0xeff9;
    case 0xf37a:
        return 0xeff9;
    case 0xf331:
        return 0xeff1;
    case 0xf332:
        return 0xeff2;
    case 0xf333:
        return 0xeff3;
    case 0xf334:
        return 0xeff4;
    case 0xf335:
        return 0xeff5;
    default:
        Zi8LogError(0x14b, work);
        return phoneticChar;
    }
}

ziU32 Zi81KeyZYinfo(ziU32 phoneticChar, ziPtr work) {
    switch (phoneticChar & 0xffff) {
    case 0xf305:
        return 0xeff1;
    case 0xf306:
        return 0xeff1;
    case 0xf307:
        return 0xeff1;
    case 0xf308:
        return 0xeff1;
    case 0xf309:
        return 0xeff2;
    case 0xf30a:
        return 0xeff2;
    case 0xf30b:
        return 0xeff2;
    case 0xf30c:
        return 0xeff2;
    case 0xf30d:
        return 0xeff3;
    case 0xf30e:
        return 0xeff3;
    case 0xf30f:
        return 0xeff3;
    case 0xf310:
        return 0xeff4;
    case 0xf311:
        return 0xeff4;
    case 0xf312:
        return 0xeff4;
    case 0xf313:
        return 0xeff5;
    case 0xf314:
        return 0xeff5;
    case 0xf315:
        return 0xeff5;
    case 0xf316:
        return 0xeff5;
    case 0xf317:
        return 0xeff6;
    case 0xf318:
        return 0xeff6;
    case 0xf319:
        return 0xeff6;
    case 0xf31a:
        return 0xeff7;
    case 0xf31b:
        return 0xeff7;
    case 0xf31c:
        return 0xeff7;
    case 0xf31d:
        return 0xeff7;
    case 0xf31e:
        return 0xeff8;
    case 0xf31f:
        return 0xeff8;
    case 0xf320:
        return 0xeff8;
    case 0xf321:
        return 0xeff8;
    case 0xf322:
        return 0xeff9;
    case 0xf323:
        return 0xeff9;
    case 0xf324:
        return 0xeff9;
    case 0xf325:
        return 0xeff9;
    case 0xf326:
        return 0xeff9;
    case 0xf327:
        return 0xeffa;
    case 0xf328:
        return 0xeffa;
    case 0xf329:
        return 0xeffa;
    case 0xf331:
        return 0xeff1;
    case 0xf332:
        return 0xeff2;
    case 0xf333:
        return 0xeff3;
    case 0xf334:
        return 0xeff4;
    case 0xf335:
        return 0xeff5;
    default:
        Zi8LogError(0x14c, work);
        return phoneticChar;
    }
}

void Zi8GetCharInfo(ziWChar ch,ziWChar* output,ziU8 outputSize,ziU8 mode,
ziPtr work)

{
    Zi8GetCharInfo2(ch,output,outputSize,mode,0,0,work);
    return;
}

ziU32 ZiCharInfo2(ziWChar ch, ziWChar* charInfoBuffer, ziU8 maxInfoBufSize, ziU32 hetMode, ziWChar* elements, ziU32 elementCount, ZiInfoWork* work)

{
    union {
        ziU8 bytes[12];
        struct {
            ziU8 strokes[9];
            ziU8 tableIndex;
            ziU8 offsetHigh;
            ziU8 offsetLow;
        } fields;
    } uniInfo;
    ziU8 *uniInfoBuffer;
    ziBool elementsMatch;
    ziU32 count;
    ziU16 codeOffset;
    ziU16 charTableCount;
    ziU8 *tableBase;
    ziU8 *tablePtr;
    ziU16 charIndex;
    ziU8 *alternateTable;
    ziU16 index;
    ziU16 alternatesRemaining;
    int strokeIndex;
    ziU8 highByte;
    ziU8 lowByte;
    uniInfoBuffer = uniInfo.bytes;
    tableBase = 0;
    if ((charInfoBuffer == 0) || (maxInfoBufSize == 0)) {
        Zi8LogError(300,work);
        return 0;
    }
    if (((ziU8)hetMode & 0x80) != 0) {
        hetMode = (ziU8)(hetMode & 0x7f);
        if (Zi8GetFormatVersion(ZI8_LANG_ZH,work) >= 4) {
            charTableCount = Zi8GetTableCount(ZI8_LANG_ZH,0x19,work);
            tablePtr = (ziU8*)Zi8GetTableAddress(ZI8_LANG_ZH,0x19,work);
        }
        else {
            charTableCount = 0;
            tablePtr = ZI8_NULL;
        }
        if ((hetMode & 0xff) == 1) {
            tableBase = (ziU8*)Zi8GetTableAddress(ZI8_LANG_ZH,3,work);
        }
        else {
            tableBase = (ziU8*)Zi8GetTableAddress(ZI8_LANG_ZH,4,work);
        }
        if ((hetMode & 0xff) != 1 && (hetMode & 0xff) != 2) goto lookupCharacter;
        if (charTableCount <= Zi8GetTableCount(ZI8_LANG_ZH,8,work)) {
            highByte = (ziU8)((ch >> 8) & 0xff);
            lowByte = (ziU8)ch;
            index = 0;
            while (index < charTableCount) {
                if ((highByte == *tablePtr) && (lowByte == tablePtr[1])) {
                    codeOffset = ((tablePtr[2] & 0x1f) << 8 | tablePtr[3]) << 1;
                    charIndex = (ziU16)(((ziU32)tablePtr[2] >> 5) & 7) + tableBase[codeOffset] +
                    (ziU16)(((ziU32)tableBase[codeOffset + 1] & 0xffff) << 8);
                    if ((hetMode & 0xff) == 1) {
                        count = Zi8GetPInfo(charIndex,charInfoBuffer,maxInfoBufSize,work);
                    }
                    else {
                        count = Zi8GetZInfo(charIndex,charInfoBuffer,maxInfoBufSize,work);
                    }
                normalizeStrokes:
                    if ((hetMode & 0xff) == 0x11) {
                        for (strokeIndex = 0; strokeIndex < (int)(count & 0xff); strokeIndex = strokeIndex + 1) {
                            switch (charInfoBuffer[strokeIndex]) {
                            case 0xef03:
                            case 0xef05:
                            case 0xef06:
                            case 0xef08:
                                charInfoBuffer[strokeIndex] = 0xef0a;
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    Zi8LogError(100,work);
                    return count;
                }
                index++;
                tablePtr = tablePtr + 4;
            }
        }
    }
    goto lookupCharacter;
lookupCharacter:
    codeOffset = Zi8Uni2Ptr(ch & 0xffff,uniInfoBuffer,work);
    if (codeOffset == 0xffff) {
        count = 0;
    }
    else {
        tablePtr = (ziU8*)Zi8GetTableAddress(ZI8_LANG_ZH,1,work);
        tablePtr += ((uniInfoBuffer[9] & 0xf) << 0x10 | (uniInfoBuffer[11] | ((ziU32)uniInfoBuffer[10] << 8)));
        work->cangjieEnabled = Zi8GetFormatVersion(ZI8_LANG_ZH,work) & 2;
        if ((((work->cangjieEnabled != 0) && ((hetMode & 0xff) != 7)) && ((hetMode & 0xff) != 10))
        && (((hetMode & 0xff) != 8 && ((hetMode & 0xff) != 9)))) {
            switch (*tablePtr & 7) {
            case 2:
                tablePtr += 2;
                break;
            case 3:
            case 4:
                tablePtr += 3;
                break;
            case 5:
                tablePtr += 4;
                break;
            default:
                tablePtr += 1;
                break;
            }
        }
        switch(hetMode & 0xff) {
        case 7:
        case 8:
        case 9:
        case 10:
            count = Zi8GetCJInfo(tablePtr,charInfoBuffer,maxInfoBufSize,work);
            if ((((hetMode & 0xff) == 9) || ((hetMode & 0xff) == 10)) && (2 < (count & 0xff))) {
                charInfoBuffer[1] = charInfoBuffer[(count & 0xff) - 1];
                charInfoBuffer[2] = 0;
                count = 2;
            }
            break;
        case 0:
        case 0x10:
        case 0x11:
            count = Zi8GetSInfo(uniInfoBuffer,tablePtr,charInfoBuffer,maxInfoBufSize,work);
            break;
        case 1:
        case 3:
            tableBase = (ziU8*)Zi8GetTableAddress(ZI8_LANG_ZH,3,work);
            charIndex = Zi8GetPCode((ziU32)tableBase,uniInfoBuffer);
            count = Zi8GetPInfo(charIndex,charInfoBuffer,maxInfoBufSize,work);
            break;
        case 2:
        case 4:
            tableBase = (ziU8*)Zi8GetTableAddress(ZI8_LANG_ZH,4,work);
            charIndex = Zi8GetPCode((ziU32)tableBase,uniInfoBuffer);
            count = Zi8GetZInfo(charIndex,charInfoBuffer,maxInfoBufSize,work);
            break;
        default:
            count = 0;
            break;
        }
        if ((((elementCount & 0xff) != 0) && ((uniInfoBuffer[0] & 0x80) != 0)) &&
        (((hetMode & 0xff) == 3 || ((hetMode & 0xff) == 4)))) {
            alternateTable = (ziU8 *)Zi8GetTableAddress(ZI8_LANG_ZH,5,work);
            alternatesRemaining = Zi8GetTableCount(ZI8_LANG_ZH,5,work);
            while (alternatesRemaining != 0) {
                if (codeOffset == (((ziU16)alternateTable[1] << 8) | (ziU16)alternateTable[0])) break;
                alternatesRemaining--;
                alternateTable += 4;
            }
        checkElements:
            if ((count & 0xff) >= (elementCount & 0xff)) {
                elementsMatch = ZI8_TRUE;
                for (index = 0; index < (int)(count & 0xff); index++) {
                    if (index == (int)(elementCount & 0xff)) break;
                    if ((hetMode & 0xff) == 3) {
                        if (elements[index] != (ziU16)Zi81KeyPYinfo(charInfoBuffer[index],work)) {
                            elementsMatch = ZI8_FALSE;
                            break;
                        }
                    } else {
                        if (elements[index] != (ziU16)Zi81KeyZYinfo(charInfoBuffer[index],work)) {
                            elementsMatch = ZI8_FALSE;
                            break;
                        }
                    }
                }
                if (elementsMatch) goto normalizeStrokes;
            }
            if ((alternatesRemaining == 0) || (codeOffset != (((ziU16)alternateTable[1] << 8) | (ziU16)alternateTable[0]))) goto normalizeStrokes;
            charIndex = ((ziU16)alternateTable[2] | ((ziU16)alternateTable[3] & 1) << 8) << 1;
            charIndex = (((ziU32)tableBase[charIndex + 1] & 0xffff) * 0x100) +
            tableBase[charIndex] + ((((int)alternateTable[3] & 0xffff) & 0xf0) >> 4);
            alternatesRemaining--;
            alternateTable = alternateTable + 4;
            if ((hetMode & 0xff) == 3) {
                count = Zi8GetPInfo(charIndex,charInfoBuffer,maxInfoBufSize,work);
            }
            else {
                count = Zi8GetZInfo(charIndex,charInfoBuffer,maxInfoBufSize,work);
            }
            goto checkElements;
        }
    }
    goto normalizeStrokes;
}

ziU32 Zi8GetCharInfo2(ziWChar ch, ziWChar* charInfoBuffer, ziU8 maxInfoBufSize, ziU8 hetMode, ziWChar* elements, ziU8 elementCount, ZiInfoWork* work)

{
    ziU8 savedWorkState;
    ziU32 result;

    savedWorkState = work->inputState;
    result = ZiCharInfo2(ch,charInfoBuffer,maxInfoBufSize,hetMode,elements,elementCount,work);
    if ((result & 0xff) == 0) {
        if (((savedWorkState & 0x80) != 0) || ((savedWorkState & 0x40) != 0) || ((savedWorkState & 1) != 0)) {
            work->inputState = 6;
        }
        else {
            work->inputState = 1;
        }
        result = ZiCharInfo2(ch,charInfoBuffer,maxInfoBufSize,hetMode,elements,elementCount,work);
        work->inputState = savedWorkState;
    }
    return result;
}
