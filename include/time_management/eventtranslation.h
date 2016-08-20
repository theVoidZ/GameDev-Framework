#ifndef EVENTTRANSLATION_H
#define EVENTTRANSLATION_H

#include <iomanip>
#include <iostream>
#include <SFML/System/Vector2.hpp>

#include "time_management/event.h"
#include "Assets/TestCases/velocitydef.h"

class EventTranslation : public Event
{
    public:
        EventTranslation();
        ~EventTranslation();

    public:
        static EventTranslation* create_event(VelocityDef* target, sf::Vector2f old_pos, sf::Vector2f new_pos, unsigned long timestamp );

    public:
        void verbose() const;

    public:
        bool exec();
        bool reverse_exec();

    public:
        sf::Vector2f old_pos;
        sf::Vector2f new_pos;


};

#endif // EVENTTRANSLATION_H
