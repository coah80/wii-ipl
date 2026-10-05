typedef signed long s32;
typedef unsigned char u8;
typedef unsigned long u32;
typedef unsigned long long ESTitleId;
typedef struct ESTicketView { u8 bytes[216]; } ESTicketView;
typedef struct NANDFileInfo { u8 bytes[140]; } NANDFileInfo;
typedef struct Heap { void* (*alloc)(u32,s32); void (*free)(void*); } Heap;
extern int NULL, ES_ERR_OK, DEFAULT_ALIGN;
extern char __FILE__[], __FUNCTION__[];
u32 OSRoundUp32B(u32);
s32 ES_ListTitlesOnCard(ESTitleId*,u32*);
s32 ES_DeleteTitle(ESTitleId);
void OSReport(const char*,...);
void verifySavedataZD(Heap*,ESTitleId,NANDFileInfo*);
s32 DeleteTicketsForce(Heap*,ESTitleId,u8*,u32*);
s32 InitSavedata(Heap* heap)
{
            u8 ticketViews[OSRoundUp32B(sizeof(ESTicketView))] __attribute__((aligned(32)));
            NANDFileInfo fileInfo __attribute__((aligned(32)));
            u32 ticketViewCount;
            ESTitleId* titleIds = NULL;
            u32 titleCount = 0;
            s32 ret = ES_ListTitlesOnCard(NULL, &titleCount);

            if (ret != ES_ERR_OK) {
                OSReport("%s::%s: Failed to ES_ListTitlesOnCard1: %d\n", __FILE__, __FUNCTION__, ret);
                goto cleanup;
            }

            titleIds = (ESTitleId*)heap->alloc(OSRoundUp32B(titleCount * sizeof(ESTitleId)), -DEFAULT_ALIGN);
            if (titleIds == NULL) {
                OSReport("%s::%s: Unable to allocate\n", __FILE__, __FUNCTION__);
                goto cleanup;
            }

            ret = ES_ListTitlesOnCard(titleIds, &titleCount);
            if (ret != ES_ERR_OK) {
                OSReport("%s::%s: Failed to ES_ListTitlesOnCard2: %d\n", __FILE__, __FUNCTION__, ret);
                goto cleanup;
            }

            {
                u8* ticketScratch = ticketViews;
                for (u32 i = 0; i < titleCount; i++) {
                    if ((titleIds[i] & 0xFFFFFFFFFFFFFF00ULL) == 0x00010000525A4400ULL) {
                        verifySavedataZD(heap, titleIds[i], &fileInfo);
                        continue;
                    }
                    switch (titleIds[i]) {
                        case 0x0001000844495343ULL:
                        case 0x000100014A4F4449ULL:
                        case 0x0001000148415858ULL:
                        case 0x0001000844564458ULL:
                        case 0x000100084449534BULL:
                            ES_DeleteTitle(titleIds[i]);
                            DeleteTicketsForce(heap, titleIds[i], ticketScratch, &ticketViewCount);
                            break;
                    }
                }
            }

        cleanup:
            if (titleIds != NULL) {
                heap->free(titleIds);
            }
            return ret;
        }
