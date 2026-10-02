#include <revolution/soex.h>
#include <private/ios.h>
#include <string.h>

int SOiPrepare(const char*, s32*);
int SOiConclude(const char*, int);
int SOiPrepareTempRm(const char*, s32*, int*);
int SOiConcludeTempRm(const char*, int, int);
void* SOiAlloc(u32, s32);
void SOiFree(u32, void*, s32);

typedef struct SocketOption {
    int socket;
    int level;
    int option;
    int length;
    u8 value[20];
} SocketOption;

typedef union InterfaceCommand {
    struct { int level; int option; };
    u8 bytes[32];
} InterfaceCommand;

typedef union InterfaceLength {
    int length;
    u8 bytes[32];
} InterfaceLength;

typedef struct InterfaceOption {
    IOSIoVector vectors[4];
    InterfaceCommand command;
    union {
        int length;
        u8 lengthBlock[32];
    };
    u8 value[1];
} InterfaceOption;

typedef struct InterfaceSetting {
    IOSIoVector vectors[4];
    InterfaceCommand command;
    u8 value[1];
} InterfaceSetting;

int SOGetSockOpt(int socket, int level, int option, void* value, int* length) {
    s32 rm;
    int result;
    SocketOption* request;
    if ((result=SOiPrepare(NULL,&rm))==0) {
        request=SOiAlloc(12,32);
        if (!request) result=-49;
        else {
            request->socket=socket; request->level=level; request->option=option;
            result=IOS_Ioctl(rm,8,NULL,0,request,24);
            if(result>=0 && length) {
                if(*length>=request->length) {
                    if(value) memcpy(value,request->value,request->length);
                    *length=request->length;
                } else { *length=request->length; result=-28; }
            }
            SOiFree(12,request,32);
        }
        result=SOiConclude(NULL,result);
    }
    return result;
}

int SOSetSockOpt(int socket, int level, int option, const void* value, int length) {
    s32 rm;
    int result;
    SocketOption* request;
    if ((result=SOiPrepare(NULL,&rm))==0) {
        if(length<0 || length>20) result=-28;
        else {
            request=SOiAlloc(12,64);
            if(!request) result=-49;
            else {
                request->socket=socket; request->level=level; request->option=option; request->length=length;
                if(value) memcpy(request->value,value,length);
                else memset(request->value,0,length);
                result=IOS_Ioctl(rm,9,request,36,NULL,0);
                SOiFree(12,request,64);
            }
        }
        result=SOiConclude(NULL,result);
    }
    return result;
}

static int OptionLength(int* length) {
    int invalid=0;
    if(length==NULL || *length<0) invalid=1;
    if(invalid) return 0;
    return *length;
}

int SOGetInterfaceOpt(void* interface, int level, int option, void* value, int* length) {
    s32 rm;
    int temporary;
    int size;
    int result;
    InterfaceOption* request;
    InterfaceCommand* command;
    int* returnedLength;
    u8* reply;
    if ((result=SOiPrepareTempRm(NULL,&rm,&temporary))==0) {
        if(option==0x1001 || option==0x1002) result=-28;
        else {
            size=(OptionLength(length)+127)&~31;
            request=SOiAlloc(12,size);
            if(!request) result=-49;
            else {
                command=&request->command;
                command->level=level; command->option=option;
                returnedLength=&((InterfaceLength*)(command + 1))->length;
                reply=(u8*)((InterfaceLength*)returnedLength + 1);
                *returnedLength=OptionLength(length);
                request->vectors[0].base=(u8*)command;
                request->vectors[0].length=8;
                request->vectors[1].base=reply;
                request->vectors[1].length=OptionLength(length);
                request->vectors[2].base=(u8*)returnedLength;
                request->vectors[2].length=4;
                result=IOS_Ioctlv(rm,28,1,2,request->vectors);
                if(result>=0 && length) {
                    if(*length>=*returnedLength) {
                        if(value) memcpy(value,reply,*returnedLength);
                        *length=*returnedLength;
                    } else { *length=*returnedLength; result=-28; }
                }
                SOiFree(12,request,size);
            }
        }
        result=SOiConcludeTempRm(NULL,result,temporary);
    }
    return result;
}

int SOSetInterfaceOpt(void* interface, int level, int option, const void* value, int length) {
    s32 rm;
    int temporary;
    int size;
    int result;
    InterfaceSetting* request;
    InterfaceCommand* command;
    u8* reply;
    if ((result=SOiPrepareTempRm(NULL,&rm,&temporary))==0) {
        if(option==0x1001 || option==0x1002 || length<0) result=-28;
        else {
            size=(length+95)&~31;
            request=SOiAlloc(12,size);
            if(!request) result=-49;
            else {
                command=&request->command;
                command->level=level; command->option=option;
                reply=(u8*)(command + 1);
                if(value) memcpy(reply,value,length);
                else memset(reply,0,length);
                request->vectors[0].base=(u8*)command; request->vectors[0].length=8;
                request->vectors[1].base=reply; request->vectors[1].length=length;
                result=IOS_Ioctlv(rm,29,2,0,request->vectors);
                SOiFree(12,request,size);
            }
        }
        result=SOiConcludeTempRm(NULL,result,temporary);
    }
    return result;
}
