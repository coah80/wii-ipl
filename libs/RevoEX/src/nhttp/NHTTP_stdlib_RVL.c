#include <revolution/types.h>
#include <string.h>

void* NHTTPi_memcpy(void* destination, const void* source, u32 size) { return memcpy(destination,source,size); }
s32 NHTTPi_strlen(const char* string) { return strlen(string); }
s32 NHTTPi_strcmp(const char* left, const char* right) { return strcmp(left,right); }
void* NHTTPi_memclr(void* destination, u32 size) { return memset(destination,0,size); }

static int LowerCase(int character) {
    if((character>='A') & (character<='Z')) character+=32;
    return character;
}

s32 NHTTPi_strnicmp(const char* left, const char* right, s32 length) {
    while(length>0) {
        int a=*left++, b=*right++;
        if(a==0 || b==0) { if(a==0 && b==0) { length=0; break; } }
        b=LowerCase(b);
        a=LowerCase(a);
        if(a!=b) break;
        --length;
    }
    return length;
}

static BOOL UrlPlain(int character) {
    return (character>='0' && character<='9') || (character>='A' && character<='Z') || (character>='a' && character<='z') || character==' ';
}

s32 NHTTPi_getUrlEncodedSize(const char* string) {
    int character=*string++;
    s32 size=0;
    while(character) {
        if((character>='0' && character<='9') || (character>='A' && character<='Z') || (character>='a' && character<='z') || character==' ') ++size;
        else size+=3;
        character=*string++;
    }
    return size;
}

s32 NHTTPi_getUrlEncodedSize2(const char* string, s32 length) {
    int character=*string++;
    s32 size=0;
    for(; length>0; --length) {
        if((character>='0' && character<='9') || (character>='A' && character<='Z') || (character>='a' && character<='z') || character==' ') ++size;
        else size+=3;
        character=*string++;
    }
    return size;
}

s32 NHTTPi_encodeUrlChar(char* destination, s8 character) {
    if(character==' ') { destination[0]='+'; return 1; }
    if((character>='0' && character<='9') || (character>='A' && character<='Z') || (character>='a' && character<='z')) {
        destination[0]=character; return 1;
    } else {
        int high=(character>>4)&15;
        int low=character&15;
        destination[0]='%';
        destination[1]=high<10 ? high+'0' : high+'A'-10;
        destination[2]=low<10 ? low+'0' : low+'A'-10;
        return 3;
    }
}

s32 NHTTPi_strToHex(const char* string, s32 length) {
    s32 value;
    BOOL started;
    if(length>8) return -1;
    if((length==8) & (*string>'7')) return -1;
    value=0; started=FALSE;
    for(; length>0; --length,++string) {
        u8 rawCharacter = *(const u8*)string;
        s8 character = LowerCase((s8)rawCharacter);
        if(character>='0' && character<='9') { value=(value<<4)+character-'0'; started=TRUE; }
        else if(character>='a' && character<='f') { value=(value<<4)+character-'a'+10; started=TRUE; }
        else {
            if(started && (character==' ' || character==0)) break;
            if(!started && character==' ') continue;
            return -1;
        }
    }
    return value;
}

s32 NHTTPi_strToInt(const char* string, s32 length) {
    s32 value;
    BOOL started;
    if(length>10) return -1;
    value=0; started=FALSE;
    for(; length>0; --length,++string) {
        s8 character=*string;
        s32 previous;
        if(started && (character==' ' || character==0)) break;
        if(!started && character==' ') continue;
        if(character<'0' || character>'9') return -1;
        previous=value;
        value=value*10+character-'0';
        started=TRUE;
        if(previous>value) return -1;
    }
    return value;
}

static inline u32 TakeDecimalDigit(u32* remaining, u32 scale) {
    u32 digit = *remaining / scale;
    *remaining -= digit * scale;
    return digit;
}

s32 NHTTPi_intToStr(char* destination, u32 value) {
    u32 scales[9]={1000000000,100000000,10000000,1000000,100000,10000,1000,100,10};
    int digit;
    BOOL started;
    s32 length;
    length = 0;
    started = FALSE;
    for(digit=0; digit<9; ++digit) {
        if(value>=scales[digit]) {
            u32 quotient=TakeDecimalDigit(&value, scales[digit]);
            started=TRUE;
            destination[length++]=quotient+'0';
        } else if(started) { destination[length++]='0'; }
    }
    destination[length]=value+'0';
    return length+1;
}

s32 NHTTPi_compareToken(const char* left, const char* right) {
    int leftCharacter, rightCharacter;
    s8 leftByte;
    goto loop;
    for (;;) {
        if((s8)*left==0 || (s8)*left==' ') return 0;
        ++left; ++right;
loop:
        rightCharacter=*right + 0x20;
        if(!((*right>='A') & (*right<='Z'))) rightCharacter=*right;
        leftByte=(s8)*left;
        leftCharacter=LowerCase(leftByte);
        if(leftCharacter!=rightCharacter) break;
    }
    return -1;
}

s32 NHTTPi_strtonum(const char* string, u32 length) {
    int character;
    s32 value;
    int digits;
    digits = 0;
    value = 0;
    for (; length != 0; --length, ++string) {
        u8 rawCharacter = *(const u8*)string;
        character = (s8)rawCharacter;
        if (character == ' ') continue;
        if ((character >= '0') & (character <= '9')) {
            value = value * 10 + character - '0';
            ++digits;
            if (digits > 9) return -1;
        }
    }
    if (digits == 0) return -1;
    return value;
}

s32 NHTTPi_Base64Encode(char* destination, const char* source) {
    static char alphabet[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const char* table=alphabet;
    char* output=destination;
    u32 length=strlen(source);
    s32 consumed=0;
    for(; consumed<(s32)length; consumed+=3) {
        output[0]=table[source[0]>>2];
        output[1]=table[((source[0]&3)<<4)+(source[1]>>4)];
        output[2]=table[((source[1]&15)<<2)+(source[2]>>6)];
        output[3]=table[source[2]&63];
        source+=3; output+=4;
    }
    if(consumed==length+1) output[-1]='=';
    else if(consumed==length+2) { output[-2]='='; output[-1]='='; }
    *output=0;
    return strlen(destination);
}
