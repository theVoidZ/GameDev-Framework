#ifndef EVENTVELOCITY_H
#define EVENTVELOCITY_H

#include <iostream>
#include <iomanip>

#include <SFML/System/Vector2.hpp>

#include "time_management/event.h"
#include "Assets/TestCases/velocitydef.h"

class EventVelocity : public Event
{
    public:
        EventVelocity();
        ~EventVelocity();

    public:
        static EventVelocity* create_event( VelocityDef* target, sf::Vector2f old_vel, sf::Vector2f new_vel, unsigned long timestamp );

    public:
        void verbose() const;

    public:
        bool exec();
        bool reverse_exec();

    public:
        sf::Vector2f old_vel;
        sf::Vector2f new_vel;
};

#endif // EVENTVELOCITY_H
