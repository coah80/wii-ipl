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

static inline int GetHostReply(const char* name, s32* rm, SOHostEnt** host) {
    HostReply* reply;
    int length;
    char* request;
    int result;
    int size;
    if (!name) return -28;
    length = strlen(name);
    size = (length + 32) & ~31;
    request = SOiAlloc(12, size);
    reply = SOiGetSysWork()->host;
    if (!request) return -49;
    strcpy(request, name);
    result = IOS_Ioctl(*rm, 17, request, length + 1, reply, 0x460);
    if (result >= 0) {
        int displacement = (int)reply->nameStorage - (int)reply->host.name;
        u8** address = reply->addresses;
        while (*address) { *address += displacement; ++address; }
        reply->host.aliases = (char**)((u8*)reply->host.aliases + displacement);
        *host = &reply->host;
        reply->host.name += displacement;
        reply->host.addrList = (u8**)((u8*)reply->host.addrList + displacement);
    }
    SOiFree(12, request, size);
    return result;
}

SOHostEnt* SOGetHostByName(const char* name) {
    SOHostEnt* host = NULL;
    s32 rm;
    int result;
    if ((result = SOiPrepare(NULL, &rm)) == 0) {
        result = GetHostReply(name, &rm, &host);
        SOiConclude(NULL, result);
    }
    return host;
}

static inline int NameSize(const char* name) {
    if (name == NULL) {
        return 0;
    } else {
        return strlen(name) + 1;
    }
}

static inline int NameLength(const char* name) {
    if (name == NULL) {
        return 0;
    } else {
        return strlen(name);
    }
}

static inline int ServiceSize(const char* node, const char* service) {
    if (service == NULL) {
        return 0;
    } else {
        return strlen(node) + 1;
    }
}

static inline int GetAddressReply(const char* nodeName, const char* servName, const SOAddrInfo* hints,
                                  SOAddrInfo** resultInfo, s32* rm) {
    SOAddrInfo* requestHints;
    AddrInfoRequest* request;
    char* service;
    int nodeLength;
    AddrInfoReply* reply;
    int size;
    char* node;
    int serviceLength;
    int result;
    serviceLength = ServiceSize(nodeName, servName);
    nodeLength = NameSize(nodeName);
    size=(((nodeLength+31)&~31)+((serviceLength+31)&~31)+95)&~31;
    request=SOiAlloc(12,size);
    if(!request) result=-49;
    else {
        reply=SOiAlloc(10,0x840);
        if(!reply) { SOiFree(12,request,size); result=-49; }
        else {
            node=(char*)request->storage;
            service=node+((NameSize(nodeName)+31)&~31);
            requestHints=(SOAddrInfo*)(service+((ServiceSize(nodeName, servName)+31)&~31));
            if(nodeName) strcpy(node,nodeName);
            request->vectors[0].base=nodeName ? (u8*)node : NULL;
            request->vectors[0].length=NameLength(nodeName);
            if(servName) strcpy(service,servName);
            request->vectors[1].base=servName ? (u8*)service : NULL;
            request->vectors[1].length=NameLength(servName);
            if(hints) memcpy(requestHints,hints,32);
            else memset(requestHints,0,32);
            if(requestHints->family==0) requestHints->family=2;
            if(requestHints->family==23) {
                *resultInfo=NULL; result=-68; SOiFree(10,reply,0x840);
            } else {
                request->vectors[2].base=(u8*)requestHints; request->vectors[2].length=32;
                request->vectors[3].base=(u8*)reply; request->vectors[3].length=0x834;
                result=IOS_Ioctlv(*rm,24,3,1,request->vectors);
                if(result>=0) {
                    SOAddrInfo* entry=reply->entries;
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
    return result;
}

int SOGetAddrInfo(const char* nodeName, const char* servName, const SOAddrInfo* hints, SOAddrInfo** resultInfo) {
    s32 rm;
    int result;
    if ((result = SOiPrepare(NULL, &rm)) == 0) {
        result = GetAddressReply(nodeName, servName, hints, resultInfo, &rm);
        result = SOiConclude(NULL, result);
    }
    return result;
}

void SOFreeAddrInfo(SOAddrInfo* head) {
    BOOL enabled=OSDisableInterrupts();
    if(SOiIsInitialized()==1 && head) SOiFree(10,head,0x840);
    OSRestoreInterrupts(enabled);
}
