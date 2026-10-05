#include "keyboard/tiUtil.h"
#include "keyboard/tiCpData.h"

#include <cstring>
#include <cwchar>

namespace textinput {
    namespace util {
        static wchar_t ConvertDakutenEtc(const wchar_t* map[], wchar_t ch);

        wchar_t toWLower(wchar_t ch) {
            const wchar_t* first = wcschr((wchar_t*)s_alphabet_map[ALPHABET_MAP_UPPER], ch);
            if (first != NULL) {
                u32 index = (u32)(first - s_alphabet_map[ALPHABET_MAP_UPPER]);
                return s_alphabet_map[ALPHABET_MAP_LOWER][index];
            } else {
                return ch;
            }
        }

        wchar_t toWUpper(wchar_t ch) {
            const wchar_t* first = wcschr((wchar_t*)s_alphabet_map[ALPHABET_MAP_LOWER], ch);
            if (first != NULL) {
                u32 index = (u32)(first - s_alphabet_map[ALPHABET_MAP_LOWER]);
                return s_alphabet_map[ALPHABET_MAP_UPPER][index];
            } else {
                return ch;
            }
        }

        wchar_t reverseLetterCaseW(wchar_t ch) {
            if (L'a' <= ch && ch <= L'z') {
                return toWUpper(ch);
            }
            if (L'A' <= ch && ch <= L'Z') {
                return toWLower(ch);
            }
            return ch;
        }

        wchar_t HankakuToZenkaku(wchar_t ch) {
            if (ch >= L'a' && ch <= L'z') {
                return static_cast<wchar_t>(ch + 0xFEE0);
            }
            if (ch >= L'A' && ch <= L'Z') {
                return static_cast<wchar_t>(ch + 0xFEE0);
            }
            if (ch >= L'0' && ch <= L'9') {
                return static_cast<wchar_t>(ch + 0xFEE0);
            }

            const wchar_t* map[] = {
                L"，．！？：　＠／＿－",
                L",.!?: @/_-",
            };

            const wchar_t* first = wcschr((wchar_t*)map[1], ch);
            if (first != NULL) {
                u32 index = (u32)(first - map[1]);
                return map[0][index];
            } else {
                return ch;
            }
        }

        static const wchar_t* s_all_map[] = {
            L"あいうえおかきくけこさしすせそたちつてとはひふへほやゆよわアイウエオカキクケコサシスセソタチツテトハヒフヘホヤユヨワ",
            L"　　　　　がぎぐげござじずぜぞだぢづでどばびぶべぼ　　　　　　ヴ　　ガギグゲゴザジズゼゾダヂヅデドバビブベボ　　　　",
            L"　　　　　　　　　　　　　　　　　　　　ぱぴぷぺぽ　　　　　　　　　　　　　　　　　　　　　　　　パピプペポ　　　　",
            L"ぁぃぅぇぉ　　　　　　　　　　　　っ　　　　　　　ゃゅょゎァィゥェォヵ　　ヶ　　　　　　　　ッ　　　　　　　ャュョヮ",
        };

        static const wchar_t* s_dakuten_map[] = {s_all_map[0], s_all_map[1]};

        static const wchar_t* s_handaku_map[] = {s_all_map[0], s_all_map[2]};

        static const wchar_t* s_small_map[] = {s_all_map[0], s_all_map[3]};

        wchar_t KBD_ConvertDakuten(wchar_t ch) {
            if (ch == L'　') {
                return ch;
            }

            // From handaku
            if (KBD_IsHandaku(ch)) {
                wchar_t ch1 = KBD_ConvertHandaku(ch);
                wchar_t ch2 = ConvertDakutenEtc(s_dakuten_map, ch1);
                if (ch2 != ch1) {
                    return ch2;
                } else {
                    return ch;
                }
            }

            // From small
            if (KBD_IsSmall(ch)) {
                wchar_t ch1 = KBD_ConvertSmall(ch);
                wchar_t ch2 = ConvertDakutenEtc(s_dakuten_map, ch1);
                if (ch2 != ch1) {
                    return ch2;
                } else {
                    return ch;
                }
            }

            return ConvertDakutenEtc(s_dakuten_map, ch);
        }

        wchar_t KBD_ConvertHandaku(wchar_t ch) {
            if (ch == L'　') {
                return ch;
            }

            // From Dakuten
            if (KBD_IsDakuten(ch)) {
                wchar_t ch1 = KBD_ConvertDakuten(ch);
                wchar_t ch2 = ConvertDakutenEtc(s_handaku_map, ch1);
                if (ch2 != ch1) {
                    return ch2;
                } else {
                    return ch;
                }
            }

            return ConvertDakutenEtc(s_handaku_map, ch);
        }

        wchar_t KBD_ConvertSmall(wchar_t ch) {
            if (ch == L'　') {
                return ch;
            }

            // From Dakuten
            if (KBD_IsDakuten(ch)) {
                wchar_t ch1 = KBD_ConvertDakuten(ch);
                wchar_t ch2 = ConvertDakutenEtc(s_small_map, ch1);
                if (ch2 != ch1) {
                    return ch2;
                } else {
                    return ch;
                }
            }

            return ConvertDakutenEtc(s_small_map, ch);
        }

        wchar_t KBD_ConvertAll(wchar_t ch) {
            int offset;

            if (ch == L'　') {
                return ch;
            }

            int i, j;
            for (i = 0; i < 4; i++) {
                wchar_t* first = wcschr((wchar_t*)s_all_map[i], ch);
                if (first != NULL) {
                    offset = first - s_all_map[i];
                    break;
                }
            }

            if (i < 4) {
                for (j = 1; j < 4; j++) {
                    if (s_all_map[(i + j) % 4][offset] != L'　') {
                        return s_all_map[(i + j) % 4][offset];
                    }
                }
            } else {
                return ch;
            }

            return ch;
        }

        bool KBD_IsDakuten(wchar_t ch) {
            wchar_t* first = wcschr((wchar_t*)s_dakuten_map[1], ch);
            return first != NULL;
        }

        bool KBD_IsHandaku(wchar_t ch) {
            wchar_t* first = wcschr((wchar_t*)s_handaku_map[1], ch);
            return first != NULL;
        }

        bool KBD_IsSmall(wchar_t ch) {
            wchar_t* first = wcschr((wchar_t*)s_small_map[1], ch);
            return first != NULL;
        }

        bool strcmp(const char* s1, const char* s2) {
            u32 len = strlen(s1);

            // should really be > but whatever
            if (len >= 16) {
                len = 16;
            }

            if (strncmp(s1, s2, len) == 0) {
                return true;
            } else {
                return false;
            }
        }

        void replaceChar(char* dest, u32 destLen, const char* src, int replaceIdx, char newCh) {
            memset(dest, 0, destLen);
            strncpy(dest, src, destLen);
            dest[replaceIdx] = newCh;
        }

        bool isAlphabet(wchar_t ch) {
            if (L'a' <= ch && ch <= L'z') {
                return true;
            }
            if (L'A' <= ch && ch <= L'Z') {
                return true;
            }
            return false;
        }

        static wchar_t ConvertDakutenEtc(const wchar_t* map[], wchar_t ch) {
            for (int i = 0; i < 2; i++) {
                const wchar_t* first = wcschr((wchar_t*)map[i], ch);

                if (first != NULL) {
                    u32 offset = (u32)(first - map[i]);

                    if (map[1 - i][offset] != L'　') {
                        return map[1 - i][offset];
                    } else {
                        return ch;
                    }
                }
            }
            return ch;
        }

        f32 hermiteInterporation(f32 time, f32 startTime, f32 startValue, f32 startTangent, f32 endTime, f32 endValue, f32 endTangent) {
            f32 timeOffset;
            f32 normalizedTimeSquared;
            f32 valueBlend;
            f32 tangentBlend;
            f32 intervalDelta;
            f32 normalizedTime;

            f32 result;

            timeOffset = time - startTime;
            intervalDelta = endTime - startTime;
            normalizedTime = timeOffset / intervalDelta;
            normalizedTimeSquared = normalizedTime * normalizedTime;
            result = normalizedTime + normalizedTime;
            tangentBlend = normalizedTimeSquared - normalizedTime;
            intervalDelta = startValue - endValue;
            valueBlend = (result * tangentBlend) - normalizedTimeSquared;
            result = startTangent + (startTangent * tangentBlend);
            valueBlend = startValue + (valueBlend * intervalDelta);
            result += endTangent * tangentBlend;
            result = (normalizedTime * startTangent) - result;
            result = valueBlend - (timeOffset * result);

            return result;
        }

        void getProjectionRect4x3(nw4r::ut::Rect* rect) {
            rect->left = -304.0;
            rect->right = 304.0;
            rect->bottom = 228.0;
            rect->top = -228.0;
        }

        void getProjectionRect16x9(nw4r::ut::Rect* rect) {
            rect->left = -416.0;
            rect->right = 416.0;
            rect->bottom = 228.0;
            rect->top = -228.0;
        }
    }  // namespace util
}  // namespace textinput
