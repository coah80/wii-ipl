#include <private/vf/PrFILE2/pf_types.h>

typedef struct PF_STR {
    const pf_s8* p_head;
    const pf_s8* p_tail;
    const pf_s8* p_current;
    pf_u32 code_mode;
} PF_STR;

typedef struct PFSTR_CHARCODE {
    pf_s32 (*oem2unicode)(const pf_s8*, pf_u16*);
    pf_s32 (*unicode2oem)(const pf_u16*, pf_s8*);
    pf_s32 (*oem_char_width)(const pf_s8*);
    pf_bool (*is_oem_mb_char)(pf_s8, pf_bool);
    pf_s32 (*unicode_char_width)(const pf_u16*);
    pf_bool (*is_unicode_mb_char)(pf_u16, pf_bool);
} PFSTR_CHARCODE;

typedef struct PFSTR_VOLUME_SET {
    pf_u8 state_prefix[0x48];
    PFSTR_CHARCODE codeset;
} PFSTR_VOLUME_SET;

extern PFSTR_VOLUME_SET pf_vol_set;

extern pf_s32 pf_toupper(pf_s32 c);
extern pf_u32 pf_strlen(const pf_s8* s);
extern pf_u32 pf_w_strlen(const pf_u16* s);
extern pf_s32 pf_strcmp(const pf_s8* s1, const pf_s8* s2);
extern pf_s32 pf_strncmp(const pf_s8* s1, const pf_s8* s2, pf_u32 length);

void PFSTR_SetCodeMode(PF_STR* p_str, pf_u32 code_mode) {
    p_str->code_mode = code_mode;
}

pf_u32 PFSTR_GetCodeMode(PF_STR* p_str) {
    return p_str->code_mode;
}

void PFSTR_SetLocalStr(PF_STR* p_str, const pf_s8* local_str) {
    if (p_str->code_mode == 1 || local_str == PF_NULL) {
        p_str->p_current = p_str->p_head;
    } else {
        p_str->p_current = local_str;
    }
}

pf_s8* PFSTR_GetStrPos(PF_STR* p_str, pf_u32 target) {
    pf_s8* p_pos;
    if (target == 1) {
        p_pos = (pf_s8*)p_str->p_head;
    } else if (target == 2) {
        p_pos = (pf_s8*)p_str->p_tail;
    } else {
        p_pos = (pf_s8*)p_str->p_current;
    }
    return p_pos;
}

void PFSTR_MoveStrPos(PF_STR* p_str, pf_s16 num_char) {
    pf_s16 cnt;
    pf_s16 offset = 0;
    pf_s32 width;
    pf_s8* p;
    pf_u16* wp;

    if (PFSTR_GetCodeMode(p_str) == 1) {
        p = (pf_s8*)p_str->p_head;
        while (num_char != 0) {
            if (pf_vol_set.codeset.is_oem_mb_char((pf_s8)*p, PF_TRUE)) {
                offset++;
            }
            offset++;
            num_char--;
        }
    } else {
        wp = (pf_u16*)p_str->p_head;

        for (cnt = 0; cnt < num_char; cnt++) {
            width = pf_vol_set.codeset.unicode_char_width(wp);
            wp += width;
            offset += (pf_s16)width;
        }
    }

    p_str->p_head = &p_str->p_head[offset];
}

pf_s32 PFSTR_InitStr(PF_STR* p_str, const pf_s8* s, pf_u32 code_mode) {
    if (code_mode == 1) {
        p_str->p_head = s;
        p_str->p_tail = &s[pf_strlen(s)];
    } else if (code_mode == 2) {
        p_str->p_head = s;
        p_str->p_tail = s + (pf_w_strlen((pf_u16*)s) * sizeof(pf_u16));
    }

    PFSTR_SetCodeMode(p_str, code_mode);
    return 0;
}

pf_u16 PFSTR_StrLen(PF_STR* p_str) {
    return (pf_u16)(p_str->p_tail - p_str->p_head);
}

pf_u16 PFSTR_StrNumChar(PF_STR* p_str, pf_u32 target) {
    pf_s8* p;
    pf_u16 cnt;
    pf_s32 width;

    if (target == 1) {
        p = (pf_s8*)p_str->p_head;
    } else {
        p = (pf_s8*)p_str->p_tail;
    }

    if (p_str->code_mode == 1) {
        for (cnt = 0; (pf_s8)*p != 0; cnt++) {
            if (pf_vol_set.codeset.is_oem_mb_char((pf_s8)*p, PF_TRUE)) {
                p++;
            }
            p++;
        }
    } else {
        for (cnt = 0; (pf_s8)p[0] != 0 || (pf_s8)p[1] != 0; cnt++) {
            width = pf_vol_set.codeset.unicode_char_width((pf_u16*)p);
            p += width;
        }
    }

    return cnt;
}

pf_s32 PFSTR_StrCmp(const PF_STR* p_str, const pf_s8* s) {
    pf_u16 wc;
    const pf_u16* wp;
    const pf_s8* stringCursor;
    const pf_s8* compareCursor;
    pf_s32 ret;

    if (p_str->code_mode == 1) {
        stringCursor = p_str->p_head;
        compareCursor = s;
        ret = pf_strcmp(stringCursor, compareCursor);
    } else {
        wp = (pf_u16*)p_str->p_head;

        do {
            pf_vol_set.codeset.oem2unicode(s, &wc);
            s++;

            if (*wp++ != wc) {
                break;
            }
        } while (*(wp - 1) != 0 && wc != 0);

        wp--;
        ret = *wp - wc;
    }

    return ret;
}

pf_s32 PFSTR_StrNCmp(PF_STR* p_str, const pf_s8* s, pf_u32 target, pf_s16 offset, pf_u16 num) {
    pf_u16 wc;
    const pf_u16* wp;
    const pf_s8* stringCursor;
    const pf_s8* compareCursor;
    pf_s32 ret;

    if (p_str->code_mode == 1 || target == 3) {
        if (target == 1) {
            stringCursor = &p_str->p_head[offset];
        } else if (target == 2) {
            stringCursor = &p_str->p_tail[offset];
        } else {
            stringCursor = &p_str->p_current[offset];
        }
        compareCursor = s;
        ret = pf_strncmp(stringCursor, compareCursor, num);
    } else {
        if (target == 1) {
            wp = (pf_u16*)p_str->p_head + offset;
        } else {
            wp = (pf_u16*)p_str->p_tail + offset;
        }

        do {
            pf_vol_set.codeset.oem2unicode(s, &wc);
            s++;
            num--;

            if (*wp++ != wc || num == 0) {
                break;
            }
        } while (*(wp - 1) != 0 && wc != 0);

        wp--;
        ret = *wp - wc;
    }

    return ret;
}

void PFSTR_ToUpperNStr(PF_STR* p_str, pf_u16 num, pf_s8* dest) {
    pf_u16 wc;
    const pf_u16* wp;
    const pf_s8* p;

    if (p_str->code_mode == 1) {
        p = (pf_s8*)p_str->p_head;

        for (; num != 0 && *p != 0; p++, num--) {
            *dest++ = pf_toupper(*p);
        }
    } else {
        wp = (pf_u16*)p_str->p_head;

        for (; num != 0 && *wp != 0; wp++, num--) {
            wc = (*wp >= 'a' && *wp <= 'z') ? *wp + ('A' - 'a') : *wp;
            *(dest) = (pf_u8)wc;
            *(dest + 1) = (pf_u8)(wc >> 8);
            dest += sizeof(pf_u16);
        }
        *dest = 0;
    }

    *dest = 0;
}
