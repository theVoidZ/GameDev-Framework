#ifndef EVENTVALUECHANGE_H
#define EVENTVALUECHANGE_H

#include <iostream>
#include <iomanip>

#include "time_management/event.h"

class SimulatorComponent;

class EventValueChange : public Event
{
    public:
        EventValueChange();
        ~EventValueChange();

    public:
        static EventValueChange* create_event(SimulatorComponent* target, int old_val, int new_val, unsigned long timestamp );

    public:
        void verbose() const;

    public:
        bool exec();
        bool reverse_exec();

    public:
        int old_val;
        int new_val;

};

#endif // EVENTVALUECHANGE_H
