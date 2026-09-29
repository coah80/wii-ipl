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

s32 NHTTPi_strToHex(const char* string, s32 length)
{
    s32 result;
    BOOL foundDigit;
    char c;

    if (length > 8)
    {
        return -1;
    }
    if ((length == 8) & (string[0] > '7'))
    {
        return -1;
    }

    result = 0;
    foundDigit = FALSE;
    while (length-- > 0)
    {
        c = ((*string >= 'A') & (*string <= 'Z'))
            ? *string + ('a' - 'A')
            : *string;

        if (c >= '0' && c <= '9')
        {
            result = result * 16 + c - '0';
            foundDigit = TRUE;
        }
        else if (c >= 'a' && c <= 'f')
        {
            result = result * 16 + c - 'a' + 10;
            foundDigit = TRUE;
        }
        else if (foundDigit && (c == ' ' || c == '\0'))
        {
            break;
        }
        else if (!foundDigit && c == ' ')
        {
        }
        else
        {
            return -1;
        }
        string++;
    }

    return result;
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

s32 NHTTPi_intToStr(char* destination, u32 value) {
    u32 scales[9]={1000000000,100000000,10000000,1000000,100000,10000,1000,100,10};
    BOOL started;
    int digit;
    char* output;
    s32 length;
    output = destination;
    length = 0;
    started = FALSE;
    for(digit=0; digit<9; ++digit) {
        if(value>=scales[digit]) {
            u32 quotient=value/scales[digit];
            started=TRUE;
            ++length;
            *output++=quotient+'0';
            value-=quotient*scales[digit];
        } else if(started) { *output++='0'; ++length; }
    }
    destination[length]=value+'0';
    return length+1;
}

s32 NHTTPi_compareToken(const char* left, const char* right) {
    for (;;) {
        int rightCharacter=LowerCase(*right);
        int leftCharacter=LowerCase(*left);
        if(leftCharacter!=rightCharacter) break;
        if(*left==0 || *left==' ') return 0;
        ++left; ++right;
    }
    return -1;
}

s32 NHTTPi_strtonum(const char* string, u32 length) {
    int digits=0;
    s32 value=0;
    while(length--) {
        int character=*string++;
        if(character==' ') continue;
        if((character>='0') & (character<='9')) {
            value=value*10+character-'0';
            ++digits;
            if(digits>9) return -1;
        }
    }
    if(digits==0) return -1;
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
