#define IPL_SCENE_MANAGER_H
#define IPL_BASE_SCENE_H
#define IPL_TREE_NODE_H
#define IPL_QUEUE_H

#include <decomp.h>
#include <revolution.h>
#include <egg/core.h>

#include "scene/iplSceneCreator.h"

namespace ipl {
    namespace utility {
        class Tree {
        public:
            Tree();
            virtual ~Tree();
            virtual Tree* getParent();
            virtual Tree* getChild();
            virtual Tree* getNext();
            virtual Tree* getPrev();
            void attach(Tree* tree);
            void insert(Tree* tree, Tree* childTree);
            void detach();
            static Tree* empty() { return (Tree*)0; }

            class iterator {
                typedef Tree value_type;
                typedef value_type* pointer;
                typedef value_type& reference;

            public:
                explicit inline iterator(pointer ptr) : mPtr(ptr) {}
                virtual reference operator*();
                pointer operator->() { return mPtr; }
                pointer getPtr() { return mPtr; }
                iterator& operator++();

            protected:
                pointer mPtr;
            };

            class reverse_iterator {
                typedef Tree value_type;
                typedef value_type* pointer;
                typedef value_type& reference;

            public:
                explicit inline reverse_iterator(pointer ptr) : mPtr(ptr) { reverse(); }
                virtual reference operator*();
                pointer operator->() { return mPtr; }
                pointer getPtr() { return mPtr; }
                void reverse();

            protected:
                pointer mPtr;
            };

        protected:
            Tree* mpParent;
            Tree* mpChild;
            Tree* mpNext;
            Tree* mpPrev;
        };
    }
}

namespace ipl {
    namespace scene {
        class Base;
        enum {
            COMMAND_NONE = 0,
            COMMAND_CREATE_CHILD,
            COMMAND_RESERVE_CHANGE,
            COMMAND_RESERVE_ALL_DESTRUCT,
        };

        typedef struct {
            int type;
            int newSceneID;
            int prevSceneID;
            int newRootID;
            Base* parent;
            Base* child;
            void* args;
        } CommandData;

        typedef struct Command {
            CommandData data;
            void clear();
            Command() { clear(); }
        } Command;

        class Base : public utility::Tree, EGG::Disposer {
        public:
            Base(EGG::Heap* heap);
            virtual ~Base();
            virtual BOOL isReady() const;
            virtual BOOL isResetAcceptable() const;
            virtual void startResetting();
            virtual BOOL isResetProcessDone();
            virtual void prepare();
            virtual void create();
            virtual void calc();
            virtual void draw();
            virtual void destroy();
            virtual Base* getParent();
            virtual Base* getChild();
            virtual Base* getNext();
            virtual Base* getPrev();
            bool isSceneCreated() const { return (mScnState & SCN_STATE_CREATED); }

            class iterator : public utility::Tree::iterator {
                typedef Base value_type;
                typedef value_type* pointer;
                typedef value_type& reference;

            public:
                explicit inline iterator(pointer ptr) : utility::Tree::iterator(ptr) {}
                virtual reference operator*();
                pointer operator->() { return (pointer)mPtr; }
                pointer getPtr() { return (pointer)mPtr; }
                void setPtr(pointer p) { mPtr = p; }
            };

            class reverse_iterator : public utility::Tree::reverse_iterator {
                typedef Base value_type;
                typedef value_type* pointer;
                typedef value_type& reference;

            public:
                explicit reverse_iterator(pointer ptr);
                virtual reference operator*();
                pointer operator->() { return (pointer)mPtr; }
                pointer getPtr() { return (pointer)mPtr; }
                void setPtr(pointer p) { mPtr = p; }
            };

        private:
            enum {
                SCN_STATE_CREATED = (1 << 0),
                SCN_STATE_DESTROY_REQ = (1 << 1),
            };

            void do_prepare();
            void do_create();
            void do_calc();
            void do_draw();
            void do_destroy();

            EGG::Heap* mpHeap;
            u32 mParentFlags;
            u32 mScnState;
            int mSceneID;
            u32 mPrevSceneID;
            Command mCommand;

        protected:
            enum {
                SCN_PARENTFLAG_CALC = (1 << 0),
                SCN_PARENTFLAG_DRAW = (1 << 1),
            };

            void createChildScene(int sceneId, Base* parent, Base* child, void* args = NULL);
            void reserveSceneChange(int sceneId, void* args = NULL);
            void reserveAllSceneDestruction(int sceneId, void* args = NULL);
            void setSceneParentFlags(u32 flag) { mParentFlags = flag; }
            void requestSceneDestruction() { mScnState |= SCN_STATE_DESTROY_REQ; }
            EGG::Heap* getSceneHeap() { return mpHeap; }
            int getSceneID() const { return mSceneID; }
            u32 getPrevSceneID() const { return mPrevSceneID; }

            friend class Manager;
        };
    }
}

namespace ipl {
    namespace utility {
        template <typename T, int c>
        class Queue {
        public:
            inline Queue() : count(c), current(0), popped(0), pushed(0) {}

            BOOL push(const T& item) {
                if (count == current) {
                    return FALSE;
                }
                items[pushed] = item;
                if (++pushed >= count) {
                    pushed = 0;
                }
                current++;
                return TRUE;
            }

            BOOL pop() {
                BOOL result = TRUE;
                if (current == 0) {
                    result = FALSE;
                    goto done;
                }
                if (++popped >= count) {
                    popped = 0;
                }
                current--;
            done:
                return result;
            }

            int get_current_index() { return current; }
            T& get_current_item() { return items[get_current_index()]; }
            int get_popped_index() { return popped; }
            T& get_popped_item() { return items[get_popped_index()]; }
            void next_popped_item() { popped++; }
            void no_popped_item() { popped = 0; }
            int get_pushed_index() { return pushed; }
            T& get_pushed_item() { return items[get_pushed_index()]; }

            T items[c];
            int count;
            int current;
            int popped, pushed;
        };

        template <>
        class Queue<ipl::scene::Command, 8> {
        public:
            inline Queue() : count(8), current(0), popped(0), pushed(0) {}

            BOOL push(const ipl::scene::Command& item) {
                if (count == current) {
                    return FALSE;
                }
                items[pushed] = item;
                if (++pushed >= count) {
                    pushed = 0;
                }
                current++;
                return TRUE;
            }

            BOOL pop();
            int get_current_index() { return current; }
            ipl::scene::Command& get_current_item() { return items[get_current_index()]; }
            int get_popped_index() { return popped; }
            ipl::scene::Command& get_popped_item() { return items[get_popped_index()]; }
            void next_popped_item() { popped++; }
            void no_popped_item() { popped = 0; }
            int get_pushed_index() { return pushed; }
            ipl::scene::Command& get_pushed_item() { return items[get_pushed_index()]; }

            ipl::scene::Command items[8];
            int count;
            int current;
            int popped, pushed;
        };
    }
}

namespace ipl {
    namespace scene {
        enum {
            DRAW_LAYER_1 = 0,
            DRAW_LAYER_2,
            DRAW_LAYER_DEFAULT = DRAW_LAYER_2,
            DRAW_LAYER_3,
            DRAW_LAYER_MAX,
        };

#define MAX_COMMANDS 8
        typedef utility::Queue<Command, MAX_COMMANDS> CommandList;

        class Manager {
        public:
            Manager(EGG::Heap* heap);
            void init();
            void calc();
            void calc(SceneObj* scene);
            void draw();
            void draw(SceneObj* scene);
            SceneObj* createScene(int sceneId, int prevSceneId, void* args);
            SceneObj* createScene(int sceneId, void* args) { return createScene(sceneId, SCENE_NONE, args); }
            void createScene(const Command& command);
            void destroyScene(SceneObj* scene);
            void detach(SceneObj* scene);
            void startResetting();
            BOOL isResetProcessDone();
            BOOL isResetAcceptable();
            BOOL pushCommand(const Command& pCommand);
            void setDestructSync();
            void doDestructSync() { mbDestroySyncTask = true; }
            SceneObj* getScene(int sceneId);
            SceneObj* getScene(int sceneId, SceneObj* obj);
            bool onDefaultDrawLayer() { return mDrawLayer == DRAW_LAYER_2; }
            bool onDrawLayer(int layer) { return mDrawLayer == layer; }
            void attachReservedScene();
            BOOL isReady(int sceneId);
            SceneObj* getReservedScene() { return mpReservedScene; }
            int getCurrentRootSceneID() { return mRootSceneID; }
            int getPreviousRootSceneID() { return mPrevRootSceneID; }

        private:
            void createRootScene(int sceneId, void* args);

            EGG::UnitHeap* mpBigSceneHeap;
            EGG::UnitHeap* mpMdmSceneHeap;
            EGG::UnitHeap* mpSmlSceneHeap;
            SceneObj* mpRootScene;
            CommandList mCommands;
            int mDrawLayer;
            SceneObj* mpReservedScene;
            Command mReservedCommand;
            bool mbCreatedReserved;
            bool mbDestroySyncTask;
            int mRootSceneID;
            int mPrevRootSceneID;
        };
    }
}

#define SCENE_CLASS(x) class x : public scene::Base
#include "scene/iplRootScene.h"
#include "iplSystem.h"
#include <cstring>

namespace ipl {
    namespace scene {
        void Command::clear() {
            memset(this, 0, sizeof(Command));
            data.type = 0;
            data.newRootID = 0;
            data.prevSceneID = 0;
            data.newSceneID = 0;
        }

        Manager::Manager(EGG::Heap* heap)
            : mpRootScene(NULL), mCommands(), mpReservedScene(NULL), mReservedCommand(), mbCreatedReserved(false), mbDestroySyncTask(false) {
            // Setup the heaps!!
            mpBigSceneHeap =
                EGG::UnitHeap::create(EGG::UnitHeap::calcHeapSize(Creator::BIG_SIZE, 3, 4), Creator::BIG_SIZE, heap, 4, MEM_HEAP_OPT_DEBUG_FILL);
            mpMdmSceneHeap = EGG::UnitHeap::create(EGG::UnitHeap::calcHeapSize(Creator::MEDIUM_SIZE, 4, 4), Creator::MEDIUM_SIZE, heap, 4,
                                                   MEM_HEAP_OPT_DEBUG_FILL);
            mpSmlSceneHeap =
                EGG::UnitHeap::create(EGG::UnitHeap::calcHeapSize(Creator::SMALL_SIZE, 6, 4), Creator::SMALL_SIZE, heap, 4, MEM_HEAP_OPT_DEBUG_FILL);
        }

        void Manager::init() {
            int initialScene = 0;
            int initialSubScene = 0;
            RootScene::proc_boot_scene(&initialScene, &initialSubScene);

            mPrevRootSceneID = 0;
            mRootSceneID = initialScene;
            createRootScene(initialScene, (void*)initialSubScene);
        }

        void Manager::createRootScene(int sceneId, void* args) {
            mpRootScene = (RootScene*)createScene(SCENE_ROOT, (void*)sceneId);
            static_cast<RootScene*>(mpRootScene)->mpInitialArgs = args;

            System::setCurrentHeap(mpRootScene->mpHeap);
            mpRootScene->do_create();

            System::getMem1Root()->becomeCurrentHeap();
        }

        void Manager::calc() {
            calc(mpRootScene);

            if (mpReservedScene) {
                if (mbCreatedReserved) {
                    attachReservedScene();
                }
            } else {
                if (mCommands.get_current_index() != 0) {
                    const Command& popped = mCommands.get_popped_item();
                    switch (popped.data.type) {
                        case COMMAND_CREATE_CHILD: {
                            createScene(popped);
                            mbCreatedReserved = true;
                            mCommands.pop();
                            break;
                        }
                        case COMMAND_RESERVE_CHANGE: {
                            createScene(popped);
                            mCommands.pop();
                            break;
                        }
                        case COMMAND_RESERVE_ALL_DESTRUCT: {
                            if (mbDestroySyncTask) {
                                mPrevRootSceneID = mRootSceneID;
                                mRootSceneID = popped.data.newRootID;

                                destroyScene(mpRootScene);

                                System::reinit();

                                createRootScene(popped.data.newRootID, popped.data.args);
                                mCommands.pop();

                                mbDestroySyncTask = false;
                            }
                            break;
                        }
                    }
                }
            }
            detach(mpRootScene);
        }

        void Manager::calc(SceneObj* scene) {
            for (SceneObj::iterator it = SceneObj::iterator(scene); it.getPtr(); ++it) {
                it->do_calc();
            }
        }

        Base& Base::iterator::operator*() {
            return *(Base*)mPtr;
        }
    }

    namespace utility {
        Tree::iterator& Tree::iterator::operator++() {
            if (mPtr->getChild()) {
                mPtr = mPtr->getChild();
            } else {
                if (mPtr->getNext()) {
                    mPtr = mPtr->getNext();
                } else {
                    while ((mPtr = mPtr->getParent())) {
                        if (!mPtr->getNext()) {
                            continue;
                        }

                        mPtr = mPtr->getNext();
                        break;
                    }
                }
            }
        }
    }

    namespace scene {
        void Manager::draw() {
            mDrawLayer = DRAW_LAYER_1;
            while (mDrawLayer < DRAW_LAYER_MAX) {
                draw(mpRootScene);
                mDrawLayer++;
            }
        }

        void Manager::draw(SceneObj* scene) {
            for (SceneObj::iterator it = SceneObj::iterator(scene); it.getPtr() != NULL; ++it) {
                it->do_draw();
            }
        }

        BOOL Manager::isResetAcceptable() {
            if (!mpRootScene) {
                return TRUE;
            } else {
                for (SceneObj::iterator it = SceneObj::iterator(mpRootScene); it.getPtr() != NULL; ++it) {
                    if (it->isResetAcceptable() == FALSE) {
                        return FALSE;
                    }
                }
            }
            return TRUE;
        }

        void Manager::startResetting() {
            if (mpRootScene) {
                for (SceneObj::iterator it = SceneObj::iterator(mpRootScene); it.getPtr() != NULL; ++it) {
                    it->startResetting();
                }
            }
        }

        BOOL Manager::isResetProcessDone() {
            if (!mpRootScene) {
                return TRUE;
            } else {
                for (SceneObj::iterator it = SceneObj::iterator(mpRootScene); it.getPtr() != NULL; ++it) {
                    if (it->isResetProcessDone() == FALSE) {
                        return FALSE;
                    }
                }
            }
            return TRUE;
        }

        void Manager::detach(SceneObj* scene) {
            SceneObj::reverse_iterator stack10 = SceneObj::reverse_iterator(scene);
            SceneObj::reverse_iterator stack18 = SceneObj::reverse_iterator(scene);
            while (stack10.getPtr()) {
                if (stack18->getPrev()) {
                    stack18.setPtr(stack18->getPrev());
                    stack18.reverse();
                } else {
                    stack18.setPtr(stack18->getParent());
                }
                if ((stack10->mScnState & SceneObj::SCN_STATE_DESTROY_REQ) != 0) {
                    if (mReservedCommand.data.prevSceneID == stack10->mSceneID) {
                        mbCreatedReserved = true;
                    }
                    destroyScene(&*stack10);
                }
                stack10.setPtr(&*stack18);
            }
        }

        Base::reverse_iterator::reverse_iterator(Base* ptr) : utility::Tree::reverse_iterator(ptr) {}
    }

    namespace utility {
        void Tree::reverse_iterator::reverse() {
            while (mPtr->getChild()) {
                mPtr = mPtr->getChild();
                while (mPtr->getNext()) {
                    mPtr = mPtr->getNext();
                }
            }
        }
    }

    namespace scene {
        Base& Base::reverse_iterator::operator*() {
            return *(Base*)mPtr;
        }

        void Manager::createScene(const Command& command) {
            mpReservedScene = createScene(command.data.newSceneID, command.data.prevSceneID, command.data.args);
            mReservedCommand = command;
            mbCreatedReserved = false;
            mpReservedScene->do_prepare();

            System::getMem1Root()->becomeCurrentHeap();
        }

        SceneObj* Manager::createScene(int sceneId, int prevSceneId, void* args) {
            EGG::Heap* heap = NULL;
            int size = Creator::size(sceneId);

            SceneObj* scene = NULL;

            switch (size) {
                case Creator::BIG_SIZE: {
                    heap = mpBigSceneHeap;
                    break;
                }
                case Creator::MEDIUM_SIZE: {
                    heap = mpMdmSceneHeap;
                    break;
                }
                case Creator::SMALL_SIZE: {
                    heap = mpSmlSceneHeap;
                    break;
                }
            }

            heap = EGG::FrmHeap::create(size, heap, MEM_HEAP_OPT_DEBUG_FILL);
            System::setCurrentHeap(heap);

            scene = Creator::create(sceneId, heap, args);
            scene->mSceneID = sceneId;
            scene->mPrevSceneID = prevSceneId;

            return scene;
        }

        void destruct_sync_task_(void* work) {
            static_cast<Manager*>(work)->doDestructSync();
        }

        void Manager::setDestructSync() {
            mbDestroySyncTask = false;
            System::getTask1()->request(destruct_sync_task_, this, NULL);
        }

        void Manager::destroyScene(SceneObj* scene) {
            while (scene->getChild()) {
                destroyScene(scene->getChild());
            }

            scene->do_destroy();
            scene->detach();
            scene->mpHeap->destroy();
        }

        void Manager::attachReservedScene() {
            if (isReady(mReservedCommand.data.newSceneID) || mpReservedScene && mpReservedScene->isReady()) {
                SceneObj* scene = mReservedCommand.data.parent;
                if (!scene) {
                    scene = mpRootScene;
                }

                if (mReservedCommand.data.child) {
                    scene->insert(mpReservedScene, mReservedCommand.data.child);
                } else {
                    scene->attach(mpReservedScene);
                }

                System::setCurrentHeap(mpReservedScene->mpHeap);
                mpReservedScene->do_create();

                System::getMem1Root()->becomeCurrentHeap();

                mpReservedScene = NULL;
                mReservedCommand.clear();
                mbCreatedReserved = false;
            }
        }

        BOOL Manager::pushCommand(const Command& command) {
            return mCommands.push(command);
        }

        BOOL Manager::isReady(int sceneId) {
            BOOL result = FALSE;
            int gotID = 0;
            if (System::getNandManager()->receiveToken(&gotID) && sceneId == gotID) {
                result = TRUE;
            }
            return result;
        }

        SceneObj* Manager::getScene(int sceneId) {
            return getScene(sceneId, mpRootScene);
        }

        SceneObj* Manager::getScene(int sceneId, SceneObj* obj) {
            SceneObj::iterator it = SceneObj::iterator(obj);
            SceneObj* found = NULL;
            while (it.getPtr() != NULL) {
                if (sceneId == it.getPtr()->mSceneID) {
                    found = it.getPtr();
                    break;
                }
                ++it;
            }
            return found;
        }
    }  // namespace scene

    namespace utility {
        Tree& Tree::reverse_iterator::operator*() {
            return *mPtr;
        }

        BOOL Queue<scene::Command, 8>::pop() {
            BOOL result = TRUE;
            if (current == 0) {
                result = FALSE;
                goto done;
            }
            if (++popped >= count) {
                popped = 0;
            }
            current--;
        done:
            return result;
        }
    }
}  // namespace ipl
