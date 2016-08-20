#ifndef BOUNDS_H
#define BOUNDS_H

// c++-includes

// sfml-includes
#include <SFML/System/Vector2.hpp>

// qt-includes
#include <iostream>

// user-includes
#include "Core/Utilities/algorithm.h"
#include "Core/DataStruct/ray.h"


//Defines bounds of an entity in 2-dimensions

class Bounds
{
    public:
        Bounds(sf::Vector2f center = sf::Vector2f(0,0), sf::Vector2f size = sf::Vector2f(0,0) );

    public:
        //! The closest point on the bounding box.
        sf::Vector2f closestPoint( sf::Vector2f point );

        //! Is point contained in the bounding box?
        bool contains( sf::Vector2f point );

        //! Grows the Bounds to include the point. Update the properties
        void encapsulate( sf::Vector2f point );

        //! Expand the bounds by increasing its size by amount along each side.
        void expand( float amount );

        //! Expand the bounds by increasing its size by amount along each side separatly.
        void expand( sf::Vector2f camount );

        //Does ray intersect this bounding box?
        bool intersectRay( Ray ray );

        //Does another bounding box intersect with this bounding box?
        bool intersects(Bounds bounds );

        //! Sets the bounds to the min and max value of the box.
        void setMinMax(sf::Vector2f min, sf::Vector2f max );

        //! The smallest squared distance between the point and this bounding box.
        float sqrDistance( sf::Vector2f point );

    public:
        //! Size of the bound, independant from its position
        sf::Vector2f size = sf::Vector2f(0,0);

        //! Half of the size
        sf::Vector2f extent = sf::Vector2f(0,0);

        //! Coordinates of the center of the bound
        sf::Vector2f center = sf::Vector2f(0,0);

        //! Coordinates of the minimum point of the bound ( top-left )
        sf::Vector2f min = sf::Vector2f(0,0);

        //! Coordinates of the maximum point of the bound ( bottom-right )
        sf::Vector2f max = sf::Vector2f(0,0);
};

#endif // BOUNDS_H
