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
    u32 titleId;
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

static s32 __nupParseServerInfo(NUPContextInfo* context, char* response, char* messageId,
                               unsigned long long deviceId) {
    s32 result = 0;
    char* start;
    char* end;
    char* afterEnd;
    char* cursor;
    size_t valueLength;
    size_t titleCount;

    if (response == 0) {
        result = -5004;
        goto done;
    }
    {
        const char* versionEndTag = "</Version>";
        const char* versionStartTag = "<Version>";
        start = strstr(response, versionStartTag);
        if (start == 0) {
            result = -5004;
            goto done;
        }
        end = strstr(start, versionEndTag);
        if (end == 0) {
            afterEnd = 0;
        } else {
            afterEnd = end + strlen(versionEndTag);
        }
        if (afterEnd == 0) {
            result = -5004;
            goto done;
        }
        start += strlen(versionStartTag);
        valueLength = end - start;
        if (valueLength != strlen("1.0") || strncmp(start, "1.0", valueLength) != 0) {
            result = -5004;
            goto done;
        }
    }

    {
        const char* deviceIdEndTag = "</DeviceId>";
        const char* deviceIdStartTag = "<DeviceId>";
        start = strstr(response, deviceIdStartTag);
        if (start == 0) {
            result = -5004;
            goto done;
        }
        end = strstr(start, deviceIdEndTag);
        if (end == 0) {
            afterEnd = 0;
        } else {
            afterEnd = end + strlen(deviceIdEndTag);
        }
        if (afterEnd == 0) {
            result = -5004;
            goto done;
        }
        start += strlen(deviceIdStartTag);
        if (strtoull(start, 0, 10) != deviceId) {
            result = -5004;
            goto done;
        }
    }

    {
        const char* messageIdEndTag = "</MessageId>";
        const char* messageIdStartTag = "<MessageId>";
        start = strstr(response, messageIdStartTag);
        if (start == 0) {
            result = -5004;
            goto done;
        }
        end = strstr(start, messageIdEndTag);
        if (end == 0) {
            afterEnd = 0;
        } else {
            afterEnd = end + strlen(messageIdEndTag);
        }
        if (afterEnd == 0) {
            result = -5004;
            goto done;
        }
        start += strlen(messageIdStartTag);
        valueLength = end - start;
        if (valueLength != strlen(messageId) || strncmp(start, messageId, valueLength) != 0) {
            result = -5004;
            goto done;
        }
    }

    {
        const char* errorCodeEndTag = "</ErrorCode>";
        const char* errorCodeStartTag = "<ErrorCode>";
        start = strstr(response, errorCodeStartTag);
        if (start == 0) {
            result = -5004;
            goto done;
        }
        end = strstr(start, errorCodeEndTag);
        if (end == 0) {
            afterEnd = 0;
        } else {
            afterEnd = end + strlen(errorCodeEndTag);
        }
        if (afterEnd == 0) {
            result = -5004;
            goto done;
        }
        start += strlen(errorCodeStartTag);
        valueLength = end - start;
        if (valueLength != strlen("0") || strncmp(start, "0", valueLength) != 0) {
            result = -5004;
            goto done;
        }
    }

    {
        const char* uploadAuditEndTag = "</UploadAuditData>";
        const char* uploadAuditStartTag = "<UploadAuditData>";
        start = strstr(response, uploadAuditStartTag);
        if (start == 0) {
            result = -5004;
            goto done;
        }
        end = strstr(start, uploadAuditEndTag);
        if (end == 0) {
            afterEnd = 0;
        } else {
            afterEnd = end + strlen(uploadAuditEndTag);
        }
        if (afterEnd == 0) {
            result = -5004;
            goto done;
        }
        start += strlen(uploadAuditStartTag);
        valueLength = end - start;
        if (valueLength != strlen("0") || (*start != '0' && *start != '1')) {
            result = -5004;
            goto done;
        }
        context->uploadAuditData = *start == '1';
    }

    {
        const char* contentPrefixEndTag = "</ContentPrefixURL>";
        const char* contentPrefixStartTag = "<ContentPrefixURL>";
        start = strstr(response, contentPrefixStartTag);
        if (start == 0) {
            result = -5004;
            goto done;
        }
        end = strstr(start, contentPrefixEndTag);
        if (end == 0) {
            afterEnd = 0;
        } else {
            afterEnd = end + strlen(contentPrefixEndTag);
        }
        if (afterEnd == 0) {
            result = -5004;
            goto done;
        }
        start += strlen(contentPrefixStartTag);
        valueLength = end - start;
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
        start = strstr(response, uncachedPrefixStartTag);
        if (start == 0) {
            result = -5004;
            goto done;
        }
        end = strstr(start, uncachedPrefixEndTag);
        if (end == 0) {
            afterEnd = 0;
        } else {
            afterEnd = end + strlen(uncachedPrefixEndTag);
        }
        if (afterEnd == 0) {
            result = -5004;
            goto done;
        }
        start += strlen(uncachedPrefixStartTag);
        valueLength = end - start;
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
            char* titleStart = strstr(cursor, titleIdStartTag);
            if (titleStart == 0) {
                break;
            }
            char* titleEnd = strstr(titleStart, titleIdEndTag);
            if (titleEnd == 0) {
                break;
            }
            afterEnd = titleEnd + strlen(titleIdEndTag);
            char* versionStart = strstr(afterEnd, versionStartTag);
            if (versionStart == 0) {
                break;
            }
            char* versionEnd = strstr(versionStart, versionEndTag);
            if (versionEnd == 0) {
                break;
            }
            afterEnd = versionEnd + strlen(versionEndTag);
            cursor = afterEnd;
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
        for (;;) {
            char* titleStart = strstr(cursor, titleIdStartTag);
            if (titleStart == 0) {
                break;
            }
            char* titleEnd = strstr(titleStart, titleIdEndTag);
            if (titleEnd == 0) {
                result = -5004;
                goto done;
            }
            afterEnd = titleEnd + strlen(titleIdEndTag);
            titleStart += strlen(titleIdStartTag);
            char* versionStart = strstr(afterEnd, versionStartTag);
            if (versionStart == 0) {
                result = -5004;
                goto done;
            }
            char* versionEnd = strstr(versionStart, versionEndTag);
            if (versionEnd == 0) {
                result = -5004;
                goto done;
            }
            versionStart += strlen(versionStartTag);
            afterEnd = versionEnd + strlen(versionEndTag);

            char* parsedEnd;
            unsigned long long titleId = strtoull(titleStart, &parsedEnd, 16);
            if (parsedEnd != titleEnd) {
                result = -5004;
                goto done;
            }
            unsigned long version = strtoul(versionStart, &parsedEnd, 10);
            if (parsedEnd != versionEnd || version > 0xffff) {
                result = -5004;
                goto done;
            }
            NUPTitleInfo* title = &context->titles[context->titleCount++];
            title->titleId = titleId;
            title->serverVersion = version;
            cursor = afterEnd;
        }
    }

done:
    return result;
}

static s32 __nupGetServerInfo(char* serverAddress, char* messageId, unsigned long long deviceId,
                              char* productArea, char* countryCode, unsigned long systemVersion,
                              char* auditData, unsigned short bootVersion, unsigned short systemMenuVersion,
                              unsigned long long systemMenuTitleId, unsigned short currentTitleVersion,
                              char** response) {
    s32 result;
    u8* responseData = 0;
    unsigned long responseSize = 0;
    char headers[0x56] =
        "User-Agent: wii libnup/1.0\r\n"
        "SOAPAction: \"urn:nus.wsapi.broadon.com/GetSystemUpdate\"\r\n";
    char* request = 0;
    char* endpoint = 0;
    unsigned long requestSize;
    unsigned long endpointSize;

    endpointSize = strlen(serverAddress) + 0x26;
    endpoint = (char*)nup::__nupMalloc(endpointSize);
    if (endpoint == 0) {
        result = -5000;
    } else {
        snprintf(endpoint, endpointSize, "https://%s/nus/services/NetUpdateSOAP", serverAddress);
        requestSize = strlen(messageId) + strlen(productArea) + strlen(countryCode) + 0x449;
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
                     systemMenuTitleId, systemMenuVersion,
                     (unsigned long long)0x0000000100000002ULL, currentTitleVersion,
                     systemVersion, auditData != 0 ? auditData : "");
            result = __nupHttpPostFull(endpoint, headers, request, &responseData, &responseSize, 0, 0, 0);
            if (result == 0) {
                char* responseCopy = (char*)nup::__nupMalloc(responseSize + 1);
                *response = responseCopy;
                if (responseCopy == 0) {
                    result = -5000;
                } else {
                    strncpy(responseCopy, (char*)responseData, responseSize);
                    responseCopy[responseSize] = '\0';
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

static u32 __nupSetAuditState(u8 state) {
    s32 result;
    if (state != 0) {
        result = NANDDelete("NUPAUDIT");
        if (result != 0 && result != -12) {
            result -= 6000;
        } else {
            result = 0;
        }
    } else {
        result = NANDCreateDir("NUPAUDIT", 0x30, 3);
        if (result != 0 && result != -6) {
            result -= 6000;
        } else {
            result = 0;
        }
    }
    return result;
}

static void __nupBase64Encode(u8* output, u8* input, unsigned long length) {
    const char* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    u8* end = input + length;
    u32 value = 0;
    u32 count = 0;
    static char fillByte = '=';

    while (input != end) {
        count++;
        value = value << 8 | *input++;
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
        output[3] = fillByte;
        return;
    }
    if (count != 1) {
        return;
    }
    value <<= 16;
    output[0] = alphabet[value >> 18 & 0x3f];
    output[1] = alphabet[value >> 12 & 0x3f];
    output[2] = fillByte;
    output[3] = fillByte;
}

static s32 __nupGetAuditData(NUPContextInfo* context, char** auditData) {
    s32 result = 0;
    ESTitleId selectedTitle = 0;
    ESTicketView* ticketViews = 0;
    u32 viewCount;
    u32 selected = 0;
    u32 selectedIndex = 0;
    void* auditRecord = 0;
    void* signatureCertificate = 0;
    void* deviceCertificate = 0;
    NUPSignedAuditData* signedData = 0;
    void* encodedData = 0;
    ESSignature signature ALIGN32;
    char deviceInfo[0x21];
    u32 i;

    for (i = 0; i < context->ownedTitleCount && selected == 0; i++) {
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
                    selectedTitle = ownedTitleId;
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
            deviceInfo[5] = '\0';
            productCodeSize = strlen(deviceInfo);
        }
        if (SCGetProductSNString(deviceInfo + productCodeSize, sizeof(deviceInfo) - productCodeSize) == 0) {
            memset(deviceInfo + productCodeSize, 0, sizeof(deviceInfo) - productCodeSize);
            strncpy(deviceInfo + productCodeSize, __nupStatusMessage[4], sizeof(deviceInfo) - productCodeSize);
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
                                memcpy(&signedData->titleId, &selectedTitle, sizeof(selectedTitle));
                                memcpy(&signedData->auditRecord, auditRecord, sizeof(NUPAuditRecord));
                                memcpy(signedData->signature, signature, sizeof(signature));
                                memcpy(signedData->signatureCertificate, signatureCertificate, 0x180);
                                memcpy(signedData->deviceCertificate, deviceCertificate, 0x180);
                                encodedData = nup::__nupMalloc(0x5a1);
                                if (encodedData == 0) {
                                    result = -5000;
                                } else {
                                    __nupBase64Encode((u8*)encodedData, (u8*)signedData, sizeof(NUPSignedAuditData));
                                    ((u8*)encodedData)[0x5a0] = 0;
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

static s32 __nupGetTmdView(ESTitleId titleId, ESTmdView** tmdView) {
    u32 tmdViewSize = 0;
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

static s32 __nupGetBootVersion(NUPContextInfo* context, ESTitleVersion* title) {
    s32 result = 0;
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

        if (result >= 0) {
            result = ES_ListTitleContentsOnCard(title->titleId, 0, &title->contentCount);
            if (result == -0x6a) {
                result = 0;
            } else if (result == 0 && tmdView != 0 && title->contentCount != 0) {
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
                    } else {
                        u32 contentIndex;
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
                        if (contentIndex == tmdView->head.numContents) {
                            title->hasContent = 1;
                        }
                    }
                }
            }
        }
    }

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

static s32 __nupGetTitleSize(NUPTitleInfo* title) {
    ESTmdView* tmdView = (ESTmdView*)title->tmdView;
    u32 contentIndex;
    s32 result = 0;
    title->progressStep += 2;
    if (title->hasTicket == 0) {
        title->progressStep += 1;
    }
    if (title->hasTmd == 0 && title->contentCount == 0) {
        title->progressStep += 4;
    }
    title->progressStep += 5;
    title->installedContentSize += 0x18000 + ((title->tmdSize + 0x3fff) & 0xffffc000);
    for (contentIndex = 0; contentIndex < tmdView->head.numContents; contentIndex++) {
        ESContentMeta* content = (ESContentMeta*)&tmdView->contents[contentIndex];
        u32 ownedIndex;
        ownedIndex = 0;
        if (title->contentCount != 0 && title->contentIds != 0) {
            for (; ownedIndex < title->contentCount; ownedIndex++) {
                if (title->contentIds[ownedIndex] == content->cid) {
                    break;
                }
            }
        }
        if (title->contentIds == 0 || ownedIndex == title->contentCount ||
            title->titleId == 0x0000000100000001ULL) {
            if (content->size > 0xfffffff0ULL) {
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
    ESTmdView* tmdView = (ESTmdView*)title->tmdView;
    u32 contentIndex;
    s32 result;
    char* url = 0;
    u8* response = 0;
    unsigned long responseSize = 0;

    for (contentIndex = 0; contentIndex < tmdView->head.numContents; contentIndex++) {
        if (tmdView->contents[contentIndex].cid == contentId) {
            break;
        }
    }
    if (contentIndex >= tmdView->head.numContents) {
        result = -0x1389;
    } else {
        unsigned long contentSize = tmdView->contents[contentIndex].size;
        unsigned long alignedSize = (contentSize + 0xf) & 0xfffffff0;
        unsigned long urlSize = strlen(contentPrefixUrl) + 0x28;
        url = (char*)nup::__nupMalloc(urlSize);
        if (url == 0) {
            result = -5000;
        } else {
            snprintf(url, urlSize, "%s/%016llx/%08x", contentPrefixUrl, title->titleId, contentId);
            result = __nupHttpGetFull(url, &response, &responseSize, alignedSize,
                                      __nupUpdateStatusIncr, context);
            if (result == 0) {
                title->content = response;
                title->contentSize = responseSize;
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
    u32 contentIndex;
    s32 result = 0;
    unsigned long urlSize = strlen(contentPrefixUrl) + 0x28;
    char* url = (char*)nup::__nupMalloc(urlSize);

    if (url == 0) {
        result = -5000;
    } else {
        for (contentIndex = 0; contentIndex < ((ESTmdView*)title->tmdView)->head.numContents; contentIndex++) {
            ESContentId contentId = ((ESTmdView*)title->tmdView)->contents[contentIndex].cid;
            u32 ownedIndex = 0;
            int alreadyInstalled = 0;
            if (title->contentCount != 0 && title->contentIds != 0) {
                for (; ownedIndex < title->contentCount; ownedIndex++) {
                    if (title->contentIds[ownedIndex] == contentId) {
                        alreadyInstalled = 1;
                        break;
                    }
                }
            }
            if (alreadyInstalled == 0) {
                snprintf(url, urlSize, "%s/%016llx/%08x", contentPrefixUrl, title->titleId, contentId);
                unsigned long contentSize = ((ESTmdView*)title->tmdView)->contents[contentIndex].size;
                ESFd fd = ES_ImportContentBegin(title->titleId, contentId);
                if (fd < 0) {
                    ES_ImportContentEnd(fd);
                    result = fd;
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
    s32 result = 0;
    if (title->titleId == 0x0000000100000001ULL) {
        result = __nupGetTicket(title, contentPrefixUrl);
        if (result == 0) {
            ESTmdView* tmdView = (ESTmdView*)title->tmdView;
            if (tmdView->head.numContents != 1) {
                result = -0x1389;
            } else {
                result = __nupGetContentFull(context, title, contentPrefixUrl, tmdView->contents[0].cid);
                if (result == 0) {
                    result = ES_ImportBoot((ESTicket*)title->ticket, title->ticketCertificate,
                                           title->ticketCertificateSize, (ESTitleMeta*)title->tmd,
                                           title->tmdSize, title->tmdCertificate, title->tmdCertificateSize,
                                           0, 0, title->content, title->contentSize);
                }
            }
        }
    } else {
        ISFSStats stats;
        result = ISFS_GetStats(&stats);
        if (result == 0) {
            if (stats.freeBlocks >= (title->installedContentSize >> 14) &&
                stats.freeInodes >= title->progressStep) {
                result = 1;
            }
        }
        if (result == 0) {
            result = -0x1392;
        } else if (result > 0) {
            result = __nupGetTicket(title, contentPrefixUrl);
        }
        if (result == 0) {
            result = ES_ImportTicket((ESTicket*)title->ticket, title->ticketCertificate,
                                     title->ticketCertificateSize, 0, 0, 0);
        }
        if (result == 0) {
            result = ES_ImportTitleInit((ESTitleMeta*)title->tmd, title->tmdSize, title->tmdCertificate,
                                        title->tmdCertificateSize, 0, 0, 0, 1);
            if (result != 0) {
                ES_ImportTitleCancel();
            }
        }
        if (result == 0) {
            result = __nupGetContentIncr(context, title, uncachedContentPrefixUrl);
            if (result != 0) {
                ES_ImportTitleCancel();
            }
        }
        if (result == 0) {
            result = ES_ImportTitleDone();
        }
    }
    if (result == 0) {
        __nupCleanupTitleInfo(title);
        title->updateRequired = 0;
    }
    return result;
}

extern "C" void* __nupOp(void* argument) {
    NUPContextInfo* context = (NUPContextInfo*)argument;
    u8* response;
    ESTmdView* tmdView;
    char* auditData;
    u32 deviceId;
    u32 bootVersion;
    u16 bootTitleVersion;
    u16 systemMenuVersion;
    ESTitleId systemMenuTitleId;
    char messageId[0x50];
    NANDStatus auditStatus;
    s32 result = 0;
    u32 i;

    response = 0;
    tmdView = 0;
    auditData = 0;
    snprintf(messageId, 0x15, "%llu", OSGetTime());
    result = ES_GetDeviceId(&deviceId);
    if (result == 0) {
        result = ES_GetBoot2Version(&bootVersion);
        if (result == 0 && (bootVersion & 0xffff) != bootVersion) {
            result = -0x1389;
        }
    }
    if (result >= 0) {
        result = __nupGetTmdView(0x0000000100000002ULL, &tmdView);
        if (result >= 0) {
            bootTitleVersion = tmdView->head.titleVersion;
            systemMenuTitleId = tmdView->head.sysVersion;
            nup::__nupFree(tmdView);
            tmdView = 0;
            result = __nupGetTmdView(systemMenuTitleId, &tmdView);
            if (result >= 0) {
                systemMenuVersion = tmdView->head.titleVersion;
            }
        }
    }
    if (result >= 0) {
        nup::__nupFree(tmdView);
        tmdView = 0;
    }
    if (result >= 0) {
        result = ES_ListOwnedTitles(0, &context->ownedTitleCount);
        if (result == 0) {
            context->ownedTitleIds = (ESTitleId*)nup::__nupMalloc(context->ownedTitleCount * sizeof(ESTitleId));
            if (context->ownedTitleIds == 0) {
                result = -5000;
            } else {
                result = ES_ListOwnedTitles(context->ownedTitleIds, &context->ownedTitleCount);
            }
        }
    }
    s32 auditResult = 0;
    if (result >= 0) {
        auditResult = NANDGetStatus("NUPAUDIT", &auditStatus);
        if (auditResult != 0) {
            result = __nupGetAuditData(context, &auditData);
        }
    }
    if (result >= 0) {
        OSLockMutex(&context->mutex);
        context->progress.result = 2;
        context->progress.message = __nupStatusMessage[2];
        OSUnlockMutex(&context->mutex);
        result = __nupGetServerInfo((char*)context->serverAddress, messageId, deviceId,
                                    (char*)context->productArea, (char*)context->countryCode,
                                    context->systemVersion, auditData, bootVersion, systemMenuVersion,
                                    systemMenuTitleId, 0, (char**)&response);
    }
    if (auditData != 0) {
        nup::__nupFree(auditData);
        auditData = 0;
    }
    if (result >= 0) {
        result = __nupParseServerInfo(context, (char*)response, messageId, deviceId);
    }
    if (result >= 0 && ((auditResult != 0) != (context->uploadAuditData != 0))) {
        result = __nupSetAuditState(context->uploadAuditData);
        if (result != 0) {
            result = 0;
        }
    }
    if (response != 0) {
        nup::__nupFree(response);
        response = 0;
    }
    if (result >= 0) {
        for (i = 0; i < context->titleCount; i++) {
            NUPTitleInfo* title = &context->titles[i];
            result = __nupGetBootVersion(context, (ESTitleVersion*)title);
            if (result >= 0) {
                title->updateRequired =
                    !title->hasTicket || !title->hasTmd || !title->hasContent ||
                    title->serverVersion < title->installedVersion;
                if (title->updateRequired != 0) {
                    context->updateCount++;
                }
                result = title->updateRequired;
            }
            if (result < 0) {
                break;
            }
        }
    }
    if (result >= 0) {
        for (i = 0; i < context->titleCount; i++) {
            NUPTitleInfo* title = &context->titles[i];
            if (title->updateRequired != 0) {
                result = __nupGetTmd(title, context->uncachedContentPrefixUrl);
                if (result < 0) {
                    break;
                }
            }
        }
    }
    if (result >= 0) {
        for (i = 0; i < context->titleCount; i++) {
            NUPTitleInfo* title = &context->titles[i];
            if (title->updateRequired != 0) {
                result = __nupGetTitleSize(title);
                if (result < 0) {
                    break;
                }
                context->progress.totalBytes += title->updateContentSize;
                context->downloadedBytes += title->installedContentSize;
            }
        }
    }
    if (result >= 0) {
        OSLockMutex(&context->mutex);
        context->progress.totalBytes = context->downloadedBytes;
        context->progress.completedBytes = 0;
        OSUnlockMutex(&context->mutex);
        OSLockMutex(&context->mutex);
        context->progress.result = 3;
        context->progress.message = __nupStatusMessage[3];
        OSUnlockMutex(&context->mutex);
        for (i = 0; i < context->titleCount; i++) {
            NUPTitleInfo* title = &context->titles[i];
            if (title->updateRequired != 0) {
                result = __nupUpdateTitle(context, title, context->contentPrefixUrl,
                                          context->uncachedContentPrefixUrl);
                if (result < 0) {
                    break;
                }
            }
        }
    }
    __nupCleanup(context);
    OSLockMutex(&context->mutex);
    context->progress.result = result < 0 ? result : 0;
    if (result < 0) {
        context->progress.message = __nupStatusMessage[5];
    } else {
        context->progress.message = __nupStatusMessage[0];
    }
    OSUnlockMutex(&context->mutex);
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
