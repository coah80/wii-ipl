#ifndef TEXTINPUT_MY_LETTER_FORM_H
#define TEXTINPUT_MY_LETTER_FORM_H

#include "MyTiInputForm.h"

namespace textinput {
    namespace extend {
        namespace letter {
            class InputForm : public textinput::MemoInputForm {
                public:
                    typedef enum Type {
                        T_MailAddressSel = 0,
                        T_Address,
                        T_Picture,
                        T_Reply,
                        T_Last,
                    } Type;

#ifdef MYTIMANAGER_IMPLEMENTATION
                    InputForm(textinput::Manager* manager, nw4r::lyt::MultiArcResourceAccessor* multiArc,
                              const char* layoutName, EventObserver* event, const char* fontName)
                        : textinput::MemoInputForm(manager, multiArc, layoutName, event, fontName),
                          mbPhotoScaledUp(0), mbPhotoDraw(false), meType(T_MailAddressSel) {}
#endif

#ifdef MYTILETTERFORM_IMPLEMENTATION
                    virtual ~InputForm();
                    virtual void create(MEMAllocator*, inputform::EditBuffer*);
                    virtual void drawBody();
                    virtual void drawFooter();
                    virtual void open();
                    virtual void close();
                    virtual bool isWholePaneInAnimation();
#endif
                    virtual nw4r::lyt::Material*    getPhotoPaneMaterial();

                    virtual void                    onPhotoTrig();
                    virtual void                    onPhotoPoint();
                    virtual void                    onPhotoLeft();
                    virtual bool                    isPhotoScaledUp();
                    virtual void                    setPhotoDraw(bool photoDraw)   { mbPhotoDraw = photoDraw; }

                    virtual void                    setType(Type type)             { meType = type; }

                    virtual void                    setSendOutMessage(const wchar_t* sendOutMessage);

                    void                            resizePhotoPane(f32 width, f32 height);

                private:
#ifdef MYTILETTERFORM_IMPLEMENTATION
                    bool mbPhotoScaledUp;
#else
                    u8      mbPhotoScaledUp;
#endif
                    bool    mbPhotoDraw;    // 0x401
                    Type    meType;         // 0x404
            };
        }
    }
    typedef extend::letter::InputForm LetterInputForm;
}

#endif // TEXTINPUT_MY_LETTER_FORM_H
