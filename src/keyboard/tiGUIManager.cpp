#include "keyboard/tiGUIManager.h"
#include "keyboard/tiUtil.h"

#include <revolution/gx.h>

#include <new>

namespace textinput {
    namespace gui {
        extern "C" void drawLine___Q29textinput3guiFfffffUcR8_GXColor();

        void drawLine_(f32 x0, f32 y0, f32 x1, f32 y1, f32 z, u8 width, GXColor& color) {
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_F32, 0);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);

            GXSetCullMode(GX_CULL_NONE);

            GXSetNumChans(1);
            GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);

            GXSetNumTexGens(0);
            GXSetNumTevStages(1);

            GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);

            GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_NOOP);

            Mtx mtx;
            MTXTrans(mtx, 0.0f, 0.0f, 0.0f);
            GXLoadPosMtxImm(mtx, 0);

            GXSetLineWidth(width, GX_TO_ZERO);

            // Draw the line
            GXBegin(GX_LINES, GX_VTXFMT0, 2);
            {
                GXPosition3f32(x0, y0, z);
                GXColor1u32(*(u32*)&color);
                GXPosition3f32(x1, y1, z);
                GXColor1u32(*(u32*)&color);
            }
            GXEnd();
        }

        #pragma push
        #pragma section sconst_type ".sdata2"
        extern "C" const f32 lbl_81694EE8 = 0.0f;
        extern "C" const u8 lbl_81694EEC = 0xFF;
        extern "C" const u8 lbl_81694EED = 0x00;
        extern "C" const u8 lbl_81694EEE = 0x00;
        extern "C" const u8 lbl_81694EEF = 0xFF;
        extern "C" const f32 lbl_81694EF0 = 0.5f;
        #pragma pop

        u32 GUIComponent::updatePointerImpl(const GUIPointer& pointer) {
            int point = pointer.getCtrlNo();
            u32 event = EVENT_NONE;
            f32 x = pointer.getPosX();
            f32 y = pointer.getPosY();

            if (isVisible()) {
                if (contain(x, y)) {
                    // Colliding with component
                    if (isPointed(point)) {
                        onMove(point, x, y);
                        event = EVENT_MOVE;
                    } else {
                        setPointed(point, true);
                        onPointIn(point);
                        event = EVENT_POINT;
                    }
                } else {
                    // Not colliding with component
                    if (isPointed(point)) {
                        setPointed(point, false);
                        onPointOut(point);
                        event = EVENT_LEFT;
                    }
                }

                // Pressing the drag button.
                if (mbDragging[point]) {
                    onDrag(x - mDraggingPos[point].x, y - mDraggingPos[point].y);
                    mDraggingPos[point].x = x;
                    mDraggingPos[point].y = y;
                }
            }

            if (mbDragging[point] && pointer.isPressed(mDraggingButton) == 0) {
                mbDragging[point] = false;
            }

            return event;
        }

        GUIManager::~GUIManager() {
            IDToComponent* p = static_cast<IDToComponent*>(nw4r::ut::List_GetFirst(&mComponents));
            while (p != NULL) {
                // Remove them from the list
                nw4r::ut::List_Remove(&mComponents, p);
                // Then delete them from memory.
                if (mpAllocator) {
                    MEMFreeToAllocator(mpAllocator, p);
                } else {
                    delete p;
                }
                // Next component to kill!
                p = static_cast<IDToComponent*>(nw4r::ut::List_GetFirst(&mComponents));
            }
        }

        void GUIManager::init() {
            for (IDToComponent* p = static_cast<IDToComponent*>(nw4r::ut::List_GetFirst(&mComponents)); p != NULL;
                 p = static_cast<IDToComponent*>(nw4r::ut::List_GetNext(&mComponents, p))) {
                p->mpComponent->init();
            }
        }

        void GUIManager::addComponent(GUIComponent* component) {
            int id = component->getID();

            component->setParentManager(this);
            if (mpAllocator) {
                void* pBuf = MEMAllocFromAllocator(mpAllocator, sizeof(IDToComponent));
                IDToComponent* p = new (pBuf) IDToComponent(id, component);
                nw4r::ut::List_Append(&mComponents, p);
            } else {
                IDToComponent* p = new IDToComponent(id, component);
                nw4r::ut::List_Append(&mComponents, p);
            }
        }

        GUIComponent* GUIManager::getComponent(u32 id) {
            IDToComponent* p = static_cast<IDToComponent*>(nw4r::ut::List_GetNth(&mComponents, (u16)id));
            return p->mpComponent;
        }

        GUIComponent* GUIManager::getComponent(u32 id) const {
            IDToComponent* p = static_cast<IDToComponent*>(nw4r::ut::List_GetNth(&mComponents, (u16)id));
            return p->mpComponent;
        }

        bool GUIManager::update(int point, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data) {
            bool touched = false;

            GUIComponent* triggerCom = NULL;
            for (IDToComponent* p = static_cast<IDToComponent*>(nw4r::ut::List_GetFirst(&mComponents)); p != NULL;
                 p = static_cast<IDToComponent*>(nw4r::ut::List_GetNext(&mComponents, p))) {
                GUIComponent* component = p->mpComponent;
                u32 result = p->mpComponent->updatePointer(point, x, y, trig, hold, release);

                switch (result) {
                    case GUIComponent::EVENT_POINT: {
                        onEvent(*component, EventHandler::ON_POINT, point, data);
                        goto hasTouched;
                    }
                    case GUIComponent::EVENT_LEFT: {
                        onEvent(*component, EventHandler::ON_LEFT, point, data);
                        break;
                    }
                    case GUIComponent::EVENT_MOVE: {
                        onEvent(*component, EventHandler::ON_MOVE, point, data);
                        goto hasTouched;
                    }
                    case GUIComponent::EVENT_TRIG: {
                        onEvent(*component, EventHandler::ON_TRIG, point, data);
                        break;
                    }
                    case GUIComponent::EVENT_RELEASE: {
                        onEvent(*component, EventHandler::ON_RELEASE, point, data);
                        break;
                    }

                    hasTouched:
                        touched = true;
                        if (component->isTriggerTarget()) {
                            triggerCom = component;
                        }
                }

                if (component->isDragging(point)) {
                    onEvent(*component, EventHandler::ON_DRAG, point, data);
                }
            }

            if (triggerCom) {
                if (trig) {
                    Vec pos = {x, y, 0.0f};
                    triggerCom->onTrig(point, trig, pos);
                    onEvent(*triggerCom, EventHandler::ON_TRIG, point, data);
                }
                if (release) {
                    onEvent(*triggerCom, EventHandler::ON_RELEASE, point, data);
                }
            }

            return touched;
        }

        void GUIManager::calc() {
            for (IDToComponent* p = static_cast<IDToComponent*>(nw4r::ut::List_GetFirst(&mComponents)); p != NULL;
                 p = static_cast<IDToComponent*>(nw4r::ut::List_GetNext(&mComponents, p))) {
                p->mpComponent->calc();
            }
        }

        void GUIManager::draw() {
            for (IDToComponent* p = static_cast<IDToComponent*>(nw4r::ut::List_GetFirst(&mComponents)); p != NULL;
                 p = static_cast<IDToComponent*>(nw4r::ut::List_GetNext(&mComponents, p))) {
                p->mpComponent->draw();
            }
        }

        void GUIManager::setAllComponentTriggerTarget(bool bEnable) {
            for (IDToComponent* p = static_cast<IDToComponent*>(nw4r::ut::List_GetFirst(&mComponents)); p != NULL;
                 p = static_cast<IDToComponent*>(nw4r::ut::List_GetNext(&mComponents, p))) {
                p->mpComponent->setTriggerTarget(bEnable);
            }
        }

        void GUIManager::setDraggingButton(u32 dragBtn) {
            for (IDToComponent* p = static_cast<IDToComponent*>(nw4r::ut::List_GetFirst(&mComponents)); p != NULL;
                 p = static_cast<IDToComponent*>(nw4r::ut::List_GetNext(&mComponents, p))) {
                p->mpComponent->setDraggingButton(dragBtn);
            }
        }

        PaneManager::~PaneManager() {
            PaneToComponent* p = static_cast<PaneToComponent*>(nw4r::ut::List_GetFirst(&mPaneComponents));
            while (p) {
                // Remove them from the list
                nw4r::ut::List_Remove(&mPaneComponents, p);
                // Then delete them from memory.
                if (mpAllocator) {
                    p->mpComponent->~PaneComponent();
                    p->~PaneToComponent();

                    MEMFreeToAllocator(mpAllocator, p->mpComponent);
                    MEMFreeToAllocator(mpAllocator, p);
                } else {
                    delete p->mpComponent;
                    delete p;
                }
                // Next component to kill!
                p = static_cast<PaneToComponent*>(nw4r::ut::List_GetFirst(&mPaneComponents));
            }
        }

        void PaneManager::createLayoutScene(const nw4r::lyt::Layout& layout) {
            mIDCounter = 0;
            walkInChildren(layout.GetRootPane()->GetChildList());
        }

        void PaneManager::walkInChildren(nw4r::lyt::PaneList& paneList) {
            for (nw4r::lyt::PaneList::Iterator it = paneList.GetBeginIter(); it != paneList.GetEndIter(); ++it) {
                addPane_(&*it);
                walkInChildren(it->GetChildList());
            }
        }

        void PaneManager::addPane_(nw4r::lyt::Pane* pane) {
            PaneComponent* pComponent = NULL;
            PaneToComponent* pToComponent = NULL;

            // Create the component
            if (mpAllocator) {
                void* pComBuf = MEMAllocFromAllocator(mpAllocator, sizeof(PaneComponent));
                void* pBuf = MEMAllocFromAllocator(mpAllocator, sizeof(PaneToComponent));

                pComponent = new (pComBuf) PaneComponent(mIDCounter);
                pToComponent = new (pBuf) PaneToComponent(pane, pComponent);
            } else {
                pComponent = new PaneComponent(mIDCounter);
                pToComponent = new PaneToComponent(pane, pComponent);
            }

            // Append it
            nw4r::ut::List_Append(&mPaneComponents, pToComponent);
            mIDCounter++;

            pComponent->setPane(pane);

            // Trigger target for pictures panes
            if (nw4r::ut::DynamicCast<nw4r::lyt::Picture*>(pane)) {
                pComponent->setTriggerTarget(true);
            }
            if (nw4r::ut::DynamicCast<nw4r::lyt::Window*>(pane)) {
                pComponent->setTriggerTarget(true);
            }

            addComponent(pComponent);
        }

        PaneComponent* PaneManager::searchPaneComponent(const char* name) {
            for (u32 i = 0; i < nw4r::ut::List_GetSize(&mPaneComponents); i++) {
                PaneToComponent* p = static_cast<PaneToComponent*>(nw4r::ut::List_GetNth(&mPaneComponents, (u16)i));
                if (util::strcmp(p->mpPane->GetName(), name)) {
                    return p->mpComponent;
                }
            }
            return NULL;
        }

        PaneComponent* PaneManager::getPaneComponentByPane(nw4r::lyt::Pane* pane) {
            for (u32 i = 0; i < nw4r::ut::List_GetSize(&mPaneComponents); i++) {
                PaneToComponent* p = static_cast<PaneToComponent*>(nw4r::ut::List_GetNth(&mPaneComponents, (u16)i));
                if (p->mpPane == pane) {
                    return p->mpComponent;
                }
            }
            return NULL;
        }

        void PaneManager::setAllBoundingBoxComponentTriggerTarget(bool bEnable) {
            for (u32 i = 0; i < nw4r::ut::List_GetSize(&mPaneComponents); i++) {
                PaneToComponent* p = static_cast<PaneToComponent*>(nw4r::ut::List_GetNth(&mPaneComponents, (u16)i));
                if (nw4r::ut::DynamicCast<nw4r::lyt::Bounding*>(p->getPane())) {
                    p->mpComponent->setTriggerTarget(bEnable);
                }
            }
        }

        bool PaneComponent::contain(f32 x, f32 y) {
            // Abort if no manager
            if (mpManager == NULL) {
                return false;
            }

            // Abort if no draw info
            const nw4r::lyt::DrawInfo* drawInfo = static_cast<PaneManager*>(mpManager)->getDrawInfo();
            if (drawInfo == NULL) {
                return false;
            }

            nw4r::math::MTX34 globalMtx;
            MTXInverse(mpPane->GetGlobalMtx(), globalMtx);

            nw4r::math::VEC3 pos;
            MTXMultVec(globalMtx, nw4r::math::VEC3(x, y, 0), pos);

            nw4r::ut::Rect rect = mpPane->GetPaneRect(*drawInfo);

            // If position is touching pane?
            if (rect.left <= pos.x && pos.x <= rect.right && rect.bottom <= pos.y && pos.y <= rect.top) {
                return true;
            } else {
                return false;
            }
        }

        extern "C" asm void draw__Q39textinput3gui13PaneComponentFv() {
            nofralloc
            stwu r1, -0x40(r1)
            mflr r0
            stw r0, 0x44(r1)
            stfd f31, 0x30(r1)
            psq_st f31, 0x38(r1), 0, 0
            stfd f30, 0x20(r1)
            psq_st f30, 0x28(r1), 0, 0
            stw r31, 0x1c(r1)
            mr r31, r3
            lwz r3, 0x94(r3)
            lwz r12, 0(r3)
            lwz r12, 0x50(r12)
            mtctr r12
            bctrl
            cmpwi r3, 0
            beq pane_component_draw_done
            lwz r5, 0x9c(r31)
            mr r3, r31
            lbz r7, lbl_81694EEC
            li r4, 0
            lfs f1, 0x4c(r5)
            lfs f0, 0x50(r5)
            lfs f31, 0x90(r5)
            lfs f30, 0xa0(r5)
            lbz r6, lbl_81694EED
            lbz r5, lbl_81694EEE
            lbz r0, lbl_81694EEF
            stb r7, 8(r1)
            stb r6, 9(r1)
            stb r5, 0xa(r1)
            stb r0, 0xb(r1)
            lwz r12, 0(r31)
            stfs f1, 0x10(r1)
            lwz r12, 0x24(r12)
            stfs f0, 0x14(r1)
            mtctr r12
            bctrl
            cmpwi r3, 0
            beq pane_component_draw_lines
            li r3, 0
            li r0, 0xff
            stb r3, 8(r1)
            stb r0, 0xa(r1)
        pane_component_draw_lines:
            lfs f1, lbl_81694EF0
            addi r4, r1, 8
            lfs f0, 0x14(r1)
            li r3, 8
            lfs f2, 0x10(r1)
            fmuls f0, f0, f1
            lfs f5, lbl_81694EE8
            fmuls f3, f2, f1
            fsubs f2, f30, f0
            fsubs f1, f31, f3
            fadds f3, f31, f3
            fmr f4, f2
            bl drawLine___Q29textinput3guiFfffffUcR8_GXColor
            lfs f1, 0x10(r1)
            addi r4, r1, 8
            lfs f2, lbl_81694EF0
            li r3, 8
            lfs f0, 0x14(r1)
            fmuls f1, f1, f2
            lfs f5, lbl_81694EE8
            fmuls f0, f0, f2
            fadds f1, f31, f1
            fsubs f2, f30, f0
            fadds f4, f30, f0
            fmr f3, f1
            bl drawLine___Q29textinput3guiFfffffUcR8_GXColor
            lfs f1, lbl_81694EF0
            addi r4, r1, 8
            lfs f0, 0x14(r1)
            li r3, 8
            lfs f2, 0x10(r1)
            fmuls f0, f0, f1
            lfs f5, lbl_81694EE8
            fmuls f3, f2, f1
            fadds f2, f30, f0
            fadds f1, f31, f3
            fsubs f3, f31, f3
            fmr f4, f2
            bl drawLine___Q29textinput3guiFfffffUcR8_GXColor
            lfs f1, 0x10(r1)
            addi r4, r1, 8
            lfs f2, lbl_81694EF0
            li r3, 8
            lfs f0, 0x14(r1)
            fmuls f1, f1, f2
            lfs f5, lbl_81694EE8
            fmuls f0, f0, f2
            fsubs f1, f31, f1
            fadds f2, f30, f0
            fsubs f4, f30, f0
            fmr f3, f1
            bl drawLine___Q29textinput3guiFfffffUcR8_GXColor
        pane_component_draw_done:
            psq_l f31, 0x38(r1), 0, 0
            lfd f31, 0x30(r1)
            psq_l f30, 0x28(r1), 0, 0
            lfd f30, 0x20(r1)
            lwz r0, 0x44(r1)
            lwz r31, 0x1c(r1)
            mtlr r0
            addi r1, r1, 0x40
            blr
        }

        static bool is_visible(nw4r::lyt::Pane* pane) {
            if (!pane->IsVisible()) {
                return false;
            }
            if (pane->GetParent() == NULL) {
                return true;
            }
            return is_visible(pane->GetParent());
        }

        bool PaneComponent::isVisible() {
            nw4r::lyt::Pane* pane = mpPane;
            if (pane == NULL) {
                return false;
            }
            while (pane != NULL) {
                if (!pane->IsVisible()) {
                    return false;
                }
                pane = pane->GetParent();
            }
            return true;
        }
    }  // namespace gui
}  // namespace textinput
