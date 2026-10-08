#include <private/nhttp.h>

void* NHTTPi_memcpy(void*, const void*, u32);
s32 NHTTPi_SocRecv(void*, NHTTPRequestInfo*, s32, void*, s32, s32);

#define NHTTPi_TOLOWER(c) ((((c) >= 'A') & ((c) <= 'Z')) ? (c) + ('a' - 'A') : (c))

static void FindHeaderBlock(const NHTTPResponseInfo* response, s32 position, NHTTPi_HDRBUFLIST** block, s32* offset) {
    if(position<NHTTP_HDRRECVBUF_INILEN) { *offset=position; *block=NULL; }
    else {
        s32 blocks=(position-NHTTP_HDRRECVBUF_INILEN)>>NHTTP_HDRRECVBUF_BLOCKSHIFT;
        *block=response->hdrBufBlock_p;
        while(blocks--) *block=(*block)->next_p;
        *offset=(position-NHTTP_HDRRECVBUF_INILEN)&NHTTP_HDRRECVBUF_BLOCKMASK;
    }
}

static int ReadHeaderChar(const NHTTPResponseInfo* response, NHTTPi_HDRBUFLIST** block, s32* offset) {
    if(!*block) {
        if(*offset<NHTTP_HDRRECVBUF_INILEN) return (s8)response->hdrBufFirst[(*offset)++];
        *block=response->hdrBufBlock_p;
        *offset=0;
    } else if(*offset==NHTTP_HDRRECVBUF_BLOCKLEN) { *offset=0; *block=(*block)->next_p; }
    return (*block)->block[(*offset)++];
}

s32 NHTTPi_findNextLineHdrRecvBuf(const NHTTPResponseInfo* response, s32 position, s32 limit, s32* colon, s32* newlineLength) {
    NHTTPi_HDRBUFLIST* block;
    s32 offset;
    if(colon) *colon=-1;
    if (position < limit) {
        s32 next=-1;
        BOOL carriage=FALSE;
        FindHeaderBlock(response,position,&block,&offset);
        for(; position<limit; ++position) {
            int character=ReadHeaderChar(response,&block,&offset);
            if((s8)character==':' && colon && *colon<0) *colon=position;
            if(carriage) {
                if((s8)character=='\n') {
                    next=position==limit-1 ? 0 : position+1;
                    if(newlineLength) *newlineLength=2;
                }
                return next;
            }
            if((s8)character=='\r') {
                next=position==limit-1 ? 0 : position+1;
                carriage=TRUE;
                if(newlineLength) *newlineLength=1;
            }
            if((s8)character=='\n') {
                next=position==limit-1 ? 0 : position+1;
                if(newlineLength) *newlineLength=1;
                return next;
            }
        }
    }
    return -1;
}

s32 NHTTPi_skipSpaceHdrRecvBuf(const NHTTPResponseInfo* response, s32 position, s32 limit) {
    NHTTPi_HDRBUFLIST* block;
    s32 offset;
    if (position < limit) {
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
    s32 i;
    s32 tokenChar;
    s32 character;

    if (position < limit) {
        FindHeaderBlock(response, position, &block, &offset);

        if (block == NULL) {
            if (offset < NHTTP_HDRRECVBUF_INILEN) {
                character = (s8)response->hdrBufFirst[offset++];
                goto compare_characters;
            }
            block = response->hdrBufBlock_p;
            offset = 0;
        } else if (offset == NHTTP_HDRRECVBUF_BLOCKLEN) {
            offset = 0;
            block = block->next_p;
        }
        character = block->block[offset++];

    compare_characters:
        i = position;
        while (NHTTPi_TOLOWER((s8)character) == NHTTPi_TOLOWER((s8)*token)) {
            tokenChar = (s8)*token;
            if (tokenChar == '\0' || tokenChar == ' ' || tokenChar == delimiter || i == limit - 1) return 0;

            if (block == NULL) {
                if (offset < NHTTP_HDRRECVBUF_INILEN) {
                    character = (s8)response->hdrBufFirst[offset++];
                    goto advance_token;
                }
                block = response->hdrBufBlock_p;
                offset = 0;
            } else if (offset == NHTTP_HDRRECVBUF_BLOCKLEN) {
                offset = 0;
                block = block->next_p;
            }
            character = block->block[offset++];

        advance_token:
            i++;
            token++;
        }
    }
    return -1;
}

s32 NHTTPi_loadFromHdrRecvBuf(NHTTPResponseInfo* response, char* destination, s32 position, s32 length) {

    s32 amount;
    NHTTPi_HDRBUFLIST* block;
    if (position + length <= response->headerLen) {
        if(length) {
            if(position<NHTTP_HDRRECVBUF_INILEN) {
                amount=length;
                if(length>NHTTP_HDRRECVBUF_INILEN-position) amount=NHTTP_HDRRECVBUF_INILEN-position;
                NHTTPi_memcpy(destination,response->hdrBufFirst+position,amount);
                position+=amount; length-=amount; destination+=amount;
            }
            if(length) {
                s32 blocks;
                position-=NHTTP_HDRRECVBUF_INILEN;
                block=response->hdrBufBlock_p;
                blocks=position>>NHTTP_HDRRECVBUF_BLOCKSHIFT;
                position&=NHTTP_HDRRECVBUF_BLOCKMASK;
                while(blocks--) block=block->next_p;
                while(length) {
                    amount=length;
                    if(length>NHTTP_HDRRECVBUF_BLOCKLEN-position) amount=NHTTP_HDRRECVBUF_BLOCKLEN-position;
                    NHTTPi_memcpy(destination,block->block+position,amount);
                    position+=amount;
                    position&=NHTTP_HDRRECVBUF_BLOCKMASK;
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
    s32 available;
    NHTTPResponseInfo* response=request->response;
    void* receiveCursor;
    if(response->recvBufLen<=offset) return -1003;
    available=response->recvBufLen;
    receiveCursor=response->recvBuf_p;
    available=available-offset;
    receiveCursor=(u8*)receiveCursor+offset;
    if(length>available) length=available;
    return NHTTPi_SocRecv(mutex,request,socket,receiveCursor,length,flags);
}
