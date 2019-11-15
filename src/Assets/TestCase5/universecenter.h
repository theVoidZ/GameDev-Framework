#ifndef UNIVERSECENTER_H
#define UNIVERSECENTER_H


#include <SFML/System/Vector2.hpp>

#include "monobehavior.h"

#include "tracker_ptr.h"
#include "sprite2d.h"

namespace gdf{
namespace kernel{
    class GameObject;
}}

class UniverseCenter : public gdf::kernel::MonoBehavior
{
    public:
        UniverseCenter();

        void on_mouse_button_pressed(const sf::Event &event);

    public:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif // UNIVERSECENTER_H
