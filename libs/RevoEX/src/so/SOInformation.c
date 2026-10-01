#include <revolution/soex.h>
#include <revolution/os.h>
#include <private/ios.h>
#include <string.h>

int SOiPrepare(const char*, s32*);
int SOiConclude(const char*, int);
int SOiIsInitialized(void);
void* SOiAlloc(u32, s32);
void SOiFree(u32, void*, s32);

typedef struct HostReply {
    SOHostEnt host;
    char nameStorage[816];
    u8* addresses[72];
} HostReply;

typedef struct SOSysWork {
    SOAlloc alloc;
    SOFree free;
    int rmState;
    int rm;
    HostReply* host;
    int allocations;
} SOSysWork;

SOSysWork* SOiGetSysWork(void);

typedef struct AddrInfoRequest {
    IOSIoVector vectors[4];
    u8 storage[1];
} AddrInfoRequest;

typedef struct AddrInfoReply {
    SOAddrInfo entries[35];
    u8 addresses[980];
} AddrInfoReply;

s32 SOGetHostID(void) {
    s32 rm;
    int result;
    s32 address=0;
    if((result=SOiPrepare(NULL,&rm))==0) {
        address=IOS_Ioctl(rm,16,NULL,0,NULL,0);
        SOiConclude(NULL,result);
    }
    return address;
}

SOHostEnt* SOGetHostByName(const char* name) {
    HostReply* reply;
    int result;
    int size;
    int length;
    SOHostEnt* host;
    s32 rm;
    char* request;
    host = NULL;
    if((result=SOiPrepare(NULL,&rm))==0) {
        if(!name) result=-28;
        else {
            length=strlen(name);
            size=(length+32)&~31;
            request=SOiAlloc(12,size);
            reply=SOiGetSysWork()->host;
            if(!request) result=-49;
            else {
                strcpy(request,name);
                result=IOS_Ioctl(rm,17,request,length+1,reply,0x460);
                if(result>=0) {
                    int displacement=(int)reply->nameStorage-(int)reply->host.name;
                    u8** address=reply->addresses;
                    while(*address) { *address+=displacement; ++address; }
                    reply->host.aliases=(char**)((u8*)reply->host.aliases+displacement);
                    host=&reply->host;
                    reply->host.name+=displacement;
                    reply->host.addrList=(u8**)((u8*)reply->host.addrList+displacement);
                }
                SOiFree(12,request,size);
            }
        }
        SOiConclude(NULL,result);
    }
    return host;
}

static int NameSize(const char* name) { return name ? strlen(name)+1 : 0; }

int SOGetAddrInfo(const char* nodeName, const char* servName, const SOAddrInfo* hints, SOAddrInfo** resultInfo) {
    s32 rm;
    int result,size;
    AddrInfoRequest* request;
    AddrInfoReply* reply;
    char* node;
    char* service;
    SOAddrInfo* requestHints;
    int nodeSize,servSize;
    if((result=SOiPrepare(NULL,&rm))==0) {
        servSize = servName==0 ? 0 : strlen(nodeName)+1;
        nodeSize = nodeName==0 ? 0 : strlen(nodeName)+1;
        size=((nodeSize+31)&~31)+((servSize+31)&~31)+95;
        size&=~31;
        request=SOiAlloc(12,size);
        if(!request) result=-49;
        else {
            reply=SOiAlloc(10,0x840);
            if(!reply) { SOiFree(12,request,size); result=-49; }
            else {
                node=(char*)request->storage;
                service=node+(((nodeName==0 ? 0 : strlen(nodeName)+1)+31)&~31);
                requestHints=(SOAddrInfo*)(service+(((servName==0 ? 0 : strlen(nodeName)+1)+31)&~31));
                if(nodeName) strcpy(node,nodeName);
                request->vectors[0].base=nodeName ? (u8*)node : NULL;
                request->vectors[0].length=nodeName==0 ? 0 : strlen(nodeName);
                if(servName) strcpy(service,servName);
                request->vectors[1].base=servName ? (u8*)service : NULL;
                request->vectors[1].length=servName==0 ? 0 : strlen(servName);
                if(hints) memcpy(requestHints,hints,32);
                else memset(requestHints,0,32);
                if(requestHints->family==0) requestHints->family=2;
                if(requestHints->family==23) {
                    *resultInfo=NULL; result=-68; SOiFree(10,reply,0x840);
                } else {
                    request->vectors[2].base=(u8*)requestHints; request->vectors[2].length=32;
                    request->vectors[3].base=(u8*)reply; request->vectors[3].length=0x834;
                    result=IOS_Ioctlv(rm,24,3,1,request->vectors);
                    if(result>=0) {
                        SOAddrInfo* entry=(SOAddrInfo*)reply;
                        u8* address=reply->addresses;
                        *resultInfo=entry;
                        while(entry) {
                            entry->addr=address;
                            if(entry->next) entry->next=entry+1;
                            entry=entry->next;
                            address+=28;
                        }
                    } else { *resultInfo=NULL; SOiFree(10,reply,0x840); }
                }
                SOiFree(12,request,size);
            }
        }
        result=SOiConclude(NULL,result);
    }
    return result;
}

void SOFreeAddrInfo(SOAddrInfo* head) {
    BOOL enabled=OSDisableInterrupts();
    if(SOiIsInitialized()==1 && head) SOiFree(10,head,0x840);
    OSRestoreInterrupts(enabled);
}
