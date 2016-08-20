#ifndef RAY_H
#define RAY_H

// c++-includes
#include <math.h>

// sfml-includes
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>

// qt-includes

// user-includes
#include "Core/Utilities/algorithm.h"
#include "Core/DataStruct/ray.h"


//Defines a ray

class Ray
{
    public:
        Ray(sf::Vector2f origin, sf::Vector2f direction);

    public:
        sf::Vector2f origin;
        sf::Vector2f direction;

    public:
        //! Get the point after far by 'distance' from origin
        sf::Vector2f getPoint( float distance );
};

#endif // RAY_H
