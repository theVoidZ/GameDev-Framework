#include "eventvelocity.h"

#include "Assets/TestCases/velocitydef.h"

EventVelocity::EventVelocity()
{

}

EventVelocity::~EventVelocity(){

}

EventVelocity* EventVelocity::create_event(VelocityDef *target, sf::Vector2f old_vel, sf::Vector2f new_vel, unsigned long timestamp){
    EventVelocity* ev = new EventVelocity();
    ev->target = target;
    ev->old_vel = old_vel;
    ev->new_vel = new_vel;
    ev->timestamp = timestamp;

    return ev;
}

void EventVelocity::verbose() const{
    std::cout << FYELLOW << std::setw(6) << timestamp << " ms "  << std::setw(18) << "+Velocity:" << "    old("<< std::setw(3) << (int)old_vel.x << ", " << std::setw(3) << (int) old_vel.y << ") \t→\tnew(" << std::setw(3) << (int)new_vel.x  << ", " << std::setw(3) << (int)new_vel.y << ")" << RESET << std::endl;
}

bool EventVelocity::exec(){
    dynamic_cast<VelocityDef*>(target)->change_velocity( new_vel.x, new_vel.y );
}

bool EventVelocity::reverse_exec(){
    dynamic_cast<VelocityDef*>(target)->change_velocity( -old_vel.x, -old_vel.y );
}
