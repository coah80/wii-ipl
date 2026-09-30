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

namespace ipl {

class SensitivityDrawing {
public:
    static void draw(nand::File* file);
};

typedef struct DPDObj {
    s16 x;     // 0x0
    s16 y;     // 0x2
    u16 size;  // 0x4
    s16 id;    // 0x6
} DPDObj;

static const u8 sFrameColor[4] = {0x60, 0x60, 0x60, 0xC0};
static const u8 sPointColor[4] = {0xFF, 0xFF, 0xFF, 0xFF};

void SensitivityDrawing::draw(nand::File* file) {
    GXRenderModeObj mode = *System::getRenderModeObj();

    nw4r::ut::Rect rect(0.0f, 0.0f, 0.0f, 0.0f);
    System::getProjectionRect(&rect);

    u32 left;
    u32 top;
    u32 width;
    u32 height;
    GXGetScissor(&left, &top, &width, &height);

    f32 w = rect.right - rect.left;
    f32 h = rect.bottom - rect.top;
    f32 fw2 = 0.5f * w;
    f32 fh2 = 0.5f * h;
    f32 ys = (0.5f * (rect.bottom - rect.top)) / 768.0f;
    f32 xs = (0.5f * (rect.right - rect.left)) * 0.0009765625f;
    GXColor color = {sFrameColor[0], sFrameColor[1], sFrameColor[2], sFrameColor[3]};
    f32 ws = mode.fbWidth / w;
    f32 hs = mode.efbHeight / h;

    utility::Graphics::setDefaultOrtho(0);

    GXSetScissor((u32)(ws * (0.5f * rect.left + fw2)),
                 (u32)(hs * (fh2 + 0.5f * rect.top + -45.0f)),
                 (u32)(ws * (0.5f * (rect.right - rect.left))),
                 (u32)(hs * (0.5f * (rect.bottom - rect.top))));

    utility::Graphics::drawPolygon(rect, color);

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

        for (DPDObj* obj = last; obj >= first; obj--) {
            if (obj->size != 0) {
                s32 x = obj->x - 0x200;
                s32 y = obj->y - 0x180;
                f32 s = 0.15f * ((u32)obj->size + 0x19);

                nw4r::ut::Rect pos;
                f32 sx = xs * x;
                f32 sy = ys * y;
                pos.left = sx - s;
                pos.top = (s - sy) - -45.0f;
                pos.right = sx + s;
                pos.bottom = (-sy - s) - -45.0f;

                GXColor pointColor = {sPointColor[0], sPointColor[1],
                                      sPointColor[2], sPointColor[3]};
                utility::Graphics::drawTexture(pos, texObj, pointColor, 2,
                                               utility::Graphics::ORI_NONE);
            }
        }
    }

    GXSetScissor(left, top, width, height);
}

}  // namespace ipl
