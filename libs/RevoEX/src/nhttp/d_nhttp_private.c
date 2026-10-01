#include <private/nhttp.h>

void* NHTTPi_GetSystemInfoP(void);
NHTTPBgnEndInfo* NHTTPi_GetBgnEndInfoP(void*);
void* NHTTPi_GetMutexInfoP(void*);
void* NHTTPi_GetThreadInfoP(void*);
void* NHTTPi_alloc(u32, int);
void NHTTPi_free(void*);
void* NHTTPi_memclr(void*, u32);
void NHTTPi_SetError(NHTTPBgnEndInfo*, NHTTPErr);
NHTTPRequestInfo* NHTTP_CreateRequest(NHTTPBgnEndInfo*, const char*, s32, void*, u32, void*, NHTTPResponseCallback, NHTTPResponseCleanup);
NHTTPConnectionInfo* NHTTPi_GetConnection(void*, NHTTPConnectionInfo*);
NHTTPRequestInfo* NHTTPi_GetRequest(void*, NHTTPRequestInfo*);
NHTTPResponseInfo* NHTTPi_Connection2Response(void*, NHTTPConnectionInfo*);
void NHTTPi_CommitConnectionList(void*, NHTTPConnectionInfo*);
s32 NHTTPi_OmitConnectionList(void*, NHTTPConnectionInfo*);
void NHTTPi_SetVirtualContentLength(NHTTPConnectionInfo*, u32);
void NHTTPi_CheckCurrentThread(void*, BOOL);
BOOL NHTTP_CancelRequestAsync(void*, s32);
void NHTTP_DestroyRequest(void*, NHTTPRequestInfo*);
void NHTTP_DestroyResponse(void*, NHTTPResponseInfo*);
s32 NHTTP_SendRequestAsync(void*, NHTTPRequestInfo*);
void NHTTPi_WaitForCompletion(NHTTPConnectionInfo*);

NHTTPConnectionInfo* NHTTPCreateConnection(const char* url, s32 method, void* buffer, u32 size, NHTTPConnectionCallback callback, void* userParam) {
    NHTTPConnectionInfo* connection;
    NHTTPBgnEndInfo* info;
    void* system;
    void* mutex;
    system=NHTTPi_GetSystemInfoP();
    info=NHTTPi_GetBgnEndInfoP(system);
    mutex=NHTTPi_GetMutexInfoP(system);
    connection=NHTTPi_alloc(sizeof(*connection),32);
    if(!connection) { NHTTPi_SetError(info,NHTTP_ERROR_ALLOC); return NULL; }
    NHTTPi_memclr(connection,sizeof(*connection));
    connection->request=NHTTP_CreateRequest(info,url,method,buffer,size,userParam,NULL,NULL);
    if(!connection->request) { NHTTPi_free(connection); return NULL; }
    connection->response=connection->request->response;
    connection->started=FALSE;
    connection->callback=callback;
    connection->_unk24=0; connection->_unk28=0;
    connection->requestId=-1;
    NHTTPi_CommitConnectionList(mutex,connection);
    connection->state=15;
    connection->sslError=0;
    connection->_unkC=1;
    NHTTPi_SetVirtualContentLength(connection,0);
    connection->requestCallback=NULL;
    connection->recvBufOffset=0; connection->recvBufDataLen=0;
    NHTTPi_memclr(connection->recvBuf,sizeof(connection->recvBuf));
    return connection;
}

static s32 ConnectionStarted(NHTTPConnectionInfo* handle) {
    void* system=NHTTPi_GetSystemInfoP();
    void* mutex=NHTTPi_GetMutexInfoP(system);
    NHTTPConnectionInfo* connection=NHTTPi_GetConnection(mutex,handle);
    s32 started;
    if (connection == NULL) {
        started = -1;
    } else {
        started = connection->started;
    }
    return started;
}

static s32 ConnectionState(NHTTPConnectionInfo* handle) {
    void* system=NHTTPi_GetSystemInfoP();
    void* mutex=NHTTPi_GetMutexInfoP(system);
    NHTTPConnectionInfo* connection=NHTTPi_GetConnection(mutex,handle);
    return connection ? connection->state : -1;
}

static void WaitConnection(NHTTPConnectionInfo* handle) {
    void* system=NHTTPi_GetSystemInfoP();
    void* thread=NHTTPi_GetThreadInfoP(system);
    void* mutex=NHTTPi_GetMutexInfoP(system);
    NHTTPConnectionInfo* connection=NHTTPi_GetConnection(mutex,handle);
    if(connection) {
        s32 started=ConnectionStarted(handle);
        NHTTPi_CheckCurrentThread(thread,TRUE);
        if(started!=-1 && started!=0 && ConnectionState(handle)==15) NHTTPi_WaitForCompletion(connection);
    }
}

s32 NHTTPDeleteConnection(NHTTPConnectionInfo* handle) {
    void* system=NHTTPi_GetSystemInfoP();
    void* mutex=NHTTPi_GetMutexInfoP(system);
    void* thread=NHTTPi_GetThreadInfoP(system);
    NHTTPConnectionInfo* connection=NHTTPi_GetConnection(mutex,handle);
    if(!connection) return -1;
    NHTTPi_CheckCurrentThread(thread,TRUE);
    if(connection->requestId>=0) {
        NHTTP_CancelRequestAsync(system,connection->requestId);
        connection->requestId=-1;
    }
    if(connection->request && connection->request->state==0) NHTTP_DestroyRequest(system,connection->request);
    if(connection->response) {
        if(!connection->request) NHTTP_DestroyResponse(mutex,connection->response);
        else { WaitConnection(connection); NHTTP_DestroyResponse(mutex,connection->response); }
    }
    NHTTPi_OmitConnectionList(mutex,connection);
    NHTTPi_free(connection);
    return 0;
}

s32 NHTTPStartConnection(NHTTPConnectionInfo* handle) {
    void* system=NHTTPi_GetSystemInfoP();
    void* mutex=NHTTPi_GetMutexInfoP(system);
    NHTTPConnectionInfo* connection=NHTTPi_GetConnection(mutex,handle);
    if(!connection) return -1;
    if(!connection->request) return -1;
    connection->requestId=NHTTP_SendRequestAsync(system,connection->request);
    if(connection->requestId>=0) connection->started=TRUE;
    return 0;
}

s32 NHTTPGetBodyBuffer(NHTTPConnectionInfo* handle, void** buffer, u32* size) {
    void* system=NHTTPi_GetSystemInfoP();
    void* mutex=NHTTPi_GetMutexInfoP(system);
    NHTTPConnectionInfo* connection=NHTTPi_GetConnection(mutex,handle);
    if(connection) {
        NHTTPResponseInfo* response=NHTTPi_Connection2Response(mutex,connection);
        if(response) { *buffer=response->recvBuf_p; *size=response->recvBufLen; return response->bodyLen; }
        return -1;
    }
    return -1;
}

void* NHTTPGetUserParam(NHTTPConnectionInfo* handle) {
    void* system=NHTTPi_GetSystemInfoP();
    void* mutex=NHTTPi_GetMutexInfoP(system);
    NHTTPConnectionInfo* connection=NHTTPi_GetConnection(mutex,handle);
    if(connection) {
        NHTTPResponseInfo* response=NHTTPi_Connection2Response(mutex,connection);
        if(response) return response->param_p;
        return NULL;
    }
    return NULL;
}

s32 NHTTPGetConnectionError(NHTTPConnectionInfo* handle) {
    void* system=NHTTPi_GetSystemInfoP();
    void* mutex=NHTTPi_GetMutexInfoP(system);
    NHTTPConnectionInfo* connection=NHTTPi_GetConnection(mutex,handle);
    return connection ? connection->state : -1;
}

s32 NHTTPSetSocketBufferSize(NHTTPRequestInfo* handle, u32 size) {
    void* system=NHTTPi_GetSystemInfoP();
    void* mutex=NHTTPi_GetMutexInfoP(system);
    NHTTPRequestInfo* request=NHTTPi_GetRequest(mutex,handle);
    if(!request) return -1;
    request->recvBufferSize=size;
    return 0;
}
