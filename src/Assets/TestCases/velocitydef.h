#ifndef VELOCITYDEF_H
#define VELOCITYDEF_H

#include <iostream>
#include <SFML/System/Vector2.hpp>

#include "Core/System/monobehavior.h"

class VelocityDef   : public MonoBehavior
{
    Q_OBJECT
    public:
        VelocityDef();

        // Simulating Transform
        //do trigger event
        sf::Vector2f getPosition();


        // go not trigger event
        void change_position( sf::Vector2f pos );
        void change_velocity(float spx, float spy);

        void update(sf::Time dt);

    public:
        float spx = 0.f;
        float spy = 0.f;
        sf::Vector2f velocity;

};

#endif // VELOCITYDEF_H
