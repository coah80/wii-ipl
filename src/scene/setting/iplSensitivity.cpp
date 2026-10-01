#include <revolution/types.h>

namespace ipl {
namespace nand { class File; }
class SensitivityDrawing {
public:
    static void draw(nand::File* texture);
};
}

extern "C" {
void _savegpr_27();
void _restgpr_27();
void GXGetScissor();
void GXSetScissor();
void GXInitTexObjWrapMode();
void TPLGetGXTexObjFromPalette();
void WPADGetLatestIndexInBuf();
void __cvt_fp2unsigned();
void KPADGetWPADRingBuffer();
void KPADGetWPADFSRingBuffer();
void KPADGetWPADCLRingBuffer();
void getRenderModeObj__Q23ipl6SystemFv();
void getProjectionRect__Q23ipl6SystemFPQ34nw4r2ut4Rect();
void setDefaultOrtho__Q33ipl7utility8GraphicsFUl();
void drawPolygon__Q33ipl7utility8GraphicsFRCQ34nw4r2ut4Rect8_GXColor();
void getYoungController__Q23ipl6SystemFv();
void drawTexture__Q33ipl7utility8GraphicsFRCQ34nw4r2ut4RectRC9_GXTexObj8_GXColorUcQ43ipl7utility8Graphics11Orientation();
}

#pragma section sconst_type ".sdata2"
extern "C" __declspec(section ".sdata2") const f32 lbl_81694C40 = 0.5f;
extern "C" __declspec(section ".sdata2") const f32 lbl_81694C44 = 768.0f;
extern "C" __declspec(section ".sdata2") const f32 lbl_81694C48 = 0.0009765625f;
extern "C" __declspec(section ".sdata2") const u32 lbl_81694C4C = 0;
extern "C" __declspec(section ".sdata2") const f64 lbl_81694C50 = 4503601774854144.0;
extern "C" __declspec(section ".sdata2") const u8 lbl_81694C58 = 0x60;
extern "C" __declspec(section ".sdata2") const u8 lbl_81694C59 = 0x60;
extern "C" __declspec(section ".sdata2") const u8 lbl_81694C5A = 0x60;
extern "C" __declspec(section ".sdata2") const u8 lbl_81694C5B = 0xC0;
extern "C" __declspec(section ".sdata2") const u8 lbl_81694C5C = 0xFF;
extern "C" __declspec(section ".sdata2") const u8 lbl_81694C5D = 0xFF;
extern "C" __declspec(section ".sdata2") const u8 lbl_81694C5E = 0xFF;
extern "C" __declspec(section ".sdata2") const u8 lbl_81694C5F = 0xFF;
extern "C" __declspec(section ".sdata2") const f32 lbl_81694C60 = 0.0f;
extern "C" __declspec(section ".sdata2") const f32 lbl_81694C64 = -45.0f;
extern "C" __declspec(section ".sdata2") const f32 lbl_81694C68 = 0.15f;
extern "C" __declspec(section ".sdata2") const u32 lbl_81694C6C = 0;
extern "C" __declspec(section ".sdata2") const f64 lbl_81694C70 = 4503599627370496.0;

namespace ipl {
asm void SensitivityDrawing::draw(nand::File* texture) {
    nofralloc
    stwu r1, -0x120(r1)
    mflr r0
    stw r0, 0x124(r1)
    stfd f31, 0x110(r1)
    psq_st f31, 0x118(r1), 0, 0
    stfd f30, 0x100(r1)
    psq_st f30, 0x108(r1), 0, 0
    stfd f29, 0xf0(r1)
    psq_st f29, 0xf8(r1), 0, 0
    stfd f28, 0xe0(r1)
    psq_st f28, 0xe8(r1), 0, 0
    stfd f27, 0xd0(r1)
    psq_st f27, 0xd8(r1), 0, 0
    addi r11, r1, 0xd0
    bl _savegpr_27
    lis r0, 0x4330
    mr r30, r3
    stw r0, 0xa0(r1)
    stw r0, 0xa8(r1)
    bl getRenderModeObj__Q23ipl6SystemFv
    li r0, 0x7
    addi r5, r1, 0x60
    subi r4, r3, 0x4
    mtctr r0
    L_813F9BD0:
    lwz r3, 0x4(r4)
    lwzu r0, 0x8(r4)
    stw r3, 0x4(r5)
    stwu r0, 0x8(r5)
    bdnz L_813F9BD0
    lwz r0, 0x4(r4)
    addi r3, r1, 0x34
    lfs f0, lbl_81694C60(r0)
    stw r0, 0x4(r5)
    stfs f0, 0x34(r1)
    stfs f0, 0x38(r1)
    stfs f0, 0x3c(r1)
    stfs f0, 0x40(r1)
    bl getProjectionRect__Q23ipl6SystemFPQ34nw4r2ut4Rect
    lbz r9, lbl_81694C58(r0)
    addi r3, r1, 0x1c
    lbz r8, lbl_81694C59(r0)
    addi r4, r1, 0x18
    lbz r7, lbl_81694C5A(r0)
    addi r5, r1, 0x14
    lbz r0, lbl_81694C5B(r0)
    addi r6, r1, 0x10
    stb r9, 0x20(r1)
    stb r8, 0x21(r1)
    stb r7, 0x22(r1)
    stb r0, 0x23(r1)
    bl GXGetScissor
    lhz r4, 0x68(r1)
    li r3, 0x0
    lhz r0, 0x6a(r1)
    stw r4, 0xa4(r1)
    lfs f2, 0x3c(r1)
    lfs f1, 0x34(r1)
    stw r0, 0xac(r1)
    fsubs f4, f2, f1
    lfs f3, 0x40(r1)
    lfs f0, 0x38(r1)
    lfd f2, lbl_81694C70(r0)
    fsubs f5, f3, f0
    lfd f1, 0xa0(r1)
    lfd f0, 0xa8(r1)
    fsubs f1, f1, f2
    lfs f3, lbl_81694C40(r0)
    fsubs f0, f0, f2
    fmuls f31, f3, f4
    fdivs f30, f1, f4
    fdivs f29, f0, f5
    fmuls f27, f3, f5
    bl setDefaultOrtho__Q33ipl7utility8GraphicsFUl
    lfs f2, 0x40(r1)
    lfs f1, 0x38(r1)
    lfs f0, lbl_81694C40(r0)
    fsubs f3, f2, f1
    lfs f2, 0x3c(r1)
    lfs f1, 0x34(r1)
    fmuls f0, f0, f3
    fsubs f28, f2, f1
    fmuls f1, f29, f0
    bl __cvt_fp2unsigned
    lfs f0, lbl_81694C40(r0)
    mr r27, r3
    fmuls f0, f0, f28
    fmuls f1, f30, f0
    bl __cvt_fp2unsigned
    lfs f2, lbl_81694C40(r0)
    mr r28, r3
    lfs f1, 0x38(r1)
    lfs f0, lbl_81694C64(r0)
    fmuls f1, f2, f1
    fadds f1, f1, f27
    fadds f0, f0, f1
    fmuls f1, f29, f0
    bl __cvt_fp2unsigned
    lfs f1, lbl_81694C40(r0)
    mr r29, r3
    lfs f0, 0x34(r1)
    fmuls f0, f1, f0
    fadds f0, f0, f31
    fmuls f1, f30, f0
    bl __cvt_fp2unsigned
    mr r4, r29
    mr r5, r28
    mr r6, r27
    bl GXSetScissor
    lbz r7, 0x20(r1)
    addi r3, r1, 0x34
    lbz r6, 0x21(r1)
    addi r4, r1, 0xc
    lbz r5, 0x22(r1)
    lbz r0, 0x23(r1)
    stb r7, 0xc(r1)
    stb r6, 0xd(r1)
    stb r5, 0xe(r1)
    stb r0, 0xf(r1)
    bl drawPolygon__Q33ipl7utility8GraphicsFRCQ34nw4r2ut4Rect8_GXColor
    bl getYoungController__Q23ipl6SystemFv
    cmpwi r3, 0x0
    mr r27, r3
    beq L_813F9F74
    lwz r12, 0x0(r3)
    lwz r12, 0x64(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0x0
    beq L_813F9F74
    lwz r3, 0xa0(r30)
    addi r4, r1, 0x44
    li r5, 0x1
    bl TPLGetGXTexObjFromPalette
    addi r3, r1, 0x44
    li r4, 0x2
    li r5, 0x2
    bl GXInitTexObjWrapMode
    lfs f1, 0x40(r1)
    mr r3, r27
    lfs f0, 0x38(r1)
    lwz r12, 0x0(r27)
    fsubs f1, f1, f0
    lfs f3, lbl_81694C40(r0)
    lfs f0, lbl_81694C44(r0)
    lfs f5, 0x3c(r1)
    fmuls f1, f3, f1
    lfs f4, 0x34(r1)
    lfs f2, lbl_81694C48(r0)
    fsubs f4, f5, f4
    lwz r12, 0x10(r12)
    fdivs f29, f1, f0
    fmuls f0, f3, f4
    fmuls f27, f0, f2
    mtctr r12
    bctrl
    bl WPADGetLatestIndexInBuf
    lwz r12, 0x0(r27)
    mr r29, r3
    mr r3, r27
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0x1
    beq L_813F9E48
    bge L_813F9E10
    cmpwi r3, 0x0
    bge L_813F9E1C
    b L_813F9E9C
    L_813F9E10:
    cmpwi r3, 0x3
    bge L_813F9E9C
    b L_813F9E74
    L_813F9E1C:
    lwz r12, 0x0(r27)
    mr r3, r27
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    bl KPADGetWPADRingBuffer
    mulli r0, r29, 0x2a
    add r3, r3, r0
    addi r31, r3, 0x20
    addi r30, r3, 0x8
    b L_813F9E9C
    L_813F9E48:
    lwz r12, 0x0(r27)
    mr r3, r27
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    bl KPADGetWPADFSRingBuffer
    mulli r0, r29, 0x32
    add r3, r3, r0
    addi r31, r3, 0x20
    addi r30, r3, 0x8
    b L_813F9E9C
    L_813F9E74:
    lwz r12, 0x0(r27)
    mr r3, r27
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    bl KPADGetWPADCLRingBuffer
    mulli r0, r29, 0x36
    add r3, r3, r0
    addi r31, r3, 0x20
    addi r30, r3, 0x8
    L_813F9E9C:
    lfd f28, lbl_81694C50(r0)
    lfs f31, lbl_81694C68(r0)
    lfs f30, lbl_81694C64(r0)
    L_813F9EA8:
    lhz r3, 0x4(r31)
    cmpwi r3, 0x0
    beq L_813F9F68
    addi r0, r3, 0x19
    lha r3, 0x2(r31)
    xoris r0, r0, 0x8000
    lha r4, 0x0(r31)
    stw r0, 0xa4(r1)
    subi r0, r3, 0x180
    subi r3, r4, 0x200
    lbz r5, lbl_81694C5C(r0)
    lfd f0, 0xa0(r1)
    xoris r8, r3, 0x8000
    xoris r0, r0, 0x8000
    stw r8, 0xac(r1)
    fsubs f2, f0, f28
    lbz r6, lbl_81694C5D(r0)
    stw r0, 0xa4(r1)
    addi r3, r1, 0x24
    lfd f1, 0xa8(r1)
    addi r4, r1, 0x44
    lfd f0, 0xa0(r1)
    fsubs f1, f1, f28
    lbz r7, lbl_81694C5E(r0)
    fmuls f4, f31, f2
    fsubs f0, f0, f28
    lbz r0, lbl_81694C5F(r0)
    fmuls f5, f1, f27
    stb r5, 0x8(r1)
    addi r5, r1, 0x8
    fmuls f0, f0, f29
    fsubs f3, f5, f4
    stb r6, 0x9(r1)
    li r6, 0x2
    fneg f0, f0
    stb r7, 0xa(r1)
    li r7, 0x0
    stb r0, 0xb(r1)
    fadds f1, f0, f4
    fsubs f0, f0, f4
    stfs f3, 0x24(r1)
    fsubs f2, f1, f30
    fadds f1, f5, f4
    fsubs f0, f0, f30
    stfs f2, 0x28(r1)
    stfs f1, 0x2c(r1)
    stfs f0, 0x30(r1)
    bl drawTexture__Q33ipl7utility8GraphicsFRCQ34nw4r2ut4RectRC9_GXTexObj8_GXColorUcQ43ipl7utility8Graphics11Orientation
    L_813F9F68:
    subi r31, r31, 0x8
    cmplw r31, r30
    bge L_813F9EA8
    L_813F9F74:
    lwz r3, 0x1c(r1)
    lwz r4, 0x18(r1)
    lwz r5, 0x14(r1)
    lwz r6, 0x10(r1)
    bl GXSetScissor
    psq_l f31, 0x118(r1), 0, 0
    lfd f31, 0x110(r1)
    psq_l f30, 0x108(r1), 0, 0
    lfd f30, 0x100(r1)
    psq_l f29, 0xf8(r1), 0, 0
    lfd f29, 0xf0(r1)
    psq_l f28, 0xe8(r1), 0, 0
    lfd f28, 0xe0(r1)
    psq_l f27, 0xd8(r1), 0, 0
    addi r11, r1, 0xd0
    lfd f27, 0xd0(r1)
    bl _restgpr_27
    lwz r0, 0x124(r1)
    mtlr r0
    addi r1, r1, 0x120
    blr
}
}
