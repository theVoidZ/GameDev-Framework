#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include <math.h>

namespace gdf {
namespace animation {
    class AnimatorCondition;
}
}

namespace gdf {
namespace system {

class Algorithm
{
    public:

        static sf::Vector2f min(sf::Vector2f p1, sf::Vector2f p2);
        static sf::Vector2f max(sf::Vector2f p1, sf::Vector2f p2);
        static sf::Time clamp( const sf::Time& t, sf::Time min , sf::Time max );
        static float length( sf::Vector2f vec );
        static sf::Time abs(sf::Time time);
        static void iamalive();
};

}}

#endif // ALGORITHM_H
