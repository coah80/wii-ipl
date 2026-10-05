typedef int BOOL;
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct Animator { void (*initAnmFrame)(void); void (*initFrame)(void); BOOL (*isPlaying)(void); } Animator;
typedef struct Pane { void (*SetVisible)(int); } Pane;
typedef struct Layout { Animator* (*getAnim)(int); Pane* (*FindPaneByName)(const char*); void (*calc)(void); } Layout;
typedef struct APScanThread { void (*setResultData)(u16*); int (*Create)(void*,int,int,int); BOOL (*IsThreadTerminated)(void); void (*WaitForThreadExit)(void); } APScanThread;
typedef struct PaneManager { void (*init)(void); void (*update)(void); } PaneManager;
typedef struct APScanList { u16 count; } APScanList;
typedef struct WiiSettingFlag { u8 smthMsgData; } WiiSettingFlag;
extern APScanList mAPScanList;
extern APScanThread* mpAPScanThread;
extern Layout* mpMainLayout;
extern PaneManager* mpPaneManager;
extern WiiSettingFlag* mpWiiSettingFlag;
extern void* mpMem1BrowserBuffer;
extern int unk_0x78, unk_0x918, unk_0x914, unk_0xB9C;
extern u8 unk_0x91C[3];
extern int FALSE, true, false;
u16* ScanListCast(void*);
void* memset(void*,int,unsigned long);
void SetFuncResult(u8);
void waitStart(void); void waitFinish(void); void resetFuncMsgQ(void);
void setAPDraw(void); void initAP(void); void initScroll(void);
void updateScroll(void); void resetAP(void);
void scanAP(void)
{
            BOOL playing = FALSE;
            switch (unk_0x78) {
                case 1:
                    memset(&mAPScanList.count, 0, 0x800);
                    mpAPScanThread->setResultData(ScanListCast(&mAPScanList.count));
                    memset(mpMem1BrowserBuffer, 0, 0x1000);
                    mpAPScanThread->Create(mpMem1BrowserBuffer, 0x1000, 0x12, true);
                    unk_0x78 = 2;
                    unk_0x91C[2] = 0;
                    break;
                case 2:
                    if (unk_0x91C[2] == 1) {
                        waitStart();
                    }
                    if (mpAPScanThread->IsThreadTerminated()) {
                        mpAPScanThread->WaitForThreadExit();
                        if (mAPScanList.count != 0) {
                            SetFuncResult(1);
                            setAPDraw();
                            unk_0x78 = 3;
                        } else {
                            SetFuncResult(2);
                            initAP();
                            mpMainLayout->getAnim(0x14)->initAnmFrame();
                            mpMainLayout->getAnim(0)->initAnmFrame();
                            mpMainLayout->getAnim(1)->initAnmFrame();
                        }
                        resetFuncMsgQ();
                        unk_0xB9C = 0;
                        waitFinish();
                    }
                    break;
                case 3:
                    if (mpWiiSettingFlag->smthMsgData == 3) {
                        unk_0x78 = 4;
                        unk_0x91C[2] = 0;
                    }
                    break;
                case 4:
                    initScroll();
                    setAPDraw();
                    mpPaneManager->init();
                    break;
                case 5:
                    mpPaneManager->update();
                    break;
                case 6: {
                    int animationIndex = unk_0x918;
                    unk_0xB9C = 1;
                    playing |= mpMainLayout->getAnim(animationIndex)->isPlaying();
                    if (!playing) {
                        unk_0x78 = 5;
                        setAPDraw();
                        if (unk_0x91C[0] != 0) {
                            mpMainLayout->getAnim(0xa)->initAnmFrame();
                        } else {
                            mpMainLayout->getAnim(0xb)->initAnmFrame();
                        }
                        if (unk_0x914 == 0) {
                            mpMainLayout->FindPaneByName("N_AP1")->SetVisible(false);
                        } else if (unk_0x914 == 1) {
                            mpMainLayout->FindPaneByName("N_AP1")->SetVisible(true);
                        }
                        if (mAPScanList.count == unk_0x914 + 4) {
                            mpMainLayout->FindPaneByName("N_AP6")->SetVisible(false);
                        } else if (mAPScanList.count == unk_0x914 + 5) {
                            mpMainLayout->FindPaneByName("N_AP6")->SetVisible(true);
                        }
                        mpMainLayout->FindPaneByName("N_AP0")->SetVisible(true);
                        mpMainLayout->FindPaneByName("N_AP7")->SetVisible(true);
                    }
                    break;
                }
                case 7: {
                    int animationIndex = unk_0x918;
                    unk_0xB9C = 1;
                    playing |= mpMainLayout->getAnim(animationIndex)->isPlaying();
                    if (!playing) {
                        updateScroll();
                        unk_0x78 = 6;
                    }
                    break;
                }
                case 8:
                    resetAP();
                    unk_0x91C[2] = 0;
                    break;
                case 9:
                    playing |= mpMainLayout->getAnim(unk_0x918)->isPlaying();
                    if (!playing) {
                        resetFuncMsgQ();
                        unk_0x78 = 1;
                        unk_0x918 = -1;
                        mpPaneManager->init();
                        mpMainLayout->getAnim(0x14)->initFrame();
                        mpMainLayout->calc();
                    }
                    break;
            }
        }
