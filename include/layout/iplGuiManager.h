#ifndef IPL_GUI_MANAGER_H
#define IPL_GUI_MANAGER_H

#include "layout/GUIManager.h"
#include "layout/iplLayout.h"

#include <egg/core.h>

#include <cstring>

#include "global/decomp/utils.h"

namespace ipl {
    namespace gui {
        class PaneComponent : public ::gui::PaneComponent {};
        class PaneManager : public ::gui::PaneManager {
            public:
#ifdef IPL_GCW_PANEMANAGER_CTOR_OUT_OF_LINE
                PaneManager(::gui::EventHandler* event, const nw4r::lyt::DrawInfo* drawInfo, EGG::Heap* heap, EGG::Allocator* allocator, bool bDisableCon = false) NO_INLINE;
#else
                PaneManager(::gui::EventHandler* event, const nw4r::lyt::DrawInfo* drawInfo, EGG::Heap* heap, EGG::Allocator* allocator, bool bDisableCon = false) :
                ::gui::PaneManager(event, allocator, drawInfo),
                mpHeap(heap),
                mbDisableCon(bDisableCon) {}
#endif

#if defined(IPL_GC_SAVEDATA_NOVTABLE) || defined(IPL_MEMORY_CARD_NOVTABLE)
                virtual ~PaneManager();
#else
                virtual ~PaneManager() {}
#endif

                void update();
                void update(int chan);

                void setTriggerTarget(nw4r::lyt::Pane* pane, bool bEnable);
                void initPane(nw4r::lyt::Pane* pane);

                void setupScene(layout::Object* layout) {
                    createLayoutScene(*layout->getNW4RLyt());
                }
            
            private:
                u32         unk_0x28;
                EGG::Heap*  mpHeap;

                bool        mbDisableCon;           // 0x30
                bool        mbDoneUpdateWithCon;    // 0x31
        };
    }
}

#endif // IPL_GUI_MANAGER_H
