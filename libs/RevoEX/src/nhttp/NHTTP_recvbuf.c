#include <private/nhttp.h>

void* NHTTPi_memcpy(void*, const void*, u32);
s32 NHTTPi_SocRecv(void*, NHTTPRequestInfo*, s32, void*, s32, s32);

static void FindHeaderBlock(const NHTTPResponseInfo* response, s32 position, NHTTPi_HDRBUFLIST** block, s32* offset) {
    if(position<1024) { *offset=position; *block=NULL; }
    else {
        s32 blocks=(position-1024)>>9;
        *block=response->hdrBufBlock_p;
        while(blocks--) *block=(*block)->next_p;
        *offset=(position-1024)&511;
    }
}

static s8 ReadHeaderChar(const NHTTPResponseInfo* response, NHTTPi_HDRBUFLIST** block, s32* offset) {
    if(!*block) {
        if(*offset<1024) return (s8)response->hdrBufFirst[(*offset)++];
        *block=response->hdrBufBlock_p;
        *offset=0;
    } else if(*offset==512) { *offset=0; *block=(*block)->next_p; }
    return (*block)->block[(*offset)++];
}

static int LowerCase(int character) {
    if((character>='A') & (character<='Z')) character+=32;
    return character;
}

s32 NHTTPi_findNextLineHdrRecvBuf(const NHTTPResponseInfo* response, s32 position, s32 limit, s32* colon, s32* newlineLength) {
    NHTTPi_HDRBUFLIST* block;
    s32 offset;
    s32 next=-1;
    BOOL carriage=FALSE;
    if(colon) *colon=-1;
    if(position>=limit) return -1;
    FindHeaderBlock(response,position,&block,&offset);
    for(; position<limit; ++position) {
        s8 character=ReadHeaderChar(response,&block,&offset);
        if(character==':' && colon && *colon<0) *colon=position;
        if(carriage) {
            if(character=='\n') {
                next=position==limit-1 ? 0 : position+1;
                if(newlineLength) *newlineLength=2;
            }
            return next;
        }
        if(character=='\r') {
            next=position==limit-1 ? 0 : position+1;
            carriage=TRUE;
            if(newlineLength) *newlineLength=1;
        }
        if(character=='\n') {
            next=position==limit-1 ? 0 : position+1;
            if(newlineLength) *newlineLength=1;
            return next;
        }
    }
    return -1;
}

s32 NHTTPi_skipSpaceHdrRecvBuf(const NHTTPResponseInfo* response, s32 position, s32 limit) {
    NHTTPi_HDRBUFLIST* block;
    s32 offset;
    if(position>=limit) return -1;
    FindHeaderBlock(response,position,&block,&offset);
    for(; position<limit; ++position) {
        s8 character=ReadHeaderChar(response,&block,&offset);
        if(character!=' ') return position;
    }
    return -1;
}

s32 NHTTPi_compareTokenN_HdrRecvBuf(const NHTTPResponseInfo* response, s32 position, s32 limit, const char* token, s8 delimiter) {
    NHTTPi_HDRBUFLIST* block;
    s32 offset;
    s8 character;
    if(position>=limit) return -1;
    FindHeaderBlock(response,position,&block,&offset);
    character=ReadHeaderChar(response,&block,&offset);
    while(LowerCase(character)==LowerCase(*token)) {
        if(*token==0 || *token==' ' || *token==delimiter || position==limit-1) return 0;
        character=ReadHeaderChar(response,&block,&offset);
        ++position;
        ++token;
    }
    return -1;
}

s32 NHTTPi_loadFromHdrRecvBuf(NHTTPResponseInfo* response, char* destination, s32 position, s32 length) {

    s32 amount;
    NHTTPi_HDRBUFLIST* block;
    if(position+length>response->headerLen) return FALSE;
    if(length) {
        if(position<1024) {
            amount=length;
            if(length>1024-position) amount=1024-position;
            NHTTPi_memcpy(destination,response->hdrBufFirst+position,amount);
            position+=amount; length-=amount; destination+=amount;
        }
        if(length) {
            s32 blocks;
            position-=1024;
            block=response->hdrBufBlock_p;
            blocks=position>>9;
            position&=511;
            while(blocks--) block=block->next_p;
            while(length) {
                amount=length;
                if(length>512-position) amount=512-position;
                NHTTPi_memcpy(destination,block->block+position,amount);
                position=(position+amount)&511;
                block=block->next_p;
                length-=amount; destination+=amount;
            }
        }
    }
    return TRUE;
}

BOOL NHTTPi_isRecvBufFull(NHTTPResponseInfo* response, u32 length) { return length>=response->recvBufLen; }

s32 NHTTPi_RecvBuf(void* mutex, NHTTPRequestInfo* request, s32 socket, u32 offset, s32 flags) {
    NHTTPResponseInfo* response=request->response;
    return NHTTPi_SocRecv(mutex,request,socket,response->recvBuf_p+offset,response->recvBufLen-offset,flags);
}

s32 NHTTPi_RecvBufN(void* mutex, NHTTPRequestInfo* request, s32 socket, u32 offset, s32 length, s32 flags) {
    s32 available;
    NHTTPResponseInfo* response=request->response;
    void* buf;
    if(response->recvBufLen<=offset) return -1003;
    available=response->recvBufLen;
    buf=response->recvBuf_p;
    available=available-offset;
    buf=(u8*)buf+offset;
    if(length>available) length=available;
    return NHTTPi_SocRecv(mutex,request,socket,buf,length,flags);
}
