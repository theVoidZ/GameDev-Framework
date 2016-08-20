#include "eventvaluechange.h"

#include "Assets/TestCases/simulatorcomponent.h"

EventValueChange::EventValueChange()
{

}

EventValueChange::~EventValueChange(){

}

EventValueChange* EventValueChange::create_event(SimulatorComponent *target, int old_val, int new_val, unsigned long timestamp){
    EventValueChange* ev = new EventValueChange();
    ev->target = target;
    ev->old_val = old_val;
    ev->new_val = new_val;
    ev->timestamp = timestamp;
    return ev;
}

void EventValueChange::verbose() const{
    std::cout << FYELLOW << std::setw(6) << timestamp << " ms " << std::setw(18) << "+ValueChanged:" << "    old("<< std::setw(8) << (int)old_val << ")\t→\tnew(" << std::setw(8) << (int)new_val << ")" << RESET << std::endl;
}

bool EventValueChange::exec(){
    dynamic_cast<SimulatorComponent*>(target)->steps = new_val;
}

bool EventValueChange::reverse_exec(){
    dynamic_cast<SimulatorComponent*>(target)->steps = old_val;
}
