#include "ray.h"

Ray::Ray(sf::Vector2f origin, sf::Vector2f direction)
{
    this->origin = origin;
    this->direction = direction;
}

sf::Vector2f Ray::getPoint(float distance){
    sf::Vector2f point;
    //! FIXME: if direction.x = 0 then a is undefined : USE COSE/SIN instead of line-equation
    float angle = atan2(direction.y, direction.x) * 180 / M_PI;

    point.x = cos(angle) * distance + origin.x;
    point.y = sin(angle) * distance + origin.y;
    return point;
}

