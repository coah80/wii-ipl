#include <revolution/ncd.h>
#include <revolution/os.h>
#include <revolution/soex.h>

#include <private/ios.h>
#include <private/nwc24/NWC24Schedule.h>
#include <private/os/OSTime.h>

#include <string.h>

typedef struct SOSysWork {
    SOAlloc allocFunc;
    SOFree freeFunc;
    s32 rmState;
    s32 rmFd;
    u32 unk10;
    s32 allocCount;
} SOSysWork;

enum {
    SO_INTERNAL_STATE_TERMINATED = 0,
    SO_INTERNAL_STATE_READY = 1,
    SO_INTERNAL_STATE_ACTIVE = 2,
};

enum {
    SO_INTERNAL_RM_STATE_OPENED = 0,
    SO_INTERNAL_RM_STATE_WORKING = -1,
    SO_INTERNAL_RM_STATE_CLOSED = -2,
};

enum {
    SO_SUCCESS = 0,
    SO_EFATAL = (s32)0x80000000,
    SO_EAGAIN = -6,
    SO_EALREADY = -7,
    SO_EBUSY = -10,
    SO_EINPROGRESS = -26,
    SO_EINVAL = -28,
    SO_ENETRESET = -39,
    SO_ENOENT = -45,
    SO_ENOLINK = -48,
    SO_ENOMEM = -49,
    SO_ETIMEDOUT = -76,
};

enum {
    SO_ERR_LINK_UP_TIMEOUT = -121,
};

enum {
    NCD_LINKSTATUS_WORKING = 1,
    NCD_LINKSTATUS_NONE = 2,
};

enum {
    NET_SO_SOCKET = 0xF,
};

typedef struct NETSoSocket {
    int af;
    int type;
    int protocol;
} NETSoSocket;

static s32 soRegistered;
static s32 soError;
static u8 soState;
static SOSysWork soWork;

const char* __SOVersion =
    "<< RVL_SDK - SO \trelease build: Dec 12 2008 03:06:16 (0x4199_60831) >>";
static int soBufAddrCheck = 1;
static char NET_RM_SOCK[] = "/dev/net/ip/top";

extern OSTime __OSGetSystemTime(void);

static int SOStartupErr(s32 errNwc24, s32 exErr);
void* SOiAlloc(u32 name, s32 size);
void SOiFree(u32 name, void* ptr, s32 size);
int SOiPrepare(const char* funcName, s32* pRmId);
int SOiConclude(const char* funcName, int result);
int SOiWaitForDHCPEx(int timeout);
int SOCleanup(void);
int SOiConcludeTempRm(const char* funcName, int result, int isTempRm);

int SOInit(SOLibraryConfig* config) {
    int result = 0;
    int enabled;
    void* ptr;
    OSThread* cur;
    SOSysWork* work;

    enabled = OSDisableInterrupts();
    if (!soRegistered) {
        OSRegisterVersion(__SOVersion);
        soRegistered = 1;
    }
    if (!((int)soState == 0 || (int)soState < 0 || (int)soState >= 3)) {
        result = -7;
        goto finish;
    }
    if (config == NULL || config->alloc == NULL || config->free == NULL) {
        result = -28;
    } else {
        memset(&soWork, 0, sizeof(soWork));
        soWork.allocFunc = config->alloc;
        work = &soWork;
        work->freeFunc = config->free;
        work->allocCount = 0;
        work->rmState = -2;
        work->rmFd = -1;
        ptr = SOiAlloc(0xB, 0x460);
        soWork.unk10 = (u32)ptr;
        if (ptr == NULL) {
            result = -49;
        } else {
            soState = 1;
        }
    }
finish:
    cur = OSGetCurrentThread();
    if (cur != NULL)
        cur->error = result;
    else
        soError = result;
    OSRestoreInterrupts(enabled);
    return result;
}

int SOFinish(void) {
  int result = 0;
  int enabled = OSDisableInterrupts();
  OSThread* cur;

  switch (soState) {
  case SO_INTERNAL_STATE_TERMINATED:
    result = SO_EALREADY;
    break;
  case SO_INTERNAL_STATE_READY:
    if (soWork.rmState > SO_INTERNAL_RM_STATE_CLOSED) {
      result = SO_EBUSY;
      break;
    } else if (soWork.allocCount > 1) {
      result = SO_EAGAIN;
      break;
    }
    soState = SO_INTERNAL_STATE_TERMINATED;
    if (soWork.unk10 != 0 && soWork.freeFunc) {
      soWork.allocCount--;
      soWork.freeFunc(0x0b, (void*)soWork.unk10, 0x460);
    }
    break;
  case SO_INTERNAL_STATE_ACTIVE:
    result = SO_EINPROGRESS;
    break;
  }
  cur = OSGetCurrentThread();
  if (cur)
    cur->error = result;
  else
    soError = result;
  OSRestoreInterrupts(enabled);
  return result;
}

int SOStartup(void) { return SOStartupEx(0x927c0); }

static int SOStartupErr(s32 errNwc24, s32 exErr) {
  s32 result = -0x1c;
  switch (errNwc24) {
  case 0:
    result = 0;
    break;
  case -0x16:
  case -0xd:
    result = -0x30;
    break;
  case -0x21:
  case -2:
    result = exErr;
    break;
  case -1:
    result = -0x80000000;
    break;
  case -0x1d:
    result = -0x1a;
    break;
  }
  return result;
}

int SOStartupEx(int timeout) {
  int result;
  int enabled;
  s32 exErr;
  s64 limitTime;
  s32 linkupRetryCount;

  limitTime = 0;
  if (timeout != 0)
    limitTime = __OSGetSystemTime() + ((timeout) * ((__OSBusClock / 4) / 1000));

  linkupRetryCount = 4;

begin_startup:
  result = SO_SUCCESS;

  enabled = OSDisableInterrupts();

  switch (soState) {
  case SO_INTERNAL_STATE_TERMINATED:
  default:
    result = SO_ENETRESET;
    break;
  case SO_INTERNAL_STATE_ACTIVE:
    result = SO_EALREADY;
    break;
  case SO_INTERNAL_STATE_READY:
    if (soWork.rmState > SO_INTERNAL_RM_STATE_CLOSED) {
      result = SO_EBUSY;
      break;
    } else if (!OSGetCurrentThread()) {
      result = SO_EFATAL;
      break;
    } else {
      int resultNCD;

      soWork.rmState = SO_INTERNAL_RM_STATE_WORKING;
      (void)OSRestoreInterrupts(enabled);

      while (1) {
        resultNCD = NCDGetLinkStatus();
        if (resultNCD != NCD_RESULT_INPROGRESS &&
            resultNCD != NCD_LINKSTATUS_WORKING)
          break;
        OSSleepTicks((((s64)100) * ((__OSBusClock / 4) / 1000)));
        if (limitTime != 0 && limitTime < __OSGetSystemTime()) {
          if (resultNCD == NCD_LINKSTATUS_WORKING)
            result = SO_ERR_LINK_UP_TIMEOUT;
          else
            result = SO_EFATAL;
          goto change_state;
        }
      }
      if (resultNCD < NCD_RESULT_SUCCESS) {
        result = SO_EFATAL;
        goto change_state;
      } else if (resultNCD == NCD_LINKSTATUS_NONE) {
        result = SO_ENOENT;
        goto change_state;
      }

      while (1) {
        soWork.rmFd = IOS_Open(NET_RM_SOCK, 0);
        if (soWork.rmFd != -6)
          break;
        OSSleepTicks((((s64)100) * ((__OSBusClock / 4) / 1000)));
        if (limitTime != 0 && limitTime < __OSGetSystemTime()) {
          result = SO_EFATAL;
          goto change_state;
        }
      };

      if (soWork.rmFd < 0) {
        result = SO_EFATAL;
        goto change_state;
      } else {
        s32 errNwc24;

        result = SO_SUCCESS;
        exErr = SO_SUCCESS;

        while (1) {
          errNwc24 = NWC24iStartupSocket(&exErr);
          if (errNwc24 != NWC24_ERR_INPROGRESS)
            break;
          OSSleepTicks((((s64)100) * ((__OSBusClock / 4) / 1000)));
          if (limitTime != 0 && limitTime < __OSGetSystemTime()) {
            result = SO_EFATAL;
            break;
          }
        }
        if (result == SO_SUCCESS)
          result = SOStartupErr(errNwc24, exErr);
        if (result != SO_SUCCESS) {
          if (IOS_Close(soWork.rmFd) < 0) {
            result = SO_EFATAL;
            goto change_state;
          } else {
            soWork.rmFd = -1;
          }
        }
      }

    change_state:
      enabled = OSDisableInterrupts();
      if (result == SO_SUCCESS) {
        soState = SO_INTERNAL_STATE_ACTIVE;
        soWork.rmState = SO_INTERNAL_RM_STATE_OPENED;
      } else {
        soState = 1;
        if (result != SO_EFATAL)
          soWork.rmState = SO_INTERNAL_RM_STATE_CLOSED;
      }
    }
    break;
  }

  {
    OSThread* cur = OSGetCurrentThread();
    if (cur)
      cur->error = result;
    else
      soError = result;
  }

  (void)OSRestoreInterrupts(enabled);

  if (result == 0) {
    s64 dhcpTimeOutTicks;

    if (limitTime != 0) {
      dhcpTimeOutTicks = limitTime - __OSGetSystemTime();
    } else {
      dhcpTimeOutTicks = 0;
    }
    if (limitTime != 0 && dhcpTimeOutTicks <= 0) {
      result = -76;
    } else {
      result = SOiWaitForDHCPEx(
          (int)((dhcpTimeOutTicks) / ((__OSBusClock / 4) / 1000)));
    }

    if (result != 0) {
      (void)SOCleanup();
    }
  }

  {
    OSThread* cur = OSGetCurrentThread();
    if (cur)
      cur->error = result;
    else
      soError = result;
  }

  if (result == -112) {
    linkupRetryCount--;
    if (linkupRetryCount >= 0) {
      goto begin_startup;
    }
  }

  return result;
}

int SOCleanup(void) {
  int result = SO_SUCCESS;
  int enabled = OSDisableInterrupts();
  s32 exErr = SO_SUCCESS;
  int errNwc24;

  switch (soState) {
  case SO_INTERNAL_STATE_TERMINATED:
  default:
    result = SO_ENETRESET;
    break;
  case SO_INTERNAL_STATE_READY:
    result = SO_EALREADY;
    break;
  case SO_INTERNAL_STATE_ACTIVE:
    if (soWork.rmState < SO_INTERNAL_RM_STATE_OPENED) {
      result = SO_EBUSY;
      break;
    } else if (!OSGetCurrentThread()) {
      result = SO_EFATAL;
      break;
    } else {
      soWork.rmState = SO_INTERNAL_RM_STATE_WORKING;
      (void)OSRestoreInterrupts(enabled);

      errNwc24 = NWC24iCleanupSocket(&exErr);
      result = SOStartupErr(errNwc24, exErr);
      if (result != SO_SUCCESS) {
      } else {
        if (IOS_Close(soWork.rmFd) < 0)
          result = SO_EFATAL;
        else
          soWork.rmFd = -1;
      }

      enabled = OSDisableInterrupts();
      if (result == SO_SUCCESS) {
        soState = SO_INTERNAL_STATE_READY;
        soWork.rmState = SO_INTERNAL_RM_STATE_CLOSED;
      } else {
        if (result != SO_EFATAL) {
          soState = SO_INTERNAL_STATE_ACTIVE;
          soWork.rmState = SO_INTERNAL_RM_STATE_OPENED;
        }
      }
    }
    break;
  }

  {
    OSThread* cur = OSGetCurrentThread();
    if (cur)
      cur->error = result;
    else
      soError = result;
  }

  OSRestoreInterrupts(enabled);
  return result;
}

SOSysWork* SOiGetSysWork(void) { return &soWork; }

int SOiIsBufferAddrCheck(void) { return soBufAddrCheck; }

int SOiIsInitialized(void) {
  int result = 0;
  int enabled = OSDisableInterrupts();
  switch (soState) {
  case SO_INTERNAL_STATE_READY:
  case SO_INTERNAL_STATE_ACTIVE:
    result = 1;
    break;
  }
  OSRestoreInterrupts(enabled);
  return result;
}

void* SOiAlloc(u32 name, s32 size) {
  if (size > 0 && soWork.allocFunc) {
    void* ptr = soWork.allocFunc(name, size);
    if (ptr) {
      soWork.allocCount++;
      if (SOiIsBufferAddrCheck() && !(((u32)ptr & 0x1fffffff) >= 0x10000000 &&
                                      ((u32)ptr & 0x1fffffff) < 0x18000000)) {
        if (ptr != NULL && soWork.freeFunc != NULL) {
          soWork.allocCount--;
          soWork.freeFunc(name, ptr, size);
        }
        ptr = NULL;
      }
    }
    return ptr;
  }
  return NULL;
}

void SOiFree(u32 name, void* ptr, s32 size) {
  if ((ptr != NULL) && (soWork.freeFunc != NULL)) {
    soWork.allocCount--;
    soWork.freeFunc(name, ptr, size);
  }
}

int SOiPrepare(const char*, s32* pRmId) {
  int result = SO_SUCCESS;
  int enabled = OSDisableInterrupts();

  switch (soState) {
  case SO_INTERNAL_STATE_TERMINATED:
    result = SO_ENETRESET;
    break;
  case SO_INTERNAL_STATE_READY:
  default:
    result = SO_EINVAL;
    break;
  case SO_INTERNAL_STATE_ACTIVE:
    if (soWork.rmState < SO_INTERNAL_RM_STATE_OPENED) {
      result = SO_EBUSY;
      break;
    } else if (!OSGetCurrentThread()) {
      result = SO_EFATAL;
      break;
    }
    *pRmId = soWork.rmFd;
    break;
  }

  if (result != SO_SUCCESS) {
    OSThread* cur = OSGetCurrentThread();
    if (cur)
      cur->error = result;
    else
      soError = result;
  }
  (void)OSRestoreInterrupts(enabled);
  return result;
}

int SOiConclude(const char*, int result) {
  int enabled = OSDisableInterrupts();
  OSThread* cur;

  cur = OSGetCurrentThread();
  if (cur)
    cur->error = result;
  else
    soError = result;
  (void)OSRestoreInterrupts(enabled);
  return result;
}

int SOiPrepareTempRm(const char* funcName, s32* pRmId, int* pIsTempRm) {
  int result = SO_SUCCESS;
  int enabled = OSDisableInterrupts();
  int errNwc24;

  switch (soState) {
  case SO_INTERNAL_STATE_TERMINATED:
    result = SO_ENETRESET;
    break;
  case SO_INTERNAL_STATE_READY:
  default:
    if (soWork.rmState > SO_INTERNAL_RM_STATE_CLOSED) {
      result = SO_EBUSY;
      break;
    } else if (!OSGetCurrentThread()) {
      result = SO_EFATAL;
      break;
    }
    soWork.rmState = SO_INTERNAL_RM_STATE_WORKING;
    (void)OSRestoreInterrupts(enabled);
    soWork.rmFd = IOS_Open(NET_RM_SOCK, 0);
    if (soWork.rmFd < 0) {
      enabled = OSDisableInterrupts();
      if (soWork.rmFd == -6) {
        result = SO_EINPROGRESS;
        soWork.rmState = SO_INTERNAL_RM_STATE_CLOSED;
      } else {
        result = SO_EFATAL;
      }
    } else {
      *pRmId = soWork.rmFd;
      if ((errNwc24 = NWC24iLockSocket()) == NWC24_OK) {
        s32 errNcd = NCDGetLinkStatus();
        switch (errNcd) {
        case 3:
        case 4:
        case 5:
          result = (int)IOS_Ioctl(soWork.rmFd, 0x1f, NULL, 0, NULL, 0);
          if (result == SO_SUCCESS) {
            *pIsTempRm = 1;
          } else {
            result = SOiConcludeTempRm(funcName, result, 1);
          }
          break;
        case -8:
          result = SOiConcludeTempRm(funcName, SO_EINPROGRESS, 1);
          break;
        case -1:
        case -2:
          result = SOiConcludeTempRm(funcName, SO_EFATAL, 1);
          break;
        default:
          result = SOiConcludeTempRm(funcName, SO_ENOLINK, 1);
        }
        enabled = OSDisableInterrupts();
      } else {
        switch (errNwc24) {
        case NWC24_ERR_INPROGRESS:
          result = SO_EINPROGRESS;
          break;
        case NWC24_ERR_FAILED:
          result = SO_ENETRESET;
          break;
        case NWC24_ERR_DONE:
          result = SO_ENOLINK;
          break;
        case NWC24_ERR_MUTEX:
        case NWC24_ERR_FATAL:
        default:
          result = SO_EFATAL;
          break;
        }
        if (IOS_Close(soWork.rmFd) < 0) {
          result = SO_EFATAL;
        }
        enabled = OSDisableInterrupts();
        if (result != SO_EFATAL) {
          soWork.rmFd = -1;
          soWork.rmState = SO_INTERNAL_RM_STATE_CLOSED;
        }
      }
    }
    break;
  case SO_INTERNAL_STATE_ACTIVE:
    if (soWork.rmState < SO_INTERNAL_RM_STATE_OPENED) {
      result = SO_EBUSY;
      break;
    } else if (!OSGetCurrentThread()) {
      result = SO_EFATAL;
      break;
    }
    *pIsTempRm = 0;
    *pRmId = soWork.rmFd;
    break;
  }

  if (result != SO_SUCCESS) {
    OSThread* cur = OSGetCurrentThread();
    if (cur)
      cur->error = result;
    else
      soError = result;
  }
  (void)OSRestoreInterrupts(enabled);
  return result;
}

int SOiConcludeTempRm(const char*, int result, int isTempRm) {
  int enabled;
  OSThread* cur;

  if (isTempRm == 1) {
    switch (NWC24iUnlockSocket()) {
    case NWC24_OK:
      break;
    case NWC24_ERR_INPROGRESS:
      result = SO_EINPROGRESS;
      break;
    case NWC24_ERR_FATAL:
    default:
      result = SO_EFATAL;
    }
    if (IOS_Close(soWork.rmFd) < 0) {
      result = SO_EFATAL;
    }
    enabled = OSDisableInterrupts();
    if (result != SO_EFATAL) {
      soWork.rmFd = -1;
      soWork.rmState = SO_INTERNAL_RM_STATE_CLOSED;
    }
  } else {
    enabled = OSDisableInterrupts();
  }
  cur = OSGetCurrentThread();
  if (cur)
    cur->error = result;
  else
    soError = result;
  (void)OSRestoreInterrupts(enabled);
  return result;
}

int SOiWaitForDHCPEx(int timeout) {
  int result = SO_SUCCESS;
  int gioResult;
  int ifError;
  int ifErrorSize;
  s64 limitTime;

  limitTime = 0;
  if (timeout != 0)
    limitTime = __OSGetSystemTime() + ((timeout) * ((__OSBusClock / 4) / 1000));

  while (1) {
    OSSleepTicks((((s64)10) * ((__OSBusClock / 4) / 1000)));

    ifErrorSize = sizeof(ifError);
    gioResult = SOGetInterfaceOpt(NULL, 0xfffe, 0x1003, &ifError, &ifErrorSize);
    if (gioResult != SO_SUCCESS) {
      result = gioResult;
      break;
    }
    if (gioResult == SO_SUCCESS && ifError != SO_SUCCESS) {
      result = ifError;
      break;
    }
    if (SOGetHostID() != 0)
      break;
    if (limitTime != 0 && limitTime < __OSGetSystemTime()) {
      result = SO_ETIMEDOUT;
      break;
    }
  }

  return result;
}

#pragma dont_inline on
int __SOCreateSocket(int pf, int type, int protocol) {
    int result;
    s32 rmId;
    NETSoSocket* soc;

    if ((result = SOiPrepare(0, &rmId)) == SO_SUCCESS) {
        if (pf == 0x17) {
            result = -5;
        } else {
            soc = (NETSoSocket*)SOiAlloc(0xC, 0x20);
            if (soc == NULL) {
                result = SO_ENOMEM;
            } else {
                soc->af = pf;
                soc->type = type;
                soc->protocol = protocol;
                result = IOS_Ioctl(rmId, NET_SO_SOCKET, soc, 0xC, NULL, 0);
                SOiFree(0xC, soc, 0x20);
            }
        }
        result = SOiConclude(0, result);
    }
    return result;
}

#pragma dont_inline reset
