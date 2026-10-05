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
    union {
        Vec2 position;
        struct {
            f32 x;
            f32 y;
        };
    };
    union {
        u32 value;
        struct {
            s8 flags;
            s8 status;
        } bytes;
    } metadata;
} KPADDPDObject;

typedef struct KPADInside {
    KPADStatus status;
    f32 posPlayRadius;
    f32 posSensitivity;
    f32 horizonPlayRadius;
    f32 horizonSensitivity;
    f32 distPlayRadius;
    f32 distSensitivity;
    f32 accPlayRadius;
    f32 accSensitivity;
    f32 referenceDistance;
    Vec2 accelNormal;
    Vec2 horizonTangent;
    Vec2 sensorBarCenter;
    f32 sensorBarScale;
    struct {
        KPADDPDObject objects[4];
        KPADDPDObject candidates[2];
    } dpdState;
    s16 dpdCount;
    u8 ringIndex;
    u8 ringCount;
    KPADSample ringData[16];
    f32 dpdObjectDistance;
    Vec2 dpdObjectDirection;
    f32 dpdReferenceDistance;
    f32 dpdObjectScale;
    Vec acceleration;
    f32 dpdAxisX;
    f32 dpdAxisY;
    Vec2 horizonAxis;
    Vec2 horizonCircle;
    u16 horizonCircleCount;
    u8 dpdValidPairCount;
    u16 repeatCount;
    u16 repeatCount2;
    u16 repeatDelay;
    u16 repeatInterval;
    u16 repeatCurrent;
    u16 repeatCurrent2;
    KPADCallback dpdCallback;
    f32 accScaleX;
    f32 accScaleY;
    f32 accScaleZ;
    f32 fsAccScaleX;
    f32 fsAccScaleY;
    f32 fsAccScaleZ;
    f32 dpdFrameMinX;
    f32 dpdFrameMinY;
    f32 dpdFrameMaxX;
    f32 dpdFrameMaxY;
    f32 invDistSpeed;
    f32 negInvDistSpeed;
    f32 horizonCircleRadiusSquared;
    f32 dpdDistanceScale;
    f32 minDpdDistance;
    WPADSamplingCallback samplingCallback;
    u8 samplingInProgress;
    u8 resetPending;
    u8 extensionResetPending;
    u8 dpdCommandPending;
    u8 dpdEnable;
    u8 dpdFormat;
    u8 dpdCallbackFired;
    u8 dpdCallbackPending;
    u8 sensorHeightPending;
    u8 sensorBarPosition;
    u8 freeStyleAccelRotation;
} KPADInside;

static KPADInside inside_kpads[4];
f32 initial_rotation_matrix[16];

const char* __KPADVersion = "<< RVL_SDK - KPAD \trelease build: Apr 20 2010 11:20:37 (0x4199_60831) >>";
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
static u32 kp_cl_trigger_min = 30;
static u32 kp_cl_trigger_max = 180;
static f32 kp_rm_acc_max = 3.4f;
static f32 kp_fs_acc_max = 2.1f;
f32 sensor_bar_angle_degrees = 24.0f;

static Vec2 icenter_org = {0.0f, 0.0f};
u32 kp_stick_clamp_cross = FALSE;
static Vec2 Vec2_0 = {0.0f, 0.0f};
f32 kp_err_dist_min;
static f32 kp_dist_vv1;

static void KPADiSamplingCallback(s32 chan);
static void KPADiControlDpdCallback(s32 chan, s32 result);
static void calc_dpd_variable(KPADInside* kpad, s8 valid);

static void* get_ring_buffer_by_kpad1_style(s32 chan, void* buffer, s32 style);

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

static void* get_ring_buffer_by_kpad1_style(s32 chan, void* buffer, s32 style) {
    KPADInside* kpad = &inside_kpads[chan];
    int enabled;
    s32 index;
    s32 latest;
    u32 i;
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

void KPADSetPosParam(s32 chan, f32 playRadius, f32 sensitivity) {
    KPADInside* kpad = &inside_kpads[chan];
    kpad->posPlayRadius = playRadius;
    kpad->posSensitivity = sensitivity;
}

extern const f32 sensorIntervalConversion;

static inline f32 object_interval_distance(f32 interval) {
    return interval / sensorIntervalConversion;
}

const f32 sensorIntervalConversion = 0.383864f;

static void reset_kpad(KPADInside* kpad) {
    f32 sensorDistance;
    f32 distanceValue;
    f32 zero;
    f32 upperY;
    f32 lowerY;
    f32 one;
    f32 negativeOne;
    KPADDPDObject* object;
    f32 calibratedDistance;
    negativeOne = -1.0f;
    one = 1.0f;
    zero = 0.0f;
    lowerY = -0.75f;
    upperY = 0.75f;
    sensorDistance = kpad->referenceDistance;
    kpad->resetPending = 0;
    kpad->dpdFrameMinX = negativeOne + kp_err_outside_frame;
    kpad->dpdFrameMaxX = one - kp_err_outside_frame;
    kpad->dpdFrameMinY = lowerY + kp_err_outside_frame;
    kpad->dpdFrameMaxY = upperY - kp_err_outside_frame;
    kpad->invDistSpeed = one / kp_err_dist_speed;
    kpad->negInvDistSpeed = negativeOne / kp_err_dist_speed;
    kpad->horizonCircleRadiusSquared = kp_ah_circle_radius * kp_ah_circle_radius;
    kpad->minDpdDistance = kp_err_dist_min;
    calibratedDistance = kp_dist_vv1;
    distanceValue = calibratedDistance / sensorDistance;
    kpad->dpdDistanceScale = calibratedDistance;
    kpad->status.release = 0;
    kpad->status.trig = 0;
    kpad->status.hold = 0;
    kpad->repeatCount = 0;
    kpad->repeatCount2 = kpad->repeatDelay;
    kpad->status.dpd_valid_fg = 0;
    kpad->dpdValidPairCount = 0;
    kpad->status.pos = kpad->status.vec = Vec2_0;
    kpad->horizonAxis.x = one;
    kpad->horizonAxis.y = zero;
    kpad->status.speed = zero;
    kpad->dpdAxisX = one;
    kpad->status.horizon.x = one;
    kpad->dpdAxisY = zero;
    kpad->status.horizon.y = zero;
    kpad->status.hori_vec = Vec2_0;
    kpad->status.acc.z = zero;
    kpad->status.acc.x = zero;
    kpad->status.acc.y = negativeOne;
    kpad->status.hori_speed = zero;
    kpad->status.acc_vertical.x = one;
    kpad->status.acc_vertical.y = zero;
    kpad->status.dist = sensorDistance;
    kpad->status.dist_speed = zero;
    kpad->status.dist_vec = zero;
    kpad->dpdReferenceDistance = sensorDistance;
    kpad->dpdObjectScale = distanceValue;
    kpad->dpdObjectDistance = distanceValue;
    kpad->dpdObjectDirection = kpad->horizonTangent;
    kpad->status.acc_value = one;
    kpad->status.acc_speed = zero;
    kpad->acceleration = kpad->status.acc;
    kpad->horizonCircle = kpad->horizonAxis;
    kpad->horizonCircleCount = kp_ah_circle_ct;
    kpad->dpdCount = 0;
    object = &kpad->dpdState.objects[3];
    do {
        object->metadata.bytes.flags = -1;
        --object;
    } while ((u32)object >= (u32)kpad->dpdState.objects);
    object = &kpad->dpdState.candidates[1];
    do {
        object->metadata.bytes.flags = -1;
        --object;
    } while ((u32)object >= (u32)kpad->dpdState.candidates);
    kpad->ringCount = 0;
    kpad->extensionResetPending = 1;
}

void KPADGetProjectionPos(Vec2* dest, Vec2* src, const Rect* rect, f32 scale) {
    f32 aspect;
    f32 halfHeight;
    f32 half;
    f32 x;
    f32 height;
    height = rect->bottom - rect->top;
    half = 0.5f;
    halfHeight = height * half;
    x = src->x * halfHeight;
    aspect = 1.2f;
    x = aspect * x;
    dest->y = aspect * (src->y * halfHeight);
    dest->x = (f32)(x * (0.908 * scale));
}

void KPADSetSensorHeight(s32 chan, f32 sensorHeight) {
    KPADInside* kpad;
    f32 halfHeightSquared;
    f32 halfHeight;
    f32 barOffsetX;
    f32 barDiagonal;
    f32 halfWidthSquared;
    f32 halfWidth;
    f32 negativeSensorHeight;
    f32 zero;
    halfWidth = 1.0f;
    kpad = chan + inside_kpads;
    halfHeight = 0.75f;
    negativeSensorHeight = -sensorHeight;
    halfWidthSquared = halfWidth * halfWidth;
    halfHeightSquared = halfHeight * halfHeight;
    zero = 0.0f;
    kpad->sensorBarCenter.x = zero;
    kpad->sensorBarCenter.y = negativeSensorHeight;
    barDiagonal = (f32)sqrt(halfWidthSquared + halfHeightSquared);
    barOffsetX = kpad->sensorBarCenter.x;
    if (barOffsetX < 0.0f) {
        halfWidth += barOffsetX;
    } else {
        halfWidth -= barOffsetX;
    }
    negativeSensorHeight = kpad->sensorBarCenter.y;
    if (negativeSensorHeight < 0.0f) {
        halfHeight += negativeSensorHeight;
    } else {
        halfHeight -= negativeSensorHeight;
    }
    halfWidth = halfWidth < halfHeight ? halfWidth : halfHeight;
    kpad->sensorBarScale = barDiagonal / halfWidth;
}

static void calc_button_repeat(KPADInside* kpad, u8 extension, s32 elapsed) {
    u16 count;
    u16 threshold;
    u16 current;
    u32 next;
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
        current = kpad->repeatCount;
        threshold = kpad->repeatCount2;
        if (current >= threshold) {
            kpad->status.hold |= 0x80000000;
            next = threshold + kpad->repeatInterval;
            kpad->repeatCount2 = next;
            if (current >= 20000) {
                kpad->repeatCount = current - 20000;
                kpad->repeatCount2 = (u16)next - 20000;
            }
        }
    }
    {
        u16 extensionCount;
        u16 extensionThreshold;
        u16 extensionCurrent;
        u32 extensionNext;
        if (extension == 2) {
            if (kpad->status.ex_status.cl.trig != 0 || kpad->status.ex_status.cl.release != 0) {
                kpad->repeatCurrent = 0;
                kpad->repeatCurrent2 = kpad->repeatDelay;
                if (kpad->status.ex_status.cl.trig != 0 && kpad->repeatInterval != 0) {
                    kpad->status.ex_status.cl.hold |= 0x80000000;
                }
            } else if (kpad->status.ex_status.cl.hold != 0) {
                extensionCount = kpad->repeatCurrent + elapsed;
                kpad->repeatCurrent = extensionCount;
                if (extensionCount >= 40000) {
                    kpad->repeatCurrent = extensionCount - 40000;
                }
                extensionCurrent = kpad->repeatCurrent;
                extensionThreshold = kpad->repeatCurrent2;
                if (extensionCurrent >= extensionThreshold) {
                    kpad->status.ex_status.cl.hold |= 0x80000000;
                    extensionNext = extensionThreshold + kpad->repeatInterval;
                    kpad->repeatCurrent2 = extensionNext;
                    if (extensionCurrent >= 20000) {
                        kpad->repeatCurrent = extensionCurrent - 20000;
                        kpad->repeatCurrent2 = (u16)extensionNext - 20000;
                    }
                }
            }
        }
    }
}

static void calc_acc_horizon(KPADInside* kpad) {
    f32 magnitude;
    f32 normalizedX;
    f32 normalizedY;
    f32 blend;
    f32 projectedX;
    f32 deltaX;
    f32 nextX;
    f32 nextY;
    f32 normalized;
    f32 oldCircleY;
    f32 circleX;
    f32 oldCircleX;
    f32 unitY;
    f32 unitX;
    f32 deltaCircleX;
    f32 circleY;
    f32 deltaCircleY;
    magnitude = (f32)sqrt(kpad->acceleration.x * kpad->acceleration.x + kpad->acceleration.y * kpad->acceleration.y);
    if (magnitude == 0.0f || magnitude >= 2.0f) {
        return;
    }
    {
        normalizedX = kpad->acceleration.x / magnitude;
        normalizedY = kpad->acceleration.y / magnitude;
        if (magnitude > 1.0f) {
            magnitude = 2.0f - magnitude;
        }
        blend = magnitude * kp_acc_horizon_pw;
        projectedX = kpad->accelNormal.x * normalizedX + kpad->accelNormal.y * normalizedY;
        magnitude *= blend;
        deltaX = magnitude * (projectedX - kpad->horizonAxis.x);
        nextX = kpad->horizonAxis.x + deltaX;
        nextY = kpad->horizonAxis.y + magnitude * (((kpad->accelNormal.y * normalizedX) - (kpad->accelNormal.x * normalizedY)) - kpad->horizonAxis.y);
        normalized = (f32)sqrt(nextX * nextX + nextY * nextY);
        if (normalized != 0.0f) {
            unitX = nextX / normalized;
            oldCircleX = kpad->horizonCircle.x;
            oldCircleY = kpad->horizonCircle.y;
            unitY = nextY / normalized;
            kpad->horizonAxis.x = unitX;
            kpad->horizonAxis.y = unitY;
            circleX = oldCircleX + kp_ah_circle_pw * (unitX - oldCircleX);
            deltaCircleX = unitX - circleX;
            kpad->horizonCircle.x = circleX;
            circleY = oldCircleY + kp_ah_circle_pw * (unitY - oldCircleY);
            deltaCircleY = unitY - circleY;
            kpad->horizonCircle.y = circleY;
            if (deltaCircleX * deltaCircleX + deltaCircleY * deltaCircleY <= kpad->horizonCircleRadiusSquared) {
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
    f32 blend;
    f32 nextZ;
    f32 horizontalMagnitude;
    f32 normalizedX;
    f32 normalized;
    f32 horizontal;
    f32 magnitude;
    f32 accelZ;
    horizontalMagnitude = kpad->acceleration.x * kpad->acceleration.x + kpad->acceleration.y * kpad->acceleration.y;
    horizontal = (f32)sqrt(horizontalMagnitude);
    accelZ = -kpad->acceleration.z;
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

static inline f32 clamp_acc_value(f32 value, f32 limit) {
    if (value < 0.0f) {
        limit = -limit;
        if (value < limit) {
            return limit;
        }
    } else if (value > limit) {
        return limit;
    }
    return value;
}

static inline void smooth_acc_value(KPADInside* kpad, f32 value, f32* result) {
    f32 amount;
    f32 delta;
    delta = value - *result;
    if (delta < 0.0f) {
        amount = -delta;
    } else {
        amount = delta;
    }
    if (amount >= kpad->accPlayRadius) {
        amount = 1.0f;
    } else {
        amount /= kpad->accPlayRadius;
        amount *= amount;
        amount *= amount;
    }
    amount *= kpad->accSensitivity;
    *result += amount * delta;
}

static void read_kpad_acc(KPADInside* kpad, KPADSample* status) {
    Vec raw;
    Vec previous;
    switch (status->dataFormat) {
    case 1:
    case 2:
    case 4:
    case 5:
    case 7:
    case 8:
        break;
    default:
        return;
    }
    kpad->acceleration.x = clamp_acc_value((f32)-(s32)status->accX * kpad->accScaleX, kp_rm_acc_max);
    kpad->acceleration.y = clamp_acc_value((f32)-(s32)status->accZ * kpad->accScaleZ, kp_rm_acc_max);
    kpad->acceleration.z = clamp_acc_value((f32)status->accY * kpad->accScaleY, kp_rm_acc_max);
    previous = kpad->status.acc;
    smooth_acc_value(kpad, kpad->acceleration.x, &kpad->status.acc.x);
    smooth_acc_value(kpad, kpad->acceleration.y, &kpad->status.acc.y);
    smooth_acc_value(kpad, kpad->acceleration.z, &kpad->status.acc.z);
    kpad->status.acc_value = (f32)sqrt(kpad->status.acc.z * kpad->status.acc.z + (kpad->status.acc.x * kpad->status.acc.x + kpad->status.acc.y * kpad->status.acc.y));
    previous.x -= kpad->status.acc.x;
    previous.y -= kpad->status.acc.y;
    previous.z -= kpad->status.acc.z;
    kpad->status.acc_speed = (f32)sqrt(previous.z * previous.z + (previous.x * previous.x + previous.y * previous.y));
    calc_acc_horizon(kpad);
    calc_acc_vertical(kpad);
    if (status->error == 0 && status->device == 1) {
        if (status->dataFormat == 4) {
            goto read_extension_acceleration;
        }
        if (status->dataFormat == 5) {
            goto read_extension_acceleration;
        }
    }
    return;
read_extension_acceleration:
    {
        Vec extensionPrevious;
        raw.x = clamp_acc_value((f32)-(s32)status->extension.fs.accX * kpad->fsAccScaleX, kp_fs_acc_max);
        raw.y = clamp_acc_value((f32)-(s32)status->extension.fs.accZ * kpad->fsAccScaleZ, kp_fs_acc_max);
        raw.z = clamp_acc_value((f32)status->extension.fs.accY * kpad->fsAccScaleY, kp_fs_acc_max);
        if (kpad->freeStyleAccelRotation != 0) {
            PSMTXMultVec((const f32 (*)[4])initial_rotation_matrix, &raw, &raw);
        }
        extensionPrevious = kpad->status.ex_status.fs.acc;
        smooth_acc_value(kpad, raw.x, &kpad->status.ex_status.fs.acc.x);
        smooth_acc_value(kpad, raw.y, &kpad->status.ex_status.fs.acc.y);
        smooth_acc_value(kpad, raw.z, &kpad->status.ex_status.fs.acc.z);
        kpad->status.ex_status.fs.acc_value = (f32)sqrt(kpad->status.ex_status.fs.acc.z * kpad->status.ex_status.fs.acc.z + (kpad->status.ex_status.fs.acc.x * kpad->status.ex_status.fs.acc.x + kpad->status.ex_status.fs.acc.y * kpad->status.ex_status.fs.acc.y));
        extensionPrevious.x -= kpad->status.ex_status.fs.acc.x;
        extensionPrevious.y -= kpad->status.ex_status.fs.acc.y;
        extensionPrevious.z -= kpad->status.ex_status.fs.acc.z;
        kpad->status.ex_status.fs.acc_speed = (f32)sqrt(extensionPrevious.z * extensionPrevious.z + (extensionPrevious.x * extensionPrevious.x + extensionPrevious.y * extensionPrevious.y));
    }
}

static s8 select_2obj_first(KPADInside* kpad) {
    KPADDPDObject* object;
    KPADDPDObject* other;
    KPADDPDObject* first;
    KPADDPDObject* second;
    f32 unit;
    f32 best = kp_err_first_inpr;
    f32 zero = 0.0f;
    unit = 1.0f;
    object = kpad->dpdState.objects;
    do {
        if ((s8)object->metadata.bytes.flags != 0) {
            goto nextObject;
        }
        other = object + 1;
        do {
            f32 dy;
            f32 dx;
            f32 scale;
            f32 dist;
            Vec2 direction;
            f32 dot;
            f32 score;
            if ((s8)other->metadata.bytes.flags != 0) {
                goto nextOther;
            }
            dx = other->x - object->x;
            dy = other->y - object->y;
            scale = unit / (f32)sqrt(dx * dx + dy * dy);
            dx *= scale;
            dy *= scale;
            direction.x = kpad->horizonTangent.x * dx + kpad->horizonTangent.y * dy;
            direction.y = kpad->horizonTangent.y * dx - kpad->horizonTangent.x * dy;
            dist = kpad->dpdDistanceScale * scale;
            if (dist <= kpad->minDpdDistance || dist >= kp_err_dist_max) {
                goto nextOther;
            }
            dot = kpad->horizonAxis.x * direction.x + kpad->horizonAxis.y * direction.y;
            score = dot;
            if (score < zero) {
                score = -score;
                if (score > best) {
                    best = score;
                    first = other;
                    second = object;
                }
            } else if (score > best) {
                best = score;
                first = object;
                second = other;
            }
nextOther:
            ++other;
        } while (other <= kpad->dpdState.objects + 3);
nextObject:
        ++object;
    } while (object < kpad->dpdState.objects + 3);
    if (best == kp_err_first_inpr) {
        return 0;
    }
    kpad->dpdState.candidates[0] = *first;
    kpad->dpdState.candidates[1] = *second;
    return 2;
}

static s8 select_2obj_continue(KPADInside* kpad) {
    KPADDPDObject* object;
    KPADDPDObject* other;
    KPADDPDObject* first;
    KPADDPDObject* second;
    f32 best = 2.0f;
    object = kpad->dpdState.objects;
    do {
        if ((s8)object->metadata.bytes.flags != 0) {
            goto nextObject;
        }
        other = object + 1;
        do {
            f32 dx;
            f32 dy;
            f32 scale;
            Vec2 direction;

            f32 dot;
            BOOL reverse;
            if ((s8)other->metadata.bytes.flags != 0) {
                goto nextOther;
            }
            dx = other->x - object->x;
            dy = other->y - object->y;
            scale = 1.0f / (f32)sqrt(dx * dx + dy * dy);
            direction.x = dx * scale;
            direction.y = dy * scale;
            scale *= kpad->dpdDistanceScale;
            if (scale <= kpad->minDpdDistance || scale >= kp_err_dist_max) {
                goto nextOther;
            }
            scale -= kpad->dpdReferenceDistance;
            if (scale < 0.0f) {
                scale *= kpad->negInvDistSpeed;
            } else {
                scale *= kpad->invDistSpeed;
            }
            if (scale >= 1.0f) {
                goto nextOther;
            }
            dot = kpad->dpdObjectDirection.x * direction.x + kpad->dpdObjectDirection.y * direction.y;
            if (dot < 0.0f) {
                dot = -dot;
                reverse = TRUE;
            } else {
                reverse = FALSE;
            }
            if (dot <= kp_err_next_inpr) {
                goto nextOther;
            }
            scale += ((1.0f - dot) / (1.0f - kp_err_next_inpr));
            if (scale < best) {
                best = scale;
                if (reverse) {
                    first = other;
                    second = object;
                } else {
                    first = object;
                    second = other;
                }
            }
nextOther:
            ++other;
        } while (other <= kpad->dpdState.objects + 3);
nextObject:
        ++object;
    } while (object < kpad->dpdState.objects + 3);
    if (2.0f == best) {
        return 0;
    }
    kpad->dpdState.candidates[0] = *first;
    kpad->dpdState.candidates[1] = *second;
    return 2;
}

static s8 select_1obj_first(KPADInside* kpad) {
    KPADDPDObject* object = kpad->dpdState.objects;
    f32 offsetX = kpad->horizonTangent.x * kpad->horizonAxis.x + kpad->horizonTangent.y * kpad->horizonAxis.y;
    f32 offsetY = kpad->horizonTangent.y * kpad->horizonAxis.x - kpad->horizonTangent.x * kpad->horizonAxis.y;
    offsetX *= kpad->dpdObjectScale;
    offsetY *= kpad->dpdObjectScale;
    do {
        if ((s8)object->metadata.bytes.flags == 0) {
            Vec2 leftPosition;
            Vec2 rightPosition;
            leftPosition.x = object->x - offsetX;
            leftPosition.y = object->y - offsetY;
            rightPosition.x = object->x + offsetX;
            rightPosition.y = object->y + offsetY;
            if (leftPosition.x <= kpad->dpdFrameMinX || leftPosition.x >= kpad->dpdFrameMaxX || leftPosition.y <= kpad->dpdFrameMinY || leftPosition.y >= kpad->dpdFrameMaxY) {
                if (rightPosition.x > kpad->dpdFrameMinX && rightPosition.x < kpad->dpdFrameMaxX && rightPosition.y > kpad->dpdFrameMinY && rightPosition.y < kpad->dpdFrameMaxY) {
                    kpad->dpdState.candidates[1] = *object;
                    kpad->dpdState.candidates[0].position = leftPosition;
                    kpad->dpdState.candidates[0].metadata.bytes.flags = 0;
                    kpad->dpdState.candidates[0].metadata.bytes.status = -1;
                    return -1;
                }
            } else if (rightPosition.x <= kpad->dpdFrameMinX || rightPosition.x >= kpad->dpdFrameMaxX || rightPosition.y <= kpad->dpdFrameMinY || rightPosition.y >= kpad->dpdFrameMaxY) {
                kpad->dpdState.candidates[0] = *object;
                kpad->dpdState.candidates[1].position = rightPosition;
                kpad->dpdState.candidates[1].metadata.bytes.flags = 0;
                kpad->dpdState.candidates[1].metadata.bytes.status = -1;
                return -1;
            }
        }
    } while (++object < kpad->dpdState.candidates);
    return 0;
}

static s8 select_1obj_continue(KPADInside* kpad) {
    KPADDPDObject* candidates = kpad->dpdState.candidates;
    KPADDPDObject* candidate;
    KPADDPDObject* object;
    KPADDPDObject* matchedCandidate;
    KPADDPDObject* source;
    f32 best = kp_err_near_pos * kp_err_near_pos;
    candidate = candidates;
    do {
        if ((s8)candidate->metadata.bytes.flags == 0 && (s8)candidate->metadata.bytes.status == 0) {
            object = kpad->dpdState.objects;
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
            } while (++object < kpad->dpdState.candidates);
        }
    } while (++candidate < (kpad->dpdState.candidates + 2));
    if (best == kp_err_near_pos * kp_err_near_pos) {
        return 0;
    }
    *matchedCandidate = *source;
    {
        f32 distance;
        f32 normY;
        f32 vertical;
        f32 directionY;
        f32 offsetX;
        f32 axisY;
        f32 horizontal;
        f32 axisX;
        f32 directionX;
        f32 normX;
        f32 offsetY;
        f32 tangentY;
        f32 tangentX;
        axisX = kpad->horizonTangent.x;
        normX = kpad->horizonAxis.x;
        axisY = kpad->horizonTangent.y;
        normY = kpad->horizonAxis.y;
        distance = kpad->dpdObjectDistance;
        horizontal = axisX * normX;
        vertical = axisY * normX;
        tangentY = axisY * normY;
        tangentX = axisX * normY;
        directionX = horizontal + tangentY;
        directionY = vertical - tangentX;
        offsetX = distance * directionX;
        kpad->dpdObjectDirection.x = directionX;
        offsetY = distance * directionY;
        kpad->dpdObjectDirection.y = directionY;
        if (matchedCandidate == kpad->dpdState.candidates) {
            kpad->dpdState.candidates[1].x = matchedCandidate->x + offsetX;
            kpad->dpdState.candidates[1].y = matchedCandidate->y + offsetY;
            kpad->dpdState.candidates[1].metadata.bytes.flags = 0;
            kpad->dpdState.candidates[1].metadata.bytes.status = -1;
        } else {
            kpad->dpdState.candidates[0].x = matchedCandidate->x - offsetX;
            kpad->dpdState.candidates[0].y = matchedCandidate->y - offsetY;
            kpad->dpdState.candidates[0].metadata.bytes.flags = 0;
            kpad->dpdState.candidates[0].metadata.bytes.status = -1;
        }
    }
    if (kpad->status.dpd_valid_fg < 0) {
        return -1;
    }
    return 1;
}

static void calc_dpd_variable(KPADInside* kpad, s8 valid) {
    Vec2 point;
    Vec2 delta;
    if (valid == 0) {
        kpad->status.dpd_valid_fg = 0;
        return;
    }
    {
        point.x = kpad->horizonTangent.x * kpad->dpdObjectDirection.x + kpad->horizonTangent.y * kpad->dpdObjectDirection.y;
        point.y = kpad->horizonTangent.y * kpad->dpdObjectDirection.x - kpad->horizonTangent.x * kpad->dpdObjectDirection.y;
        if (kpad->status.dpd_valid_fg == 0) {
            kpad->status.horizon = point;
            kpad->status.hori_vec = Vec2_0;
            kpad->status.hori_speed = 0.0f;
        } else {
            f32 length;
            f32 amount;
            delta.x = point.x - kpad->status.horizon.x;
            delta.y = point.y - kpad->status.horizon.y;
            length = (f32)sqrt(delta.x * delta.x + delta.y * delta.y);
            if (length >= kpad->horizonPlayRadius) {
                amount = 1.0f;
            } else {
                amount = length / kpad->horizonPlayRadius;
                amount *= amount;
                amount *= amount;
            }
            amount *= kpad->horizonSensitivity;
            delta.x = kpad->status.horizon.x + amount * delta.x;
            delta.y = kpad->status.horizon.y + amount * delta.y;
            length = (f32)sqrt(delta.x * delta.x + delta.y * delta.y);
            delta.x /= length;
            delta.y /= length;
            kpad->status.hori_vec.x = delta.x - kpad->status.horizon.x;
            kpad->status.hori_vec.y = delta.y - kpad->status.horizon.y;
            kpad->status.hori_speed = (f32)sqrt(kpad->status.hori_vec.x * kpad->status.hori_vec.x + kpad->status.hori_vec.y * kpad->status.hori_vec.y);
            kpad->status.horizon = delta;
        }
    }
    {
        f32 value = kpad->dpdDistanceScale / kpad->dpdObjectDistance;
        if (kpad->status.dpd_valid_fg == 0) {
            kpad->status.dist = value;
            kpad->status.dist_vec = 0.0f;
            kpad->status.dist_speed = 0.0f;
        } else {
            f32 magnitude;
            f32 dx;
            f32 next;
            dx = value - kpad->status.dist;
            if (dx < 0.0f) {
                magnitude = -dx;
            } else {
                magnitude = dx;
            }
            if (magnitude >= kpad->distPlayRadius) {
                magnitude = 1.0f;
            } else {
                magnitude /= kpad->distPlayRadius;
                magnitude *= magnitude;
                magnitude *= magnitude;
            }
            magnitude *= kpad->distSensitivity;
            next = magnitude * dx;
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
        f32 midpointFactor = 0.5f;
        f32 scaleX = midpointFactor * (kpad->dpdState.candidates[0].x + kpad->dpdState.candidates[1].x);
        f32 scaleY = midpointFactor * (kpad->dpdState.candidates[0].y + kpad->dpdState.candidates[1].y);
        f32 rotatedX = kpad->dpdObjectDirection.x * kpad->horizonTangent.x + kpad->dpdObjectDirection.y * kpad->horizonTangent.y;
        f32 rotatedY = -kpad->dpdObjectDirection.y * kpad->horizonTangent.x + kpad->dpdObjectDirection.x * kpad->horizonTangent.y;
        f32 transformedX = rotatedX * scaleX - rotatedY * scaleY;
        f32 transformedY = rotatedY * scaleX + rotatedX * scaleY;
        delta.x = kpad->sensorBarScale * (kpad->sensorBarCenter.x - transformedX);
        delta.y = kpad->sensorBarScale * (kpad->sensorBarCenter.y - transformedY);
        point.x = -kpad->accelNormal.y * delta.x + kpad->accelNormal.x * delta.y;
        point.y = -kpad->accelNormal.x * delta.x - kpad->accelNormal.y * delta.y;
        if (kpad->status.dpd_valid_fg == 0) {
            kpad->status.pos = point;
            kpad->status.vec = Vec2_0;
            kpad->status.speed = 0.0f;
        } else {
            f32 length;
            f32 amount;
            delta.x = point.x - kpad->status.pos.x;
            delta.y = point.y - kpad->status.pos.y;
            length = (f32)sqrt(delta.x * delta.x + delta.y * delta.y);
            if (length >= kpad->posPlayRadius) {
                amount = 1.0f;
            } else {
                amount = length / kpad->posPlayRadius;
                amount *= amount;
                amount *= amount;
            }
            amount *= kpad->posSensitivity;
            kpad->status.vec.x = amount * delta.x;
            kpad->status.vec.y = amount * delta.y;
            kpad->status.speed = (f32)sqrt(kpad->status.vec.x * kpad->status.vec.x + kpad->status.vec.y * kpad->status.vec.y);
            kpad->status.pos.x += kpad->status.vec.x;
            kpad->status.pos.y += kpad->status.vec.y;
        }
    }
    kpad->status.dpd_valid_fg = valid;
}

static void read_kpad_dpd(KPADInside* kpad, KPADSample* status) {
    u8 format = status->dataFormat;
    DPDObject* source;
    KPADDPDObject* object;
    s8 selected;
    if (format == 2 || format == 5 || format == 8) {
        source = &status->objects[3];
        object = kpad->dpdState.objects + 3;
        for (;;) {
            if (source->size != 0) {
                object->x = 0.001953125f * (f32)source->x - 0.9990234375f;
                object->y = 0.001953125f * (f32)source->y - 0.7490234375f;
                object->metadata.bytes.flags = 0;
                object->metadata.bytes.status = 0;
            } else {
                object->metadata.bytes.flags = -1;
            }
            object--;
            source--;
            if ((u32)object < (u32)kpad->dpdState.objects) {
                break;
            }
        }
    } else {
        object = kpad->dpdState.objects + 3;
        for (;;) {
            object->metadata.bytes.flags = -1;
            object--;
            if ((u32)object < (u32)kpad->dpdState.objects) {
                break;
            }
        }
    }
    {
        KPADDPDObject* other;
        KPADDPDObject* first = kpad->dpdState.objects;
        KPADDPDObject* last = kpad->dpdState.objects + 3;
        KPADDPDObject* current = last;
        for (;;) {
            if ((s8)current->metadata.bytes.flags >= 0 &&
            (current->x <= kpad->dpdFrameMinX || current->x >= kpad->dpdFrameMaxX ||
            current->y <= kpad->dpdFrameMinY || current->y >= kpad->dpdFrameMaxY)) {
                current->metadata.bytes.flags |= 1;
            }
            current--;
            if ((u32)current < (u32)first) {
                break;
            }
        }
        do {
            if ((s8)first->metadata.bytes.flags == 0) {
                other = first + 1;
                for (;;) {
                    if ((s8)other->metadata.bytes.flags == 0 && first->x == other->x && first->y == other->y) {
                        other->metadata.bytes.flags |= 2;
                    }
                    other++;
                    if (other > last) {
                        break;
                    }
                }
            }
            first++;
        } while (first < last);
    }
    kpad->dpdCount = 0;
    object = kpad->dpdState.objects + 3;
    for (;;) {
        if ((s8)object->metadata.bytes.flags == 0) {
            kpad->dpdCount++;
        }
        object--;
        if ((u32)object < (u32)kpad->dpdState.objects) {
            break;
        }
    }
    if (!(kpad->status.acc_vertical.x <= kp_err_up_inpr)) {
        if (kpad->status.dpd_valid_fg == 2 || kpad->status.dpd_valid_fg == -2) {
            if (kpad->dpdCount >= 2) {
                selected = select_2obj_continue(kpad);
                if (selected != 0) {
                    goto updateSelection;
                }
            }
            if (kpad->dpdCount >= 1) {
                selected = select_1obj_continue(kpad);
                if (selected != 0) {
                    goto updateSelection;
                }
            }
        } else if (kpad->status.dpd_valid_fg == 1 || kpad->status.dpd_valid_fg == -1) {
            if (kpad->dpdCount >= 2) {
                selected = select_2obj_first(kpad);
                if (selected != 0) {
                    goto updateSelection;
                }
            }
            if (kpad->dpdCount >= 1) {
                selected = select_1obj_continue(kpad);
                if (selected != 0) {
                    goto updateSelection;
                }
            }
        } else {
            if (kpad->dpdCount >= 2) {
                selected = select_2obj_first(kpad);
                if (selected != 0) {
                    goto updateSelection;
                }
            }
            if (kpad->dpdCount == 1) {
                selected = select_1obj_first(kpad);
                if (selected != 0) {
                    goto updateSelection;
                }
            }
        }
    }
    selected = 0;
updateSelection:
    if (selected != 0) {
        f32 dy;
        f32 dx;
        f32 scale;
        f32 length;
        f32 axisX;
        f32 axisY;
        dx = kpad->dpdState.candidates[1].x - kpad->dpdState.candidates[0].x;
        dy = kpad->dpdState.candidates[1].y - kpad->dpdState.candidates[0].y;
        length = (f32)sqrt(dx * dx + dy * dy);
        scale = 1.0f / length;
        dx *= scale;
        dy *= scale;
        kpad->dpdObjectDistance = length;
        kpad->dpdObjectDirection.x = dx;
        kpad->dpdReferenceDistance = kpad->dpdDistanceScale * scale;
        kpad->dpdObjectDirection.y = dy;
        axisX = kpad->horizonTangent.x * kpad->dpdObjectDirection.x + kpad->horizonTangent.y * kpad->dpdObjectDirection.y;
        axisY = kpad->horizonTangent.y * kpad->dpdObjectDirection.x - kpad->horizonTangent.x * kpad->dpdObjectDirection.y;
        kpad->dpdAxisX = axisX;
        kpad->dpdAxisY = axisY;
        if (kpad->horizonCircleCount == 0 && axisX * kpad->horizonAxis.x + axisY * kpad->horizonAxis.y <= kp_err_acc_inpr) {
            selected = 0;
            kpad->dpdState.candidates[1].metadata.bytes.flags = 1;
            kpad->dpdState.candidates[0].metadata.bytes.flags = 1;
        }
        if (kpad->status.dpd_valid_fg == 2 && selected == 2) {
            if (kpad->dpdValidPairCount == 0xC8) {
                kpad->dpdObjectScale = kpad->dpdObjectDistance;
            } else {
                kpad->dpdValidPairCount++;
            }
        } else {
            kpad->dpdValidPairCount = 0;
        }
    } else {
        kpad->dpdValidPairCount = 0;
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
    u8 format;
    s32 maximum;
    s32 minimum;
    s32 rightMaximum;
    s32 rightMinimum;
    if (kp_stick_clamp_cross != 0) {
        clamp = clamp_stick_circle;
    }
    device = status->device;
    if (device == 1) {
        format = status->dataFormat;
        if ((u8)(format + 0xFD) <= 2) {
            if (kpad->extensionResetPending != 0) {
                kpad->extensionResetPending = 0;
                extension->fs.stick = Vec2_0;
                extension->fs.acc.z = 0.0f;
                extension->fs.acc.x = 0.0f;
                extension->fs.acc.y = -1.0f;
                extension->fs.acc_value = 1.0f;
                extension->fs.acc_speed = 0.0f;
            }
            clamp(&extension->fs.stick, status->extension.fs.stickX, status->extension.fs.stickY, kp_fs_fstick_min, kp_fs_fstick_max);
            return;
        }
    }
    if (device == 2) {
        format = status->dataFormat;
        if ((u8)(format + 0xFA) > 2) {
            return;
        }
        if (kpad->extensionResetPending != 0) {
            kpad->extensionResetPending = 0;
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
        minimum = kp_cl_trigger_min;
        maximum = kp_cl_trigger_max;
        if (status->extension.cl.triggerL <= minimum) {
            extension->cl.ltrigger = 0.0f;
        } else if (status->extension.cl.triggerL >= maximum) {
            extension->cl.ltrigger = 1.0f;
        } else {
            extension->cl.ltrigger = (f32)(status->extension.cl.triggerL - minimum) / (maximum - minimum);
        }
        rightMinimum = kp_cl_trigger_min;
        rightMaximum = kp_cl_trigger_max;
        if (status->extension.cl.triggerR <= rightMinimum) {
            extension->cl.rtrigger = 0.0f;
            return;
        }
        if (status->extension.cl.triggerR >= rightMaximum) {
            extension->cl.rtrigger = 1.0f;
            return;
        }
        extension->cl.rtrigger = (f32)(status->extension.cl.triggerR - rightMinimum) / (rightMaximum - rightMinimum);
    }
}

s32 KPADRead(s32 chan, KPADStatus* statuses, u32 count) {
    u32 changed;
    u16 heldButtons;
    KPADStatus* output;
    KPADInside* kpad = &inside_kpads[chan];
    s32 probe;
    BOOL interruptState;
    u32 available = 0;
    u32 ringCount;
    s32 start;
    s32 sampleIndex;
    s32 remaining;
    u32 remainingSamples;
    u32 buttons;
    u16 previousButtons;
    u32 coreButtons;
    u32 extensionButtons;
    u8 device;
    KPADSample latestSample;
    KPADSample* sample;
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
        if (kpad->dpdCallback != 0 && kpad->dpdCallbackPending == 0) {
            kpad->dpdCallbackPending = 1;
            kpad->dpdCallback(chan, 1);
            kpad->dpdCallbackFired = 0;
        }
        kpad->dpdCommandPending = 0;
    }
    OSRestoreInterrupts(interruptState);
    if (kpad->resetPending != 0) {
        kpad->status.wpad_err = probe;
        reset_kpad(kpad);
    }
    WPADSetSamplingCallback(chan, KPADiSamplingCallback);
    if (kpad->ringCount == 0 || statuses == 0 || count == 0) {
        goto finish;
    }
    interruptState = OSDisableInterrupts();
    ringCount = kpad->ringCount;
    available = ringCount;
    if (available > count) {
        available = count;
    }
    remaining = available;
    kpad->ringCount = 0;
    output = statuses + remaining;
    start = kpad->ringIndex - available;
    if (start < 0) {
        start += 16;
    }
    --output;
    {
        sampleIndex = start;
        while (--remaining != 0) {
            output--;
            *(KPADSample*)output = kpad->ringData[sampleIndex];
            sampleIndex++;
            if (sampleIndex >= 16) {
                sampleIndex = 0;
            }
        }
    }
    latestSample = kpad->ringData[sampleIndex];
    OSRestoreInterrupts(interruptState);
    {
        WPADAccGravityUnit gravity = {1, 1, 1};
        WPADAccGravityUnit extensionGravity = {1, 1, 1};
        WPADGetAccGravityUnit(chan, WPAD_ACC_GRAVITY_UNIT_CORE, &gravity);
        if (gravity.x * gravity.y * gravity.z != 0) {
            kpad->accScaleX = 1.0f / gravity.x;
            kpad->accScaleY = 1.0f / gravity.y;
            kpad->accScaleZ = 1.0f / gravity.z;
        } else {
            kpad->accScaleX = 0.01f;
            kpad->accScaleY = 0.01f;
            kpad->accScaleZ = 0.01f;
        }
        WPADGetAccGravityUnit(chan, WPAD_ACC_GRAVITY_UNIT_FS, &extensionGravity);
        if (extensionGravity.x * extensionGravity.y * extensionGravity.z != 0) {
            kpad->fsAccScaleX = 1.0f / extensionGravity.x;
            kpad->fsAccScaleY = 1.0f / extensionGravity.y;
            kpad->fsAccScaleZ = 1.0f / extensionGravity.z;
        } else {
            kpad->fsAccScaleX = 0.005f;
            kpad->fsAccScaleY = 0.005f;
            kpad->fsAccScaleZ = 0.005f;
        }
        remainingSamples = available;
        output = statuses + available;
        --output;
        device = 0xFD;
        extensionButtons = 0xFFFF;
        coreButtons = 0xFFFF;
        buttons = 0xFFFF;
        do {
            output--;
            sample = remainingSamples > 1 ? (KPADSample*)output : &latestSample;
            switch (sample->error) {
            case 0:
                device = sample->device;
                if (device == 1) {
                    coreButtons = sample->buttons;
                    extensionButtons = 0;
                } else if (device == 2) {
                    extensionButtons = sample->extension.cl.buttons;
                    coreButtons = 0;
                } else {
                    extensionButtons = 0;
                    coreButtons = 0;
                }
            case -2:
            case -7:
                buttons = sample->buttons;
                break;
            }
        } while (--remainingSamples != 0);
        if (buttons == 0xFFFF) {
            output = statuses;
            do {
                memcpy(output, &kpad->status, sizeof(KPADStatus));
                output++;
            } while (--available != 0);
        } else {
            if (coreButtons == 0xFFFF) {
                coreButtons = kpad->status.hold;
            }
            if (extensionButtons == 0xFFFF) {
                extensionButtons = kpad->status.ex_status.cl.hold;
            }
            previousButtons = kpad->status.hold;
            heldButtons = (buttons & 0x9FFF) | (coreButtons & 0x6000);
            changed = heldButtons ^ previousButtons;
            kpad->status.hold = heldButtons;
            kpad->status.trig = changed & heldButtons;
            kpad->status.release = changed & previousButtons;
            if (device == 2) {
                u16 previousExtensionButtons;
                previousExtensionButtons = kpad->status.ex_status.cl.hold;
                extensionButtons = (u16)extensionButtons;
                kpad->status.ex_status.cl.hold = extensionButtons;
                changed = extensionButtons ^ previousExtensionButtons;
                kpad->status.ex_status.cl.trig = changed & extensionButtons;
                kpad->status.ex_status.cl.release = changed & previousExtensionButtons;
            }
            calc_button_repeat(kpad, device, ringCount);
            remainingSamples = available;
            output = statuses + available;
            --output;
            do {
                output--;
                sample = remainingSamples > 1 ? (KPADSample*)output : &latestSample;
                kpad->status.wpad_err = sample->error;
                if (kpad->status.dev_type != sample->device && (u8)(sample->error + 2) <= 2) {
                    kpad->status.dev_type = sample->device;
                    kpad->extensionResetPending = 1;
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
                output[1] = kpad->status;
            } while (--remainingSamples != 0);
        }
    }
finish:
    kpad->samplingInProgress = 0;
    return available;
}

void KPADInit(void) {
    KPADInside* kpad;
    f32 degreesToRadians;
    f32 zero;
    f32 one;
    f32 distanceValue;
    f32 sensorDistance;
    f32 rotationElement;
    f64 negativeSine;
    f32 sineElement;
    f32 referenceHeight;
    f32 objectInterval;
    f32 referenceWidth;
    u32 i;
    s32 chan;
    BOOL enabled;
    WPADInit();
    memset(inside_kpads, 0, 0x14A0);
    kp_err_dist_max = 1.0f + (f32)WPADGetDpdSensitivity();
    chan = 0;
    one = 1.0f;
    zero = 0.0f;
    degreesToRadians = 0.017453292f;
    kpad = inside_kpads;
    do {
        kpad->dpdEnable = 1;
        referenceWidth = 1.0f;
        kpad->dpdFormat = 0;
        referenceHeight = 0.75f;
        kpad->status.dev_type = 0xFD;
        kpad->status.data_format = 0;
        kpad->referenceDistance = idist_org;
        kpad->accelNormal = iaccXY_nrm_hori;
        kpad->horizonTangent = isec_nrm_hori;
        kpad->sensorBarCenter = icenter_org;
        sensorDistance = (f32)sqrt(referenceWidth * referenceWidth + referenceHeight * referenceHeight);
        distanceValue = kpad->sensorBarCenter.x;
        if (distanceValue < zero) {
            referenceWidth += distanceValue;
        } else {
            referenceWidth -= distanceValue;
        }
        distanceValue = kpad->sensorBarCenter.y;
        if (distanceValue < zero) {
            referenceHeight += distanceValue;
        } else {
            referenceHeight -= distanceValue;
        }
        referenceWidth = referenceWidth < referenceHeight ? referenceWidth : referenceHeight;
        kpad->sensorBarScale = sensorDistance / referenceWidth;
        kpad->accPlayRadius = zero;
        kpad->distPlayRadius = zero;
        kpad->horizonPlayRadius = zero;
        kpad->posPlayRadius = zero;
        kpad->accSensitivity = one;
        kpad->distSensitivity = one;
        kpad->horizonSensitivity = one;
        kpad->posSensitivity = one;
        kpad->repeatDelay = 40000;
        kpad->repeatInterval = 0;
        kpad->repeatCount = 0;
        kpad->repeatCount2 = 40000;
        kpad->repeatCurrent = 0;
        kpad->repeatCurrent2 = 40000;
        kpad->sensorHeightPending = 1;
        kpad->sensorBarPosition = 1;
        kpad->freeStyleAccelRotation = 0;
        initial_rotation_matrix[0] = one;
        initial_rotation_matrix[1] = zero;
        initial_rotation_matrix[2] = zero;
        initial_rotation_matrix[3] = zero;
        initial_rotation_matrix[4] = zero;
        rotationElement = (f32)cos(degreesToRadians * sensor_bar_angle_degrees);
        initial_rotation_matrix[5] = rotationElement;
        negativeSine = -sin(degreesToRadians * sensor_bar_angle_degrees);
        sineElement = (f32)negativeSine;
        initial_rotation_matrix[7] = zero;
        initial_rotation_matrix[8] = zero;
        initial_rotation_matrix[6] = sineElement;
        rotationElement = (f32)sin(degreesToRadians * sensor_bar_angle_degrees);
        initial_rotation_matrix[9] = rotationElement;
        rotationElement = (f32)cos(degreesToRadians * sensor_bar_angle_degrees);
        initial_rotation_matrix[10] = rotationElement;
        initial_rotation_matrix[11] = zero;
        {
            i = 0;
            do {
                i++;
                kpad->ringData[i - 1].error = -1;
            } while (i < 16);
        }
        chan++;
        kpad++;
    } while (chan < 4);
    objectInterval = kp_obj_interval;
    enabled = OSDisableInterrupts();
    kp_obj_interval = objectInterval;
    distanceValue = object_interval_distance(objectInterval);
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
        kpad->resetPending = 1;
        kpad--;
    } while (chan >= 0);
    OSRegisterVersion(__KPADVersion);
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

static void KPADiSamplingCallback(s32 chan) {
    KPADInside* kpad = &inside_kpads[chan];
    u32 device;
    if (WPADProbe(chan, &device) != -1) {
        u8 index = kpad->ringIndex;
        u32 tier;
        KPADSample* status;
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
            f32 sensor;
            f32 angle;
            f32 height;
            f32 distance;
            f32 x;
            if (kpad->sensorBarPosition != 0) {
                if (WPADGetSensorBarPosition() == 1) {
                    sensor = 0.2f;
                } else {
                    sensor = -0.2f;
                }
            } else {
                sensor = 0.0f;
            }
            x = 1.0f;
            height = 0.75f;
            kpad->sensorBarCenter.x = 0.0f;
            kpad->sensorBarCenter.y = -sensor;
            angle = (f32)sqrt(x * x + height * height);
            if (kpad->sensorBarCenter.x < 0.0f) {
                x += kpad->sensorBarCenter.x;
            } else {
                x -= kpad->sensorBarCenter.x;
            }
            if (kpad->sensorBarCenter.y < 0.0f) {
                height += kpad->sensorBarCenter.y;
            } else {
                height -= kpad->sensorBarCenter.y;
            }
            x = x < height ? x : height;
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
            goto callback;
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
            if (kpad->dpdCommandPending == 0) {
                kpad->dpdCommandPending = 1;
                if (WPADControlDpd(chan, dpdModeTable[tableIndex], KPADiControlDpdCallback) == 0) {
                    kpad->dpdFormat = dpdModeTable[tableIndex];
                }
            }
        } else if (status->dataFormat != dpdModeTable[tableIndex + 1]) {
            WPADSetDataFormat(chan, dpdModeTable[tableIndex + 1]);
        }
    }
callback:
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
    kpad->dpdCommandPending = 0;
}
