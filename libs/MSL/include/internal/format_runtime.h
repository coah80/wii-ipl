#ifndef MSL_FORMAT_RUNTIME_H
#define MSL_FORMAT_RUNTIME_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <internal/locale.h>
#define SIGDIGLEN 36
#define LDBL_MANT_DIG 53
#define LDBL_MAX_EXP 1024
#define LDBL_MIN_EXP (-1021)
#define DBL_MAX 1.7976931348623157e308
#define DBL_MIN 2.2250738585072014e-308
#define DBL_EPSILON 2.2204460492503131e-16
#define EOF (-1)
typedef long ptrdiff_t;
typedef long long intmax_t;
typedef unsigned long long uintmax_t;
typedef struct {
    char sign;
    short exp;
    struct { unsigned char length; unsigned char text[SIGDIGLEN]; } sig;
} decimal;
typedef struct { char style; short digits; } decform;
enum __ReadProcActions { __GetAChar, __UngetAChar, __TestForError };
typedef struct { char* CharStr; size_t MaxCharCount; size_t CharsWritten; } __OutStrCtrl;
typedef struct { char* NextChar; int NullCharDetected; } __InStrCtrl;
void __num2dec(const decform*, double, decimal*);
double __dec2num(const decimal*);
size_t __fwrite(const void*, size_t, size_t, FILE*);
int __StringRead(void*, int, int);
unsigned long __strtoul(int, int, int (*)(void*, int, int), void*, int*, int*, int*);
unsigned long long __strtoull(int, int, int (*)(void*, int, int), void*, int*, int*, int*);
long double __strtold(int, int (*)(void*, int, int), void*, int*, int*);
int wctomb(char*, wchar_t);
double nan(const char*);
#define signbit(x) __signbitd(x)
#endif
