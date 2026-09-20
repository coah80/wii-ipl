#include "system/iplException.h"

#include <revolution/kpad.h>

#include <nw4r/ut.h>

#include <cstring>

namespace ipl {
    // clang-format off
    static const u32 sKeyInputs[8] = {
        // Left, down, down, 1, -, 2, +, down
        WPAD_BUTTON_LEFT,
        WPAD_BUTTON_DOWN,
        WPAD_BUTTON_DOWN,
        WPAD_BUTTON_1,   
        WPAD_BUTTON_MINUS,
        WPAD_BUTTON_2,   
        WPAD_BUTTON_PLUS,
        WPAD_BUTTON_DOWN,
    };
    // clang-format on

#define LINES_ON_SCREEN_OFFSET 4
#define LINES_ON_SCREEN_WIDTH 24
#define LINES_ON_SCREEN_HEIGHT 18

#define FONT_WIDTH 46
#define FONT_HEIGHT 48

    bool exception_callback_(nw4r::db::ConsoleHandle console, void* param) {
        Exception* exception = ((Exception*)param);
        exception->exception_callback(console);
    }

    Exception::Exception(EGG::Heap* heap, const GXRenderModeObj& rMode) : mConsole(NULL), unk_0x04(0), mpBuffer(), unk_0x0C(0) {
        nw4r::db::Exception_Init();
        nw4r::db::DirectPrint_Init();

        mpBuffer = new (heap, 4) u8[NW4R_CONSOLE_BUFFER_SIZE(FONT_WIDTH, FONT_HEIGHT)];
        mConsole = nw4r::db::Console_Create(mpBuffer, FONT_WIDTH, FONT_HEIGHT, 18, 0, 4);

        setConsole(rMode);

        nw4r::db::Exception_SetUserCallback(exception_callback_, this);
    }

    void Exception::setConsole(const GXRenderModeObj& rMode) {
        nw4r::db::Exception_SetConsole(mConsole, &rMode);
        nw4r::db::Console_SetVisible(mConsole, false);

        nw4r::db::ConsoleHandle handle = mConsole;
        // Using Console_SetPosition turns it into a weak...
        handle->viewPosX = 14;
        handle->viewPosY = 30;
    }

    void Exception::key_input() {
        KPADStatus cons[WPAD_MAX_CONTROLLERS];
        memset(cons, 0, sizeof(cons));

        int inputCur = 0;

        OSEnableInterrupts();

        while (inputCur < (int)ARRAY_LENGTH(sKeyInputs)) {
            for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
                KPADRead(i, &cons[i], 1);
            }

            wait(50);

            for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
                u32 pressed = cons[i].trig;
                if (pressed) {
                    if (pressed & sKeyInputs[inputCur]) {
                        inputCur++;
                    } else {
                        inputCur = 0;
                    }
                    break;
                }
            }
        }
    }

    
#ifdef __MWERKS__
    extern "C" void _savegpr_23();
    extern "C" void key_input__Q23ipl9ExceptionFv();
    extern "C" void wait__Q23ipl9ExceptionFUl();
    extern "C" s32 Console_GetTotalLines__Q24nw4r2dbFPQ44nw4r2db6detail11ConsoleHead();
    extern "C" void Console_DrawDirect__Q24nw4r2dbFPQ44nw4r2db6detail11ConsoleHead();

    asm void Exception::exception_callback(register nw4r::db::ConsoleHandle console) {
        nofralloc

        stwu r1, -0x240(r1)
        mflr r0
        stw r0, 0x244(r1)
        addi r11, r1, 0x240
        bl _savegpr_23
        li r0, 1
        mr r28, r3
        stb r0, 0x22(r4)
        lwz r3, 0(r3)
        lwz r26, 0x14(r3)
        bl Console_GetTotalLines__Q24nw4r2dbFPQ44nw4r2db6detail11ConsoleHead
        subi r30, r3, 0x12
        mr r3, r28
        bl key_input__Q23ipl9ExceptionFv
        b Exception_exception_callback_L1
    Exception_exception_callback_L2:
        lwz r3, 0(r28)
        stw r26, 0x18(r3)
        lwz r3, 0(r28)
        bl Console_DrawDirect__Q24nw4r2dbFPQ44nw4r2db6detail11ConsoleHead
        mr r3, r28
        li r4, 0xfa
        bl wait__Q23ipl9ExceptionFUl
        addi r26, r26, 1
    Exception_exception_callback_L1:
        cmpw r26, r30
        ble Exception_exception_callback_L2
        lwz r3, 0(r28)
        li r31, 0
        stw r31, 0x18(r3)
        lwz r3, 0(r28)
        bl Console_DrawDirect__Q24nw4r2dbFPQ44nw4r2db6detail11ConsoleHead
        bl OSEnableInterrupts
        addi r3, r1, 8
        li r4, 0
        li r5, 0x210
        bl memset
        li r27, 4
    Exception_exception_callback_L3:
        lwz r3, 0(r28)
        mr r25, r31
        li r23, 0
        li r26, 0
        lha r29, 0x1c(r3)
        mr r24, r29
    Exception_exception_callback_L4:
        addi r4, r1, 8
        mr r3, r23
        add r4, r4, r26
        li r5, 1
        bl KPADRead
        addi r23, r23, 1
        addi r26, r26, 0x84
        cmpwi r23, 4
        blt Exception_exception_callback_L4
        mr r3, r28
        li r4, 0x32
        bl wait__Q23ipl9ExceptionFUl
        li r3, 0
        mtctr r27
    Exception_exception_callback_L5:
        addi r4, r1, 8
        add r4, r4, r3
        lbz r0, 0x5d(r4)
        extsb. r0, r0
        bne Exception_exception_callback_L6
        lwz r4, 0(r4)
        rlwinm. r0, r4, 0, 28, 28
        beq Exception_exception_callback_L7
        cmpwi r31, 0
        ble Exception_exception_callback_L7
        subi r31, r31, 1
        b Exception_exception_callback_L6
    Exception_exception_callback_L7:
        rlwinm. r0, r4, 0, 29, 29
        beq Exception_exception_callback_L8
        cmpw r31, r30
        bge Exception_exception_callback_L8
        addi r31, r31, 1
        b Exception_exception_callback_L6
    Exception_exception_callback_L8:
        rlwinm. r0, r4, 0, 30, 30
        beq Exception_exception_callback_L9
        cmpwi r29, 4
        ble Exception_exception_callback_L9
        subi r29, r29, 2
        b Exception_exception_callback_L6
    Exception_exception_callback_L9:
        clrlwi. r0, r4, 31
        beq Exception_exception_callback_L6
        cmpwi r29, 0x18
        bge Exception_exception_callback_L6
        addi r29, r29, 2
    Exception_exception_callback_L6:
        addi r3, r3, 0x84
        bdnz Exception_exception_callback_L5
        cmpw r31, r25
        bne Exception_exception_callback_L10
        cmpw r29, r24
        beq Exception_exception_callback_L3
    Exception_exception_callback_L10:
        lwz r3, 0(r28)
        sth r29, 0x1c(r3)
        lwz r3, 0(r28)
        stw r31, 0x18(r3)
        lwz r3, 0(r28)
        bl Console_DrawDirect__Q24nw4r2dbFPQ44nw4r2db6detail11ConsoleHead
        b Exception_exception_callback_L3
    }
#else
    void Exception::exception_callback(nw4r::db::ConsoleHandle console) {
        nw4r::db::Console_SetVisible(console, true);

        s32 line = nw4r::db::Console_GetBufferHeadLine(mConsole);
        s32 lineScrollMax = nw4r::db::Console_GetTotalLines(mConsole) - LINES_ON_SCREEN_HEIGHT;

        key_input();  // Wait until they pressed key input

        // Scroll through the exception.
        for (; line <= lineScrollMax; line++) {
            nw4r::db::Console_SetViewBaseLine(mConsole, line);
            nw4r::db::Console_DrawDirect(mConsole);
            wait(250);
        }

        // Go back to the first line
        int yCur = 0;
        nw4r::db::Console_SetViewBaseLine(mConsole, 0);
        nw4r::db::Console_DrawDirect(mConsole);

        OSEnableInterrupts();

        // Setup controllers
        KPADStatus cons[WPAD_MAX_CONTROLLERS];
        memset(cons, 0, sizeof(cons));

        while (true) {
            int xCur = nw4r::db::Console_GetPositionX(mConsole);
            int yPrevCur = yCur;
            int xPrevCur = xCur;

            // Read controllers
            for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
                KPADRead(i, &cons[i], 1);
            }

            wait(50);

            int chan = 0;
            for (int i = WPAD_MAX_CONTROLLERS; i != 0; i--) {
                if (cons[chan].wpad_err == 0) {
                    u32 held = cons[chan].hold;

                    // Scroll depending on what the user presses
                    if ((held & WPAD_BUTTON_UP) && yCur > 0) {
                        yCur--;
                    } else if ((held & WPAD_BUTTON_DOWN) && yCur < lineScrollMax) {
                        yCur++;
                    } else if ((held & WPAD_BUTTON_RIGHT) && xCur > LINES_ON_SCREEN_OFFSET) {
                        xCur -= 2;
                    } else if ((held & WPAD_BUTTON_LEFT) && xCur < LINES_ON_SCREEN_WIDTH) {
                        xCur += 2;
                    }
                }
                chan++;
            }

            // Refresh screen
            if (yCur != yPrevCur || xCur != xPrevCur) {
                nw4r::db::Console_SetPosition(mConsole, xCur, nw4r::db::Console_GetPositionY(mConsole));
                nw4r::db::Console_SetViewBaseLine(mConsole, yCur);
                nw4r::db::Console_DrawDirect(mConsole);
            }
        }
    }
#endif

    void Exception::wait(u32 tick) {
        OSTick prevTick = OSGetTick();
        while (OSTicksToMilliseconds(OSDiffTick(OSGetTick(), prevTick)) < tick) {
            // do nothing until it finished
        }
    }
}  // namespace ipl

extern "C" __declspec(weak) nw4r::ut::Color& __as__Q34nw4r2ut5ColorFRCQ34nw4r2ut5Color(nw4r::ut::Color& dst,
                                                                                         const nw4r::ut::Color& src) {
    dst.r = src.r;
    dst.g = src.g;
    dst.b = src.b;
    dst.a = src.a;
    return dst;
}
