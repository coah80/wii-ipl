#ifndef TEXTINPUT_MY_BACKGROUND_H
#define TEXTINPUT_MY_BACKGROUND_H

#include "tiNw4rManager.h"

namespace textinput {
    namespace extend {
        namespace bg {
            class Base {
                public:
                    virtual void    create(MEMAllocator* allocator);
                    virtual void    init();
            };

            class LayoutByNW4R : public Base, public nw4rmanager::Layout {
                public:
#ifdef MYTIMANAGER_IMPLEMENTATION
                    LayoutByNW4R(nw4r::lyt::MultiArcResourceAccessor* multiArc, const char* layoutName, EventObserver* event)
                        : nw4rmanager::Layout(multiArc, layoutName, event) {}
#endif
#ifdef MYTIMANAGER_IMPLEMENTATION
                    virtual ~LayoutByNW4R();
#else
                    virtual ~LayoutByNW4R() {}
#endif

                    virtual void    create(MEMAllocator* allocator);
                    virtual void    init();

                    virtual void    draw();
            };
        }
    }

    typedef extend::bg::LayoutByNW4R Background;
}

#endif // TEXTINPUT_MY_BACKGROUND_H
