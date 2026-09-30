#define TI_PC_KEYBOARD_IMPLEMENTATION
#include "keyboard/tiPcKeyboard.h"
#include "keyboard/tiManager.h"
#include "keyboard/tiUtil.h"
#include "keyboard/tiLayoutGather.h"
#include "keyboard/tiPredictLang.h"
#include "keyboard/tiToolBar.h"
#include <nw4r/lyt/textbox.h>
#include <new>
#include <string.h>
#include "keyboard/tiLanguageIndependentData.h"

namespace textinput {
    namespace keyboard {
        namespace pctype {
            struct SelectorPosition {
                f32 coordinates[3];
            };
            extern SelectorPosition chinesePosition;
            extern SelectorPosition koreanPosition;

            static const wchar_t* PREDICT_CAPTIONS[] = {L"", L"", L"Eng", L"Fra", L"Esp", L"EN", L"DE", L"FR", L"ES", L"IT", L"NL", L"CN", L"KR"};

            static const GridKey csGridKeyboard[] = {
                {"P_Gkey_00", {0xe0, 0x21, 0x0, 0x0}},         {"P_Gkey_01", {0xe1, 0x3f, 0x3042, 0x30a2}},
                {"P_Gkey_02", {0xe2, 0x26, 0x304b, 0x30ab}},   {"P_Gkey_03", {0xe4, 0x2033, 0x3055, 0x30b5}},
                {"P_Gkey_04", {0xe8, 0x27, 0x305f, 0x30bf}},   {"P_Gkey_05", {0xe9, 0xff5e, 0x306a, 0x30ca}},
                {"P_Gkey_06", {0xea, 0x3a, 0x306f, 0x30cf}},   {"P_Gkey_07", {0xeb, 0x3b, 0x307e, 0x30de}},
                {"P_Gkey_08", {0xec, 0x40, 0x3084, 0x30e4}},   {"P_Gkey_09", {0xed, 0x7e, 0x3089, 0x30e9}},
                {"P_Gkey_10", {0xee, 0x5f, 0x308f, 0x30ef}},   {"P_Gkey_11", {0xe0, 0x2b, 0x0, 0x0}},
                {"P_Gkey_12", {0xe1, 0x2d, 0x3044, 0x30a4}},   {"P_Gkey_13", {0xe2, 0x2a, 0x304d, 0x30ad}},
                {"P_Gkey_14", {0xe4, 0x2f, 0x3057, 0x30b7}},   {"P_Gkey_15", {0xe8, 0xd7, 0x3061, 0x30c1}},
                {"P_Gkey_16", {0xe9, 0xf7, 0x306b, 0x30cb}},   {"P_Gkey_17", {0xea, 0x3d, 0x3072, 0x30d2}},
                {"P_Gkey_18", {0xeb, 0x2192, 0x307f, 0x30df}}, {"P_Gkey_19", {0xec, 0x2190, 0x3086, 0x30e6}},
                {"P_Gkey_20", {0xed, 0x2191, 0x308a, 0x30ea}}, {"P_Gkey_21", {0xee, 0x2193, 0x3092, 0x30f2}},
                {"P_Gkey_22", {0xf1, 0x300c, 0x0, 0x0}},       {"P_Gkey_23", {0xdf, 0x300d, 0x3046, 0x30a6}},
                {"P_Gkey_24", {0xc0, 0x201c, 0x304f, 0x30af}}, {"P_Gkey_25", {0xc1, 0x201d, 0x3059, 0x30b9}},
                {"P_Gkey_26", {0xc2, 0x28, 0x3064, 0x30c4}},   {"P_Gkey_27", {0xc4, 0x29, 0x306c, 0x30cc}},
                {"P_Gkey_28", {0xc8, 0x3c, 0x3075, 0x30d5}},   {"P_Gkey_29", {0xc9, 0x3e, 0x3080, 0x30e0}},
                {"P_Gkey_30", {0xca, 0x7b, 0x3088, 0x30e8}},   {"P_Gkey_31", {0xcb, 0x7d, 0x308b, 0x30eb}},
                {"P_Gkey_32", {0xcc, 0x2022, 0x3093, 0x30f3}}, {"P_Gkey_33", {0xcd, 0x25, 0x0, 0x0}},
                {"P_Gkey_34", {0xce, 0x203b, 0x3048, 0x30a8}}, {"P_Gkey_35", {0xcf, 0x3012, 0x3051, 0x30b1}},
                {"P_Gkey_36", {0xd2, 0x23, 0x305b, 0x30bb}},   {"P_Gkey_37", {0xd3, 0x266d, 0x3066, 0x30c6}},
                {"P_Gkey_38", {0xd4, 0x266a, 0x306d, 0x30cd}}, {"P_Gkey_39", {0xd6, 0xb1, 0x3078, 0x30d8}},
                {"P_Gkey_40", {0x152, 0x24, 0x3081, 0x30e1}},  {"P_Gkey_41", {0xd9, 0xa2, 0xff01, 0xff01}},
                {"P_Gkey_42", {0xda, 0xa3, 0x308c, 0x30ec}},   {"P_Gkey_43", {0xdb, 0x205c, 0x3001, 0x3001}},
                {"P_Gkey_44", {0xdc, 0x5e, 0x0, 0x0}},         {"P_Gkey_45", {0xc7, 0xb0, 0x304a, 0x30aa}},
                {"P_Gkey_46", {0xd1, 0xff5c, 0x3053, 0x30b3}}, {"P_Gkey_47", {0xa1, 0xff0f, 0x305d, 0x30bd}},
                {"P_Gkey_48", {0xbf, 0xff3c, 0x3068, 0x30c8}}, {"P_Gkey_49", {0xac, 0x221e, 0x306e, 0x30ce}},
                {"P_Gkey_50", {0xa2, 0x2234, 0x307b, 0x30db}}, {"P_Gkey_51", {0xa3, 0x2026, 0x3082, 0x30e2}},
                {"P_Gkey_52", {0xa7, 0x2122, 0xff1f, 0xff1f}}, {"P_Gkey_53", {0x0, 0xa9, 0x308d, 0x30ed}},
                {"P_Gkey_54", {0x0, 0xae, 0x3002, 0x3002}},    {"P_Gkey_55", {0xa2, 0x2234, 0x30fc, 0x30fc}},
            };

            static const ControlKey csPaneNameToControlKey[] = {
                {"P_key_LF", 0},        {"P_key_DELETE", 1},    {"P_key_CAPS", 3},      {"P_key_SHIFT", 4},       {"P_key_SPACE", 2},
                {"P_Gkey_LF", 0},       {"P_Gkey_DELETE", 1},   {"P_Gkey_SPACE", 2},    {"W_USEU_prdc_lang", 10}, {"W_USEU_Chng_sign", 13},
                {"W_JP_Chng_ABC", 11},  {"W_JP_Chng_KANA", 12}, {"W_JP_Chng_sign", 13}, {"P_Mode_roma_hira", 16}, {"P_Mode_roma_kata", 17},
                {"P_Mode_direct", 15},  {"P_hiragana", 18},     {"P_katakana", 19},     {"P_Gkey_komoji", 22},    {"P_Gkey_handaku", 21},
                {"P_Gkey_dakuten", 20}, {"P_Mode_kr_eng", 15},  {"P_Mode_kr_han", 16},
            };

            static const VisiblePanes csJPNAsciiVisiblePanes = {

                13,
                24,
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
                    NULL},
                {"P_key_41",         "T_key_41",         "P_key_42",         "T_key_42",    "P_key_43",   "T_key_43",
                 "N_KeyChange_USEU", "P_Gkey_00",        "P_Gkey_11",        "P_Gkey_22",   "P_Gkey_33",  "P_Gkey_44",
                 "T_Gkey_00",        "T_Gkey_11",        "T_Gkey_22",        "T_Gkey_33",   "T_Gkey_44",  "W_USEU_prdc_lang",
                 "W_USEU_Chng_sign", "T_USEU_prdc_lang", "T_USEU_Chng_sign", "P_SHIFTMark", "P_CAPSMark", "N_modeSelect_kr"}};

            static const VisiblePanes csUSAsciiVisiblePanes = {

                17,
                20,
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
                    NULL},
                {"P_key_41",
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
                 NULL}};

            static const VisiblePanes csEngAsciiVisiblePanesUK = {

                21,
                16,
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
                    NULL},
                {"P_key_41",
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
                 NULL}};

            static const VisiblePanes csEngAsciiVisiblePanesSP = {

                21,
                16,
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
                    NULL},
                {"P_key_41",
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
                 NULL}};

            static const VisiblePanes csAsciiVisiblePanes = {

                23,
                14,
                {

                    "P_key_41",         "T_key_41",         "P_key_42",         "T_key_42",    "P_key_43",   "T_key_43",
                    "N_KeyChange_USEU", "P_Gkey_00",        "P_Gkey_11",        "P_Gkey_22",   "P_Gkey_33",  "P_Gkey_44",
                    "T_Gkey_00",        "T_Gkey_11",        "T_Gkey_22",        "T_Gkey_33",   "T_Gkey_44",  "W_USEU_prdc_lang",
                    "W_USEU_Chng_sign", "T_USEU_prdc_lang", "T_USEU_Chng_sign", "P_SHIFTMark", "P_CAPSMark", NULL},
                {"N_modeSelect_all",
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
                 NULL}};

            static const VisiblePanes csAsciiVisiblePanesNL = {

                19,
                18,
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
                    NULL},
                {"P_key_41",
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
                 NULL}};

            static const VisiblePanes csCNAsciiVisiblePanes = {

                20,
                21,
                {

                    "N_KeyChange_USEU", "P_Gkey_00",       "P_Gkey_11",   "P_Gkey_22", "P_Gkey_33", "P_Gkey_44",
                    "T_Gkey_00",        "T_Gkey_11",       "T_Gkey_22",   "T_Gkey_33", "T_Gkey_44", "W_USEU_Chng_sign",
                    "T_USEU_Chng_sign", "T_key_CAPS",      "T_key_SHIFT", "P_key_42",  "T_key_42",  "P_key_43",
                    "T_key_43",         "N_modeSelect_kr", NULL,          NULL,        NULL,        NULL},
                {"P_key_41",
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
                 NULL}};

            static const VisiblePanes csKRAsciiVisiblePanes = {

                16,
                22,
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
                    NULL},
                {"P_key_41",
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
                 NULL}};

            static const Ablaut csCharCodeToAblautSP[] = {
                {0x61, {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0x0, 0x0}}, {0x69, {0xec, 0xed, 0xee, 0x0, 0xef, 0x0, 0x0}},
                {0x75, {0xf9, 0xfa, 0xfb, 0x0, 0xfc, 0x0, 0x0}},  {0x65, {0xe8, 0xe9, 0xea, 0x0, 0xeb, 0x0, 0x0}},
                {0x6f, {0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0x0, 0x0}}, {0x41, {0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0x0, 0x0}},
                {0x49, {0xcc, 0xcd, 0xce, 0x0, 0xcf, 0x0, 0x0}},  {0x55, {0xd9, 0xda, 0xdb, 0x0, 0xdc, 0x0, 0x0}},
                {0x45, {0xc8, 0xc9, 0xca, 0x0, 0xcb, 0x0, 0x0}},  {0x4f, {0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0x0, 0x0}},
                {0x79, {0x0, 0xfd, 0x0, 0x0, 0xff, 0x0, 0x0}},    {0x59, {0x0, 0xdd, 0x0, 0x0, 0x178, 0x0, 0x0}},
            };

            static const Ablaut csCharCodeToAblautNL[] = {
                {0x61, {0xe0, 0x0, 0xe2, 0xe3, 0x0, 0xe1, 0xe4}}, {0x69, {0xec, 0x0, 0xee, 0x0, 0x0, 0xed, 0xef}},
                {0x75, {0xf9, 0x0, 0xfb, 0x0, 0x0, 0xfa, 0xfc}},  {0x65, {0xe8, 0x0, 0xea, 0x0, 0x0, 0xe9, 0xeb}},
                {0x6f, {0xf2, 0x0, 0xf4, 0xf5, 0x0, 0xf3, 0xf6}}, {0x41, {0xc0, 0x0, 0xc2, 0xc3, 0x0, 0xc1, 0xc4}},
                {0x49, {0xcc, 0x0, 0xce, 0x0, 0x0, 0xcd, 0xcf}},  {0x55, {0xd9, 0x0, 0xdb, 0x0, 0x0, 0xda, 0xdc}},
                {0x45, {0xc8, 0x0, 0xca, 0x0, 0x0, 0xc9, 0xcb}},  {0x4f, {0xd2, 0x0, 0xd4, 0xd5, 0x0, 0xd3, 0xd6}},
                {0x79, {0x0, 0x0, 0x0, 0x0, 0x0, 0xfd, 0xff}},    {0x59, {0x0, 0x0, 0x0, 0x0, 0x0, 0xdd, 0x178}},
            };

            static const Ablaut csCharCodeToAblautDE[] = {
                {0x61, {0xe0, 0xe1, 0x0, 0x0, 0x0, 0x0, 0x0}}, {0x69, {0xec, 0xed, 0x0, 0x0, 0x0, 0x0, 0x0}},
                {0x75, {0xf9, 0xfa, 0x0, 0x0, 0x0, 0x0, 0x0}}, {0x65, {0xe8, 0xe9, 0x0, 0x0, 0x0, 0x0, 0x0}},
                {0x6f, {0xf2, 0xf3, 0x0, 0x0, 0x0, 0x0, 0x0}}, {0x41, {0xc0, 0xc1, 0x0, 0x0, 0x0, 0x0, 0x0}},
                {0x49, {0xcc, 0xcd, 0x0, 0x0, 0x0, 0x0, 0x0}}, {0x55, {0xd9, 0xda, 0x0, 0x0, 0x0, 0x0, 0x0}},
                {0x45, {0xc8, 0xc9, 0x0, 0x0, 0x0, 0x0, 0x0}}, {0x4f, {0xd2, 0xd3, 0x0, 0x0, 0x0, 0x0, 0x0}},
                {0x79, {0x0, 0xfd, 0x0, 0x0, 0x0, 0x0, 0x0}},  {0x59, {0x0, 0xdd, 0x0, 0x0, 0x0, 0x0, 0x0}},
            };

            static const Ablaut csCharCodeToAblautFR[] = {
                {0x61, {0x0, 0x0, 0xe2, 0x0, 0xe4, 0x0, 0x0}}, {0x69, {0x0, 0x0, 0xee, 0x0, 0xef, 0x0, 0x0}},
                {0x75, {0x0, 0x0, 0xfb, 0x0, 0xfc, 0x0, 0x0}}, {0x65, {0x0, 0x0, 0xea, 0x0, 0xeb, 0x0, 0x0}},
                {0x6f, {0x0, 0x0, 0xf4, 0x0, 0xf6, 0x0, 0x0}}, {0x41, {0x0, 0x0, 0xc2, 0x0, 0xc4, 0x0, 0x0}},
                {0x49, {0x0, 0x0, 0xce, 0x0, 0xcf, 0x0, 0x0}}, {0x55, {0x0, 0x0, 0xdb, 0x0, 0xdc, 0x0, 0x0}},
                {0x45, {0x0, 0x0, 0xca, 0x0, 0xcb, 0x0, 0x0}}, {0x4f, {0x0, 0x0, 0xd4, 0x0, 0xd6, 0x0, 0x0}},
                {0x79, {0x0, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0}},  {0x59, {0x0, 0x0, 0x0, 0x0, 0x178, 0x0, 0x0}},
            };

            static const LanguageData csLanguageDependencyData[] = {
                {csUSKeyboard, csGridKeyboard, csPaneNameToControlKey, &csJPNAsciiVisiblePanes, NULL},
                {csUSKeyboard, csGridKeyboard, csPaneNameToControlKey, &csUSAsciiVisiblePanes, NULL},
                {csUKKeyboard, csGridKeyboard, csPaneNameToControlKey, &csEngAsciiVisiblePanesUK, NULL},
                {csFRKeyboard, csGridKeyboard, csPaneNameToControlKey, &csAsciiVisiblePanes, csCharCodeToAblautFR},
                {csDEKeyboard, csGridKeyboard, csPaneNameToControlKey, &csAsciiVisiblePanes, csCharCodeToAblautDE},
                {csITKeyboard, csGridKeyboard, csPaneNameToControlKey, &csAsciiVisiblePanes, NULL},
                {csESKeyboard, csGridKeyboard, csPaneNameToControlKey, &csEngAsciiVisiblePanesSP, csCharCodeToAblautSP},
                {csNLKeyboard, csGridKeyboard, csPaneNameToControlKey, &csAsciiVisiblePanesNL, csCharCodeToAblautNL},
                {csCNKeyboard, csGridKeyboard, csPaneNameToControlKey, &csCNAsciiVisiblePanes, NULL},
                {csUSKeyboard, csGridKeyboard, csPaneNameToControlKey, &csKRAsciiVisiblePanes, NULL},
            };

            static const LanguageData csJapanKanaInput = {csJPKeyboard, csGridKeyboard, csPaneNameToControlKey, &csJPNAsciiVisiblePanes, NULL};

            struct AnimationFile {
                u32 id;
                char fileName[64];
            };
            struct PaneAnimation {
                int type;
                const char* paneName;
                u32 count;
                const char* sharedPane;
                const AnimationFile* animations[12];
            };
            static const AnimationFile csAninationFile[] = {
                {0, "fs_VK_ascii_keytop_a_normal.brlan"},
                {1, "fs_VK_ascii_keytop_a_Focus-IN.brlan"},
                {2, "fs_VK_ascii_keytop_a_Focus-OUT.brlan"},
                {3, "fs_VK_ascii_keytop_a_Roll_over.brlan"},
                {4, "fs_VK_ascii_keytop_a_Pushed.brlan"},
                {5, "fs_VK_ascii_keytop_a_toggle-ON.brlan"},
                {6, "fs_VK_ascii_keytop_a_toggle-OFF.brlan"},
                {7, "fs_VK_ascii_keytop_a_Target_ON.brlan"},
                {8, "fs_VK_ascii_keytop_a_toggleON_Focus-IN.brlan"},
                {9, "fs_VK_ascii_keytop_a_toggleON_Focus-OUT.brlan"},
                {10, "fs_VK_ascii_keytop_a_normal_toggle-ON.brlan"},
                {11, "fs_VK_ascii_keytop_a_toggleON_Pushed.brlan"},
                {12, "fs_VK_ascii_keytop_a_active-ON.brlan"},
                {13, "fs_VK_ascii_keytop_a_active-OFF.brlan"},
                {14, "fs_VK_ascii_keytop_a_active_normal.brlan"},
                {15, "fs_VK_ascii_keytop_a_not_active_normal.brlan"},
            };
            static const wchar_t KOREAN_LOWER[] = {0x3141, 0x3160, 0x314a, 0x3147, 0x3137, 0x3139, 0x314e, 0x3157, 0x3151,
                                                   0x3153, 0x314f, 0x3163, 0x3161, 0x315c, 0x3150, 0x3154, 0x3142, 0x3131,
                                                   0x3134, 0x3145, 0x3155, 0x314d, 0x3148, 0x314c, 0x315b, 0x314b};
            static const wchar_t KOREAN_UPPER[] = {0x3141, 0x3160, 0x314a, 0x3147, 0x3138, 0x3139, 0x314e, 0x3157, 0x3151,
                                                   0x3153, 0x314f, 0x3163, 0x3161, 0x315c, 0x3152, 0x3156, 0x3143, 0x3132,
                                                   0x3134, 0x3146, 0x3155, 0x314d, 0x3149, 0x314c, 0x315b, 0x314b};
            static const char* COMMON_KEY_ANIMATION = "P_key_00";
            static const PaneAnimation csPaneToAnimation[] = {
                {0,
                 "P_key_00",
                 5,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_01",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_02",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_03",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_04",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_05",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_06",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_07",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_08",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_09",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_10",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_11",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_12",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_13",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_15",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_16",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_17",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_18",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_14",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_19",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_20",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_21",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_22",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_23",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_24",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_25",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_26",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_27",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_28",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_29",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_30",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_31",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_32",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_33",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_34",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_35",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_36",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_37",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_38",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_39",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_40",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_41",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_42",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_43",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_44",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_45",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_46",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_47",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_48",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_49",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_DELETE",
                 5,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_LF",
                 5,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_key_SPACE",
                 5,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {1,
                 "P_key_SHIFT",
                 12,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5],
                  &csAninationFile[6], &csAninationFile[7], &csAninationFile[8], &csAninationFile[9], &csAninationFile[10], &csAninationFile[11]}},
                {1,
                 "P_key_CAPS",
                 12,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5],
                  &csAninationFile[6], &csAninationFile[7], &csAninationFile[8], &csAninationFile[9], &csAninationFile[10], &csAninationFile[11]}},
                {0,
                 "P_Gkey_00",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_01",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_02",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_03",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_04",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_05",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_06",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_07",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_08",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_09",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_10",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_11",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_12",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_13",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_14",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_15",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_16",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_17",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_18",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_19",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_20",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_21",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_22",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_23",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_24",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_25",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_26",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_27",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_28",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_29",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_30",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_31",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_32",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_33",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_34",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_35",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_36",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_37",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_38",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_39",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_40",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_41",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_42",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_43",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_44",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_45",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_46",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_47",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_48",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_49",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_50",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_51",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_52",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_53",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_54",
                 5,
                 COMMON_KEY_ANIMATION,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_55",
                 5,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_DELETE",
                 5,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_LF",
                 5,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "P_Gkey_SPACE",
                 5,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "W_USEU_prdc_lang",
                 5,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {0,
                 "W_USEU_Chng_sign",
                 5,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {2,
                 "W_JP_Chng_ABC",
                 7,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5],
                  &csAninationFile[6], &csAninationFile[7], NULL, NULL, NULL, NULL}},
                {2,
                 "W_JP_Chng_KANA",
                 7,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5],
                  &csAninationFile[6], &csAninationFile[7], NULL, NULL, NULL, NULL}},
                {0,
                 "W_JP_Chng_sign",
                 5,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5], NULL,
                  NULL, NULL, NULL, NULL, NULL}},
                {2,
                 "P_hiragana",
                 7,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5],
                  &csAninationFile[6], &csAninationFile[7], NULL, NULL, NULL, NULL}},
                {2,
                 "P_katakana",
                 7,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5],
                  &csAninationFile[6], &csAninationFile[7], NULL, NULL, NULL, NULL}},
                {3,
                 "P_Gkey_dakuten",
                 11,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5],
                  &csAninationFile[6], &csAninationFile[12], &csAninationFile[13], &csAninationFile[14], &csAninationFile[15], NULL}},
                {3,
                 "P_Gkey_handaku",
                 11,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5],
                  &csAninationFile[6], &csAninationFile[12], &csAninationFile[13], &csAninationFile[14], &csAninationFile[15], NULL}},
                {3,
                 "P_Gkey_komoji",
                 11,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5],
                  &csAninationFile[6], &csAninationFile[12], &csAninationFile[13], &csAninationFile[14], &csAninationFile[15], NULL}},
                {2,
                 "P_Mode_roma_hira",
                 7,
                 "P_Mode_direct",
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5],
                  &csAninationFile[6], &csAninationFile[7], NULL, NULL, NULL, NULL}},
                {2,
                 "P_Mode_roma_kata",
                 7,
                 "P_Mode_direct",
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5],
                  &csAninationFile[6], &csAninationFile[7], NULL, NULL, NULL, NULL}},
                {2,
                 "P_Mode_direct",
                 7,
                 NULL,
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5],
                  &csAninationFile[6], &csAninationFile[7], NULL, NULL, NULL, NULL}},
                {2,
                 "P_Mode_kr_eng",
                 7,
                 "P_Mode_direct",
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5],
                  &csAninationFile[6], &csAninationFile[7], NULL, NULL, NULL, NULL}},
                {2,
                 "P_Mode_kr_han",
                 7,
                 "P_Mode_direct",
                 {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3], &csAninationFile[4], &csAninationFile[5],
                  &csAninationFile[6], &csAninationFile[7], NULL, NULL, NULL, NULL}},
            };

            Base::TranslateMode Base::getTranslateMode() const {
                switch (static_cast<int>(mKeyState.abcFlags & 15)) {
                    case 0:
                        return TM_Direct;
                    case 1:
                        return TM_Roman;
                    case 2:
                        return TM_Kana;
                    default:
                        return TM_Direct;
                }
            }

            bool Base::isCapsOn() const {
                return (mKeyState.abcFlags >> 6) & 1;
            }

            void Base::create(MEMAllocator* allocator) {
                mpAllocator = allocator;
            }

            void Base::init() {
                mState.rejected = false;
                Language language = getLanguage();
                mKeyState.inputType = 0;
                mpInitialLanguageData = &csLanguageDependencyData[language];
                if (mKeyState.language == JP && !mKeyState.owner->mbOnlyQwerty) {
                    mKeyState.abcFlags = 1;
                } else if (static_cast<u32>(mKeyState.language - CN) <= 1 && mKeyState.owner->mbLanguageKeyActive) {
                    mKeyState.abcFlags = 1;
                } else {
                    mKeyState.abcFlags = 0;
                }
                mKeyState.aiuFlags = 0;
                mKeyState.refresh_();
                TranslateMode mode = Base::getTranslateMode();
                sendCommand(18, &mode);
            }

            void Base::inputCharCode(wchar_t code) {
                sendInputWChar(code, false);
            }

            void Base::onKey(u32 event, void* data) {
                wchar_t code = getWCCode(static_cast<char*>(data));
                if (event == 4) {
                    if (code == 0) {
                        switch (getControlKey(static_cast<char*>(data))) {
                            case 1:
                                sendCommand(1, NULL);
                                break;
                            case 0:
                                sendCommand(7, NULL);
                                sendCommand(39, NULL);
                                break;
                            case 2:
                                if (mpManager->getInputForm()->canConvert())
                                    sendCommand(40, NULL);
                                else
                                    sendInputWChar(L' ', false);
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
                            case 10:
                                changePredictLanguage();
                                break;
                            case 14:
                                changeAIUInputMode(IM_04);
                                break;
                            case 15: {
                                TranslateMode mode = TM_Direct;
                                sendCommand(18, &mode);
                                setTranslateMode(TM_Direct);
                                break;
                            }
                            case 16: {
                                struct TranslateCommand {
                                    TranslateMode mode;
                                };
                                TranslateCommand command = {TM_Roman};
                                sendCommand(18, &command);
                                setTranslateMode(TM_Roman);
                                break;
                            }
                            case 17: {
                                struct TranslateCommand {
                                    TranslateMode mode;
                                };
                                TranslateCommand command = {TM_Kana};
                                sendCommand(18, &command);
                                setTranslateMode(TM_Kana);
                                break;
                            }
                            case 18:
                                mKeyState.setAIUMode(0);
                                break;
                            case 19:
                                mKeyState.setAIUMode(1);
                                break;
                            case 20:
                                if (mKeyState.aiuFlags & 32)
                                    sendCommand(25, NULL);
                                break;
                            case 21:
                                if (mKeyState.aiuFlags & 64)
                                    sendCommand(26, NULL);
                                break;
                            case 22:
                                if (mKeyState.aiuFlags & 128)
                                    sendCommand(28, NULL);
                                break;
                        }
                    } else {
                        inputCharCode(code);
                    }
                }
            }

            void Base::goSignInputMode() {
            }

            void Base::changePredictLanguage() {
            }

            void Base::updateFromReceiver(u32 command, void* data) {
                if (command == 31)
                    return;
                CommandReceiver::ChangePredictMode mode = {0, false};
                sendCommand(31, &mode);
                if (command != 25 && command != 26 && command != 28 && command != 24 && command != 20 && command != 19 && command != 35 ||
                    command == 36) {
                    if (mKeyState.aiuFlags & ~15) {
                        mKeyState.aiuFlags &= 15;
                        mKeyState.refresh_();
                    }
                }
                if (command == 36)
                    mState.rejected = true;
            }

            void Base::onActive() {
                TranslateMode mode = Base::getTranslateMode();
                sendCommand(18, &mode);
                sendCommand(39, NULL);
                if (mKeyState.inputType == 0) {
                    struct RomanMode {
                        bool enabled;
                    };
                    RomanMode roman;
                    switch (Base::getTranslateMode()) {
                        case TM_Roman:
                            roman.enabled = true;
                            break;
                        case TM_Kana:
                            roman.enabled = false;
                            break;
                        default:
                            goto updateFix;
                    }
                    sendCommand(19, &roman);
                } else {
                    struct HiraganaMode {
                        bool enabled;
                    };
                    HiraganaMode hiragana;
                    switch (Base::getAIUInputMode()) {
                        case IM_Hiragana:
                            hiragana.enabled = true;
                            break;
                        case IM_Katakana:
                            hiragana.enabled = false;
                            break;
                        default:
                            goto updateFix;
                    }
                    sendCommand(19, &hiragana);
                }
            updateFix:
                updateFixMode();
            }

            void Base::onClose() {
            }

            wchar_t Base::getWCCode(char* paneName) {
                return mKeyState.getWCCode(paneName);
            }

            u32 Base::getControlKey(char* paneName) {
                for (u16 i = 0; i < 23; i++) {
                    if (util::strcmp(mKeyState.data->controls[i].paneName, paneName))
                        return mKeyState.data->controls[i].key;
                }
                return 27;
            }

            void Base::changeABCInputMode(InputMode mode) {
                switch (mode) {
                    case IM_Direct:
                        mKeyState.setABCMode(0);
                        break;
                    case IM_Hiragana:
                        mKeyState.setABCMode(1);
                        break;
                    case IM_Katakana:
                        mKeyState.setABCMode(2);
                        break;
                }
            }

            void Base::changeAIUInputMode(InputMode mode) {
                switch (mode) {
                    case IM_Hiragana:
                        mKeyState.setAIUMode(0);
                        break;
                    case IM_Katakana:
                        mKeyState.setAIUMode(1);
                        break;
                }
            }

            void Base::sendInputWChar(wchar_t code, bool repeat) {
                struct InputCharacter {
                    wchar_t code;
                    wchar_t reserved;
                    u32 flags;
                    u32 count;
                    u32 type;
                };
                mState.rejected = false;
                u32 flags = 0;
                if (mKeyState.abcFlags & 64)
                    flags |= 2;
                if (mKeyState.abcFlags & 128)
                    flags |= 1;
                InputCharacter input = {code, 0, flags, 0x10000, 0};
                sendCommand(0, &input);
                if (mKeyState.abcFlags & 128) {
                    if (!LayoutGather::Singleton::getInstance().isHoldingShift() && (mKeyState.abcFlags & ~15)) {
                        mKeyState.abcFlags &= ~128;
                        mKeyState.refresh_();
                    }
                }
                if (!mState.rejected) {
                    u32 conversions = 0;
                    if (code != util::KBD_ConvertDakuten(code))
                        conversions |= 32;
                    if (code != util::KBD_ConvertHandaku(code))
                        conversions |= 64;
                    if (code != util::KBD_ConvertSmall(code))
                        conversions |= 128;
                    if ((mKeyState.aiuFlags & ~15) != conversions) {
                        mKeyState.aiuFlags = (mKeyState.aiuFlags & 15) | (conversions & ~15);
                        mKeyState.refresh_();
                    }
                }
            }

            void Base::setLanguage(Language language) {
                meLanguage = language;
                mKeyState.language = language;
                mKeyState.refresh_();
            }

            void Base::updateFixMode() {
                toolbar::LayoutByNW4R* toolbar = mpManager->getToolBar();
                if (toolbar != NULL && !mpManager->getToolBar()->isQwerty())
                    return;
                switch (getLanguage()) {
                    case JP: {
                        bool direct = false;
                        if (isABC() && (mKeyState.abcFlags & 15) == 0)
                            direct = true;
                        else
                            direct = false;
                        sendCommand(20, &direct);
                        break;
                    }
                }
            }

            bool Base::isABC() {
                return mKeyState.inputType == 0;
            }

            void Base::setABC(bool abc) {
                u32 inputType = !abc;
                if (inputType != mKeyState.inputType) {
                    mKeyState.inputType = inputType;
                    mKeyState.refresh_();
                }
                sendCommand(41, NULL);
            }

            void Base::setTranslateMode(TranslateMode mode) {
                u32 keyMode;
                switch (mode) {
                    case TM_Direct:
                        keyMode = 0;
                        break;
                    case TM_Roman:
                        keyMode = 1;
                        break;
                    case TM_Kana:
                        keyMode = 2;
                        break;
                    default:
                        break;
                }
                if (keyMode != (mKeyState.abcFlags & 15)) {
                    if (getLanguage() == KR || getLanguage() == CN)
                        mpManager->getInputForm()->onCommand(static_cast<CommandReceiver::INPUT_COMMAND>(6), NULL);
                    mKeyState.setABCMode(keyMode);
                    if (getLanguage() == CN && mpManager->getCandidateBox() != NULL)
                        mpManager->getCandidateBox()->checkValidation();
                    TranslateMode inputMode = mode;
                    sendCommand(18, &inputMode);
                    mpInitialLanguageData = &csJapanKanaInput;
                    sendCommand(41, NULL);
                }
            }

            void LayoutByNW4R::setABC(bool abc) {
                changeAnimationAllToNormal();
                if (abc != isABC()) {
                    if (abc) {
                        searchAnmPane("W_JP_Chng_ABC")->changeAnimation(4);
                        searchAnmPane("W_JP_Chng_KANA")->changeAnimation(6);
                    } else {
                        searchAnmPane("W_JP_Chng_ABC")->changeAnimation(6);
                        searchAnmPane("W_JP_Chng_KANA")->changeAnimation(4);
                    }
                }
                Base::setABC(abc);
            }

            void Base::KeyState::refresh_() {
                if (((language != JP && language != KR && language != CN) || owner->mbOnlyQwerty) && (abcFlags & 15) != 0) {
                    abcFlags &= ~15;
                    refresh_();
                }
                if (static_cast<u32>(language - CN) <= 1 && getABCMode() == 2) {
                    if ((abcFlags & 15) != 1) {
                        abcFlags = (abcFlags & ~15) | 1;
                        refresh_();
                    }
                }
                if ((abcFlags & 15) == 0)
                    data = &csLanguageDependencyData[language];
                else if (language == JP)
                    data = &csJapanKanaInput;
                else
                    data = &csLanguageDependencyData[language];
                struct BooleanMode {
                    bool enabled;
                };
                BooleanMode direct;
                BooleanMode roman;
                if (inputType == 0) {
                    switch (static_cast<int>(abcFlags & 15)) {
                        case 0:
                            direct.enabled = true;
                            owner->sendCommand(20, &direct);
                            break;
                        case 1:
                            direct.enabled = false;
                            roman.enabled = true;
                            owner->sendCommand(20, &direct);
                            owner->sendCommand(19, &roman);
                            break;
                        case 2:
                            direct.enabled = false;
                            roman.enabled = false;
                            owner->sendCommand(20, &direct);
                            owner->sendCommand(19, &roman);
                            break;
                    }
                } else {
                    switch (static_cast<int>(aiuFlags & 15)) {
                        case 0:
                            direct.enabled = false;
                            roman.enabled = true;
                            owner->sendCommand(20, &direct);
                            owner->sendCommand(19, &roman);
                            break;
                        case 1:
                            direct.enabled = false;
                            roman.enabled = false;
                            owner->sendCommand(20, &direct);
                            owner->sendCommand(19, &roman);
                            break;
                    }
                }
                if (owner != NULL)
                    owner->refreshState();
            }

            void Base::refreshState() {
            }

            void Base::KeyState::refreshText(nw4r::lyt::Pane* root) {
                for (u16 i = 0; i < 50; i++) {
                    char name[17];
                    util::replaceChar(name, sizeof(name), data->ascii[i].szPaneName, 0, 'T');
                    nw4r::lyt::TextBox* text = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(root->FindPaneByName(name, true));
                    if (text != NULL) {
                        wchar_t caption[2];
                        caption[0] = getWCCode(i);
                        caption[1] = 0;
                        if (language == KR && (abcFlags & 15) == 1) {
                            bool caps = owner->isCapsOn();
                            u32 character = caption[0];
                            if (caps)
                                character = util::reverseLetterCaseW(character);
                            if (character >= L'a' && character <= L'z')
                                character = KOREAN_LOWER[static_cast<wchar_t>(character) - L'a'];
                            else if (character >= L'A' && character <= L'Z')
                                character = KOREAN_UPPER[static_cast<wchar_t>(character) - L'A'];
                            caption[0] = character;
                        }
                        text->SetString(caption);
                    }
                }
                for (u16 i = 0; i < 56; i++) {
                    char name[17];
                    util::replaceChar(name, sizeof(name), data->grid[i].paneName, 0, 'T');
                    nw4r::lyt::TextBox* text = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(root->FindPaneByName(name, true));
                    if (text != NULL) {
                        wchar_t caption[2];
                        caption[0] = data->grid[i].codes[(aiuFlags & 15) == 0 ? 2 : 3];
                        caption[1] = 0;
                        text->SetString(caption);
                    }
                }
            }

            void Base::KeyState::setABCFlag(u32 flags) {
                if ((abcFlags & ~15) != flags) {
                    Base* keyboard = owner;
                    abcFlags = (abcFlags & 15) | (flags & ~15);
                    if (keyboard != NULL)
                        keyboard->refreshState();
                }
            }

            wchar_t Base::KeyState::getWCCode(u32 index) {
                u32 modifiers = 0;
                if (abcFlags & 64)
                    modifiers |= 1;
                if (abcFlags & 128)
                    modifiers |= 2;
                wchar_t code = data->ascii[index].wc[modifiers];
                if (inputType == 0 && getABCMode() == 0) {
                    if (code == 0x3001)
                        code = L',';
                    else if (code == 0x3002)
                        code = L'.';
                    else if (code == 0x30fc)
                        code = L'-';
                    else if (code == 0x300c)
                        code = L'[';
                    else if (code == 0x300d)
                        code = L']';
                } else if (owner->getLanguage() == CN && getABCMode() == 1) {
                    if (code == L'[')
                        code = 0x300a;
                    else if (code == L']')
                        code = 0x300b;
                    else if (code == L'.')
                        code = 0x3002;
                    else if (code == L'\'')
                        code = 0x3001;
                    else if (code == L',')
                        code = 0xff0c;
                    else if (code == L'-')
                        code = 0xff0d;
                    else if (code == L'_')
                        code = 0xff3f;
                    else if (code == L':')
                        code = 0xff1a;
                    else if (code == L';')
                        code = 0xff1b;
                    else if (code == L'!')
                        code = 0xff01;
                    else if (code == L'?')
                        code = 0xff1f;
                    else if (code == L'(')
                        code = 0xff08;
                    else if (code == L')')
                        code = 0xff09;
                }
                return code;
            }

            wchar_t Base::KeyState::getWCCode(char* paneName) {
                wchar_t code = 0;
                for (u16 i = 0; i < 50; i++) {
                    if (util::strcmp(data->ascii[i].szPaneName, paneName))
                        code = getWCCode(i);
                }
                for (u16 i = 0; i < 56; i++) {
                    if (util::strcmp(data->grid[i].paneName, paneName))
                        code = data->grid[i].codes[(aiuFlags & 15) == 0 ? 2 : 3];
                }
                return code;
            }

            void Base::onlyQwerty(bool only) {
                mbOnlyQwerty = only;
                if (getLanguage() == JP) {
                    if (only) {
                        setABC(true);
                        mKeyState.setABCFlag(0);
                        changeABCInputMode(IM_Direct);
                    } else {
                        setABC(false);
                        changeAIUInputMode(IM_Hiragana);
                    }
                }
            }

            void Base::setLangKeyActive(bool active) {
                mbLanguageKeyActive = active;
                if (getLanguage() == KR || getLanguage() == CN) {
                    if (!active) {
                        mKeyState.setABCFlag(0);
                        changeABCInputMode(IM_Direct);
                    }
                }
            }

            LayoutByNW4R::~LayoutByNW4R() {
                mpKeyboardEventHandler->~EventHandler();
                MEMFreeToAllocator(mpAllocator, mpKeyboardEventHandler);
                AnmPane* pane = static_cast<AnmPane*>(nw4r::ut::List_GetFirst(&mAnmPanes));
                while (pane != NULL) {
                    nw4r::ut::List_Remove(&mAnmPanes, pane);
                    pane->destroy(mpAllocator);
                    pane = static_cast<AnmPane*>(nw4r::ut::List_GetFirst(&mAnmPanes));
                }
            }

            UIModePanel::~UIModePanel() {
            }

            UIObj::~UIObj() {
            }

            UIModifierButton::~UIModifierButton() {
            }

            Base::~Base() {
            }

            EventHandler::~EventHandler() {
            }

            inline void UIModifierButton::Create(nw4rmanager::Layout* layout, const char* pane, const char* bounding) {
                gui::PaneManager* manager = layout->getPaneManager();
                mpPaneComponent = manager->searchPaneComponent(pane);
                mpBoundingComponent = manager->searchPaneComponent(bounding);
                mpAnimation = static_cast<AnmPane*>(layout->searchAnmPane(pane));
                mpBoundingComponent->setListener(this);
            }

            void LayoutByNW4R::create(MEMAllocator* allocator) {
                Base::create(allocator);
                void* storage = MEMAllocFromAllocator(allocator, sizeof(EventHandler));
                mpKeyboardEventHandler = new (storage) EventHandler(this);
                nw4rmanager::Layout::createWithEventHandler(allocator, mpKeyboardEventHandler);
                mpPaneManager->setAllComponentTriggerTarget(false);
                mpPaneManager->setAllBoundingBoxComponentTriggerTarget(true);
                createAnmPane_(allocator);
                mShiftButton.Create(this, "P_key_SHIFT", "B_key_SHIFT");
                mCapsButton.Create(this, "P_key_CAPS", "B_key_CAPS");
                mModePanel.Create(this);
                mShiftButton.mpBoundingComponent->setTriggerTarget(true);
                mCapsButton.mpBoundingComponent->setTriggerTarget(true);
                for (u32 i = 0; i < 5; i++)
                    mModePanel.mpBoundingComponents[i]->setTriggerTarget(true);
                init();
                mKeyState.setABCFlag(0);
                changeABCInputMode(IM_Direct);
            }

            void LayoutByNW4R::createAnmPane_(MEMAllocator* allocator) {
                const char* shared;
                for (u16 i = 0; i < 129; i++) {
                    const PaneAnimation& entry = csPaneToAnimation[i];
                    AnmPane* pane = NULL;
                    switch (entry.type) {
                        case 0: {
                            void* storage = MEMAllocFromAllocator(allocator, sizeof(NormalButtonAnmPane));
                            pane = new (storage) NormalButtonAnmPane(getPane(entry.paneName), NULL);
                            break;
                        }
                        case 1: {
                            void* storage = MEMAllocFromAllocator(allocator, sizeof(ShiftCapsAnmPane));
                            pane = new (storage) ShiftCapsAnmPane(getPane(entry.paneName), NULL);
                            break;
                        }
                        case 2: {
                            void* storage = MEMAllocFromAllocator(allocator, sizeof(ToggleButtonAnmPane));
                            pane = new (storage) ToggleButtonAnmPane(getPane(entry.paneName), NULL);
                            break;
                        }
                        case 3: {
                            void* storage = MEMAllocFromAllocator(allocator, sizeof(OnOffButtonAnmPane));
                            pane = new (storage) OnOffButtonAnmPane(getPane(entry.paneName), NULL);
                            break;
                        }
                    }
                    nw4r::ut::List_Append(&mAnmPanes, pane);
                    shared = entry.sharedPane;
                    for (u16 j = 0; j < entry.count; j++) {
                        void* resource = mpMultiArcResourceAccessor->GetResource(0, entry.animations[j]->fileName);
                        AnimTransformPane* transform =
                            static_cast<AnimTransformPane*>(getLayout()->CreateAnimTransform(resource, mpMultiArcResourceAccessor));
                        if (shared == NULL)
                            pane->addAnimation(allocator, entry.animations[j]->id, transform, false, true);
                        else
                            pane->forceAddAnimation(allocator, entry.animations[j]->id, transform, shared, false, true);
                    }
                }
            }

            AnmPane::~AnmPane() {
            }

            void LayoutByNW4R::init() {
                Base::init();
                setLineFeedButton(true);
                setPredictLanguageButton(true);
                setSignWindowButton(true);
                nw4r::math::VEC3 koreanVector;
                nw4r::math::VEC3 chineseVector;
                SelectorPosition koreanTranslation;
                SelectorPosition chineseTranslation;
                chineseTranslation = chinesePosition;
                koreanTranslation = koreanPosition;
                if (meLanguage == CN) {
                    mModePanel.mpEnglishText->GetMaterial()->SetTexture(0, mModePanel.mDirectTexture);
                    mModePanel.mpHangulText->GetMaterial()->SetTexture(0, mModePanel.mPinyinTexture);
                    chineseVector.x = chineseTranslation.coordinates[0];
                    chineseVector.y = chineseTranslation.coordinates[1];
                    chineseVector.z = chineseTranslation.coordinates[2];
                    mModePanel.mpModeSelect->SetTranslate(chineseVector);
                } else if (meLanguage == KR) {
                    mModePanel.mpEnglishText->GetMaterial()->SetTexture(0, mModePanel.mEnglishTexture);
                    mModePanel.mpHangulText->GetMaterial()->SetTexture(0, mModePanel.mHangulTexture);
                    koreanVector.x = koreanTranslation.coordinates[0];
                    koreanVector.y = koreanTranslation.coordinates[1];
                    koreanVector.z = koreanTranslation.coordinates[2];
                    mModePanel.mpModeSelect->SetTranslate(koreanVector);
                }
                searchAnmPane("P_key_SHIFT")->changeAnimation(0);
                searchAnmPane("P_key_CAPS")->changeAnimation(0);
                const VisiblePanes* panes = mpInitialLanguageData->panes;
                for (u16 i = 0; i < panes->visibleCount; i++)
                    setVisible(panes->visible[i], true);
                for (u16 i = 0; i < panes->hiddenCount; i++)
                    setVisible(panes->hidden[i], false);
                if (getLanguage() == JP)
                    setString("T_JP_Chng_sign", langindependent::cLanguageIndependentString[langindependent::LANG_STRID_SIGN_WINDOW][getLanguage()]);
                else
                    setString("T_USEU_Chng_sign",
                              langindependent::cLanguageIndependentString[langindependent::LANG_STRID_SIGN_WINDOW][getLanguage()]);
                setString("T_key_SPACE", langindependent::cLanguageIndependentString[langindependent::LANG_STRID_SPACE][getLanguage()]);
                onlyQwerty(false);
                setLangKeyActive(true);
                CommandReceiver::ChangePredictMode mode = {0, false};
                sendCommand(31, &mode);
                updatePredictLanguage(&mode);
                mpLayout->Animate(0);
                mpLayout->CalculateMtx(mDrawInfo);
                setVisible("T_key_SPACE", true);
                setVisible("T_Gkey_SPACE", true);
                setVisible("P_key_HENKAN", false);
                setVisible("P_Gkey_HENKAN", false);
            }

            void LayoutByNW4R::initLayout() {
                if (getLanguage() == JP) {
                    if (isABC()) {
                        searchAnmPane("W_JP_Chng_ABC")->changeAnimation(5);
                        searchAnmPane("W_JP_Chng_KANA")->changeAnimation(0);
                    } else {
                        searchAnmPane("W_JP_Chng_ABC")->changeAnimation(0);
                        searchAnmPane("W_JP_Chng_KANA")->changeAnimation(5);
                    }
                    if ((mKeyState.aiuFlags & 15) == 0) {
                        searchAnmPane("P_hiragana")->changeAnimation(5);
                        searchAnmPane("P_katakana")->changeAnimation(0);
                    } else {
                        searchAnmPane("P_hiragana")->changeAnimation(0);
                        searchAnmPane("P_katakana")->changeAnimation(5);
                    }
                    if (mKeyState.aiuFlags & 32)
                        searchAnmPane("P_Gkey_dakuten")->changeAnimation(14);
                    else
                        searchAnmPane("P_Gkey_dakuten")->changeAnimation(15);
                    if (mKeyState.aiuFlags & 64)
                        searchAnmPane("P_Gkey_handaku")->changeAnimation(14);
                    else
                        searchAnmPane("P_Gkey_handaku")->changeAnimation(15);
                    if (mKeyState.aiuFlags & 128)
                        searchAnmPane("P_Gkey_komoji")->changeAnimation(14);
                    else
                        searchAnmPane("P_Gkey_komoji")->changeAnimation(15);
                    switch (static_cast<int>(mKeyState.abcFlags & 15)) {
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
                if (getLanguage() == KR || getLanguage() == CN) {
                    switch (mKeyState.abcFlags & 15) {
                        case 0: {
                            searchAnmPane("P_Mode_kr_eng")->changeAnimation(5);
                            searchAnmPane("P_Mode_kr_han")->changeAnimation(0);
                            break;
                        }
                        default: {
                            searchAnmPane("P_Mode_kr_eng")->changeAnimation(0);
                            searchAnmPane("P_Mode_kr_han")->changeAnimation(5);
                            break;
                        }
                    }
                }
                mpLayout->Animate(0);
                mpLayout->CalculateMtx(mDrawInfo);
            }

            void LayoutByNW4R::calc() {
                nw4rmanager::Layout::calc();
                if (mpManager->getInputForm()->canConvert()) {
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

            void LayoutByNW4R::inputCharCode(wchar_t code) {
                sendInputWChar(code, false);
            }

            void LayoutByNW4R::onPressedCaps() {
                LayoutGather& gather = LayoutGather::Singleton::getInstance();
                if (!gather.isHoldingShift()) {
                    if (mKeyState.abcFlags & ~15) {
                        mKeyState.abcFlags &= ~128;
                        mKeyState.refresh_();
                    }
                    if (mShiftButton.mbOn) {
                        mShiftButton.mbOn = false;
                        mShiftButton.mpAnimation->onAnmEvent(static_cast<AnmPane::AnmPaneEvent>(5));
                    }
                }
                u8 caps = !gather.isCapsLock();
                gather.changeCapsLock(caps);
                mKeyState.abcFlags = ((mKeyState.abcFlags ^ 64) & 64) | (mKeyState.abcFlags & ~64);
                mKeyState.refresh_();
                mCapsButton.SetState((mKeyState.abcFlags >> 6) & 1, 11);
                mpEventObserver->onSE(static_cast<sound::SE>(13));
            }

            inline void UIModifierButton::SetState(bool enabled, u32 inactiveAnimation) {
                mbOn = enabled;
                if (mbOn)
                    mpAnimation->onAnmEvent(static_cast<AnmPane::AnmPaneEvent>(10));
                else
                    mpAnimation->onAnmEvent(static_cast<AnmPane::AnmPaneEvent>(inactiveAnimation));
            }

            void LayoutByNW4R::onPressedShift(bool sound) {
                u32 flags = mKeyState.getABCFlag();
                flags |= 128;
                mKeyState.setABCFlag(flags);
                mShiftButton.SetState(true, 5);
                if (sound)
                    mpEventObserver->onSE(static_cast<sound::SE>(13));
            }

            void LayoutByNW4R::onReleasedShift() {
                u32 flags = mKeyState.getABCFlag();
                flags &= ~128;
                mKeyState.setABCFlag(flags);
                if (mShiftButton.mbOn) {
                    mShiftButton.mbOn = false;
                    mShiftButton.mpAnimation->onAnmEvent(static_cast<AnmPane::AnmPaneEvent>(5));
                }
            }

            void LayoutByNW4R::onKey(u32 event, void* data) {
                getWCCode(static_cast<char*>(data));
                if (event == 4 && getWCCode(static_cast<char*>(data)) == 0) {
                    switch (getControlKey(static_cast<char*>(data))) {
                        case 3: {
                            LayoutGather& gather = LayoutGather::Singleton::getInstance();
                            if (!gather.isHoldingShift()) {
                                if (mKeyState.abcFlags & ~15) {
                                    mKeyState.abcFlags &= ~128;
                                    mKeyState.refresh_();
                                }
                                if (mShiftButton.mbOn) {
                                    mShiftButton.mbOn = false;
                                    mShiftButton.mpAnimation->onAnmEvent(static_cast<AnmPane::AnmPaneEvent>(5));
                                }
                            }
                            u8 caps = !gather.isCapsLock();
                            gather.changeCapsLock(caps);
                            mKeyState.abcFlags = ((mKeyState.abcFlags ^ 64) & 64) | (mKeyState.abcFlags & ~64);
                            mKeyState.refresh_();
                            mCapsButton.mbOn = (mKeyState.abcFlags >> 6) & 1;
                            if (mCapsButton.mbOn)
                                mCapsButton.mpAnimation->onAnmEvent(static_cast<AnmPane::AnmPaneEvent>(10));
                            else
                                mCapsButton.mpAnimation->onAnmEvent(static_cast<AnmPane::AnmPaneEvent>(11));
                            mpEventObserver->onSE(static_cast<sound::SE>(13));

                            break;
                        }
                        case 4: {
                            LayoutGather& shiftGather = LayoutGather::Singleton::getInstance();
                            if (mKeyState.abcFlags & ~15) {
                                mKeyState.abcFlags &= ~64;
                                mKeyState.refresh_();
                            }
                            if (mCapsButton.mbOn) {
                                mCapsButton.mbOn = false;
                                mCapsButton.mpAnimation->onAnmEvent(static_cast<AnmPane::AnmPaneEvent>(5));
                            }
                            if (!shiftGather.isHoldingShift()) {
                                mKeyState.abcFlags = ((mKeyState.abcFlags ^ 128) & 128) | (mKeyState.abcFlags & ~128);
                                mKeyState.refresh_();
                            }
                            mShiftButton.mbOn = (mKeyState.abcFlags >> 7) & 1;
                            if (mShiftButton.mbOn)
                                mShiftButton.mpAnimation->onAnmEvent(static_cast<AnmPane::AnmPaneEvent>(10));
                            else
                                mShiftButton.mpAnimation->onAnmEvent(static_cast<AnmPane::AnmPaneEvent>(11));
                            mpEventObserver->onSE(static_cast<sound::SE>(13));
                            break;
                        }
                        case 0:
                            mpEventObserver->onSE(static_cast<sound::SE>(9));
                            break;
                        case 11:
                            if (!isABC()) {
                                mpEventObserver->onSE(static_cast<sound::SE>(13));
                                searchAnmPane("W_JP_Chng_KANA")->changeAnimation(6);
                            }
                            break;
                        case 12:
                            if (isABC()) {
                                mpEventObserver->onSE(static_cast<sound::SE>(13));
                                searchAnmPane("W_JP_Chng_ABC")->changeAnimation(6);
                            }
                            break;
                        case 18:
                            if ((mKeyState.aiuFlags & 15) == 1) {
                                mpEventObserver->onSE(static_cast<sound::SE>(13));
                                searchAnmPane("P_katakana")->changeAnimation(6);
                            }
                            break;
                        case 19:
                            if ((mKeyState.aiuFlags & 15) == 0) {
                                mpEventObserver->onSE(static_cast<sound::SE>(13));
                                searchAnmPane("P_hiragana")->changeAnimation(6);
                            }
                            break;
                        case 15:
                            if ((mKeyState.abcFlags & 15) == 2)
                                searchAnmPane("P_Mode_roma_kata")->changeAnimation(6);
                            if ((mKeyState.abcFlags & 15) == 1) {
                                searchAnmPane("P_Mode_roma_hira")->changeAnimation(6);
                                searchAnmPane("P_Mode_kr_han")->changeAnimation(6);
                            }
                            break;
                        case 16:
                            if ((mKeyState.abcFlags & 15) == 0) {
                                searchAnmPane("P_Mode_direct")->changeAnimation(6);
                                searchAnmPane("P_Mode_kr_eng")->changeAnimation(6);
                            }
                            if ((mKeyState.abcFlags & 15) == 2)
                                searchAnmPane("P_Mode_roma_kata")->changeAnimation(6);
                            break;
                        case 17:
                            if ((mKeyState.abcFlags & 15) == 0)
                                searchAnmPane("P_Mode_direct")->changeAnimation(6);
                            if ((mKeyState.abcFlags & 15) == 1)
                                searchAnmPane("P_Mode_roma_hira")->changeAnimation(6);
                            break;
                    }
                }
                Base::onKey(event, data);
            }

            void LayoutByNW4R::setLanguage(Language language) {
                meLanguage = language;
                mKeyState.language = language;
                mKeyState.refresh_();
                init();
            }

            void LayoutByNW4R::updateFromReceiver(u32 command, void* data) {
                Base::updateFromReceiver(command, data);
                updateDakuten();
                switch (static_cast<int>(command)) {
                    case 29:
                        updatePredictLanguage(static_cast<CommandReceiver::ChangePredictMode*>(data));
                        break;
                }
            }

            void LayoutByNW4R::onActive() {
                Base::onActive();
                nw4rmanager::Layout::init();
                if (mKeyState.aiuFlags & 32)
                    searchAnmPane("P_Gkey_dakuten")->changeAnimation(14);
                else
                    searchAnmPane("P_Gkey_dakuten")->changeAnimation(15);
                if (mKeyState.aiuFlags & 64)
                    searchAnmPane("P_Gkey_handaku")->changeAnimation(14);
                else
                    searchAnmPane("P_Gkey_handaku")->changeAnimation(15);
                if (mKeyState.aiuFlags & 128)
                    searchAnmPane("P_Gkey_komoji")->changeAnimation(14);
                else
                    searchAnmPane("P_Gkey_komoji")->changeAnimation(15);
            }

            void LayoutByNW4R::onClose() {
                initPaneLastDrawReceived();
                cancelStateFocusIn();
            }

            void LayoutByNW4R::throwReleaseForAll() {
                for (AnmPane* pane = static_cast<AnmPane*>(nw4r::ut::List_GetFirst(&mAnmPanes)); pane != NULL;
                     pane = static_cast<AnmPane*>(nw4r::ut::List_GetNext(&mAnmPanes, pane))) {
                    if (pane->getKeyType() == 0)
                        pane->onAnmEvent(AnmPane::PE_2);
                }
            }

            void LayoutByNW4R::cancelStateFocusIn() {
                for (AnmPane* pane = static_cast<AnmPane*>(nw4r::ut::List_GetFirst(&mAnmPanes)); pane != NULL;
                     pane = static_cast<AnmPane*>(nw4r::ut::List_GetNext(&mAnmPanes, pane))) {
                    switch (pane->getKeyType()) {
                        case 0:
                            switch (pane->getState()) {
                                case 1:
                                case 3:
                                case 4:
                                    pane->changeAnimation(2);
                                    break;
                                case 16:
                                    pane->changeAnimation(0);
                                    break;
                            }
                            break;
                        case 1:
                            switch (pane->getState()) {
                                case 1:
                                case 3:
                                case 11:
                                    pane->changeAnimation(2);
                                    break;
                                case 4:
                                case 5:
                                case 8:
                                    pane->changeAnimation(9);
                                    break;
                            }
                            break;
                        case 2:
                            switch (pane->getState()) {
                                case 1:
                                case 3:
                                    pane->changeAnimation(2);
                                    break;
                                case 4:
                                    pane->changeAnimation(5);
                                    break;
                            }
                            break;
                        case 3:
                            switch (pane->getState()) {
                                case 1:
                                case 3:
                                case 4:
                                    pane->changeAnimation(2);
                                    break;
                            }
                            break;
                    }
                }
            }

            void LayoutByNW4R::goSignInputMode() {
                mpSignWindow->open(this, false);
                throwReleaseForAll();
            }

            void LayoutByNW4R::changePredictLanguage() {
                throwReleaseForAll();
                CommandReceiver::ChangePredictMode mode = {0, false};
                sendCommand(31, &mode);
                mpPredictDialog->open(static_cast<inputform::Base::PredictMode>(mode.mode), this);
            }

            void LayoutByNW4R::updatePredictLanguage(CommandReceiver::ChangePredictMode* mode) {
                if (getLanguage() != JP) {
                    if (!mode->enabled) {
                        setVisible("P_prdc_ON", false);
                        setVisible("P_prdc_OFF", true);
                    } else {
                        setVisible("P_prdc_ON", true);
                        setVisible("P_prdc_OFF", false);
                    }
                    static_cast<nw4r::lyt::TextBox*>(getPane("T_USEU_prdc_lang"))->SetString(PREDICT_CAPTIONS[mode->mode]);
                }
            }

            void LayoutByNW4R::sendInputWChar(wchar_t code, bool repeat) {
                bool shift = false;
                nw4r::lyt::Pane* last = NULL;
                if (mKeyState.abcFlags & 128) {
                    last = mAnmPaneFifo.getLast();
                    shift = true;
                }
                Base::sendInputWChar(code, repeat);
                if (shift && last != NULL)
                    setPaneLastDrawReceived(last);
                updateDakuten();
            }

            void LayoutByNW4R::updateDakuten() {
                if (mKeyState.aiuFlags & 32)
                    searchAnmPane("P_Gkey_dakuten")->onAnmEvent(static_cast<AnmPane::AnmPaneEvent>(6));
                else
                    searchAnmPane("P_Gkey_dakuten")->onAnmEvent(static_cast<AnmPane::AnmPaneEvent>(7));
                if (mKeyState.aiuFlags & 64)
                    searchAnmPane("P_Gkey_handaku")->onAnmEvent(static_cast<AnmPane::AnmPaneEvent>(6));
                else
                    searchAnmPane("P_Gkey_handaku")->onAnmEvent(static_cast<AnmPane::AnmPaneEvent>(7));
                if (mKeyState.aiuFlags & 128)
                    searchAnmPane("P_Gkey_komoji")->onAnmEvent(static_cast<AnmPane::AnmPaneEvent>(6));
                else
                    searchAnmPane("P_Gkey_komoji")->onAnmEvent(static_cast<AnmPane::AnmPaneEvent>(7));
            }

            void LayoutByNW4R::setLineFeedButton(bool visible) {
                mbLineFeed = visible;
                setVisible("P_key_LF", mbLineFeed);
                setVisible("P_Gkey_LF", mbLineFeed);
            }

            void LayoutByNW4R::setPredictLanguageButton(bool visible) {
                setVisible("W_USEU_prdc_lang", visible);
            }

            void LayoutByNW4R::setSignWindowButton(bool visible) {
                if (!visible) {
                    setVisible("W_USEU_Chng_sign", visible);
                    setVisible("W_JP_Chng_sign", visible);
                } else {
                    setVisible("W_USEU_Chng_sign", false);
                    setVisible("W_JP_Chng_sign", false);
                    if (getLanguage() == JP)
                        setVisible("W_JP_Chng_sign", true);
                    else
                        setVisible("W_USEU_Chng_sign", true);
                }
            }

            void LayoutByNW4R::onlyQwerty(bool only) {
                Base::onlyQwerty(only);
                if (getLanguage() == JP) {
                    initLayout();
                    bool visible = !only;
                    setVisible("W_JP_Chng_ABC", visible);
                    setVisible("W_JP_Chng_KANA", visible);
                    setVisible("P_Mode_roma_hira", visible);
                    setVisible("P_Mode_roma_kata", visible);
                    setVisible("P_Mode_direct", visible);
                    setVisible("P_romajiBox", visible);
                } else if (getLanguage() == KR || getLanguage() == CN) {
                    if (mpManager->getCandidateBox()->isActive())
                        setLangKeyActive(!only);
                    else
                        setLangKeyActive(false);
                }
            }

            void LayoutByNW4R::setLangKeyActive(bool active) {
                Base::setLangKeyActive(active);
                if (getLanguage() == KR || getLanguage() == CN) {
                    initLayout();
                    setVisible("P_Mode_kr_eng", active);
                    setVisible("P_Mode_kr_han", active);
                    setVisible("P_hangulBox", active);
                    if (getLanguage() == CN) {
                        setVisible("P_key_42", active);
                        setVisible("P_key_43", active);
                    }
                }
            }

            void LayoutByNW4R::setInputModeJP(bool abc, u32 abcMode, u32 aiuMode) {
                setABC(abc);
                mKeyState.setABCMode(abcMode);
                mKeyState.setAIUMode(aiuMode);
                switch (static_cast<int>(abcMode)) {
                    case 0:
                        mpInitialLanguageData = &csLanguageDependencyData[getLanguage()];
                        break;
                    case 1:
                        mpInitialLanguageData = &csJapanKanaInput;
                        break;
                    case 2:
                        mpInitialLanguageData = &csJapanKanaInput;
                        break;
                }
                initLayout();
                sendCommand(41, NULL);
            }

            void LayoutByNW4R::setTranslateMode(TranslateMode mode) {
                u32 oldMode = mKeyState.abcFlags & 15;
                Base::setTranslateMode(mode);
                if (oldMode != (mKeyState.abcFlags & 15)) {
                    mpEventObserver->onSE(static_cast<sound::SE>(13));
                    switch (static_cast<int>(oldMode)) {
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
                        case TM_Direct:
                            searchAnmPane("P_Mode_direct")->onAnmEvent(AnmPane::PE_0);
                            searchAnmPane("P_Mode_kr_eng")->onAnmEvent(AnmPane::PE_0);
                            break;
                        case TM_Roman:
                            searchAnmPane("P_Mode_roma_hira")->onAnmEvent(AnmPane::PE_0);
                            searchAnmPane("P_Mode_kr_han")->onAnmEvent(AnmPane::PE_0);
                            break;
                        case TM_Kana:
                            searchAnmPane("P_Mode_roma_kata")->onAnmEvent(AnmPane::PE_0);
                            break;
                    }
                }
            }

            bool LayoutByNW4R::updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data) {
                bool handled = nw4rmanager::Layout::updateInput(chan, x, y, trig, hold, release, data);
                LayoutGather& gather = LayoutGather::Singleton::getInstance();
                bool wasShift = gather.isHoldingShift();
                if (!(!(hold & 0x400))) {
                    gather.setPressedShiftB(true);
                    input::HKBManager::getInstance().SetForceModifierState(2, 2);
                    if (!wasShift) {
                        bool sound = isABC();
                        onPressedShift(sound);
                    }
                } else {
                    gather.setPressedShiftB(false);
                    input::HKBManager::getInstance().SetForceModifierState(0, 0);
                    if (wasShift && !gather.isHoldingShift())
                        onReleasedShift();
                }
                return handled;
            }

            bool LayoutByNW4R::updateInput(input::HKBManager& hkb) {
                input::HKBManager::KeySet keys = hkb.GetTriggeredKeySet();
                while (keys.IsValid()) {
                    nw4rmanager::AnmPane* animation = NULL;
                    u8 key = keys.GetKey();
                    wchar_t code = keys.GetWChar();
                    switch (static_cast<int>(key)) {
                        case 0x2c:
                            break;
                        case 0x28:
                        case 0x58:
                            if (!(hkb.GetModifierState() & 4))
                                animation = searchAnmPane("P_key_LF");
                            break;
                        default: {
                            code = inputform::DeadKeyStream::ToIndependentClass(code);
                            code = static_cast<const Manager*>(mpManager)->getHWKeyboard()->convertWCCode(code);
                            if (static_cast<const Manager*>(mpManager)->getToolBar()->isQwerty()) {
                                if (static_cast<const Manager*>(mpManager)->getPCKeyboard()->getTranslateMode() != TM_Direct &&
                                    mpManager->getLanguage() == KR) {
                                    bool caps = isCapsOn();
                                    u32 koreanCode = code;
                                    if (caps)
                                        koreanCode = util::reverseLetterCaseW(koreanCode);
                                    if (koreanCode >= L'a' && koreanCode <= L'z')
                                        koreanCode = KOREAN_LOWER[static_cast<u16>(koreanCode) - L'a'];
                                    else if (koreanCode >= L'A' && koreanCode <= L'Z')
                                        koreanCode = KOREAN_UPPER[static_cast<u16>(koreanCode) - L'A'];
                                    code = koreanCode;
                                }
                            }
                            animation = searchAnmPane(code);
                            break;
                        }
                    }
                    if (animation != NULL)
                        animation->onAnmEvent(nw4rmanager::AnmPane::PE_0);
                    keys = keys.GetNext();
                }
                keys = hkb.GetRepeatedKeySet();
                while (keys.IsValid()) {
                    nw4rmanager::AnmPane* animation = NULL;
                    u8 key = keys.GetKey();
                    keys.GetWChar();
                    switch (static_cast<int>(key)) {
                        case 0x2a:
                            if (hkb.GetModifierState() & 4)
                                break;
                        case 0x4c:
                            animation = searchAnmPane("P_key_DELETE");
                            break;
                        case 0x2c:
                            if (!(hkb.GetModifierState() & 8))
                                animation = searchAnmPane("P_key_SPACE");
                            break;
                    }
                    if (animation != NULL)
                        animation->onAnmEvent(nw4rmanager::AnmPane::PE_0);
                    keys = keys.GetNext();
                }
                return false;
            }

            void LayoutByNW4R::changeAnimationAllToNormal() {
                for (AnmPane* pane = static_cast<AnmPane*>(nw4r::ut::List_GetFirst(&mAnmPanes)); pane != NULL;
                     pane = static_cast<AnmPane*>(nw4r::ut::List_GetNext(&mAnmPanes, pane))) {
                    if (pane->getKeyType() == 0)
                        pane->changeAnimation(0);
                }
                if ((mKeyState.aiuFlags & 15) == 0) {
                    searchAnmPane("P_hiragana")->changeAnimation(5);
                    searchAnmPane("P_katakana")->changeAnimation(0);
                } else {
                    searchAnmPane("P_hiragana")->changeAnimation(0);
                    searchAnmPane("P_katakana")->changeAnimation(5);
                }
            }

            void LayoutByNW4R::refreshState() {
                bool visible;
                if (isABC()) {
                    if (isVisible("N_VK_grid", &visible))
                        visible = visible != false;
                    else
                        visible = false;
                    setVisible("N_VK_grid", false);
                    setVisible("N_VK_grd_Bnd_ALL", false);
                    setVisible("N_VK_ascii", true);
                    setVisible("N_VK_asc_Bnd_ALL", true);
                } else {
                    if (isVisible("N_VK_grid", &visible))
                        visible = visible != true;
                    else
                        visible = false;
                    setVisible("N_VK_grid", true);
                    setVisible("N_VK_grd_Bnd_ALL", true);
                    setVisible("N_VK_ascii", false);
                    setVisible("N_VK_asc_Bnd_ALL", false);
                }
                mKeyState.refreshText(mpLayout->GetRootPane());
                if (getLanguage() == JP) {
                    if ((mKeyState.aiuFlags & 15) == 0)
                        static_cast<nw4r::lyt::TextBox*>(getPane("T_JP_Chng_KANA"))->SetString(L"あいう");
                    else if ((mKeyState.aiuFlags & 15) == 1)
                        static_cast<nw4r::lyt::TextBox*>(getPane("T_JP_Chng_KANA"))->SetString(L"アイウ");
                }
                if (!isShiftOn() && mShiftButton.mbOn) {
                    mShiftButton.mbOn = false;
                    mShiftButton.mpAnimation->onAnmEvent(static_cast<AnmPane::AnmPaneEvent>(5));
                }
                if (!isCapsOn()) {
                    if (mCapsButton.mbOn) {
                        mCapsButton.mbOn = false;
                        mCapsButton.mpAnimation->onAnmEvent(static_cast<AnmPane::AnmPaneEvent>(5));
                    }
                    LayoutGather::Singleton::getInstance().changeCapsLock(0);
                }
                if (visible)
                    initPaneLastDrawReceived();
            }

            bool Base::isShiftOn() const {
                return (mKeyState.abcFlags >> 7) & 1;
            }

            void LayoutByNW4R::onEvent(UIObj*, u32 event, void* data) {
                if (event == 0)
                    mpEventObserver->onSE(static_cast<sound::SE>(reinterpret_cast<u32>(data)));
            }

            void EventHandler::onTiEvent(gui::PaneComponent* component, u32 event, Input* input) {
                nw4r::lyt::Pane* pane = component->getPane();
                const char* name = pane->GetName();
                if (!util::strcmp("B_key_SHIFT", name)) {
                    switch (util::strcmp("B_key_CAPS", name)) {
                        case 0:
                            if (name[0] == 'B') {
                                char animationName[17];
                                util::replaceChar(animationName, sizeof(animationName), name, 0, 'P');
                                if (strncmp(name + 5, "Chng", 4) == 0 || strncmp(name + 7, "Chng", 4) == 0 || strncmp(name + 7, "prdc", 4) == 0) {
                                    util::replaceChar(animationName, sizeof(animationName), name, 0, 'W');
                                }
                                nw4rmanager::AnmPane* animation = mpKeyboard->searchAnmPane(animationName);
                                switch (static_cast<int>(event)) {
                                    case 4:
                                        if (input->field_0x0C & 0x800) {
                                            if (animation != NULL)
                                                animation->onAnmEvent(nw4rmanager::AnmPane::PE_0);
                                            mpKeyboard->onKey(4, animationName);
                                        }
                                        break;
                                    case 1:
                                        if (animation != NULL)
                                            animation->onAnmEvent(nw4rmanager::AnmPane::PE_2);
                                        mpKeyboard->onKey(1, animationName);
                                        break;
                                    case 0:
                                        if (animation != NULL) {
                                            mpEventObserver->onSE(static_cast<sound::SE>(4));
                                            mpKeyboard->setPaneLastDrawReceived(animation->getPane());
                                            animation->onAnmEvent(nw4rmanager::AnmPane::PE_1);
                                        }
                                        break;
                                }
                                if (event == 2 && (input->field_0x10 & 0x800) && !(input->field_0x0C & 0x800) &&
                                    (util::strcmp("P_key_DELETE", animationName) || util::strcmp("P_Gkey_DELETE", animationName) ||
                                     util::strcmp("P_key_SPACE", animationName) || util::strcmp("P_Gkey_SPACE", animationName)) &&
                                    component->isDragging(input->field_0x00)) {
                                    u32 frames = mpKeyboard->getFlightDuration(input->field_0x00, name);
                                    if (frames >= 30 && frames % 9 == 0) {
                                        animation->onAnmEvent(nw4rmanager::AnmPane::PE_0);
                                        mpKeyboard->onKey(4, animationName);
                                    }
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
            }

            void AnmPane::changeAnimation(u32 animation) {
                mAnimation = animation;
                nw4rmanager::AnmPane::changeAnimation(animation == 16 ? 2 : animation);
            }

            void NormalButtonAnmPane::onAnmEvent(AnmPaneEvent event) {
                switch (mAnimation) {
                    case 0:
                        if (event == 1) {
                            changeAnimation(1);
                        }
                        if (event == 0) {
                            changeAnimation(0x10);
                        }
                        break;
                    case 1:
                        if (event == 4) {
                            changeAnimation(3);
                        }
                        if (event == 2) {
                            changeAnimation(2);
                        }
                        if (event == 0) {
                            changeAnimation(4);
                        }
                        break;
                    case 3:
                        if (event == 2) {
                            changeAnimation(2);
                        }
                        if (event == 0) {
                            changeAnimation(4);
                        }
                        break;
                    case 2:
                        if (event == 4) {
                            changeAnimation(0);
                        }
                        if (event == 1) {
                            changeAnimation(1);
                        }
                        if (event == 0) {
                            changeAnimation(0x10);
                        }
                        break;
                    case 4:
                        if (event == 4) {
                            changeAnimation(3);
                        }
                        if (event == 2) {
                            changeAnimation(2);
                        }
                        if (event == 0) {
                            changeAnimation(4);
                        }
                        break;
                    case 0x10:
                        if (event == 4) {
                            changeAnimation(0);
                        }
                        if (event == 1) {
                            changeAnimation(1);
                        }
                        if (event == 0) {
                            changeAnimation(0x10);
                        }
                }
                return;
            }

            bool ShiftCapsAnmPane::isFocused() const {
                switch (mAnimation) {
                    case 0:
                    case 2:
                    case 6:
                    case 9:
                    case 10:
                        return false;
                    default:
                        return true;
                }
            }

            void ShiftCapsAnmPane::onAnmEvent(AnmPaneEvent event) {
                int state;
                bool focused;

                if (event == 10) {
                    mbOn = 1;
                    switch (mAnimation) {
                        case 0:
                        case 2:
                        case 6:
                        case 9:
                        case 10:
                            focused = false;
                            break;
                        default:
                            focused = true;
                    }
                    if (!focused) {
                        changeAnimation(9);
                    } else {
                        changeAnimation(4);
                    }
                } else if (event == 0xb) {
                    mbOn = 0;
                    switch (mAnimation) {
                        case 0:
                        case 2:
                        case 6:
                        case 9:
                        case 10:
                            focused = false;
                            break;
                        default:
                            focused = true;
                    }
                    if (!focused) {
                        changeAnimation(2);
                    } else {
                        changeAnimation(0xb);
                    }
                } else if (event == 5) {
                    state = mAnimation;
                    mbOn = 0;
                    if (state != 9) {
                        if (state == 10) {
                            changeAnimation(6);
                        } else if ((state == 8) || (state - 4U <= 1)) {
                            changeAnimation(3);
                        }
                    }
                } else if (mbOn == '\0') {
                    switch (mAnimation) {
                        case 9:
                            if (event == 4) {
                                changeAnimation(0);
                            }
                            break;
                        case 6:
                            if (event == 4) {
                                changeAnimation(0);
                            }
                        case 0:
                            if (event == 1) {
                                changeAnimation(1);
                            }
                            break;
                        case 1:
                            if (event == 4) {
                                changeAnimation(3);
                            }
                            if (event == 2) {
                                changeAnimation(2);
                            }
                            break;
                        case 3:
                            if (event == 2) {
                                changeAnimation(2);
                            }
                            break;
                        case 2:
                            if (event == 4) {
                                changeAnimation(0);
                            }
                            if (event == 1) {
                                changeAnimation(1);
                            }
                            break;
                        case 0xb:
                            if (event == 4) {
                                changeAnimation(3);
                            }
                            if (event == 2) {
                                changeAnimation(2);
                            }
                    }
                } else {
                    switch (mAnimation) {
                        case 6:
                            if (event == 4) {
                                changeAnimation(0);
                            }
                        case 0:
                            if (event == 1) {
                                changeAnimation(1);
                            }
                            if (event == 0) {
                                changeAnimation(9);
                            }
                            break;
                        case 10:
                            if (event == 1) {
                                changeAnimation(8);
                            }
                            break;
                        case 8:
                            if (event == 4) {
                                changeAnimation(5);
                            }
                            if (event == 2) {
                                changeAnimation(9);
                            }
                            break;
                        case 5:
                            if (event == 2) {
                                changeAnimation(9);
                            }
                            break;
                        case 9:
                            if (event == 4) {
                                changeAnimation(10);
                            }
                            if (event == 1) {
                                changeAnimation(8);
                            }
                            break;
                        case 11:
                            break;
                        case 4:
                            if (event == 4) {
                                changeAnimation(5);
                            }
                            if (event == 2) {
                                changeAnimation(9);
                            }
                            break;
                    }
                }
                return;
            }

            void ToggleButtonAnmPane::onAnmEvent(AnmPaneEvent event) {
                if (((event == 0) && (mAnimation != 5)) && (mAnimation != 4)) {
                    changeAnimation(4);
                }
                switch (mAnimation) {
                    case 0:
                        if (event == 1) {
                            changeAnimation(1);
                        }
                        break;
                    case 1:
                        if (event == 4) {
                            changeAnimation(3);
                        }
                        if (event == 2) {
                            changeAnimation(2);
                        }
                        break;
                    case 3:
                        if (event == 2) {
                            changeAnimation(2);
                        }
                        break;
                    case 2:
                        if (event == 4) {
                            changeAnimation(0);
                        }
                        if (event == 1) {
                            changeAnimation(1);
                        }
                        break;
                    case 4:
                        if (event == 4) {
                            changeAnimation(5);
                        }
                        break;
                    case 6:
                        if (event == 4) {
                            changeAnimation(0);
                        }
                }
                return;
            }

            void OnOffButtonAnmPane::onAnmEvent(AnmPaneEvent event) {
                int state;

                if ((((event == 0) && (state = mAnimation, state != 0xf)) && (state != 2)) && (state != 0xd)) {
                    changeAnimation(4);
                } else if (((((event == 6) && (state = mAnimation, state != 0xe)) && ((state != 4 && ((state != 3 && (state != 0xc)))))) &&
                            (state != 1)) &&
                           (state != 2)) {
                    changeAnimation(0xc);
                } else if ((event == 7) && (mAnimation != 0xf)) {
                    changeAnimation(0xd);
                } else {
                    switch (mAnimation) {
                        case 0xc:
                            if (event == 4) {
                                changeAnimation(0xe);
                            }
                            if (event == 1) {
                                changeAnimation(1);
                            }
                            break;
                        case 0xd:
                            if (event == 4) {
                                changeAnimation(0xf);
                            }
                            break;
                        case 0xe:
                            if (event == 1) {
                                changeAnimation(1);
                            }
                            break;
                        case 1:
                            if (event == 4) {
                                changeAnimation(3);
                            }
                            if (event == 2) {
                                changeAnimation(2);
                            }
                            break;
                        case 3:
                            if (event == 2) {
                                changeAnimation(2);
                            }
                            break;
                        case 2:
                            if (event == 4) {
                                changeAnimation(0xe);
                            }
                            if (event == 1) {
                                changeAnimation(1);
                            }
                            break;
                        case 4:
                            if (event == 4) {
                                changeAnimation(3);
                            }
                            if (event == 2) {
                                changeAnimation(2);
                            }
                            break;
                    }
                }
                return;
            }

            UIModifierButton::UIModifierButton(u32 id, LayoutByNW4R* layout, Listener* listener)
                : UIObj(id, layout, listener), mpPaneComponent(NULL), mpBoundingComponent(NULL), mpAnimation(NULL), mbOn(false) {
            }

            void UIModifierButton::onGUIEvent(gui::PaneComponent&, u32 event, nw4rmanager::TiEventHandler::Input* input) {
                const char* name = "P_key_CAPS";
                if (mId == 1)
                    name = "P_key_SHIFT";
                switch (static_cast<int>(event)) {
                    case 4:
                        if (input->field_0x0C & 0x800)
                            mpLayout->onKey(4, const_cast<char*>(name));
                        break;

                    case 1:
                        mpAnimation->onAnmEvent(AnmPane::PE_2);
                        mpLayout->onKey(1, const_cast<char*>(name));
                        break;
                    case 0:
                        if (mpListener != NULL)
                            mpListener->onEvent(this, 0, reinterpret_cast<void*>(4));
                        mpLayout->setPaneLastDrawReceived(mpAnimation->getPane());
                        mpAnimation->onAnmEvent(AnmPane::PE_1);
                        break;
                }
            }

            UIModePanel::UIModePanel(u32 id, LayoutByNW4R* layout, Listener* listener)
                : UIObj(id, layout, listener), mMode(0), mpEnglishText(NULL), mpHangulText(NULL), mpModeSelect(NULL) {
                for (u32 index = 0; index < 5; index++) {
                    mpPaneComponents[index] = NULL;
                    mpBoundingComponents[index] = NULL;
                    mpAnimations[index] = NULL;
                }
            }

            void UIModePanel::Create(nw4rmanager::Layout* layout) {
                const char* paneNames[5] = {"P_Mode_direct", "P_Mode_roma_hira", "P_Mode_roma_kata", "P_Mode_kr_eng", "P_Mode_kr_han"};
                const char* boundingNames[5] = {"B_Mode_direct", "B_Mode_roma_hira", "B_Mode_roma_kata", "B_Mode_kr_eng", "B_Mode_kr_han"};
                gui::PaneManager* manager = layout->getPaneManager();
                for (u32 i = 0; i < 5; i++) {
                    mpPaneComponents[i] = manager->searchPaneComponent(paneNames[i]);
                    mpBoundingComponents[i] = manager->searchPaneComponent(boundingNames[i]);
                    mpAnimations[i] = static_cast<AnmPane*>(layout->searchAnmPane(paneNames[i]));
                    mpBoundingComponents[i]->setListener(this);
                }
                nw4r::lyt::Pane* root = layout->getLayout()->GetRootPane();
                mpEnglishText = root->FindPaneByName("T_Mode_kr_eng", true);
                mpHangulText = root->FindPaneByName("T_Mode_kr_han", true);
                mpModeSelect = root->FindPaneByName("N_modeSelect_kr", true);
                root->FindPaneByName("T_Mode_kr_eng", true)->GetMaterial()->GetTexture(&mEnglishTexture, 0);
                root->FindPaneByName("T_Mode_kr_han", true)->GetMaterial()->GetTexture(&mHangulTexture, 0);
                root->FindPaneByName("T_Mode_direct", true)->GetMaterial()->GetTexture(&mDirectTexture, 0);
                root->FindPaneByName("T_Mode_cn_pinyin", true)->GetMaterial()->GetTexture(&mPinyinTexture, 0);
            }

            void UIModePanel::onGUIEvent(gui::PaneComponent&, u32, nw4rmanager::TiEventHandler::Input*) {
            }

            Base::InputMode Base::getAIUInputMode() const {
                switch (static_cast<int>(mKeyState.aiuFlags & 15)) {
                    case 0:
                        return IM_Hiragana;
                    case 1:
                        return IM_Katakana;
                    default:
                        return IM_Hiragana;
                }
            }

            Base::InputMode Base::getABCInputMode() const {
                return IM_Direct;
            }

            Base::State* Base::getState() {
                return &mState;
            }

            int Base::getType() {
                return 0;
            }

            void LayoutByNW4R::setInputModeCK(u32 mode) {
                setInputModeJP(true, mode, 0);
            }

            void LayoutByNW4R::setSignWindow(signwindow::LayoutByNW4R* window) {
                mpSignWindow = window;
            }

            void LayoutByNW4R::setPredictLanguageDialog(predictlang::LayoutByNW4R* dialog) {
                mpPredictDialog = dialog;
            }

            void AnmPane::init() {
                mAnimation = 0;
            }

            OnOffButtonAnmPane::~OnOffButtonAnmPane() {
            }

            ToggleButtonAnmPane::~ToggleButtonAnmPane() {
            }

            ShiftCapsAnmPane::~ShiftCapsAnmPane() {
            }

            NormalButtonAnmPane::~NormalButtonAnmPane() {
            }

            void UIObj::onEvent(gui::GUIComponent& component, u32 event, void* data) {
                onGUIEvent(static_cast<gui::PaneComponent&>(component), event, static_cast<nw4rmanager::TiEventHandler::Input*>(data));
            }

            void UIObj::onGUIEvent(gui::PaneComponent&, u32, nw4rmanager::TiEventHandler::Input*) {
            }

            void Base::setInputModeCK(u32) {
            }

            void Base::setInputModeJP(bool, u32, u32) {
            }

            SelectorPosition chinesePosition = {{-219.0f, -130.0f, 0.0f}};
            SelectorPosition koreanPosition = {{-209.0f, -90.0f, 0.0f}};

        }
    }
    namespace gui {
        void EventHandler::onEvent(GUIComponent&, u32, void*) {
        }

        void EventHandler::setLatestEventCtrlNo(int ctrlNo) {
            muLatestEventCtrlNo = ctrlNo;
        }

        int EventHandler::getLatestEventCtrlNo() {
            return muLatestEventCtrlNo;
        }
    }
}
