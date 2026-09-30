#include <internal/locale.h>
#include <limits.h>
#include <stddef.h>

extern int __mbtowc_noconv(wchar_t*, const char*, size_t);
extern int __wctomb_noconv(char*, wchar_t);

struct lconv __lconv = {
    ".",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    "",
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
};

extern const unsigned short __ctype_mapC[256];
extern const unsigned char __upper_mapC[256];
extern const unsigned char __lower_mapC[256];
extern const unsigned short __wctype_mapC[256];
extern const wchar_t __wupper_mapC[256];
extern const wchar_t __wlower_mapC[256];

struct _loc_ctype_cmpt _loc_ctyp_C = {
    "C",
    __ctype_mapC,
    __upper_mapC,
    __lower_mapC,
    __wctype_mapC,
    __wupper_mapC,
    __wlower_mapC,
    __mbtowc_noconv,
    __wctomb_noconv
};

unsigned short char_coll_tableC[96] = {
    1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 17, 18, 19, 20, 21, 22, 23, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65, 67, 69, 71,
    73, 75, 77, 79, 81, 83, 85, 87, 89, 91, 93, 24, 25, 26, 27, 28, 0,  44, 46, 48, 50, 52, 54, 56,
    58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 29, 30, 31, 32, 0,
};

struct _loc_coll_cmpt _loc_coll_C = {
    "C",
    ' ',
    110,
    0,
    char_coll_tableC,
    NULL
};

struct _loc_mon_cmpt _loc_mon_C = {
    "C",
    "",
    "",
    "",
    "",
    "",
    "",
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    "",
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX
};

struct _loc_num_cmpt _loc_num_C = {
    "C",
    ".",
    "",
    ""
};

struct _loc_time_cmpt _loc_tim_C = {
    "C",
    "AM|PM",
    "%a %b %e %T %Y",
    "%I:%M:%S %p",
    "%m/%d/%y",
    "%T",
    "Sun|Sunday|Mon|Monday|Tue|Tuesday|Wed|Wednesday|Thu|Thursday|Fri|Friday|Sat|Saturday",
    "Jan|January|Feb|February|Mar|March|Apr|April|May|May|Jun|June|Jul|July|Aug|August|Sep|September|Oct|October|Nov|"
    "November|Dec|December",
    ""
};

struct __locale _current_locale = {
    NULL,
    "C",
    &_loc_coll_C,
    &_loc_ctyp_C,
    &_loc_mon_C,
    &_loc_num_C,
    &_loc_tim_C
};
