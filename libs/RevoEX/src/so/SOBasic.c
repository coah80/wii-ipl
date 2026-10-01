#include <revolution/soex.h>
#include <revolution/os.h>
#include <private/ios.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

int SOiPrepare(const char*, s32*);
int SOiConclude(const char*, int);
int SOiPrepareTempRm(const char*, s32*, int*);
int SOiConcludeTempRm(const char*, int, int);
int SOiIsBufferAddrCheck(void);
void* SOiAlloc(u32, s32);
void SOiFree(u32, void*, s32);

static int soSocketRegistered;
const char* __SOCKETVersion="<< RVL_SDK - SOCKET \trelease build: Dec 12 2008 03:06:17 (0x4199_60831) >>";

typedef struct SocketRequest { int socket; int type; int protocol; } SocketRequest;
typedef struct AddressRequest { int socket; int hasAddress; SOSockAddr address; } AddressRequest;
typedef struct NameRequest {
    union { int socket; u8 socketBlock[32]; };
    SOSockAddr address;
} NameRequest;
typedef struct PollRequest {
    union { s64 timeout; u8 timeoutBlock[32]; };
    SOPollFD fds[1];
} PollRequest;
typedef struct InetRequest {
    union { struct { int family; u8 address[16]; } reply; u8 replyBlock[32]; };
    char text[1];
} InetRequest;
typedef struct RecvRequest {
    IOSIoVector vectors[4];
    union { struct { int socket; int flags; } command; u8 commandBlock[32]; };
    SOSockAddr address;
} RecvRequest;
typedef struct SendRequest {
    IOSIoVector vectors[4];
    struct { int socket; int flags; int hasAddress; SOSockAddr address; } command;
} SendRequest;

static int RecvFrom(const char*, int, void*, int, int, SOSockAddr*);
static int SendTo(const char*, int, const void*, int, int, const SOSockAddr*);

int SOSocket(int family, int type, int protocol) {
    s32 rm;
    SocketRequest* request;
    int result;
    if(!soSocketRegistered) { OSRegisterVersion(__SOCKETVersion); soSocketRegistered=1; }
    if((result=SOiPrepare(NULL,&rm))==0) {
        if(family==23) result=-5;
        else {
            request=SOiAlloc(12,32);
            if(!request) result=-49;
            else {
                request->socket=family; request->type=type; request->protocol=protocol;
                result=IOS_Ioctl(rm,15,request,12,NULL,0);
                SOiFree(12,request,32);
            }
        }
        result=SOiConclude(NULL,result);
    }
    return result;
}

int SOClose(int socket) {
    s32 rm;
    int result;
    SocketRequest* request;
    if((result=SOiPrepare(NULL,&rm))==0) {
        request=SOiAlloc(12,32);
        if(!request) result=-49;
        else {
            request->socket=socket;
            result=IOS_Ioctl(rm,3,request,4,NULL,0);
            SOiFree(12,request,32);
        }
        result=SOiConclude(NULL,result);
    }
    return result;
}

int SOBind(int socket, void* address) {
    SOSockAddr* addr=address;
    s32 rm;
    int result;
    AddressRequest* request;
    if((result=SOiPrepare(NULL,&rm))==0) {
        if(!addr || addr->len>8 || addr->len<8) result=-28;
        else {
            request=SOiAlloc(12,64);
            if(!request) result=-49;
            else {
                request->socket=socket; request->hasAddress=1;
                memcpy(&request->address,addr,addr->len);
                result=IOS_Ioctl(rm,2,request,36,NULL,0);
                SOiFree(12,request,64);
            }
        }
        result=SOiConclude(NULL,result);
    }
    return result;
}

int SOConnect(int socket, void* address) {
    SOSockAddr* addr=address;
    s32 rm;
    int result;
    AddressRequest* request;
    if((result=SOiPrepare(NULL,&rm))==0) {
        if(!addr || addr->len>8 || addr->len<8) result=-28;
        else {
            request=SOiAlloc(12,64);
            if(!request) result=-49;
            else {
                request->socket=socket; request->hasAddress=1;
                memcpy(&request->address,addr,addr->len);
                result=IOS_Ioctl(rm,4,request,36,NULL,0);
                SOiFree(12,request,64);
            }
        }
        result=SOiConclude(NULL,result);
    }
    return result;
}

int SOGetSockName(int socket, void* address) {
    int size;
    int result;
    s32 rm;
    SOSockAddr* addr;
    SOSockAddr* reply;
    NameRequest* request;
    addr=address;
    if((result=SOiPrepare(NULL,&rm))==0) {
        if(!addr || addr->len>8 || addr->len<8) result=-28;
        else {
            size=(addr->len+63)&~31;
            request=SOiAlloc(12,size);
            if(!request) result=-49;
            else {
                request->socket=socket;
                reply=&request->address;
                memcpy(reply,addr,addr->len);
                result=IOS_Ioctl(rm,7,request,4,reply,addr->len);
                if(result>=0) memcpy(addr,reply,reply->len);
                SOiFree(12,request,size);
            }
        }
        result=SOiConclude(NULL,result);
    }
    return result;
}

int SORecvFrom(int socket, void* data, int length, int flags, void* address) { return RecvFrom(NULL,socket,data,length,flags,address); }
int SORecv(int socket, void* data, int length, int flags) { return RecvFrom(NULL,socket,data,length,flags,NULL); }
int SORead(int socket, void* data, int length) { return RecvFrom(NULL,socket,data,length,0,NULL); }
int SOSendTo(int socket, const void* data, int length, int flags, const void* address) { return SendTo(NULL,socket,data,length,flags,address); }
int SOSend(int socket, const void* data, int length, int flags) { return SendTo(NULL,socket,data,length,flags,NULL); }

int SOFcntl(int socket, int command, ...) {
    va_list args;
    s32 rm;
    int result,value;
    SocketRequest* request;
    va_start(args,command);
    value=va_arg(args,int);
    va_end(args);
    if((result=SOiPrepare(NULL,&rm))==0) {
        request=SOiAlloc(12,32);
        if(!request) result=-49;
        else {
            request->socket=socket; request->type=command; request->protocol=value;
            result=IOS_Ioctl(rm,5,request,12,NULL,0);
            SOiFree(12,request,32);
        }
        result=SOiConclude(NULL,result);
    }
    return result;
}

int SOShutdown(int socket, int how) {
    s32 rm;
    int result;
    SocketRequest* request;
    if((result=SOiPrepare(NULL,&rm))==0) {
        request=SOiAlloc(12,32);
        if(!request) result=-49;
        else {
            request->socket=socket; request->type=how;
            result=IOS_Ioctl(rm,14,request,8,NULL,0);
            SOiFree(12,request,32);
        }
        result=SOiConclude(NULL,result);
    }
    return result;
}

int SOPoll(SOPollFD* fds, unsigned int count, s64 timeout) {
    s32 size;
    s32 bytes;
    s32 result;
    s32 rm;
    PollRequest* request;
    SOPollFD* reply;
    if((result=SOiPrepare(NULL,&rm))==0) {
        if(!fds) result=-28;
        else {
            bytes=count*12; size=(bytes+63)&~31;
            request=SOiAlloc(12,size);
            if(!request) result=-49;
            else {
                reply=request->fds;
                if(timeout<=-1) memcpy(&request->timeout,&timeout,8);
                else request->timeout=timeout/((__OSBusClock/4)/1000);
                memcpy(reply,fds,bytes);
                result=IOS_Ioctl(rm,11,request,8,reply,bytes);
                if(result>=0) memcpy(fds,reply,bytes);
                SOiFree(12,request,size);
            }
        }
        result=SOiConclude(NULL,result);
    }
    return result;
}

int SOInetAtoN(const char* text, SOInAddr* address) {
    s32 rm;
    int temporary,size,result;
    InetRequest* request;
    char* input;
    if((result=SOiPrepareTempRm(NULL,&rm,&temporary))==0) {
        if(!text) result=-28;
        else {
            size=(strlen(text)+64)&~31;
            request=SOiAlloc(12,size);
            if(!request) result=-49;
            else {
                input=request->text;
                if(text) strcpy(input,text);
                result=IOS_Ioctl(rm,21,input,strlen(text),request,4);
                if(result>=0 && address) memcpy(address,request,4);
                SOiFree(12,request,size);
            }
        }
        result=SOiConcludeTempRm(NULL,result,temporary);
    }
    return result;
}

char* SOInetNtoA(SOInAddr address) {
    static char ascii[40];
    const u8* bytes=(const u8*)&address;
    sprintf(ascii,"%d.%d.%d.%d",bytes[0],bytes[1],bytes[2],bytes[3]);
    return ascii;
}

int SOInetPtoN(int family, const char* text, void* address) {
    s32 rm;
    int temporary,result,size,bytes;
    InetRequest* request;
    if((result=SOiPrepareTempRm(NULL,&rm,&temporary))==0) {
        bytes=0;
        if(family==2) bytes=4;
        if(!bytes) result=-5;
        else if(!text) result=-28;
        else {
            size=(strlen(text)+64)&~31;
            request=SOiAlloc(12,size);
            if(!request) result=-49;
            else {
                strcpy(request->text,text);
                request->reply.family=family;
                memset(request->reply.address,0,bytes);
                result=IOS_Ioctl(rm,22,(void*)text,strlen(text)+1,request,20);
                if(result>=0 && address) memcpy(address,request->reply.address,bytes);
                SOiFree(12,request,size);
            }
        }
        result=SOiConcludeTempRm(NULL,result,temporary);
    }
    return result;
}

u32 SONtoHl(u32 value) { return value; }
u16 SONtoHs(u16 value) { return value; }
u32 SOHtoNl(u32 value) { return value; }
u16 SOHtoNs(u16 value) { return value; }

static inline int DirectBuffer(const void* data, int length) {
    BOOL direct=FALSE;
    BOOL aligned=FALSE;
    if(((u32)data&31)==0 && length%32==0) aligned=TRUE;
    if(aligned) {
        BOOL accessible=TRUE;
        if(SOiIsBufferAddrCheck()) {
            BOOL inMemory=FALSE;
            if(((u32)data&0x1fffffff)>=0x10000000 && ((u32)data&0x1fffffff)<0x18000000) inMemory=TRUE;
            if(!inMemory) accessible=FALSE;
        }
        if(accessible) direct=TRUE;
    }
    return direct;
}

static int RecvFrom(const char* name, int socket, void* data, int length, int flags, SOSockAddr* address) {
    s32 rm;
    int result,size;
    BOOL direct;
    RecvRequest* request;
    void* buffer;
    SOSockAddr* reply;
    if(length>32768) length=32768;
    if((result=SOiPrepare(name,&rm))==0) {
        if(address && (address->len>8 || address->len<8)) result=-28;
        else if(length<0 || (length>0 && !data)) result=-28;
        else {
            direct=TRUE;
            if(length && !DirectBuffer(data,length)) direct=FALSE;
            size=((address ? address->len : 0)+95)&~31;
            request=SOiAlloc(12,size);
            if(!direct) buffer=SOiAlloc(13,(length+31)&~31);
            else buffer=data;
            if(!request || !buffer) result=-49;
            else {
                request->command.socket=socket; request->command.flags=flags;
                reply=&request->address;
                request->vectors[0].base=(u8*)&request->command; request->vectors[0].length=8;
                request->vectors[1].base=buffer; request->vectors[1].length=length;
                if(!address) {
                    request->vectors[2].base=NULL; request->vectors[2].length=0;
                    result=IOS_Ioctlv(rm,12,1,2,request->vectors);
                } else {
                    memcpy(reply,address,address->len);
                    request->vectors[2].base=(u8*)reply; request->vectors[2].length=address->len;
                    result=IOS_Ioctlv(rm,12,1,2,request->vectors);
                    if(result>=0) {
                        u32 bytes=address->len;
                        if(bytes>reply->len) bytes=reply->len;
                        memcpy(address,reply,bytes);
                    }
                }
                if(result>=0 && !direct) memcpy(data,buffer,length);
            }
            if(!direct) SOiFree(13,buffer,(length+31)&~31);
            SOiFree(12,request,size);
        }
        result=SOiConclude(name,result);
    }
    return result;
}

static int SendTo(const char* name, int socket, const void* data, int length, int flags, const SOSockAddr* address) {
    BOOL direct;
    int result;
    s32 rm;
    void* buffer;
    SendRequest* request;
    if((result=SOiPrepare(name,&rm))==0) {
        if(address && (address->len>8 || address->len<8)) result=-28;
        else if(length<0 || (length>0 && !data)) result=-28;
        else {
            direct=TRUE;
            if(length && !DirectBuffer(data,length)) direct=FALSE;
            request=SOiAlloc(12,96);
            if(!direct) buffer=SOiAlloc(14,(length+31)&~31);
            else buffer=(void*)data;
            if(!request || !buffer) result=-49;
            else {
                request->command.socket=socket; request->command.flags=flags;
                if(!address) request->command.hasAddress=0;
                else {
                    request->command.hasAddress=1;
                    memcpy(&request->command.address,address,address->len);
                }
                if(!direct) memcpy(buffer,data,length);
                request->vectors[0].base=buffer; request->vectors[0].length=length;
                request->vectors[1].base=(u8*)&request->command; request->vectors[1].length=40;
                result=IOS_Ioctlv(rm,13,2,0,request->vectors);
            }
            if(!direct) SOiFree(14,buffer,(length+31)&~31);
            SOiFree(12,request,96);
        }
        result=SOiConclude(name,result);
    }
    return result;
}
