.include "macros.inc"
.file "eggAudioExpMgr.cpp"

# 0x815F6150..0x815F635C | size: 0x20C
.text
.balign 4

# .text:0x0 | 0x815F6150 | size: 0x54
# EGG::SimpleAudioMgrWithFx::SimpleAudioMgrWithFx()
.fn __ct__Q23EGG20SimpleAudioMgrWithFxFv, global
/* 815F6150 002C6670  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 815F6154 002C6674  7C 08 02 A6 */	mflr r0
/* 815F6158 002C6678  90 01 00 14 */	stw r0, 0x14(r1)
/* 815F615C 002C667C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 815F6160 002C6680  7C 7F 1B 78 */	mr r31, r3
/* 815F6164 002C6684  48 00 0B 39 */	bl __ct__Q23EGG14SimpleAudioMgrFv
/* 815F6168 002C6688  38 7F 05 D8 */	addi r3, r31, 0x5d8
/* 815F616C 002C668C  48 00 09 55 */	bl __ct__Q23EGG10AudioFxMgrFv
/* 815F6170 002C6690  3C A0 81 69 */	lis r5, __vt__Q23EGG20SimpleAudioMgrWithFx@ha
/* 815F6174 002C6694  7F E3 FB 78 */	mr r3, r31
/* 815F6178 002C6698  38 A5 34 A8 */	addi r5, r5, __vt__Q23EGG20SimpleAudioMgrWithFx@l
/* 815F617C 002C669C  38 85 00 10 */	addi r4, r5, 0x10
/* 815F6180 002C66A0  90 BF 00 00 */	stw r5, 0x0(r31)
/* 815F6184 002C66A4  38 05 00 20 */	addi r0, r5, 0x20
/* 815F6188 002C66A8  90 9F 00 04 */	stw r4, 0x4(r31)
/* 815F618C 002C66AC  90 1F 00 34 */	stw r0, 0x34(r31)
/* 815F6190 002C66B0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 815F6194 002C66B4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 815F6198 002C66B8  7C 08 03 A6 */	mtlr r0
/* 815F619C 002C66BC  38 21 00 10 */	addi r1, r1, 0x10
/* 815F61A0 002C66C0  4E 80 00 20 */	blr
.endfn __ct__Q23EGG20SimpleAudioMgrWithFxFv

# .text:0x54 | 0x815F61A4 | size: 0x68
# EGG::SimpleAudioMgrWithFx::~SimpleAudioMgrWithFx()
.fn __dt__Q23EGG20SimpleAudioMgrWithFxFv, global
/* 815F61A4 002C66C4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 815F61A8 002C66C8  7C 08 02 A6 */	mflr r0
/* 815F61AC 002C66CC  2C 03 00 00 */	cmpwi r3, 0x0
/* 815F61B0 002C66D0  90 01 00 14 */	stw r0, 0x14(r1)
/* 815F61B4 002C66D4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 815F61B8 002C66D8  7C 9F 23 78 */	mr r31, r4
/* 815F61BC 002C66DC  93 C1 00 08 */	stw r30, 0x8(r1)
/* 815F61C0 002C66E0  7C 7E 1B 78 */	mr r30, r3
/* 815F61C4 002C66E4  41 82 00 2C */	beq .L_815F61F0
/* 815F61C8 002C66E8  38 80 00 00 */	li r4, 0x0
/* 815F61CC 002C66EC  38 63 05 D8 */	addi r3, r3, 0x5d8
/* 815F61D0 002C66F0  48 00 09 39 */	bl __dt__Q23EGG10AudioFxMgrFv
/* 815F61D4 002C66F4  7F C3 F3 78 */	mr r3, r30
/* 815F61D8 002C66F8  38 80 00 00 */	li r4, 0x0
/* 815F61DC 002C66FC  48 00 0B D5 */	bl __dt__Q23EGG14SimpleAudioMgrFv
/* 815F61E0 002C6700  2C 1F 00 00 */	cmpwi r31, 0x0
/* 815F61E4 002C6704  40 81 00 0C */	ble .L_815F61F0
/* 815F61E8 002C6708  7F C3 F3 78 */	mr r3, r30
/* 815F61EC 002C670C  48 00 1E F9 */	bl __dl__FPv
.L_815F61F0:
/* 815F61F0 002C6710  7F C3 F3 78 */	mr r3, r30
/* 815F61F4 002C6714  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 815F61F8 002C6718  83 C1 00 08 */	lwz r30, 0x8(r1)
/* 815F61FC 002C671C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 815F6200 002C6720  7C 08 03 A6 */	mtlr r0
/* 815F6204 002C6724  38 21 00 10 */	addi r1, r1, 0x10
/* 815F6208 002C6728  4E 80 00 20 */	blr
.endfn __dt__Q23EGG20SimpleAudioMgrWithFxFv

# .text:0xBC | 0x815F620C | size: 0x48
# EGG::SimpleAudioMgrWithFx::ArgWithFx::ArgWithFx()
.fn __ct__Q33EGG20SimpleAudioMgrWithFx9ArgWithFxFv, global
/* 815F620C 002C672C  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 815F6210 002C6730  7C 08 02 A6 */	mflr r0
/* 815F6214 002C6734  90 01 00 44 */	stw r0, 0x44(r1)
/* 815F6218 002C6738  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 815F621C 002C673C  7C 7F 1B 78 */	mr r31, r3
/* 815F6220 002C6740  48 00 0A 41 */	bl __ct__Q33EGG14SimpleAudioMgr17SimpleAudioMgrArgFv
/* 815F6224 002C6744  38 7F 00 18 */	addi r3, r31, 0x18
/* 815F6228 002C6748  48 00 00 2D */	bl __ct__Q33EGG10AudioFxMgr13AudioFxMgrArgFv
/* 815F622C 002C674C  38 61 00 14 */	addi r3, r1, 0x14
/* 815F6230 002C6750  48 00 0A 31 */	bl __ct__Q33EGG14SimpleAudioMgr17SimpleAudioMgrArgFv
/* 815F6234 002C6754  38 61 00 08 */	addi r3, r1, 0x8
/* 815F6238 002C6758  48 00 00 1D */	bl __ct__Q33EGG10AudioFxMgr13AudioFxMgrArgFv
/* 815F623C 002C675C  7F E3 FB 78 */	mr r3, r31
/* 815F6240 002C6760  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 815F6244 002C6764  80 01 00 44 */	lwz r0, 0x44(r1)
/* 815F6248 002C6768  7C 08 03 A6 */	mtlr r0
/* 815F624C 002C676C  38 21 00 40 */	addi r1, r1, 0x40
/* 815F6250 002C6770  4E 80 00 20 */	blr
.endfn __ct__Q33EGG20SimpleAudioMgrWithFx9ArgWithFxFv

# .text:0x104 | 0x815F6254 | size: 0x24
# EGG::AudioFxMgr::AudioFxMgrArg::AudioFxMgrArg()
.fn __ct__Q33EGG10AudioFxMgr13AudioFxMgrArgFv, global
/* 815F6254 002C6774  3C 80 00 02 */	lis r4, 0x2
/* 815F6258 002C6778  38 00 00 03 */	li r0, 0x3
/* 815F625C 002C677C  38 A4 58 00 */	addi r5, r4, 0x5800
/* 815F6260 002C6780  38 80 00 00 */	li r4, 0x0
/* 815F6264 002C6784  7C 09 03 A6 */	mtctr r0
.L_815F6268:
/* 815F6268 002C6788  7C A3 21 2E */	stwx r5, r3, r4
/* 815F626C 002C678C  38 84 00 04 */	addi r4, r4, 0x4
/* 815F6270 002C6790  42 00 FF F8 */	bdnz .L_815F6268
/* 815F6274 002C6794  4E 80 00 20 */	blr
.endfn __ct__Q33EGG10AudioFxMgr13AudioFxMgrArgFv

# .text:0x128 | 0x815F6278 | size: 0x84
# EGG::SimpleAudioMgrWithFx::initialize(EGG::IAudioMgr::Arg*)
.fn initialize__Q23EGG20SimpleAudioMgrWithFxFPQ33EGG9IAudioMgr3Arg, global
/* 815F6278 002C6798  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 815F627C 002C679C  7C 08 02 A6 */	mflr r0
/* 815F6280 002C67A0  90 01 00 14 */	stw r0, 0x14(r1)
/* 815F6284 002C67A4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 815F6288 002C67A8  7C 9F 23 78 */	mr r31, r4
/* 815F628C 002C67AC  93 C1 00 08 */	stw r30, 0x8(r1)
/* 815F6290 002C67B0  7C 7E 1B 78 */	mr r30, r3
/* 815F6294 002C67B4  48 00 0B 85 */	bl initialize__Q23EGG14SimpleAudioMgrFPQ33EGG9IAudioMgr3Arg
/* 815F6298 002C67B8  2C 1F 00 00 */	cmpwi r31, 0x0
/* 815F629C 002C67BC  41 82 00 08 */	beq .L_815F62A4
/* 815F62A0 002C67C0  3B FF 00 18 */	addi r31, r31, 0x18
.L_815F62A4:
/* 815F62A4 002C67C4  7F E5 FB 78 */	mr r5, r31
/* 815F62A8 002C67C8  38 7E 05 D8 */	addi r3, r30, 0x5d8
/* 815F62AC 002C67CC  38 9E 00 08 */	addi r4, r30, 0x8
/* 815F62B0 002C67D0  48 00 08 BD */	bl initializeFx__Q23EGG10AudioFxMgrFPQ34nw4r3snd9SoundHeapPQ33EGG10AudioFxMgr13AudioFxMgrArg
/* 815F62B4 002C67D4  48 00 09 75 */	bl getDefaultFxReverbHi__Q23EGG10AudioFxMgrFv
/* 815F62B8 002C67D8  7C 65 1B 78 */	mr r5, r3
/* 815F62BC 002C67DC  38 7E 05 D8 */	addi r3, r30, 0x5d8
/* 815F62C0 002C67E0  38 80 00 00 */	li r4, 0x0
/* 815F62C4 002C67E4  48 00 09 45 */	bl setFxReverbHi__Q23EGG10AudioFxMgrFQ34nw4r3snd6AuxBusPCQ44nw4r3snd10FxReverbHi13ReverbHiParam
/* 815F62C8 002C67E8  48 00 09 6D */	bl getDefaultFxChorus__Q23EGG10AudioFxMgrFv
/* 815F62CC 002C67EC  7C 65 1B 78 */	mr r5, r3
/* 815F62D0 002C67F0  38 7E 05 D8 */	addi r3, r30, 0x5d8
/* 815F62D4 002C67F4  38 80 00 01 */	li r4, 0x1
/* 815F62D8 002C67F8  48 00 09 41 */	bl setFxChorus__Q23EGG10AudioFxMgrFQ34nw4r3snd6AuxBusPCQ44nw4r3snd8FxChorus11ChorusParam
/* 815F62DC 002C67FC  38 7E 00 08 */	addi r3, r30, 0x8
/* 815F62E0 002C6800  48 00 00 1D */	bl SaveState__Q34nw4r3snd9SoundHeapFv
/* 815F62E4 002C6804  80 01 00 14 */	lwz r0, 0x14(r1)
/* 815F62E8 002C6808  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 815F62EC 002C680C  83 C1 00 08 */	lwz r30, 0x8(r1)
/* 815F62F0 002C6810  7C 08 03 A6 */	mtlr r0
/* 815F62F4 002C6814  38 21 00 10 */	addi r1, r1, 0x10
/* 815F62F8 002C6818  4E 80 00 20 */	blr
.endfn initialize__Q23EGG20SimpleAudioMgrWithFxFPQ33EGG9IAudioMgr3Arg

# .text:0x1AC | 0x815F62FC | size: 0x50
# nw4r::snd::SoundHeap::SaveState()
.fn SaveState__Q34nw4r3snd9SoundHeapFv, global
/* 815F62FC 002C681C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 815F6300 002C6820  7C 08 02 A6 */	mflr r0
/* 815F6304 002C6824  90 01 00 24 */	stw r0, 0x24(r1)
/* 815F6308 002C6828  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 815F630C 002C682C  7C 7F 1B 78 */	mr r31, r3
/* 815F6310 002C6830  38 61 00 08 */	addi r3, r1, 0x8
/* 815F6314 002C6834  38 9F 00 04 */	addi r4, r31, 0x4
/* 815F6318 002C6838  4B D7 5F 91 */	bl "__ct__Q44nw4r2ut6detail18AutoLock<7OSMutex>FR7OSMutex"
/* 815F631C 002C683C  38 7F 00 1C */	addi r3, r31, 0x1c
/* 815F6320 002C6840  4B F0 97 11 */	bl SaveState__Q44nw4r3snd6detail9FrameHeapFv
/* 815F6324 002C6844  7C 7F 1B 78 */	mr r31, r3
/* 815F6328 002C6848  38 61 00 08 */	addi r3, r1, 0x8
/* 815F632C 002C684C  38 80 FF FF */	li r4, -0x1
/* 815F6330 002C6850  4B D7 5F B1 */	bl "__dt__Q44nw4r2ut6detail18AutoLock<7OSMutex>Fv"
/* 815F6334 002C6854  7F E3 FB 78 */	mr r3, r31
/* 815F6338 002C6858  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 815F633C 002C685C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 815F6340 002C6860  7C 08 03 A6 */	mtlr r0
/* 815F6344 002C6864  38 21 00 20 */	addi r1, r1, 0x20
/* 815F6348 002C6868  4E 80 00 20 */	blr
.endfn SaveState__Q34nw4r3snd9SoundHeapFv

# .text:0x1FC | 0x815F634C | size: 0x8
.fn "@52@__dt__Q23EGG20SimpleAudioMgrWithFxFv", global
/* 815F634C 002C686C  38 63 FF CC */	subi r3, r3, 0x34
/* 815F6350 002C6870  4B FF FE 54 */	b __dt__Q23EGG20SimpleAudioMgrWithFxFv
.endfn "@52@__dt__Q23EGG20SimpleAudioMgrWithFxFv"

# .text:0x204 | 0x815F6354 | size: 0x8
# EGG::SimpleAudioMgr::@52@calc()
.fn "@52@calc__Q23EGG14SimpleAudioMgrFv", global
/* 815F6354 002C6874  38 63 FF CC */	subi r3, r3, 0x34
/* 815F6358 002C6878  48 00 0B 4C */	b calc__Q23EGG14SimpleAudioMgrFv
.endfn "@52@calc__Q23EGG14SimpleAudioMgrFv"

# 0x816934A8..0x81693520 | size: 0x78
.data
.balign 8

# .data:0x0 | 0x816934A8 | size: 0x78
# EGG::SimpleAudioMgrWithFx::__vtable
.obj __vt__Q23EGG20SimpleAudioMgrWithFx, global
	.4byte 0x00000000
	.4byte 0x00000000
	.4byte initialize__Q23EGG20SimpleAudioMgrWithFxFPQ33EGG9IAudioMgr3Arg
	.4byte calc__Q23EGG14SimpleAudioMgrFv
	.4byte 0x00000000
	.4byte 0x00000000
	.4byte loadState__Q23EGG12SoundHeapMgrFl
	.4byte getCurrentLevel__Q23EGG12SoundHeapMgrFv
	.4byte 0x00000000
	.4byte 0x00000000
	.4byte "@52@__dt__Q23EGG20SimpleAudioMgrWithFxFv"
	.4byte openArchive__Q23EGG9ArcPlayerFPCcPQ34nw4r3snd9SoundHeapQ23EGG12SARC_STORAGE
	.4byte openDvdArchive__Q23EGG9ArcPlayerFPCcPQ34nw4r3snd9SoundHeap
	.4byte openNandArchive__Q23EGG9ArcPlayerFPCcPQ34nw4r3snd9SoundHeap
	.4byte setupMemoryArchive__Q23EGG9ArcPlayerFPCvPQ34nw4r3snd9SoundHeap
	.4byte closeArchive__Q23EGG9ArcPlayerFv
	.4byte loadGroup__Q23EGG9ArcPlayerFUiPQ34nw4r3snd9SoundHeap
	.4byte loadGroup__Q23EGG9ArcPlayerFiPQ34nw4r3snd9SoundHeap
	.4byte loadGroup__Q23EGG9ArcPlayerFPCcPQ34nw4r3snd9SoundHeap
	.4byte "@52@calc__Q23EGG14SimpleAudioMgrFv"
	.4byte startSound__Q23EGG9ArcPlayerFPQ34nw4r3snd11SoundHandleUl
	.4byte startSound__Q23EGG9ArcPlayerFPQ34nw4r3snd11SoundHandleUi
	.4byte startSound__Q23EGG9ArcPlayerFPQ34nw4r3snd11SoundHandlePCc
	.4byte prepareSound__Q23EGG9ArcPlayerFPQ34nw4r3snd11SoundHandleUl
	.4byte prepareSound__Q23EGG9ArcPlayerFPQ34nw4r3snd11SoundHandleUi
	.4byte prepareSound__Q23EGG9ArcPlayerFPQ34nw4r3snd11SoundHandlePCc
	.4byte holdSound__Q23EGG9ArcPlayerFPQ34nw4r3snd11SoundHandleUl
	.4byte holdSound__Q23EGG9ArcPlayerFPQ34nw4r3snd11SoundHandleUi
	.4byte holdSound__Q23EGG9ArcPlayerFPQ34nw4r3snd11SoundHandlePCc
	.4byte __dt__Q23EGG20SimpleAudioMgrWithFxFv
.endobj __vt__Q23EGG20SimpleAudioMgrWithFx
