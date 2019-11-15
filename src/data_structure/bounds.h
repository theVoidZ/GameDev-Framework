#ifndef BOUNDS_H
#define BOUNDS_H

// c++-includes

// sfml-includes
#include <SFML/System/Vector2.hpp>

// qt-includes
#include <iostream>

// user-includes
#include "algorithm.h"
//#include "ray.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
///Defines bounds of an entity in 2-dimensions AABB like
///
class Bounds
{
    public:
        Bounds(sf::Vector2f center = sf::Vector2f(), sf::Vector2f half_size = sf::Vector2f() );

    public:
        static Bounds from_min_max(sf::Vector2f min, sf::Vector2f max);
        static Bounds from_center_extent(sf::Vector2f center, sf::Vector2f extent);
        static Bounds from_center_size(sf::Vector2f center, sf::Vector2f size);
        static Bounds from_min_size(sf::Vector2f min, sf::Vector2f size);

    public:
        // Creation
        //! Sets the bounds to the min and max value of the box.
        void set_min_max(sf::Vector2f min, sf::Vector2f max );

        //! Grows the Bounds to include the point. Update the properties
        void encapsulate( sf::Vector2f point );

        //! Expand the bounds by increasing its size by amount along each side.
        void expand( float amount );

        //! Expand the bounds by increasing its size by amount along each side separatly.
        void expand( sf::Vector2f camount );

    public:
        // Algortihms
        //! The closest point on the bounding box.
        sf::Vector2f closestPoint( sf::Vector2f point );

        //! Is point contained in the bounding box?
        bool contains( sf::Vector2f point );

        //Does another bounding box intersect with this bounding box?
        bool intersects(Bounds bounds );
        bool intersects2(Bounds bounds );

    public:



        //Does ray intersect this bounding box?
//        bool intersectRay( Ray ray );

        //! The smallest squared distance between the point and this bounding box.
        float sqrDistance( sf::Vector2f point );

    public:
        // GETTERS
        sf::Vector2f size() const;
        sf::Vector2f extent() const;
        sf::Vector2f center() const;
        sf::Vector2f min() const;
        sf::Vector2f max() const;

    private:
        //! Size of the bound, independant from its position
        sf::Vector2f size_ = sf::Vector2f(0,0);

        //! Half of the size
        sf::Vector2f extent_ = sf::Vector2f(0,0);

        //! Coordinates of the center of the bound
        sf::Vector2f center_ = sf::Vector2f(0,0);

        //! Coordinates of the minimum point of the bound ( top-left )
        sf::Vector2f min_ = sf::Vector2f(0,0);

        //! Coordinates of the maximum point of the bound ( bottom-right )
        sf::Vector2f max_ = sf::Vector2f(0,0);
};

//std::ostream &operator<<(std::ostream &os, Bounds const &b);

#endif // BOUNDS_H
