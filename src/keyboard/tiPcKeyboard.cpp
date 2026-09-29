#include <new>
#include <cstring>
#include <revolution/mem.h>
#include <nw4r/lyt/Pane.h>
#include <nw4r/lyt/Bounding.h>
#include <nw4r/lyt/TextBox.h>

#include "keyboard/tiPcKeyboard.h"
#include "keyboard/tiUtil.h"
#include "keyboard/tiManager.h"
#include "keyboard/tiPredictLang.h"
#include "keyboard/tiSignWindow.h"
#include "keyboard/tiHwKeyboard.h"
#include "keyboard/tiTextInputBase.h"
#include "keyboard/tiLanguageIndependentData.h"
#include "keyboard/tiGUIManager.h"
#include "keyboard/tiKeyboard.h"
#include "keyboard/tiLayoutGather.h"

namespace textinput {
    namespace keyboard {
        namespace pctype {

            extern const u8 csUSKeyboard[];
            extern const u8 csUKKeyboard[];
            extern const u8 csFRKeyboard[];
            extern const u8 csDEKeyboard[];
            extern const u8 csITKeyboard[];
            extern const u8 csESKeyboard[];
            extern const u8 csNLKeyboard[];
            extern const u8 csCNKeyboard[];
            extern const u8 csJPKeyboard[];

            static const char* scPaneName00 = "P_Gkey_00";
            static const u32 csHangulChoseong = 1;
            static const u32 csHangulJungseong = 2;

            struct InputWCharCommand {
                u16 mWChar;
                u16 mPad;
                u32 mFlags;
                u32 mX;
                u32 mY;
            };
            static const InputWCharCommand csInputWChar0 = {0, 0, 0, 0x10000, 0};
static const struct GridKeyboard { char mPaneName[0x16]; u16 muHiragana; u16 muKatakana; } csGridKeyboard[] = {
    { "P_Gkey_00", 0x0000, 0x0000 },
    { "P_Gkey_01", 0x3042, 0x30a2 },
    { "P_Gkey_02", 0x304b, 0x30ab },
    { "P_Gkey_03", 0x3055, 0x30b5 },
    { "P_Gkey_04", 0x305f, 0x30bf },
    { "P_Gkey_05", 0x306a, 0x30ca },
    { "P_Gkey_06", 0x306f, 0x30cf },
    { "P_Gkey_07", 0x307e, 0x30de },
    { "P_Gkey_08", 0x3084, 0x30e4 },
    { "P_Gkey_09", 0x3089, 0x30e9 },
    { "P_Gkey_10", 0x308f, 0x30ef },
    { "P_Gkey_11", 0x0000, 0x0000 },
    { "P_Gkey_12", 0x3044, 0x30a4 },
    { "P_Gkey_13", 0x304d, 0x30ad },
    { "P_Gkey_14", 0x3057, 0x30b7 },
    { "P_Gkey_15", 0x3061, 0x30c1 },
    { "P_Gkey_16", 0x306b, 0x30cb },
    { "P_Gkey_17", 0x3072, 0x30d2 },
    { "P_Gkey_18", 0x307f, 0x30df },
    { "P_Gkey_19", 0x3086, 0x30e6 },
    { "P_Gkey_20", 0x308a, 0x30ea },
    { "P_Gkey_21", 0x3092, 0x30f2 },
    { "P_Gkey_22", 0x0000, 0x0000 },
    { "P_Gkey_23", 0x3046, 0x30a6 },
    { "P_Gkey_24", 0x304f, 0x30af },
    { "P_Gkey_25", 0x3059, 0x30b9 },
    { "P_Gkey_26", 0x3064, 0x30c4 },
    { "P_Gkey_27", 0x306c, 0x30cc },
    { "P_Gkey_28", 0x3075, 0x30d5 },
    { "P_Gkey_29", 0x3080, 0x30e0 },
    { "P_Gkey_30", 0x3088, 0x30e8 },
    { "P_Gkey_31", 0x308b, 0x30eb },
    { "P_Gkey_32", 0x3093, 0x30f3 },
    { "P_Gkey_33", 0x0000, 0x0000 },
    { "P_Gkey_34", 0x3048, 0x30a8 },
    { "P_Gkey_35", 0x3051, 0x30b1 },
    { "P_Gkey_36", 0x305b, 0x30bb },
    { "P_Gkey_37", 0x3066, 0x30c6 },
    { "P_Gkey_38", 0x306d, 0x30cd },
    { "P_Gkey_39", 0x3078, 0x30d8 },
    { "P_Gkey_40", 0x3081, 0x30e1 },
    { "P_Gkey_41", 0xff01, 0xff01 },
    { "P_Gkey_42", 0x308c, 0x30ec },
    { "P_Gkey_43", 0x3001, 0x3001 },
    { "P_Gkey_44", 0x0000, 0x0000 },
    { "P_Gkey_45", 0x304a, 0x30aa },
    { "P_Gkey_46", 0x3053, 0x30b3 },
    { "P_Gkey_47", 0x305d, 0x30bd },
    { "P_Gkey_48", 0x3068, 0x30c8 },
    { "P_Gkey_49", 0x306e, 0x30ce },
    { "P_Gkey_50", 0x307b, 0x30db },
    { "P_Gkey_51", 0x3082, 0x30e2 },
    { "P_Gkey_52", 0xff1f, 0xff1f },
    { "P_Gkey_53", 0x308d, 0x30ed },
    { "P_Gkey_54", 0x3002, 0x3002 },
    { "P_Gkey_55", 0x30fc, 0x30fc },
};

static const struct PaneNameToControlKey { char mPaneName[0x14]; u32 mControlKey; } csPaneNameToControlKey[] = {
    { "P_key_LF", 0 },
    { "P_key_DELETE", 1 },
    { "P_key_CAPS", 3 },
    { "P_key_SHIFT", 4 },
    { "P_key_SPACE", 2 },
    { "P_Gkey_LF", 0 },
    { "P_Gkey_DELETE", 1 },
    { "P_Gkey_SPACE", 2 },
    { "W_USEU_prdc_lang", 10 },
    { "W_USEU_Chng_sign", 13 },
    { "W_JP_Chng_ABC", 11 },
    { "W_JP_Chng_KANA", 12 },
    { "W_JP_Chng_sign", 13 },
    { "P_Mode_roma_hira", 16 },
    { "P_Mode_roma_kata", 17 },
    { "P_Mode_direct", 15 },
    { "P_hiragana", 18 },
    { "P_katakana", 19 },
    { "P_Gkey_komoji", 22 },
    { "P_Gkey_handaku", 21 },
    { "P_Gkey_dakuten", 20 },
    { "P_Mode_kr_eng", 15 },
    { "P_Mode_kr_han", 16 },
};

typedef struct AsciiVisiblePanes {
    u16 muCount1;
    u16 muCount2;
    const char* mpaPanes[2][24];
} AsciiVisiblePanes;

static const AsciiVisiblePanes csJPNAsciiVisiblePanes = { 13, 24, {
        {
            "N_modeSelect_all",
            "P_Mode_direct",
            "P_Mode_roma_hira",
            "P_Mode_roma_kata",
            "N_KeyChange_JP",
            "W_JP_Chng_ABC",
            "W_JP_Chng_KANA",
            "W_JP_Chng_sign",
            "T_JP_Chng_ABC",
            "T_JP_Chng_KANA",
            "T_JP_Chng_sign",
            "T_key_CAPS",
            "T_key_SHIFT",
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            "P_key_41",
            "T_key_41",
            "P_key_42",
            "T_key_42",
            "P_key_43",
            "T_key_43",
            "N_KeyChange_USEU",
            "P_Gkey_00",
            "P_Gkey_11",
            "P_Gkey_22",
            "P_Gkey_33",
            "P_Gkey_44",
            "T_Gkey_00",
            "T_Gkey_11",
            "T_Gkey_22",
            "T_Gkey_33",
            "T_Gkey_44",
            "W_USEU_prdc_lang",
            "W_USEU_Chng_sign",
            "T_USEU_prdc_lang",
            "T_USEU_Chng_sign",
            "P_SHIFTMark",
            "P_CAPSMark",
            "N_modeSelect_kr",
        },
    } };
static const AsciiVisiblePanes csUSAsciiVisiblePanes = { 17, 20, {
        {
            "N_KeyChange_USEU",
            "P_Gkey_00",
            "P_Gkey_11",
            "P_Gkey_22",
            "P_Gkey_33",
            "P_Gkey_44",
            "T_Gkey_00",
            "T_Gkey_11",
            "T_Gkey_22",
            "T_Gkey_33",
            "T_Gkey_44",
            "W_USEU_prdc_lang",
            "W_USEU_Chng_sign",
            "T_USEU_prdc_lang",
            "T_USEU_Chng_sign",
            "T_key_CAPS",
            "T_key_SHIFT",
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            "P_key_41",
            "T_key_41",
            "P_key_42",
            "T_key_42",
            "P_key_43",
            "T_key_43",
            "N_modeSelect_all",
            "P_Mode_direct",
            "P_Mode_roma_hira",
            "P_Mode_roma_kata",
            "N_KeyChange_JP",
            "W_JP_Chng_ABC",
            "W_JP_Chng_KANA",
            "W_JP_Chng_sign",
            "T_JP_Chng_ABC",
            "T_JP_Chng_KANA",
            "T_JP_Chng_sign",
            "P_SHIFTMark",
            "P_CAPSMark",
            "N_modeSelect_kr",
            NULL,
            NULL,
            NULL,
            NULL,
        },
    } };
static const AsciiVisiblePanes csEngAsciiVisiblePanesUK = { 21, 16, {
        {
            "P_key_42",
            "T_key_42",
            "P_key_43",
            "T_key_43",
            "N_KeyChange_USEU",
            "P_Gkey_00",
            "P_Gkey_11",
            "P_Gkey_22",
            "P_Gkey_33",
            "P_Gkey_44",
            "T_Gkey_00",
            "T_Gkey_11",
            "T_Gkey_22",
            "T_Gkey_33",
            "T_Gkey_44",
            "W_USEU_prdc_lang",
            "W_USEU_Chng_sign",
            "T_USEU_prdc_lang",
            "T_USEU_Chng_sign",
            "T_key_CAPS",
            "T_key_SHIFT",
            NULL,
            NULL,
            NULL,
        },
        {
            "P_key_41",
            "T_key_41",
            "N_modeSelect_all",
            "P_Mode_direct",
            "P_Mode_roma_hira",
            "P_Mode_roma_kata",
            "N_KeyChange_JP",
            "W_JP_Chng_ABC",
            "W_JP_Chng_KANA",
            "W_JP_Chng_sign",
            "T_JP_Chng_ABC",
            "T_JP_Chng_KANA",
            "T_JP_Chng_sign",
            "P_SHIFTMark",
            "P_CAPSMark",
            "N_modeSelect_kr",
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
    } };
static const AsciiVisiblePanes csEngAsciiVisiblePanesSP = { 21, 16, {
        {
            "P_key_42",
            "T_key_42",
            "P_key_43",
            "T_key_43",
            "N_KeyChange_USEU",
            "P_Gkey_00",
            "P_Gkey_11",
            "P_Gkey_22",
            "P_Gkey_33",
            "P_Gkey_44",
            "T_Gkey_00",
            "T_Gkey_11",
            "T_Gkey_22",
            "T_Gkey_33",
            "T_Gkey_44",
            "W_USEU_prdc_lang",
            "W_USEU_Chng_sign",
            "T_USEU_prdc_lang",
            "T_USEU_Chng_sign",
            "P_SHIFTMark",
            "P_CAPSMark",
            NULL,
            NULL,
            NULL,
        },
        {
            "P_key_41",
            "T_key_41",
            "N_modeSelect_all",
            "P_Mode_direct",
            "P_Mode_roma_hira",
            "P_Mode_roma_kata",
            "N_KeyChange_JP",
            "W_JP_Chng_ABC",
            "W_JP_Chng_KANA",
            "W_JP_Chng_sign",
            "T_JP_Chng_ABC",
            "T_JP_Chng_KANA",
            "T_JP_Chng_sign",
            "T_key_CAPS",
            "T_key_SHIFT",
            "N_modeSelect_kr",
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
    } };
static const AsciiVisiblePanes csAsciiVisiblePanes = { 23, 14, {
        {
            "P_key_41",
            "T_key_41",
            "P_key_42",
            "T_key_42",
            "P_key_43",
            "T_key_43",
            "N_KeyChange_USEU",
            "P_Gkey_00",
            "P_Gkey_11",
            "P_Gkey_22",
            "P_Gkey_33",
            "P_Gkey_44",
            "T_Gkey_00",
            "T_Gkey_11",
            "T_Gkey_22",
            "T_Gkey_33",
            "T_Gkey_44",
            "W_USEU_prdc_lang",
            "W_USEU_Chng_sign",
            "T_USEU_prdc_lang",
            "T_USEU_Chng_sign",
            "P_SHIFTMark",
            "P_CAPSMark",
            NULL,
        },
        {
            "N_modeSelect_all",
            "P_Mode_direct",
            "P_Mode_roma_hira",
            "P_Mode_roma_kata",
            "N_KeyChange_JP",
            "W_JP_Chng_ABC",
            "W_JP_Chng_KANA",
            "W_JP_Chng_sign",
            "T_JP_Chng_ABC",
            "T_JP_Chng_KANA",
            "T_JP_Chng_sign",
            "T_key_CAPS",
            "T_key_SHIFT",
            "N_modeSelect_kr",
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
    } };
static const AsciiVisiblePanes csAsciiVisiblePanesNL = { 19, 18, {
        {
            "P_key_43",
            "T_key_43",
            "N_KeyChange_USEU",
            "P_Gkey_00",
            "P_Gkey_11",
            "P_Gkey_22",
            "P_Gkey_33",
            "P_Gkey_44",
            "T_Gkey_00",
            "T_Gkey_11",
            "T_Gkey_22",
            "T_Gkey_33",
            "T_Gkey_44",
            "W_USEU_prdc_lang",
            "W_USEU_Chng_sign",
            "T_USEU_prdc_lang",
            "T_USEU_Chng_sign",
            "T_key_CAPS",
            "T_key_SHIFT",
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            "P_key_41",
            "T_key_41",
            "P_key_42",
            "T_key_42",
            "N_modeSelect_all",
            "P_Mode_direct",
            "P_Mode_roma_hira",
            "P_Mode_roma_kata",
            "N_KeyChange_JP",
            "W_JP_Chng_ABC",
            "W_JP_Chng_KANA",
            "W_JP_Chng_sign",
            "T_JP_Chng_ABC",
            "T_JP_Chng_KANA",
            "T_JP_Chng_sign",
            "P_SHIFTMark",
            "P_CAPSMark",
            "N_modeSelect_kr",
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
    } };
static const AsciiVisiblePanes csCNAsciiVisiblePanes = { 20, 21, {
        {
            "N_KeyChange_USEU",
            "P_Gkey_00",
            "P_Gkey_11",
            "P_Gkey_22",
            "P_Gkey_33",
            "P_Gkey_44",
            "T_Gkey_00",
            "T_Gkey_11",
            "T_Gkey_22",
            "T_Gkey_33",
            "T_Gkey_44",
            "W_USEU_Chng_sign",
            "T_USEU_Chng_sign",
            "T_key_CAPS",
            "T_key_SHIFT",
            "P_key_42",
            "T_key_42",
            "P_key_43",
            "T_key_43",
            "N_modeSelect_kr",
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            "P_key_41",
            "T_key_41",
            "N_modeSelect_all",
            "P_Mode_direct",
            "P_Mode_roma_hira",
            "P_Mode_roma_kata",
            "N_KeyChange_JP",
            "W_JP_Chng_ABC",
            "W_JP_Chng_KANA",
            "W_JP_Chng_sign",
            "T_JP_Chng_ABC",
            "T_JP_Chng_KANA",
            "T_JP_Chng_sign",
            "P_SHIFTMark",
            "P_CAPSMark",
            "W_USEU_prdc_lang",
            "T_USEU_prdc_lang",
            "B_Mode_direct",
            "B_Mode_roma_hira",
            "B_Mode_roma_kata",
            "T_Mode_cn_pinyin",
            NULL,
            NULL,
            NULL,
        },
    } };
static const AsciiVisiblePanes csKRAsciiVisiblePanes_ = { 16, 22, {
        {
            "N_KeyChange_USEU",
            "P_Gkey_00",
            "P_Gkey_11",
            "P_Gkey_22",
            "P_Gkey_33",
            "P_Gkey_44",
            "T_Gkey_00",
            "T_Gkey_11",
            "T_Gkey_22",
            "T_Gkey_33",
            "T_Gkey_44",
            "W_USEU_Chng_sign",
            "T_USEU_Chng_sign",
            "T_key_CAPS",
            "T_key_SHIFT",
            "N_modeSelect_kr",
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            "P_key_41",
            "T_key_41",
            "P_key_42",
            "T_key_42",
            "P_key_43",
            "T_key_43",
            "P_Mode_direct",
            "N_KeyChange_JP",
            "W_JP_Chng_ABC",
            "W_JP_Chng_KANA",
            "W_JP_Chng_sign",
            "T_JP_Chng_ABC",
            "T_JP_Chng_KANA",
            "T_JP_Chng_sign",
            "P_SHIFTMark",
            "P_CAPSMark",
            "W_USEU_prdc_lang",
            "T_USEU_prdc_lang",
            "N_modeSelect_all",
            "B_Mode_direct",
            "B_Mode_roma_hira",
            "B_Mode_roma_kata",
            NULL,
            NULL,
        },
    } };

static const u16 csCharCodeToAblautSP[12][8] = {
    { 0x61, 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0x0, 0x0 },
    { 0x69, 0xec, 0xed, 0xee, 0x0, 0xef, 0x0, 0x0 },
    { 0x75, 0xf9, 0xfa, 0xfb, 0x0, 0xfc, 0x0, 0x0 },
    { 0x65, 0xe8, 0xe9, 0xea, 0x0, 0xeb, 0x0, 0x0 },
    { 0x6f, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0x0, 0x0 },
    { 0x41, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0x0, 0x0 },
    { 0x49, 0xcc, 0xcd, 0xce, 0x0, 0xcf, 0x0, 0x0 },
    { 0x55, 0xd9, 0xda, 0xdb, 0x0, 0xdc, 0x0, 0x0 },
    { 0x45, 0xc8, 0xc9, 0xca, 0x0, 0xcb, 0x0, 0x0 },
    { 0x4f, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0x0, 0x0 },
    { 0x79, 0x0, 0xfd, 0x0, 0x0, 0xff, 0x0, 0x0 },
    { 0x59, 0x0, 0xdd, 0x0, 0x0, 0x178, 0x0, 0x0 },
};
static const u16 csCharCodeToAblautNL[12][8] = {
    { 0x61, 0xe0, 0x0, 0xe2, 0xe3, 0x0, 0xe1, 0xe4 },
    { 0x69, 0xec, 0x0, 0xee, 0x0, 0x0, 0xed, 0xef },
    { 0x75, 0xf9, 0x0, 0xfb, 0x0, 0x0, 0xfa, 0xfc },
    { 0x65, 0xe8, 0x0, 0xea, 0x0, 0x0, 0xe9, 0xeb },
    { 0x6f, 0xf2, 0x0, 0xf4, 0xf5, 0x0, 0xf3, 0xf6 },
    { 0x41, 0xc0, 0x0, 0xc2, 0xc3, 0x0, 0xc1, 0xc4 },
    { 0x49, 0xcc, 0x0, 0xce, 0x0, 0x0, 0xcd, 0xcf },
    { 0x55, 0xd9, 0x0, 0xdb, 0x0, 0x0, 0xda, 0xdc },
    { 0x45, 0xc8, 0x0, 0xca, 0x0, 0x0, 0xc9, 0xcb },
    { 0x4f, 0xd2, 0x0, 0xd4, 0xd5, 0x0, 0xd3, 0xd6 },
    { 0x79, 0x0, 0x0, 0x0, 0x0, 0x0, 0xfd, 0xff },
    { 0x59, 0x0, 0x0, 0x0, 0x0, 0x0, 0xdd, 0x178 },
};
static const u16 csCharCodeToAblautDE[12][8] = {
    { 0x61, 0xe0, 0xe1, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x69, 0xec, 0xed, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x75, 0xf9, 0xfa, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x65, 0xe8, 0xe9, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x6f, 0xf2, 0xf3, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x41, 0xc0, 0xc1, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x49, 0xcc, 0xcd, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x55, 0xd9, 0xda, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x45, 0xc8, 0xc9, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x4f, 0xd2, 0xd3, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x79, 0x0, 0xfd, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x59, 0x0, 0xdd, 0x0, 0x0, 0x0, 0x0, 0x0 },
};
static const u16 csCharCodeToAblautFR[12][8] = {
    { 0x61, 0x0, 0x0, 0xe2, 0x0, 0xe4, 0x0, 0x0 },
    { 0x69, 0x0, 0x0, 0xee, 0x0, 0xef, 0x0, 0x0 },
    { 0x75, 0x0, 0x0, 0xfb, 0x0, 0xfc, 0x0, 0x0 },
    { 0x65, 0x0, 0x0, 0xea, 0x0, 0xeb, 0x0, 0x0 },
    { 0x6f, 0x0, 0x0, 0xf4, 0x0, 0xf6, 0x0, 0x0 },
    { 0x41, 0x0, 0x0, 0xc2, 0x0, 0xc4, 0x0, 0x0 },
    { 0x49, 0x0, 0x0, 0xce, 0x0, 0xcf, 0x0, 0x0 },
    { 0x55, 0x0, 0x0, 0xdb, 0x0, 0xdc, 0x0, 0x0 },
    { 0x45, 0x0, 0x0, 0xca, 0x0, 0xcb, 0x0, 0x0 },
    { 0x4f, 0x0, 0x0, 0xd4, 0x0, 0xd6, 0x0, 0x0 },
    { 0x79, 0x0, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0 },
    { 0x59, 0x0, 0x0, 0x0, 0x0, 0x178, 0x0, 0x0 },
};

typedef struct KeyTblEntry {
    const char* mPaneName;
    u16         mWChars[4];
} KeyTblEntry;

typedef struct LanguageDependency {
    const void* mpKeyTbl;
    const void* mpGridTbl;
    const void* mpCtrlTbl;
    const void* mpNamesTbl;
    const void* mpAblautTbl;
} LanguageDependency;

static const LanguageDependency csLanguageDependencyData[10] = {
    { &csUSKeyboard, &csGridKeyboard, &csPaneNameToControlKey, &csJPNAsciiVisiblePanes, NULL },
    { &csUSKeyboard, &csGridKeyboard, &csPaneNameToControlKey, &csUSAsciiVisiblePanes, NULL },
    { &csUKKeyboard, &csGridKeyboard, &csPaneNameToControlKey, &csEngAsciiVisiblePanesUK, NULL },
    { &csFRKeyboard, &csGridKeyboard, &csPaneNameToControlKey, &csAsciiVisiblePanes, &csCharCodeToAblautFR },
    { &csDEKeyboard, &csGridKeyboard, &csPaneNameToControlKey, &csAsciiVisiblePanes, &csCharCodeToAblautDE },
    { &csITKeyboard, &csGridKeyboard, &csPaneNameToControlKey, &csAsciiVisiblePanes, NULL },
    { &csESKeyboard, &csGridKeyboard, &csPaneNameToControlKey, &csEngAsciiVisiblePanesSP, &csCharCodeToAblautSP },
    { &csNLKeyboard, &csGridKeyboard, &csPaneNameToControlKey, &csAsciiVisiblePanesNL, &csCharCodeToAblautNL },
    { &csCNKeyboard, &csGridKeyboard, &csPaneNameToControlKey, &csCNAsciiVisiblePanes, NULL },
    { &csUSKeyboard, &csGridKeyboard, &csPaneNameToControlKey, &csKRAsciiVisiblePanes_, NULL },
};
static const LanguageDependency csJapanKanaInput = {
    &csJPKeyboard,
    &csGridKeyboard,
    &csPaneNameToControlKey,
    &csJPNAsciiVisiblePanes,
    NULL,
};

static const struct AnimationFile { u32 mAnimationNo; char mFileName[0x40]; } csAninationFile[16] = {
    { 0, "fs_VK_ascii_keytop_a_normal.brlan" },
    { 1, "fs_VK_ascii_keytop_a_Focus-IN.brlan" },
    { 2, "fs_VK_ascii_keytop_a_Focus-OUT.brlan" },
    { 3, "fs_VK_ascii_keytop_a_Roll_over.brlan" },
    { 4, "fs_VK_ascii_keytop_a_Pushed.brlan" },
    { 5, "fs_VK_ascii_keytop_a_toggle-ON.brlan" },
    { 6, "fs_VK_ascii_keytop_a_toggle-OFF.brlan" },
    { 7, "fs_VK_ascii_keytop_a_Target_ON.brlan" },
    { 8, "fs_VK_ascii_keytop_a_toggleON_Focus-IN.brlan" },
    { 9, "fs_VK_ascii_keytop_a_toggleON_Focus-OUT.brlan" },
    { 10, "fs_VK_ascii_keytop_a_normal_toggle-ON.brlan" },
    { 11, "fs_VK_ascii_keytop_a_toggleON_Pushed.brlan" },
    { 12, "fs_VK_ascii_keytop_a_active-ON.brlan" },
    { 13, "fs_VK_ascii_keytop_a_active-OFF.brlan" },
    { 14, "fs_VK_ascii_keytop_a_active_normal.brlan" },
    { 15, "fs_VK_ascii_keytop_a_not_active_normal.brlan" },
};

static const u16 csHangulLowerJamoTbl[26] = {
    0x3141, 0x3160, 0x314a, 0x3147, 0x3137, 0x3139, 0x314e, 0x3157, 0x3151, 0x3153, 0x314f, 0x3163, 0x3161, 0x315c, 0x3150, 0x3154, 0x3142, 0x3131, 0x3134, 0x3145, 0x3155, 0x314d, 0x3148, 0x314c, 0x315b, 0x314b
};

static const u16 csHangulUpperJamoTbl[26] = {
    0x3141, 0x3160, 0x314a, 0x3147, 0x3138, 0x3139, 0x314e, 0x3157, 0x3151, 0x3153, 0x314f, 0x3163, 0x3161, 0x315c, 0x3152, 0x3156, 0x3143, 0x3132, 0x3134, 0x3146, 0x3155, 0x314d, 0x3149, 0x314c, 0x315b, 0x314b
};

static const wchar_t* csLanguageNames[13] = {
    L"", L"", L"Eng", L"Fra", L"Esp", L"EN", L"DE", L"FR", L"ES", L"IT", L"NL", L"CN", L"KR"
};

typedef struct PaneToAnimation {
    u32 muType;
    const char* mpPaneName;
    u32 muAnimationCount;
    const char* mpLinkedPaneName;
    const AnimationFile* mpaAnimations[12];
} PaneToAnimation;

static const PaneToAnimation csPaneToAnimation[129] = {
    { 0, "P_key_00", 5, NULL, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_01", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_02", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_03", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_04", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_05", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_06", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_07", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_08", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_09", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_10", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_11", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_12", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_13", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_15", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_16", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_17", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_18", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_14", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_19", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_20", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_21", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_22", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_23", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_24", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_25", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_26", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_27", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_28", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_29", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_30", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_31", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_32", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_33", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_34", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_35", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_36", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_37", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_38", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_39", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_40", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_41", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_42", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_43", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_44", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_45", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_46", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_47", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_48", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_49", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_DELETE", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_LF", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_key_SPACE", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 1, "P_key_SHIFT", 12, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], &csAninationFile[6], &csAninationFile[7], &csAninationFile[8], &csAninationFile[9], &csAninationFile[10], &csAninationFile[11] } },
    { 1, "P_key_CAPS", 12, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], &csAninationFile[6], &csAninationFile[7], &csAninationFile[8], &csAninationFile[9], &csAninationFile[10], &csAninationFile[11] } },
    { 0, "P_Gkey_00", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_01", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_02", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_03", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_04", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_05", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_06", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_07", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_08", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_09", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_10", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_11", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_12", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_13", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_14", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_15", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_16", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_17", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_18", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_19", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_20", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_21", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_22", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_23", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_24", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_25", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_26", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_27", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_28", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_29", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_30", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_31", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_32", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_33", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_34", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_35", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_36", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_37", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_38", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_39", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_40", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_41", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_42", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_43", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_44", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_45", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_46", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_47", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_48", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_49", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_50", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_51", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_52", 5, scPaneName00, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_53", 5, NULL, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_54", 5, NULL, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_55", 5, NULL, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_DELETE", 5, NULL, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_LF", 5, NULL, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "P_Gkey_SPACE", 5, NULL, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "W_USEU_prdc_lang", 5, NULL, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 0, "W_USEU_Chng_sign", 5, NULL, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 2, "W_JP_Chng_ABC", 7, NULL, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], &csAninationFile[6], &csAninationFile[7], NULL, NULL, NULL, NULL } },
    { 2, "W_JP_Chng_KANA", 7, NULL, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], &csAninationFile[6], &csAninationFile[7], NULL, NULL, NULL, NULL } },
    { 0, "W_JP_Chng_sign", 5, NULL, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL, NULL, NULL, NULL, NULL, NULL } },
    { 2, "P_hiragana", 7, NULL, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], &csAninationFile[6], &csAninationFile[7], NULL, NULL, NULL, NULL } },
    { 2, "P_katakana", 7, NULL, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], &csAninationFile[6], &csAninationFile[7], NULL, NULL, NULL, NULL } },
    { 3, "P_Gkey_dakuten", 11, NULL, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], &csAninationFile[6], &csAninationFile[12], &csAninationFile[13], &csAninationFile[14], &csAninationFile[15], NULL } },
    { 3, "P_Gkey_handaku", 11, NULL, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], &csAninationFile[6], &csAninationFile[12], &csAninationFile[13], &csAninationFile[14], &csAninationFile[15], NULL } },
    { 3, "P_Gkey_komoji", 11, NULL, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], &csAninationFile[6], &csAninationFile[12], &csAninationFile[13], &csAninationFile[14], &csAninationFile[15], NULL } },
    { 2, "P_Mode_roma_hira", 7, "P_Mode_direct", { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], &csAninationFile[6], &csAninationFile[7], NULL, NULL, NULL, NULL } },
    { 2, "P_Mode_roma_kata", 7, "P_Mode_direct", { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], &csAninationFile[6], &csAninationFile[7], NULL, NULL, NULL, NULL } },
    { 2, "P_Mode_direct", 7, NULL, { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], &csAninationFile[6], &csAninationFile[7], NULL, NULL, NULL, NULL } },
    { 2, "P_Mode_kr_eng", 7, "P_Mode_direct", { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], &csAninationFile[6], &csAninationFile[7], NULL, NULL, NULL, NULL } },
    { 2, "P_Mode_kr_han", 7, "P_Mode_direct", { &csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], &csAninationFile[6], &csAninationFile[7], NULL, NULL, NULL, NULL } },
};

            // == Manager accessors (inline uses) ==

            void Base::create(MEMAllocator* allocator) {
                mpAllocator = allocator;
            }

            void Base::init() {
                unk_0x14 = 0;
                mpLanguageDep = &csLanguageDependencyData[getLanguage()];
                mKeyState.mIsABC = 0;
                if (mKeyState.mLanguage == 0 && !mKeyState.mpBase->mbOnlyQwerty) {
                    mKeyState.mFlags = 1;
                } else if ((u32)(mKeyState.mLanguage - 8) <= 1 && mKeyState.mpBase->mbLangKeyActive) {
                    mKeyState.mFlags = 1;
                } else {
                    mKeyState.mFlags = 0;
                }
                mKeyState.mAIUFlags = 0;
                mKeyState.refresh_();
                u32 mode;
                switch (mKeyState.mFlags & 0xF) {
                    case 0: mode = 0; break;
                    case 1: mode = 1; break;
                    case 2: mode = 2; break;
                    default: mode = 0; break;
                }
                sendCommand(0x12, &mode);
            }

            void Base::updateFromReceiver(u32 command, void* data) {
                if (command != 0x1F) {
                    CommandReceiver::ChangePredictMode mode = {0, 0};
                    sendCommand(0x1F, &mode);
                    if (!(command == 0x19 || command == 0x1A || command == 0x1C || command == 0x18 ||
                          command == 0x14 || command == 0x13 || command == 0x23) ||
                        command == 0x24) {
                        if ((mKeyState.mAIUFlags & ~0xF) != 0) {
                            mKeyState.mAIUFlags &= 0xF;
                            mKeyState.refresh_();
                        }
                    }
                    if (command == 0x24) {
                        unk_0x14 = 1;
                    }
                }
            }

            void Base::onKey(u32 key, void* data) {
                wchar_t wc = getWCCode((char*)data);
                if (key == 4) {
                    if ((wc & 0xFFFF) != 0) {
                        inputCharCode(wc);
                    } else {
                        switch (getControlKey((char*)data)) {
                            case 0:
                                sendCommand(7, NULL);
                                sendCommand(0x27, NULL);
                                break;
                            case 1:
                                sendCommand(1, NULL);
                                break;
                            case 2:
                                if (mgr()->getInputForm()->canConvert()) {
                                    sendCommand(0x28, NULL);
                                } else {
                                    sendInputWChar(0x20, false);
                                }
                                break;
                            case 10:
                                changePredictLanguage();
                                break;
                            case 11:
                                setABC(true);
                                break;
                            case 12:
                                setABC(false);
                                break;
                            case 13:
                                goSignInputMode();
                                break;
                            case 14:
                                changeAIUInputMode(IM_04);
                                break;
                            case 15: {
                                u32 mode = 0;
                                sendCommand(0x12, &mode);
                                setTranslateMode((TranslateMode)0);
                                break;
                            }
                            case 16: {
                                u32 mode = csHangulChoseong;
                                sendCommand(0x12, &mode);
                                setTranslateMode((TranslateMode)1);
                                break;
                            }
                            case 17: {
                                u32 mode = csHangulJungseong;
                                sendCommand(0x12, &mode);
                                setTranslateMode((TranslateMode)2);
                                break;
                            }
                            case 18:
                                if ((mKeyState.mAIUFlags & 0xF) != 0) {
                                    mKeyState.mAIUFlags &= ~0xF;
                                    mKeyState.refresh_();
                                }
                                break;
                            case 19:
                                if ((mKeyState.mAIUFlags & 0xF) != 1) {
                                    mKeyState.mAIUFlags &= ~0xF;
                                    mKeyState.mAIUFlags |= 1;
                                    mKeyState.refresh_();
                                }
                                break;
                            case 20:
                                if ((mKeyState.mAIUFlags & 0x20) != 0) {
                                    sendCommand(0x19, NULL);
                                }
                                break;
                            case 21:
                                if ((mKeyState.mAIUFlags & 0x40) != 0) {
                                    sendCommand(0x1A, NULL);
                                }
                                break;
                            case 22:
                                if ((mKeyState.mAIUFlags & 0x80) != 0) {
                                    sendCommand(0x1C, NULL);
                                }
                                break;
                            default:
                                break;
                        }
                    }
                }
            }

            bool Base::isABC() {
                return mKeyState.mIsABC == 0;
            }

            void Base::setABC(bool flag) {
                u32 notABC = (flag == 0);
                if (notABC != mKeyState.mIsABC) {
                    mKeyState.mIsABC = notABC;
                    mKeyState.refresh_();
                }
                sendCommand(0x29, NULL);
            }

            void Base::setTranslateMode(TranslateMode mode) {
                u32 newMode;
                switch (mode) {
                    case TM_00: newMode = 0; break;
                    case TM_01: newMode = 1; break;
                    case TM_02: newMode = 2; break;
                    default:    newMode = 0; break;
                }
                if (newMode != (mKeyState.mFlags & 0xF)) {
                    if (getLanguage() == 9 || getLanguage() == 8) {
                        mgr()->getInputForm()->onCommand((CommandReceiver::INPUT_COMMAND)6, NULL);
                    }
                    if ((mKeyState.mFlags & 0xF) != newMode) {
                        mKeyState.mFlags = (mKeyState.mFlags & ~0xF) | (newMode & 0xF);
                        mKeyState.refresh_();
                    }
                    if (getLanguage() == 8) {
                        if (mgr()->getCandidateBox() != NULL) {
                            mgr()->getCandidateBox()->checkValidation();
                        }
                    }
                    sendCommand(0x12, &mode);
                    mKeyState.mpLanguageDep = &csJapanKanaInput;
                    sendCommand(0x29, NULL);
                }
            }

            Base::TranslateMode Base::getTranslateMode() const {
                switch (mKeyState.mFlags & 0xF) {
                    case 0: return TM_00;
                    case 1: return TM_01;
                    case 2: return TM_02;
                    default: return TM_00;
                }
            }

            bool Base::isShiftOn() const {
                return (mKeyState.mFlags & 0x80) != 0;
            }

            bool Base::isCapsOn() const {
                return (mKeyState.mFlags & 0x40) != 0;
            }

            void Base::onActive() {
                u32 mode;
                switch (mKeyState.mFlags & 0xF) {
                    case 0: mode = 0; break;
                    case 1: mode = 1; break;
                    case 2: mode = 2; break;
                    default: mode = 0; break;
                }
                sendCommand(0x12, &mode);
                sendCommand(0x27, NULL);
                if (mKeyState.mIsABC == 0) {
                    switch (mKeyState.mFlags & 0xF) {
                        case 0: mode = 0; break;
                        case 1: mode = 1; break;
                        case 2: mode = 2; break;
                        default: mode = 0; break;
                    }
                    if (mode == 1 || mode == 2) {
                        u8 flag = (mode == 2) ? 0 : 1;
                        sendCommand(0x13, &flag);
                    }
                } else {
                    switch (mKeyState.mAIUFlags & 0xF) {
                        case 1: mode = 7; break;
                        default: mode = 6; break;
                    }
                    u8 flag = (mode == 7) ? 0 : 1;
                    sendCommand(0x13, &flag);
                }
                updateFixMode();
            }

            void Base::onClose() {
            }

            wchar_t Base::getWCCode(char* paneName) {
                return mKeyState.getWCCode(paneName);
            }

            u32 Base::getControlKey(char* paneName) {
                const LanguageDependency* dep = (const LanguageDependency*)mKeyState.mpLanguageDep;
                const struct PaneNameToControlKey* ctrl = (const struct PaneNameToControlKey*)dep->mpCtrlTbl;
                for (u16 i = 0; i < 0x17; i++) {
                    if (util::strcmp(ctrl[i].mPaneName, paneName)) {
                        return ctrl[i].mControlKey;
                    }
                }
                return 0x1B;
            }

            void Base::changeABCInputMode(InputMode mode) {
                switch (mode) {
                    case IM_00:
                        if ((mKeyState.mFlags & 0xF) == 0) {
                            return;
                        }
                        mKeyState.mFlags &= ~0xF;
                        mKeyState.refresh_();
                        break;
                    case IM_06:
                        if ((mKeyState.mFlags & 0xF) == 1) {
                            return;
                        }
                        mKeyState.mFlags = (mKeyState.mFlags & ~0xF) | 1;
                        mKeyState.refresh_();
                        break;
                    case IM_07:
                        if ((mKeyState.mFlags & 0xF) == 2) {
                            return;
                        }
                        mKeyState.mFlags = (mKeyState.mFlags & ~0xF) | 2;
                        mKeyState.refresh_();
                        break;
                }
            }

            void Base::changeAIUInputMode(InputMode mode) {
                switch (mode) {
                    case IM_06:
                        if ((mKeyState.mAIUFlags & 0xF) == 0) {
                            return;
                        }
                        mKeyState.mAIUFlags &= ~0xF;
                        mKeyState.refresh_();
                        break;
                    case IM_07:
                        if ((mKeyState.mAIUFlags & 0xF) == 1) {
                            return;
                        }
                        mKeyState.mAIUFlags = (mKeyState.mAIUFlags & ~0xF) | 1;
                        mKeyState.refresh_();
                        break;
                }
            }

            void Base::sendInputWChar(wchar_t wc, bool flag) {
                u32 flags = 0;
                unk_0x14 = 0;
                if (mKeyState.mFlags & 0x40) {
                    flags |= 2;
                }
                if (mKeyState.mFlags & 0x80) {
                    flags |= 1;
                }
                InputWCharCommand cmd = csInputWChar0;
                cmd.mWChar = wc;
                cmd.mFlags = flags;
                sendCommand(0, &cmd);
                if ((mKeyState.mFlags & 0x80) != 0 && !LayoutGather::Singleton::getInstance().isHoldingShift()) {
                    if ((mKeyState.mFlags & ~0xF) != 0) {
                        mKeyState.mFlags &= ~0x80;
                        mKeyState.refresh_();
                    }
                }
                if (unk_0x14 == 0) {
                    u32 dakFlags = 0;
                    if (util::KBD_ConvertDakuten(wc) != wc) {
                        dakFlags |= 0x20;
                    }
                    if (util::KBD_ConvertHandaku(wc) != wc) {
                        dakFlags |= 0x40;
                    }
                    if (util::KBD_ConvertSmall(wc) != wc) {
                        dakFlags |= 0x80;
                    }
                    if ((mKeyState.mAIUFlags & ~0xF) != dakFlags) {
                        mKeyState.mAIUFlags = (mKeyState.mAIUFlags & 0xF) | (dakFlags & ~0xF);
                        mKeyState.refresh_();
                    }
                }
            }

            void Base::KeyState::refresh_() {
                if ((mLanguage != 0 && mLanguage != 9 && mLanguage != 8) || mpBase->mbOnlyQwerty != 0) {
                    if ((mFlags & 0xF) != 0) {
                        mFlags &= ~0xF;
                        refresh_();
                    }
                }
                if ((mLanguage == 8 || mLanguage == 9) && (mFlags & 0xF) == 2 && (mFlags & 0xF) != 1) {
                    mFlags = (mFlags & ~0xF) | 1;
                    refresh_();
                }
                if ((mFlags & 0xF) == 0) {
                    mpLanguageDep = &csLanguageDependencyData[mLanguage];
                } else {
                    if (mLanguage == 0) {
                        mpLanguageDep = &csJapanKanaInput;
                    } else {
                        mpLanguageDep = &csLanguageDependencyData[mLanguage];
                    }
                }
                u8 isABC = 0;
                u8 isAIU = 0;
                if (mIsABC == 0) {
                    switch (mFlags & 0xF) {
                        case 0:
                            isABC = 1;
                            mpBase->sendCommand(0x14, &isABC);
                            break;
                        case 1:
                            mpBase->sendCommand(0x14, &isABC);
                            isAIU = 1;
                            mpBase->sendCommand(0x13, &isAIU);
                            break;
                        case 2:
                            mpBase->sendCommand(0x14, &isABC);
                            mpBase->sendCommand(0x13, &isAIU);
                            break;
                        default:
                            break;
                    }
                } else {
                    switch (mAIUFlags & 0xF) {
                        case 0:
                            mpBase->sendCommand(0x14, &isABC);
                            isAIU = 1;
                            mpBase->sendCommand(0x13, &isAIU);
                            break;
                        case 1:
                            mpBase->sendCommand(0x14, &isABC);
                            mpBase->sendCommand(0x13, &isAIU);
                            break;
                        default:
                            break;
                    }
                }
                if (mpBase != NULL) {
                    mpBase->refreshState();
                }
            }

            void Base::KeyState::refreshText(nw4r::lyt::Pane* pane) {
                const u16* keyTbl = *(const u16**)mpLanguageDep;
                const GridKeyboard* gridTbl = *(const GridKeyboard**)((u8*)mpLanguageDep + 4);
                for (u16 i = 0; i < 0x32; i++) {
                    char paneName[0x14];
                    util::replaceChar(paneName, 0x11, *(const char**)((const u8*)keyTbl + i * 0xC), 0, 'T');
                    nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(
                        pane->FindPaneByName(paneName, true));
                    if (textBox != NULL) {
                        wchar_t buf[2];
                        buf[0] = getWCCode(i);
                        buf[1] = 0;
                        if (mLanguage == 9 && (mFlags & 0xF) == 1) {
                            if (mpBase->isCapsOn()) {
                                buf[0] = util::reverseLetterCaseW(buf[0]);
                            }
                            if (buf[0] >= 0x61 && buf[0] <= 0x7A) {
                                buf[0] = csHangulLowerJamoTbl[buf[0] - 0x61];
                            } else if (buf[0] >= 0x41 && buf[0] <= 0x5A) {
                                buf[0] = csHangulUpperJamoTbl[buf[0] - 0x41];
                            }
                        }
                        textBox->SetString(buf, 0);
                    }
                }
                for (u16 i = 0; i < 0x38; i++) {
                    char paneName[0x14];
                    util::replaceChar(paneName, 0x11, gridTbl[i].mPaneName, 0, 'T');
                    nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(
                        pane->FindPaneByName(paneName, true));
                    if (textBox != NULL) {
                        wchar_t buf[2];
                        buf[0] = ((mAIUFlags & 0xF) == 0) ? gridTbl[i].muHiragana : gridTbl[i].muKatakana;
                        buf[1] = 0;
                        textBox->SetString(buf, 0);
                    }
                }
            }

            void Base::refreshState() {
            }

            void Base::KeyState::setABCFlag(u32 flag) {
                if ((mFlags & ~0xF) != flag) {
                    mFlags = (mFlags & 0xF) | (flag & ~0xF);
                    if (mpBase != NULL) {
                        mpBase->refreshState();
                    }
                }
            }

            wchar_t Base::KeyState::getWCCode(u32 keyType) {
                u32 shift = 0;
                if (mFlags & 0x40) {
                    shift |= 1;
                }
                if (mFlags & 0x80) {
                    shift |= 2;
                }
                const u16* keyTbl = *(const u16**)mpLanguageDep;
                wchar_t wc = keyTbl[keyType * 6 + shift + 2];
                if (mIsABC == 0 && (mFlags & 0xF) == 0) {
                    switch (wc) {
                        case 0x3001:
                            wc = 0x2C;
                            break;
                        case 0x3002:
                            wc = 0x2E;
                            break;
                        case 0x30FC:
                            wc = 0x2D;
                            break;
                        case 0x300C:
                            wc = 0x5B;
                            break;
                        case 0x300D:
                            wc = 0x5D;
                            break;
                        default:
                            break;
                    }
                } else if (mpBase->getLanguage() == 8 && (mFlags & 0xF) == 1) {
                    switch (wc) {
                        case 0x5B:
                            wc = 0x300A;
                            break;
                        case 0x5D:
                            wc = 0x300B;
                            break;
                        case 0x2E:
                            wc = 0x3002;
                            break;
                        case 0x27:
                            wc = 0x3001;
                            break;
                        case 0x2C:
                            wc = 0xFF0C;
                            break;
                        case 0x2D:
                            wc = 0xFF0D;
                            break;
                        case 0x5F:
                            wc = 0xFF3F;
                            break;
                        case 0x3A:
                            wc = 0xFF1A;
                            break;
                        case 0x3B:
                            wc = 0xFF1B;
                            break;
                        case 0x21:
                            wc = 0xFF01;
                            break;
                        case 0x3F:
                            wc = 0xFF1F;
                            break;
                        case 0x28:
                            wc = 0xFF08;
                            break;
                        case 0x29:
                            wc = 0xFF09;
                            break;
                        default:
                            break;
                    }
                }
                return wc;
            }

            wchar_t Base::KeyState::getWCCode(char* paneName) {
                wchar_t wc = 0;
                const u16* keyTbl = *(const u16**)mpLanguageDep;
                const GridKeyboard* gridTbl = *(const GridKeyboard**)((u8*)mpLanguageDep + 4);
                for (u16 i = 0; i < 0x32; i++) {
                    const char* name = *(const char**)((const u8*)keyTbl + i * 0xC);
                    if (util::strcmp(name, paneName)) {
                        wc = getWCCode(i);
                    }
                }
                for (u16 i = 0; i < 0x38; i++) {
                    if (util::strcmp(gridTbl[i].mPaneName, paneName)) {
                        wc = ((mAIUFlags & 0xF) == 0) ? gridTbl[i].muHiragana : gridTbl[i].muKatakana;
                    }
                }
                return wc;
            }

            // ============ ~LayoutByNW4R ============
            LayoutByNW4R::~LayoutByNW4R() {
            }

            UIModePanel::~UIModePanel() {
            }

            UIObj::~UIObj() {
            }

            UIModifierButton::~UIModifierButton() {
            }

            EventHandler::~EventHandler() {
            }

            // ============ LayoutByNW4R ============
            void LayoutByNW4R::create(MEMAllocator* allocator) {
                mpAllocator = allocator;
                mpEventHandler = new (MEMAllocFromAllocator(allocator, sizeof(EventHandler))) EventHandler(this);
                nw4rmanager::Layout::createWithEventHandler(allocator, mpEventHandler);
                mpPaneManager->setAllComponentTriggerTarget(false);
                mpPaneManager->setAllBoundingBoxComponentTriggerTarget(true);
                createAnmPane_(allocator);
                mShiftButton.mpPaneComp1 = getPaneManager()->searchPaneComponent("P_key_SHIFT");
                mShiftButton.mpPaneComp2 = getPaneManager()->searchPaneComponent("B_key_SHIFT");
                mShiftButton.mpAnmPane = searchAnmPane("P_key_SHIFT");
                mShiftButton.mpPaneComp2->setOwner(&mShiftButton);
                mCapsButton.mpPaneComp1 = getPaneManager()->searchPaneComponent("P_key_CAPS");
                mCapsButton.mpPaneComp2 = getPaneManager()->searchPaneComponent("B_key_CAPS");
                mCapsButton.mpAnmPane = searchAnmPane("P_key_CAPS");
                mCapsButton.mpPaneComp2->setOwner(&mCapsButton);
                mModePanel.Create(this);
                mShiftButton.mpPaneComp2->setTriggerTarget(true);
                mCapsButton.mpPaneComp2->setTriggerTarget(true);
                for (int i = 0; i < 5; i++) {
                    mModePanel.mpComps2[i]->setTriggerTarget(true);
                }
                init();
                if ((mKeyState.mFlags & 0xFFF) != 0) {
                    mKeyState.mFlags &= 0xF;
                    if (mKeyState.mpBase != NULL) {
                        mKeyState.mpBase->refreshState();
                    }
                }
                changeABCInputMode(IM_00);
            }

            void LayoutByNW4R::createAnmPane_(MEMAllocator* allocator) {
                AnmPane* anmPane;
                for (u32 i = 0; i < sizeof(csPaneToAnimation) / sizeof(csPaneToAnimation[0]); i++) {
                    const PaneToAnimation* pa = &csPaneToAnimation[i];
                    anmPane = NULL;
                    switch (pa->muType) {
                        case 0: {
                            void* buf = MEMAllocFromAllocator(allocator, sizeof(NormalButtonAnmPane));
                            if (buf != NULL) {
                                anmPane = new (buf) NormalButtonAnmPane(getPane(pa->mpPaneName), NULL);
                            }
                            break;
                        }
                        case 1: {
                            void* buf = MEMAllocFromAllocator(allocator, sizeof(ShiftCapsAnmPane));
                            if (buf != NULL) {
                                anmPane = new (buf) ShiftCapsAnmPane(getPane(pa->mpPaneName), NULL);
                            }
                            break;
                        }
                        case 2: {
                            void* buf = MEMAllocFromAllocator(allocator, sizeof(ToggleButtonAnmPane));
                            if (buf != NULL) {
                                anmPane = new (buf) ToggleButtonAnmPane(getPane(pa->mpPaneName), NULL);
                            }
                            break;
                        }
                        case 3: {
                            void* buf = MEMAllocFromAllocator(allocator, sizeof(OnOffButtonAnmPane));
                            if (buf != NULL) {
                                anmPane = new (buf) OnOffButtonAnmPane(getPane(pa->mpPaneName), NULL);
                            }
                            break;
                        }
                    }
                    nw4r::ut::List_Append(&mAnmPanes, anmPane);
                    for (u16 j = 0; j < pa->muAnimationCount; j++) {
                        const AnimationFile* af = pa->mpaAnimations[j];
                        void* resBuf = mpMultiArcResourceAccessor->GetResource(0, af->mFileName, 0);
                        AnimTransformPane* anim = (AnimTransformPane*)getLayout()->CreateAnimTransform(resBuf, mpMultiArcResourceAccessor);
                        if (pa->mpLinkedPaneName == NULL) {
                            anmPane->addAnimation(allocator, af->mAnimationNo, anim, false, true);
                        } else {
                            anmPane->forceAddAnimation(allocator, af->mAnimationNo, anim, pa->mpLinkedPaneName, false, true);
                        }
                    }
                }
            }

            void LayoutByNW4R::calc() {
                nw4rmanager::Layout::calc();
                if (mgr()->getInputForm()->canConvert()) {
                    setVisible("T_key_SPACE", false);
                    setVisible("T_Gkey_SPACE", false);
                    setVisible("P_key_HENKAN", true);
                    setVisible("P_Gkey_HENKAN", true);
                } else {
                    setVisible("T_key_SPACE", true);
                    setVisible("T_Gkey_SPACE", true);
                    setVisible("P_key_HENKAN", false);
                    setVisible("P_Gkey_HENKAN", false);
                }
            }

            void LayoutByNW4R::draw() {
                nw4rmanager::Layout::draw();
            }

            void LayoutByNW4R::inputCharCode(wchar_t wc) {
                sendInputWChar(wc, false);
            }

            void LayoutByNW4R::onPressedCaps() {
                textinput::LayoutGather& gather = textinput::LayoutGather::Singleton::getInstance();
                if (!gather.isHoldingShift()) {
                    if ((mKeyState.mFlags & ~0xF) != 0) {
                        mKeyState.mFlags &= ~0x80;
                        mKeyState.refresh_();
                    }
                    if (mShiftButton.mbFocused) {
                        mShiftButton.mbFocused = 0;
                        mShiftButton.mpAnmPane->onAnmEvent(nw4rmanager::AnmPane::PE_5);
                    }
                }
                gather.changeCapsLock(!gather.isCapsLock());
                mKeyState.mFlags = (mKeyState.mFlags & ~0x40) | ((mKeyState.mFlags ^ 0x40) & 0x40);
                mKeyState.refresh_();
                mCapsButton.mbFocused = (mKeyState.mFlags & 0x40) != 0;
                if (mCapsButton.mbFocused) {
                    mCapsButton.mpAnmPane->onAnmEvent(nw4rmanager::AnmPane::PE_10);
                } else {
                    mCapsButton.mpAnmPane->onAnmEvent(nw4rmanager::AnmPane::PE_11);
                }
                mpEventObserver->onSE(sound::SE_KETAI_MODE_SWITCHING);
            }

            void LayoutByNW4R::onPressedShift(bool flag) {
                mKeyState.setABCFlag(mKeyState.mFlags | 0x80);
                mShiftButton.mbFocused = true;
                mShiftButton.mpAnmPane->onAnmEvent(nw4rmanager::AnmPane::PE_10);
                if (flag) {
                    mpEventObserver->onSE(sound::SE_KETAI_MODE_SWITCHING);
                }
            }

            void LayoutByNW4R::onReleasedShift() {
                mKeyState.setABCFlag(mKeyState.mFlags & ~0x80);
                if (mShiftButton.mbFocused) {
                    mShiftButton.mbFocused = 0;
                    mShiftButton.mpAnmPane->onAnmEvent(nw4rmanager::AnmPane::PE_5);
                }
            }

            void LayoutByNW4R::onClose() {
                this->initPaneLastDrawReceived();
                cancelStateFocusIn();
            }

            void LayoutByNW4R::throwReleaseForAll() {
                AnmPane* it = (AnmPane*)nw4r::ut::List_GetNext(&mAnmPanes, NULL);
                for (; it != NULL; it = (AnmPane*)nw4r::ut::List_GetNext(&mAnmPanes, it)) {
                    if (it->getKeyType() == 0) {
                        it->onAnmEvent((nw4rmanager::AnmPane::AnmPaneEvent)2);
                    }
                }
            }

            void LayoutByNW4R::cancelStateFocusIn() {
                AnmPane* it = (AnmPane*)nw4r::ut::List_GetNext(&mAnmPanes, NULL);
                for (; it != NULL; it = (AnmPane*)nw4r::ut::List_GetNext(&mAnmPanes, it)) {
                    switch (it->getKeyType()) {
                        case 0:
                            switch (it->getState()) {
                                case 1:
                                case 3:
                                case 4:
                                    it->changeAnimation(2);
                                    break;
                                case 0x10:
                                    it->changeAnimation(0);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case 1:
                            switch (it->getState()) {
                                case 1:
                                case 3:
                                case 0xB:
                                    it->changeAnimation(2);
                                    break;
                                case 4:
                                case 5:
                                case 8:
                                    it->changeAnimation(9);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case 2:
                            switch (it->getState()) {
                                case 1:
                                case 3:
                                    it->changeAnimation(2);
                                    break;
                                case 4:
                                    it->changeAnimation(5);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case 3:
                            switch (it->getState()) {
                                case 1:
                                case 3:
                                case 4:
                                    it->changeAnimation(2);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        default:
                            break;
                    }
                }
            }

            void LayoutByNW4R::goSignInputMode() {
                mpSignWindow->open(this, 0);
                throwReleaseForAll();
            }

            void LayoutByNW4R::changePredictLanguage() {
                throwReleaseForAll();
                CommandReceiver::ChangePredictMode mode = {0, 0};
                sendCommand(0x1F, &mode);
                mpPredictLanguageDialog->open((inputform::Base::PredictMode)mode.muLanguage, this);
            }

            void LayoutByNW4R::updatePredictLanguage(CommandReceiver::ChangePredictMode* mode) {
                if (getLanguage() != 0) {
                    if (mode->mbPredictOn == 0) {
                        setVisible("P_prdc_ON", false);
                        setVisible("P_prdc_OFF", true);
                    } else {
                        setVisible("P_prdc_ON", true);
                        setVisible("P_prdc_OFF", false);
                    }
                    ((nw4r::lyt::TextBox*)getPane("T_USEU_prdc_lang"))->SetString(csLanguageNames[mode->muLanguage], 0);
                }
            }

            void LayoutByNW4R::sendInputWChar(wchar_t wc, bool flag) {
                nw4r::lyt::Pane* pane = NULL;
                bool gotPane = false;
                if (mKeyState.mFlags & 0x80) {
                    pane = mAnmPaneFifo.getLast();
                    gotPane = true;
                }
                Base::sendInputWChar(wc, flag);
                if (gotPane && pane != NULL) {
                    setPaneLastDrawReceived(pane);
                }
                updateDakuten();
            }

            void LayoutByNW4R::updateDakuten() {
                if ((mKeyState.mAIUFlags & 0x20) != 0) {
                    this->searchAnmPane("P_Gkey_dakuten")->changeAnimation(7);
                } else {
                    this->searchAnmPane("P_Gkey_dakuten")->changeAnimation(8);
                }
                if ((mKeyState.mAIUFlags & 0x40) != 0) {
                    this->searchAnmPane("P_Gkey_handaku")->changeAnimation(7);
                } else {
                    this->searchAnmPane("P_Gkey_handaku")->changeAnimation(8);
                }
                if ((mKeyState.mAIUFlags & 0x80) != 0) {
                    this->searchAnmPane("P_Gkey_komoji")->changeAnimation(7);
                } else {
                    this->searchAnmPane("P_Gkey_komoji")->changeAnimation(8);
                }
            }

            void LayoutByNW4R::setLineFeedButton(bool flag) {
                mbLineFeed = flag;
                setVisible("P_key_LF", flag);
                setVisible("P_Gkey_LF", mbLineFeed);
            }

            void LayoutByNW4R::setPredictLanguageButton(bool flag) {
                setVisible("W_USEU_prdc_lang", flag);
            }

            void LayoutByNW4R::setSignWindowButton(bool flag) {
                if (flag == 0) {
                    setVisible("W_USEU_Chng_sign", flag);
                    setVisible("W_JP_Chng_sign", flag);
                } else {
                    setVisible("W_USEU_Chng_sign", false);
                    setVisible("W_JP_Chng_sign", false);
                    if (getLanguage() == 0) {
                        setVisible("W_JP_Chng_sign", true);
                    } else {
                        setVisible("W_USEU_Chng_sign", true);
                    }
                }
            }

            void LayoutByNW4R::onlyQwerty(bool flag) {
                mbOnlyQwerty = flag;
                if (getLanguage() == 0) {
                    if (flag) {
                        setABC(true);
                        if ((mKeyState.mFlags & ~0xF) != 0) {
                            mKeyState.mFlags &= 0xF;
                            if (mKeyState.mpBase != NULL) {
                                mKeyState.mpBase->refreshState();
                            }
                        }
                        changeABCInputMode(IM_00);
                    } else {
                        setABC(false);
                        changeAIUInputMode(IM_06);
                    }
                }
                if (getLanguage() == 0) {
                    initLayout();
                    u32 inv = (flag == 0);
                    setVisible("W_JP_Chng_ABC", inv);
                    setVisible("W_JP_Chng_KANA", inv);
                    setVisible("P_Mode_roma_hira", inv);
                    setVisible("P_Mode_roma_kata", inv);
                    setVisible("P_Mode_direct", inv);
                    setVisible("P_romajiBox", inv);
                }
                if (getLanguage() == 9 || getLanguage() == 8) {
                    if (mgr()->getCandidateBox()->isActive()) {
                        setLangKeyActive(!flag);
                    } else {
                        setLangKeyActive(false);
                    }
                }
            }

            void LayoutByNW4R::setLangKeyActive(bool flag) {
                mbLangKeyActive = flag;
                if (getLanguage() == 9 || getLanguage() == 8) {
                    if (!flag) {
                        if ((mKeyState.mFlags & ~0xF) != 0) {
                            mKeyState.mFlags &= 0xF;
                            if (mKeyState.mpBase != NULL) {
                                mKeyState.mpBase->refreshState();
                            }
                        }
                        changeABCInputMode(IM_00);
                    }
                }
                if (getLanguage() == 9 || getLanguage() == 8) {
                    initLayout();
                    setVisible("P_Mode_kr_eng", flag);
                    setVisible("P_Mode_kr_han", flag);
                    setVisible("P_hangulBox", flag);
                    if (getLanguage() == 8) {
                        setVisible("P_key_42", flag);
                        setVisible("P_key_43", flag);
                    }
                }
            }

            void LayoutByNW4R::setInputModeJP(bool abc, u32 abcMode, u32 aiuMode) {
                setABC(abc);
                if ((mKeyState.mFlags & 0xF) != abcMode) {
                    mKeyState.mFlags = (mKeyState.mFlags & ~0xF) | (abcMode & 0xF);
                    mKeyState.refresh_();
                }
                if ((mKeyState.mAIUFlags & 0xF) != aiuMode) {
                    mKeyState.mAIUFlags = (mKeyState.mAIUFlags & ~0xF) | (aiuMode & 0xF);
                    mKeyState.refresh_();
                }
                switch (abcMode) {
                    case 0:
                        mKeyState.mpLanguageDep = &csLanguageDependencyData[getLanguage()];
                        break;
                    case 1:
                        mKeyState.mpLanguageDep = &csJapanKanaInput;
                        break;
                    case 2:
                        mKeyState.mpLanguageDep = &csJapanKanaInput;
                        break;
                }
                initLayout();
                sendCommand(0x29, NULL);
            }

            void LayoutByNW4R::setInputModeCK(u32 mode) {
                setInputModeJP(true, mode, 0);
            }

            void LayoutByNW4R::setTranslateMode(TranslateMode mode) {
                u32 prev = mKeyState.mFlags & 0xF;
                Base::setTranslateMode(mode);
                if ((mKeyState.mFlags & 0xF) != prev) {
                    mpEventObserver->onSE(sound::SE_KETAI_MODE_SWITCHING);
                    switch (prev) {
                        case 0:
                            searchAnmPane("P_Mode_direct")->changeAnimation(6);
                            searchAnmPane("P_Mode_kr_eng")->changeAnimation(6);
                            break;
                        case 1:
                            searchAnmPane("P_Mode_roma_hira")->changeAnimation(6);
                            searchAnmPane("P_Mode_kr_han")->changeAnimation(6);
                            break;
                        case 2:
                            searchAnmPane("P_Mode_roma_kata")->changeAnimation(6);
                            break;
                    }
                    switch (mode) {
                        case 0:
                            searchAnmPane("P_Mode_direct")->onAnmEvent(nw4rmanager::AnmPane::PE_0);
                            searchAnmPane("P_Mode_kr_eng")->onAnmEvent(nw4rmanager::AnmPane::PE_0);
                            break;
                        case 1:
                            searchAnmPane("P_Mode_roma_hira")->onAnmEvent(nw4rmanager::AnmPane::PE_0);
                            searchAnmPane("P_Mode_kr_han")->onAnmEvent(nw4rmanager::AnmPane::PE_0);
                            break;
                        case 2:
                            searchAnmPane("P_Mode_roma_kata")->onAnmEvent(nw4rmanager::AnmPane::PE_0);
                            break;
                    }
                }
            }

            void LayoutByNW4R::setSignWindow(signwindow::LayoutByNW4R* window) {
                mpSignWindow = window;
            }

            void LayoutByNW4R::setPredictLanguageDialog(predictlang::LayoutByNW4R* dialog) {
                mpPredictLanguageDialog = dialog;
            }

            void LayoutByNW4R::onEvent(UIObj* uiObj, u32 event, void* data) {
                if (event == 0) {
                    mpEventObserver->onSE((sound::SE)(u32)data);
                }
            }

            static const nw4r::math::VEC3 csTranslatePanePos8(-219.0f, -130.0f, 0.0f);
            static const nw4r::math::VEC3 csTranslatePanePos9(-209.0f, -90.0f, 0.0f);

            void LayoutByNW4R::init() {
                unk_0x14 = 0;
                mpLanguageDep = &csLanguageDependencyData[getLanguage()];
                mKeyState.mIsABC = 0;
                if (mKeyState.mLanguage == 0 && !((LayoutByNW4R*)mKeyState.mpBase)->mbOnlyQwerty) {
                    mKeyState.mFlags = 1;
                } else if ((u32)(mKeyState.mLanguage - 8) <= 1 && ((LayoutByNW4R*)mKeyState.mpBase)->mbLangKeyActive) {
                    mKeyState.mFlags = 1;
                } else {
                    mKeyState.mFlags = 0;
                }
                mKeyState.mAIUFlags = 0;
                mKeyState.refresh_();
                u32 mode;
                switch (mKeyState.mFlags & 0xF) {
                    case 0: mode = 0; break;
                    case 1: mode = 1; break;
                    case 2: mode = 2; break;
                    default: mode = 0; break;
                }
                sendCommand(0x12, &mode);
                setLineFeedButton(true);
                setPredictLanguageButton(true);
                setSignWindowButton(true);
                if (meLanguage == 8) {
                    mModePanel.mExtraPanes[0]->GetMaterial()->SetTexture(0, mModePanel.mTexObjs[0]);
                    mModePanel.mExtraPanes[1]->GetMaterial()->SetTexture(0, mModePanel.mTexObjs[1]);
                    mModePanel.mExtraPanes[2]->SetTranslate(csTranslatePanePos8);
                } else if (meLanguage == 9) {
                    mModePanel.mExtraPanes[0]->GetMaterial()->SetTexture(0, mModePanel.mTexObjs[2]);
                    mModePanel.mExtraPanes[1]->GetMaterial()->SetTexture(0, mModePanel.mTexObjs[3]);
                    mModePanel.mExtraPanes[2]->SetTranslate(csTranslatePanePos9);
                }
                searchAnmPane("P_key_SHIFT")->changeAnimation(0);
                searchAnmPane("P_key_CAPS")->changeAnimation(0);
                const AsciiVisiblePanes* nt = (const AsciiVisiblePanes*)((const LanguageDependency*)mpLanguageDep)->mpNamesTbl;
                for (u16 i = 0; i < nt->muCount1; i++) {
                    setVisible(nt->mpaPanes[0][i], true);
                }
                for (u16 i = 0; i < nt->muCount2; i++) {
                    setVisible(nt->mpaPanes[1][i], false);
                }
                if (getLanguage() == 0) {
                    setString("T_JP_Chng_sign", langindependent::cLanguageIndependentString[langindependent::LANG_STRID_SIGN_WINDOW][getLanguage()]);
                } else {
                    setString("T_USEU_Chng_sign", langindependent::cLanguageIndependentString[langindependent::LANG_STRID_SIGN_WINDOW][getLanguage()]);
                }
                setString("T_key_SPACE", langindependent::cLanguageIndependentString[langindependent::LANG_STRID_SPACE][getLanguage()]);
                onlyQwerty(false);
                setLangKeyActive(true);
                CommandReceiver::ChangePredictMode predMode = {0, 0};
                sendCommand(0x1F, &predMode);
                updatePredictLanguage(&predMode);
                mpLayout->Animate(0);
                mpLayout->CalculateMtx(mDrawInfo);
                setVisible("T_key_SPACE", true);
                setVisible("T_Gkey_SPACE", true);
                setVisible("P_key_HENKAN", false);
                setVisible("P_Gkey_HENKAN", false);
            }

            void LayoutByNW4R::initLayout() {
                if (getLanguage() == 0) {
                    if (isABC()) {
                        searchAnmPane("W_JP_Chng_ABC")->changeAnimation(5);
                        searchAnmPane("W_JP_Chng_KANA")->changeAnimation(0);
                    } else {
                        searchAnmPane("W_JP_Chng_ABC")->changeAnimation(0);
                        searchAnmPane("W_JP_Chng_KANA")->changeAnimation(5);
                    }
                    if ((mKeyState.mAIUFlags & 0xF) == 0) {
                        searchAnmPane("P_hiragana")->changeAnimation(5);
                        searchAnmPane("P_katakana")->changeAnimation(0);
                    } else {
                        searchAnmPane("P_hiragana")->changeAnimation(0);
                        searchAnmPane("P_katakana")->changeAnimation(5);
                    }
                    if (mKeyState.mAIUFlags & 0x20) {
                        searchAnmPane("P_Gkey_dakuten")->changeAnimation(0xE);
                    } else {
                        searchAnmPane("P_Gkey_dakuten")->changeAnimation(0xF);
                    }
                    if (mKeyState.mAIUFlags & 0x40) {
                        searchAnmPane("P_Gkey_handaku")->changeAnimation(0xE);
                    } else {
                        searchAnmPane("P_Gkey_handaku")->changeAnimation(0xF);
                    }
                    if (mKeyState.mAIUFlags & 0x80) {
                        searchAnmPane("P_Gkey_komoji")->changeAnimation(0xE);
                    } else {
                        searchAnmPane("P_Gkey_komoji")->changeAnimation(0xF);
                    }
                    switch (mKeyState.mFlags & 0xF) {
                        case 0:
                            searchAnmPane("P_Mode_roma_hira")->changeAnimation(0);
                            searchAnmPane("P_Mode_roma_kata")->changeAnimation(0);
                            searchAnmPane("P_Mode_direct")->changeAnimation(5);
                            break;
                        case 1:
                            searchAnmPane("P_Mode_roma_hira")->changeAnimation(5);
                            searchAnmPane("P_Mode_roma_kata")->changeAnimation(0);
                            searchAnmPane("P_Mode_direct")->changeAnimation(0);
                            break;
                        case 2:
                            searchAnmPane("P_Mode_roma_hira")->changeAnimation(0);
                            searchAnmPane("P_Mode_roma_kata")->changeAnimation(5);
                            searchAnmPane("P_Mode_direct")->changeAnimation(0);
                            break;
                    }
                }
                if (getLanguage() == 9 || getLanguage() == 8) {
                    if ((mKeyState.mFlags & 0xF) == 0) {
                        searchAnmPane("P_Mode_kr_eng")->changeAnimation(5);
                        searchAnmPane("P_Mode_kr_han")->changeAnimation(0);
                    } else {
                        searchAnmPane("P_Mode_kr_eng")->changeAnimation(0);
                        searchAnmPane("P_Mode_kr_han")->changeAnimation(5);
                    }
                }
                mpLayout->Animate(0);
                mpLayout->CalculateMtx(mDrawInfo);
            }

            void LayoutByNW4R::onKey(u32 event, void* paneName) {
                getWCCode((char*)paneName);
                if (event == 4) {
                    if ((u16)getWCCode((char*)paneName) == 0) {
                        switch (getControlKey((char*)paneName)) {
                        case 3: {
                            textinput::LayoutGather& gather = textinput::LayoutGather::Singleton::getInstance();
                            if (!gather.isHoldingShift()) {
                                if ((mKeyState.mFlags & ~0xF) != 0) {
                                    mKeyState.mFlags &= ~0x80;
                                    mKeyState.refresh_();
                                }
                                if (mShiftButton.mbFocused) {
                                    mShiftButton.mbFocused = 0;
                                    mShiftButton.mpAnmPane->onAnmEvent(nw4rmanager::AnmPane::PE_5);
                                }
                            }
                            gather.changeCapsLock(!gather.isCapsLock());
                            mKeyState.mFlags = (mKeyState.mFlags & ~0x40) | ((mKeyState.mFlags ^ 0x40) & 0x40);
                            mKeyState.refresh_();
                            mCapsButton.mbFocused = (mKeyState.mFlags & 0x40) != 0;
                            if (mCapsButton.mbFocused) {
                                mCapsButton.mpAnmPane->onAnmEvent(nw4rmanager::AnmPane::PE_10);
                            } else {
                                mCapsButton.mpAnmPane->onAnmEvent(nw4rmanager::AnmPane::PE_11);
                            }
                            mpEventObserver->onSE(sound::SE_KETAI_MODE_SWITCHING);
                            break;
                        }
                        case 4: {
                            LayoutGather& gather = LayoutGather::Singleton::getInstance();
                            if ((mKeyState.mFlags & ~0xF) != 0) {
                                mKeyState.mFlags &= ~0x40;
                                mKeyState.refresh_();
                            }
                            if (mCapsButton.mbFocused) {
                                mCapsButton.mbFocused = 0;
                                mCapsButton.mpAnmPane->onAnmEvent(nw4rmanager::AnmPane::PE_5);
                            }
                            if (!gather.isHoldingShift()) {
                                mKeyState.mFlags = (mKeyState.mFlags & ~0x80) | ((mKeyState.mFlags ^ 0x80) & 0x80);
                                mKeyState.refresh_();
                            }
                            mShiftButton.mbFocused = (mKeyState.mFlags & 0x80) ? 1 : 0;
                            if (mShiftButton.mbFocused) {
                                mShiftButton.mpAnmPane->onAnmEvent(nw4rmanager::AnmPane::PE_10);
                            } else {
                                mShiftButton.mpAnmPane->onAnmEvent(nw4rmanager::AnmPane::PE_11);
                            }
                            mpEventObserver->onSE(sound::SE_KETAI_MODE_SWITCHING);
                            break;
                        }
                        case 0: {
                            mpEventObserver->onSE(sound::SE_CHAR_DECIDE);
                            break;
                        }
                        case 11: {
                            if (!isABC()) {
                                mpEventObserver->onSE(sound::SE_KETAI_MODE_SWITCHING);
                                searchAnmPane("W_JP_Chng_KANA")->changeAnimation(6);
                            }
                            break;
                        }
                        case 12: {
                            if (isABC()) {
                                mpEventObserver->onSE(sound::SE_KETAI_MODE_SWITCHING);
                                searchAnmPane("W_JP_Chng_ABC")->changeAnimation(6);
                            }
                            break;
                        }
                        case 18: {
                            if ((mKeyState.mAIUFlags & 0xF) == 1) {
                                mpEventObserver->onSE(sound::SE_KETAI_MODE_SWITCHING);
                                searchAnmPane("P_katakana")->changeAnimation(6);
                            }
                            break;
                        }
                        case 19: {
                            if ((mKeyState.mAIUFlags & 0xF) == 0) {
                                mpEventObserver->onSE(sound::SE_KETAI_MODE_SWITCHING);
                                searchAnmPane("P_hiragana")->changeAnimation(6);
                            }
                            break;
                        }
                        case 15: {
                            if ((mKeyState.mFlags & 0xF) == 2) {
                                searchAnmPane("P_Mode_roma_kata")->changeAnimation(6);
                            }
                            if ((mKeyState.mFlags & 0xF) == 1) {
                                searchAnmPane("P_Mode_roma_hira")->changeAnimation(6);
                                searchAnmPane("P_Mode_kr_han")->changeAnimation(6);
                            }
                            break;
                        }
                        case 16: {
                            if ((mKeyState.mFlags & 0xF) == 0) {
                                searchAnmPane("P_Mode_direct")->changeAnimation(6);
                                searchAnmPane("P_Mode_kr_eng")->changeAnimation(6);
                            }
                            if ((mKeyState.mFlags & 0xF) == 2) {
                                searchAnmPane("P_Mode_roma_kata")->changeAnimation(6);
                            }
                            break;
                        }
                        case 17: {
                            if ((mKeyState.mFlags & 0xF) == 0) {
                                searchAnmPane("P_Mode_direct")->changeAnimation(6);
                            }
                            if ((mKeyState.mFlags & 0xF) == 1) {
                                searchAnmPane("P_Mode_roma_hira")->changeAnimation(6);
                            }
                            break;
                        }
                        default: {
                            break;
                        }
                        }
                    }
                }
                Base::onKey(event, paneName);
            }

            void LayoutByNW4R::setLanguage(Language language) {
                meLanguage = language;
                mKeyState.mLanguage = language;
                mKeyState.refresh_();
                this->init();
            }

            void LayoutByNW4R::onActive() {
                Base::onActive();
                nw4rmanager::Layout::init();
                if (mKeyState.mAIUFlags & 0x20) {
                    searchAnmPane("P_Gkey_dakuten")->changeAnimation(0xe);
                } else {
                    searchAnmPane("P_Gkey_dakuten")->changeAnimation(0xf);
                }
                if (mKeyState.mAIUFlags & 0x40) {
                    searchAnmPane("P_Gkey_handaku")->changeAnimation(0xe);
                } else {
                    searchAnmPane("P_Gkey_handaku")->changeAnimation(0xf);
                }
                if (mKeyState.mAIUFlags & 0x80) {
                    searchAnmPane("P_Gkey_komoji")->changeAnimation(0xe);
                } else {
                    searchAnmPane("P_Gkey_komoji")->changeAnimation(0xf);
                }
            }

            void LayoutByNW4R::updateFromReceiver(u32 command, void* data) {
                Base::updateFromReceiver(command, data);
                updateDakuten();
                switch (command) {
                    case 0x1D:
                        updatePredictLanguage((CommandReceiver::ChangePredictMode*)data);
                        break;
                }
            }

            void LayoutByNW4R::setABC(bool flag) {
                changeAnimationAllToNormal();
                if (flag != isABC()) {
                    if (flag) {
                        searchAnmPane("W_JP_Chng_ABC")->changeAnimation(4);
                        searchAnmPane("W_JP_Chng_KANA")->changeAnimation(6);
                    } else {
                        searchAnmPane("W_JP_Chng_ABC")->changeAnimation(6);
                        searchAnmPane("W_JP_Chng_KANA")->changeAnimation(4);
                    }
                }
                u32 notABC = (flag == 0);
                if (notABC != mKeyState.mIsABC) {
                    mKeyState.mIsABC = notABC;
                    mKeyState.refresh_();
                }
                sendCommand(0x29, NULL);
            }

            void LayoutByNW4R::refreshState() {
                bool bVisible = false;
                if (isABC()) {
                    if (isVisible("N_VK_grid", &bVisible)) {
                        bVisible = (bVisible != 0);
                    } else {
                        bVisible = false;
                    }
                    setVisible("N_VK_grid", false);
                    setVisible("N_VK_grd_Bnd_ALL", false);
                    setVisible("N_VK_ascii", true);
                    setVisible("N_VK_asc_Bnd_ALL", true);
                } else {
                    if (isVisible("N_VK_grid", &bVisible)) {
                        bVisible = (bVisible != 1);
                    } else {
                        bVisible = false;
                    }
                    setVisible("N_VK_grid", true);
                    setVisible("N_VK_grd_Bnd_ALL", true);
                    setVisible("N_VK_ascii", false);
                    setVisible("N_VK_asc_Bnd_ALL", false);
                }
                mKeyState.refreshText(mpLayout->GetRootPane());
                if (getLanguage() == 0) {
                    if ((mKeyState.mAIUFlags & 0xF) == 0) {
                        ((nw4r::lyt::TextBox*)getPane("T_JP_Chng_KANA"))->SetString(L"あいう", 0);
                    } else if ((mKeyState.mAIUFlags & 0xF) == 1) {
                        ((nw4r::lyt::TextBox*)getPane("T_JP_Chng_KANA"))->SetString(L"アイウ", 0);
                    }
                }
                if (!isShiftOn()) {
                    if (mShiftButton.mbFocused) {
                        mShiftButton.mbFocused = 0;
                        mShiftButton.mpAnmPane->onAnmEvent(nw4rmanager::AnmPane::PE_5);
                    }
                }
                if (!isCapsOn()) {
                    if (mCapsButton.mbFocused) {
                        mCapsButton.mbFocused = 0;
                        mCapsButton.mpAnmPane->onAnmEvent(nw4rmanager::AnmPane::PE_5);
                    }
                    textinput::LayoutGather& gather = textinput::LayoutGather::Singleton::getInstance();
                    gather.changeCapsLock(0);
                }
                if (bVisible) {
                    initPaneLastDrawReceived();
                }
            }

            bool LayoutByNW4R::updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data) {
                bool ret = nw4rmanager::Layout::updateInput(chan, x, y, trig, hold, release, data);
                textinput::LayoutGather& gather = textinput::LayoutGather::Singleton::getInstance();
                u32 wasPressed = (gather.isHWPressedShift() || gather.isPressedShiftB()) ? 1 : 0;
                if (trig & 0x400) {
                    gather.setPressedShiftB(1);
                    input::HKBManager::getInstance().SetForceModifierState(2, 2);
                    if (wasPressed == 0) {
                        onPressedShift(isABC());
                    }
                } else {
                    gather.clearPressedShift();
                    input::HKBManager::getInstance().SetForceModifierState(0, 0);
                    if (wasPressed != 0 && !gather.isHWPressedShift() && !gather.isPressedShiftB()) {
                        onReleasedShift();
                    }
                }
                return ret;
            }

            bool LayoutByNW4R::updateInput(input::HKBManager& hkbManager) {
                input::HKBManager::KeySet keySet = hkbManager.GetTriggeredKeySet();
                while (keySet.IsValid()) {
                    nw4rmanager::AnmPane* anmPane = NULL;
                    u8 key = keySet.GetKey();
                    wchar_t wc = keySet.GetWChar();
                    switch (key) {
                        case 0x28:
                        case 0x58:
                            if (!(hkbManager.GetModifierState() & 0x4)) {
                                anmPane = searchAnmPane("P_key_LF");
                            }
                            break;
                        case 0x2C:
                            break;
                        default: {
                            wc = inputform::DeadKeyStream::ToIndependentClass(wc);
                            wc = ((const Manager*)mgr())->getHWKeyboard()->convertWCCode(wc);
                            if (((const Manager*)mgr())->getToolBar()->isQwerty() != 0 &&
                                ((const Manager*)mgr())->getPCKeyboard()->getTranslateMode() != 0 &&
                                ((const Manager*)mgr())->getLanguage() == 9) {
                                if (isCapsOn()) {
                                    wc = util::reverseLetterCaseW(wc);
                                }
                                if (wc >= 'a' && wc <= 'z') {
                                    wc = csHangulUpperJamoTbl[wc - 'a'];
                                } else if (wc >= 'A' && wc <= 'Z') {
                                    wc = csHangulLowerJamoTbl[wc - 'A'];
                                }
                            }
                            anmPane = searchAnmPane(wc);
                            break;
                        }
                    }
                    if (anmPane != NULL) {
                        anmPane->onAnmEvent(nw4rmanager::AnmPane::PE_0);
                    }
                    keySet = keySet.GetNext();
                }
                keySet = hkbManager.GetRepeatedKeySet();
                while (keySet.IsValid()) {
                    nw4rmanager::AnmPane* anmPane = NULL;
                    u8 key = keySet.GetKey();
                    wchar_t wc = keySet.GetWChar();
                    switch (key) {
                        case 0x2C:
                            if (!(hkbManager.GetModifierState() & 0x8)) {
                                anmPane = searchAnmPane("P_key_SPACE");
                            }
                            break;
                        case 0x4C:
                            anmPane = searchAnmPane("P_key_DELETE");
                            break;
                        case 0x2A:
                            if (!(hkbManager.GetModifierState() & 0x4)) {
                                anmPane = searchAnmPane("P_key_DELETE");
                            }
                            break;
                    }
                    if (anmPane != NULL) {
                        anmPane->onAnmEvent(nw4rmanager::AnmPane::PE_0);
                    }
                    keySet = keySet.GetNext();
                }
                return false;
            }

            void LayoutByNW4R::changeAnimationAllToNormal() {
                for (AnmPane* anmPane = (AnmPane*)nw4r::ut::List_GetNext(&mAnmPanes, NULL);
                     anmPane != NULL;
                     anmPane = (AnmPane*)nw4r::ut::List_GetNext(&mAnmPanes, anmPane)) {
                    if (anmPane->getKeyType() == 0) {
                        anmPane->changeAnimation(0);
                    }
                }
                if ((mKeyState.mAIUFlags & 0xF) == 0) {
                    searchAnmPane("P_hiragana")->changeAnimation(5);
                    searchAnmPane("P_katakana")->changeAnimation(0);
                } else {
                    searchAnmPane("P_hiragana")->changeAnimation(0);
                    searchAnmPane("P_katakana")->changeAnimation(5);
                }
            }

            void EventHandler::onTiEvent(gui::PaneComponent* paneComponent, u32 event, TiEventHandler::Input* input) {
                char paneName[0x14];
                const char* name = paneComponent->getPane()->GetName();
                if (util::strcmp("B_key_SHIFT", name)) {
                    return;
                }
                if (util::strcmp("B_key_CAPS", name)) {
                    return;
                }
                if (name[0] != 'B') {
                    return;
                }
                util::replaceChar(paneName, 0x11, name, 0, 'P');
                if (strncmp(name + 5, "Chng", 4) == 0 || strncmp(name + 7, "Chng", 4) == 0 ||
                    strncmp(name + 7, "prdc", 4) == 0) {
                    util::replaceChar(paneName, 0x11, name, 0, 'W');
                }
                nw4rmanager::AnmPane* anmPane = mpLayout->searchAnmPane(paneName);
                switch (event) {
                    case 4:
                        if (input->field_0x0C & 0x800) {
                            if (anmPane != NULL) {
                                anmPane->onAnmEvent(nw4rmanager::AnmPane::PE_0);
                            }
                            mpLayout->onKey(4, paneName);
                        }
                        break;
                    case 1:
                        if (anmPane != NULL) {
                            anmPane->onAnmEvent(nw4rmanager::AnmPane::PE_2);
                        }
                        mpLayout->onKey(1, paneName);
                        break;
                    case 0:
                        if (anmPane != NULL) {
                            mpEventObserver->onSE(sound::SE_SELECT);
                            mpLayout->setPaneLastDrawReceived(anmPane->getPane());
                            anmPane->onAnmEvent(nw4rmanager::AnmPane::PE_1);
                        }
                        break;
                }
                if (event != 2) {
                    return;
                }
                if (!(input->field_0x10 & 0x800)) {
                    return;
                }
                if (input->field_0x0C & 0x800) {
                    return;
                }
                if (!util::strcmp("P_key_DELETE", paneName) &&
                    !util::strcmp("P_Gkey_DELETE", paneName) &&
                    !util::strcmp("P_key_SPACE", paneName) &&
                    !util::strcmp("P_Gkey_SPACE", paneName)) {
                    return;
                }
                if (!paneComponent->isDragging(input->field_0x00)) {
                    return;
                }
                u32 dur = mpLayout->getFlightDuration(input->field_0x00, name);
                if (dur < 30 || (dur % 9) != 0) {
                    return;
                }
                anmPane->onAnmEvent(nw4rmanager::AnmPane::PE_0);
                mpLayout->onKey(4, paneName);
            }

            // ============ AnmPane ============
            void AnmPane::init() {
                mState = 0;
            }

            void AnmPane::changeAnimation(u32 id) {
                mState = id;
                nw4rmanager::AnmPane::changeAnimation(id == 0x10 ? 2 : id);
            }

            AnmPane::~AnmPane() {
            }

            void NormalButtonAnmPane::onAnmEvent(AnmPaneEvent paneEvent) {
                switch (mKeyType) {
                    case 0:
                        if (paneEvent == 1) changeAnimation(1);
                        if (paneEvent == 0) changeAnimation(0x10);
                        break;
                    case 1:
                        if (paneEvent == 4) changeAnimation(3);
                        if (paneEvent == 2) changeAnimation(2);
                        if (paneEvent == 0) changeAnimation(4);
                        break;
                    case 2:
                        if (paneEvent == 2) changeAnimation(2);
                        if (paneEvent == 0) changeAnimation(4);
                        break;
                    case 3:
                        if (paneEvent == 4) changeAnimation(0);
                        if (paneEvent == 1) changeAnimation(1);
                        if (paneEvent == 0) changeAnimation(0x10);
                        break;
                    case 4:
                        if (paneEvent == 4) changeAnimation(3);
                        if (paneEvent == 2) changeAnimation(2);
                        if (paneEvent == 0) changeAnimation(4);
                        break;
                    case 5:
                        if (paneEvent == 4) changeAnimation(0);
                        if (paneEvent == 1) changeAnimation(1);
                        if (paneEvent == 0) changeAnimation(0x10);
                        break;
                    default:
                        break;
                }
            }

            NormalButtonAnmPane::~NormalButtonAnmPane() {
            }

            bool ShiftCapsAnmPane::isFocused() const {
                switch (mState) {
                    case 0:
                    case 2:
                    case 6:
                    case 9:
                    case 10:
                        return 0;
                    case 1:
                    case 3:
                    case 4:
                    case 5:
                    case 7:
                    case 8:
                    default:
                        return 1;
                }
            }

            void ShiftCapsAnmPane::onAnmEvent(AnmPaneEvent paneEvent) {
                if (paneEvent == 0xA) {
                    mbFocused = true;
                    if (mKeyType <= 0xA) {
                        changeAnimation(9);
                    } else {
                        changeAnimation(4);
                    }
                } else if (paneEvent == 0xB) {
                    mbFocused = false;
                    if (mKeyType <= 0xA) {
                        changeAnimation(2);
                    } else {
                        changeAnimation(0xB);
                    }
                } else if (paneEvent == 5) {
                    mbFocused = false;
                    if (mKeyType == 0xA) {
                        changeAnimation(6);
                    } else if (mKeyType == 8 || (mKeyType >= 4 && mKeyType <= 5)) {
                        changeAnimation(3);
                    }
                } else if (!mbFocused) {
                    switch (mKeyType) {
                        case 0:
                            if (paneEvent == 4) changeAnimation(0);
                            if (paneEvent == 1) changeAnimation(1);
                            if (paneEvent == 0) changeAnimation(9);
                            break;
                        case 1:
                            if (paneEvent == 1) changeAnimation(8);
                            break;
                        case 2:
                            if (paneEvent == 4) changeAnimation(5);
                            if (paneEvent == 2) changeAnimation(9);
                            break;
                        case 3:
                            if (paneEvent == 2) changeAnimation(9);
                            break;
                        case 4:
                            if (paneEvent == 4) changeAnimation(0xA);
                            if (paneEvent == 1) changeAnimation(1);
                            break;
                        case 5:
                            if (paneEvent == 4) changeAnimation(3);
                            if (paneEvent == 2) changeAnimation(2);
                            break;
                        default:
                            break;
                    }
                }
            }

            ShiftCapsAnmPane::~ShiftCapsAnmPane() {
            }

            void ToggleButtonAnmPane::onAnmEvent(AnmPaneEvent paneEvent) {
                if (paneEvent == 0) {
                    if (mKeyType != 5 && mKeyType != 4) {
                        changeAnimation(4);
                    }
                }
                switch (mKeyType) {
                    case 0:
                        if (paneEvent == 1) changeAnimation(1);
                        break;
                    case 1:
                        if (paneEvent == 4) changeAnimation(3);
                        if (paneEvent == 2) changeAnimation(2);
                        break;
                    case 2:
                        if (paneEvent == 2) changeAnimation(2);
                        break;
                    case 3:
                        if (paneEvent == 4) changeAnimation(0);
                        if (paneEvent == 1) changeAnimation(1);
                        break;
                    case 4:
                        if (paneEvent == 4) changeAnimation(5);
                        break;
                    case 5:
                        if (paneEvent == 4) changeAnimation(0);
                        break;
                    default:
                        break;
                }
            }

            ToggleButtonAnmPane::~ToggleButtonAnmPane() {
            }

            void OnOffButtonAnmPane::onAnmEvent(AnmPaneEvent paneEvent) {
                if (paneEvent == 0) {
                    if (mKeyType != 0xF && mKeyType != 2 && mKeyType != 0xD) {
                        changeAnimation(4);
                    }
                    return;
                }
                if (paneEvent == 6) {
                    if (mKeyType != 0xE && mKeyType != 4 && mKeyType != 3 && mKeyType != 0xC &&
                        mKeyType != 1 && mKeyType != 2) {
                        changeAnimation(0xC);
                    }
                    return;
                }
                if (paneEvent == 7) {
                    if (mKeyType != 0xF) {
                        changeAnimation(0xD);
                    }
                    return;
                }
                switch (mKeyType) {
                    case 0:
                        if (paneEvent == 4) changeAnimation(0xE);
                        if (paneEvent == 1) changeAnimation(1);
                        break;
                    case 1:
                        if (paneEvent == 4) changeAnimation(0xF);
                        break;
                    case 2:
                        if (paneEvent == 1) changeAnimation(1);
                        break;
                    case 3:
                        if (paneEvent == 4) changeAnimation(3);
                        if (paneEvent == 2) changeAnimation(2);
                        break;
                    case 4:
                        if (paneEvent == 2) changeAnimation(2);
                        break;
                    case 5:
                        if (paneEvent == 4) changeAnimation(0xE);
                        if (paneEvent == 1) changeAnimation(1);
                        break;
                    case 6:
                        if (paneEvent == 4) changeAnimation(3);
                        if (paneEvent == 2) changeAnimation(2);
                        break;
                    default:
                        break;
                }
            }

            OnOffButtonAnmPane::~OnOffButtonAnmPane() {
            }

            // ============ UI objects ============
            UIModifierButton::UIModifierButton(u32 ctrlNo, LayoutByNW4R* layout, Listener* listener)
                : UIObj(ctrlNo, layout, listener) {
                mpPaneComp1 = NULL;
                mpPaneComp2 = NULL;
                mpAnmPane = NULL;
                mbFocused = false;
            }

            void UIModifierButton::onGUIEvent(gui::PaneComponent& pane, u32 event, nw4rmanager::TiEventHandler::Input* input) {
                const char* paneName = (mCtrlNo == 1) ? "P_key_SHIFT" : "P_key_CAPS";
                switch (event) {
                    case 4:
                        if (input->field_0x0C & 0x800) {
                            mpLayout->onKey(4, (void*)paneName);
                        }
                        break;
                    case 1:
                        mpAnmPane->onAnmEvent(nw4rmanager::AnmPane::PE_2);
                        mpLayout->onKey(1, (void*)paneName);
                        break;
                    case 0:
                        if (mpListener != NULL) {
                            mpListener->onEvent(this, 0, (void*)4);
                        }
                        mpLayout->setPaneLastDrawReceived(mpAnmPane->getPane());
                        mpAnmPane->onAnmEvent(nw4rmanager::AnmPane::PE_1);
                        break;
                }
            }

            UIModePanel::UIModePanel(u32 ctrlNo, LayoutByNW4R* layout, Listener* listener)
                : UIObj(ctrlNo, layout, listener) {
                unk_0x14 = 0;
                for (int i = 0; i < 3; i++) {
                    mExtraPanes[i] = NULL;
                }
                for (int i = 0; i < 5; i++) {
                    mpComps1[i] = NULL;
                    mpComps2[i] = NULL;
                    mpAnmPanes[i] = NULL;
                }
            }

            void UIModePanel::onGUIEvent(gui::PaneComponent& pane, u32 event, nw4rmanager::TiEventHandler::Input* input) {
            }

            void UIModePanel::Create(nw4rmanager::Layout* layout) {
                static const char* csAnmPaneNames[5] = {
                    "P_Mode_direct", "P_Mode_roma_hira", "P_Mode_roma_kata", "P_Mode_kr_eng", "P_Mode_kr_han"
                };
                static const char* csCompNames[5] = {
                    "B_Mode_direct", "B_Mode_roma_hira", "B_Mode_roma_kata", "B_Mode_kr_eng", "B_Mode_kr_han"
                };
                gui::PaneManager* pm = layout->getPaneManager();
                for (int i = 0; i < 5; i++) {
                    mpComps1[i] = pm->searchPaneComponent(csAnmPaneNames[i]);
                    mpComps2[i] = pm->searchPaneComponent(csCompNames[i]);
                    mpAnmPanes[i] = layout->searchAnmPane(csAnmPaneNames[i]);
                    mpComps2[i]->setOwner(this);
                }
                nw4r::lyt::Pane* rootPane = layout->getLayout()->GetRootPane();
                mExtraPanes[0] = rootPane->FindPaneByName("T_Mode_kr_eng", true);
                mExtraPanes[1] = rootPane->FindPaneByName("T_Mode_kr_han", true);
                mExtraPanes[2] = rootPane->FindPaneByName("N_modeSelect_kr", true);
                rootPane->FindPaneByName("T_Mode_kr_eng", true)->GetMaterial()->GetTexture(&mTexObjs[2], 0);
                rootPane->FindPaneByName("T_Mode_kr_han", true)->GetMaterial()->GetTexture(&mTexObjs[3], 0);
                rootPane->FindPaneByName("T_Mode_direct", true)->GetMaterial()->GetTexture(&mTexObjs[0], 0);
                rootPane->FindPaneByName("T_Mode_cn_pinyin", true)->GetMaterial()->GetTexture(&mTexObjs[1], 0);
            }

            void UIObj::onEvent(gui::GUIComponent& comp, u32 event, void* data) {
                onGUIEvent(*(gui::PaneComponent*)&comp, event, (nw4rmanager::TiEventHandler::Input*)data);
            }

            void UIObj::onGUIEvent(gui::PaneComponent& pane, u32 event, nw4rmanager::TiEventHandler::Input* input) {
            }

            gui::EventHandler::~EventHandler() {
            }

            void nw4rmanager::AnmPane::onAnmEvent(AnmPaneEvent) {
            }

            void gui::EventHandler::setLatestEventCtrlNo(int ctrlNo) {
                muLatestEventCtrlNo = ctrlNo;
            }

            int gui::EventHandler::getLatestEventCtrlNo() {
                return muLatestEventCtrlNo;
            }

            void gui::EventHandler::onEvent(gui::GUIComponent& comp, u32 event, void* data) {
            }

            void nw4rmanager::PaneFifo::init() {
                for (int i = 0; i < MAX_COUNT; i++) {
                    mpaFifo[i] = NULL;
                }
            }

            void nw4rmanager::PaneFifo::push(nw4r::lyt::Pane* pane) {
                if (mpaFifo[MAX_COUNT-1] == NULL) {
                    for (int i = 0; i < MAX_COUNT; i++) {
                        if (mpaFifo[i] == NULL) {
                            mpaFifo[i] = pane;
                            return;
                        }
                    }
                }
                else {
                    for (int i = 1; i < MAX_COUNT; i++) {
                        mpaFifo[i-1] = mpaFifo[i];
                        if (pane == mpaFifo[i-1]) {
                            mpaFifo[i-1] = NULL;
                        }
                    }
                    mpaFifo[MAX_COUNT-1] = pane;
                }
            }

            nw4r::lyt::Pane* nw4rmanager::PaneFifo::getLast() {
                for (int i = MAX_COUNT-1; i > -1; i--) {
                    if (mpaFifo[i] != NULL) {
                        return mpaFifo[i];
                    }
                }
                return NULL;
            }

            void CommandSender::sendCommand(u32 command, void* data) {
                if (mpCommandReceiver != NULL) {
                    mpCommandReceiver->onCommand((CommandReceiver::INPUT_COMMAND)command, data);
                }
            }

            void KeyboardBase::update() {
            }

            Language KeyboardBase::getLanguage() const {
                return meLanguage;
            }

            Language Manager::getLanguage() const {
                return meLanguage;
            }

            const keyboard::hwkey::HWKeyboard* Manager::getHWKeyboard() const {
                return mpHWKeyboard;
            }

            const pctype::LayoutByNW4R* Manager::getPCKeyboard() const {
                return mpPCKeyboard;
            }

            toolbar::LayoutByNW4R* Manager::getToolBar() {
                return mpToolBar;
            }

            const toolbar::LayoutByNW4R* Manager::getToolBar() const {
                return mpToolBar;
            }

            candidatebox::LayoutByNW4R* Manager::getCandidateBox() {
                return mpCandidateBox;
            }

            TiLayout* nw4rmanager::Layout::getLayout() {
                return mpLayout;
            }

            gui::PaneManager* nw4rmanager::Layout::getPaneManager() {
                return mpPaneManager;
            }

            void nw4rmanager::Layout::setAnimOn(bool flag) {
                mbAnimOn = flag;
            }

            nw4r::ut::List& nw4rmanager::Layout::getAnmPaneList() {
                return mAnmPanes;
            }

            void nw4rmanager::Layout::initPaneLastDrawReceived() {
                mAnmPaneFifo.init();
            }

            void nw4rmanager::Layout::setPaneLastDrawReceived(nw4r::lyt::Pane* pane) {
                mAnmPaneFifo.push(pane);
            }

            bool nw4rmanager::AnmPane::isInAnimation() {
                return mpCurrentAnim != NULL;
            }

            nw4rmanager::Anim* nw4rmanager::AnmPane::searchAnimation(u32 id) {
                Anim* it = (Anim*)nw4r::ut::List_GetNext(&mAnms, NULL);
                while (it != NULL) {
                    if (it->muID == id) {
                        return it;
                    }
                    it = (Anim*)nw4r::ut::List_GetNext(&mAnms, it);
                }
                return NULL;
            }

            bool candidatebox::LayoutByNW4R::isActive() const {
                return mbActive;
            }

            bool inputform::Base::canConvert() {
                return getCurrentString(false) == mpUnfixString;
            }

            Base::~Base() {
            }

            int Base::getType() {
                return 0;
            }

            void* Base::getState() {
                return &unk_0x14;
            }

            void Base::inputCharCode(wchar_t wc) {
                sendInputWChar(wc, false);
            }

            void Base::setInputModeCK(u32) {
            }

            void Base::setInputModeJP(bool, u32, u32) {
            }

            void Base::goSignInputMode() {
            }

            void Base::changePredictLanguage() {
            }

            void Base::setLanguage(Language language) {
                meLanguage = language;
                mKeyState.mLanguage = language;
                mKeyState.refresh_();
            }

            void Base::setLangKeyActive(bool flag) {
                mbLangKeyActive = flag;
                if (getLanguage() == (Language)9 || getLanguage() == (Language)8) {
                    if (!flag) {
                        mKeyState.setABCFlag(0);
                        changeABCInputMode(IM_00);
                    }
                }
            }

            void Base::onlyQwerty(bool flag) {
                mbOnlyQwerty = flag;
                if (getLanguage() == (Language)0) {
                    if (flag) {
                        setABC(true);
                        mKeyState.setABCFlag(0);
                        changeABCInputMode(IM_00);
                    }
                    else {
                        setABC(false);
                        changeAIUInputMode(IM_06);
                    }
                }
            }

            void Base::updateFixMode() {
                if (mgr()->getToolBar() != NULL && !mgr()->getToolBar()->isQwerty()) {
                    return;
                }
                switch (getLanguage()) {
                    case JP: {
                        u8 flag = 0;
                        if (isABC() && (mKeyState.mFlags & 0xF) == 0) {
                            flag = 1;
                        }
                        else {
                            flag = 0;
                        }
                        sendCommand(0x14, &flag);
                        break;
                    }
                }
            }

            int Base::getABCInputMode() const {
                return IM_00;
            }

            int Base::getAIUInputMode() const {
                switch (mKeyState.mAIUFlags & 0xF) {
                    case 0:     return IM_06;
                    case 1:     return IM_07;
                    default:    return IM_06;
                }
            }

        }  // namespace pctype
    }  // namespace keyboard
}  // namespace textinput
