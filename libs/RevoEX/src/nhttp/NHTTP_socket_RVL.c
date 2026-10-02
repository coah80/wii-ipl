#include <private/nhttp.h>
#include <revolution/ncd.h>
#include <revolution/soex.h>

struct NHTTPBgnEndInfo {
    NCDIpConfig ipConfig;
    NHTTPAlloc alloc;
    NHTTPFree free;
    BOOL started;
    s32 socket;
    s32 sslError;
    NHTTPErr error;
    u32 stop;
    void* threadStack;
    void (*sslInit)(SSLId, void*);
};

void NHTTPi_lockReqList(void*);
void NHTTPi_unlockReqList(void*);
void NHTTPi_SetSSLError(NHTTPBgnEndInfo*, s32);
NHTTPConnectionInfo* NHTTPi_Request2Connection(void*, NHTTPRequestInfo*);
void* NHTTPi_memcpy(void*, const void*, u32);
void* NHTTPi_memclr(void*, u32);
s32 NHTTPi_SocSSLConnect(NHTTPBgnEndInfo*, void*, NHTTPRequestInfo*, s32);

s32 NHTTPi_SocOpen(NHTTPRequestInfo* request) {
    s32 socket=__SOCreateSocket(2,1,0);
    s32 bufferSize=0;
    if(request) bufferSize=request->recvBufferSize;
    if(socket>=0 && bufferSize!=0) SOSetSockOpt(socket,0xffff,0x1002,&bufferSize,4);
    return socket;
}

s32 NHTTPi_SocClose(void* mutex, NHTTPRequestInfo* request, s32 socket) {
    NHTTPi_lockReqList(mutex);
    if(request->sslId>0) { SSLShutdown(request->sslId); request->sslId=-1; }
    NHTTPi_unlockReqList(mutex);
    return SOClose(socket);
}

s32 NHTTPi_SocConnect(NHTTPBgnEndInfo* info, void* mutex, NHTTPRequestInfo* request, s32 socket, u32 address, u32 port) {
    SOSockAddrIn destination;
    destination.len=8; destination.family=2;
    destination.port=SOHtoNs(port);
    destination.addr.addr=address;
    if(SOConnect(socket,&destination)<0) {
        s32 error=-1001;
        if(request->cancel) error=-1002;
        return error;
    }
    if(request->secure && !request->proxyEnabled) return NHTTPi_SocSSLConnect(info,mutex,request,socket);
    return 0;
}

s32 NHTTPi_SocSSLConnect(NHTTPBgnEndInfo* info, void* mutex, NHTTPRequestInfo* request, s32 socket) {
    BOOL complete=FALSE;
    request->sslId=SSLNew(request->verifyOption,request->host);
    if(info->sslInit && request->_unkD4) info->sslInit(request->sslId,request->_unkD4);
    if(request->clientCertDefault==1) {
        if(SSLSetBuiltinClientCert(request->sslId,request->builtinClientCert)!=0) return -1005;
    } else if(request->clientCertData && request->privateKeyData) {
        if(SSLSetClientCert(request->sslId,request->clientCertData,request->clientCertSize,request->privateKeyData,request->privateKeySize)!=0) return -1005;
    }
    if(request->rootCAData) {
        if(SSLSetRootCA(request->sslId,request->rootCAData,request->rootCASize)!=0) return -1004;
    } else {
        if(SSLSetBuiltinRootCA(request->sslId,request->builtinRootCA)!=0) return -1004;
    }
    if(SSLConnect(request->sslId,socket)<-1) return -1001;
    while(!complete) {
        NHTTPConnectionInfo* connection=NHTTPi_Request2Connection(mutex,request);
        s32 result=SSLDoHandshake(request->sslId);
        NHTTPi_SetSSLError(info,result);
        if(connection) connection->sslError=result;
        switch(result) {
        case -7:
        case -3:
        case -2: break;
        case 0: complete=TRUE; break;
        default: return -1001;
        }
    }
    return 0;
}

s32 NHTTPi_SocRecv_sub(NHTTPConnectionInfo* connection, s32 socket, void* data, s32 length, s32 flags) {
    u8* buffer=connection->recvBuf;
    s32 received=0;
    if(length>0) {
        if(connection->recvBufDataLen==0) {
            s32 result=SORecv(socket,buffer,32768,flags);
            if(result>0) {
                connection->recvBufDataLen=result;
                connection->recvBufOffset=0;
            } else return result;
        }
        if(connection->recvBufDataLen!=0) {
            length = (u32)length > connection->recvBufDataLen ? connection->recvBufDataLen : length;
            NHTTPi_memcpy(data,buffer+connection->recvBufOffset,length);
            connection->recvBufDataLen-=length;
            if(connection->recvBufDataLen==0) {
                NHTTPi_memclr(buffer,32768);
                connection->recvBufOffset=0;
            } else connection->recvBufOffset+=length;
            received=length;
        }
    }
    return received;
}

s32 NHTTPi_SocRecv(void* mutex, NHTTPRequestInfo* request, s32 socket, void* data, s32 length, s32 flags) {
    s32 result;
    if(request->sslId>0) result=SSLRead(request->sslId,data,length);
    else {
        NHTTPConnectionInfo* connection=NHTTPi_Request2Connection(mutex,request);
        if(connection) result=NHTTPi_SocRecv_sub(connection,socket,data,length,flags);
        else return -1001;
    }
    if(result<0) {
        if(request->cancel) return -1002;
        if(request->sslId>0) { if(result==-7 || result==-6) return 0; }
        else if(result==-56) return 0;
        return -1001;
    }
    return result;
}

s32 NHTTPi_SocSend_sub(s32 socket, const char* data, u32 length, s32 flags) {
    char buffer[32] ATTRIBUTE_ALIGN(32);
    u32 head=((u32)data&31) ? 32-((u32)data&31) : 0;
    s32 sent=0;
    s32 result;
    NHTTPi_memclr(buffer,32);
    if(head) {
        if(head>length) head=length;
        NHTTPi_memcpy(buffer,data,head);
        result=SOSend(socket,buffer,head,flags);
        if (result > 0) {
            sent = result;
            if ((u32)result < head) return result;
            data += result;
            length -= result;
        } else {
            return result;
        }
    }
    if((s32)length>0) {
        head=length&~31;
        if(head) {
            result=SOSend(socket,data,head,flags);
            if(result>0) {
                sent+=result;
                if((u32)result<head) return sent;
                data+=result; length-=result;
            } else { if(sent>0) return sent; return result; }
        }
    }
    if((s32)length>0) {
        head=length&31;
        if(head) {
            NHTTPi_memclr(buffer,32);
            NHTTPi_memcpy(buffer,data,head);
            result=SOSend(socket,buffer,head,flags);
            if(result>0) sent+=result;
            else { if(sent>0) return sent; return result; }
        }
    }
    return sent;
}

s32 NHTTPi_SocSend(NHTTPRequestInfo* request, s32 socket, const char* data, s32 length, s32 flags) {
    s32 result;
    SSLId ssl=request->sslId;
    if(ssl>0) result=SSLWrite(ssl,data,length);
    else result=NHTTPi_SocSend_sub(socket,data,length,flags);
    if(result<0) {
        if(request->cancel) return -1002;
        if(request->sslId>0) { if(result==-7 || result==-6) return 0; }
        else if(result==-56) return 0;
        return -1001;
    }
    return result;
}

void NHTTPi_SocCancel(void* mutex, NHTTPRequestInfo* request, s32 socket) {
    NHTTPi_lockReqList(mutex);
    if(socket>=0) SOShutdown(socket,2);
    NHTTPi_unlockReqList(mutex);
}

u32 NHTTPi_resolveHostname(NHTTPBgnEndInfo* info, const char* hostname) {
    u32 address=0;
    SOAddrInfo* result;
    if(SOGetAddrInfo(hostname,NULL,NULL,&result)==0) {
        SOSockAddrIn* socketAddress=result->addr;
        NHTTPi_memcpy(&address,&socketAddress->addr,4);
        SOFreeAddrInfo(result);
    } else address=0;
    return address;
}
