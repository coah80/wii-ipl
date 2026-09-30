#include <private/es.h>
#include <revolution/nup.h>
#include <revolution/nand.h>
#include <revolution/os/OSMutex.h>
#include <revolution/os/OSThread.h>
#include <revolution/os/OSTime.h>
#include <revolution/sc.h>
#include <private/fs.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace nup {
int __nupRegisterAllocator(MEMAllocator* allocator);
void* __nupMalloc(unsigned long size);
void* __nupMallocAlign(unsigned long size, unsigned long alignment);
void __nupFree(void* block);
}

extern "C" void* __nupOp(void* context);
extern "C" ESError ES_GetBoot2Version(u32* version);
int __nupHttpPostFull(char* url, char* headers, char* body, u8** response, unsigned long* responseSize,
                      unsigned long timeout, void (*update)(void*, unsigned long), void* updateContext);
int __nupHttpGetFull(char* url, u8** response, unsigned long* responseSize, unsigned long alignment,
                     void (*update)(void*, unsigned long), void* updateContext);
int __nupHttpGetIncr(char* url, unsigned long alignment, void (*update)(void*, unsigned long),
                     void* updateContext, ESError (*flush)(u8*, unsigned long, unsigned long, void*), void* flushContext);

struct NUPProgress {
    s32 result;
    const char* message;
    u64 totalBytes;
    u64 completedBytes;
};

struct NUPAuditRecord {
    u8 deviceInfo[0x20];
    ESTicketView ticketView;
};

struct NUPSignedAuditData {
    u32 format;
    NUPAuditRecord auditRecord;
    ESSignature signature;
    u8 signatureCertificate[0x180];
    u8 deviceCertificate[0x180];
};

struct NUPTitleInfo {
    u64 titleId;
    u16 serverVersion;
    u16 installedVersion;
    s32 updateRequired;
    u64 installedContentSize;
    u64 updateContentSize;
    u32 progressStep;
    void* ticket;
    void* content;
    u32 contentSize;
    void* tmd;
    u32 tmdSize;
    void* ticketCertificate;
    u32 ticketCertificateSize;
    void* tmdCertificate;
    u32 tmdCertificateSize;
    void* tmdView;
    u32 tmdViewSize;
    u8 hasTicket;
    u8 hasTmd;
    u8 hasContent;
    u8 statusFlags;
    u32 contentCount;
    u32* contentIds;
    u32 reservedContentId;
};

struct ESTitleVersion {
    ESTitleId titleId;
    u16 serverVersion;
    u16 installedVersion;
    s32 updateRequired;
    u64 installedContentSize;
    u64 updateContentSize;
    u32 progressStep;
    void* ticket;
    void* content;
    u32 contentSize;
    void* tmd;
    u32 tmdSize;
    void* ticketCertificate;
    u32 ticketCertificateSize;
    void* tmdCertificate;
    u32 tmdCertificateSize;
    void* tmdView;
    u32 tmdViewSize;
    u8 hasTicket;
    u8 hasTmd;
    u8 hasContent;
    u8 statusFlags;
    u32 contentCount;
    ESContentId* contentIds;
    u32 reservedContentId;
};

struct NUPContextInfo {
    u8 threadStarted;
    u32 titleCount;
    u32 updateCount;
    NUPTitleInfo* titles;
    u8 uploadAuditData;
    char* contentPrefixUrl;
    char* uncachedContentPrefixUrl;
    u64 downloadedBytes;
    u32 ownedTitleCount;
    ESTitleId* ownedTitleIds;
    const char* serverAddress;
    const char* countryCode;
    const char* productArea;
    u32 systemVersion;
    NUPProgress progress;
    OSThread thread;
    OSMutex mutex;
    u64 threadStack[0x400];
};

static const char* __nupStatusMessage[6] = {
    "successful completion",
    "initializing",
    "connecting to server",
    "downloading content from server",
    "unknown",
    "an error occurred",
};

int NUP_GetStatus(void* instance, u64* status) {
    NUPContextInfo* context = (NUPContextInfo*)instance;

    OSLockMutex(&context->mutex);
    if (status != 0) {
        memcpy(status, &context->progress, 0x18);
    }
    s32 result = *(s32*)status;
    OSUnlockMutex(&context->mutex);
    return result;
}

static void __nupUpdateStatusIncr(void* instance, unsigned long amount) {
    if (instance != 0) {
        NUPContextInfo* context = (NUPContextInfo*)instance;
        OSLockMutex(&context->mutex);
        context->progress.completedBytes += amount;
        if (context->progress.completedBytes > context->progress.totalBytes) {
            context->progress.completedBytes = context->progress.totalBytes;
        }
        OSUnlockMutex(&context->mutex);
    }
}

static ESError __nupHttpBufferFlushES(u8* buffer, unsigned long size, unsigned long, void* file) {
    ESError result = 0;
    if (size != 0) {
        result = ES_ImportContentData((ESFd)file, buffer, size);
    }
    return result;
}

static inline char* __nupFindTag(char* response, const char* endTag, const char* startTag,
                                char** value, size_t* length) {
    char* start;
    char* end;
    if (response != 0 && (start = strstr(response, startTag)) != 0 &&
        (end = strstr(start, endTag)) != 0) {
        *value = start + strlen(startTag);
        *length = end - *value;
        return end + strlen(endTag);
    }
    return 0;
}

static s32 __nupParseServerInfo(NUPContextInfo* context, char* response, char* messageId,
                               unsigned long long deviceId) {
    s32 result = 0;
    char* start;
    char* afterEnd;
    char* cursor;
    size_t valueLength;
    size_t titleCount;

    {
        const char* versionEndTag = "</Version>";
        const char* versionStartTag = "<Version>";
        afterEnd = __nupFindTag(response, versionEndTag, versionStartTag,
                                &start, &valueLength);
        if (afterEnd == 0 || valueLength != strlen("1.0") || strncmp(start, "1.0", valueLength) != 0) {
            result = -5004;
            goto done;
        }
    }

    {
        const char* deviceIdEndTag = "</DeviceId>";
        const char* deviceIdStartTag = "<DeviceId>";
        afterEnd = __nupFindTag(response, deviceIdEndTag, deviceIdStartTag,
                                &start, &valueLength);
        if (afterEnd == 0) {
            result = -5004;
            goto done;
        }
        if (strtoull(start, 0, 10) != deviceId) {
            result = -5004;
            goto done;
        }
    }

    {
        const char* messageIdEndTag = "</MessageId>";
        const char* messageIdStartTag = "<MessageId>";
        afterEnd = __nupFindTag(response, messageIdEndTag, messageIdStartTag,
                                &start, &valueLength);
        if (afterEnd == 0) {
            result = -5004;
            goto done;
        }
        if (valueLength != strlen(messageId) || strncmp(start, messageId, valueLength) != 0) {
            result = -5004;
            goto done;
        }
    }

    {
        const char* errorCodeEndTag = "</ErrorCode>";
        const char* errorCodeStartTag = "<ErrorCode>";
        afterEnd = __nupFindTag(response, errorCodeEndTag, errorCodeStartTag,
                                &start, &valueLength);
        if (afterEnd == 0) {
            result = -5004;
            goto done;
        }
        if (valueLength != strlen("0") || strncmp(start, "0", valueLength) != 0) {
            result = -5004;
            goto done;
        }
    }

    {
        const char* uploadAuditEndTag = "</UploadAuditData>";
        const char* uploadAuditStartTag = "<UploadAuditData>";
        afterEnd = __nupFindTag(response, uploadAuditEndTag, uploadAuditStartTag,
                                &start, &valueLength);
        if (afterEnd == 0) {
            result = -5004;
            goto done;
        }
        if (valueLength != strlen("0") || (*start != '0' && *start != '1')) {
            result = -5004;
            goto done;
        }
        context->uploadAuditData = *start == '1';
    }

    {
        const char* contentPrefixEndTag = "</ContentPrefixURL>";
        const char* contentPrefixStartTag = "<ContentPrefixURL>";
        afterEnd = __nupFindTag(response, contentPrefixEndTag, contentPrefixStartTag,
                                &start, &valueLength);
        if (afterEnd == 0) {
            result = -5004;
            goto done;
        }
        if (valueLength == 0) {
            result = -5004;
            goto done;
        }
        context->contentPrefixUrl = (char*)nup::__nupMalloc(valueLength + 1);
        if (context->contentPrefixUrl == 0) {
            result = -5000;
            goto done;
        }
        strncpy(context->contentPrefixUrl, start, valueLength);
        context->contentPrefixUrl[valueLength] = '\0';
    }

    {
        const char* uncachedPrefixEndTag = "</UncachedContentPrefixURL>";
        const char* uncachedPrefixStartTag = "<UncachedContentPrefixURL>";
        afterEnd = __nupFindTag(response, uncachedPrefixEndTag, uncachedPrefixStartTag,
                                &start, &valueLength);
        if (afterEnd == 0) {
            result = -5004;
            goto done;
        }
        if (valueLength == 0) {
            result = -5004;
            goto done;
        }
        context->uncachedContentPrefixUrl = (char*)nup::__nupMalloc(valueLength + 1);
        if (context->uncachedContentPrefixUrl == 0) {
            result = -5000;
            goto done;
        }
        strncpy(context->uncachedContentPrefixUrl, start, valueLength);
        context->uncachedContentPrefixUrl[valueLength] = '\0';
    }

    titleCount = 0;
    cursor = response;
    {
        const char* titleIdEndTag = "</TitleId>";
        const char* titleIdStartTag = "<TitleId>";
        const char* versionEndTag = "</Version>";
        const char* versionStartTag = "<Version>";
        for (;;) {
            cursor = __nupFindTag(cursor, titleIdEndTag, titleIdStartTag, &start, &valueLength);
            if (cursor == 0) {
                break;
            }
            cursor = __nupFindTag(cursor, versionEndTag, versionStartTag, &start, &valueLength);
            if (cursor == 0) {
                break;
            }
            titleCount++;
        }
    }

    context->titles = (NUPTitleInfo*)nup::__nupMalloc(titleCount * sizeof(NUPTitleInfo));
    if (context->titles == 0) {
        result = -5000;
        goto done;
    }
    memset(context->titles, 0, titleCount * sizeof(NUPTitleInfo));
    cursor = response;
    {
        const char* titleIdEndTag = "</TitleId>";
        const char* titleIdStartTag = "<TitleId>";
        const char* versionEndTag = "</Version>";
        const char* versionStartTag = "<Version>";
        char* titleStart;
        char* versionStart;
        size_t titleLength;
        size_t versionLength;
        char* parsedEnd;
        goto first;
        for (;;) {
            unsigned long long titleId = strtoull(titleStart, &parsedEnd, 16);
            if (parsedEnd != titleStart + titleLength) {
                result = -5004;
                goto done;
            }
            unsigned long version = strtoul(versionStart, &parsedEnd, 10);
            if (parsedEnd != versionStart + versionLength) {
                result = -5004;
                goto done;
            }
            if (version != (u16)version) {
                result = -5004;
                goto done;
            }
            context->titles[context->titleCount].titleId = titleId;
            context->titles[context->titleCount].serverVersion = version;
            context->titleCount++;
        first:
            cursor = __nupFindTag(cursor, titleIdEndTag, titleIdStartTag,
                                  &titleStart, &titleLength);
            if (cursor == 0) {
                break;
            }
            cursor = __nupFindTag(cursor, versionEndTag, versionStartTag,
                                  &versionStart, &versionLength);
            if (cursor == 0) {
                break;
            }
        }
    }

done:
    return result;
}

static s32 __nupGetServerInfo(char* serverAddress, char* messageId, unsigned long long deviceId,
                              char* productArea, char* countryCode, unsigned long systemVersion,
                              char* auditData, unsigned short bootVersion, unsigned short systemMenuVersion,
                              unsigned long long currentTitleId, unsigned short currentTitleVersion,
                              char** response) {
    s32 result;
    char* request = 0;
    u8* responseData = 0;
    unsigned long responseSize = 0;
    char headers[0x56] =
        "User-Agent: wii libnup/1.0\r\n"
        "SOAPAction: \"urn:nus.wsapi.broadon.com/GetSystemUpdate\"\r\n";
    char* endpoint = 0;
    unsigned long requestSize;
    unsigned long endpointSize;

    endpointSize = strlen(serverAddress) + 0x26;
    endpoint = (char*)nup::__nupMalloc(endpointSize);
    if (endpoint == 0) {
        result = -5000;
    } else {
        snprintf(endpoint, endpointSize, "https://%s/nus/services/NetUpdateSOAP", serverAddress);
        requestSize = strlen(messageId) + strlen(productArea);
        requestSize += strlen(countryCode) + 0x449;
        if (auditData != 0) {
            requestSize += strlen(auditData);
        }
        request = (char*)nup::__nupMalloc(requestSize);
        if (request == 0) {
            result = -5000;
        } else {
            snprintf(request, requestSize,
                     "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                     "  <soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\"\n"
                     "                    xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"\n"
                     "                    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n"
                     "    <soapenv:Body>\n"
                     "      <GetSystemUpdateRequest xmlns=\"urn:nus.wsapi.broadon.com\">\n"
                     "        <Version>1.0</Version>\n"
                     "        <MessageId>%s</MessageId>\n"
                     "        <DeviceId>%llu</DeviceId>\n"
                     "        <RegionId>%s</RegionId>\n"
                     "        <CountryCode>%s</CountryCode>\n"
                     "        <TitleVersion>\n"
                     "          <TitleId>%016llx</TitleId>\n"
                     "          <Version>%hd</Version>\n"
                     "        </TitleVersion>\n"
                     "        <TitleVersion>\n"
                     "          <TitleId>%016llx</TitleId>\n"
                     "          <Version>%hd</Version>\n"
                     "        </TitleVersion>\n"
                     "        <TitleVersion>\n"
                     "          <TitleId>%016llx</TitleId>\n"
                     "          <Version>%hd</Version>\n"
                     "        </TitleVersion>\n"
                     "        <Attribute>%u</Attribute>\n"
                     "        <AuditData>%s</AuditData>\n"
                     "      </GetSystemUpdateRequest>\n"
                     "    </soapenv:Body>\n"
                     "  </soapenv:Envelope>\n",
                     messageId, deviceId, productArea, countryCode,
                     (unsigned long long)0x0000000100000001ULL, bootVersion,
                     (unsigned long long)0x0000000100000002ULL, systemMenuVersion,
                     currentTitleId, currentTitleVersion,
                     systemVersion, auditData != 0 ? auditData : "");
            result = __nupHttpPostFull(endpoint, headers, request, &responseData, &responseSize, 0, 0, 0);
            if (result == 0) {
                *response = (char*)nup::__nupMalloc(responseSize + 1);
                if (*response == 0) {
                    result = -5000;
                } else {
                    strncpy(*response, (char*)responseData, responseSize);
                    (*response)[responseSize] = '\0';
                }
            }
        }
    }

    if (request != 0) {
        nup::__nupFree(request);
    }
    if (endpoint != 0) {
        nup::__nupFree(endpoint);
    }
    if (responseData != 0) {
        nup::__nupFree(responseData);
    }
    return result;
}

static s32 __nupGetTicketViews(ESTitleId titleId, ESTicketView** ticketViews, u32* viewCount) {
    s32 result;
    ESTicketView* views = 0;
    result = ES_GetTicketViews(titleId, 0, viewCount);
    if (result != -0x6a && result >= 0) {
        unsigned long size = (*viewCount * sizeof(ESTicketView) + 0x1f) & 0xffffffe0;
        views = (ESTicketView*)nup::__nupMalloc(size);
        if (views != 0) {
            result = ES_GetTicketViews(titleId, views, viewCount);
        } else {
            result = -5000;
        }
    }
    if (result < 0 && views != 0) {
        nup::__nupFree(views);
        views = 0;
    }
    *ticketViews = views;
    return result;
}

#pragma dont_inline on
static u32 __nupSetAuditState(u8 state) {
    const char* auditPath = "NUPAUDIT";
    s32 result;
    if (state != 0) {
        result = NANDDelete(auditPath);
        if (result != 0) {
            if (result == -12) {
                result = 0;
            } else {
                result -= 6000;
            }
        }
    } else {
        result = NANDCreateDir(auditPath, 0x30, 3);
        if (result != 0) {
            result = result == -6 ? 0 : result - 6000;
        }
    }
    return result;
}
#pragma dont_inline reset

static void __nupBase64Encode(u8* output, u8* input, unsigned long length) {
    static const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    u8* end = input + length;
    u32 value = 0;
    u32 count = 0;
    static char pad = '=';

    while (input != end) {
        count++;
        value <<= 8;
        value |= *input++;
        if (count < 3) {
            continue;
        }
        output[0] = alphabet[value >> 18 & 0x3f];
        output[1] = alphabet[value >> 12 & 0x3f];
        output[2] = alphabet[value >> 6 & 0x3f];
        output[3] = alphabet[value & 0x3f];
        count = 0;
        output += 4;
    }

    if (count == 2) {
        value <<= 8;
        output[0] = alphabet[value >> 18 & 0x3f];
        output[1] = alphabet[value >> 12 & 0x3f];
        output[2] = alphabet[value >> 6 & 0x3f];
        output[3] = pad;
        return;
    }
    if (count != 1) {
        return;
    }
    value <<= 16;
    output[0] = alphabet[value >> 18 & 0x3f];
    output[1] = alphabet[value >> 12 & 0x3f];
    output[2] = pad;
    output[3] = pad;
}

static s32 __nupGetAuditData(NUPContextInfo* context, char** auditData) {
    s32 result = 0;
    u32 auditFormat = 0;
    ESTicketView* ticketViews = 0;
    u32 viewCount;
    u32 selected = 0;
    u32 selectedIndex;
    void* auditRecord = 0;
    void* signatureCertificate = 0;
    void* deviceCertificate = 0;
    NUPSignedAuditData* signedData = 0;
    void* encodedData = 0;
    ESSignature signature ALIGN32;
    char deviceInfo[0x21];
    u32 i;

    for (i = 0; selected == 0 && i < context->ownedTitleCount; i++) {
        ESTitleId ownedTitleId = context->ownedTitleIds[i];
        if (ownedTitleId != 0x0000000100000002ULL && ownedTitleId != 0x0000000100000100ULL &&
            ownedTitleId != 0x0000000100000101ULL) {
            if (ownedTitleId >= 0x0000000100000003ULL) {
                if (ownedTitleId <= 0x00000001000000ffULL) {
                    continue;
                }
            }
            result = __nupGetTicketViews(ownedTitleId, &ticketViews, &viewCount);
            if (result != 0) {
                goto done;
            }
            for (selectedIndex = 0; selectedIndex < viewCount; selectedIndex++) {
                if (ticketViews[selectedIndex].reserved.empty_0x00[46] != 0) {
                    selected = 1;
                    break;
                }
            }
        }
    }

    if (selected != 0) {
        memset(deviceInfo, 0, sizeof(deviceInfo));
        char* productCode = SCGetProductCode();
        unsigned long productCodeSize = 0;
        if (productCode != 0) {
            memcpy(deviceInfo, productCode, 5);
            deviceInfo[4] = '\0';
            productCodeSize = strlen(deviceInfo);
        }
        if (SCGetProductSNString(deviceInfo + productCodeSize, sizeof(deviceInfo) - productCodeSize) == 0) {
            memset(deviceInfo + productCodeSize, 0, sizeof(deviceInfo) - productCodeSize);
            strncpy(deviceInfo + productCodeSize, "", sizeof(deviceInfo) - productCodeSize);
        }
        deviceInfo[0x20] = '\0';

        auditRecord = nup::__nupMallocAlign(0xf8, 0x40);
        if (auditRecord == 0) {
            result = -5000;
        } else {
            memcpy(((NUPAuditRecord*)auditRecord)->deviceInfo, deviceInfo, 0x20);
            memcpy(&((NUPAuditRecord*)auditRecord)->ticketView, &ticketViews[selectedIndex], sizeof(ESTicketView));
            signatureCertificate = nup::__nupMallocAlign(0x180, 0x40);
            if (signatureCertificate == 0) {
                result = -5000;
            } else {
                result = ES_Sign(auditRecord, 0xf8, signature, (ESCertSignature*)signatureCertificate);
                if (result == 0) {
                    deviceCertificate = nup::__nupMallocAlign(0x180, 0x40);
                    if (deviceCertificate == 0) {
                        result = -5000;
                    } else {
                        result = ES_GetDeviceCert(deviceCertificate);
                        if (result == 0) {
                            signedData = (NUPSignedAuditData*)nup::__nupMalloc(0x438);
                            if (signedData == 0) {
                                result = -5000;
                            } else {
                                memcpy(&signedData->format, &auditFormat, sizeof(auditFormat));
                                memcpy(&signedData->auditRecord, auditRecord, sizeof(NUPAuditRecord));
                                memcpy(signedData->signature, signature, sizeof(signature));
                                memcpy(signedData->signatureCertificate, signatureCertificate, 0x180);
                                memcpy(signedData->deviceCertificate, deviceCertificate, 0x180);
                                unsigned long dataSize = sizeof(NUPSignedAuditData);
                                encodedData = nup::__nupMalloc((dataSize + 2) / 3 * 4 + 1);
                                if (encodedData == 0) {
                                    result = -5000;
                                } else {
                                    __nupBase64Encode((u8*)encodedData, (u8*)signedData, sizeof(NUPSignedAuditData));
                                    ((u8*)encodedData)[(dataSize + 2) / 3 * 4] = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

done:
    if (result < 0 && encodedData != 0) {
        nup::__nupFree(encodedData);
        encodedData = 0;
    }
    if (signedData != 0) {
        nup::__nupFree(signedData);
    }
    if (ticketViews != 0) {
        nup::__nupFree(ticketViews);
    }
    if (auditRecord != 0) {
        nup::__nupFree(auditRecord);
    }
    if (signatureCertificate != 0) {
        nup::__nupFree(signatureCertificate);
    }
    if (deviceCertificate != 0) {
        nup::__nupFree(deviceCertificate);
    }
    *auditData = (char*)encodedData;
    return result;
}

#pragma dont_inline on
static s32 __nupGetTmdView(ESTitleId titleId, ESTmdView** tmdView) {
    u32 tmdViewSize;
    s32 result;
    ESTmdView* view = 0;
    result = ES_GetTmdView(titleId, 0, &tmdViewSize);
    if (result != -0x6a && result >= 0) {
        view = (ESTmdView*)nup::__nupMalloc(tmdViewSize);
        if (view != 0) {
            result = ES_GetTmdView(titleId, view, &tmdViewSize);
        } else {
            result = -5000;
        }
    }
    if (result < 0 && view != 0) {
        nup::__nupFree(view);
        view = 0;
    }
    *tmdView = view;
    return result;
}
#pragma dont_inline reset

static s32 __nupGetBootVersion(NUPContextInfo* context, ESTitleVersion* title) {
    s32 result;
    ESTmdView* tmdView = 0;

    if (title->titleId == 0x0000000100000001ULL) {
        u32 bootVersion;
        title->hasTicket = 1;
        title->hasTmd = 1;
        title->hasContent = 1;
        result = ES_GetBoot2Version(&bootVersion);
        if (result == 0) {
            if ((bootVersion & 0xffff) == bootVersion) {
                title->installedVersion = bootVersion;
            } else {
                result = -0x1389;
            }
        }
    } else {
        u32 i;
        for (i = 0; i < context->ownedTitleCount; i++) {
            if (context->ownedTitleIds[i] == title->titleId) {
                break;
            }
        }
        if (i < context->ownedTitleCount) {
            title->hasTicket = 1;
        }

        result = __nupGetTmdView(title->titleId, &tmdView);
        if (result == 0) {
            title->hasTmd = 1;
            title->installedVersion = tmdView->head.titleVersion;
        } else if (result == -0x6a) {
            result = 0;
        }

        if (result < 0) {
            goto done;
        }
        if (tmdView != 0) {
            result = ES_ListTitleContentsOnCard(title->titleId, 0, &title->contentCount);
            if (result == -0x6a) {
                result = 0;
            } else if (result == 0) {
                if (title->contentCount != 0) {
                    title->contentIds = (ESContentId*)nup::__nupMalloc(title->contentCount * sizeof(ESContentId));
                    if (title->contentIds == 0) {
                        result = -5000;
                        title->contentCount = 0;
                    } else {
                        result = ES_ListTitleContentsOnCard(title->titleId, title->contentIds, &title->contentCount);
                        if (result != 0) {
                            nup::__nupFree(title->contentIds);
                            title->contentIds = 0;
                            title->contentCount = 0;
                        }
                    }
                }
                if (result == 0 && title->contentCount >= tmdView->head.numContents) {
                    s32 contentIndex;
                    for (contentIndex = 0; contentIndex < tmdView->head.numContents; contentIndex++) {
                        u32 installedIndex;
                        for (installedIndex = 0; installedIndex < title->contentCount; installedIndex++) {
                            if (title->contentIds[installedIndex] == tmdView->contents[contentIndex].cid) {
                                break;
                            }
                        }
                        if (installedIndex == title->contentCount) {
                            break;
                        }
                    }
                    if (contentIndex >= tmdView->head.numContents) {
                        title->hasContent = 1;
                    }
                }
            }
        }
    }

done:
    if (tmdView != 0) {
        nup::__nupFree(tmdView);
    }
    return result;
}

static s32 __nupGetTicket(NUPTitleInfo* title, char* contentPrefixUrl) {
    u8* response = 0;
    unsigned long responseSize = 0;
    unsigned long urlSize = strlen(contentPrefixUrl) + 0x20;
    char* url = (char*)nup::__nupMalloc(urlSize);
    s32 result;

    if (url == 0) {
        result = -5000;
    } else {
        snprintf(url, urlSize, "%s/%016llx/cetk", contentPrefixUrl, title->titleId);
        result = __nupHttpGetFull(url, &response, &responseSize, 0, 0, 0);
        if (result == 0) {
            if (responseSize <= 0x2a4) {
                result = -0x138c;
            } else {
                title->ticket = nup::__nupMalloc(0x2a4);
                if (title->ticket == 0) {
                    result = -5000;
                } else {
                    title->ticketCertificate = nup::__nupMalloc(responseSize - 0x2a4);
                    if (title->ticketCertificate == 0) {
                        result = -5000;
                    } else {
                        title->ticketCertificateSize = responseSize - 0x2a4;
                        memcpy(title->ticket, response, 0x2a4);
                        memcpy(title->ticketCertificate, response + 0x2a4, title->ticketCertificateSize);
                    }
                }
            }
        }
    }

    if (url != 0) {
        nup::__nupFree(url);
    }
    if (response != 0) {
        nup::__nupFree(response);
    }
    return result;
}

static s32 __nupGetTmd(NUPTitleInfo* title, char* contentPrefixUrl) {
    u8* response = 0;
    unsigned long responseSize = 0;
    unsigned long urlSize = strlen(contentPrefixUrl) + 0x28;
    char* url = (char*)nup::__nupMalloc(urlSize);
    s32 result;

    if (url == 0) {
        result = -5000;
    } else {
        snprintf(url, urlSize, "%s/%016llx/tmd.%hu", contentPrefixUrl, title->titleId, title->serverVersion);
        result = __nupHttpGetFull(url, &response, &responseSize, 0, 0, 0);
        if (result == 0) {
            result = ES_GetTmdSize((ESTitleMeta*)response, &title->tmdSize);
            if (result == 0) {
                if (responseSize <= title->tmdSize) {
                    result = -0x138c;
                } else {
                    title->tmd = nup::__nupMalloc(title->tmdSize);
                    if (title->tmd == 0) {
                        result = -5000;
                    } else {
                        title->tmdCertificateSize = responseSize - title->tmdSize;
                        title->tmdCertificate = nup::__nupMalloc(title->tmdCertificateSize);
                        if (title->tmdCertificate == 0) {
                            result = -5000;
                        } else {
                            memcpy(title->tmd, response, title->tmdSize);
                            memcpy(title->tmdCertificate, response + title->tmdSize, title->tmdCertificateSize);
                            nup::__nupFree(response);
                            response = 0;
                            result = ES_DiGetTmdView((ESTitleMeta*)title->tmd, title->tmdSize, 0,
                                                     &title->tmdViewSize);
                            if (result == 0) {
                                title->tmdView = nup::__nupMalloc(title->tmdViewSize);
                                if (title->tmdView == 0) {
                                    result = -5000;
                                } else {
                                    result = ES_DiGetTmdView((ESTitleMeta*)title->tmd, title->tmdSize,
                                                            (ESTmdView*)title->tmdView, &title->tmdViewSize);
                                    if (result != 0) {
                                        nup::__nupFree(title->tmdView);
                                        title->tmdView = 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (url != 0) {
        nup::__nupFree(url);
    }
    if (response != 0) {
        nup::__nupFree(response);
    }
    return result;
}

static inline BOOL __nupHasContent(const NUPTitleInfo* title, ESContentId contentId) {
    if (title->contentCount == 0 || title->contentIds == 0) {
        return FALSE;
    }
    ESContentId* installedContent = title->contentIds;
    u32 index;
    for (index = 0; index < title->contentCount; index++) {
        if (contentId == *installedContent) {
            break;
        }
        installedContent++;
    }
    return index < title->contentCount;
}

static s32 __nupGetTitleSize(NUPTitleInfo* title) {
    s32 contentIndex;
    s32 result = 0;
    title->progressStep += 2;
    if (title->hasTicket == 0) {
        title->progressStep += 1;
    }
    if (title->hasTmd == 0 && title->contentCount == 0) {
        title->progressStep += 4;
    }
    title->progressStep += 5;
    title->installedContentSize += 0x4000;
    title->installedContentSize += (title->tmdSize + 0x3fff) & 0xffffc000;
    title->installedContentSize += 0x8000;
    title->installedContentSize += 0x4000;
    title->installedContentSize += 0x4000;
    for (contentIndex = 0; contentIndex < ((ESTmdView*)title->tmdView)->head.numContents; contentIndex++) {
        ESCmdView* content = &((ESTmdView*)title->tmdView)->contents[contentIndex];
        ESContentId cid = content->cid;
        if (!__nupHasContent(title, cid) ||
            title->titleId == 0x0000000100000001ULL) {
            if (content->size > 0xffffffefULL) {
                result = -0x1394;
                break;
            }
            title->updateContentSize += (content->size + 0xf) & 0xfffffffffffffff0ULL;
            title->installedContentSize += (content->size + 0x3fff) & 0xffffffffffffc000ULL;
            title->progressStep++;
        }
    }
    return result;
}

static s32 __nupGetContentFull(NUPContextInfo* context, NUPTitleInfo* title, char* contentPrefixUrl,
                               unsigned long contentId) {
    ESTmdView* tmdView;
    s32 contentIndex;
    s32 result;
    char* url = 0;
    u8* response = 0;
    unsigned long responseSize = 0;
    tmdView = (ESTmdView*)title->tmdView;

    for (contentIndex = 0; contentIndex < tmdView->head.numContents; contentIndex++) {
        if (contentId == ((ESTmdView*)title->tmdView)->contents[contentIndex].cid) {
            break;
        }
    }
    if (contentIndex >= tmdView->head.numContents) {
        result = -0x1389;
    } else {
        u64 contentSize = tmdView->contents[contentIndex].size;
        unsigned long urlSize;
        unsigned long alignedSize;
        alignedSize = (u32)((contentSize + 0xf) & ~0xfULL);
        urlSize = strlen(contentPrefixUrl) + 0x28;
        url = (char*)nup::__nupMalloc(urlSize);
        if (url == 0) {
            result = -5000;
        } else {
            snprintf(url, urlSize, "%s/%016llx/%08x", contentPrefixUrl, title->titleId, contentId);
            result = __nupHttpGetFull(url, &response, &responseSize, alignedSize,
                                      __nupUpdateStatusIncr, context);
            if (result == 0) {
                title->contentSize = responseSize;
                title->content = response;
            }
        }
    }
    if (url != 0) {
        nup::__nupFree(url);
    }
    if (response != 0 && result < 0) {
        nup::__nupFree(response);
    }
    return result;
}

static s32 __nupGetContentIncr(NUPContextInfo* context, NUPTitleInfo* title, char* contentPrefixUrl) {
    s32 contentIndex;
    s32 result = 0;
    unsigned long urlSize = strlen(contentPrefixUrl) + 0x28;
    char* url = (char*)nup::__nupMalloc(urlSize);

    if (url == 0) {
        result = -5000;
    } else {
        for (contentIndex = 0; contentIndex < ((ESTmdView*)title->tmdView)->head.numContents; contentIndex++) {
            ESContentId contentId = ((ESTmdView*)title->tmdView)->contents[contentIndex].cid;
            if (!__nupHasContent(title, contentId)) {
                snprintf(url, urlSize, "%s/%016llx/%08x", contentPrefixUrl, title->titleId, contentId);
                unsigned long contentSize = ((ESTmdView*)title->tmdView)->contents[contentIndex].size;
                ESFd fd = ES_ImportContentBegin(title->titleId, contentId);
                result = fd;
                if (result < 0) {
                    ES_ImportContentEnd(fd);
                    break;
                }
                result = __nupHttpGetIncr(url, (contentSize + 0xf) & 0xfffffff0,
                                          __nupUpdateStatusIncr, context, __nupHttpBufferFlushES, (void*)fd);
                if (result != 0) {
                    ES_ImportContentEnd(fd);
                    break;
                }
                result = ES_ImportContentEnd(fd);
                if (result != 0) {
                    break;
                }
            }
        }
    }
    if (url != 0) {
        nup::__nupFree(url);
    }
    return result;
}

static void __nupCleanupTitleInfo(NUPTitleInfo* title) {
    if (title != 0) {
        if (title->ticket != 0) {
            nup::__nupFree(title->ticket);
        }
        if (title->content != 0) {
            nup::__nupFree(title->content);
        }
        if (title->tmd != 0) {
            nup::__nupFree(title->tmd);
        }
        if (title->ticketCertificate != 0) {
            nup::__nupFree(title->ticketCertificate);
        }
        if (title->tmdCertificate != 0) {
            nup::__nupFree(title->tmdCertificate);
        }
        if (title->tmdView != 0) {
            nup::__nupFree(title->tmdView);
        }
        if (title->contentIds != 0) {
            nup::__nupFree(title->contentIds);
        }
        title->ticket = 0;
        title->content = 0;
        title->tmd = 0;
        title->ticketCertificate = 0;
        title->tmdCertificate = 0;
        title->tmdView = 0;
        title->contentIds = 0;
    }
}

static void __nupCleanup(NUPContextInfo* context) {
    if (context->titles != 0) {
        for (u32 i = 0; i < context->titleCount; i++) {
            NUPTitleInfo* title = &context->titles[i];
            if (title != 0) {
                __nupCleanupTitleInfo(title);
            }
        }
        nup::__nupFree(context->titles);
        context->titles = 0;
    }
    if (context->ownedTitleIds != 0) {
        nup::__nupFree(context->ownedTitleIds);
    }
    context->ownedTitleIds = 0;
    if (context->contentPrefixUrl != 0) {
        nup::__nupFree(context->contentPrefixUrl);
    }
    context->contentPrefixUrl = 0;
    if (context->uncachedContentPrefixUrl != 0) {
        nup::__nupFree(context->uncachedContentPrefixUrl);
    }
    context->uncachedContentPrefixUrl = 0;
    if (context->serverAddress != 0) {
        nup::__nupFree((void*)context->serverAddress);
    }
    context->serverAddress = 0;
    if (context->countryCode != 0) {
        nup::__nupFree((void*)context->countryCode);
    }
    context->countryCode = 0;
    if (context->productArea != 0) {
        nup::__nupFree((void*)context->productArea);
    }
    context->productArea = 0;
}

static s32 __nupUpdateTitle(NUPContextInfo* context, NUPTitleInfo* title, char* contentPrefixUrl,
                            char* uncachedContentPrefixUrl) {
    s32 result;
    if (title->titleId == 0x0000000100000001ULL) {
        result = __nupGetTicket(title, contentPrefixUrl);
        if (result != 0) {
            goto done;
        }
        ESTmdView* tmdView = (ESTmdView*)title->tmdView;
        if (tmdView->head.numContents != 1) {
            result = -0x1389;
            goto done;
        }
        result = __nupGetContentFull(context, title, uncachedContentPrefixUrl, tmdView->contents[0].cid);
        if (result != 0) {
            goto done;
        }
        result = ES_ImportBoot((ESTicket*)title->ticket, title->ticketCertificate,
                               title->ticketCertificateSize, (ESTitleMeta*)title->tmd,
                               title->tmdSize, title->tmdCertificate, title->tmdCertificateSize,
                               0, 0, title->content, title->contentSize);
        if (result != 0) {
            goto done;
        }
    } else {
        ISFSStats stats;
        s32 hasSpace = ISFS_GetStats(&stats);
        if (hasSpace == 0 && stats.freeBlocks >= (title->installedContentSize >> 14) &&
            title->progressStep <= stats.freeInodes) {
            hasSpace = 1;
        }
        result = hasSpace;
        if (result == 0) {
            result = -0x1392;
            goto done;
        }
        if (result < 0) {
            goto done;
        }
        result = __nupGetTicket(title, contentPrefixUrl);
        if (result != 0) {
            goto done;
        }
        result = ES_ImportTicket((ESTicket*)title->ticket, title->ticketCertificate,
                                 title->ticketCertificateSize, 0, 0, 0);
        if (result != 0) {
            goto done;
        }
        result = ES_ImportTitleInit((ESTitleMeta*)title->tmd, title->tmdSize, title->tmdCertificate,
                                    title->tmdCertificateSize, 0, 0, 0, 1);
        if (result != 0) {
            ES_ImportTitleCancel();
            goto done;
        }
        result = __nupGetContentIncr(context, title, uncachedContentPrefixUrl);
        if (result != 0) {
            ES_ImportTitleCancel();
            goto done;
        }
        result = ES_ImportTitleDone();
        if (result != 0) {
            goto done;
        }
    }
    __nupCleanupTitleInfo(title);
    title->updateRequired = 0;
done:
    return result;
}

extern "C" void* __nupOp(void* argument) {
    NUPContextInfo* context = (NUPContextInfo*)argument;
    u8* response = 0;
    ESTmdView* tmdView = 0;
    char* auditData = 0;
    NUPTitleInfo* bootTitle = 0;
    NUPTitleInfo* menuTitle = 0;
    NUPTitleInfo* systemTitle = 0;
    u32 deviceId;
    u32 bootVersion;
    u32 serverBootVersion = 0;
    u16 bootTitleVersion;
    u16 systemMenuVersion;
    ESTitleId currentTitleId;
    char messageId[0x15];
    NANDStatus auditStatus;
    s32 result;
    u32 i;
    BOOL needsAudit;

    snprintf(messageId, sizeof(messageId), "%llu", OSGetTime());
    result = ES_GetDeviceId(&deviceId);
    if (result != 0) {
        goto done;
    }
    result = ES_GetBoot2Version(&bootVersion);
    if (result == 0) {
        serverBootVersion = bootVersion;
        if ((u16)serverBootVersion != bootVersion) {
            result = -0x1389;
        }
    }
    if (result < 0) {
        goto done;
    }
    result = __nupGetTmdView(0x0000000100000002ULL, &tmdView);
    if (result < 0) {
        goto done;
    }
    bootTitleVersion = tmdView->head.titleVersion;
    currentTitleId = tmdView->head.sysVersion;
    nup::__nupFree(tmdView);
    tmdView = 0;
    result = __nupGetTmdView(currentTitleId, &tmdView);
    if (result < 0) {
        goto done;
    }
    systemMenuVersion = tmdView->head.titleVersion;
    nup::__nupFree(tmdView);
    tmdView = 0;
    result = ES_ListOwnedTitles(0, &context->ownedTitleCount);
    if (result == 0) {
        context->ownedTitleIds = (ESTitleId*)nup::__nupMalloc(context->ownedTitleCount * sizeof(ESTitleId));
        if (context->ownedTitleIds != 0) {
            result = ES_ListOwnedTitles(context->ownedTitleIds, &context->ownedTitleCount);
        } else {
            result = -5000;
        }
    }
    if (result != 0) {
        goto done;
    }
    needsAudit = TRUE;
    if (NANDGetStatus("NUPAUDIT", &auditStatus) == 0) {
        needsAudit = FALSE;
    }
    if (needsAudit) {
        result = __nupGetAuditData(context, &auditData);
        if (result != 0) {
            goto done;
        }
    }
    OSLockMutex(&context->mutex);
    context->progress.result = 2;
    context->progress.message = __nupStatusMessage[2];
    OSUnlockMutex(&context->mutex);
    result = __nupGetServerInfo((char*)context->serverAddress, messageId,
                                0x0000000100000000ULL | deviceId,
                                (char*)context->productArea, (char*)context->countryCode,
                                context->systemVersion, auditData, serverBootVersion, bootTitleVersion,
                                currentTitleId, systemMenuVersion, (char**)&response);
    if (result != 0) {
        goto done;
    }
    if (auditData != 0) {
        nup::__nupFree(auditData);
    }
    auditData = 0;
    result = __nupParseServerInfo(context, (char*)response, messageId,
                                 0x0000000100000000ULL | deviceId);
    if (result != 0) {
        goto done;
    }
    if (needsAudit != context->uploadAuditData) {
        result = __nupSetAuditState(context->uploadAuditData);
        if (result != 0) {
            result = 0;
        }
    }
    for (i = 0; i < context->titleCount; i++) {
        NUPTitleInfo* title = &context->titles[i];
        result = __nupGetBootVersion(context, (ESTitleVersion*)title);
        if (result == 0) {
            if (title->hasTicket && title->hasTmd && title->hasContent &&
                title->installedVersion >= title->serverVersion) {
                title->updateRequired = 0;
            } else {
                title->updateRequired = 1;
            }
        }
        if (result >= 0) {
            result = title->updateRequired;
        }
        if (result < 0) {
            goto done;
        }
        if (result != 0) {
            context->updateCount++;
        }
    }
    for (i = 0; i < context->titleCount; i++) {
        NUPTitleInfo* title = &context->titles[i];
        if (title->updateRequired != 0) {
            result = __nupGetTmd(title, context->uncachedContentPrefixUrl);
            if (result < 0) {
                goto done;
            }
        }
    }
    for (i = 0; i < context->titleCount; i++) {
        NUPTitleInfo* title = &context->titles[i];
        if (title->updateRequired != 0) {
            result = __nupGetTitleSize(title);
            if (result < 0) {
                goto done;
            }
            context->downloadedBytes += context->titles[i].updateContentSize;
        }
    }
    {
        u64 totalBytes = context->downloadedBytes;
        OSLockMutex(&context->mutex);
        context->progress.totalBytes = totalBytes;
        context->progress.completedBytes = 0;
        OSUnlockMutex(&context->mutex);
    }
    OSLockMutex(&context->mutex);
    context->progress.result = 3;
    context->progress.message = __nupStatusMessage[3];
    OSUnlockMutex(&context->mutex);
    for (i = 0; i < context->titleCount; i++) {
        NUPTitleInfo* title = &context->titles[i];
        if (title->titleId == 0x0000000100000001ULL) {
            bootTitle = title;
        } else if (title->titleId == 0x0000000100000002ULL) {
            menuTitle = title;
        } else if (title->titleId == currentTitleId) {
            systemTitle = title;
        }
        if (bootTitle != 0 && menuTitle != 0 && systemTitle != 0) {
            break;
        }
    }
    if (menuTitle != 0 && menuTitle->updateRequired != 0) {
        ESTitleId requiredSystemTitle = ((ESTmdView*)menuTitle->tmdView)->head.sysVersion;
        for (i = 0; i < context->titleCount; i++) {
            if (context->titles[i].titleId == requiredSystemTitle) {
                systemTitle = &context->titles[i];
                break;
            }
        }
    }
    if (bootTitle != 0 && bootTitle->updateRequired != 0) {
        result = __nupUpdateTitle(context, bootTitle, context->uncachedContentPrefixUrl,
                                 context->contentPrefixUrl);
        if (result < 0) {
            goto done;
        }
    }
    if (systemTitle != 0 && systemTitle->updateRequired != 0) {
        result = __nupUpdateTitle(context, systemTitle, context->uncachedContentPrefixUrl,
                                 context->contentPrefixUrl);
        if (result < 0) {
            goto done;
        }
    }
    if (menuTitle != 0 && menuTitle->updateRequired != 0) {
        result = __nupUpdateTitle(context, menuTitle, context->uncachedContentPrefixUrl,
                                 context->contentPrefixUrl);
        if (result < 0) {
            goto done;
        }
    }
    for (i = 0; i < context->titleCount; i++) {
        NUPTitleInfo* title = &context->titles[i];
        if (title->updateRequired != 0) {
            result = __nupUpdateTitle(context, title, context->uncachedContentPrefixUrl,
                                     context->contentPrefixUrl);
            if (result < 0) {
                goto done;
            }
        }
    }
done:
    if (tmdView != 0) {
        nup::__nupFree(tmdView);
    }
    if (response != 0) {
        nup::__nupFree(response);
    }
    if (auditData != 0) {
        nup::__nupFree(auditData);
    }
    __nupCleanup(context);
    if (result >= 0) {
        OSLockMutex(&context->mutex);
        context->progress.result = 0;
        context->progress.message = __nupStatusMessage[0];
        OSUnlockMutex(&context->mutex);
    } else {
        OSLockMutex(&context->mutex);
        context->progress.result = result;
        if (result < 0) {
            context->progress.message = __nupStatusMessage[5];
        } else if (result >= 4) {
            context->progress.message = __nupStatusMessage[4];
        } else {
            context->progress.message = __nupStatusMessage[result];
        }
        OSUnlockMutex(&context->mutex);
    }
    return 0;
}

void* NUP_Init(MEMAllocator* allocator) {
    void* instance = 0;
    if (nup::__nupRegisterAllocator(allocator) == 0) {
        instance = nup::__nupMalloc(sizeof(NUPContextInfo));
        if (instance != 0) {
            memset(instance, 0, sizeof(NUPContextInfo));
            NUPContextInfo* context = (NUPContextInfo*)instance;
            OSInitMutex(&context->mutex);
            OSLockMutex(&context->mutex);
            context->progress.message = (context->progress.result = 1, __nupStatusMessage[1]);
            OSUnlockMutex(&context->mutex);
        }
    }
    return instance;
}

int NUP_Start(void* instance, const char* serverAddress, const char* countryCode, void* productArea, int systemVersion) {
    s32 result = 0;
    NUPContextInfo* context = (NUPContextInfo*)instance;

    if (serverAddress == 0 || *serverAddress == '\0') {
        result = -5002;
    } else if (countryCode == 0 || *countryCode == '\0') {
        result = -5002;
    } else if (productArea == 0 || *(const char*)productArea == '\0') {
        result = -5002;
    } else {
        unsigned long length = strlen(serverAddress) + 1;
        context->serverAddress = (const char*)nup::__nupMalloc(length);
        if (context->serverAddress == 0) {
            result = -5000;
        } else {
            strncpy((char*)context->serverAddress, serverAddress, length);
            length = strlen(countryCode) + 1;
            context->countryCode = (const char*)nup::__nupMalloc(length);
            if (context->countryCode == 0) {
                result = -5000;
            } else {
                strncpy((char*)context->countryCode, countryCode, length);
                length = strlen((const char*)productArea) + 1;
                context->productArea = (const char*)nup::__nupMalloc(length);
                if (context->productArea == 0) {
                    result = -5000;
                } else {
                    strncpy((char*)context->productArea, (const char*)productArea, length);
                    context->systemVersion = systemVersion;
                    if (context->threadStarted != 0) {
                        result = -5003;
                    } else if (OSCreateThread(&context->thread, __nupOp, context,
                                              context->threadStack + 0x400, 0x2000, 0x10, 0) == 0) {
                        result = -5001;
                    } else {
                        context->threadStarted = 1;
                        OSResumeThread(&context->thread);
                    }
                }
            }
        }
    }

    if (result < 0) {
        OSLockMutex(&context->mutex);
        context->progress.result = result;
        if (result < 0) {
            context->progress.message = __nupStatusMessage[5];
        } else {
            if (result >= 4) {
                context->progress.message = __nupStatusMessage[4];
            } else {
                context->progress.message = __nupStatusMessage[result];
            }
        }
        OSUnlockMutex(&context->mutex);
    }
    return result;
}

int NUP_Finish(void* instance) {
    s32 result = 0;
    NUPContextInfo* context = (NUPContextInfo*)instance;
    static void* rvThread;

    if (context->threadStarted != 0) {
        if (OSJoinThread(&context->thread, &rvThread) == 0) {
            result = -5001;
        } else {
            context->threadStarted = 0;
        }
    }
    if (context != 0) {
        nup::__nupFree(context);
    }
    return result;
}
