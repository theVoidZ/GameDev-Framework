#ifndef DEBUGGERITEM_H
#define DEBUGGERITEM_H

#include "monobehavior.h"

namespace gdf{
namespace animation {
    class Animator;
}

namespace kernel{
    class GameObject;
    template<typename T> class tracker_ptr;
}}


class DebuggerItem : public gdf::kernel::MonoBehavior
{
    public:
        DebuggerItem();

        void init();
        void update(sf::Time dt);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    public:
        gdf::animation::Animator* animator = nullptr;

};

#endif // DEBUGGERITEM_H
