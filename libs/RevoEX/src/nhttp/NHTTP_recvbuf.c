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
    return (character>='A') & (character<='Z') ? character+32 : character;
}

s32 NHTTPi_findNextLineHdrRecvBuf(const NHTTPResponseInfo* response, s32 position, s32 limit, s32* colon, s32* newlineLength) {
    NHTTPi_HDRBUFLIST* block;
    s32 offset;
    s32 next;
    BOOL carriage;
    if(colon) *colon=-1;
    if(position>=limit) goto done;
    next=-1;
    carriage=FALSE;
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
done:
    return -1;
}

s32 NHTTPi_skipSpaceHdrRecvBuf(const NHTTPResponseInfo* response, s32 position, s32 limit) {
    NHTTPi_HDRBUFLIST* block;
    s32 offset;
    if(position<limit) {
        FindHeaderBlock(response,position,&block,&offset);
        for(; position<limit; ++position) {
            s8 character=ReadHeaderChar(response,&block,&offset);
            if(character!=' ') return position;
        }
    }
    return -1;
}

s32 NHTTPi_compareTokenN_HdrRecvBuf(const NHTTPResponseInfo* response, s32 position, s32 limit, const char* token, s8 delimiter) {
    NHTTPi_HDRBUFLIST* block;
    s32 offset;
    s8 character;
    if(position>=limit) goto done;
    FindHeaderBlock(response,position,&block,&offset);
    character=ReadHeaderChar(response,&block,&offset);
    while(LowerCase(character)==LowerCase(*token)) {
        if(*token==0 || *token==' ' || *token==delimiter || position==limit-1) return 0;
        character=ReadHeaderChar(response,&block,&offset);
        ++position;
        ++token;
    }
done:
    return -1;
}

s32 NHTTPi_loadFromHdrRecvBuf(NHTTPResponseInfo* response, char* destination, s32 position, s32 length) {

    s32 amount;
    NHTTPi_HDRBUFLIST* block;
    if(position+length<=response->headerLen) {
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
                position+=amount;
                position&=511;
                block=block->next_p;
                length-=amount; destination+=amount;
            }
        }
    }
        return TRUE;
    }
    return FALSE;
}

BOOL NHTTPi_isRecvBufFull(NHTTPResponseInfo* response, u32 length) { return length>=response->recvBufLen; }

s32 NHTTPi_RecvBuf(void* mutex, NHTTPRequestInfo* request, s32 socket, u32 offset, s32 flags) {
    NHTTPResponseInfo* response=request->response;
    return NHTTPi_SocRecv(mutex,request,socket,response->recvBuf_p+offset,response->recvBufLen-offset,flags);
}

s32 NHTTPi_RecvBufN(void* mutex, NHTTPRequestInfo* request, s32 socket, u32 offset, s32 length, s32 flags) {
    NHTTPResponseInfo* response=request->response;
    s32 remaining;
    char* buf;
    if(response->recvBufLen<=offset) return -1003;
    remaining=((volatile NHTTPResponseInfo*)response)->recvBufLen-offset;
    buf=response->recvBuf_p+offset;
    if(length>remaining) length=remaining;
    return NHTTPi_SocRecv(mutex,request,socket,buf,length,flags);
}
