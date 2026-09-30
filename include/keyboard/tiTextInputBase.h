#ifndef TEXTINPUT_BASE_H
#define TEXTINPUT_BASE_H

#include <revolution/types.h>

#include <revolution/mem/allocator.h>

#include <nw4r/ut/list.h>

namespace textinput {
    typedef enum Language {
        JP = 0,
        USA,
        UK,
        FR,
        DE,
        IT,
        SP,
        NL,
        CN,
        KR,

        LanguageEnd
    } Language;

    typedef enum Destination {
        DST_JP = 0,
        DST_US,
        DST_EU,
        DST_CN,
        DST_KR,

        DST_Last
    } Destination;

    typedef struct Scroll {
        bool absY;  // 0x00
        f32  x;     // 0x04
        f32  y;     // 0x08
    } Scroll;

#if defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
    enum HVKCode { HVK_None = 0 };
#endif

    class Base {
        public :
            virtual ~Base() {}

            virtual void    create(MEMAllocator* allocator);
            virtual void    init();
    };

    class CommandSender;
    class CommandReceiver : public Base {
        public:
#ifdef TI_CELLPHONE_IMPLEMENTATION
            struct ChangePredictMode;
#endif
#if defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
            CommandReceiver() { clearSender(); }
            virtual ~CommandReceiver();
#endif
#if defined(MYTIINPUTFORM_IMPLEMENTATION) || defined(MYTILETTERFORM_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
            struct Scroll {
                bool absY;
                f32 x;
                f32 y;
            };
#endif
            typedef enum INPUT_COMMAND {
                INPUT_COMMAND_0 = 0,
                INPUT_COMMAND_37 = 37,
            } INPUT_COMMAND;

#if (defined(TI_PC_KEYBOARD_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION)) || defined(TIMANAGER_IMPLEMENTATION) || defined(TISIGNWINDOW_IMPLEMENTATION)
            struct ChangePredictMode { u32 mode; bool enabled; };
#endif
            virtual void    clearSender();
            virtual void    onCommand(INPUT_COMMAND command, void* data);
            virtual void    addSender(CommandSender* cmdSend);

        private:
            nw4r::ut::List  mSenderList;    // 0x04
    };

    class CommandSender : public Base {
        public:
            CommandSender() : mpCommandReceiver(NULL) {}

            virtual void    setCommandReceiver(CommandReceiver* cmdRecv);
            #if (defined(TI_PC_KEYBOARD_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION)) || defined(TIMANAGER_IMPLEMENTATION)
            virtual void sendCommand(u32 command, void* data) {
                if (mpCommandReceiver != NULL) mpCommandReceiver->onCommand(static_cast<CommandReceiver::INPUT_COMMAND>(command), data);
            }
#else
            virtual void    sendCommand(u32, void*);
#endif
            virtual void    updateFromReceiver(u32, void*) {}

            nw4r::ut::Link      mLink;              // 0x00

        private:
            CommandReceiver*    mpCommandReceiver;  // 0x08
    };
}

#endif // TEXTINPUT_BASE_H
