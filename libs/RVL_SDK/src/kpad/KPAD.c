#include <math.h>
#include <string.h>
#include <revolution/kpad.h>
#include <revolution/mtx.h>
#include <revolution/os.h>

typedef struct KPADSampleFS {
    s16 accX;
    s16 accY;
    s16 accZ;
    s8 stickX;
    s8 stickY;
} KPADSampleFS;

typedef struct KPADSampleCL {
    u16 buttons;
    s16 lStickX;
    s16 lStickY;
    s16 rStickX;
    s16 rStickY;
    u8 triggerL;
    u8 triggerR;
} KPADSampleCL;

typedef struct KPADSample {
    u16 buttons;
    s16 accX;
    s16 accY;
    s16 accZ;
    DPDObject objects[WPAD_MAX_DPD_OBJECTS];
    u8 device;
    s8 error;
    union {
        KPADSampleFS fs;
        KPADSampleCL cl;
    } extension;
    u8 dataFormat;
} KPADSample;

typedef struct KPADDPDObject {
    f32 x;
    f32 y;
    union {
        u32 value;
        struct {
            u8 flags;
            u8 status;
        } bytes;
    } metadata;
} KPADDPDObject;

typedef struct KPADInside {
    KPADStatus status;
    f32 posParamX;
    f32 posParamY;
    f32 value8C;
    f32 value90;
    f32 value94;
    f32 value98;
    f32 value9C;
    f32 valueA0;
    f32 referenceDistance;
    f32 accelNormalX;
    f32 accelNormalY;
    f32 horizonTangentX;
    f32 horizonTangentY;
    f32 sensorBarCenterX;
    f32 sensorBarCenterY;
    f32 sensorBarScale;
    struct {
        KPADDPDObject objects[4];
        KPADDPDObject candidates[2];
    } dpdState;
    u16 dpdCount;
    u8 ringIndex;
    u8 ringCount;
    KPADSample ringData[16];
    f32 dpdObjectDistance;
    f32 dpdObjectDirectionX;
    f32 dpdObjectDirectionY;
    f32 dpdReferenceDistance;
    f32 dpdObjectScale;
    f32 accelerationX;
    f32 accelerationY;
    f32 accelerationZ;
    f32 dpdAxisX;
    f32 dpdAxisY;
    f32 horizonAxisX;
    f32 horizonAxisY;
    f32 horizonCircleX;
    f32 horizonCircleY;
    u16 horizonCircleCount;
    u8 value4CA;
    u16 repeatCount;
    u16 repeatCount2;
    u16 repeatDelay;
    u16 repeatInterval;
    u16 repeatCurrent;
    u16 repeatCurrent2;
    KPADCallback dpdCallback;
    f32 value4DC;
    f32 value4E0;
    f32 value4E4;
    f32 value4E8;
    f32 value4EC;
    f32 value4F0;
    f32 value4F4;
    f32 value4F8;
    f32 value4FC;
    f32 value500;
    f32 value504;
    f32 value508;
    f32 value50C;
    f32 value510;
    f32 value514;
    WPADSamplingCallback samplingCallback;
    u8 samplingInProgress;
    u8 flag51D;
    u8 flag51E;
    u8 flag51F;
    u8 dpdEnable;
    u8 dpdFormat;
    u8 dpdCallbackFired;
    u8 dpdCallbackPending;
    u8 sensorHeightPending;
    u8 sensorBarPosition;
    u16 freeStyleAccelRotation;
} KPADInside;

static KPADInside inside_kpads[4];
f32 initial_rotation_matrix[16];

static char kpadVersion[] = "<< RVL_SDK - KPAD \trelease build: Apr 20 2010 11:20:37 (0x4199_60831) >>";
const char* __KPADVersion = kpadVersion;
static u8 dpdModeTable[12] = {0, 1, 3, 2, 0, 4, 1, 5, 0, 7, 1, 8};

static f32 idist_org = 1.0f;
static Vec2 iaccXY_nrm_hori = {0.0f, -1.0f};
static Vec2 isec_nrm_hori = {1.0f, 0.0f};
f32 kp_obj_interval = 0.2f;
f32 kp_acc_horizon_pw = 0.05f;
f32 kp_ah_circle_radius = 0.07f;
f32 kp_ah_circle_pw = 0.06f;
u16 kp_ah_circle_ct = 100;
f32 kp_err_outside_frame = 0.05f;
f32 kp_err_dist_max = 3.0f;
f32 kp_err_dist_speed = 0.04f;
f32 kp_err_first_inpr = 0.9f;
f32 kp_err_next_inpr = 0.9f;
f32 kp_err_acc_inpr = 0.9f;
f32 kp_err_up_inpr = 0.7f;
f32 kp_err_near_pos = 0.1f;
static u32 kp_fs_fstick_min = 15;
static u32 kp_fs_fstick_max = 71;
static u32 kp_cl_stick_min = 60;
static u32 kp_cl_stick_max = 308;
static s32 kp_cl_trigger_min = 30;
static s32 kp_cl_trigger_max = 180;
static f32 kp_rm_acc_max = 3.4f;
static f32 kp_fs_acc_max = 2.1f;
static const WPADAccGravityUnit kp_default_gravity_core = {1, 1, 1};
static const WPADAccGravityUnit kp_default_gravity_fs = {1, 1, 1};
f32 sensor_bar_angle_degrees = 24.0f;

static Vec2 icenter_org;
u32 kp_stick_clamp_cross;
static Vec2 Vec2_0;
static f32 kp_dist_vv1;
f32 kp_err_dist_min;

static void KPADiSamplingCallback(s32 chan);
static void KPADiControlDpdCallback(s32 chan, s32 result);
static void calc_dpd_variable(KPADInside* kpad, s8 valid);

static void* get_ring_buffer_by_kpad1_style(s32 chan, void* buffer, s32 style) {
    KPADInside* kpad = &inside_kpads[chan];
    u32 i;
    s32 index;
    s32 latest;
    int enabled;
    s32 size;
    u32 type;
    switch (style) {
    case 0:
        size = 0x2A;
        goto process;
    case 1:
        size = 0x32;
        goto process;
    case 2:
        size = 0x36;
        goto process;
    default:
        return buffer;
    }
process:
    enabled = OSDisableInterrupts();
    index = kpad->ringIndex - 1;
    latest = WPADGetLatestIndexInBuf(chan);
    for (i = 0; i < 16; i++) {
        if (index < 0) {
            index = 15;
        }
        if (latest < 0) {
            latest = 15;
        }
        type = kpad->ringData[index].device;
        switch (type) {
        case 0:
        case 0xFB:
        case 0xFC:
        case 0xFF:
            type = 0;
            break;
        case 1:
            type = 1;
            break;
        case 2:
            type = 2;
            break;
        default:
            type = 0xFF;
            break;
        }
        if (type == style) {
            if (WPADGetStatus() != 3) {
                kpad->ringData[index].error = 0xFC;
            }
            memcpy((u8*)buffer + latest * size, &kpad->ringData[index], size);
        }
        index--;
        latest--;
    }
    OSRestoreInterrupts(enabled);
    return buffer;
}

void* KPADGetWPADRingBuffer(s32 chan) {
    static u8 status[0x2A0];
    return get_ring_buffer_by_kpad1_style(chan, status, 0);
}

void* KPADGetWPADFSRingBuffer(s32 chan) {
    static u8 status[0x320];
    return get_ring_buffer_by_kpad1_style(chan, status, 1);
}

void* KPADGetWPADCLRingBuffer(s32 chan) {
    static u8 status[0x360];
    return get_ring_buffer_by_kpad1_style(chan, status, 2);
}

void KPADSetBtnRepeat(s32 chan, f32 delay, f32 pulse) {
    KPADInside* kpad = &inside_kpads[chan];
    if (pulse) {
        kpad->repeatDelay = (u16)(0.5f + 200.0f * delay);
        kpad->repeatInterval = (u16)(0.5f + 200.0f * pulse);
    } else {
        kpad->repeatDelay = 40000;
        kpad->repeatInterval = 0;
    }
    kpad->repeatCount = 0;
    kpad->repeatCount2 = kpad->repeatDelay;
    kpad->repeatCurrent = 0;
    kpad->repeatCurrent2 = kpad->repeatDelay;
}

void KPADSetPosParam(s32 chan, f32 x, f32 y) {
    KPADInside* kpad = &inside_kpads[chan];
    kpad->posParamX = x;
    kpad->posParamY = y;
}

static void calc_button_repeat(KPADInside* kpad, u8 extension, s32 elapsed) {
    u16 count;
    u16 threshold;
    u16 current;
    u16 next;
    if (kpad->status.trig != 0 || kpad->status.release != 0) {
        kpad->repeatCount = 0;
        kpad->repeatCount2 = kpad->repeatDelay;
        if (kpad->status.trig != 0 && kpad->repeatInterval != 0) {
            kpad->status.hold |= 0x80000000;
        }
    } else if (kpad->status.hold != 0) {
        count = kpad->repeatCount + elapsed;
        kpad->repeatCount = count;
        if (count >= 40000) {
            kpad->repeatCount = count - 40000;
        }
        threshold = kpad->repeatCount2;
        current = kpad->repeatCount;
        if (current >= threshold) {
            kpad->status.hold |= 0x80000000;
            next = threshold + kpad->repeatInterval;
            kpad->repeatCount2 = next;
            if (current >= 20000) {
                kpad->repeatCount = current - 20000;
                kpad->repeatCount2 = next - 20000;
            }
        }
    }
    if (extension == 2) {
        if (kpad->status.ex_status.cl.trig != 0 || kpad->status.ex_status.cl.release != 0) {
            kpad->repeatCurrent = 0;
            kpad->repeatCurrent2 = kpad->repeatDelay;
            if (kpad->status.ex_status.cl.trig != 0 && kpad->repeatInterval != 0) {
                kpad->status.ex_status.cl.hold |= 0x80000000;
            }
        } else if (kpad->status.ex_status.cl.hold != 0) {
            count = kpad->repeatCurrent + elapsed;
            kpad->repeatCurrent = count;
            if (count >= 40000) {
                kpad->repeatCurrent = count - 40000;
            }
            threshold = kpad->repeatCurrent2;
            current = kpad->repeatCurrent;
            if (current >= threshold) {
                kpad->status.ex_status.cl.hold |= 0x80000000;
                next = threshold + kpad->repeatInterval;
                kpad->repeatCurrent2 = next;
                if (current >= 20000) {
                    kpad->repeatCurrent = current - 20000;
                    kpad->repeatCurrent2 = next - 20000;
                }
            }
        }
    }
}

static void calc_acc_horizon(KPADInside* kpad) {
    f32 accelX = kpad->accelerationX;
    f32 accelY = kpad->accelerationY;
    f32 magnitude = (f32)sqrt(accelX * accelX + accelY * accelY);
    f32 normalizedX;
    f32 normalizedY;
    f32 targetY;
    f32 targetX;
    f32 productX;
    f32 oldX;
    f32 oldY;
    f32 blend;
    f32 projectedX;
    f32 smoothing;
    f32 deltaX;
    f32 nextX;
    f32 nextY;
    f32 normalized;
    f32 unitX;
    f32 oldCircleX;
    f32 oldCircleY;
    f32 unitY;
    f32 circleX;
    f32 deltaCircleX;
    f32 circleY;
    f32 deltaCircleY;
    if (magnitude != 0.0f) {
        if (magnitude >= 2.0f) {
            return;
        }
        normalizedX = kpad->accelerationX / magnitude;
        normalizedY = kpad->accelerationY / magnitude;
        if (magnitude > 1.0f) {
            magnitude = 2.0f - magnitude;
        }
        targetY = kpad->accelNormalY;
        targetX = kpad->accelNormalX;
        productX = targetX * normalizedX;
        oldX = kpad->horizonAxisX;
        oldY = kpad->horizonAxisY;
        blend = magnitude * kp_acc_horizon_pw;
        projectedX = productX + targetY * normalizedY;
        smoothing = magnitude * blend;
        deltaX = smoothing * (projectedX - oldX);
        nextX = oldX + deltaX;
        nextY = oldY + smoothing * (((targetY * normalizedX) - (targetX * normalizedY)) - oldY);
        normalized = (f32)sqrt(nextX * nextX + nextY * nextY);
        if (normalized != 0.0f) {
            unitX = nextX / normalized;
            oldCircleX = kpad->horizonCircleX;
            oldCircleY = kpad->horizonCircleY;
            unitY = nextY / normalized;
            kpad->horizonAxisX = unitX;
            kpad->horizonAxisY = unitY;
            circleX = oldCircleX + kp_ah_circle_pw * (unitX - oldCircleX);
            deltaCircleX = unitX - circleX;
            kpad->horizonCircleX = circleX;
            circleY = oldCircleY + kp_ah_circle_pw * (unitY - oldCircleY);
            deltaCircleY = unitY - circleY;
            kpad->horizonCircleY = circleY;
            if (deltaCircleX * deltaCircleX + deltaCircleY * deltaCircleY == kpad->value50C) {
                if (kpad->horizonCircleCount != 0) {
                    kpad->horizonCircleCount--;
                }
            } else {
                kpad->horizonCircleCount = kp_ah_circle_ct;
            }
        }
    }
}

static void calc_acc_vertical(KPADInside* kpad) {
    f32 horizontal;
    f32 horizontalMagnitude;
    f32 accelZ;
    f32 blend;
    f32 magnitude;
    f32 normalizedX;
    f32 nextZ;
    f32 normalized;
    horizontalMagnitude = kpad->accelerationX * kpad->accelerationX + kpad->accelerationY * kpad->accelerationY;
    horizontal = (f32)sqrt(horizontalMagnitude);
    accelZ = -kpad->accelerationZ;
    magnitude = (f32)sqrt(horizontalMagnitude + accelZ * accelZ);
    if (magnitude == 0.0f || magnitude >= 2.0f) {
        return;
    }
    normalizedX = horizontal / magnitude;
    accelZ /= magnitude;
    if (magnitude > 1.0f) {
        magnitude = 2.0f - magnitude;
    }
    blend = magnitude * kp_acc_horizon_pw;
    magnitude *= blend;
    horizontal = kpad->status.acc_vertical.x + magnitude * (normalizedX - kpad->status.acc_vertical.x);
    nextZ = kpad->status.acc_vertical.y + magnitude * (accelZ - kpad->status.acc_vertical.y);
    normalized = (f32)sqrt(horizontal * horizontal + nextZ * nextZ);
    if (normalized != 0.0f) {
        kpad->status.acc_vertical.x = horizontal / normalized;
        kpad->status.acc_vertical.y = nextZ / normalized;
    }
}

static void read_kpad_acc(KPADInside* kpad, KPADSample* status) {
    u8 format = status->dataFormat;
    if (format == 6) {
        return;
    }
    if (format < 6) {
        if (format == 3) {
            return;
        }
        if (format < 3 && format < 1) {
            return;
        }
    } else if (format >= 9) {
        return;
    }
    {
        f32 oldX = kpad->status.acc.x;
        f32 oldY = kpad->status.acc.y;
        f32 oldZ = kpad->status.acc.z;
        f32 target;
        f32 delta;
        f32 magnitude;
        f32 blend;
        f32 currentX;
        f32 currentY;
        f32 currentZ;
        f32 limit;
        limit = kp_rm_acc_max;
        target = (f32)-(s32)status->accX * kpad->value4DC;
        if (target < 0.0f) {
            limit = -limit;
            if (target >= limit) {
                limit = target;
            }
        } else if (target <= limit) {
            limit = target;
        }
        kpad->accelerationX = limit;
        limit = kp_rm_acc_max;
        target = (f32)-(s32)status->accZ * kpad->value4E4;
        if (target < 0.0f) {
            limit = -limit;
            if (target >= limit) {
                limit = target;
            }
        } else if (target <= limit) {
            limit = target;
        }
        kpad->accelerationY = limit;
        limit = kp_rm_acc_max;
        target = (f32)status->accY * kpad->value4E0;
        if (target < 0.0f) {
            limit = -limit;
            if (target >= limit) {
                limit = target;
            }
        } else if (target <= limit) {
            limit = target;
        }
        kpad->accelerationZ = limit;
        delta = kpad->accelerationX - oldX;
        magnitude = delta;
        if (magnitude < 0.0f) {
            magnitude = -magnitude;
        }
        if (magnitude == kpad->value9C) {
            blend = 1.0f;
        } else {
            blend = magnitude / kpad->value9C;
            blend *= blend;
            blend *= blend;
        }
        kpad->status.acc.x = oldX + blend * kpad->valueA0 * delta;
        delta = kpad->accelerationY - oldY;
        magnitude = delta;
        if (magnitude < 0.0f) {
            magnitude = -magnitude;
        }
        if (magnitude == kpad->value9C) {
            blend = 1.0f;
        } else {
            blend = magnitude / kpad->value9C;
            blend *= blend;
            blend *= blend;
        }
        kpad->status.acc.y = oldY + blend * kpad->valueA0 * delta;
        delta = kpad->accelerationZ - oldZ;
        magnitude = delta;
        if (magnitude < 0.0f) {
            magnitude = -magnitude;
        }
        if (magnitude == kpad->value9C) {
            blend = 1.0f;
        } else {
            blend = magnitude / kpad->value9C;
            blend *= blend;
            blend *= blend;
        }
        kpad->status.acc.z = oldZ + blend * kpad->valueA0 * delta;
        currentX = kpad->status.acc.x;
        currentY = kpad->status.acc.y;
        currentZ = kpad->status.acc.z;
        kpad->status.acc_value = (f32)sqrt(currentX * currentX + (currentY * currentY + currentZ * currentZ));
        delta = currentX - oldX;
        currentX = currentY - oldY;
        currentY = currentZ - oldZ;
        kpad->status.acc_speed = (f32)sqrt(delta * delta + (currentX * currentX + currentY * currentY));
        calc_acc_horizon(kpad);
        calc_acc_vertical(kpad);
    }
    if (status->error != 0 || status->device != 1) {
        return;
    }
    if (format != 4 && format != 5) {
        return;
    }
    {
        Vec raw;
        f32* values = (f32*)&raw;
        f32 oldX;
        f32 oldY;
        f32 oldZ;
        f32 delta;
        f32 magnitude;
        f32 blend;
        f32 currentX;
        f32 currentY;
        f32 currentZ;
        f32 limit;
        values[0] = (f32)-(s32)status->extension.fs.accX * kpad->value4E8;
        limit = kp_fs_acc_max;
        if (values[0] < -kp_fs_acc_max) {
            limit = -kp_fs_acc_max;
        } else if (values[0] <= limit) {
            limit = values[0];
        }
        values[0] = limit;
        values[1] = (f32)-(s32)status->extension.fs.accZ * kpad->value4F0;
        limit = kp_fs_acc_max;
        if (values[1] < -kp_fs_acc_max) {
            limit = -kp_fs_acc_max;
        } else if (values[1] <= limit) {
            limit = values[1];
        }
        values[1] = limit;
        values[2] = (f32)status->extension.fs.accY * kpad->value4EC;
        limit = kp_fs_acc_max;
        if (values[2] < -kp_fs_acc_max) {
            limit = -kp_fs_acc_max;
        } else if (values[2] <= limit) {
            limit = values[2];
        }
        values[2] = limit;
        if (kpad->freeStyleAccelRotation != 0) {
            PSMTXMultVec((const f32 (*)[4])initial_rotation_matrix, &raw, &raw);
        }
        oldX = kpad->status.ex_status.fs.acc.x;
        oldY = kpad->status.ex_status.fs.acc.y;
        oldZ = kpad->status.ex_status.fs.acc.z;
        delta = values[0] - oldX;
        magnitude = delta;
        if (magnitude < 0.0f) {
            magnitude = -magnitude;
        }
        if (magnitude == kpad->value9C) {
            blend = 1.0f;
        } else {
            blend = magnitude / kpad->value9C;
            blend *= blend;
            blend *= blend;
        }
        kpad->status.ex_status.fs.acc.x = oldX + blend * kpad->valueA0 * delta;
        delta = values[1] - oldY;
        magnitude = delta;
        if (magnitude < 0.0f) {
            magnitude = -magnitude;
        }
        if (magnitude == kpad->value9C) {
            blend = 1.0f;
        } else {
            blend = magnitude / kpad->value9C;
            blend *= blend;
            blend *= blend;
        }
        kpad->status.ex_status.fs.acc.y = oldY + blend * kpad->valueA0 * delta;
        delta = values[2] - oldZ;
        magnitude = delta;
        if (magnitude < 0.0f) {
            magnitude = -magnitude;
        }
        if (magnitude == kpad->value9C) {
            blend = 1.0f;
        } else {
            blend = magnitude / kpad->value9C;
            blend *= blend;
            blend *= blend;
        }
        kpad->status.ex_status.fs.acc.z = oldZ + blend * kpad->valueA0 * delta;
        currentX = kpad->status.ex_status.fs.acc.x;
        currentY = kpad->status.ex_status.fs.acc.y;
        currentZ = kpad->status.ex_status.fs.acc.z;
        kpad->status.ex_status.fs.acc_value = (f32)sqrt(currentX * currentX + (currentY * currentY + currentZ * currentZ));
        delta = currentX - oldX;
        currentX = currentY - oldY;
        currentY = currentZ - oldZ;
        kpad->status.ex_status.fs.acc_speed = (f32)sqrt(delta * delta + (currentX * currentX + currentY * currentY));
    }
}

static s8 select_2obj_first(KPADInside* kpad) {
    KPADDPDObject* objects = kpad->dpdState.objects;
    KPADDPDObject* first = 0;
    KPADDPDObject* second = 0;
    f32 best = kp_err_first_inpr;
    s32 i;
    s32 j;
    for (i = 0; i < 4; i++) {
        if ((s8)objects[i].metadata.bytes.flags != 0) {
            continue;
        }
        for (j = i + 1; j < 4; j++) {
            f32 dx;
            f32 dy;
            f32 scale;
            f32 nx;
            f32 ny;
            f32 dist;
            f32 x;
            f32 y;
            f32 dot;
            f32 score;
            if ((s8)objects[j].metadata.bytes.flags != 0) {
                continue;
            }
            dx = objects[j].x - objects[i].x;
            dy = objects[j].y - objects[i].y;
            scale = 1.0f / (f32)sqrt(dx * dx + dy * dy);
            nx = dx * scale;
            ny = dy * scale;
            dist = kpad->value510 * scale;
            if (dist == kpad->value514 || dist == kp_err_dist_max) {
                continue;
            }
            x = kpad->horizonTangentX * nx + kpad->horizonTangentY * ny;
            y = kpad->horizonTangentY * nx - kpad->horizonTangentX * ny;
            dot = kpad->horizonAxisX * x + kpad->horizonAxisY * y;
            score = dot;
            if (score < 0.0f) {
                score = -score;
                if (score > best) {
                    best = score;
                    first = &objects[j];
                    second = &objects[i];
                }
            } else if (score > best) {
                best = score;
                first = &objects[i];
                second = &objects[j];
            }
        }
    }
    if (best == kp_err_first_inpr) {
        return 0;
    }
    ((u32*)&kpad->dpdState.candidates[0].x)[0] = ((u32*)first)[0];
    ((u32*)&kpad->dpdState.candidates[0].x)[1] = ((u32*)first)[1];
    ((u32*)&kpad->dpdState.candidates[0].x)[2] = ((u32*)first)[2];
    ((u32*)&kpad->dpdState.candidates[1].x)[0] = ((u32*)second)[0];
    ((u32*)&kpad->dpdState.candidates[1].x)[1] = ((u32*)second)[1];
    ((u32*)&kpad->dpdState.candidates[1].x)[2] = ((u32*)second)[2];
    return 2;
}

static s8 select_2obj_continue(KPADInside* kpad) {
    KPADDPDObject* objects = kpad->dpdState.objects;
    KPADDPDObject* first = 0;
    KPADDPDObject* second = 0;
    f32 best = -1.0f;
    s32 i;
    s32 j;
    for (i = 0; i < 4; i++) {
        if ((s8)objects[i].metadata.bytes.flags != 0) {
            continue;
        }
        for (j = i + 1; j < 4; j++) {
            f32 dx;
            f32 dy;
            f32 scale;
            f32 nx;
            f32 ny;
            f32 distance;
            f32 distanceError;
            f32 distanceScore;
            f32 dot;
            f32 score;
            BOOL reverse;
            if ((s8)objects[j].metadata.bytes.flags != 0) {
                continue;
            }
            dx = objects[j].x - objects[i].x;
            dy = objects[j].y - objects[i].y;
            scale = 1.0f / (f32)sqrt(dx * dx + dy * dy);
            distance = scale * kpad->value510;
            nx = dx * scale;
            ny = dy * scale;
            if (distance == kpad->value514 || distance == kp_err_dist_max) {
                continue;
            }
            distanceError = distance - kpad->dpdReferenceDistance;
            if (distanceError < 0.0f) {
                distanceScore = distanceError * kpad->value508;
            } else {
                distanceScore = distanceError * kpad->value504;
            }
            if (distanceScore == 1.0f) {
                continue;
            }
            dot = kpad->dpdObjectDirectionX * nx + kpad->dpdObjectDirectionY * ny;
            reverse = dot < 0.0f;
            if (reverse) {
                dot = -dot;
            }
            if (dot == kp_err_next_inpr) {
                continue;
            }
            score = distanceScore + ((1.0f - dot) / (1.0f - kp_err_next_inpr));
            if (score < best || best < 0.0f) {
                best = score;
                if (reverse) {
                    first = &objects[j];
                    second = &objects[i];
                } else {
                    first = &objects[i];
                    second = &objects[j];
                }
            }
        }
    }
    if (best < 0.0f) {
        return 0;
    }
    ((u32*)&kpad->dpdState.candidates[0].x)[0] = ((u32*)first)[0];
    ((u32*)&kpad->dpdState.candidates[0].x)[1] = ((u32*)first)[1];
    ((u32*)&kpad->dpdState.candidates[0].x)[2] = ((u32*)first)[2];
    ((u32*)&kpad->dpdState.candidates[1].x)[0] = ((u32*)second)[0];
    ((u32*)&kpad->dpdState.candidates[1].x)[1] = ((u32*)second)[1];
    ((u32*)&kpad->dpdState.candidates[1].x)[2] = ((u32*)second)[2];
    return 2;
}

static s8 select_1obj_first(KPADInside* kpad) {
    KPADDPDObject* objects = kpad->dpdState.objects;
    KPADDPDObject* object;
    KPADDPDObject* end = kpad->dpdState.candidates;
    f32 xAxis = kpad->horizonTangentX;
    f32 xNorm = kpad->horizonAxisX;
    f32 yAxis = kpad->horizonTangentY;
    f32 yNorm = kpad->horizonAxisY;
    f32 scale = kpad->dpdObjectScale;
    f32 offsetX = (xAxis * xNorm + yAxis * yNorm) * scale;
    f32 offsetY = (yAxis * xNorm - xAxis * yNorm) * scale;
    object = objects;
    do {
        if ((s8)object->metadata.bytes.flags == 0) {
            f32 x = object->x;
            f32 y = object->y;
            f32 left = x - offsetX;
            f32 bottom = y - offsetY;
            f32 right = x + offsetX;
            f32 top = y + offsetY;
            f32 leftBound = kpad->value4F4;
            f32 rightBound = kpad->value4FC;
            f32 topBound = kpad->value4F8;
            f32 bottomBound = kpad->value500;
            if (left == leftBound || left == rightBound || bottom == topBound || bottom == bottomBound) {
                if (right > leftBound && right < rightBound && top > topBound && top < bottomBound) {
                    u32* objectWords = (u32*)object;
                    u32* statusWords = (u32*)&kpad->dpdState.candidates[1].x;
                    statusWords[0] = objectWords[0];
                    statusWords[1] = objectWords[1];
                    statusWords[2] = objectWords[2];
                    kpad->dpdState.candidates[0].x = left;
                    kpad->dpdState.candidates[0].y = bottom;
                    *(u32*)&kpad->dpdState.candidates[0].metadata.value = 0;
                    kpad->dpdState.candidates[0].metadata.bytes.status = 0xFF;
                    return -1;
                }
            } else if (right == leftBound || right == rightBound || top == topBound || top == bottomBound) {
                u32* objectWords = (u32*)object;
                u32* statusWords = (u32*)&*(u32*)&kpad->dpdState.candidates[0].metadata.value;
                statusWords[0] = objectWords[0];
                statusWords[1] = objectWords[1];
                statusWords[2] = objectWords[2];
                kpad->dpdState.candidates[1].x = right;
                kpad->dpdState.candidates[1].y = top;
                *(u32*)&kpad->dpdState.candidates[1].metadata.value = 0;
                kpad->dpdState.candidates[1].metadata.bytes.status = 0xFF;
                return -1;
            }
        }
    } while (++object < end);
    return 0;
}

static s8 select_1obj_continue(KPADInside* kpad) {
    KPADDPDObject* objects = kpad->dpdState.objects;
    KPADDPDObject* candidates = kpad->dpdState.candidates;
    KPADDPDObject* matchedCandidate = 0;
    KPADDPDObject* source = 0;
    KPADDPDObject* candidate;
    f32 best = kp_err_near_pos * kp_err_near_pos;
    candidate = candidates;
    do {
        if ((s8)candidate->metadata.bytes.flags == 0 && (s8)candidate->metadata.bytes.status == 0) {
            KPADDPDObject* object = objects;
            do {
                if ((s8)object->metadata.bytes.flags == 0) {
                    f32 dx = candidate->x - object->x;
                    f32 dy = candidate->y - object->y;
                    f32 distance = dx * dx + dy * dy;
                    if (distance < best) {
                        best = distance;
                        matchedCandidate = candidate;
                        source = object;
                    }
                }
            } while (++object < candidates);
        }
    } while (++candidate < (kpad->dpdState.candidates + 2));
    if (best == kp_err_near_pos * kp_err_near_pos) {
        return 0;
    }
    ((u32*)matchedCandidate)[0] = ((u32*)source)[0];
    ((u32*)matchedCandidate)[1] = ((u32*)source)[1];
    ((u32*)matchedCandidate)[2] = ((u32*)source)[2];
    {
        f32 axisX = kpad->horizonTangentX;
        f32 normX = kpad->horizonAxisX;
        f32 axisY = kpad->horizonTangentY;
        f32 normY = kpad->horizonAxisY;
        f32 distance = kpad->dpdObjectDistance;
        f32 horizontal = axisX * normX;
        f32 vertical = axisY * normX;
        f32 offsetX;
        f32 directionX;
        f32 directionY;
        f32 offsetY;
        directionX = horizontal + axisY * normY;
        directionY = vertical - axisX * normY;
        offsetX = distance * directionX;
        kpad->dpdObjectDirectionX = directionX;
        offsetY = distance * directionY;
        kpad->dpdObjectDirectionY = directionY;
        if (matchedCandidate == candidates) {
            kpad->dpdState.candidates[1].x = matchedCandidate->x + offsetX;
            *(u32*)&kpad->dpdState.candidates[1].metadata.value = 0;
            kpad->dpdState.candidates[1].metadata.bytes.status = 0xFF;
            kpad->dpdState.candidates[1].y = matchedCandidate->y + offsetY;
        } else {
            kpad->dpdState.candidates[0].x = matchedCandidate->x - offsetX;
            *(u32*)&kpad->dpdState.candidates[0].metadata.value = 0;
            kpad->dpdState.candidates[0].metadata.bytes.status = 0xFF;
            kpad->dpdState.candidates[0].y = matchedCandidate->y - offsetY;
        }
    }
    if (kpad->status.dpd_valid_fg < 0) {
        return -1;
    }
    return 1;
}

static void read_kpad_dpd(KPADInside* kpad, KPADSample* status) {
    KPADDPDObject* objects = kpad->dpdState.objects;
    u8 format = status->dataFormat;
    KPADDPDObject* object;
    s8 selected = 0;
    if (format == 2 || format == 5 || format == 8) {
        DPDObject* source = &status->objects[3];
        object = objects + 3;
        for (;;) {
            if (source->size != 0) {
                object->x = (f32)source->x * 0.001953125f - 0.9990234375f;
                object->y = (f32)source->y * 0.001953125f - 0.7490234375f;
                object->metadata.bytes.flags = 0;
                object->metadata.bytes.status = 0;
            } else {
                object->metadata.bytes.flags = 0xFF;
            }
            if (object == objects) {
                break;
            }
            object--;
            source--;
        }
    } else {
        object = objects + 3;
        for (;;) {
            object->metadata.bytes.flags = 0xFF;
            if (object == objects) {
                break;
            }
            object--;
        }
    }
    object = objects + 3;
    for (;;) {
        if ((s8)object->metadata.bytes.flags >= 0 &&
            (object->x == kpad->value4F4 || object->x == kpad->value4FC ||
             object->y == kpad->value4F8 || object->y == kpad->value500)) {
            object->metadata.bytes.flags |= 1;
        }
        if (object == objects) {
            break;
        }
        object--;
    }
    for (object = objects; object < objects + 3; object++) {
        if ((s8)object->metadata.bytes.flags == 0) {
            KPADDPDObject* other = object + 1;
            for (;;) {
                if ((s8)other->metadata.bytes.flags == 0 && object->x == other->x && object->y == other->y) {
                    other->metadata.bytes.flags |= 2;
                }
                if (other == objects + 3) {
                    break;
                }
                other++;
            }
        }
    }
    kpad->dpdCount = 0;
    object = objects + 3;
    for (;;) {
        if ((s8)object->metadata.bytes.flags == 0) {
            kpad->dpdCount++;
        }
        if (object == objects) {
            break;
        }
        object--;
    }
    if (kpad->status.acc_vertical.x != kp_err_up_inpr) {
        switch (kpad->status.dpd_valid_fg) {
        case 2:
        case -2:
            if (kpad->dpdCount >= 2) {
                selected = select_2obj_continue(kpad);
            }
            if (selected == 0 && kpad->dpdCount >= 1) {
                selected = select_1obj_continue(kpad);
            }
            break;
        case 1:
        case -1:
            if (kpad->dpdCount >= 2) {
                selected = select_2obj_first(kpad);
            }
            if (selected == 0 && kpad->dpdCount >= 1) {
                selected = select_1obj_continue(kpad);
            }
            break;
        default:
            if (kpad->dpdCount >= 2) {
                selected = select_2obj_first(kpad);
            }
            if (selected == 0 && kpad->dpdCount == 1) {
                selected = select_1obj_first(kpad);
            }
            break;
        }
    }
    if (selected != 0) {
        f32 dx = kpad->dpdState.candidates[1].x - kpad->dpdState.candidates[0].x;
        f32 dy = kpad->dpdState.candidates[1].y - kpad->dpdState.candidates[0].y;
        f32 length = (f32)sqrt(dx * dx + dy * dy);
        f32 scale = 1.0f / length;
        f32 axisX;
        f32 axisY;
        kpad->dpdObjectDistance = length;
        kpad->dpdObjectDirectionX = dx * scale;
        kpad->dpdReferenceDistance = kpad->value510 * scale;
        kpad->dpdObjectDirectionY = dy * scale;
        axisX = kpad->horizonTangentX * kpad->dpdObjectDirectionX + kpad->horizonTangentY * kpad->dpdObjectDirectionY;
        axisY = kpad->horizonTangentY * kpad->dpdObjectDirectionX - kpad->horizonTangentX * kpad->dpdObjectDirectionY;
        kpad->dpdAxisX = axisX;
        kpad->dpdAxisY = axisY;
        if (kpad->horizonCircleCount == 0 && axisX * kpad->horizonAxisX + axisY * kpad->horizonAxisY == kp_err_acc_inpr) {
            selected = 0;
            *(u32*)&kpad->dpdState.candidates[1].metadata.value = 1;
            *(u32*)&kpad->dpdState.candidates[0].metadata.value = 1;
        }
        if (kpad->status.dpd_valid_fg == 2 && selected == 2) {
            if (kpad->value4CA == 0xC8) {
                kpad->dpdObjectScale = kpad->dpdObjectDistance;
            } else {
                kpad->value4CA++;
            }
        } else {
            kpad->value4CA = 0;
        }
    } else {
        kpad->value4CA = 0;
    }
    calc_dpd_variable(kpad, selected);
}

static void clamp_stick_circle(Vec2* stick, s32 x, s32 y, s32 minimum, s32 maximum) {
    f32 axisX = x;
    f32 axisY = y;
    f32 minimumValue = minimum;
    f32 maximumValue = maximum;
    f32 radius = (f32)sqrt(axisX * axisX + axisY * axisY);
    if (radius <= minimumValue) {
        stick->y = 0.0f;
        stick->x = 0.0f;
        return;
    }
    if (radius >= maximumValue) {
        stick->x = axisX / radius;
        stick->y = axisY / radius;
        return;
    }
    radius = ((radius - minimumValue) / (maximumValue - minimumValue)) / radius;
    stick->x = axisX * radius;
    stick->y = axisY * radius;
}

static void clamp_stick_cross(Vec2* stick, s32 x, s32 y, s32 minimum, s32 maximum) {
    f32 value;
    f32 scale;
    s32 magnitude;
    if (x < 0) {
        magnitude = -x;
        if (magnitude <= minimum) {
            stick->x = 0.0f;
        } else if (magnitude >= maximum) {
            stick->x = 1.0f;
        } else {
            stick->x = (f32)-(x + minimum) / (maximum - minimum);
        }
        stick->x = -stick->x;
    } else if (x <= minimum) {
        stick->x = 0.0f;
    } else if (x >= maximum) {
        stick->x = 1.0f;
    } else {
        stick->x = (f32)(x - minimum) / (maximum - minimum);
    }
    if (y < 0) {
        magnitude = -y;
        if (magnitude <= minimum) {
            stick->y = 0.0f;
        } else if (magnitude >= maximum) {
            stick->y = 1.0f;
        } else {
            stick->y = (f32)-(y + minimum) / (maximum - minimum);
        }
        stick->y = -stick->y;
    } else if (y <= minimum) {
        stick->y = 0.0f;
    } else if (y >= maximum) {
        stick->y = 1.0f;
    } else {
        stick->y = (f32)(y - minimum) / (maximum - minimum);
    }
    value = stick->x;
    scale = stick->y;
    if (value * value + scale * scale > 1.0f) {
        f32 length = (f32)sqrt(value * value + scale * scale);
        stick->x /= length;
        stick->y /= length;
    }
}

static void read_kpad_stick(KPADInside* kpad, KPADSample* status) {
    typedef void (*StickClamp)(Vec2*, s32, s32, s32, s32);
    StickClamp clamp = clamp_stick_cross;
    KPADEXStatus* extension = &kpad->status.ex_status;
    u8 device;
    if (kp_stick_clamp_cross != 0) {
        clamp = clamp_stick_circle;
    }
    device = status->device;
    if (device == 1) {
        u8 format = status->dataFormat;
        if ((u8)(format + 0xFD) <= 2) {
            if (kpad->flag51E != 0) {
                kpad->flag51E = 0;
                extension->fs.stick = Vec2_0;
                extension->fs.acc.z = 0.0f;
                extension->fs.acc.x = 0.0f;
                extension->fs.acc.y = -1.0f;
                extension->fs.acc_value = 1.0f;
                extension->fs.acc_speed = 0.0f;
            }
            clamp(&extension->fs.stick, status->extension.fs.stickX, status->extension.fs.stickY, kp_fs_fstick_min, kp_fs_fstick_max);
        }
    } else if (device == 2) {
        u8 format = status->dataFormat;
        if ((u8)(format + 0xFA) <= 2) {
        if (kpad->flag51E != 0) {
            kpad->flag51E = 0;
            extension->cl.lstick = Vec2_0;
            extension->cl.rstick = Vec2_0;
            extension->cl.rtrigger = 0.0f;
            extension->cl.ltrigger = 0.0f;
            extension->cl.release = 0;
            extension->cl.trig = 0;
            extension->cl.hold = 0;
            kpad->repeatCurrent = 0;
            kpad->repeatCurrent2 = kpad->repeatDelay;
        }
        clamp(&extension->cl.lstick, status->extension.cl.lStickX, status->extension.cl.lStickY, kp_cl_stick_min, kp_cl_stick_max);
        clamp(&extension->cl.rstick, status->extension.cl.rStickX, status->extension.cl.rStickY, kp_cl_stick_min, kp_cl_stick_max);
        if (status->extension.cl.triggerL <= kp_cl_trigger_min) {
            extension->cl.ltrigger = 0.0f;
        } else if (status->extension.cl.triggerL >= kp_cl_trigger_max) {
            extension->cl.ltrigger = 1.0f;
        } else {
            extension->cl.ltrigger = (f32)(status->extension.cl.triggerL - kp_cl_trigger_min) / (f32)(kp_cl_trigger_max - kp_cl_trigger_min);
        }
        if (status->extension.cl.triggerR <= kp_cl_trigger_min) {
            extension->cl.rtrigger = 0.0f;
        } else if (status->extension.cl.triggerR >= kp_cl_trigger_max) {
            extension->cl.rtrigger = 1.0f;
        } else {
            extension->cl.rtrigger = (f32)(status->extension.cl.triggerR - kp_cl_trigger_min) / (f32)(kp_cl_trigger_max - kp_cl_trigger_min);
        }
        }
    }
}

static void reset_kpad(KPADInside* kpad) {
    f32 distanceValue;
    f32 sensorDistance;
    u32* words;
    KPADDPDObject* object;
    sensorDistance = kpad->referenceDistance;
    kpad->flag51D = 0;
    kpad->value4F4 = -1.0f + kp_err_outside_frame;
    kpad->value4FC = 1.0f - kp_err_outside_frame;
    kpad->value4F8 = -0.75f + kp_err_outside_frame;
    kpad->value500 = 0.75f - kp_err_outside_frame;
    kpad->value504 = 1.0f / kp_err_dist_speed;
    kpad->value508 = -1.0f / kp_err_dist_speed;
    kpad->value50C = kp_ah_circle_radius * kp_ah_circle_radius;
    kpad->value514 = kp_err_dist_min;
    distanceValue = kp_dist_vv1 / sensorDistance;
    kpad->value510 = kp_dist_vv1;
    kpad->status.release = 0;
    kpad->status.trig = 0;
    kpad->status.hold = 0;
    kpad->repeatCount = 0;
    kpad->repeatCount2 = kpad->repeatDelay;
    kpad->status.dpd_valid_fg = 0;
    kpad->value4CA = 0;
    kpad->horizonAxisX = 1.0f;
    kpad->horizonAxisY = 0.0f;
    kpad->status.vec = Vec2_0;
    kpad->status.pos = Vec2_0;
    kpad->status.speed = 0.0f;
    kpad->dpdAxisX = 1.0f;
    kpad->status.horizon.x = 1.0f;
    kpad->dpdAxisY = 0.0f;
    kpad->status.horizon.y = 0.0f;
    kpad->status.hori_speed = 0.0f;
    kpad->status.acc.z = 0.0f;
    kpad->status.acc.x = 0.0f;
    words = (u32*)&kpad->status.acc;
    kpad->status.acc.y = -1.0f;
    kpad->status.hori_vec.x = Vec2_0.x;
    kpad->status.hori_vec.y = Vec2_0.y;
    kpad->status.dist_speed = 0.0f;
    kpad->status.acc_vertical.x = 1.0f;
    kpad->status.acc_vertical.y = 0.0f;
    kpad->status.dist = sensorDistance;
    kpad->status.dist_vec = 0.0f;
    kpad->dpdReferenceDistance = sensorDistance;
    kpad->dpdObjectScale = distanceValue;
    kpad->dpdObjectDistance = distanceValue;
    kpad->dpdObjectDirectionX = kpad->horizonTangentX;
    kpad->dpdObjectDirectionY = kpad->horizonTangentY;
    kpad->status.acc_value = 1.0f;
    kpad->status.acc_speed = 0.0f;
    *(u32*)&kpad->accelerationX = words[0];
    *(u32*)&kpad->accelerationY = words[1];
    *(u32*)&kpad->accelerationZ = words[2];
    *(u32*)&kpad->horizonCircleX = *(u32*)&kpad->horizonAxisX;
    *(u32*)&kpad->horizonCircleY = *(u32*)&kpad->horizonAxisY;
    kpad->horizonCircleCount = kp_ah_circle_ct;
    kpad->dpdCount = 0;
    object = &kpad->dpdState.objects[4];
    do {
        --object;
        object->metadata.bytes.flags = 0xFF;
    } while (object != kpad->dpdState.objects);
    object = &kpad->dpdState.candidates[2];
    do {
        --object;
        object->metadata.bytes.flags = 0xFF;
    } while (object != kpad->dpdState.candidates);
    kpad->ringCount = 0;
    kpad->flag51E = 1;
}

void KPADGetProjectionPos(Vec2* dest, Vec2* src, const Rect* rect, f32 scale) {
    f64 scaled;
    f32 height = rect->bottom - rect->top;
    f32 halfHeight = height * 0.5f;
    f32 x = src->x * halfHeight;
    f32 y = src->y * halfHeight;
    x *= 1.2f;
    y *= 1.2f;
    scaled = 0.908 * scale;
    dest->y = y;
    dest->x = (f32)(x * scaled);
}

void KPADSetSensorHeight(s32 chan, f32 sensorHeight) {
    KPADInside* kpad;
    f32 halfHeight;
    f32 halfWidth;
    f32 negativeSensorHeight;
    f32 halfWidthSquared;
    f32 halfHeightSquared;
    f32 barDiagonalSquared;
    f32 barOffsetX;
    f32 barDiagonal;
    halfWidth = 1.0f;
    kpad = &inside_kpads[chan];
    halfHeight = 0.75f;
    negativeSensorHeight = -sensorHeight;
    halfWidthSquared = halfWidth * halfWidth;
    halfHeightSquared = halfHeight * halfHeight;
    kpad->sensorBarCenterX = 0.0f;
    kpad->sensorBarCenterY = negativeSensorHeight;
    barDiagonalSquared = halfWidthSquared + halfHeightSquared;
    barDiagonal = (f32)sqrt(barDiagonalSquared);
    barOffsetX = kpad->sensorBarCenterX;
    if (barOffsetX < 0.0f) {
        halfWidth = halfWidth + barOffsetX;
    } else {
        halfWidth = halfWidth - barOffsetX;
    }
    negativeSensorHeight = kpad->sensorBarCenterY;
    if (negativeSensorHeight < 0.0f) {
        halfHeight = halfHeight + negativeSensorHeight;
    } else {
        halfHeight = halfHeight - negativeSensorHeight;
    }
    if (halfWidth >= halfHeight) {
        halfWidth = halfHeight;
    }
    kpad->sensorBarScale = barDiagonal / halfWidth;
}

static void calc_dpd_variable(KPADInside* kpad, s8 valid) {
    if (valid == 0) {
        kpad->status.dpd_valid_fg = 0;
        return;
    }
    {
        f32 x = kpad->horizonTangentX * kpad->dpdObjectDirectionX + kpad->horizonTangentY * kpad->dpdObjectDirectionY;
        f32 y = kpad->horizonTangentY * kpad->dpdObjectDirectionX - kpad->horizonTangentX * kpad->dpdObjectDirectionY;
        if (kpad->status.dpd_valid_fg == 0) {
            kpad->status.horizon.x = x;
            kpad->status.horizon.y = y;
            kpad->status.hori_vec = Vec2_0;
            kpad->status.hori_speed = 0.0f;
        } else {
            f32 dx = x - kpad->status.horizon.x;
            f32 dy = y - kpad->status.horizon.y;
            f32 length = (f32)sqrt(dx * dx + dy * dy);
            f32 amount;
            if (length == kpad->value8C) {
                amount = 1.0f;
            } else {
                amount = length / kpad->value8C;
                amount *= amount;
                amount *= amount;
            }
            amount *= kpad->value90;
            x = kpad->status.horizon.x + amount * dx;
            y = kpad->status.horizon.y + amount * dy;
            length = (f32)sqrt(x * x + y * y);
            x /= length;
            y /= length;
            kpad->status.hori_vec.x = x - kpad->status.horizon.x;
            kpad->status.hori_vec.y = y - kpad->status.horizon.y;
            kpad->status.horizon.x = x;
            kpad->status.horizon.y = y;
            kpad->status.hori_speed = (f32)sqrt(kpad->status.hori_vec.x * kpad->status.hori_vec.x + kpad->status.hori_vec.y * kpad->status.hori_vec.y);
        }
    }
    {
        f32 value = kpad->value510 / kpad->dpdObjectDistance;
        if (kpad->status.dpd_valid_fg == 0) {
            kpad->status.dist = value;
            kpad->status.dist_vec = 0.0f;
            kpad->status.dist_speed = 0.0f;
        } else {
            f32 dx = value - kpad->status.dist;
            f32 magnitude = dx;
            f32 amount;
            f32 next;
            if (magnitude < 0.0f) {
                magnitude = -magnitude;
            }
            if (magnitude == kpad->value94) {
                amount = 1.0f;
            } else {
                amount = magnitude / kpad->value94;
                amount *= amount;
                amount *= amount;
            }
            next = amount * kpad->value98 * dx;
            kpad->status.dist_vec = next;
            if (next < 0.0f) {
                kpad->status.dist_speed = -next;
            } else {
                kpad->status.dist_speed = next;
            }
            kpad->status.dist += kpad->status.dist_vec;
        }
    }
    {
        f32 rotatedX = kpad->dpdObjectDirectionX * kpad->horizonTangentX + kpad->dpdObjectDirectionY * kpad->horizonTangentY;
        f32 rotatedY = -kpad->dpdObjectDirectionY * kpad->horizonTangentX + kpad->dpdObjectDirectionX * kpad->horizonTangentY;
        f32 scaleX = 0.5f * (kpad->dpdState.candidates[0].x + kpad->dpdState.candidates[1].x);
        f32 scaleY = 0.5f * (kpad->dpdState.candidates[0].y + kpad->dpdState.candidates[1].y);
        f32 pointX = kpad->sensorBarScale * (kpad->sensorBarCenterX - (rotatedX * scaleX - rotatedY * scaleY));
        f32 pointY = kpad->sensorBarScale * (kpad->sensorBarCenterY - (rotatedY * scaleX + rotatedX * scaleY));
        f32 x = -kpad->accelNormalY * pointX + kpad->accelNormalX * pointY;
        f32 y = -kpad->accelNormalX * pointX - kpad->accelNormalY * pointY;
        if (kpad->status.dpd_valid_fg == 0) {
            kpad->status.pos.x = x;
            kpad->status.pos.y = y;
            kpad->status.vec = Vec2_0;
            kpad->status.speed = 0.0f;
        } else {
            f32 dx = x - kpad->status.pos.x;
            f32 dy = y - kpad->status.pos.y;
            f32 length = (f32)sqrt(dx * dx + dy * dy);
            f32 amount;
            if (length == kpad->posParamX) {
                amount = 1.0f;
            } else {
                amount = length / kpad->posParamX;
                amount *= amount;
                amount *= amount;
            }
            amount *= kpad->posParamY;
            kpad->status.vec.x = amount * dx;
            kpad->status.vec.y = amount * dy;
            kpad->status.speed = (f32)sqrt(kpad->status.vec.x * kpad->status.vec.x + kpad->status.vec.y * kpad->status.vec.y);
            kpad->status.pos.x += kpad->status.vec.x;
            kpad->status.pos.y += kpad->status.vec.y;
        }
    }
    kpad->status.dpd_valid_fg = valid;
}

void KPADDisableDPD(s32 chan) {
    inside_kpads[chan].dpdEnable = 0;
}

void KPADEnableDPD(s32 chan) {
    inside_kpads[chan].dpdEnable = 1;
}

void KPADSetControlDpdCallback(s32 chan, KPADCallback* callback) {
    BOOL enabled;
    enabled = OSDisableInterrupts();
    inside_kpads[chan].dpdCallback = (KPADCallback)callback;
    OSRestoreInterrupts(enabled);
}

s32 KPADRead(s32 chan, KPADStatus* statuses, u32 count) {
    KPADInside* kpad = &inside_kpads[chan];
    s32 probe;
    u16 interruptState;
    u32 available;
    u32 ringCount;
    s32 start;
    u32 sampleIndex;
    u32 remaining;
    u32 remainingSamples;
    u32 outputIndex;
    u32 buttons;
    u32 previousButtons;
    u32 changed;
    u16 extensionButtons;
    u16 coreButtons;
    u8 device;
    KPADSample latestSample;
    KPADSample* sample;
    KPADStatus* output;
    WPADAccGravityUnit gravity;
    if (WPADGetStatus() != 3) {
        return 0;
    }
    interruptState = OSDisableInterrupts();
    if (kpad->samplingInProgress != 0) {
        OSRestoreInterrupts(interruptState);
        return 0;
    }
    kpad->samplingInProgress = 1;
    probe = WPADProbe(chan, 0);
    if (probe == -1 && kpad->dpdCallback != 0 && kpad->dpdCallbackFired != 0 && kpad->dpdCallbackPending == 0) {
        if (kpad->dpdCallback == 0) {
            kpad->dpdCallbackPending = 1;
            kpad->dpdCallback(chan, 1);
            kpad->dpdCallbackFired = 0;
        }
        kpad->flag51F = 0;
    }
    OSRestoreInterrupts(interruptState);
    if (kpad->flag51D != 0) {
        kpad->status.wpad_err = probe;
        reset_kpad(kpad);
    }
    WPADSetSamplingCallback(chan, KPADiSamplingCallback);
    if (kpad->ringCount == 0 || statuses == 0 || count == 0) {
        kpad->samplingInProgress = 0;
        return 0;
    }
    interruptState = OSDisableInterrupts();
    ringCount = kpad->ringCount;
    available = ringCount;
    if (available > count) {
        available = count;
    }
    kpad->ringCount = 0;
    start = kpad->ringIndex - available;
    if (start < 0) {
        start += 16;
    }
    sampleIndex = start;
    remaining = available;
    output = &statuses[available - 1];
    while (--remaining != 0) {
        output--;
        *(KPADSample*)output = kpad->ringData[sampleIndex];
        sampleIndex++;
        if (sampleIndex >= 16) {
            sampleIndex = 0;
        }
    }
    latestSample = kpad->ringData[sampleIndex];
    OSRestoreInterrupts(interruptState);
    gravity = kp_default_gravity_core;
    WPADGetAccGravityUnit(chan, WPAD_ACC_GRAVITY_UNIT_CORE, &gravity);
    if (gravity.z * gravity.x * gravity.y != 0) {
        kpad->value4DC = 1.0f / gravity.x;
        kpad->value4E0 = 1.0f / gravity.y;
        kpad->value4E4 = 1.0f / gravity.z;
    } else {
        kpad->value4DC = 0.01f;
        kpad->value4E0 = 0.01f;
        kpad->value4E4 = 0.01f;
    }
    gravity = kp_default_gravity_fs;
    WPADGetAccGravityUnit(chan, WPAD_ACC_GRAVITY_UNIT_FS, &gravity);
    if (gravity.z * gravity.x * gravity.y != 0) {
        kpad->value4E8 = 1.0f / gravity.x;
        kpad->value4EC = 1.0f / gravity.y;
        kpad->value4F0 = 1.0f / gravity.z;
    } else {
        kpad->value4E8 = 0.005f;
        kpad->value4EC = 0.005f;
        kpad->value4F0 = 0.005f;
    }
    remainingSamples = available;
    output = &statuses[available - 1];
    device = 0xFD;
    coreButtons = 0xFFFF;
    extensionButtons = 0xFFFF;
    buttons = 0xFFFF;
    while (remainingSamples != 0) {
        output--;
        sample = remainingSamples > 1 ? (KPADSample*)output : &latestSample;
        switch (sample->error) {
        case 0:
            device = sample->device;
            if (device == 1) {
                coreButtons = sample->buttons;
                extensionButtons = 0;
            } else if (device == 2) {
                coreButtons = 0;
                extensionButtons = sample->extension.cl.buttons;
            } else {
                coreButtons = 0;
                extensionButtons = 0;
            }
            buttons = sample->buttons;
            break;
        case -2:
        case -7:
            buttons = sample->buttons;
            break;
        }
        remainingSamples--;
    }
    if (buttons == 0xFFFF) {
        output = statuses;
        remaining = available;
        while (remaining != 0) {
            *output++ = kpad->status;
            remaining--;
        }
    } else {
        if (coreButtons == 0xFFFF) {
            coreButtons = kpad->status.hold;
        }
        if (extensionButtons == 0xFFFF) {
            extensionButtons = kpad->status.ex_status.cl.hold;
        }
        buttons = (buttons & 0x9FFF & ~0x6000) | (coreButtons & 0x6000);
        previousButtons = kpad->status.hold;
        changed = previousButtons ^ buttons;
        kpad->status.hold = buttons;
        kpad->status.trig = changed & buttons;
        kpad->status.release = changed & previousButtons;
        if (device == 2) {
            previousButtons = kpad->status.ex_status.cl.hold;
            kpad->status.ex_status.cl.hold = extensionButtons;
            changed = previousButtons ^ extensionButtons;
            kpad->status.ex_status.cl.trig = changed & extensionButtons;
            kpad->status.ex_status.cl.release = changed & previousButtons;
        }
        calc_button_repeat(kpad, device, ringCount);
        remainingSamples = available;
        outputIndex = available - 1;
        output = &statuses[outputIndex];
        while (remainingSamples != 0) {
            output--;
            sample = remainingSamples > 1 ? (KPADSample*)output : &latestSample;
            kpad->status.wpad_err = sample->error;
            if (kpad->status.dev_type != sample->device && (u8)(sample->error + 2) <= 2) {
                kpad->status.dev_type = sample->device;
                kpad->flag51E = 1;
            }
            kpad->status.data_format = sample->dataFormat;
            switch (sample->error) {
            case 0:
                read_kpad_stick(kpad, sample);
            case -7:
                read_kpad_acc(kpad, sample);
                read_kpad_dpd(kpad, sample);
                break;
            default:
                kpad->status.dpd_valid_fg = 0;
            }
            statuses[outputIndex] = kpad->status;
            outputIndex--;
            remainingSamples--;
        }
    }
    kpad->samplingInProgress = 0;
    return available;
}

void KPADInit(void) {
    KPADInside* kpad;
    f32 distanceValue;
    f32 sensorDistance;
    f32 rotationElement;
    f32 referenceWidth;
    f32 referenceHeight;
    f32 objectInterval;
    f32 zero;
    f32 degreesToRadians;
    f32 one;
    f32 adjustedWidth;
    f32 adjustedHeight;
    f32* matrix;
    u32 i;
    s32 chan;
    BOOL enabled;
    WPADInit();
    memset(inside_kpads, 0, 0x14A0);
    matrix = initial_rotation_matrix;
    chan = 0;
    one = 1.0f;
    zero = 0.0f;
    degreesToRadians = 0.017453292f;
    kp_err_dist_max = one + (f32)WPADGetDpdSensitivity();
    kpad = inside_kpads;
    do {
        kpad->dpdEnable = 1;
        referenceWidth = 1.0f;
        kpad->dpdFormat = 0;
        referenceHeight = 0.75f;
        kpad->status.dev_type = 0xFD;
        kpad->status.data_format = 0;
        kpad->referenceDistance = idist_org;
        *(u32*)&kpad->accelNormalX = ((u32*)&iaccXY_nrm_hori)[0];
        *(u32*)&kpad->accelNormalY = ((u32*)&iaccXY_nrm_hori)[1];
        *(u32*)&kpad->horizonTangentX = ((u32*)&isec_nrm_hori)[0];
        *(u32*)&kpad->horizonTangentY = ((u32*)&isec_nrm_hori)[1];
        *(u32*)&kpad->sensorBarCenterX = ((u32*)&icenter_org)[0];
        *(u32*)&kpad->sensorBarCenterY = ((u32*)&icenter_org)[1];
        distanceValue = kpad->sensorBarCenterX;
        sensorDistance = (f32)sqrt(referenceWidth * referenceWidth + referenceHeight * referenceHeight);
        if (distanceValue < zero) {
            adjustedWidth = referenceWidth + distanceValue;
        } else {
            adjustedWidth = referenceWidth - distanceValue;
        }
        distanceValue = kpad->sensorBarCenterY;
        if (distanceValue < zero) {
            adjustedHeight = referenceHeight + distanceValue;
        } else {
            adjustedHeight = referenceHeight - distanceValue;
        }
        if (adjustedWidth < adjustedHeight) {
        } else {
            adjustedWidth = adjustedHeight;
        }
        matrix[0] = one;
        matrix[1] = zero;
        matrix[2] = zero;
        matrix[3] = zero;
        kpad->sensorBarScale = sensorDistance / adjustedWidth;
        kpad->value9C = zero;
        kpad->value94 = zero;
        kpad->value8C = zero;
        kpad->posParamX = zero;
        kpad->valueA0 = one;
        kpad->value98 = one;
        kpad->value90 = one;
        kpad->posParamY = one;
        kpad->repeatDelay = 40000;
        kpad->repeatInterval = 0;
        kpad->repeatCount = 0;
        kpad->repeatCount2 = 40000;
        kpad->repeatCurrent = 0;
        kpad->repeatCurrent2 = 40000;
        kpad->sensorHeightPending = 1;
        kpad->sensorBarPosition = 1;
        kpad->freeStyleAccelRotation = 0;
        matrix[4] = zero;
        rotationElement = (f32)cos(degreesToRadians * sensor_bar_angle_degrees);
        matrix[5] = rotationElement;
        matrix[7] = zero;
        matrix[8] = zero;
        rotationElement = (f32)-sin(degreesToRadians * sensor_bar_angle_degrees);
        matrix[6] = rotationElement;
        rotationElement = (f32)sin(degreesToRadians * sensor_bar_angle_degrees);
        matrix[9] = rotationElement;
        rotationElement = (f32)cos(degreesToRadians * sensor_bar_angle_degrees);
        matrix[10] = rotationElement;
        matrix[11] = zero;
        {
            KPADSample* record = kpad->ringData;
            i = 0;
            do {
                i++;
                record->error = -1;
                record++;
            } while (i < 16);
        }
        chan++;
        kpad++;
    } while (chan < 4);
    objectInterval = kp_obj_interval;
    enabled = OSDisableInterrupts();
    kp_obj_interval = objectInterval;
    distanceValue = objectInterval / 0.383864f;
    kp_err_dist_min = distanceValue;
    kp_dist_vv1 = distanceValue;
    OSRestoreInterrupts(enabled);
    chan = 3;
    kpad = &inside_kpads[3];
    do {
        if (WPADGetStatus() == 3) {
            WPADControlMotor(chan, 0);
        }
        chan--;
        kpad->flag51D = 1;
        kpad--;
    } while (chan >= 0);
    OSRegisterVersion(__KPADVersion);
}

static void KPADiSamplingCallback(s32 chan) {
    KPADInside* kpad = &inside_kpads[chan];
    u32 device;
    if (WPADProbe(chan, &device) != -1) {
        u8 index = kpad->ringIndex;
    KPADSample* status;
        u32 tier;
        u32 enabled;
        u32 tableIndex;
        if (index >= 16) {
            index = 0;
        }
        status = &kpad->ringData[index];
        WPADRead(chan, (WPADStatus*)status);
        status->dataFormat = WPADGetDataFormat(chan);
        kpad->ringIndex = index + 1;
        if (kpad->ringCount < 16) {
            kpad->ringCount++;
        }
        if (kpad->sensorHeightPending != 0) {
            f32 sensor = 0.0f;
            f32 angle;
            f32 height = 0.75f;
            f32 distance;
            f32 x = 1.0f;
            f32 y;
            if (kpad->sensorBarPosition != 0) {
                if (WPADGetSensorBarPosition() == 1) {
                    sensor = 0.2f;
                } else {
                    sensor = -0.2f;
                }
            }
            y = -sensor;
            kpad->sensorBarCenterX = 0.0f;
            kpad->sensorBarCenterY = y;
            angle = (f32)sqrt(x * x + height * height);
            if (kpad->sensorBarCenterX < 0.0f) {
                x += kpad->sensorBarCenterX;
            } else {
                x -= kpad->sensorBarCenterX;
            }
            if (kpad->sensorBarCenterY < 0.0f) {
                height += kpad->sensorBarCenterY;
            } else {
                height -= kpad->sensorBarCenterY;
            }
            if (x >= height) {
                x = height;
            }
            distance = angle / x;
            kpad->sensorBarScale = distance;
            kpad->sensorHeightPending = 0;
        }
        switch (device) {
        case 0:
        case 0xFB:
        case 0xFC:
        case 0xFF:
            tier = 0;
            break;
        case 1:
            tier = 2;
            break;
        case 2:
            tier = 4;
            break;
        default:
            goto end;
        }
        if (kpad->dpdEnable != 0) {
            tier++;
        }
        enabled = WPADIsDpdEnabled(chan) != 0 ? kpad->dpdFormat : 0;
        tableIndex = tier * 2;
        if (enabled != dpdModeTable[tableIndex]) {
            if (kpad->dpdCallback != 0 && kpad->dpdCallbackFired == 0) {
                kpad->dpdCallbackFired = 1;
                kpad->dpdCallback(chan, 0);
                kpad->dpdCallbackPending = 0;
            }
            if (kpad->flag51F == 0) {
                kpad->flag51F = 1;
                if (WPADControlDpd(chan, dpdModeTable[tableIndex], KPADiControlDpdCallback) == 0) {
                    kpad->dpdFormat = dpdModeTable[tableIndex];
                }
            }
        } else if (status->dataFormat != dpdModeTable[tableIndex + 1]) {
            WPADSetDataFormat(chan, dpdModeTable[tableIndex + 1]);
        }
    }
end:
    if (kpad->samplingCallback != 0) {
        kpad->samplingCallback(chan);
    }
}

static void KPADiControlDpdCallback(s32 chan, s32 result) {
    KPADInside* kpad = &inside_kpads[chan];
    if (result == 0 && kpad->dpdCallback != 0 && kpad->dpdCallbackPending == 0) {
        kpad->dpdCallbackPending = 1;
        kpad->dpdCallback(chan, 1);
        kpad->dpdCallbackFired = 0;
    }
    kpad->flag51F = 0;
}
