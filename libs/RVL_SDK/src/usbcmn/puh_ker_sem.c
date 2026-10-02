#include <private/usbcmn/puh_ker_sem.h>

#include <revolution/os.h>

#define MAX_PUH_SEM 12

static struct {
    struct {
        OSSemaphore* sem;  // 0x00
        u32 initCount;
        u32 flags;
    } entries[MAX_PUH_SEM];  // 0x00
    u32 usedCount;
    OSSemaphore* lockSem;
    u8 pad[0x0C];
} st_uhs_ker_sem_mng;

static OSSemaphore st_uhf_ker_sem[MAX_PUH_SEM];

static s32 st_uhs_ker_sem_status;

static int uhf_ker_sem_inline_0() {
    if (st_uhs_ker_sem_status != 1 || st_uhs_ker_sem_mng.lockSem == 0) {
        return -1;
    } else {
        OSWaitSemaphore(st_uhs_ker_sem_mng.lockSem);
        return 0;
    }
}

static void uhf_ker_sem_inline_1() {
    if (st_uhs_ker_sem_status == 1 && st_uhs_ker_sem_mng.lockSem != 0) {
        OSSignalSemaphore(st_uhs_ker_sem_mng.lockSem);
    }
}

s32 uhf_ker_create_sem(u32 initCount, int flags) {
    int i, k;

    if (initCount != 0 && initCount != 1) {
        return -5;
    }
    if (flags != 0) {
        return -5;
    }

    if (uhf_ker_sem_inline_0() != 0) {
        return -5;
    }

    if (st_uhs_ker_sem_mng.usedCount == 12) {
        uhf_ker_sem_inline_1();
        return -24;
    }

    for (i = 0; i < MAX_PUH_SEM; i++) {
        if (st_uhs_ker_sem_mng.entries[i].sem == 0) {
            OSSemaphore* sem;

            OSInitSemaphore(&st_uhf_ker_sem[i], 1);
            sem = &st_uhf_ker_sem[i];

            for (k = (int)(1 - initCount); k > 0; k--) {
                OSWaitSemaphore((OSSemaphore*)sem);
            }

            st_uhs_ker_sem_mng.entries[i].sem = sem;
            st_uhs_ker_sem_mng.entries[i].initCount = initCount;
            st_uhs_ker_sem_mng.entries[i].flags = flags;
            st_uhs_ker_sem_mng.usedCount++;

            uhf_ker_sem_inline_1();

            return i + 1;
        }
    }

    uhf_ker_sem_inline_1();

    return -24;
}

s32 uhf_ker_delete_sem(int sem) {
    int i;

    if (sem == 0 || sem > MAX_PUH_SEM) {
        return -5;
    }

    if (uhf_ker_sem_inline_0() != 0) {
        return -5;
    }

    if (st_uhs_ker_sem_mng.entries[sem - 1].sem == NULL) {
        uhf_ker_sem_inline_1();
        return -5;
    }

    st_uhs_ker_sem_mng.entries[sem - 1].sem = NULL;
    st_uhs_ker_sem_mng.entries[sem - 1].initCount = 0;
    st_uhs_ker_sem_mng.entries[sem - 1].flags = 0;
    st_uhs_ker_sem_mng.usedCount--;

    uhf_ker_sem_inline_1();

    return 0;
}

s32 uhf_ker_get_sem(int sem) {
    if (sem == 0 || sem > MAX_PUH_SEM) {
        return -5;
    }

    if (st_uhs_ker_sem_mng.entries[sem - 1].sem == NULL) {
        return -5;
    }

    OSWaitSemaphore(st_uhs_ker_sem_mng.entries[sem - 1].sem);

    return 0;
}
