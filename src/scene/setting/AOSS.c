#include "scene/setting/AOSS.h"

#include <revolution/os.h>
#include <revolution/soex.h>

#include <string.h>

typedef union AOSSWaitSettings {
    u32 value;
    struct {
        s16 high;
        s16 low;
    } halfwords;
    struct {
        u16 retryDelay;
        u16 retryStep;
        u16 connectWait;
        u16 responseWait;
    } fields;
} AOSSWaitSettings;

typedef struct AOSSSocketAddress {
    u8 length;
    u8 family;
    u16 port;
    u32 address;
} AOSSSocketAddress;

typedef struct AOSSRuntimeState {
    void* config;
    u32 configLength;
    u32 state;
    u32 flags;
    u32 ipAddress;
    u32 subnetMask;
    s8 active;
    u8 interfaceType;
    u8 reserved1[6];
} AOSSRuntimeState;

typedef struct AOSSNetworkSettings {
    u32 networkNameLength;
    u8 networkName[32];
    u32 useManufacturer;
    u32 manufacturerLength;
    u8 manufacturer[16];
    u32 gatewayAddress;
    u32 ipAddress;
} AOSSNetworkSettings;

typedef struct AOSSPacketHeader {
    u16 initialLength;
    u16 initialType;
    u16 initialSequence;
    u16 responseLength;
    u16 responseType;
    u16 finalLength;
    u16 finalSequence;
    u8 reserved;
    u8 messageType;
    u8 messageIdentity[8];
} AOSSPacketHeader;

typedef struct AOSSDiscoveryPacket {
    AOSSPacketHeader header;
    u8 payload[1];
} AOSSDiscoveryPacket;

typedef struct AOSSOptionRecord {
    u8 type;
    u8 reserved01;
    u16 length;
    u16 nextOffset;
    u8 data[1];
} AOSSOptionRecord;

typedef struct AOSSRequestBuffer {
    u8 type;
    u8 reserved01;
    u16 length;
    AOSSOptionRecord record;
} AOSSRequestBuffer;

typedef union AOSSReplyOptionData {
    u8 bytes[1];
    struct {
        u8 reserved04[2];
        u8 networkType;
        u8 reserved07;
        u16 networkLength;
        u8 reserved0a[2];
        u8 networkData[1];
    } network;
} AOSSReplyOptionData;

typedef union AOSSReplyOption {
    struct {
        u8 type;
        u8 reserved01;
        u16 length;
        AOSSReplyOptionData payload;
    } fields;
    u8 bytes[1];
} AOSSReplyOption;

typedef struct AOSSStoredConfig {
    u32 reserved00;
    u32 dataLength;
    u8 networkName[0x28];
    u8 keyData[4][0x40];
} AOSSStoredConfig;

typedef struct AOSSReplyPayload {
    u8 responseType;
    u8 reserved;
    u16 status;
    union {
        u32 address;
        AOSSOptionRecord optionRecord;
    } data;
} AOSSReplyPayload;

typedef struct AOSSPacketPayload {
    u8 manufacturerAddress[6];
    u16 sequence;
    AOSSReplyPayload reply;
} AOSSPacketPayload;

typedef struct AOSSIncomingMessage {
    u16 messageLength;
    u16 reserved02;
    u16 reserved04;
    u16 opcode;
    u8 reserved08[2];
    u16 authType;
    u16 flags;
    u8 reserved0e;
    u8 messageType;
    AOSSPacketPayload payload;
} AOSSIncomingMessage;

typedef struct AOSSDecryptionMessage {
    u8 reserved00[6];
    u16 command;
    u8 reserved08[2];
    u16 outputLength;
    u16 controlFlags;
    u8 checksum;
    u8 messageType;
    u8 manufacturerAddress[8];
    u8 data[0x5c4];
} AOSSDecryptionMessage;

typedef struct AOSSKeySchedule {
    u32 i;
    u32 j;
    u8* bytes;
    u32 length;
} AOSSKeySchedule;

typedef struct AOSSReceiveBuffer {
    s32 socket;
    u32 length;
    u32 reserved08;
    AOSSIncomingMessage message;
} AOSSReceiveBuffer;

typedef struct AOSSRequestRecord {
    u8 address[6];
    u16 transactionId;
} AOSSRequestRecord;

typedef union AOSSRequestRecords {
    u8 bytes[0x18];
    AOSSRequestRecord records[3];
} AOSSRequestRecords;

typedef struct AOSSAccessPointRecord {
    union {
        u32 listCount;
        u32 flags;
    } header;
    u32 networkNameLength;
    union {
        u8 bytes[0x4c];
        u32 words[0x13];
    } networkName;
} AOSSAccessPointRecord;

typedef struct AOSSConfigRecord {
    u8 reserved00[0x0c];
    u32 ssidLength;
    u8 ssid[0x28];
    u8 wep40Keys[4][0x40];
    u8 reserved138[4];
    u32 key104Length;
    u8 wep104Ssid[0x28];
    u8 wep104Keys[4][0x40];
    u8 reserved268[4];
    u32 tkipLength;
    u8 tkipSsid[0x28];
    u8 tkipKey[0x40];
    u8 reserved2d8[4];
    u32 aesLength;
    u8 aesSsid[0x28];
    u8 aesKey[0x40];
    u8 reserved348[8];
} AOSSConfigRecord;

typedef struct AOSSNetworkBufferRecord {
    u8 bytes[0x80];
} AOSSNetworkBufferRecord;

typedef struct AOSSHelloRecord {
    union {
        struct {
            u8 type;
            u8 reserved01;
            u16 length;
            u32 address;
        } fields;
        u8 bytes[8];
    } data;
} AOSSHelloRecord;

typedef union AOSSHelloPayload {
    u8 bytes[12];
    struct {
        u16 length;
        union {
            u16 nonce;
            u8 nonceBytes[2];
        } key;
        u8 encryptedData[8];
    } encrypted;
} AOSSHelloPayload;

typedef struct AOSSHelloPacket {
    AOSSPacketHeader header;
    AOSSHelloPayload payload;
} AOSSHelloPacket;

typedef struct AOSSConfigData {
    AOSSConfigRecord records[2];
} AOSSConfigData;

static AOSSRuntimeState s_runtime;
static AOSSConfigData s_configData;
static u8 s_networkBuffer[0x280];
static struct {
    u8 keyNonce[2];
    u8 keyAddress[8];
    u8 payload[0x5e];
} s_packetState;
static u32 s_crcTable[0x100];

static s32 s_socket = -1;
static char s_manufacturer[] = "MELCO";
static s32 s_operationState = -1;
static const u8 s_messageId[8] = { 9, 8, 0, 0, 0, 0, 0, 0 };
static u8 s_responseTypeByState[8] = { 9, 8, 0, 0, 0, 0, 0, 0 };
static const u16 s_defaultOptions[4] = { 0xffff, 0xffff, 0, 0 };

static void* s_accessPointList;
static int* s_accessPointConfig;
static u8 s_accessPointName[8];
static s32 s_connectionState;
static u32 s_errorCode;
static s32 s_socketStarted;
static void* s_responseBuffer;

extern int AOSSi_cancel_flag;

extern int AOSSi_WLANGetBSSList(void** list);
extern int AOSSi_Status(int status);
extern int AOSSi_SetNCDIPAddr(u32 ipAddress, u32 netmask, u32 gateway, u32 dns1, u32 dns2);
extern int AOSSi_Sleep(u32 duration);
extern int AOSSi_WLANConnect(void);
extern int SOPoll(s32* descriptors, int count, s32 timeoutHigh, s32 timeoutLow);
extern int SORecvFrom(int socket, void* buffer, int length, int flags, void* address);
extern int SOSendTo(int socket, const void* buffer, int length, int flags, const void* address);
extern int SOBind(int socket, const void* address);

int AOSS_813FFD68(AOSSInitInput* input);
int AOSS_CheckAP(AOSSAccessPointRecord* list);
int AOSS_814001B4(int state, AOSSReceiveBuffer* packet, int* count, AOSSRequestRecords* request);
int AOSS_814002F0(int state, AOSSReceiveBuffer* packet, int* count, AOSSRequestRecords* request);
int AOSS_814004D0(int state, AOSSReceiveBuffer* packet, int* count, AOSSRequestRecords* request);
int AOSS_814006A4(int state, AOSSReceiveBuffer* packet, int* count, AOSSRequestRecords* request);
int AOSS_81400830(AOSSDecryptionMessage* message);
int AOSS_81400D34(u16 command, const u8* manufacturerAddress);
int AOSS_81401104(const AOSSOptionRecord* packet, AOSSStoredConfig* config);
int AOSS_81401284(const AOSSOptionRecord* packet, AOSSStoredConfig* config);
void AOSS_81401C9C(AOSSKeySchedule* schedule, const u8* key, u32 keyLength, u32 stateLength);
void AOSS_81401DC0(u32 seed, u32* table);
s16 AOSS_81401BBC(void* buffer);
int AOSS_81401574(void* packet, AOSSRequestRecords* request, int socket);
int AOSS_81401778(void* packet, void* request, int socket);
int AOSS_81401E80(void* packet, s32 length, const char* key, int keyLength);
int AOSS_814020CC(void* settings, void* config);
int AOSS_81400E0C(const AOSSOptionRecord* packet, u8* settings);
int AOSS_814013AC(int state, const AOSSReplyOption* response, int responseLength, void* config, void* networkData);

int AOSSi_Init(AOSSInitInput* input) {
    int result;
    int cleanupResult;

    if (input->options[0] == 0 || input->options[0] < -1 || input->options[1] < -1 || input->options[2] == 0 ||
        input->options[2] < -1 || input->options[3] < -1 || input->options[4] < -1 || input->ssidLength == 0 ||
        input->ssidLength > 0x100 || input->ssid[input->ssidLength - 1] != 0) {
        result = -1;
    } else {
        result = 0;
    }

    if (result == -1) {
        input->status = 0xf;
        if (s_accessPointConfig != 0) {
            AOSSi_Free(s_accessPointConfig);
            s_accessPointConfig = 0;
        }
        if (s_accessPointList != 0) {
            AOSSi_Free(s_accessPointList);
            s_accessPointList = 0;
        }
        return -1;
    }

    s_responseBuffer = AOSSi_Alloc(0x5f8);
    if (s_responseBuffer == 0) {
        input->status = 0xf;
        if (s_accessPointConfig != 0) {
            AOSSi_Free(s_accessPointConfig);
            s_accessPointConfig = 0;
        }
        if (s_accessPointList != 0) {
            AOSSi_Free(s_accessPointList);
            s_accessPointList = 0;
        }
        return -1;
    }

    result = AOSS_Init_old(input);
    AOSSi_Free(s_responseBuffer);
    if (s_accessPointConfig != 0) {
        AOSSi_Free(s_accessPointConfig);
        s_accessPointConfig = 0;
    }
    if (s_accessPointList != 0) {
        AOSSi_Free(s_accessPointList);
        s_accessPointList = 0;
    }
    if (s_socket != -1) {
        SOClose(s_socket);
    }
    if (s_socketStarted == 1) {
        s_socketStarted = 0;
        cleanupResult = SOCleanup();
        if (cleanupResult < 0) {
            cleanupResult = -1;
            goto cleanup_done;
        }
    }
    cleanupResult = 0;
cleanup_done:
    if (cleanupResult != 0) {
        input->status = 0xf;
        if (s_accessPointConfig != 0) {
            AOSSi_Free(s_accessPointConfig);
            s_accessPointConfig = 0;
        }
        if (s_accessPointList != 0) {
            AOSSi_Free(s_accessPointList);
            s_accessPointList = 0;
        }
        return -1;
    } else if (result == -1 && AOSSi_cancel_flag == 1) {
        result = -2;
    }
    return result;
}
int AOSS_Init_old(AOSSInitInput* input)
{
  u64 tickRemainder;
  AOSSReceiveBuffer* packetBuffer;
  AOSSPacketHeader* packetWords;
  s16 initialSleep;
  u8 errorStatus;
  u32 resultCode;
  int state;
  u32 retryWait;
  u32 packetLength;
  u16 receivedLength;
  int requestResult;
  size_t manufacturerLength;
  int timeoutSeconds;
  int timeoutMilliseconds;
  u32 responseSleep;
  u64 timeoutTicks;
  int initializationResult = 0;
  short attemptCount;
  s16 remainingWait;
  short waitAttempt;
  int receivedPackets;
  AOSSWaitSettings waitSettings;
  AOSSNetworkSettings settings;
  AOSSRequestRecords requestRecords;
  AOSSSocketAddress replyAddress;
  u8 messageIdentity[8] ATTRIBUTE_ALIGN(32);
  AOSSSocketAddress socketAddress;
  int pollSeconds;
  int pollSubseconds;
  AOSSSocketAddress receivedAddress;
  s32 pollArguments[4];
  u32 pollResultHigh;
  u32 pollResultLow;
  u32 networkAddresses[5];
  u32 gatewayAddress;

  waitSettings.fields.connectWait = s_defaultOptions[0];
  waitSettings.fields.responseWait = s_defaultOptions[1];
  waitSettings.value = 0;
  receivedPackets = 0;
  memset(&requestRecords,0,0x18);
  waitSettings.fields.connectWait = (s16)input->options[0];
  if ((s16)input->options[0] == -1) {
    waitSettings.fields.connectWait = 10;
  }
  waitSettings.halfwords.high = (s16)input->options[2];
  if ((s16)input->options[2] == -1) {
    waitSettings.halfwords.high = 10;
  }
  waitSettings.fields.responseWait = (s16)input->options[1];
  if ((s16)input->options[1] == -1) {
    waitSettings.fields.responseWait = 100;
  }
  waitSettings.halfwords.low = (s16)input->options[3];
  if ((s16)input->options[3] == -1) {
    waitSettings.halfwords.low = 100;
  }
  timeoutMilliseconds = (int)(short)input->options[4];
  if (input->options[4] == -1) {
    timeoutMilliseconds = 2000;
  }
  memset(&s_accessPointName,0,8);
  s_errorCode = 1;
  memset(&s_runtime,0,0x1c);
  s_runtime.config = input->ssid;
  s_runtime.configLength = (u32)input->ssidLength;
  s_runtime.flags = input->flags & 0xf;
  s_runtime.interfaceType = input->mode;
  s_runtime.state = 0;
  s_runtime.ipAddress = 0xc0a80b01;
  s_runtime.active = '\0';
  if ((input->flags & 1) == 1) {
    attemptCount = 0;
    waitSettings.halfwords.high = waitSettings.fields.connectWait;
    if (s_operationState != 0) {
      s_operationState = 0;
      AOSSi_Status(0);
      waitSettings.halfwords.high = waitSettings.fields.connectWait;
    }
    while (1) {
      if (s_accessPointList != 0) {
        AOSSi_Free(s_accessPointList);
        s_accessPointList = 0;
      }
      state = AOSSi_WLANGetBSSList(&s_accessPointList);
      if (state == -1) {
        input->status = 0xf;
        if (s_accessPointConfig != NULL) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = NULL;
        }
        if (s_accessPointList != 0) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto LAB_00012878;
      }
      if (AOSSi_cancel_flag == 1) {
        input->status = 0xf;
        if (s_accessPointConfig != NULL) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = NULL;
        }
        if (s_accessPointList != 0) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto LAB_00012878;
      }
      state = AOSS_CheckAP(s_accessPointList);
      if (state == 4) {
        input->status = 2;
        if (s_accessPointConfig != NULL) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = NULL;
        }
        if (s_accessPointList != 0) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto LAB_00012878;
      }
      if (state == 0) {
        if (s_operationState != 1) {
          s_operationState = 1;
          AOSSi_Status(1);
        }
        memset(&settings,0,0x3c);
        settings.networkNameLength = strlen("ESSID-AOSS");
        memcpy(settings.networkName,"ESSID-AOSS",settings.networkNameLength);
        settings.useManufacturer = 1;
        settings.manufacturerLength = strlen(s_manufacturer);
        if (settings.manufacturerLength < 0xe) {
          memcpy(settings.manufacturer,s_manufacturer,settings.manufacturerLength);
        }
        state = AOSSi_SetNCDIPAddr(0xc0a80b65,0xffffff00,0xc0a80b01,0,0);
        if (state == 0) {
          s_accessPointConfig = (int *)AOSSi_Alloc(0x58);
          if (s_accessPointConfig != NULL) {
            memset(s_accessPointConfig,0,0x58);
            waitSettings.halfwords.high = waitSettings.fields.connectWait;
            remainingWait = 0;
            goto LAB_00011698;
          }
          input->status = 0xf;
          if (s_accessPointConfig != NULL) {
            AOSSi_Free(s_accessPointConfig);
            s_accessPointConfig = NULL;
          }
          if (s_accessPointList != 0) {
            AOSSi_Free(s_accessPointList);
            s_accessPointList = 0;
          }
          resultCode = 0xffffffff;
        }
        else {
          s_errorCode = 0xc;
          input->status = 0xf;
          if (s_accessPointConfig != NULL) {
            AOSSi_Free(s_accessPointConfig);
            s_accessPointConfig = NULL;
          }
          if (s_accessPointList != 0) {
            AOSSi_Free(s_accessPointList);
            s_accessPointList = 0;
          }
          resultCode = 0xffffffff;
        }
        goto LAB_00012878;
      }
      remainingWait = waitSettings.fields.responseWait;
      if ((short)waitSettings.halfwords.high <= attemptCount) {
        input->status = 1;
        if (s_accessPointConfig != NULL) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = NULL;
        }
        if (s_accessPointList != 0) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto LAB_00012878;
      }
      for (; remainingWait != 0; remainingWait = remainingWait - initialSleep) {
        if (AOSSi_cancel_flag == 1) {
          input->status = 0xf;
          if (s_accessPointConfig != NULL) {
            AOSSi_Free(s_accessPointConfig);
            s_accessPointConfig = NULL;
          }
          if (s_accessPointList != 0) {
            AOSSi_Free(s_accessPointList);
            s_accessPointList = 0;
          }
          resultCode = 0xffffffff;
          goto LAB_00012878;
        }
        initialSleep = remainingWait;
        if (100 < remainingWait) {
          initialSleep = 100;
        }
        AOSSi_Sleep(initialSleep);
        initialSleep = remainingWait;
        if (100 < remainingWait) {
          initialSleep = 100;
        }
      }
      if (AOSSi_cancel_flag == 1) break;
      attemptCount = attemptCount + 1;
    }
    input->status = 0xf;
    if (s_accessPointConfig != NULL) {
      AOSSi_Free(s_accessPointConfig);
      s_accessPointConfig = NULL;
    }
    if (s_accessPointList != 0) {
      AOSSi_Free(s_accessPointList);
      s_accessPointList = 0;
    }
    resultCode = 0xffffffff;
  }
  else {
    s_errorCode = 0x13;
    input->status = 0xf;
    if (s_accessPointConfig != NULL) {
      AOSSi_Free(s_accessPointConfig);
      s_accessPointConfig = NULL;
    }
    if (s_accessPointList != 0) {
      AOSSi_Free(s_accessPointList);
      s_accessPointList = 0;
    }
    resultCode = 0xffffffff;
  }
  goto LAB_00012878;
LAB_00011698:
  if ((short)waitSettings.halfwords.high <= (short)remainingWait) goto LAB_000116a4;
  state = AOSS_814020CC(&settings,s_accessPointConfig);
  if (state == -1) {
    input->status = 0xf;
    if (s_accessPointConfig != NULL) {
      AOSSi_Free(s_accessPointConfig);
      s_accessPointConfig = NULL;
    }
    if (s_accessPointList != 0) {
      AOSSi_Free(s_accessPointList);
      s_accessPointList = 0;
    }
    resultCode = 0xffffffff;
    goto LAB_00012878;
  }
  initialSleep = waitSettings.fields.responseWait;
  if ((state == 0) && (*s_accessPointConfig == 1)) goto LAB_000116a4;
  for (; initialSleep != 0; initialSleep = initialSleep - waitSettings.halfwords.low) {
    if (AOSSi_cancel_flag == 1) {
      input->status = 0xf;
      if (s_accessPointConfig != NULL) {
        AOSSi_Free(s_accessPointConfig);
        s_accessPointConfig = NULL;
      }
      if (s_accessPointList != 0) {
        AOSSi_Free(s_accessPointList);
        s_accessPointList = 0;
      }
      resultCode = 0xffffffff;
      goto LAB_00012878;
    }
    waitSettings.halfwords.low = initialSleep;
    if (100 < initialSleep) {
      waitSettings.halfwords.low = 100;
    }
    AOSSi_Sleep(waitSettings.halfwords.low);
    waitSettings.halfwords.low = initialSleep;
    if (100 < initialSleep) {
      waitSettings.halfwords.low = 100;
    }
  }
  if (AOSSi_cancel_flag == 1) {
    input->status = 0xf;
    if (s_accessPointConfig != NULL) {
      AOSSi_Free(s_accessPointConfig);
      s_accessPointConfig = NULL;
    }
    if (s_accessPointList != 0) {
      AOSSi_Free(s_accessPointList);
      s_accessPointList = 0;
    }
    resultCode = 0xffffffff;
    goto LAB_00012878;
  }
  remainingWait = remainingWait + 1;
  goto LAB_00011698;
LAB_00012088:
  receivedAddress.length = 8;
  receivedLength = SORecvFrom(s_socket,&packetBuffer->message,0x5dc,0,&receivedAddress);
  packetBuffer->socket = s_socket;
  retryWait = SONtoHs(receivedLength);
  packetBuffer->length = retryWait & 0xffff;
  requestResult = AOSS_814001B4(state,packetBuffer,&receivedPackets,&requestRecords);
  if (requestResult == 100) {
    timeoutMilliseconds = 0;
  }
  else if (requestResult == -1) {
    timeoutMilliseconds = -1;
  }
  else {
    if (state != requestResult) {
      state = requestResult;
      if (requestResult != 2) goto LAB_000118e8;
      if (s_socket != -1) {
        SOClose(s_socket);
      }
      s_socket = -1;
      if (s_socketStarted == 1) {
        s_socketStarted = 0;
        state = SOCleanup();
        if (state < 0) {
          state = -1;
          goto LAB_00012148;
        }
      }
      state = 0;
LAB_00012148:
      if (state != 0) {
        input->status = 0xf;
        if (s_accessPointConfig != NULL) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = NULL;
        }
        if (s_accessPointList != 0) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto LAB_00012878;
      }
      if (s_operationState != 4) {
        s_operationState = 4;
        AOSSi_Status(4);
      }
      if (s_accessPointList != 0) {
        AOSSi_Free(s_accessPointList);
        s_accessPointList = 0;
      }
      state = AOSSi_WLANGetBSSList(&s_accessPointList);
      if (state == -1) {
        input->status = 0xf;
        if (s_accessPointConfig != NULL) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = NULL;
        }
        if (s_accessPointList != 0) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto LAB_00012878;
      }
      if (AOSSi_cancel_flag == 1) {
        input->status = 0xf;
        if (s_accessPointConfig != NULL) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = NULL;
        }
        if (s_accessPointList != 0) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto LAB_00012878;
      }
      state = AOSS_CheckAP(s_accessPointList);
      if (state == 4) {
        input->status = 2;
        if (s_accessPointConfig != NULL) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = NULL;
        }
        if (s_accessPointList != 0) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto LAB_00012878;
      }
      if (state != 0) {
        input->status = 1;
        if (s_accessPointConfig != NULL) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = NULL;
        }
        if (s_accessPointList != 0) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto LAB_00012878;
      }
      s_accessPointConfig = (int *)AOSSi_Alloc(0x58);
      if (s_accessPointConfig == NULL) {
        input->status = 0xf;
        if (s_accessPointConfig != NULL) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = NULL;
        }
        if (s_accessPointList != 0) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto LAB_00012878;
      }
      memset(s_accessPointConfig,0,0x58);
      waitSettings.halfwords.high = waitSettings.fields.connectWait;
      for (waitAttempt = 0; waitAttempt < (short)waitSettings.halfwords.high; waitAttempt = waitAttempt + 1) {
        state = AOSS_814020CC(&settings,s_accessPointConfig);
        if (state == -1) {
          input->status = 0xf;
          if (s_accessPointConfig != NULL) {
            AOSSi_Free(s_accessPointConfig);
            s_accessPointConfig = NULL;
          }
          if (s_accessPointList != 0) {
            AOSSi_Free(s_accessPointList);
            s_accessPointList = 0;
          }
          resultCode = 0xffffffff;
          goto LAB_00012878;
        }
        remainingWait = waitSettings.fields.responseWait;
        if ((state == 0) && (*s_accessPointConfig == 1)) break;
        for (; remainingWait != 0; remainingWait = remainingWait - initialSleep) {
          if (AOSSi_cancel_flag == 1) {
            input->status = 0xf;
            if (s_accessPointConfig != NULL) {
              AOSSi_Free(s_accessPointConfig);
              s_accessPointConfig = NULL;
            }
            if (s_accessPointList != 0) {
              AOSSi_Free(s_accessPointList);
              s_accessPointList = 0;
            }
            resultCode = 0xffffffff;
            goto LAB_00012878;
          }
          initialSleep = remainingWait;
          if (100 < remainingWait) {
            initialSleep = 100;
          }
          AOSSi_Sleep(initialSleep);
          initialSleep = remainingWait;
          if (100 < remainingWait) {
            initialSleep = 100;
          }
        }
        if (AOSSi_cancel_flag == 1) {
          input->status = 0xf;
          if (s_accessPointConfig != NULL) {
            AOSSi_Free(s_accessPointConfig);
            s_accessPointConfig = NULL;
          }
          if (s_accessPointList != 0) {
            AOSSi_Free(s_accessPointList);
            s_accessPointList = 0;
          }
          resultCode = 0xffffffff;
          goto LAB_00012878;
        }
      }
      if (s_accessPointConfig != NULL) {
        AOSSi_Free(s_accessPointConfig);
        s_accessPointConfig = NULL;
      }
      if (s_accessPointList != 0) {
        AOSSi_Free(s_accessPointList);
        s_accessPointList = 0;
      }
      s_socket = SOSocket(2,2,0);
      if (s_socket < 0) {
        input->status = 0xf;
        if (s_accessPointConfig != NULL) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = NULL;
        }
        if (s_accessPointList != 0) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto LAB_00012878;
      }
      memset(&socketAddress,0,8);
      socketAddress.family = 2;
      socketAddress.address = SOGetHostID();
      socketAddress.port = SOHtoNs(0x5790);
      socketAddress.length = 8;
      timeoutSeconds = SOBind(s_socket,&socketAddress);
      state = requestResult;
      if (timeoutSeconds < 0) goto code_r0x00012580;
      goto LAB_000118e8;
    }
    retryWait = waitSettings.value;
    if (receivedPackets <= waitSettings.halfwords.high) {
      for (; retryWait = retryWait & 0xffff, retryWait != 0; retryWait = retryWait - responseSleep) {
        if (AOSSi_cancel_flag == 1) {
          input->status = 0xf;
          if (s_accessPointConfig != NULL) {
            AOSSi_Free(s_accessPointConfig);
            s_accessPointConfig = NULL;
          }
          if (s_accessPointList != 0) {
            AOSSi_Free(s_accessPointList);
            s_accessPointList = 0;
          }
          resultCode = 0xffffffff;
          goto LAB_00012878;
        }
        responseSleep = retryWait;
        if (100 < retryWait) {
          responseSleep = 100;
        }
        AOSSi_Sleep(responseSleep);
        responseSleep = retryWait;
        if (100 < retryWait) {
          responseSleep = 100;
        }
      }
      state = requestResult;
      if (AOSSi_cancel_flag == 1) {
        input->status = 0xf;
        if (s_accessPointConfig != NULL) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = NULL;
        }
        if (s_accessPointList != 0) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto LAB_00012878;
      }
      goto LAB_000118e8;
    }
    if (requestResult == 0) {
      s_errorCode = 0xf;
    }
    else if (requestResult == 1) {
      s_errorCode = 0x10;
    }
    else {
      s_errorCode = 0x11;
    }
    timeoutMilliseconds = -1;
  }
LAB_000126f0:
  if (s_socket != -1) {
    SOClose(s_socket);
  }
  s_socket = -1;
  if (s_socketStarted == 1) {
    s_socketStarted = 0;
    state = SOCleanup();
    if (-1 < state) goto LAB_00012730;
    state = -1;
  }
  else {
LAB_00012730:
    state = 0;
  }
  if (state != 0) {
    input->status = 0xf;
    if (s_accessPointConfig != NULL) {
      AOSSi_Free(s_accessPointConfig);
      s_accessPointConfig = NULL;
    }
    if (s_accessPointList != 0) {
      AOSSi_Free(s_accessPointList);
      s_accessPointList = 0;
    }
    resultCode = 0xffffffff;
    goto LAB_00012878;
  }
  if (timeoutMilliseconds != 0) {
    if (s_errorCode == 0x11) {
      errorStatus = 5;
    }
    else if (s_errorCode < 0x11) {
      if (s_errorCode == 0xf) {
        errorStatus = 3;
      }
      else if (0xe < s_errorCode) {
        errorStatus = 4;
      }
      else {
        errorStatus = 0xf;
      }
    }
    else {
      if (s_errorCode == 0x15) {
        errorStatus = 8;
      }
      else if ((s_errorCode < 0x15) && (0x13 < s_errorCode)) {
        errorStatus = 7;
      }
      else {
        errorStatus = 0xf;
      }
    }
    input->status = errorStatus;
    if (s_accessPointConfig != NULL) {
      AOSSi_Free(s_accessPointConfig);
      s_accessPointConfig = NULL;
    }
    if (s_accessPointList != 0) {
      AOSSi_Free(s_accessPointList);
      s_accessPointList = 0;
    }
    resultCode = 0xffffffff;
    goto LAB_00012878;
  }
  else {
    if (AOSS_813FFD68(input) == 0) {
      resultCode = 0;
    }
    else {
      input->status = 6;
      if (s_accessPointConfig != NULL) {
        AOSSi_Free(s_accessPointConfig);
        s_accessPointConfig = NULL;
      }
      if (s_accessPointList != 0) {
        AOSSi_Free(s_accessPointList);
        s_accessPointList = 0;
      }
      resultCode = 0xffffffff;
    }
    goto LAB_00012878;
  }
code_r0x00012580:
  input->status = 0xf;
  if (s_accessPointConfig != NULL) {
    AOSSi_Free(s_accessPointConfig);
    s_accessPointConfig = NULL;
  }
  if (s_accessPointList != 0) {
    AOSSi_Free(s_accessPointList);
    s_accessPointList = 0;
  }
  resultCode = 0xffffffff;
  goto LAB_00012878;
LAB_000116a4:
  if (remainingWait == waitSettings.fields.connectWait) {
    input->status = 0xf;
    if (s_accessPointConfig != NULL) {
      AOSSi_Free(s_accessPointConfig);
      s_accessPointConfig = NULL;
    }
    if (s_accessPointList != 0) {
      AOSSi_Free(s_accessPointList);
      s_accessPointList = 0;
    }
    resultCode = 0xffffffff;
  }
  else {
    if (s_accessPointConfig != NULL) {
      AOSSi_Free(s_accessPointConfig);
      s_accessPointConfig = NULL;
    }
    if (s_accessPointList != 0) {
      AOSSi_Free(s_accessPointList);
      s_accessPointList = 0;
    }
    requestResult = 0;
    state = 0;
    do {
      memcpy(requestRecords.bytes + state,input->optionData,6);
      retryWait = rand();
      requestRecords.records[requestResult].transactionId = (short)retryWait;
      receivedLength = SOHtoNs(retryWait & 0xffff);
      requestResult = requestResult + 1;
      requestRecords.records[requestResult].transactionId = receivedLength;
      state = state + 8;
    } while (requestResult < 3);
    s_socket = SOSocket(2,2,0);
    if (s_socket < 0) {
      input->status = 0xf;
      if (s_accessPointConfig != NULL) {
        AOSSi_Free(s_accessPointConfig);
        s_accessPointConfig = NULL;
      }
      if (s_accessPointList != 0) {
        AOSSi_Free(s_accessPointList);
        s_accessPointList = 0;
      }
      resultCode = 0xffffffff;
    }
    else if (initializationResult < 0) {
      s_errorCode = 0xb;
      input->status = 0xf;
      if (s_accessPointConfig != NULL) {
        AOSSi_Free(s_accessPointConfig);
        s_accessPointConfig = NULL;
      }
      if (s_accessPointList != 0) {
        AOSSi_Free(s_accessPointList);
        s_accessPointList = 0;
      }
      resultCode = 0xffffffff;
    }
    else {
      memset(&socketAddress,0,8);
      socketAddress.family = 2;
      socketAddress.address = SOGetHostID();
      socketAddress.port = SOHtoNs(0x5790);
      socketAddress.length = 8;
      state = SOBind(s_socket,&socketAddress);
      if (-1 < state) {
        attemptCount = waitSettings.halfwords.high;
        settings.gatewayAddress = 0xc0a80b65;
        settings.ipAddress = 0xc0a80b01;
        state = 0;
LAB_000118e8:
        packetBuffer = s_responseBuffer;
        memset(networkAddresses,0,0x14);
        gatewayAddress = settings.gatewayAddress;
        networkAddresses[0] = settings.ipAddress;
        do {
          if ((state == 1) && (s_runtime.active != '\x01')) {
            if (s_socket != -1) {
              SOClose(s_socket);
            }
            s_socket = -1;
            if (s_socketStarted == 1) {
              s_socketStarted = 0;
              requestResult = SOCleanup();
              if (-1 < requestResult) goto LAB_00011958;
              requestResult = -1;
            }
            else {
LAB_00011958:
              requestResult = 0;
            }
            if (requestResult != 0) {
              input->status = 0xf;
              if (s_accessPointConfig != NULL) {
                AOSSi_Free(s_accessPointConfig);
                s_accessPointConfig = NULL;
              }
              if (s_accessPointList != 0) {
                AOSSi_Free(s_accessPointList);
                s_accessPointList = 0;
              }
              resultCode = 0xffffffff;
              goto LAB_00012878;
            }
            responseSleep = s_runtime.ipAddress & s_runtime.subnetMask;
            retryWait = responseSleep | (s_runtime.ipAddress & ~s_runtime.subnetMask) + 1;
            if ((responseSleep | ~s_runtime.subnetMask) <= retryWait) {
              retryWait = responseSleep | 1;
            }
            requestResult = AOSSi_SetNCDIPAddr(retryWait,s_runtime.subnetMask,s_runtime.ipAddress,0,0);
            if (requestResult != 0) {
              s_errorCode = 0xc;
              input->status = 0xf;
              if (s_accessPointConfig != NULL) {
                AOSSi_Free(s_accessPointConfig);
                s_accessPointConfig = NULL;
              }
              if (s_accessPointList != 0) {
                AOSSi_Free(s_accessPointList);
                s_accessPointList = 0;
              }
              resultCode = 0xffffffff;
              goto LAB_00012878;
            }
            s_runtime.active = '\x01';
            s_accessPointConfig = (int *)AOSSi_Alloc(0x58);
            if (s_accessPointConfig == NULL) {
              input->status = 0xf;
              if (s_accessPointConfig != NULL) {
                AOSSi_Free(s_accessPointConfig);
                s_accessPointConfig = NULL;
              }
              if (s_accessPointList != 0) {
                AOSSi_Free(s_accessPointList);
                s_accessPointList = 0;
              }
              resultCode = 0xffffffff;
              goto LAB_00012878;
            }
            memset(s_accessPointConfig,0,0x58);
            waitSettings.halfwords.high = waitSettings.fields.connectWait;
            for (waitAttempt = 0; waitAttempt < (short)waitSettings.halfwords.high; waitAttempt = waitAttempt + 1) {
              requestResult = AOSS_814020CC(&settings,s_accessPointConfig);
              if (requestResult == -1) {
                input->status = 0xf;
                if (s_accessPointConfig != NULL) {
                  AOSSi_Free(s_accessPointConfig);
                  s_accessPointConfig = NULL;
                }
                if (s_accessPointList != 0) {
                  AOSSi_Free(s_accessPointList);
                  s_accessPointList = 0;
                }
                resultCode = 0xffffffff;
                goto LAB_00012878;
              }
              remainingWait = waitSettings.fields.responseWait;
              if ((requestResult == 0) && (*s_accessPointConfig == 1)) break;
              for (; remainingWait != 0; remainingWait = remainingWait - initialSleep) {
                if (AOSSi_cancel_flag == 1) {
                  input->status = 0xf;
                  if (s_accessPointConfig != NULL) {
                    AOSSi_Free(s_accessPointConfig);
                    s_accessPointConfig = NULL;
                  }
                  if (s_accessPointList != 0) {
                    AOSSi_Free(s_accessPointList);
                    s_accessPointList = 0;
                  }
                  resultCode = 0xffffffff;
                  goto LAB_00012878;
                }
                initialSleep = remainingWait;
                if (100 < remainingWait) {
                  initialSleep = 100;
                }
                AOSSi_Sleep(initialSleep);
                initialSleep = remainingWait;
                if (100 < remainingWait) {
                  initialSleep = 100;
                }
              }
              if (AOSSi_cancel_flag == 1) {
                input->status = 0xf;
                if (s_accessPointConfig != NULL) {
                  AOSSi_Free(s_accessPointConfig);
                  s_accessPointConfig = NULL;
                }
                if (s_accessPointList != 0) {
                  AOSSi_Free(s_accessPointList);
                  s_accessPointList = 0;
                }
                resultCode = 0xffffffff;
                goto LAB_00012878;
              }
            }
            s_socket = SOSocket(2,2,0);
            if (s_socket < 0) {
              input->status = 0xf;
              if (s_accessPointConfig != NULL) {
                AOSSi_Free(s_accessPointConfig);
                s_accessPointConfig = NULL;
              }
              if (s_accessPointList != 0) {
                AOSSi_Free(s_accessPointList);
                s_accessPointList = 0;
              }
              resultCode = 0xffffffff;
              goto LAB_00012878;
            }
            memset(&socketAddress,0,8);
            socketAddress.family = 2;
            socketAddress.address = SOGetHostID();
            socketAddress.port = SOHtoNs(0x5790);
            socketAddress.length = 8;
            requestResult = SOBind(s_socket,&socketAddress);
            if (requestResult < 0) {
              input->status = 0xf;
              if (s_accessPointConfig != NULL) {
                AOSSi_Free(s_accessPointConfig);
                s_accessPointConfig = NULL;
              }
              if (s_accessPointList != 0) {
                AOSSi_Free(s_accessPointList);
                s_accessPointList = 0;
              }
              resultCode = 0xffffffff;
              goto LAB_00012878;
            }
          }
          requestResult = s_socket;
          if (state == 1) {
            if (s_operationState != 3) {
              s_operationState = 3;
              AOSSi_Status(3);
            }
            requestResult = AOSS_81401778(networkAddresses,&requestRecords,requestResult);
          }
          else if (state < 1) {
            if (state < 0) {
LAB_00011e70:
              requestResult = -1;
            }
            else {
              if (s_operationState != 2) {
                s_operationState = 2;
                AOSSi_Status(2);
              }
              requestResult = AOSS_81401574(networkAddresses,&requestRecords,requestResult);
            }
          }
          else {
            if (2 < state) goto LAB_00011e70;
            if (s_operationState != 5) {
              s_operationState = 5;
              AOSSi_Status(5);
            }
            packetWords = s_responseBuffer;
            memset(s_responseBuffer,0,0x5dc);
            memcpy(messageIdentity,&requestRecords.records[2],8);
            manufacturerLength = strlen(s_manufacturer);
            AOSS_81401E80(messageIdentity,8,s_manufacturer,manufacturerLength);
            receivedLength = SOHtoNs(1);
            packetWords->initialLength = receivedLength;
            packetWords->initialType = 0;
            packetWords->initialSequence = 0;
            packetWords->responseLength = SOHtoNs(0x3000);
            packetWords->responseType = 0;
            packetWords->finalLength = SOHtoNs(0);
            packetWords->finalSequence = SOHtoNs(0);
            packetWords->reserved = 0;
            packetWords->messageType = 0x11;
            memcpy(packetWords->messageIdentity,messageIdentity,8);
            memset(&replyAddress,0,8);
            replyAddress.family = 2;
            replyAddress.port = SOHtoNs(0x5790);
            replyAddress.address = SOHtoNl(s_runtime.ipAddress);
            if (s_runtime.active == '\0') {
              replyAddress.address = 0xffffffff;
            }
            replyAddress.length = 8;
            SOSendTo(requestResult,packetWords,0x18,0,&replyAddress);
            requestResult = 0;
          }
          if (requestResult == -1) {
            s_errorCode = state + 0x1000;
            input->status = 0xf;
            if (s_accessPointConfig != NULL) {
              AOSSi_Free(s_accessPointConfig);
              s_accessPointConfig = NULL;
            }
            if (s_accessPointList != 0) {
              AOSSi_Free(s_accessPointList);
              s_accessPointList = 0;
            }
            resultCode = 0xffffffff;
            goto LAB_00012878;
          }
          memset(packetBuffer,0,0x5f8);
          timeoutSeconds = timeoutMilliseconds >> 0x1f;
          requestResult = timeoutMilliseconds / 1000 + timeoutSeconds;
          pollArguments[1] = 1;
          pollArguments[0] = s_socket;
          pollSeconds = requestResult - timeoutSeconds;
          pollArguments[2] = 0;
          pollArguments[3] = s_socket;
          pollResultLow = 0;
          pollResultHigh = 1;
          pollSubseconds = (timeoutMilliseconds + (requestResult - timeoutSeconds) * -1000) * 1000;
          timeoutTicks = (s64)pollSeconds * (s64)(int)(OS_BUS_CLOCK >> 2);
          tickRemainder = ((s64)pollSubseconds * (s64)(int)((OS_BUS_CLOCK >> 2) / 0x1e848) &
                  0xffffffffU) >> 3;
          requestResult = SOPoll(pollArguments,1,((u32)((timeoutTicks + tickRemainder) >> 32)),(int)timeoutTicks + (int)tickRemainder);
          if (0 < requestResult) goto LAB_00012088;
          receivedPackets = receivedPackets + 1;
          retryWait = waitSettings.value;
          if (attemptCount < receivedPackets) {
            if (state == 0) {
              s_errorCode = 0xf;
            }
            else if (state == 1) {
              s_errorCode = 0x10;
            }
            else {
              s_errorCode = 0x11;
            }
            timeoutMilliseconds = -1;
            goto LAB_000126f0;
          }
          for (; retryWait = retryWait & 0xffff, retryWait != 0; retryWait = retryWait - responseSleep) {
            if (AOSSi_cancel_flag == 1) {
              input->status = 0xf;
              if (s_accessPointConfig != NULL) {
                AOSSi_Free(s_accessPointConfig);
                s_accessPointConfig = NULL;
              }
              if (s_accessPointList != 0) {
                AOSSi_Free(s_accessPointList);
                s_accessPointList = 0;
              }
              resultCode = 0xffffffff;
              goto LAB_00012878;
            }
            responseSleep = retryWait;
            if (100 < retryWait) {
              responseSleep = 100;
            }
            AOSSi_Sleep(responseSleep);
            responseSleep = retryWait;
            if (100 < retryWait) {
              responseSleep = 100;
            }
          }
          if (AOSSi_cancel_flag == 1) {
            input->status = 0xf;
            if (s_accessPointConfig != NULL) {
              AOSSi_Free(s_accessPointConfig);
              s_accessPointConfig = NULL;
            }
            if (s_accessPointList != 0) {
              AOSSi_Free(s_accessPointList);
              s_accessPointList = 0;
            }
            resultCode = 0xffffffff;
            goto LAB_00012878;
          }
        } while (1);
      }
      input->status = 0xf;
      if (s_accessPointConfig != NULL) {
        AOSSi_Free(s_accessPointConfig);
        s_accessPointConfig = NULL;
      }
      if (s_accessPointList != 0) {
        AOSSi_Free(s_accessPointList);
        s_accessPointList = 0;
      }
      resultCode = 0xffffffff;
    }
  }
LAB_00012878:
  return (int)resultCode;}

int AOSS_813FFD68(AOSSInitInput* input) {
    AOSSConfigRecord* config;
    u8* output;
    u8* cursor;
    size_t length;
    u8 value;
    int valid;
    int count;

    output = input->result;
    config = &s_configData.records[0];
    if (output == 0) {
        return -1;
    }

    input->flags = s_runtime.state & s_runtime.flags;
    memset(output, 0, sizeof(input->result));

    if ((input->flags & 1) != 0) {
        memcpy(output, config->wep40Keys[0], config->ssidLength);
        memcpy(output + 6, config->wep40Keys[1], config->ssidLength);
        memcpy(output + 12, config->wep40Keys[2], config->ssidLength);
        memcpy(output + 18, config->wep40Keys[3], config->ssidLength);
        length = strlen((const char*)config->ssid);
        cursor = config->ssid;
        for (count = (int)length; count > 0; count--) {
            value = *cursor++;
            if (value < 0x20 || value > 0x7f) {
                valid = -1;
                goto validate_wep40_ssid;
            }
        }
        valid = 0;
validate_wep40_ssid:
        if (valid != 0) {
            goto invalid_config;
        }
        length = strlen((const char*)config->ssid);
        memcpy(output + 24, config->ssid, length);
    }

    if ((input->flags & 2) != 0) {
        memcpy(output + 0x39, config->wep104Keys[0], config->key104Length);
        memcpy(output + 0x47, config->wep104Keys[1], config->key104Length);
        memcpy(output + 0x55, config->wep104Keys[2], config->key104Length);
        memcpy(output + 0x63, config->wep104Keys[3], config->key104Length);
        length = strlen((const char*)config->wep104Ssid);
        cursor = config->wep104Ssid;
        for (count = (int)length; count > 0; count--) {
            value = *cursor++;
            if (value < 0x20 || value > 0x7f) {
                valid = -1;
                goto validate_wep104_ssid;
            }
        }
        valid = 0;
validate_wep104_ssid:
        if (valid != 0) {
            goto invalid_config;
        }
        length = strlen((const char*)config->wep104Ssid);
        memcpy(output + 0x71, config->wep104Ssid, length);
    }

    if ((input->flags & 4) != 0) {
        cursor = config->tkipKey;
        count = config->tkipLength - 1;
        for (; count > 0; count--) {
            value = *cursor++;
            if (value < 0x20 || value > 0x7f) {
                valid = -1;
                goto validate_tkip_key;
            }
        }
        valid = 0;
validate_tkip_key:
        if (valid != 0) {
            goto invalid_config;
        }
        memcpy(output + 0x92, config->tkipKey, config->tkipLength);
        length = strlen((const char*)config->tkipSsid);
        cursor = config->tkipSsid;
        for (count = (int)length; count > 0; count--) {
            value = *cursor++;
            if (value < 0x20 || value > 0x7f) {
                valid = -1;
                goto validate_tkip_ssid;
            }
        }
        valid = 0;
validate_tkip_ssid:
        if (valid != 0) {
            goto invalid_config;
        }
        length = strlen((const char*)config->tkipSsid);
        memcpy(output + 0xd2, config->tkipSsid, length);
    }

    if ((input->flags & 8) != 0) {
        cursor = config->aesKey;
        count = config->aesLength - 1;
        for (; count > 0; count--) {
            value = *cursor++;
            if (value < 0x20 || value > 0x7f) {
                valid = -1;
                goto validate_aes_key;
            }
        }
        valid = 0;
validate_aes_key:
        if (valid != 0) {
            goto invalid_config;
        }
        memcpy(output + 0xf3, config->aesKey, config->aesLength);
        length = strlen((const char*)config->aesSsid);
        cursor = config->aesSsid;
        for (count = (int)length; count > 0; count--) {
            value = *cursor++;
            if (value < 0x20 || value > 0x7f) {
                valid = -1;
                goto validate_aes_ssid;
            }
        }
        valid = 0;
validate_aes_ssid:
        if (valid != 0) {
            goto invalid_config;
        }
        length = strlen((const char*)config->aesSsid);
        memcpy(output + 0x133, config->aesSsid, length);
    }

    input->status = 0;
    return 0;

invalid_config:
    memset(output, 0, sizeof(input->result));
    return -1;
}

int AOSS_CheckAP(AOSSAccessPointRecord* list) {
    u32 count = list->header.listCount;
    u32 limit;
    AOSSAccessPointRecord* current;
    u32* networkName;
    int index;
    int result;
    int comparisonResult;
    int matchingAccessPoints;
    size_t networkNameLength;

    result = 0;
    matchingAccessPoints = 0;
    if (count == 0) {
        return 5;
    }
    limit = 0x40;
    if (count <= 0x40) {
        limit = count;
    }
        current = list;
        networkName = list->networkName.words;
        for (index = 0; index < (int)limit; index++) {
            if ((current[1].header.flags & 1) != 0) {
                networkNameLength = strlen("ESSID-AOSS");
                if (current->networkNameLength == networkNameLength) {
                    networkNameLength = strlen("ESSID-AOSS");
                    comparisonResult = memcmp(networkName, "ESSID-AOSS", networkNameLength);
                    if (comparisonResult == 0) {
                        matchingAccessPoints++;
                    }
                }
            }
            current++;
            networkName += 0x15;
        }
        if (1 < matchingAccessPoints) {
            result = 4;
        }
        if (matchingAccessPoints == 0) {
            result = 5;
        }
    return result;
}

int AOSS_814001B4(int state, AOSSReceiveBuffer* packet, int* count, AOSSRequestRecords* request) {
    u16 messageLength = SONtoHs(packet->message.messageLength);
    int opcode;

    if (messageLength < 1) {
        *count = *count + 1;
        return state;
    }
    if (packet->message.messageType != 0x11) {
        *count = *count + 1;
        return state;
    }
    if (AOSS_81400830((AOSSDecryptionMessage*)&packet->message) > 0) {
        *count = *count + 1;
        return state;
    }
    opcode = (u16)SONtoHs(packet->message.opcode);
    switch (opcode) {
    case 0x1010:
        state = AOSS_814002F0(state, packet, count, request);
        break;
    case 0x2010:
        state = AOSS_814004D0(state, packet, count, request);
        break;
    case 0x3010:
        state = AOSS_814006A4(state, packet, count, request);
        break;
    }
    return state;
}

int AOSS_814002F0(int state, AOSSReceiveBuffer* packet, int* count, AOSSRequestRecords* request) {
    AOSSReplyPayload* reply;
    AOSSRequestRecord* requestRecord;
    int compareResult;
    u16 packetSequence;
    u16 requestSequence;
    u16 status;
    int validationResult;
    int parserResult;
    u32 addressStatus;

    if (state != 0) {
        *count = *count + 1;
        return state;
    }

    validationResult = 0;
    reply = &packet->message.payload.reply;
    requestRecord = &request->records[0];
    AOSS_81401E80(&packet->message.payload.manufacturerAddress, 8, s_manufacturer, strlen(s_manufacturer));
    compareResult = memcmp(requestRecord->address,
                           packet->message.payload.manufacturerAddress, 6);
    if (compareResult != 0) {
        validationResult = -1;
    } else {
        packetSequence = SONtoHs(packet->message.payload.sequence);
        requestSequence = SONtoHs(requestRecord->transactionId);
        if ((requestSequence & 0xffff) + 1 != (packetSequence & 0xffff)) {
            validationResult = -2;
        }
    }
    if (validationResult < 0) {
        *count = *count + 1;
        return state;
    }
    status = SONtoHs(reply->status);
    if (status == 0) {
        *count = *count + 1;
        return state;
    }
    if (reply->responseType == 7) {
        u32* addressPtr = &reply->data.address;
        if (SONtoHl(*addressPtr) == -2) {
            s_errorCode = 0x14;
        } else {
            addressStatus = SONtoHl(*addressPtr);
            s_errorCode = addressStatus == (u32)-3 ? 0x15 : 0x18;
        }
        return -1;
    }
    if (reply->responseType == 1) {
        parserResult = AOSS_81400E0C(&reply->data.optionRecord, s_networkBuffer);
        if (parserResult < 0) {
            if (parserResult == -2) {
                s_errorCode = 0x16;
                return -1;
            }
            *count = *count + 1;
            return state;
        }
        s_operationState = (SONtoHs(packet->message.flags) & 0x10) != 0;
        *count = 0;
        return 1;
    }
    *count = *count + 1;
    return state;
}

int AOSS_814004D0(int state, AOSSReceiveBuffer* packet, int* count, AOSSRequestRecords* request) {
    size_t manufacturerLength;
    int compareResult;
    u16 packetSequence;
    u16 requestSequence;
    u16 status;
    u16 authType;
    int operationResult;
    u32 addressStatus;
    AOSSReplyPayload* reply;

    if (state != 1) {
        *count = *count + 1;
        return state;
    }

    operationResult = 0;
    reply = &packet->message.payload.reply;
    manufacturerLength = strlen(s_manufacturer);
    AOSS_81401E80(&packet->message.payload.manufacturerAddress, 8, s_manufacturer, manufacturerLength);
    compareResult = memcmp(request->records[1].address,
                           packet->message.payload.manufacturerAddress, 6);
    if (compareResult != 0) {
        operationResult = -1;
    } else {
        packetSequence = SONtoHs(packet->message.payload.sequence);
        requestSequence = SONtoHs(request->records[1].transactionId);
        if ((requestSequence & 0xffff) + 1 != (packetSequence & 0xffff)) {
            operationResult = -2;
        }
    }
    if (operationResult < 0) {
        *count = *count + 1;
        return state;
    } else {
        status = SONtoHs(reply->status);
        if (status == 0) {
            *count = *count + 1;
            return state;
        } else if (reply->responseType == 7) {
            addressStatus = SONtoHl(reply->data.address);
            if (addressStatus == (u32)-2) {
                s_errorCode = 0x14;
            } else {
                addressStatus = SONtoHl(reply->data.address);
                s_errorCode = addressStatus == (u32)-3 ? 0x15 : 0x18;
            }
            return -1;
        } else {
            memset(&s_configData, 0, sizeof(s_configData));
            authType = SONtoHs(packet->message.authType);
            operationResult = AOSS_814013AC(0, (const AOSSReplyOption*)reply, authType, &s_configData,
                                            s_networkBuffer);
            if (operationResult < 0) {
                *count = *count + 1;
                return state;
            }
            if ((s_runtime.flags & s_runtime.state) == 0) {
                return state;
            }
            *count = 0;
            return 2;
        }
    }
    return state;
}

int AOSS_814006A4(int state, AOSSReceiveBuffer* packet, int* count, AOSSRequestRecords* request) {
    int result = state;
    size_t manufacturerLength;
    int compareResult;
    u16 packetSequence;
    u16 requestSequence;
    u16 status;
    int errorCode;

    if (state != 2) {
        *count = *count + 1;
        return result;
    }

    errorCode = 0;
    manufacturerLength = strlen(s_manufacturer);
    AOSS_81401E80(&packet->message.payload.manufacturerAddress, 8, s_manufacturer, manufacturerLength);
    compareResult = memcmp(request->records[2].address,
                           packet->message.payload.manufacturerAddress, 6);
    if (compareResult != 0) {
        errorCode = -1;
    } else {
        packetSequence = SONtoHs(packet->message.payload.sequence);
        requestSequence = SONtoHs(request->records[2].transactionId);
        if ((requestSequence & 0xffff) + 1 != (packetSequence & 0xffff)) {
            errorCode = -2;
        }
    }
    if (errorCode < 0) {
        *count = *count + 1;
        return result;
    }
    if (packet->message.payload.reply.responseType != 7) {
        *count = *count + 1;
        return result;
    }
    status = SONtoHs(packet->message.payload.reply.status);
    if (status == 0) {
        *count = *count + 1;
        return result;
    }
    if (SONtoHl(packet->message.payload.reply.data.address) == 0) {
        result = 100;
    } else if (SONtoHl(packet->message.payload.reply.data.address) == -2) {
        result = -1;
        s_errorCode = 0x14;
    } else if (SONtoHl(packet->message.payload.reply.data.address) == -3) {
        result = -1;
        s_errorCode = 0x15;
    } else {
        result = -1;
        s_errorCode = 0x18;
    }
    return result;
}

int AOSS_81400830(AOSSDecryptionMessage* message) {
    u8 manufacturerAddress[8];
    AOSSKeySchedule schedule;
    u8* decryptedData;
    u8* data;
    const u8* in;
    u8* out;
    u32 dataLength;
    u32 checksum;
    s32 i;
    u32 pairCount;
    u32 oddCount;
    u32 firstIndex;
    u32 secondIndex;
    u32 firstValue;
    u32 secondValue;
    u32 crc;
    int result;

    data = message->data;

    memcpy(manufacturerAddress, message->manufacturerAddress, sizeof(manufacturerAddress));
    result = AOSS_81401E80(manufacturerAddress, sizeof(manufacturerAddress), s_manufacturer,
                           strlen(s_manufacturer));
    if (result == -1) {
        s_errorCode = 2;
        return -100;
    }

    result = AOSS_81400D34(SONtoHs(message->command), manufacturerAddress);
    if (result != 0) {
        return result;
    }

    if (SONtoHs(message->command) == 0x1000) {
        memcpy(s_accessPointName, manufacturerAddress, sizeof(s_accessPointName));
    }

    if ((SONtoHs(message->controlFlags) & 0xf) == 0) {
        return 0;
    }

    dataLength = SONtoHs(*(u16*)data);
    decryptedData = AOSSi_Alloc(dataLength);
    if (decryptedData == 0) {
        s_errorCode = 2;
        return 100;
    }

    checksum = message->checksum;
    schedule.bytes = AOSSi_Alloc(dataLength);
    if (schedule.bytes == 0) {
        s_errorCode = 2;
        result = -1;
    } else {
        memcpy(s_packetState.keyNonce, data + 2, sizeof(s_packetState.keyNonce));
        memcpy(s_packetState.keyAddress, s_accessPointName, sizeof(s_accessPointName));
        AOSS_81401C9C(&schedule, s_packetState.keyNonce,
                      sizeof(s_packetState.keyNonce) + sizeof(s_packetState.keyAddress), dataLength);

        if (dataLength != 0) {
            in = data + 4;
            out = decryptedData;
            i = 0;
            pairCount = dataLength >> 1;
            while (pairCount != 0) {
                firstIndex = ((schedule.i + 1) % schedule.length) & 0xff;
                firstValue = schedule.bytes[firstIndex];
                secondIndex = ((firstValue + schedule.j) % schedule.length) & 0xff;
                secondValue = schedule.bytes[secondIndex];
                schedule.i = firstIndex;
                schedule.j = secondIndex;
                schedule.bytes[secondIndex] = (u8)firstValue;
                schedule.bytes[firstIndex] = (u8)secondValue;
                out[0] = schedule.bytes[(firstValue + secondValue) % schedule.length] ^ in[0];
                firstIndex = ((schedule.i + 1) % schedule.length) & 0xff;
                firstValue = schedule.bytes[firstIndex];
                secondIndex = ((firstValue + schedule.j) % schedule.length) & 0xff;
                secondValue = schedule.bytes[secondIndex];
                schedule.i = firstIndex;
                schedule.j = secondIndex;
                schedule.bytes[secondIndex] = (u8)firstValue;
                schedule.bytes[firstIndex] = (u8)secondValue;
                out[1] = schedule.bytes[(firstValue + secondValue) % schedule.length] ^ in[1];
                in += 2;
                out += 2;
                i += 2;
                pairCount--;
            }
            for (oddCount = dataLength & 1; oddCount != 0; oddCount--) {
                firstIndex = ((schedule.i + 1) % schedule.length) & 0xff;
                firstValue = schedule.bytes[firstIndex];
                secondIndex = ((firstValue + schedule.j) % schedule.length) & 0xff;
                secondValue = schedule.bytes[secondIndex];
                schedule.i = firstIndex;
                schedule.j = secondIndex;
                schedule.bytes[secondIndex] = (u8)firstValue;
                schedule.bytes[firstIndex] = (u8)secondValue;
                out[0] = schedule.bytes[(firstValue + secondValue) % schedule.length] ^ in[0];
                in++;
                out++;
            }
        }

        AOSS_81401DC0(0, s_crcTable);
        crc = 0xffffffff;
        for (i = 0; i < (s32)dataLength - 8; i += 8) {
            crc = (crc >> 8) ^ s_crcTable[(crc ^ decryptedData[i]) & 0xff];
            crc = (crc >> 8) ^ s_crcTable[(crc ^ decryptedData[i + 1]) & 0xff];
            crc = (crc >> 8) ^ s_crcTable[(crc ^ decryptedData[i + 2]) & 0xff];
            crc = (crc >> 8) ^ s_crcTable[(crc ^ decryptedData[i + 3]) & 0xff];
            crc = (crc >> 8) ^ s_crcTable[(crc ^ decryptedData[i + 4]) & 0xff];
            crc = (crc >> 8) ^ s_crcTable[(crc ^ decryptedData[i + 5]) & 0xff];
            crc = (crc >> 8) ^ s_crcTable[(crc ^ decryptedData[i + 6]) & 0xff];
            crc = (crc >> 8) ^ s_crcTable[(crc ^ decryptedData[i + 7]) & 0xff];
        }
        for (; i < (s32)dataLength; i++) {
            crc = (crc >> 8) ^ s_crcTable[(crc ^ decryptedData[i]) & 0xff];
        }
        if (((crc ^ 0xffffffff) & 0xff) == checksum) {
            AOSSi_Free(schedule.bytes);
            result = 0;
        } else {
            s_errorCode = 0x12;
            AOSSi_Free(schedule.bytes);
            result = -1;
        }
    }

    if (result < 0) {
        AOSSi_Free(decryptedData);
        return s_errorCode == 2 ? 100 : 200;
    }

    memcpy(data, decryptedData, dataLength);
    message->outputLength = SOHtoNs(dataLength);
    AOSSi_Free(decryptedData);
    return 0;
}

int AOSS_81400D34(u16 command, const u8* manufacturerAddress) {
    u8* storedAddress = s_accessPointName;
    int result = 0;
    int hasAddress = 0;
    int comparisonResult;

    if (storedAddress[0] != 0) {
        hasAddress = 1;
    } else if (storedAddress[1] != 0) {
        hasAddress = 1;
    } else if (storedAddress[2] != 0) {
        hasAddress = 1;
    } else if (storedAddress[3] != 0) {
        hasAddress = 1;
    } else if (storedAddress[4] != 0) {
        hasAddress = 1;
    } else if (storedAddress[5] != 0) {
        hasAddress = 1;
    }
    if (hasAddress != 0) {
        comparisonResult = memcmp(s_accessPointName, manufacturerAddress, 6);
        if (comparisonResult != 0) {
            result = 1;
        }
    } else if (command != 0x1000) {
        result = 2;
    }
    return result;
}

int AOSS_81400E0C(const AOSSOptionRecord* packet, u8* settings) {
    const u8* packetBytes = (const u8*)packet;
    const AOSSOptionRecord* record = packet;
    int length;
    int index;
    u32 value;
    int remaining;
    u16 nextOffset;
    const u8* valueBytes;
    int canUnroll;

    memset(settings, 0, 0x104);
    for (;;) {
        length = SONtoHs(record->length);
        if (length <= 0) {
            return -1;
        }

        switch (record->type) {
        case 0:
            memcpy(settings, record->data, length);
            break;
        case 1:
            memcpy(settings + 0x80, record->data, length);
            break;
        case 2:
            memcpy(settings + 0x100, record->data, length);
            break;
        case 3:
        case 4:
            if ((int)SONtoHs(record->data[0]) <= 0) {
                return -2;
            }
            break;
        case 5:
            value = 0;
            valueBytes = record->data;
            index = 0;
            if (length > 0) {
            remaining = length - 8;
            if (length > 8) {
                canUnroll = (length >= 0) && !(length > 0x7ffffffe);
                if (canUnroll) {
                    for (; index < remaining; index += 8) {
                        value = (value << 8) + valueBytes[0];
                        value = (value << 8) + valueBytes[1];
                        value = (value << 8) + valueBytes[2];
                        value = (value << 8) + valueBytes[3];
                        value = (value << 8) + valueBytes[4];
                        value = (value << 8) + valueBytes[5];
                        value = (value << 8) + valueBytes[6];
                        value = (value << 8) + valueBytes[7];
                        valueBytes += 8;
                    }
                }
            }
            for (; index < length; index++) {
                value = (value << 8) + *valueBytes++;
            }
            }
            value = SONtoHl(value);
            s_runtime.ipAddress = value;
            break;
        case 6:
            value = 0;
            valueBytes = record->data;
            index = 0;
            if (length > 0) {
            remaining = length - 8;
            if (length > 8) {
                canUnroll = (length >= 0) && !(length > 0x7ffffffe);
                if (canUnroll) {
                    for (; index < remaining; index += 8) {
                        value = (value << 8) + valueBytes[0];
                        value = (value << 8) + valueBytes[1];
                        value = (value << 8) + valueBytes[2];
                        value = (value << 8) + valueBytes[3];
                        value = (value << 8) + valueBytes[4];
                        value = (value << 8) + valueBytes[5];
                        value = (value << 8) + valueBytes[6];
                        value = (value << 8) + valueBytes[7];
                        valueBytes += 8;
                    }
                }
            }
            for (; index < length; index++) {
                value = (value << 8) + *valueBytes++;
            }
            }
            value = SONtoHl(value);
            s_runtime.subnetMask = value;
            break;
        default:
            return -1;
        }

        nextOffset = record->nextOffset;
        if (nextOffset != 0) {
            record = (const AOSSOptionRecord*)(packetBytes + SONtoHs(nextOffset));
        } else {
            return 0;
        }
    }
}

int AOSS_81401104(const AOSSOptionRecord* packet, AOSSStoredConfig* config) {
    const u8* packetBytes = (const u8*)packet;
    const AOSSOptionRecord* record = (const AOSSOptionRecord*)(packetBytes + 6);
    u32 length;

    for (;;) {
        length = SONtoHs(record->length);
        switch (record->type) {
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
            if (length > 5) {
                return -1;
            }
            break;
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
            if (length > 0xd) {
                return -1;
            }
            break;
        case 0x15:
        case 0x25:
            if (length > 0x21) {
                return -1;
            }
            break;
        }

        switch (record->type) {
        case 0x10:
        case 0x20:
            memcpy(config->keyData[0], record->data, length);
            config->dataLength = length;
            break;
        case 0x11:
        case 0x21:
            memcpy(config->keyData[1], record->data, length);
            config->dataLength = length;
            break;
        case 0x12:
        case 0x22:
            memcpy(config->keyData[2], record->data, length);
            config->dataLength = length;
            break;
        case 0x13:
        case 0x23:
            memcpy(config->keyData[3], record->data, length);
            config->dataLength = length;
            break;
        case 0x15:
        case 0x25:
            if (length != 0 && record->data[length - 1] != 0) {
                return -1;
            }
            memcpy(config->networkName, record->data, length);
            break;
        default:
            return -1;
        }

        if (record->nextOffset == 0) {
            break;
        }
        record = (const AOSSOptionRecord*)(packetBytes + 6 + SONtoHs(record->nextOffset));
    }
    return 0;
}

int AOSS_81401284(const AOSSOptionRecord* packet, AOSSStoredConfig* config) {
    const u8* packetBytes = (const u8*)packet;
    const AOSSOptionRecord* record = (const AOSSOptionRecord*)(packetBytes + 6);
    u32 length;

    for (;;) {
        length = SONtoHs(record->length);
        switch (record->type) {
        case 0x30:
        case 0x40:
            if (length > 0x40) {
                return -1;
            }
            break;
        case 0x35:
        case 0x45:
            if (length > 0x21) {
                return -1;
            }
            break;
        }

        switch (record->type) {
        case 0x30:
        case 0x40:
            memcpy(config->keyData[0], record->data, length);
            config->dataLength = length;
            break;
        case 0x35:
        case 0x45:
            if (length != 0 && record->data[length - 1] != 0) {
                return -1;
            }
            memcpy(config->networkName, record->data, length);
            break;
        default:
            return -1;
        }

        if (record->nextOffset == 0) {
            break;
        }
        record = (const AOSSOptionRecord*)(packetBytes + 6 + SONtoHs(record->nextOffset));
    }
    return 0;
}

int AOSS_814013AC(int state, const AOSSReplyOption* response, int responseLength, void* config, void* networkData) {
    const AOSSReplyOption* responseRecord;
    const AOSSReplyOption* option;
    AOSSConfigRecord* configRecord;
    AOSSStoredConfig* wep40Config;
    AOSSStoredConfig* wep104Config;
    AOSSStoredConfig* tkipConfig;
    AOSSStoredConfig* aesConfig;
    u8* networkSettings;
    u32 length;
    int result;
    u32 flags = 0;
    s32 remainingLength = responseLength;

    if (remainingLength <= 0) {
        return -2;
    }

    responseRecord = response;
    for (;;) {
        if (responseRecord->fields.type == s_responseTypeByState[state]) {
            break;
        }
        length = SONtoHs(responseRecord->fields.length) + 4;
        remainingLength -= length;
        responseRecord = (const AOSSReplyOption*)((u8*)responseRecord + length);
        if (remainingLength <= 0) {
            return -4;
        }
    }

    length = responseRecord->fields.length;
    option = (const AOSSReplyOption*)&responseRecord->bytes[4];
    remainingLength = SONtoHs((u16)length);
    configRecord = &((AOSSConfigData*)config)->records[state];
    networkSettings = ((AOSSNetworkBufferRecord*)networkData)[state + 3].bytes;
    wep40Config = (AOSSStoredConfig*)&configRecord->reserved00[8];
    wep104Config = (AOSSStoredConfig*)&configRecord->reserved138[0];
    tkipConfig = (AOSSStoredConfig*)&configRecord->reserved268[0];
    aesConfig = (AOSSStoredConfig*)&configRecord->reserved2d8[0];

    do {
        switch (option->fields.type) {
        case 3:
            result = AOSS_81401104((const AOSSOptionRecord*)option, wep40Config);
            flags |= 1;
            break;
        case 4:
            result = AOSS_81401104((const AOSSOptionRecord*)option, wep104Config);
            flags |= 2;
            break;
        case 5:
            result = AOSS_81401284((const AOSSOptionRecord*)option, tkipConfig);
            flags |= 4;
            break;
        case 6:
            result = AOSS_81401284((const AOSSOptionRecord*)option, aesConfig);
            flags |= 8;
            break;
        case 10:
            length = SONtoHs(option->fields.payload.network.networkLength);
            if ((s32)length <= 0) {
                return -1;
            }
            if (option->fields.payload.network.networkType != 0x70) {
                return -1;
            }
            memcpy(networkSettings, option->fields.payload.network.networkData, length);
            result = 0;
            break;
        default:
            result = -3;
            break;
        }

        if (result != 0) {
            return result;
        }

        length = SONtoHs(option->fields.length) + 4;
        remainingLength -= length;
        option = (const AOSSReplyOption*)((u8*)option + length);
    } while (remainingLength > 0);

    s_runtime.flags |= flags;
    return 0;
}

int AOSS_81401574(void* packet, AOSSRequestRecords* request, int socket) {
    AOSSDiscoveryPacket* response = (AOSSDiscoveryPacket*)s_responseBuffer;
    u8* responsePayload;
    u8 accessPointName[8];
    AOSSSocketAddress destination;
    AOSSRequestBuffer* requestRecord;
    s16 recordLength;
    int encryptionResult;
    int result;

    memset(response, 0, 0x5dc);
    requestRecord = (AOSSRequestBuffer*)AOSSi_Alloc(0x210);
    if (requestRecord == 0) {
        s_connectionState = 2;
        return -1;
    }

    memset(requestRecord, 0, 0x210);
    responsePayload = response->payload;
    memcpy(s_accessPointName, &request->records[0], 8);
    memcpy(accessPointName, s_accessPointName, 8);
    recordLength = AOSS_81401BBC(&requestRecord->record);
    if (recordLength < 0) {
        s_connectionState = 3;
        if (requestRecord != 0) {
            AOSSi_Free(requestRecord);
        }
        result = -1;
    } else {
        s16 requestLength;

        requestRecord->type = 0;
        requestRecord->length = SOHtoNs((u16)recordLength);
        requestLength = (s16)(recordLength + 4);
        memcpy(responsePayload, requestRecord, requestLength);
        encryptionResult = AOSS_81401E80(accessPointName, 8, s_manufacturer, 6);
        if (encryptionResult != 0) {
            s_connectionState = 2;
            if (requestRecord != 0) {
                AOSSi_Free(requestRecord);
            }
            return -1;
        }
        response->header.initialLength = SOHtoNs(1);
        response->header.initialType = 0;
        response->header.initialSequence = 0;
        response->header.responseLength = SOHtoNs(0x1000);
        response->header.responseType = 0;
        response->header.finalLength = SOHtoNs(requestLength);
        response->header.finalSequence = SOHtoNs(0x10);
        response->header.reserved = 0;
        response->header.messageType = 0x11;
        memcpy(response->header.messageIdentity, accessPointName, 8);
        memset(&destination, 0, sizeof(destination));
        destination.family = 2;
        destination.port = SOHtoNs(0x5790);
        SOHtoNl(s_runtime.ipAddress);
        destination.address = 0xffffffff;
        destination.length = 8;
        requestLength += 0x18;
        SOSendTo(socket, response, requestLength, 0, &destination);
        if (requestRecord != 0) {
            AOSSi_Free(requestRecord);
        }
        result = 0;
    }
    return result;
}

int AOSS_81401778(void* packet, void* request, int socket) {
    AOSSHelloPacket* response = (AOSSHelloPacket*)s_responseBuffer;
    AOSSHelloPayload* payload = &response->payload;
    AOSSRequestRecords* requestRecords = (AOSSRequestRecords*)request;
    AOSSHelloRecord hello;
    AOSSSocketAddress destination;
    AOSSKeySchedule schedule;
    u8 accessPointName[8];
    u8 checksum;
    u16 nonce;
    u32 crc;
    u32 stateLength;
    u32 index;
    u32 firstByte;
    u32 secondByte;
    u8 value;
    u8 swap;
    s16 responseLength;
    int sequence;
    int encryptionResult;

    checksum = 0;
    sequence = 0;
    memset(&hello, 0, sizeof(hello));
    memset(response, 0, 0x5dc);
    hello.data.fields.type = 2;
    hello.data.fields.reserved01 = 0;
    hello.data.fields.length = SOHtoNs(4);
    hello.data.fields.address = s_runtime.ipAddress;
    hello.data.fields.address = SOHtoNl(s_runtime.ipAddress);
    responseLength = 8;

    if (s_connectionState == 1) {
        sequence = 1;
        AOSS_81401DC0(0, s_crcTable);
        crc = 0xffffffff;
        crc = (crc >> 8) ^ s_crcTable[(crc ^ hello.data.bytes[0]) & 0xff];
        crc = (crc >> 8) ^ s_crcTable[(crc ^ hello.data.bytes[1]) & 0xff];
        crc = (crc >> 8) ^ s_crcTable[(crc ^ hello.data.bytes[2]) & 0xff];
        crc = (crc >> 8) ^ s_crcTable[(crc ^ hello.data.bytes[3]) & 0xff];
        crc = (crc >> 8) ^ s_crcTable[(crc ^ hello.data.bytes[4]) & 0xff];
        crc = (crc >> 8) ^ s_crcTable[(crc ^ hello.data.bytes[5]) & 0xff];
        crc = (crc >> 8) ^ s_crcTable[(crc ^ hello.data.bytes[6]) & 0xff];
        crc = (crc >> 8) ^ s_crcTable[(crc ^ hello.data.bytes[7]) & 0xff];
        checksum = (u8)crc ^ 0xff;

        schedule.bytes = (u8*)AOSSi_Alloc(8);
        if (schedule.bytes != 0) {
            nonce = (u16)rand();
            memcpy(&payload->encrypted.key.nonce, &nonce, 2);
            memcpy(s_packetState.keyNonce, payload->encrypted.key.nonceBytes, 2);
            memcpy(s_packetState.keyAddress, s_accessPointName, 8);
            AOSS_81401C9C(&schedule, s_packetState.keyNonce,
                          sizeof(s_packetState.keyNonce) + sizeof(s_packetState.keyAddress), 8);
            for (index = 0; index < 8; index += 2) {
                schedule.i = (schedule.i + 1) % schedule.length & 0xff;
                firstByte = schedule.bytes[schedule.i];
                schedule.j = (firstByte + schedule.j) % schedule.length & 0xff;
                swap = schedule.bytes[schedule.j];
                stateLength = firstByte + swap;
                schedule.bytes[schedule.j] = schedule.bytes[schedule.i];
                schedule.bytes[schedule.i] = swap;
                value = schedule.bytes[stateLength % schedule.length] ^ hello.data.bytes[index];
                payload->bytes[index + 4] = value;

                schedule.i = (schedule.i + 1) % schedule.length & 0xff;
                secondByte = schedule.bytes[schedule.i];
                schedule.j = (secondByte + schedule.j) % schedule.length & 0xff;
                swap = schedule.bytes[schedule.j];
                stateLength = secondByte + swap;
                schedule.bytes[schedule.j] = schedule.bytes[schedule.i];
                schedule.bytes[schedule.i] = swap;
                value = schedule.bytes[stateLength % schedule.length] ^ hello.data.bytes[index + 1];
                payload->bytes[index + 5] = value;
            }
            AOSSi_Free(schedule.bytes);
        }
        payload->encrypted.length = SOHtoNs(8);
        responseLength = 0x0c;
    } else {
        memcpy(payload->bytes, &hello, 8);
    }

    memcpy(accessPointName, &requestRecords->records[1], 8);
    encryptionResult = AOSS_81401E80(accessPointName, 8, s_manufacturer, 6);
    if (encryptionResult != 0) {
        s_connectionState = 2;
        return -1;
    }

    response->header.initialLength = SOHtoNs(1);
    response->header.initialType = 0;
    response->header.initialSequence = 0;
    response->header.responseLength = SOHtoNs(0x2000);
    response->header.responseType = 0;
    response->header.finalLength = SOHtoNs(responseLength);
    response->header.finalSequence = SOHtoNs(sequence);
    response->header.reserved = checksum;
    response->header.messageType = 0x11;
    memcpy(response->header.messageIdentity, accessPointName, 8);
    memset(&destination, 0, sizeof(destination));
    destination.family = 2;
    destination.port = SOHtoNs(0x5790);
    destination.address = SOHtoNl(s_runtime.ipAddress);
    if (s_runtime.active == 0) {
        destination.address = 0xffffffff;
    }
    destination.length = 8;
    SOSendTo(socket, response, responseLength + 0x18, 0, &destination);
    return 0;
}

s16 AOSS_81401BBC(void* buffer) {
    AOSSOptionRecord* record = (AOSSOptionRecord*)buffer;
    u32 optionValue;
    u32 roundedLength;
    s16 dataLength;

    record->type = s_runtime.interfaceType;
    record->reserved01 = 1;
    dataLength = (s16)s_runtime.configLength;
    memcpy(record->data, s_runtime.config, dataLength);
    record->length = SOHtoNs(dataLength);
    dataLength = (s16)(dataLength + 6);
    roundedLength = (u32)((s32)dataLength + 1);
    roundedLength = (roundedLength >> 31) + roundedLength;
    dataLength = (s16)(roundedLength & ~1u);
    record->nextOffset = SOHtoNs(dataLength);
    record = (AOSSOptionRecord*)(dataLength + (u32)record);
    record->type = 0x60;
    record->reserved01 = 0;
    record->nextOffset = SOHtoNs(0);
    optionValue = SOHtoNl(0x0e);
    memcpy(record->data, &optionValue, sizeof(optionValue));
    record->length = SOHtoNs(4);
    return (s16)(dataLength + 10);
}void AOSS_81401C9C(AOSSKeySchedule* schedule, const u8* key, u32 keyLength, u32 stateLength) {
    u8* state;
    u8* cur;
    u32 index;
    u32 keyIndex;
    u32 swapIndex;
    u32 unrolledLimit;

    schedule->j = 0;
    state = schedule->bytes;
    schedule->i = 0;
    schedule->length = stateLength;
    index = 0;
    if (stateLength != 0) {
        unrolledLimit = stateLength - 8;
        if (stateLength > 8) {
            for (; index < unrolledLimit; index += 8) {
                cur = state + index;
                cur[0] = (u8)index;
                cur[1] = (u8)(index + 1);
                cur[2] = (u8)(index + 2);
                cur[3] = (u8)(index + 3);
                cur[4] = (u8)(index + 4);
                cur[5] = (u8)(index + 5);
                cur[6] = (u8)(index + 6);
                cur[7] = (u8)(index + 7);
            }
        }

        for (; index < stateLength; index++) {
            state[index] = (u8)index;
        }
    }

    index = 0;
    swapIndex = 0;
    keyIndex = 0;
    for (; index < stateLength; index++) {
        u8 value = state[index];
        u8 swapValue;

        swapIndex = (swapIndex + value + key[keyIndex]) % schedule->length;
        swapValue = state[swapIndex];
        state[swapIndex] = value;
        state[index] = swapValue;
        keyIndex++;
        if (keyIndex >= keyLength) {
            keyIndex = 0;
        }
    }
}

void AOSS_81401DC0(u32 seed, u32* table) {
    u32 index;
    u32 value;

    for (index = 0; index < 0x100; index++) {
        value = index;
        if ((value & 1) != 0) value = (value >> 1) ^ 0xedb88320;
        else value >>= 1;
        if ((value & 1) != 0) value = (value >> 1) ^ 0xedb88320;
        else value >>= 1;
        if ((value & 1) != 0) value = (value >> 1) ^ 0xedb88320;
        else value >>= 1;
        if ((value & 1) != 0) value = (value >> 1) ^ 0xedb88320;
        else value >>= 1;
        if ((value & 1) != 0) value = (value >> 1) ^ 0xedb88320;
        else value >>= 1;
        if ((value & 1) != 0) value = (value >> 1) ^ 0xedb88320;
        else value >>= 1;
        if ((value & 1) != 0) value = (value >> 1) ^ 0xedb88320;
        else value >>= 1;
        if ((value & 1) != 0) value = (value >> 1) ^ 0xedb88320;
        else value >>= 1;
        *table++ = value;
    }
}

int AOSS_81401E80(void* packet, s32 length, const char* key, int keyLength) {
    u8* packetBytes = (u8*)packet;
    u8* keyMask;
    u8* temporary;
    s32 halfLength = (((s32)((u32)length >> 31) + length) >> 1);
    s32 round;
    s32 index;
    s32 keyIndex;
    int result = -1;
    int unrollAllowed;

    keyMask = (u8*)AOSSi_Alloc(halfLength);
    if (keyMask == 0) {
        return -1;
    }

    temporary = (u8*)AOSSi_Alloc(length);
    if (temporary == 0) {
        AOSSi_Free(keyMask);
        return -1;
    }

    for (round = 0; round < 2; round++) {
        keyIndex = round % keyLength;
        for (index = 0; index < halfLength; index++) {
            keyMask[index] = (u8)index;
            keyMask[index] ^= (u8)key[keyIndex];
            keyIndex++;
            if (keyIndex >= keyLength) {
                keyIndex = 0;
            }
        }

        index = 0;
        if (halfLength > 0) {
            if (halfLength > 8) {
                unrollAllowed = halfLength >= 0 && halfLength <= 0x7ffffffe;
                if (unrollAllowed != 0) {
                    for (; index < halfLength - 8; index += 8) {
                        packetBytes[halfLength + index] ^= keyMask[index];
                        packetBytes[halfLength + index + 1] ^= keyMask[index + 1];
                        packetBytes[halfLength + index + 2] ^= keyMask[index + 2];
                        packetBytes[halfLength + index + 3] ^= keyMask[index + 3];
                        packetBytes[halfLength + index + 4] ^= keyMask[index + 4];
                        packetBytes[halfLength + index + 5] ^= keyMask[index + 5];
                        packetBytes[halfLength + index + 6] ^= keyMask[index + 6];
                        packetBytes[halfLength + index + 7] ^= keyMask[index + 7];
                    }
                }
            }
            for (; index < halfLength; index++) {
                packetBytes[halfLength + index] ^= keyMask[index];
            }
        }

        memcpy(temporary, packetBytes + halfLength, halfLength);
        memcpy(temporary + halfLength, packetBytes, halfLength);
        memcpy(packetBytes, temporary, length);
    }

    AOSSi_Free(keyMask);
    AOSSi_Free(temporary);
    result = 0;
    return result;
}

int AOSS_814020CC(void* settings, void* config) {
    s32 connectionAttempts = 0;
    u32 ticksPerMillisecond;

    if (AOSSi_WLANConnect() != 0) {
        return -1;
    }

    if (SOStartup() == 0) {
        s_socketStarted = 1;
        while (SOGetHostID() == 0) {
            if (AOSSi_cancel_flag == 1) {
                return -1;
            }

            connectionAttempts++;
            if (connectionAttempts > 30) {
                if (s_socketStarted == 1) {
                    s_socketStarted = 0;
                    SOCleanup();
                }
                *(u32*)s_responseBuffer = 0;
                break;
            }

            ticksPerMillisecond = (u32)(((u64)(__OSBusClock >> 2) * 0x10624dd3) >> 38);
            OSSleepTicks((OSTime)(ticksPerMillisecond * 100));
        }

        return 0;
    }

    return -1;
}
