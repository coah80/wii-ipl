#include <private/nwc24.h>
#include <revolution/nwc24.h>

#include <ctype.h>

char* Mail_strcpy(char* dest, const char* src) {
    char* pDest;
    char cSrc;

    for (pDest = dest; *src != 0; pDest++) {
        cSrc = *src++;
        *pDest = cSrc;
    }
    *pDest = 0;
    return dest;
}

int Mail_strlen(const char* str) {
    int i;
    for (i = 0; *str != 0; i++, str++) {
    }
    return i;
}

int STD_strnlen(const char* str, u32 len) {
    int i;
    for (i = 0; i < len; i++, str++) {
        if (*str == 0) {
            break;
        }
    }
    return i;
}

int Mail_isdigit(int ch) {
    if (ch >= '0' && ch <= '9') {
        return 1;
    }
    return 0;
}

int Mail_tolower(int ch) {
    if (ch >= 'A') {
        if (ch <= 'Z') {
            return ch + 0x20;
        }
    }
    return ch;
}
