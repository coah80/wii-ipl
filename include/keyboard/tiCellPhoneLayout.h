#ifndef TEXTINPUT_CELL_PHONE_LAYOUT_H
#define TEXTINPUT_CELL_PHONE_LAYOUT_H

            class LayoutByNW4R : public Base, public nw4rmanager::Layout {
            public:
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
#ifdef TIMANAGER_IMPLEMENTATION
                LayoutByNW4R(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* accessor, EventObserver* observer, const char* layoutName)
                    : Base(manager), nw4rmanager::Layout(accessor, layoutName, observer), mpEventHandler(NULL) {}
                virtual ~LayoutByNW4R();
                virtual void create(MEMAllocator* allocator);
                virtual void init();
                virtual void setCommandReceiver(CommandReceiver* receiver);
                virtual void updateFromReceiver(u32 command, void* data);
                virtual void onKey(u32 event, void* data);
                virtual void setLanguage(Language language);
                virtual void update();
                virtual void onActive();
                virtual void calc();
                virtual void draw();
                virtual void changeInputMode(InputMode mode);
                virtual void setInputMode(InputMode mode);
                virtual void setUpperCaseJP(bool upper);
                virtual void setLangKeyActive(bool active);
                virtual void goSignInputMode();
                virtual void changePredictLanguage();
                virtual void setAbcMode(bool abc);
                virtual void doNumericMode(bool);
                virtual void setPredictLanguageDialog(predictlang::LayoutByNW4R* dialog);
                virtual void setSignWindow(signwindow::LayoutByNW4R* window);
#else
#if defined(MYTIMANAGER_IMPLEMENTATION) && defined(TI_CELLPHONE_SAMPLE_CLASS)
                LayoutByNW4R(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* resAccessor, EventObserver* observer)
                    : Base(manager), nw4rmanager::Layout(resAccessor, "fs_VK_cellPhone_a.brlyt", observer), mpSignWindow(NULL) {}
#endif
                virtual void doNumericMode(bool);
#ifdef TI_CELLPHONE_IMPLEMENTATION
                virtual void setPredictLanguageDialog(predictlang::LayoutByNW4R*);
                virtual void setSignWindow(signwindow::LayoutByNW4R*);
#else
                virtual void setPredictLanguageDialog(void*);
                virtual void setSignWindow(void*);
#endif
#endif
                virtual void doNumericWithDotMode(bool);
                virtual void setLineFeedButton(bool);
                virtual void setPredictLanguageButton(bool);
                virtual void setSignWindowButton(bool);
#endif
                virtual bool onClose();

                void onPressedShift(bool shift);
                void onReleasedShift();
#if defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
                bool hasLineFeedButton() const { return mbLineFeedButton; }
            private:
                bool mbLineFeedButton;
#ifdef TIMANAGER_IMPLEMENTATION
                GXTexObj mSpaceTexture;
                GXTexObj mSpaceTextureCN;
                GXTexObj mSpaceTextureKR;
                nw4rmanager::TiEventHandler* mpEventHandler;
                predictlang::LayoutByNW4R* mpPredictDialog;
                signwindow::LayoutByNW4R* mpSignWindow;
#endif
            public:
#endif
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
                virtual bool updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data) override;
                virtual bool updateInput(input::HKBManager& hkbManager) override;
#endif
#ifdef TI_CELLPHONE_IMPLEMENTATION
                virtual ~LayoutByNW4R();
                virtual void create(MEMAllocator* allocator) override;
                virtual void init() override;
                virtual void draw() override;
                virtual void calc() override;
                virtual void update() override;
                virtual void onKey(u32 key, void* data) override;
                virtual void onActive() override;
                virtual void updateFromReceiver(u32 command, void* data) override;
                virtual void changeInputMode(InputMode mode) override;
                virtual void changePredictLanguage() override;
                virtual void setAbcMode(bool enabled) override;
                virtual void goSignInputMode() override;
                virtual void setInputMode(InputMode mode) override;
                virtual void setLanguage(Language language) override;
                virtual void setCommandReceiver(CommandReceiver* receiver) override;

                virtual CellPhoneAnmPane* getAnmPane(InputMode mode);
                virtual void throwReleaseForAll();
                virtual void changeAnimationAllToNormal();
                virtual void updatePredictLanguage(CommandReceiver::ChangePredictMode* mode);
                virtual void changeKeyTop(const PaneNameToCharCode* keys);
                virtual void changeSpaceKeyTop(const PaneNameToCharCode* keys);
                void setUpperCaseJP(bool enabled);
                void setLangKeyActive(bool enabled);
                void resetHoldingButton();

            private:
                bool mbLineFeedButton;
                GXTexObj mTextures[3];
                EventHandler* mpEventHandler;
                predictlang::LayoutByNW4R* mpPredictLanguageDialog;
                signwindow::LayoutByNW4R* mpSignWindow;
#elif defined(TIMANAGER_IMPLEMENTATION)
                virtual nw4rmanager::AnmPane* getAnmPane(InputMode mode);
                virtual void throwReleaseForAll();
                virtual void changeAnimationAllToNormal();
                virtual void updatePredictLanguage(CommandReceiver::ChangePredictMode* mode);
                virtual void changeKeyTop(const struct PaneNameToCharCode* table);
                virtual void changeSpaceKeyTop(const struct PaneNameToCharCode* table);
#endif
            };

#ifdef TI_CELLPHONE_SAMPLE_CLASS
            class Sample : public LayoutByNW4R {
            public:
                Sample(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* resAccessor, EventObserver* observer)
                    : LayoutByNW4R(manager, resAccessor, observer) {}
                virtual ~Sample() {}
            };
#endif


#endif
