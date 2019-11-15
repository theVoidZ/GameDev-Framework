#ifndef COLLIDER_H
#define COLLIDER_H

#include <iostream>

#include <SFML/System/Vector2.hpp>

#include "component.h"

#include "bounds.h"

namespace gdf {
namespace graphic {
    class Renderer;
}}

class Collider : public gdf::kernel::Component
{
    public:
        Collider();
        void update(sf::Time dt);
        void fixed_update(sf::Time dt);
        void late_update(sf::Time dt);

        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void on_gui();

        void callback( Collider* other );

        sf::Vector2f displacement;
        sf::Vector2f go_pos;
        Bounds* aabb = nullptr;
        Bounds* global_aabb = nullptr;

};

#endif // COLLIDER_H
