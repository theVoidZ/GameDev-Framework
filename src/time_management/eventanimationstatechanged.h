#ifndef EVENTANIMATIONFINISHED_H
#define EVENTANIMATIONFINISHED_H

#include <iostream>
#include <iomanip>

#include "time_management/event.h"

class Animation;

class EventAnimationStateChanged : public Event
{
    public:
        EventAnimationStateChanged();
        ~EventAnimationStateChanged();

    public:
        static EventAnimationStateChanged* create_event(Animation* target, int old_status, int new_status, unsigned long timestamp );

    public:
        void verbose() const;

    public:
        bool exec();
        bool reverse_exec();

    public:
        int old_status;
        int new_status;

};

#endif // EVENTANIMATIONFINISHED_H
