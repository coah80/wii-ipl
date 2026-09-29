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

typedef enum {
    FAT_12 = 0,
    FAT_16 = 1,
    FAT_32 = 2,
    FAT_ERR = -1,
} PF_FAT_TYPE;

typedef struct PF_BPB {
    u16 bytes_per_sector;         // 0x00
    u16 num_reserved_sectors;     // 0x02
    u16 num_root_dir_entries;     // 0x04
    u8 sectors_per_cluster;       // 0x06
    u8 num_FATs;                  // 0x07
    u32 total_sectors;            // 0x08
    u32 sectors_per_FAT;          // 0x0C
    u32 root_dir_cluster;         // 0x10
    u16 fs_info_sector;           // 0x14
    u16 backup_boot_sector;       // 0x16
    u16 ext_flags;                // 0x18
    u8 media;                     // 0x1A
    u8 pad_1B;
    PF_FAT_TYPE fat_type;         // 0x1C
    u8 log2_bytes_per_sector;     // 0x20
    u8 log2_sectors_per_cluster;  // 0x21
    u8 num_active_FATs;           // 0x22
    u8 pad_23;
    u16 num_root_dir_sectors;     // 0x24
    u8 pad_26[2];
    u32 active_FAT_sector;        // 0x28
    u32 first_root_dir_sector;    // 0x2C
    u32 first_data_sector;        // 0x30
    u32 num_clusters;             // 0x34
} PF_BPB;

typedef struct PF_DIR_ENT {
    u16 long_name[261];          // 0x00
    u8 num_entry_LFNs;           // 0x20A
    u8 ordinal;                  // 0x20B
    u8 check_sum;                // 0x20C
    u8 align_pad[1];             // 0x20D
    s8 short_name[13];           // 0x20E
    u8 small_letter_flag;        // 0x21B
    u8 attr;                     // 0x21C
    u8 create_time_ms;           // 0x21D
    u16 create_time;             // 0x21E
    u16 create_date;             // 0x220
    u16 access_date;             // 0x222
    u16 modify_time;             // 0x224
    u16 modify_date;             // 0x226
    u32 file_size;               // 0x228
    struct PF_VOLUME* p_vol;     // 0x22C
    u32 path_len;                // 0x230
    u32 start_cluster;           // 0x234
    u32 entry_sector;            // 0x238
    u16 entry_offset;            // 0x23C
    u16 pad_23E;
} PF_DIR_ENT;

typedef struct PF_SDD {
    u32 stat;               // 0x00
    u32 num_handlers;       // 0x04
    u8 pad_08[0x34];
    PF_DIR_ENT dir_entry;   // 0x3C
} PF_SDD;

typedef struct PF_SDD_HANDLE {
    u32 stat;          // 0x00
    u32 pad_4;
    PF_SDD* p_sdd;     // 0x08
    u8 pad_C[0x24];
} PF_SDD_HANDLE;

typedef struct PF_CUR_DIR {
    u32 stat;              // 0x00
    s32 context_id;        // 0x04
    PF_DIR_ENT directory;  // 0x08
} PF_CUR_DIR;

typedef struct PF_LAST_CLUSTER {
    u32 num_last_cluster;
    u32 max_chain_index;
} PF_LAST_CLUSTER;

typedef struct PF_FAT_LAST_ACCESS {
    u32 chain_index;
    u32 cluster;
} PF_FAT_LAST_ACCESS;

typedef struct PF_CLUSTER_LINK {
    u32* buffer;
    u16 interval;
    u16 interval_offset;
    u32 position;
    u32 max_count;
    u32 save_index;
} PF_CLUSTER_LINK;

typedef struct PF_FAT_HINT {
    u32 chain_index;
    u32 cluster;
    u32 start_cluster;
} PF_FAT_HINT;

typedef struct PF_FFD {
    u32 start_cluster;
    u32 field_04;
    u32* p_start_cluster;
    PF_LAST_CLUSTER last_cluster;
    PF_FAT_LAST_ACCESS last_access_cluster;
    PF_CLUSTER_LINK cluster_link;
    PF_FAT_HINT* p_hint;
    struct PF_VOLUME* p_vol;
} PF_FFD;

typedef struct PF_ENT_ITER PF_ENT_ITER;

typedef struct PF_VOLUME {
    PF_BPB bpb;                    // 0x00
    u32 num_free_clusters;         // 0x38
    u32 last_free_cluster;         // 0x3C
    u8 pad_40[0xD0C];              // 0x40
    PF_SDD_HANDLE dir_handle[5];   // 0xD4C
    u8 pad_DDC[0x7E0];             // 0xDDC
    u32 num_open_files;            // 0x161C
    u32 num_open_dirs;             // 0x1620
    u32 buffer_mode;               // 0x1624
    u16 cache_max_fat;             // 0x1628
    u16 cache_max_data;            // 0x162A
    u8 pad_162C[0x10];
    u32 fat_buffer_size;           // 0x163C
    u32 data_buffer_size;          // 0x1640
    u32 pad_1644;
    s8 label[12];                  // 0x1648
    PF_CUR_DIR current_dir[4];     // 0x1654
    u32 tail_size;                 // 0x1F74
    u8 tail_area[4];               // 0x1F78
    u32* p_tail_buf;               // 0x1F7C
    s32 last_error;                // 0x1F80
    s32 last_driver_error;         // 0x1F84
    u32 file_config;               // 0x1F88
    u16 flags;                     // 0x1F8C
    s8 drv_char;                   // 0x1F8E
    u8 pad_1F8F;
    u16 fsi_flag;                  // 0x1F90
    u8 pad_1F92[2];
    u16 clst_flag;                 // 0x1F94
    u16 clst_interval;             // 0x1F96
    u32* clst_buf;                 // 0x1F98
    u32 clst_count;                // 0x1F9C
    void* p_part;                  // 0x1FA0
    s32 (*p_callback)(s32);        // 0x1FA4
    const u8* format_param;        // 0x1FA8
} PF_VOLUME;

typedef struct PF_CONTEXT {
    u32 stat;          // 0x00
    s32 context_id;    // 0x04
} PF_CONTEXT;

typedef struct PF_CUR_VOLUME {
    u32 stat;          // 0x00
    s32 context_id;    // 0x04
    PF_VOLUME* p_vol;  // 0x08
} PF_CUR_VOLUME;

/* pf_vol_set global; offsets verified against base object */
typedef struct PF_VOLUME_SET {
    PF_CUR_VOLUME current_vol[4];   // 0x00
    s32 num_attached_volumes;       // 0x30
    s32 num_mounted_volumes;        // 0x34
    u32 config;                     // 0x38
    u32 pad_3C;                     // 0x3C
    s32 last_error;                 // 0x40
    s32 last_driver_error;          // 0x44
    PF_CHARCODE codeset;            // 0x48
    u32 setting;                    // 0x60
    u8 pad_64[0x0C];                // 0x64
    PF_CONTEXT context[3];          // 0x70
    PF_VOLUME volumes[26];          // 0x88
} PF_VOLUME_SET;

extern PF_VOLUME_SET pf_vol_set;

/* pf_str.c */
void PFSTR_SetCodeMode(PF_STR* p_str, u32 code_mode);
u32 PFSTR_GetCodeMode(PF_STR* p_str);
s8* PFSTR_GetStrPos(PF_STR* p_str, u32 target);
void PFSTR_MoveStrPos(PF_STR* p_str, s16 num_char);
s32 PFSTR_InitStr(PF_STR* p_str, const s8* s, u32 code_mode);
u32 PFSTR_StrLen(PF_STR* p_str);
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
