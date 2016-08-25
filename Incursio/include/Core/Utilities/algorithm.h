#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include <math.h>

class AnimatorCondition;

class Algorithm
{
    public:
        static bool evaluateCondition(void* v, AnimatorCondition* cond);
        static sf::Vector2f min(sf::Vector2f p1, sf::Vector2f p2);
        static sf::Vector2f max(sf::Vector2f p1, sf::Vector2f p2);
        static sf::Time clamp( const sf::Time& t, sf::Time min , sf::Time max );
};

#endif // ALGORITHM_H
