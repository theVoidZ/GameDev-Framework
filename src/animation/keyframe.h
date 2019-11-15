#ifndef KEYFRAME_H
#define KEYFRAME_H

#include <list>
#include <functional>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "bounds.h"

namespace gdf {
namespace animation{

class AnimationEvent;

class KeyFrame
{
    public:
        KeyFrame();
        KeyFrame(int sprite_id, int frame_id, int frame_rate);

    public:
        std::function< void(void*) > fire_event = [](void*){};
        std::list<AnimationEvent*> starting_events;
        std::list<AnimationEvent*> ending_events;

        int sprite_id;
        int frame_id;

        //Specific frame rate of this keyframe. ( duration of this keyframe ) ( ms )
        int frame_rate = 0;
        int frame_rate_cumulative = 0; //! SUGG

        // Hitbox
        sf::Vector2f offset;
        sf::RectangleShape aabb = sf::RectangleShape( sf::Vector2f(0,0));

};

}}

#endif // KEYFRAME_H
