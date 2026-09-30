#include "system/iplSystem.h"
#include "system/iplNand.h"
#include "utility/iplGraphics.h"
#include <revolution/tpl.h>

extern "C" {
WPADStatus* KPADGetWPADRingBuffer(s32 channel);
WPADFSStatus* KPADGetWPADFSRingBuffer(s32 channel);
WPADCLStatus* KPADGetWPADCLRingBuffer(s32 channel);
}

namespace ipl {
class SensitivityDrawing {
public:
    static void draw(nand::File* texture);
};

void SensitivityDrawing::draw(nand::File* texture) {
    GXRenderModeObj renderMode = *System::getRenderModeObj();
    nw4r::ut::Rect projection;
    System::getProjectionRect(&projection);
    GXColor background = {96, 96, 96, 192};
    u32 scissorX, scissorY, scissorWidth, scissorHeight;
    GXGetScissor(&scissorX, &scissorY, &scissorWidth, &scissorHeight);
    f32 projectionWidth = projection.GetWidth();
    f32 projectionHeight = projection.GetHeight();
    f32 halfWidth = 0.5f * projectionWidth;
    f32 scaleX = renderMode.fbWidth / projectionWidth;
    f32 scaleY = renderMode.efbHeight / projectionHeight;
    f32 halfHeight = 0.5f * projectionHeight;
    utility::Graphics::setDefaultOrtho(0);
    projectionHeight = projection.GetHeight();
    projectionWidth = projection.GetWidth();
    GXSetScissor(scaleX * (0.5f * projection.left + halfWidth),
                 scaleY * (-45.0f + (0.5f * projection.top + halfHeight)),
                 scaleX * (0.5f * projectionWidth),
                 scaleY * (0.5f * projectionHeight));
    utility::Graphics::drawPolygon(projection, background);
    controller::Interface* controller = System::getYoungController();
    if (controller != NULL && controller->getKPADStatus() != NULL) {
        GXTexObj image;
        TPLGetGXTexObjFromPalette((TPLPalette*)texture->getBuffer(), &image, 1);
        GXInitTexObjWrapMode(&image, GX_MIRROR, GX_MIRROR);
        f32 width = projection.GetWidth();
        f32 height = projection.GetHeight();
        f32 horizontalScale = (0.5f * width) / 1024.0f;
        f32 verticalScale = (0.5f * height) / 768.0f;
        int sample = WPADGetLatestIndexInBuf(controller->getChannel());
        DPDObject* object;
        DPDObject* first;
        switch (controller->getType()) {
        case 0: {
            WPADStatus* status = KPADGetWPADRingBuffer(controller->getChannel()) + sample;
            object = &status->obj[3];
            first = &status->obj[0];
            break;
        }
        case 1: {
            WPADFSStatus* status = KPADGetWPADFSRingBuffer(controller->getChannel()) + sample;
            object = &status->obj[3];
            first = &status->obj[0];
            break;
        }
        case 2: {
            WPADCLStatus* status = KPADGetWPADCLRingBuffer(controller->getChannel()) + sample;
            object = &status->obj[3];
            first = &status->obj[0];
            break;
        }
        }
        do {
            if (object->size != 0) {
                f32 radius = 0.15f * (object->size + 25);
                f32 x = (object->x - 512) * horizontalScale;
                f32 y = (object->y - 384) * verticalScale;
                GXColor foreground = {255, 255, 255, 255};
                nw4r::ut::Rect rectangle(x - radius, -y + radius - -45.0f,
                                         x + radius, -y - radius - -45.0f);
                utility::Graphics::drawTexture(rectangle, image, foreground, 2, utility::Graphics::ORI_NONE);
            }
        } while (--object >= first);
    }
    GXSetScissor(scissorX, scissorY, scissorWidth, scissorHeight);
}
}
