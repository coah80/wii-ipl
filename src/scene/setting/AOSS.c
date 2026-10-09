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
} AOSSWaitSettings;

typedef struct AOSSSocketAddress {
    u8 length;
    u8 family;
    u16 port;
    u32 address;
} AOSSSocketAddress;

typedef struct AOSSPollDescriptor {
    s32 socket;
    s32 events;
    s32 returnedEvents;
} AOSSPollDescriptor;

typedef struct AOSSRuntimeState {
    void* config;
    u32 configLength;
    u32 flags;
    u32 state;
    u32 ipAddress;
    u32 subnetMask;
    u8 active;
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
    u16 controlFlags;
    u8 checksum;
    u8 messageType;
    AOSSPacketPayload payload;
} AOSSIncomingMessage;

typedef struct AOSSEncryptedPayload {
    u16 dataLength;
    u16 keyNonce;
    u8 data[0x5c0];
} AOSSEncryptedPayload;

typedef struct AOSSDecryptionMessage {
    u8 reserved00[6];
    u16 command;
    u8 reserved08[2];
    u16 outputLength;
    u16 controlFlags;
    u8 checksum;
    u8 messageType;
    u8 manufacturerAddress[8];
    union {
        AOSSEncryptedPayload encrypted;
        u8 bytes[0x5c4];
    } payload;
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
            u32 supportedModes;
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

static s32 s_socket = -1;
static char s_manufacturer[] = "MELCO";
static s32 s_operationState = -1;
static const u8 s_messageId[8] = { 9, 8, 0, 0, 0, 0, 0, 0 };
static u8 s_responseTypeByState[8] = { 9, 8, 0, 0, 0, 0, 0, 0 };
static const u16 s_defaultOptions[4] = { 0xffff, 0xffff, 0, 0 };

static void* s_responseBuffer;
static s32 s_socketStarted;
static u32 s_errorCode;
static u32 s_connectionState;
static u8 s_accessPointName[8];
static int* s_accessPointConfig;
static void* s_accessPointList;

extern int AOSSi_cancel_flag;

extern int AOSSi_WLANGetBSSList(void** list);
extern int AOSSi_Status(int status);
extern int AOSSi_SetNCDIPAddr(u32 ipAddress, u32 netmask, u32 gateway, u32 dns1, u32 dns2);
extern void AOSSi_Sleep(u32 duration);
struct AOSSConnection;
struct AOSSConnectionStatus;
extern int AOSSi_WLANConnect(struct AOSSConnection* connection, struct AOSSConnectionStatus* status);
extern int SOPoll(AOSSPollDescriptor* descriptors, int count, OSTime timeout);
extern int SORecvFrom(int socket, void* buffer, int length, int flags, void* address);
extern int SOSendTo(int socket, const void* buffer, int length, int flags, const void* address);
extern int SOBind(int socket, const void* address);

int AOSSValidateInitConfig(AOSSInitInput* input);
int AOSS_CheckAP(AOSSAccessPointRecord* list);
int AOSSDispatchReceiveState(int state, AOSSReceiveBuffer* packet, int* count, AOSSRequestRecords* request, int socket);
int AOSSHandleDiscoverReply(int state, AOSSReceiveBuffer* packet, int* count, AOSSRequestRecords* request);
int AOSSHandleAuthReply(int state, AOSSReceiveBuffer* packet, int* count, AOSSRequestRecords* request);
int AOSSHandleFinalReply(int state, AOSSReceiveBuffer* packet, int* count, AOSSRequestRecords* request);
int AOSSDecryptMessage(AOSSDecryptionMessage* message);
int AOSSCheckAccessPointName(u16 command, const u8* manufacturerAddress);
int AOSSParseWepConfig(const AOSSOptionRecord* packet, AOSSStoredConfig* config);
int AOSSParsePskConfig(const AOSSOptionRecord* packet, AOSSStoredConfig* config);
void AOSSInitKeySchedule(AOSSKeySchedule* schedule, const u8* key, u32 keyLength, u32 stateLength);
void AOSSInitCrc32Table(u32 seed, u32* table);
s16 AOSSBuildInterfaceOption(void* buffer);
int AOSSSendDiscoveryRequest(void* packet, AOSSRequestRecords* request, int socket);
int AOSSSendHelloRequest(void* packet, void* request, int socket);
int AOSSXorBufferWithKey(void* packet, s32 length, char* key, int keyLength);
int AOSSConnectAndAwaitHost(void* settings, void* config);
int AOSSParseNetworkSettings(const AOSSOptionRecord* packet, u8* settings);
int AOSSApplyAuthOptions(int state, const AOSSReplyOption* response, int responseLength, void* config, void* networkData);

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
  s16 initialWait;
  AOSSReceiveBuffer* packetBuffer;
  AOSSPacketHeader* packetWords;
  u32 initialSleep;
  u32 nextSleep;
  u32 resultCode;
  u32 flags;
  int state;
  int protocolState;
  u32 retryWait;
  u16 retryDelay;
  u32 delayStep;
  u32 packetLength;
  u16 receivedLength;
  int requestResult;
  size_t manufacturerLength;
  int timeoutSeconds;
  int timeoutMilliseconds;
  int protocolResult;
  OSTime timeoutTicks;
  int initializationResult;
  short attemptCount;
  u16 remainingWait;
  short waitAttempt;
  u16 defaultConnection;
  u16 defaultResponse;
  union {
    struct { s16 connection; s16 response; } limits;
    struct { u16 connection; u16 response; } defaults;
  } waitIntervals;
  AOSSWaitSettings waitSettings;
  int receivedPackets;
  u8 failureStatus;
  AOSSNetworkSettings settings;
  AOSSRequestRecords requestRecords;
  AOSSSocketAddress replyAddress;
  u8 messageIdentity[8];
  __declspec(align(32)) AOSSSocketAddress socketAddress;
  struct { int seconds; int microseconds; } pollTime;
  u32 networkAddresses[5];
  AOSSPollDescriptor pollArguments[2];

  defaultConnection = s_defaultOptions[0];
  defaultResponse = s_defaultOptions[1];
  waitIntervals.defaults.connection = defaultConnection;
  waitIntervals.defaults.response = defaultResponse;
  waitSettings.value = 0;
  receivedPackets = 0;
  protocolState = 0;
  memset(&requestRecords,0,0x18);
  waitIntervals.limits.connection = input->options[0];
  if (waitIntervals.limits.connection == -1) {
    waitIntervals.limits.connection = 10;
  }
  waitSettings.halfwords.high = input->options[2];
  if (waitSettings.halfwords.high == -1) {
    waitSettings.halfwords.high = 10;
  }
  waitIntervals.limits.response = input->options[1];
  if (waitIntervals.limits.response == -1) {
    waitIntervals.limits.response = 100;
  }
  waitSettings.halfwords.low = input->options[3];
  if (waitSettings.halfwords.low == -1) {
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
  flags = input->flags;
  s_runtime.flags = flags & 0xf;
  s_runtime.interfaceType = input->mode;
  s_runtime.state = 0;
  s_runtime.ipAddress = 0xc0a80b01;
  s_runtime.active = '\0';
  if ((flags & 1u) != 1u) {
    s_errorCode = 0x13;
    input->status = 0xf;
    if (s_accessPointConfig) {
      AOSSi_Free(s_accessPointConfig);
      s_accessPointConfig = (int *)0x0;
    }
    if (s_accessPointList) {
      AOSSi_Free(s_accessPointList);
      s_accessPointList = 0;
    }
    resultCode = 0xffffffff;
  } else {
    attemptCount = 0;
    if (s_operationState != 0) {
      s_operationState = 0;
      AOSSi_Status(0);
    }
    initialWait = waitIntervals.limits.connection;
    while (1) {
      if (s_accessPointList) {
        AOSSi_Free(s_accessPointList);
        s_accessPointList = 0;
      }
      state = AOSSi_WLANGetBSSList(&s_accessPointList);
      if (state == -1) {
        input->status = 0xf;
        if (s_accessPointConfig) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = (int *)0x0;
        }
        if (s_accessPointList) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto finish_initialization;
      }
      if (AOSSi_cancel_flag == 1) {
        input->status = 0xf;
        if (s_accessPointConfig) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = (int *)0x0;
        }
        if (s_accessPointList) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto finish_initialization;
      }
      state = AOSS_CheckAP(s_accessPointList);
      if (state == 4) {
        input->status = 2;
        if (s_accessPointConfig) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = (int *)0x0;
        }
        if (s_accessPointList) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto finish_initialization;
      }
      if (state != 0) {
        if (attemptCount >= initialWait) {
          input->status = 1;
          if (s_accessPointConfig) {
            AOSSi_Free(s_accessPointConfig);
            s_accessPointConfig = (int *)0x0;
          }
          if (s_accessPointList) {
            AOSSi_Free(s_accessPointList);
            s_accessPointList = 0;
          }
          resultCode = 0xffffffff;
          goto finish_initialization;
        }
        remainingWait = waitIntervals.limits.response;
        for (; remainingWait != 0; remainingWait -= initialSleep) {
          if (AOSSi_cancel_flag == 1) {
            input->status = 0xf;
            if (s_accessPointConfig) {
              AOSSi_Free(s_accessPointConfig);
              s_accessPointConfig = (int *)0x0;
            }
            if (s_accessPointList) {
              AOSSi_Free(s_accessPointList);
              s_accessPointList = 0;
            }
            resultCode = 0xffffffff;
            goto finish_initialization;
          }
          AOSSi_Sleep(remainingWait > 100 ? 100 : remainingWait);
          if (remainingWait > 100) initialSleep = 100;
          else initialSleep = remainingWait;
        }
        if (AOSSi_cancel_flag == 1) {
          input->status = 0xf;
          if (s_accessPointConfig) {
            AOSSi_Free(s_accessPointConfig);
            s_accessPointConfig = 0;
          }
          if (s_accessPointList) {
            AOSSi_Free(s_accessPointList);
            s_accessPointList = 0;
          }
          resultCode = 0xffffffff;
          goto finish_initialization;
        }
        attemptCount++;
      } else {
        if (s_operationState != 1) {
          s_operationState = 1;
          AOSSi_Status(1);
        }
        memset(&settings,0,0x3c);
        settings.networkNameLength = strlen("ESSID-AOSS");
        memcpy(settings.networkName,"ESSID-AOSS",settings.networkNameLength);
        settings.useManufacturer = 1;
        settings.manufacturerLength = strlen(s_manufacturer);
        if (settings.manufacturerLength <= 0xd) {
          memcpy(settings.manufacturer,s_manufacturer,settings.manufacturerLength);
        }
        initializationResult = AOSSi_SetNCDIPAddr(0xc0a80b65,0xffffff00,0xc0a80b01,0,0);
        state = initializationResult;
        if (state != 0) {
          s_errorCode = 0xc;
          input->status = 0xf;
          if (s_accessPointConfig) {
            AOSSi_Free(s_accessPointConfig);
            s_accessPointConfig = (int *)0x0;
          }
          if (s_accessPointList) {
            AOSSi_Free(s_accessPointList);
            s_accessPointList = 0;
          }
          resultCode = 0xffffffff;
        } else {
          /* The original initialization path repeats this status check. */
          if (state != 0) {
            input->status = 0xf;
            if (s_accessPointConfig) {
              AOSSi_Free(s_accessPointConfig);
              s_accessPointConfig = 0;
            }
            if (s_accessPointList) {
              AOSSi_Free(s_accessPointList);
              s_accessPointList = 0;
            }
            resultCode = 0xffffffff;
            goto finish_initialization;
          }
          s_accessPointConfig = (int *)AOSSi_Alloc(0x58);
          if (s_accessPointConfig == 0) {
            input->status = 0xf;
            if (s_accessPointConfig) {
              AOSSi_Free(s_accessPointConfig);
              s_accessPointConfig = (int *)0x0;
            }
            if (s_accessPointList) {
              AOSSi_Free(s_accessPointList);
              s_accessPointList = 0;
            }
            resultCode = 0xffffffff;
          } else {
            memset(s_accessPointConfig,0,0x58);
            initialWait = waitIntervals.limits.connection;
            attemptCount = 0;
            goto test_initial_link;
          }
        }
        goto finish_initialization;
      }
    }
    input->status = 0xf;
    if (s_accessPointConfig) {
      AOSSi_Free(s_accessPointConfig);
      s_accessPointConfig = (int *)0x0;
    }
    if (s_accessPointList) {
      AOSSi_Free(s_accessPointList);
      s_accessPointList = 0;
    }
    resultCode = 0xffffffff;
    }
  goto finish_initialization;
wait_for_initial_link:
  state = AOSSConnectAndAwaitHost(&settings,s_accessPointConfig);
  if (state == -1) {
    input->status = 0xf;
    if (s_accessPointConfig) {
      AOSSi_Free(s_accessPointConfig);
      s_accessPointConfig = (int *)0x0;
    }
    if (s_accessPointList) {
      AOSSi_Free(s_accessPointList);
      s_accessPointList = 0;
    }
    resultCode = 0xffffffff;
    goto finish_initialization;
  }
  if ((state == 0) && (*s_accessPointConfig == 1u)) goto handle_initial_link;
  remainingWait = (u16)waitIntervals.limits.response;
  for (; remainingWait != 0; remainingWait = (u16)(remainingWait - nextSleep)) {
    if (AOSSi_cancel_flag == 1) {
      input->status = 0xf;
      if (s_accessPointConfig) {
        AOSSi_Free(s_accessPointConfig);
        s_accessPointConfig = (int *)0x0;
      }
      if (s_accessPointList) {
        AOSSi_Free(s_accessPointList);
        s_accessPointList = 0;
      }
      resultCode = 0xffffffff;
      goto finish_initialization;
    }
    AOSSi_Sleep(remainingWait > 100 ? 100 : remainingWait);
    if (remainingWait > 100) nextSleep = 100;
    else nextSleep = remainingWait;
  }
  if (AOSSi_cancel_flag == 1) {
    input->status = 0xf;
    if (s_accessPointConfig) {
      AOSSi_Free(s_accessPointConfig);
      s_accessPointConfig = (int *)0x0;
    }
    if (s_accessPointList) {
      AOSSi_Free(s_accessPointList);
      s_accessPointList = 0;
    }
    resultCode = 0xffffffff;
    goto finish_initialization;
  }
  attemptCount++;
test_initial_link:
  if (attemptCount < initialWait) goto wait_for_initial_link;
handle_initial_link:
  if (attemptCount == waitIntervals.limits.connection) {
    input->status = 0xf;
    if (s_accessPointConfig) {
      AOSSi_Free(s_accessPointConfig);
      s_accessPointConfig = (int *)0x0;
    }
    if (s_accessPointList) {
      AOSSi_Free(s_accessPointList);
      s_accessPointList = 0;
    }
    resultCode = 0xffffffff;
  }
  else {
    if (s_accessPointConfig) {
      AOSSi_Free(s_accessPointConfig);
      s_accessPointConfig = (int *)0x0;
    }
    if (s_accessPointList) {
      AOSSi_Free(s_accessPointList);
      s_accessPointList = 0;
    }
    {
      int recordIndex;
      for (recordIndex = 0; recordIndex < 3; recordIndex++) {
        memcpy(requestRecords.records[recordIndex].address, input->optionData, 6);
        requestRecords.records[recordIndex].transactionId = rand();
        requestRecords.records[recordIndex].transactionId =
            SOHtoNs(requestRecords.records[recordIndex].transactionId);
      }
    }
    s_socket = SOSocket(2,2,0);
    if (s_socket < 0) {
      input->status = 0xf;
      if (s_accessPointConfig) {
        AOSSi_Free(s_accessPointConfig);
        s_accessPointConfig = (int *)0x0;
      }
      if (s_accessPointList) {
        AOSSi_Free(s_accessPointList);
        s_accessPointList = 0;
      }
      resultCode = 0xffffffff;
    }
    else if (initializationResult < 0) {
      s_errorCode = 0xb;
      input->status = 0xf;
      if (s_accessPointConfig) {
        AOSSi_Free(s_accessPointConfig);
        s_accessPointConfig = (int *)0x0;
      }
      if (s_accessPointList) {
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
      if (state < 0) {
        input->status = 0xf;
        if (s_accessPointConfig) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = 0;
        }
        if (s_accessPointList) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto finish_initialization;
      }
      {
        attemptCount = waitSettings.halfwords.high;
        settings.gatewayAddress = 0xc0a80b65;
        settings.ipAddress = 0xc0a80b01;
perform_request:
        packetBuffer = s_responseBuffer;
        memset(networkAddresses,0,0x14);
        networkAddresses[4] = settings.gatewayAddress;
        networkAddresses[0] = settings.ipAddress;
        do {
          if ((protocolState == 1) && ((s8)s_runtime.active != 1)) {
            if (s_socket != -1) {
              SOClose(s_socket);
            }
            s_socket = -1;
            if (s_socketStarted == 1) {
              s_socketStarted = 0;
              requestResult = SOCleanup();
              if (requestResult >= 0) goto request_socket_cleanup_complete;
              requestResult = -1;
            }
            else {
request_socket_cleanup_complete:
              requestResult = 0;
            }
            if (requestResult != 0) {
              input->status = 0xf;
              if (s_accessPointConfig) {
                AOSSi_Free(s_accessPointConfig);
                s_accessPointConfig = (int *)0x0;
              }
              if (s_accessPointList) {
                AOSSi_Free(s_accessPointList);
                s_accessPointList = 0;
              }
              resultCode = 0xffffffff;
              goto finish_initialization;
            }
            {
              u32 mask = s_runtime.subnetMask;
              u32 networkAddress = s_runtime.ipAddress & mask;
              u32 localAddress = networkAddress | ((s_runtime.ipAddress & ~mask) + 1);
              if (localAddress >= (networkAddress | ~mask)) {
                localAddress = networkAddress | 1;
              }
              requestResult = AOSSi_SetNCDIPAddr(localAddress,s_runtime.subnetMask,s_runtime.ipAddress,0,0);
            }
            if (requestResult != 0) {
              s_errorCode = 0xc;
              input->status = 0xf;
              if (s_accessPointConfig) {
                AOSSi_Free(s_accessPointConfig);
                s_accessPointConfig = (int *)0x0;
              }
              if (s_accessPointList) {
                AOSSi_Free(s_accessPointList);
                s_accessPointList = 0;
              }
              resultCode = 0xffffffff;
              goto finish_initialization;
            }
            s_runtime.active = '\x01';
            s_accessPointConfig = (int *)AOSSi_Alloc(0x58);
            if (s_accessPointConfig == (int *)0x0) {
              input->status = 0xf;
              if (s_accessPointConfig) {
                AOSSi_Free(s_accessPointConfig);
                s_accessPointConfig = (int *)0x0;
              }
              if (s_accessPointList) {
                AOSSi_Free(s_accessPointList);
                s_accessPointList = 0;
              }
              resultCode = 0xffffffff;
              goto finish_initialization;
            }
            memset(s_accessPointConfig,0,0x58);
            initialWait = waitIntervals.limits.connection;
            for (waitAttempt = 0; waitAttempt < (short)initialWait; waitAttempt++) {
              requestResult = AOSSConnectAndAwaitHost(&settings,s_accessPointConfig);
              if (requestResult == -1) {
                input->status = 0xf;
                if (s_accessPointConfig) {
                  AOSSi_Free(s_accessPointConfig);
                  s_accessPointConfig = (int *)0x0;
                }
                if (s_accessPointList) {
                  AOSSi_Free(s_accessPointList);
                  s_accessPointList = 0;
                }
                resultCode = 0xffffffff;
                goto finish_initialization;
              }
              if ((requestResult == 0) && ((u32)*s_accessPointConfig == 1u)) break;
              remainingWait = waitIntervals.limits.response;
              for (; remainingWait != 0; remainingWait -= initialSleep) {
                if (AOSSi_cancel_flag == 1) {
                  input->status = 0xf;
                  if (s_accessPointConfig) {
                    AOSSi_Free(s_accessPointConfig);
                    s_accessPointConfig = (int *)0x0;
                  }
                  if (s_accessPointList) {
                    AOSSi_Free(s_accessPointList);
                    s_accessPointList = 0;
                  }
                  resultCode = 0xffffffff;
                  goto finish_initialization;
                }
                AOSSi_Sleep(remainingWait > 100 ? 100 : remainingWait);
                if (remainingWait > 100) initialSleep = 100;
                else initialSleep = remainingWait;
              }
              if (AOSSi_cancel_flag == 1) {
                input->status = 0xf;
                if (s_accessPointConfig) {
                  AOSSi_Free(s_accessPointConfig);
                  s_accessPointConfig = (int *)0x0;
                }
                if (s_accessPointList) {
                  AOSSi_Free(s_accessPointList);
                  s_accessPointList = 0;
                }
                resultCode = 0xffffffff;
                goto finish_initialization;
              }
            }
            s_socket = SOSocket(2,2,0);
            if (s_socket < 0) {
              input->status = 0xf;
              if (s_accessPointConfig) {
                AOSSi_Free(s_accessPointConfig);
                s_accessPointConfig = (int *)0x0;
              }
              if (s_accessPointList) {
                AOSSi_Free(s_accessPointList);
                s_accessPointList = 0;
              }
              resultCode = 0xffffffff;
              goto finish_initialization;
            }
            memset(&socketAddress,0,8);
            socketAddress.family = 2;
            socketAddress.address = SOGetHostID();
            socketAddress.port = SOHtoNs(0x5790);
            socketAddress.length = 8;
            requestResult = SOBind(s_socket,&socketAddress);
            if (requestResult < 0) {
              input->status = 0xf;
              if (s_accessPointConfig) {
                AOSSi_Free(s_accessPointConfig);
                s_accessPointConfig = (int *)0x0;
              }
              if (s_accessPointList) {
                AOSSi_Free(s_accessPointList);
                s_accessPointList = 0;
              }
              resultCode = 0xffffffff;
              goto finish_initialization;
            }
          }
          {
            int sendResult;
            int requestSocket = s_socket;
            switch (protocolState) {
            case 0:
              if (s_operationState != 2) {
                s_operationState = 2;
                AOSSi_Status(2);
              }
              sendResult = AOSSSendDiscoveryRequest(networkAddresses,&requestRecords,requestSocket);
              break;
            case 1:
              if (s_operationState != 3) {
                s_operationState = 3;
                AOSSi_Status(3);
              }
              sendResult = AOSSSendHelloRequest(networkAddresses,&requestRecords,requestSocket);

              break;
            case 2:
              if (s_operationState != 5) {
                s_operationState = 5;
                AOSSi_Status(5);
              }
              packetWords = s_responseBuffer;
              memset(s_responseBuffer,0,0x5dc);
              memcpy(messageIdentity,&requestRecords.records[2],8);
              manufacturerLength = strlen(s_manufacturer);
              AOSSXorBufferWithKey(messageIdentity,8,s_manufacturer,manufacturerLength);
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
              if ((s8)s_runtime.active == 0) {
                replyAddress.address = 0xffffffff;
              }
              replyAddress.length = 8;
              SOSendTo(requestSocket,packetWords,0x18,0,&replyAddress);
              sendResult = 0;

              break;
            default:
              sendResult = -1;
              break;
            }
            if (sendResult == -1) {
              s_errorCode = protocolState + 0x1000;
              input->status = 0xf;
              if (s_accessPointConfig) {
                AOSSi_Free(s_accessPointConfig);
                s_accessPointConfig = (int *)0x0;
              }
              if (s_accessPointList) {
                AOSSi_Free(s_accessPointList);
                s_accessPointList = 0;
              }
              resultCode = 0xffffffff;
              goto finish_initialization;
            }
          }
          memset(packetBuffer,0,0x5f8);
          pollTime.seconds = timeoutMilliseconds / 1000;
          pollTime.microseconds = (timeoutMilliseconds % 1000) * 1000;
          pollArguments[0].events = 1;
          pollArguments[0].socket = s_socket;
          pollArguments[0].returnedEvents = 0;
          pollArguments[1].socket = s_socket;
          pollArguments[1].returnedEvents = 0;
          pollArguments[1].events = 1;
          timeoutTicks = 0;
          timeoutTicks += (OSTime)(u32)OSSecondsToTicks(pollTime.seconds);
          timeoutTicks += (OSTime)(u32)OSMicrosecondsToTicks(pollTime.microseconds);
          requestResult = SOPoll(pollArguments,1,(OSTime)timeoutTicks);
          if (0 < requestResult) goto process_received_packet;
          receivedPackets = receivedPackets + 1;
          if (receivedPackets > attemptCount) {
            if (protocolState == 0) {
              s_errorCode = 0xf;
            } else if (protocolState == 1) {
              s_errorCode = 0x10;
            } else {
              s_errorCode = 0x11;
            }
            protocolResult = -1;
            goto close_protocol_socket;
          }
          retryDelay = waitSettings.halfwords.low;
          for (; retryDelay != 0; retryDelay -= delayStep) {
            if (AOSSi_cancel_flag == 1) {
              input->status = 0xf;
              if (s_accessPointConfig) {
                AOSSi_Free(s_accessPointConfig);
                s_accessPointConfig = (int *)0x0;
              }
              if (s_accessPointList) {
                AOSSi_Free(s_accessPointList);
                s_accessPointList = 0;
              }
              resultCode = 0xffffffff;
              goto finish_initialization;
            }
            AOSSi_Sleep(retryDelay > 100 ? 100 : retryDelay);
            if (retryDelay > 100) delayStep = 100;
            else delayStep = retryDelay;
          }
          if (AOSSi_cancel_flag == 1) {
            input->status = 0xf;
            if (s_accessPointConfig) {
              AOSSi_Free(s_accessPointConfig);
              s_accessPointConfig = (int *)0x0;
            }
            if (s_accessPointList) {
              AOSSi_Free(s_accessPointList);
              s_accessPointList = 0;
            }
            resultCode = 0xffffffff;
            goto finish_initialization;
          }
        } while (1);
      }
      input->status = 0xf;
      if (s_accessPointConfig) {
        AOSSi_Free(s_accessPointConfig);
        s_accessPointConfig = (int *)0x0;
      }
      if (s_accessPointList) {
        AOSSi_Free(s_accessPointList);
        s_accessPointList = 0;
      }
      resultCode = 0xffffffff;
    }
  }
  goto finish_initialization;
process_received_packet:
  {
    AOSSSocketAddress receivedAddress;
    u8 addressLength = sizeof(receivedAddress);
    receivedAddress.length = addressLength;
    receivedLength = SORecvFrom(s_socket,&packetBuffer->message,0x5dc,0,&receivedAddress);
  }
  packetBuffer->socket = s_socket;
  retryWait = SONtoHs(receivedLength);
  packetBuffer->length = retryWait & 0xffff;
  requestResult = AOSSDispatchReceiveState(protocolState,packetBuffer,&receivedPackets,&requestRecords,s_socket);
  if (requestResult == 100) {
    protocolResult = 0;
  }
  else if (requestResult == -1) {
    protocolResult = -1;
  }
  else {
    if (protocolState != requestResult) {
      if (requestResult != 2) goto advance_protocol_state;
      if (s_socket != -1) {
        SOClose(s_socket);
      }
      s_socket = -1;
      if (s_socketStarted == 1) {
        s_socketStarted = 0;
        state = SOCleanup();
        if (state < 0) {
          state = -1;
          goto wait_for_packet;
        }
      }
      state = 0;
wait_for_packet:
      if (state != 0) {
        input->status = 0xf;
        if (s_accessPointConfig) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = (int *)0x0;
        }
        if (s_accessPointList) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto finish_initialization;
      }
      if (s_operationState != 4) {
        s_operationState = 4;
        AOSSi_Status(4);
      }
      if (s_accessPointList) {
        AOSSi_Free(s_accessPointList);
        s_accessPointList = 0;
      }
      state = AOSSi_WLANGetBSSList(&s_accessPointList);
      if (state == -1) {
        input->status = 0xf;
        if (s_accessPointConfig) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = (int *)0x0;
        }
        if (s_accessPointList) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto finish_initialization;
      }
      if (AOSSi_cancel_flag == 1) {
        input->status = 0xf;
        if (s_accessPointConfig) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = (int *)0x0;
        }
        if (s_accessPointList) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto finish_initialization;
      }
      state = AOSS_CheckAP(s_accessPointList);
      if (state == 4) {
        input->status = 2;
        if (s_accessPointConfig) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = (int *)0x0;
        }
        if (s_accessPointList) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto finish_initialization;
      }
      if (state != 0) {
        input->status = 1;
        if (s_accessPointConfig) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = (int *)0x0;
        }
        if (s_accessPointList) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto finish_initialization;
      }
      s_accessPointConfig = (int *)AOSSi_Alloc(0x58);
      if (s_accessPointConfig == (int *)0x0) {
        input->status = 0xf;
        if (s_accessPointConfig) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = (int *)0x0;
        }
        if (s_accessPointList) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto finish_initialization;
      }
      memset(s_accessPointConfig,0,0x58);
      initialWait = waitIntervals.limits.connection;
      for (waitAttempt = 0; waitAttempt < (short)initialWait; waitAttempt++) {
        state = AOSSConnectAndAwaitHost(&settings,s_accessPointConfig);
        if (state == -1) {
          input->status = 0xf;
          if (s_accessPointConfig) {
            AOSSi_Free(s_accessPointConfig);
            s_accessPointConfig = (int *)0x0;
          }
          if (s_accessPointList) {
            AOSSi_Free(s_accessPointList);
            s_accessPointList = 0;
          }
          resultCode = 0xffffffff;
          goto finish_initialization;
        }
        if ((state == 0) && ((u32)*s_accessPointConfig == 1u)) break;
        remainingWait = waitIntervals.limits.response;
        for (; remainingWait != 0; remainingWait -= initialSleep) {
          if (AOSSi_cancel_flag == 1) {
            input->status = 0xf;
            if (s_accessPointConfig) {
              AOSSi_Free(s_accessPointConfig);
              s_accessPointConfig = (int *)0x0;
            }
            if (s_accessPointList) {
              AOSSi_Free(s_accessPointList);
              s_accessPointList = 0;
            }
            resultCode = 0xffffffff;
            goto finish_initialization;
          }
          AOSSi_Sleep(remainingWait > 100 ? 100 : remainingWait);
          if (remainingWait > 100) initialSleep = 100;
          else initialSleep = remainingWait;
        }
        if (AOSSi_cancel_flag == 1) {
          input->status = 0xf;
          if (s_accessPointConfig) {
            AOSSi_Free(s_accessPointConfig);
            s_accessPointConfig = (int *)0x0;
          }
          if (s_accessPointList) {
            AOSSi_Free(s_accessPointList);
            s_accessPointList = 0;
          }
          resultCode = 0xffffffff;
          goto finish_initialization;
        }
      }
      if (s_accessPointConfig) {
        AOSSi_Free(s_accessPointConfig);
        s_accessPointConfig = (int *)0x0;
      }
      if (s_accessPointList) {
        AOSSi_Free(s_accessPointList);
        s_accessPointList = 0;
      }
      s_socket = SOSocket(2,2,0);
      if (s_socket < 0) {
        input->status = 0xf;
        if (s_accessPointConfig) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = (int *)0x0;
        }
        if (s_accessPointList) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto finish_initialization;
      }
      memset(&socketAddress,0,8);
      socketAddress.family = 2;
      socketAddress.address = SOGetHostID();
      socketAddress.port = SOHtoNs(0x5790);
      socketAddress.length = 8;
      timeoutSeconds = SOBind(s_socket,&socketAddress);
      if (timeoutSeconds < 0) {
        input->status = 0xf;
        if (s_accessPointConfig) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = (int *)0x0;
        }
        if (s_accessPointList) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto finish_initialization;
      }
advance_protocol_state:
      protocolState = requestResult;
      goto perform_request;
    }
    protocolState = requestResult;
    if (receivedPackets > waitSettings.halfwords.high) {
      if (requestResult == 0) {
        s_errorCode = 0xf;
      } else if (requestResult == 1) {
        s_errorCode = 0x10;
      } else {
        s_errorCode = 0x11;
      }
      protocolResult = -1;
      goto close_protocol_socket;
    }
    retryDelay = waitSettings.halfwords.low;
    for (; retryDelay != 0; retryDelay -= delayStep) {
      if (AOSSi_cancel_flag == 1) {
        input->status = 0xf;
        if (s_accessPointConfig) {
          AOSSi_Free(s_accessPointConfig);
          s_accessPointConfig = (int *)0x0;
        }
        if (s_accessPointList) {
          AOSSi_Free(s_accessPointList);
          s_accessPointList = 0;
        }
        resultCode = 0xffffffff;
        goto finish_initialization;
      }
      AOSSi_Sleep(retryDelay > 100 ? 100 : retryDelay);
      if (retryDelay > 100) delayStep = 100;
      else delayStep = retryDelay;
    }
    if (AOSSi_cancel_flag == 1) {
      input->status = 0xf;
      if (s_accessPointConfig) {
        AOSSi_Free(s_accessPointConfig);
        s_accessPointConfig = (int *)0x0;
      }
      if (s_accessPointList) {
        AOSSi_Free(s_accessPointList);
        s_accessPointList = 0;
      }
      resultCode = 0xffffffff;
      goto finish_initialization;
    }
    goto perform_request;
  }
close_protocol_socket:
  if (s_socket != -1) {
    SOClose(s_socket);
  }
  s_socket = -1;
  if (s_socketStarted == 1) {
    s_socketStarted = 0;
    state = SOCleanup();
    if (state >= 0) goto protocol_socket_cleanup_complete;
    state = -1;
  }
  else {
protocol_socket_cleanup_complete:
    state = 0;
  }
  if (state != 0) {
    input->status = 0xf;
    if (s_accessPointConfig) {
      AOSSi_Free(s_accessPointConfig);
      s_accessPointConfig = (int *)0x0;
    }
    if (s_accessPointList) {
      AOSSi_Free(s_accessPointList);
      s_accessPointList = 0;
    }
    resultCode = 0xffffffff;
    goto finish_initialization;
  }
  if (protocolResult != 0) {
    switch (s_errorCode) {
    case 0xf: failureStatus = 3; break;
    case 0x10: failureStatus = 4; break;
    case 0x11: failureStatus = 5; break;
    case 0x14: failureStatus = 7; break;
    case 0x15: failureStatus = 8; break;
    default: failureStatus = 0xf; break;
    }
    input->status = failureStatus;
    if (s_accessPointConfig) {
      AOSSi_Free(s_accessPointConfig);
      s_accessPointConfig = (int *)0x0;
    }
    if (s_accessPointList) {
      AOSSi_Free(s_accessPointList);
      s_accessPointList = 0;
    }
    resultCode = 0xffffffff;
    goto finish_initialization;
  } else {
    protocolResult = AOSSValidateInitConfig(input);
    if (protocolResult == 0) goto configuration_success;
    {
      input->status = 6;
      if (s_accessPointConfig) {
        AOSSi_Free(s_accessPointConfig);
        s_accessPointConfig = (int *)0x0;
      }
      if (s_accessPointList) {
        AOSSi_Free(s_accessPointList);
        s_accessPointList = 0;
      }
      resultCode = 0xffffffff;
    }
    goto finish_initialization;
configuration_success:
    resultCode = 0;
    goto finish_initialization;
  }
finish_initialization:
  return (int)resultCode;
}

int AOSSValidateInitConfig(AOSSInitInput* input) {
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

    input->flags = s_runtime.flags & s_runtime.state;
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

int AOSSDispatchReceiveState(int state, AOSSReceiveBuffer* packet, int* count, AOSSRequestRecords* request, int socket) {
    u16 messageLength = SONtoHs(packet->message.messageLength);
    u16 opcode;

    if (messageLength < 1) {
        (*count)++;
        return state;
    }
    if (packet->message.messageType != 0x11) {
        (*count)++;
        return state;
    }
    if (AOSSDecryptMessage((AOSSDecryptionMessage*)&packet->message) > 0) {
        (*count)++;
        return state;
    }
    opcode = SONtoHs(packet->message.opcode);
    switch (opcode) {
    case 0x1010:
        state = AOSSHandleDiscoverReply(state, packet, count, request);
        break;
    case 0x2010:
        state = AOSSHandleAuthReply(state, packet, count, request);
        break;
    case 0x3010:
        state = AOSSHandleFinalReply(state, packet, count, request);
        break;
    }
    return state;
}

int AOSSHandleDiscoverReply(int state, AOSSReceiveBuffer* packet, int* count, AOSSRequestRecords* request) {
    AOSSReplyPayload* reply;
    AOSSRequestRecord* requestRecord;
    size_t manufacturerLength;
    int compareResult;
    u16 packetSequence;
    u16 requestSequence;
    u16 status;
    int validationResult;
    int parserResult;
    u32 addressStatus;
    u32* address;
    u32 operationState;

    if (state != 0) {
        (*count)++;
        return state;
    }
    validationResult = 0;
    manufacturerLength = strlen(s_manufacturer);
    reply = &packet->message.payload.reply;
    requestRecord = &request->records[0];
    AOSSXorBufferWithKey(&packet->message.payload.manufacturerAddress, 8, s_manufacturer, manufacturerLength);
    compareResult = memcmp(requestRecord->address, packet->message.payload.manufacturerAddress, 6);
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
        (*count)++;
        return state;
    }
    status = SONtoHs(reply->status);
    if (status == 0) {
        (*count)++;
        return state;
    }
    if (reply->responseType == 7) {
        address = &reply->data.address;
        if (SONtoHl(*address) == (u32)-2) {
            s_errorCode = 0x14;
        } else {
            addressStatus = SONtoHl(*address);
            s_errorCode = addressStatus == (u32)-3 ? 0x15 : 0x18;
        }
        return -1;
    }
    if (reply->responseType != 1) {
        (*count)++;
        return state;
    }
    parserResult = AOSSParseNetworkSettings(&reply->data.optionRecord, s_networkBuffer);
    if (parserResult < 0) {
        if (parserResult == -2) {
            s_errorCode = 0x16;
            return -1;
        }
        (*count)++;
        return state;
    }
    packetSequence = SONtoHs(packet->message.controlFlags);
    operationState = 0;
    if ((packetSequence & 0x10) != 0) {
        operationState = 1;
    }
    s_connectionState = operationState;
    *count = 0;
    return 1;
}

int AOSSHandleAuthReply(int state, AOSSReceiveBuffer* packet, int* count, AOSSRequestRecords* request) {
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
    AOSSXorBufferWithKey(&packet->message.payload.manufacturerAddress, 8, s_manufacturer, manufacturerLength);
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
            operationResult = AOSSApplyAuthOptions(0, (const AOSSReplyOption*)reply, authType, &s_configData,
                                            s_networkBuffer);
            if (operationResult < 0) {
                *count = *count + 1;
                return state;
            }
            if ((s_runtime.state & s_runtime.flags) == 0) {
                return state;
            }
            *count = 0;
            return 2;
        }
    }
    return state;
}

int AOSSHandleFinalReply(int state, AOSSReceiveBuffer* packet, int* count, AOSSRequestRecords* request) {
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
    AOSSXorBufferWithKey(&packet->message.payload.manufacturerAddress, 8, s_manufacturer, manufacturerLength);
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

int AOSSDecryptMessage(AOSSDecryptionMessage* message) {
    struct { u32 expected; u32 actual; } integrity;
    u8 manufacturerAddress[8];
    AOSSKeySchedule schedule;
    AOSSEncryptedPayload* encrypted = &message->payload.encrypted;
    u32 firstValue;
    u32 secondValue;
    u8* state;
    u32 i;
    s32 crcIndex;
    u32 firstIndex;
    u32 secondIndex;
    u8* decryptedData;
    u32 controlFlags;
    u32 stateIndex;
    const u8* inputCursor;
    u32 dataLength;
    int result;

    memcpy(manufacturerAddress, message->manufacturerAddress, sizeof(manufacturerAddress));
    result = AOSSXorBufferWithKey(manufacturerAddress, sizeof(manufacturerAddress), s_manufacturer,
        strlen(s_manufacturer));
    if (result == -1) {
        s_errorCode = 2;
        return -100;
    }

    result = AOSSCheckAccessPointName(SONtoHs(message->command), manufacturerAddress);
    if (result != 0) {
        return result;
    }

    if (SONtoHs(message->command) == 0x1000) {
        memcpy(s_accessPointName, manufacturerAddress, sizeof(s_accessPointName));
    }

    controlFlags = SONtoHs(message->controlFlags);
    if ((controlFlags & 0xf) == 0) {
        return 0;
    }

    dataLength = SONtoHs(encrypted->dataLength);
    decryptedData = AOSSi_Alloc(dataLength);
    if (decryptedData == 0) {
        s_errorCode = 2;
        return 100;
    }

    integrity.expected = message->checksum;
    schedule.bytes = AOSSi_Alloc(dataLength);
    if (schedule.bytes == 0) {
        s_errorCode = 2;
        result = -1;
    } else {
        memcpy(s_packetState.key.nonce, &encrypted->keyNonce, sizeof(encrypted->keyNonce));
        memcpy(s_packetState.key.address, s_accessPointName, sizeof(s_accessPointName));
        AOSSInitKeySchedule(&schedule, (const u8*)&s_packetState.key, sizeof(s_packetState.key), dataLength);

        inputCursor = encrypted->data;
        for (i = 0; i < dataLength; i++) {
            state = schedule.bytes;
            firstIndex = ((schedule.i + 1) % schedule.length) & 0xff;
            firstValue = state[firstIndex];
            secondIndex = ((firstValue + schedule.j) % schedule.length) & 0xff;
            secondValue = state[secondIndex];
            stateIndex = firstValue + secondValue;
            schedule.i = firstIndex;
            schedule.j = secondIndex;
            state[secondIndex] = (u8)firstValue;
            state[firstIndex] = (u8)secondValue;
            {
                u8 streamByte = state[stateIndex % schedule.length];
                decryptedData[i] = streamByte ^ *inputCursor++;
            }
        }

        integrity.actual = 0xffffffff;
        AOSSInitCrc32Table(0, s_crcTable);
        for (crcIndex = 0; crcIndex < (s32)dataLength; crcIndex++) {
            integrity.actual = (integrity.actual >> 8) ^ s_crcTable[(integrity.actual ^ decryptedData[crcIndex]) & 0xff];
        }
        if (((integrity.actual ^ 0xffffffff) & 0xff) != integrity.expected) {
            s_errorCode = 0x12;
            AOSSi_Free(schedule.bytes);
            result = -1;
        } else {
            AOSSi_Free(schedule.bytes);
            result = 0;
        }
    }

    if (result < 0) {
        AOSSi_Free(decryptedData);
        return s_errorCode == 2 ? 100 : 200;
    }

    memcpy(encrypted, decryptedData, dataLength);
    message->outputLength = SOHtoNs(dataLength);
    AOSSi_Free(decryptedData);
    return 0;
}

int AOSSCheckAccessPointName(u16 command, const u8* manufacturerAddress) {
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

int AOSSParseNetworkSettings(const AOSSOptionRecord* packet, u8* settings) {
    const u8* packetBytes = (const u8*)packet;
    const AOSSOptionRecord* record;
    s32 length;
    const u8* valueBytes;
    s32 index;
    u32 value;
    u16 nextOffset;

    memset(settings, 0, 0x104);
    record = packet;
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
            if ((s32)(u16)SONtoHs(record->data[0]) <= 0) {
                return -2;
            }
            break;
        case 5:
            value = 0;
            valueBytes = record->data;
            for (index = 0; index < length; index++) {
                value <<= 8;
                value += *valueBytes++;
            }
            value = SONtoHl(value);
            s_runtime.ipAddress = value;
            break;
        case 6:
            value = 0;
            valueBytes = record->data;
            for (index = 0; index < length; index++) {
                value <<= 8;
                value += *valueBytes++;
            }
            value = SONtoHl(value);
            s_runtime.subnetMask = value;
            break;
        default:
            return -1;
        }

        nextOffset = record->nextOffset;
        if (nextOffset == 0) {
            break;
        }
        record = (const AOSSOptionRecord*)(packetBytes + SONtoHs(nextOffset));
    }
    return 0;
}

int AOSSParseWepConfig(const AOSSOptionRecord* packet, AOSSStoredConfig* config) {
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

int AOSSParsePskConfig(const AOSSOptionRecord* packet, AOSSStoredConfig* config) {
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

#pragma push
#pragma optimization_level 3
int AOSSApplyAuthOptions(int state, const AOSSReplyOption* response, int responseLength, void* config, void* networkData) {
    u32 flags = 0;
    const AOSSReplyOption* responseRecord;
    const u8* responseTypes;
    AOSSConfigRecord* configRecord;
    AOSSStoredConfig* wep40Config;
    AOSSStoredConfig* wep104Config;
    AOSSStoredConfig* tkipConfig;
    AOSSStoredConfig* aesConfig;
    u8* networkSettings;
    u32 length;
    int result;
    s32 optionRemaining;

    if (responseLength <= 0) {
        return -2;
    }

    responseTypes = s_responseTypeByState;
    responseRecord = response;
    for (;;) {
        if (responseRecord->fields.type == responseTypes[state]) {
            break;
        }
        length = SONtoHs(responseRecord->fields.length) + 4;
        responseLength -= length;
        responseRecord = (const AOSSReplyOption*)&responseRecord->bytes[length];
        if (responseLength <= 0) {
            return -4;
        }
    }

    length = responseRecord->fields.length;
    responseRecord = (const AOSSReplyOption*)&responseRecord->bytes[4];
    optionRemaining = SONtoHs((u16)length);
    configRecord = &((AOSSConfigData*)config)->records[state];
    wep40Config = (AOSSStoredConfig*)&configRecord->reserved00[8];
    networkSettings = ((AOSSNetworkBufferRecord*)networkData)[state + 3].bytes;
    wep104Config = (AOSSStoredConfig*)&configRecord->reserved138[0];
    tkipConfig = (AOSSStoredConfig*)&configRecord->reserved268[0];
    aesConfig = (AOSSStoredConfig*)&configRecord->reserved2d8[0];

    do {
        switch (responseRecord->fields.type) {
        case 3:
            result = AOSSParseWepConfig((const AOSSOptionRecord*)responseRecord, wep40Config);
            flags |= 1;
            break;
        case 4:
            result = AOSSParseWepConfig((const AOSSOptionRecord*)responseRecord, wep104Config);
            flags |= 2;
            break;
        case 5:
            result = AOSSParsePskConfig((const AOSSOptionRecord*)responseRecord, tkipConfig);
            flags |= 4;
            break;
        case 6:
            result = AOSSParsePskConfig((const AOSSOptionRecord*)responseRecord, aesConfig);
            flags |= 8;
            break;
        case 10:
            length = SONtoHs(responseRecord->fields.payload.network.networkLength);
            if ((s32)length <= 0) {
                result = -1;
            } else if (responseRecord->fields.payload.network.networkType != 0x70) {
                result = -1;
            } else {
                memcpy(networkSettings, responseRecord->fields.payload.network.networkData, length);
                result = 0;
            }
            break;
        default:
            result = -3;
            break;
        }

        if (result != 0) {
            return result;
        }

        length = SONtoHs(responseRecord->fields.length) + 4;
        optionRemaining -= length;
        responseRecord = (const AOSSReplyOption*)&responseRecord->bytes[length];
    } while (optionRemaining > 0);

    s_runtime.state |= flags;
    return 0;
}
#pragma pop

int AOSSSendDiscoveryRequest(void* packet, AOSSRequestRecords* request, int socket) {
    u8* responsePayload;
    u8 accessPointName[8];
    AOSSSocketAddress destination;
    AOSSRequestBuffer* requestRecord;
    AOSSDiscoveryPacket* response;
    s16 recordLength;
    s16 requestLength;
    int encryptionResult;
    int result;

    response = (AOSSDiscoveryPacket*)s_responseBuffer;
    memset(response, 0, 0x5dc);
    requestRecord = (AOSSRequestBuffer*)AOSSi_Alloc(0x210);
    if (requestRecord == 0) {
        s_errorCode = 2;
        return -1;
    }

    memset(requestRecord, 0, 0x210);
    responsePayload = response->payload;
    memcpy(s_accessPointName, &request->records[0], 8);
    memcpy(accessPointName, s_accessPointName, 8);
    recordLength = AOSSBuildInterfaceOption(&requestRecord->record);
    if (recordLength < 0) {
        s_errorCode = 3;
        if (requestRecord != 0) {
            AOSSi_Free(requestRecord);
        }
        result = -1;
    } else {
        requestRecord->type = 0;
        requestRecord->length = SOHtoNs(recordLength);
        requestLength = recordLength + 4;
        memcpy(responsePayload, requestRecord, requestLength);
        encryptionResult = AOSSXorBufferWithKey(accessPointName, 8, s_manufacturer, 6);
        if (encryptionResult != 0) {
            s_errorCode = 2;
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
        SOSendTo(socket, response, (s16)(requestLength + 0x18), 0, &destination);
        if (requestRecord != 0) {
            AOSSi_Free(requestRecord);
        }
        result = 0;
    }
    return result;
}

int AOSSSendHelloRequest(void* packet, void* request, int socket) {
    AOSSHelloPayload* payload;
    u32 checksum;
    AOSSRequestRecords* requestRecords = (AOSSRequestRecords*)request;
    u8 accessPointName[8];
    AOSSHelloRecord hello;
    AOSSSocketAddress destination;
    AOSSKeySchedule schedule;
    int sequence;
    u32 crc;
    AOSSHelloPacket* response = (AOSSHelloPacket*)s_responseBuffer;
    u16 nonce;
    u32 stateLength;
    u32 index;
    u32 firstIndex;
    u32 firstByte;
    u32 secondIndex;
    u8* state;
    u32 i;
    const u8* input;
    u8 value;
    u8 swap;
    s16 responseLength;
    s16 sendLength;
    int encryptionResult;

    checksum = 0;
    sequence = 0;
    memset(&hello, 0, sizeof(hello));
    memset(response, 0, 0x5dc);
    payload = &response->payload;
    hello.data.fields.type = 2;
    hello.data.fields.reserved01 = 0;
    hello.data.fields.length = SOHtoNs(4);
    hello.data.fields.supportedModes = s_runtime.flags;
    hello.data.fields.supportedModes = SOHtoNl(hello.data.fields.supportedModes);
    responseLength = 8;

    if ((s32)s_connectionState == 1) {
        sequence = 1;
        crc = 0xffffffff;
        AOSSInitCrc32Table(0, s_crcTable);
        index = 0;
        while (index < 8) {
            crc = (crc >> 8) ^ s_crcTable[(crc ^ hello.data.bytes[index++]) & 0xff];
        }
        checksum = (crc ^ 0xffffffff) & 0xff;

        schedule.bytes = (u8*)AOSSi_Alloc(8);
        if (schedule.bytes != 0) {
            nonce = (u16)rand();
            memcpy(&payload->encrypted.key.nonce, &nonce, 2);
            memcpy(s_packetState.key.nonce, payload->encrypted.key.nonceBytes, 2);
            memcpy(s_packetState.key.address, s_accessPointName, 8);
            AOSSInitKeySchedule(&schedule, (const u8*)&s_packetState.key, sizeof(s_packetState.key), 8);
            input = hello.data.bytes;
            for (i = 0; i < 8; i++) {
                state = schedule.bytes;
                firstIndex = (schedule.i + 1) % schedule.length & 0xff;
                firstByte = state[firstIndex];
                secondIndex = (firstByte + schedule.j) % schedule.length & 0xff;
                swap = state[secondIndex];
                stateLength = firstByte + swap;
                schedule.i = firstIndex;
                schedule.j = secondIndex;
                state[secondIndex] = (u8)firstByte;
                state[firstIndex] = swap;
                value = state[stateLength % schedule.length];
                payload->bytes[i + 4] = value ^ *input++;
            }
            AOSSi_Free(schedule.bytes);
        }
        payload->encrypted.length = SOHtoNs(8);
        responseLength = 0x0c;
    } else {
        memcpy(payload->bytes, &hello, 8);
    }

    memcpy(accessPointName, &requestRecords->records[1], 8);
    encryptionResult = AOSSXorBufferWithKey(accessPointName, 8, s_manufacturer, 6);
    if (encryptionResult != 0) {
        s_errorCode = 2;
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
    sendLength = (s16)(responseLength + 0x18);
    memset(&destination, 0, sizeof(destination));
    destination.family = 2;
    destination.port = SOHtoNs(0x5790);
    destination.address = SOHtoNl(s_runtime.ipAddress);
    if ((s8)s_runtime.active == 0) {
        destination.address = 0xffffffff;
    }
    destination.length = 8;
    SOSendTo(socket, response, sendLength, 0, &destination);
    return 0;
}

s16 AOSSBuildInterfaceOption(void* buffer) {
    AOSSOptionRecord* record = (AOSSOptionRecord*)buffer;
    u32 optionValue;
    s16 dataLength;

    record->type = s_runtime.interfaceType;
    record->reserved01 = 1;
    dataLength = (s16)s_runtime.configLength;
    memcpy(record->data, s_runtime.config, dataLength);
    record->length = SOHtoNs(dataLength);
    dataLength = (s16)(dataLength + 6);
    dataLength = (s16)(((s32)((u32)((s32)dataLength + 1) >> 31) +
                        ((s32)dataLength + 1)) & ~1u);
    record->nextOffset = SOHtoNs(dataLength);
    record = (AOSSOptionRecord*)((u8*)record + dataLength);
    record->type = 0x60;
    record->reserved01 = 0;
    record->nextOffset = SOHtoNs(0);
    optionValue = SOHtoNl(0x0e);
    memcpy(record->data, &optionValue, sizeof(optionValue));
    record->length = SOHtoNs(4);
    return (s16)(dataLength + 10);
}

void AOSSInitKeySchedule(AOSSKeySchedule* schedule, const u8* key, u32 keyLength, u32 stateLength) {
    u32 index = 0;
    u32 keyIndex;
    u32 swapIndex;
    u8 value;
    u8* state;

    schedule->j = 0;
    state = schedule->bytes;
    schedule->i = 0;
    schedule->length = stateLength;
    for (index = 0; index < stateLength; index++) {
        state[index] = (u8)index;
    }
    index = 0;
    swapIndex = 0;
    keyIndex = 0;
    for (; index < stateLength; index++) {
        value = state[index];
        swapIndex = (value + swapIndex + key[keyIndex]) % schedule->length;
        {
            u8 swapped = state[swapIndex];
            state[swapIndex] = value;
            state[index] = swapped;
        }
        keyIndex++;
        if (keyIndex >= keyLength) {
            keyIndex = 0;
        }
    }
}

void AOSSInitCrc32Table(u32 seed, u32* table) {
    u32 index;
    u32 value;

    for (index = 0; index < 0x100; index++) {
        value = index;
        {
            u32 bit;
            for (bit = 0; bit < 8; bit++) {
                if ((value & 1) != 0) value = (value >> 1) ^ 0xedb88320;
                else value >>= 1;
            }
        }
        *table++ = value;
    }
}

int AOSSXorBufferWithKey(void* packet, s32 length, char* key, int keyLength) {
    u8* temporaryHalf;
    s32 halfLength = length / 2;
    u8* packetHalf;
    s32 round;
    u8* keyMask;
    u8* temporary;
    s32 keyIndex;
    s32 index;
    int result = -1;
    u8* packetBytes;
    u8* mask;
    u8* output;

    keyMask = (u8*)AOSSi_Alloc(halfLength);
    if (keyMask == 0) {
        return -1;
    }

    temporary = (u8*)AOSSi_Alloc(length);
    if (temporary == 0) {
        AOSSi_Free(keyMask);
        return -1;
    }

    packetBytes = (u8*)packet;
    packetHalf = packetBytes + halfLength;
    temporaryHalf = temporary + halfLength;
    for (round = 0; round < 2; round++) {
        keyIndex = round % keyLength;
        for (index = 0; index < halfLength; index++) {
            mask = &keyMask[index];
            *mask = (u8)index;
            *mask = *mask ^ (u8)key[keyIndex];
            keyIndex++;
            if (keyIndex >= keyLength) {
                keyIndex = 0;
            }
        }

        for (index = 0; index < halfLength; index++) {
            mask = &keyMask[index];
            output = &packetHalf[index];
            *output = *output ^ *mask;
        }

        memcpy(temporary, packetHalf, halfLength);
        memcpy(temporaryHalf, packetBytes, halfLength);
        memcpy(packetBytes, temporary, length);
    }

    AOSSi_Free(keyMask);
    AOSSi_Free(temporary);
    result = 0;
    return result;
}

int AOSSConnectAndAwaitHost(void* settings, void* config) {
    s32 connectionAttempts = 0;
    u32 ticksPerMillisecond;

    if (AOSSi_WLANConnect(settings, config) != 0) {
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
                *s_accessPointConfig = 0;
                break;
            }

            ticksPerMillisecond = (__mulhwu(0x10624dd3, __OSBusClock >> 2) >> 6);
            OSSleepTicks((OSTime)(ticksPerMillisecond * 100));
        }

    } else {
        return -1;
    }

    return 0;
}
