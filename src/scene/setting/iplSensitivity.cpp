#include <nw4r/ut/Rect.h>

extern "C" {
#include <revolution/gx.h>
#include <revolution/tpl.h>
#include <revolution/wpad.h>
}

#include <system/iplController.h>
#include <system/iplNand.h>
#include <system/iplSystem.h>
#include <utility/iplGraphics.h>

extern "C" void* KPADGetWPADRingBuffer(s32 chan);
extern "C" void* KPADGetWPADFSRingBuffer(s32 chan);
extern "C" void* KPADGetWPADCLRingBuffer(s32 chan);

extern __declspec(section ".sdata2") const GXColor sFrameColor;
extern __declspec(section ".sdata2") const GXColor sPointColor;

namespace ipl {

typedef struct DPDObj {
    s16 x;     // 0x0
    s16 y;     // 0x2
    u16 size;  // 0x4
    s16 id;    // 0x6
} DPDObj;

class SensitivityDrawing {
public:
    static void draw(nand::File* file);

private:
    static void drawDpdObjects(DPDObj* first, DPDObj* last,
                               const GXTexObj& texObj, f32 xs, f32 ys);
};

void SensitivityDrawing::draw(nand::File* file) {
    GXRenderModeObj mode = *System::getRenderModeObj();

    nw4r::ut::Rect rect(0.0f, 0.0f, 0.0f, 0.0f);
    System::getProjectionRect(&rect);

    u32 left;
    u32 top;
    u32 width;
    u32 height;
    GXGetScissor(&left, &top, &width, &height);

    f32 fw2 = 0.5f * (rect.right - rect.left);
    f32 fh2 = 0.5f * (rect.bottom - rect.top);
    f32 ws = mode.fbWidth / (rect.right - rect.left);
    f32 hs = mode.efbHeight / (rect.bottom - rect.top);

    utility::Graphics::setDefaultOrtho(0);

    GXSetScissor((u32)(ws * (0.5f * rect.left + fw2)),
                 (u32)(hs * (0.5f * rect.top + fh2 + -45.0f)),
                 (u32)(ws * ((rect.right - rect.left) * 0.5f)),
                 (u32)(hs * ((rect.bottom - rect.top) * 0.5f)));

    utility::Graphics::drawPolygon(rect, sFrameColor);

    controller::Interface* controller = System::getYoungController();
    if (controller != NULL && controller->getKPADStatus() != NULL) {
        GXTexObj texObj;
        TPLGetGXTexObjFromPalette((TPLPalette*)file->getBuffer(), &texObj, 1);
        GXInitTexObjWrapMode(&texObj, GX_MIRROR, GX_MIRROR);

        s32 index = WPADGetLatestIndexInBuf(controller->getChannel());

        DPDObj* first;
        DPDObj* last;
        switch (controller->getType()) {
            case 0: {
                u8* base = (u8*)KPADGetWPADRingBuffer(
                               controller->getChannel()) +
                           index * 0x2A;
                last = (DPDObj*)(base + 0x20);
                first = (DPDObj*)(base + 8);
                break;
            }
            case 1: {
                u8* base = (u8*)KPADGetWPADFSRingBuffer(
                               controller->getChannel()) +
                           index * 0x32;
                last = (DPDObj*)(base + 0x20);
                first = (DPDObj*)(base + 8);
                break;
            }
            case 2: {
                u8* base = (u8*)KPADGetWPADCLRingBuffer(
                               controller->getChannel()) +
                           index * 0x36;
                last = (DPDObj*)(base + 0x20);
                first = (DPDObj*)(base + 8);
                break;
            }
        }

        f32 ys = (0.5f * (rect.bottom - rect.top)) / 768.0f;
        f32 xs = (0.5f * (rect.right - rect.left)) * 0.0009765625f;
        drawDpdObjects(first, last, texObj, xs, ys);
    }

    GXSetScissor(left, top, width, height);
}

extern __declspec(section ".sdata2") const GXColor sFrameColor = {0x60, 0x60, 0x60, 0xC0};
extern __declspec(section ".sdata2") const GXColor sPointColor = {0xFF, 0xFF, 0xFF, 0xFF};

inline void SensitivityDrawing::drawDpdObjects(DPDObj* first, DPDObj* last,
                                               const GXTexObj& texObj, f32 xs,
                                               f32 ys) {
    for (DPDObj* obj = last; obj >= first; obj--) {
        if (obj->size != 0) {
            s32 x = obj->x - 0x200;
            s32 y = obj->y - 0x180;
            f32 s = 0.15f * (obj->size + 0x19);

            nw4r::ut::Rect pos;
            f32 sx = xs * x;
            f32 sy = ys * y;
            pos.left = sx - s;
            pos.top = (-sy + s) - -45.0f;
            pos.right = sx + s;
            pos.bottom = (-sy - s) - -45.0f;

            utility::Graphics::drawTexture(pos, texObj, sPointColor, 2,
                                           utility::Graphics::ORI_NONE);
        }
    }
}

}  // namespace ipl
