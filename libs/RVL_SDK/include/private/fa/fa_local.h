#ifndef FA_LOCAL_H
#define FA_LOCAL_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PF_STR {
    const s8* p_head;   // 0x00
    const s8* p_tail;   // 0x04
    s8* p_local;        // 0x08
    u32 code_mode;      // 0x0C
} PF_STR;

typedef struct PF_FILE_NAME_ITER {
    const s8* buf;    // 0x00
    u32 field_04;     // 0x04
    u32 kind;         // 0x08
    u16 index;        // 0x0C
    u16 pad_0E;       // 0x0E
} PF_FILE_NAME_ITER;

typedef struct PF_CHARCODE {
    s32 (*oem2unicode)(const s8*, u16*);         // 0x00
    s32 (*unicode2oem)(const u16*, s8*);         // 0x04
    s32 (*oem_char_width)(const s8*);            // 0x08
    u32 (*is_oem_mb_char)(s8, u32);              // 0x0C
    s32 (*unicode_char_width)(const u16*);       // 0x10
    u32 (*is_unicode_mb_char)(u16, u32);         // 0x14
} PF_CHARCODE;

typedef struct PF_VOLUME PF_VOLUME;
typedef struct PF_DIR_ENT PF_DIR_ENT;
typedef struct PF_ENT_ITER PF_ENT_ITER;

/* pf_vol_set global; offsets verified against base object */
typedef struct PF_VOLUME_SET {
    u8 pad_00[0x38];            // 0x00
    u32 config;                 // 0x38
    u8 pad_3C[0x4];             // 0x3C
    s32 last_error;             // 0x40
    s32 last_driver_error;      // 0x44
    PF_CHARCODE codeset;        // 0x48
    u32 setting;                // 0x60
    u8 pad_64[0x1C];            // 0x64
} PF_VOLUME_SET;

extern PF_VOLUME_SET pf_vol_set;

/* pf_str.c */
void PFSTR_SetCodeMode(PF_STR* p_str, u32 code_mode);
u32 PFSTR_GetCodeMode(PF_STR* p_str);
s8* PFSTR_GetStrPos(PF_STR* p_str, u32 target);
void PFSTR_MoveStrPos(PF_STR* p_str, s16 num_char);
s32 PFSTR_InitStr(PF_STR* p_str, const s8* s, u32 code_mode);
u16 PFSTR_StrLen(PF_STR* p_str);
u16 PFSTR_StrNumChar(PF_STR* p_str, u32 target);
s32 PFSTR_StrCmp(const PF_STR* p_str, const s8* s);
s32 PFSTR_StrNCmp(PF_STR* p_str, const s8* s, u32 target, s16 offset, u16 num);
void PFSTR_ToUpperNStr(PF_STR* p_str, u16 num, s8* dest);

/* pf_clib.c */
s32 pf_strcmp(const s8* s1, const s8* s2);
s32 pf_strncmp(const s8* s1, const s8* s2, u32 n);
s8* pf_strcpy(s8* dst, const s8* src);
u32 pf_strlen(const s8* s);
s32 pf_toupper(s32 c);
s32 pf_w_strcmp(const u16* s1, const u16* s2);
s32 pf_w_strncmp(const u16* s1, const u16* s2, u32 n);
u16* pf_w_strcpy(u16* dst, const u16* src);
u32 pf_w_strlen(const u16* s);

/* pf_code.c */
void PFCODE_Divide_Width(s32 width, s16* oem_width, s16* uni_width);
#define PF_CODE_C_TO_WC(x0, x1) ((u16)(((u8)(x0) << 8) + (u8)(x1)))
#define PF_CODE_C_TO_WC_ARR(x, i) PF_CODE_C_TO_WC(x[i], x[i + 1])

extern const u8 pf_valid_fn_char[96];

/* pf_service.c */
u16 PF_GET_LE_U16(const u8* p);

/* pf_volume.c */
PF_VOLUME* PFVOL_GetCurrentVolume(void);
PF_VOLUME* PFVOL_GetVolumeFromDrvChar(s8 drv_char);

#define PF_IS_PATH_SEPERATOR(s, t, i) ((PFSTR_StrNCmp(s, (const s8*)"\\", t, i, 1) == 0 || PFSTR_StrNCmp(s, (const s8*)"/", t, i, 1) == 0))
#define PF_IS_PATH_NULL(s, t, i) (PFSTR_StrNCmp(s, (const s8*)"\0", t, i, 1) == 0)
#define PF_IS_PATH_NOT_NULL(s, t, i) (PFSTR_StrNCmp(s, (const s8*)"\0", t, i, 1) != 0)

/* pf_path.c */
void PFPATH_InitTokenOfPath(PF_STR* p_str, s8* path, u32 code_mode);
s32 PFPATH_GetNextTokenOfPath(PF_STR* p_str, u32 wildcard);
s32 PFPATH_DoSplitPath(PF_STR* p_path, PF_STR* p_dir_path, PF_STR* p_filename, u32 wildcard);
s32 PFPATH_SplitPath(PF_STR* p_path, PF_STR* p_dir_path, PF_STR* p_filename);
s32 PFPATH_SplitPathPattern(PF_STR* p_path, PF_STR* p_dir_path, PF_STR* p_pattern);
PF_VOLUME* PFPATH_GetVolumeFromPath(PF_STR* p_path);
u32 PFPATH_MatchFileNameWithPattern(const s8* file_name, PF_STR* p_pattern, u32 is_long_name);
s32 PFPATH_cmpNameUni(const u16* p_name, PF_STR* sPattern);
s32 PFPATH_cmpNameImpl(const s8* p_name, const s8* p_pattern, u32* p_flag);
s32 PFPATH_cmpName(const s8* sShort, PF_STR* p_pattern, u32 is_short_search);
s32 PFPATH_cmpTailSFN(const s8* sfn_name, const s8* pattern);
s32 PFPATH_putShortName(u8* pDirEntry, const s8* short_name, u8 attr);
s32 PFPATH_getShortName(s8* short_name, const u8* pDirEntry, u8 attr);
void PFPATH_getLongNameformShortName(s8* short_name, s8* long_name, u8 flag);
u32 PFPATH_GetLengthFromShortname(const s8* sSrc);
u32 PFPATH_GetLengthFromUnicode(const u16* sSrc);
s32 PFPATH_transformFromUnicodeToNormal(s8* sDest, const u16* sSrc);
s32 PFPATH_transformInUnicode(u16* sDestStr, const s8* sSrcStr);
u32 PFPATH_parseShortName(s8* pDest, PF_STR* p_pattern);
s32 PFPATH_parseShortNameNumeric(s8* p_char, u32 count);
void PFPATH_SetSearchPattern(s8* p_buf_local, u16* p_buf_unicode, PF_STR* p_pattern);
u32 PFPATH_CheckExtShortNameSignature(PF_STR* p_str);
u32 PFPATH_CheckExtShortName(PF_STR* p_str, u32 target, u32 wildcard);
u32 PFPATH_GetExtShortNameIndex(PF_STR* p_str, u32* p_index);
s32 PFPATH_AdjustExtShortName(s8* pName, u32 position);
u16 PFPATH_GetNextCharOfPattern(PF_STR* p_pattern, u32 name_kind);
u32 PFPATH_DoMatchFileNameWithPattern(u16 c_name, PF_FILE_NAME_ITER* p_name, u16 c_pat, PF_STR* p_pattern, u32 name_kind);

#ifdef __cplusplus
}
#endif

#endif
