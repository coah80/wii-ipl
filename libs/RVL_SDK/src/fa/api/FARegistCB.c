#include <revolution/fa/types.h>

typedef struct FA_MEDIA_CALLBACKS {
    FAInsertCallback sd_insert;
    FAEjectCallback sd_eject;
    FAInsertCallback usb_insert;
    FAEjectCallback usb_eject;
    u32 flags;
} FA_MEDIA_CALLBACKS;

FA_MEDIA_CALLBACKS gMediaInOutCallback;
extern s32 pfd_sddrv_registar_callback(FAInsertCallback insert, FAEjectCallback eject);
extern s32 pfd_mscdrv_registar_callback(FAInsertCallback insert, FAEjectCallback eject);
void FANotifySDInsert(s8 drive);
void FANotifySDEject(s8 drive);
void FANotifyUSBInsert(s8 drive);
void FANotifyUSBEject(s8 drive);

FAError FARegistCB(s32 device, FAInsertCallback insert, FAEjectCallback eject) {
    s32 error;
    switch (device) {
        case 0:
            gMediaInOutCallback.sd_insert = insert;
            gMediaInOutCallback.sd_eject = eject;
            error = pfd_sddrv_registar_callback(FANotifySDInsert, FANotifySDEject);
            break;
        case 1:
            gMediaInOutCallback.usb_insert = insert;
            gMediaInOutCallback.usb_eject = eject;
            error = pfd_mscdrv_registar_callback(FANotifyUSBInsert, FANotifyUSBEject);
            break;
        default:
            return -2;
    }
    if (error != 0) {
        return -1;
    }
    return 0;
}

void FANotifySDInsert(s8 drive) {
    if (gMediaInOutCallback.sd_insert) {
        gMediaInOutCallback.sd_insert(drive);
    }
}

void FANotifySDEject(s8 drive) {
    if (gMediaInOutCallback.sd_eject) {
        gMediaInOutCallback.sd_eject(drive);
    }
}

void FANotifyUSBInsert(s8 drive) {
    if (gMediaInOutCallback.usb_insert) {
        gMediaInOutCallback.usb_insert(drive);
    }
}

void FANotifyUSBEject(s8 drive) {
    if (gMediaInOutCallback.usb_eject) {
        gMediaInOutCallback.usb_eject(drive);
    }
}
