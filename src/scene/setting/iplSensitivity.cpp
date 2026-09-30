#define IPL_CONTROLLER_TRIVIAL_RECT_DTOR
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

extern __declspec(section ".sdata2") u8 sFrameColorR;
extern __declspec(section ".sdata2") u8 sFrameColorG;
extern __declspec(section ".sdata2") u8 sFrameColorB;
extern __declspec(section ".sdata2") u8 sFrameColorA;
extern __declspec(section ".sdata2") u8 sPointColorR;
extern __declspec(section ".sdata2") u8 sPointColorG;
extern __declspec(section ".sdata2") u8 sPointColorB;
extern __declspec(section ".sdata2") u8 sPointColorA;
extern __declspec(section ".sdata2") const f32 sPosZero;
extern __declspec(section ".sdata2") f32 sDpdOffsetY;
extern __declspec(section ".sdata2") f32 sDpdScale;

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
};

void SensitivityDrawing::draw(nand::File* file) {
    GXRenderModeObj mode = *System::getRenderModeObj();

    nw4r::ut::Rect rect(sPosZero, sPosZero, sPosZero, sPosZero);
    System::getProjectionRect(&rect);

    GXColor frameColor = {sFrameColorR, sFrameColorG, sFrameColorB,
                          sFrameColorA};
    u32 left;
    u32 top;
    u32 width;
    u32 height;
    GXGetScissor(&left, &top, &width, &height);

    f32 fw2 = 0.5f * (rect.right - rect.left);
    f32 ys = (0.5f * (rect.bottom - rect.top)) / 768.0f;
    f32 xs = (0.5f * (rect.right - rect.left)) * 0.0009765625f;
    f32 ws = mode.fbWidth / (rect.right - rect.left);
    f32 hs = mode.efbHeight / (rect.bottom - rect.top);
    f32 fh2 = 0.5f * (rect.bottom - rect.top);

    utility::Graphics::setDefaultOrtho(0);

    GXSetScissor((u32)(ws * (0.5f * rect.left + fw2)),
                 (u32)(hs * (0.5f * rect.top + fh2 + sDpdOffsetY)),
                 (u32)(ws * ((rect.right - rect.left) * 0.5f)),
                 (u32)(hs * ((rect.bottom - rect.top) * 0.5f)));

    utility::Graphics::drawPolygon(rect, frameColor);

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

        DPDObj* obj = last;
        do {
            if (obj->size != 0) {
                s32 x = obj->x - 0x200;
                s32 y = obj->y - 0x180;
                f32 s = sDpdScale * (obj->size + 0x19);

                nw4r::ut::Rect pos(sPosZero, sPosZero, sPosZero, sPosZero);
                f32 sx = xs * x;
                f32 sy = ys * y;
                pos.left = sx - s;
                pos.top = (-sy + s) - sDpdOffsetY;
                pos.right = sx + s;
                pos.bottom = (-sy - s) - sDpdOffsetY;

                utility::Graphics::drawTexture(pos, texObj,
                                               *(GXColor*)&sPointColorR, 2,
                                               utility::Graphics::ORI_NONE);
            }
            obj--;
        } while (obj >= first);
    }

    GXSetScissor(left, top, width, height);
}

}  // namespace ipl

extern __declspec(section ".sdata2") u8 sFrameColorR = 0x60;
extern __declspec(section ".sdata2") u8 sFrameColorG = 0x60;
extern __declspec(section ".sdata2") u8 sFrameColorB = 0x60;
extern __declspec(section ".sdata2") u8 sFrameColorA = 0xC0;
extern __declspec(section ".sdata2") u8 sPointColorR = 0xFF;
extern __declspec(section ".sdata2") u8 sPointColorG = 0xFF;
extern __declspec(section ".sdata2") u8 sPointColorB = 0xFF;
extern __declspec(section ".sdata2") u8 sPointColorA = 0xFF;
extern __declspec(section ".sdata2") const f32 sPosZero = 0.0f;
extern __declspec(section ".sdata2") f32 sDpdOffsetY = -45.0f;
extern __declspec(section ".sdata2") f32 sDpdScale = 0.15f;
