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

                    InputForm(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* resAccessor, const char* arcName,
                              EventObserver* observer, const char* subName)
                        : MemoInputForm(manager, resAccessor, arcName, observer, subName),
                          mbPhotoScaledUp(false), mbPhotoDraw(false), meType(T_MailAddressSel) {}

                    ~InputForm();

                    virtual void                    create(MEMAllocator* allocator, inputform::EditBuffer* editBuffer);
                    virtual void                    drawBody();
                    virtual void                    drawFooter();
                    virtual void                    open();
                    virtual void                    close();
                    virtual bool                    isWholePaneInAnimation();

                    virtual nw4r::lyt::Material*    getPhotoPaneMaterial();

                    virtual void                    onPhotoTrig();
                    virtual void                    onPhotoPoint();
                    virtual void                    onPhotoLeft();
                    virtual bool                    isPhotoScaledUp();
                    virtual void                    setPhotoDraw(bool photoDraw);

                    virtual void                    setType(Type type);

                    virtual void                    setSendOutMessage(const wchar_t* sendOutMessage);

                    void                            resizePhotoPane(f32 width, f32 height);

                private:
                    bool    mbPhotoScaledUp; // 0x400
                    bool    mbPhotoDraw;    // 0x401
                    Type    meType;         // 0x404
            };
        }
    }
    typedef extend::letter::InputForm LetterInputForm;
}

#endif // TEXTINPUT_MY_LETTER_FORM_H
