#include "eventanimationstatechanged.h"

#include "Core/Graphic/Animation/animation.h"

EventAnimationStateChanged::EventAnimationStateChanged()
{

}

EventAnimationStateChanged::~EventAnimationStateChanged(){

}

EventAnimationStateChanged* EventAnimationStateChanged::create_event(Animation *target, int old_status, int new_status, unsigned long timestamp){
    EventAnimationStateChanged* ev = new EventAnimationStateChanged();
    ev->target = target;
    ev->old_status = old_status;
    ev->new_status = new_status;
    ev->timestamp = timestamp;

    return ev;
}

void EventAnimationStateChanged::verbose() const{
    std::cout << FYELLOW << std::setw(6) << timestamp << " ms " << std::setw(18) << "+Animation:" << "    old("<< std::setw(8) <<  ( (old_status == 1 ) ? "Playing": "Finished" ) << ")\t→\tnew(" << std::setw(8) << ( (new_status == 1 ) ? "Playing": "Finished" ) << ")" << RESET << std::endl;
}

bool EventAnimationStateChanged::exec(){
    //! DUMMY: not chechking all the cases
    dynamic_cast<Animation*>(target)->play();
}

bool EventAnimationStateChanged::reverse_exec(){
    //! DUMMY: not chechking all the cases
    dynamic_cast<Animation*>(target)->play_reverse();
}
