#include "eventtranslation.h"

#include "Assets/TestCases/velocitydef.h"

EventTranslation::EventTranslation()
{

}

EventTranslation::~EventTranslation(){

}

EventTranslation* EventTranslation::create_event(VelocityDef *target, sf::Vector2f old_pos, sf::Vector2f new_pos, unsigned long timestamp){
    EventTranslation* ev = new EventTranslation();
    ev->target = target;
    ev->old_pos = old_pos;
    ev->new_pos = new_pos;
    ev->timestamp = timestamp;

    return ev;
}

void EventTranslation::verbose() const{
    std::cout << FYELLOW << std::setw(6) << timestamp << " ms " << std::setw(18) << "+Translation:" << "    old("<< std::setw(3) << (int)old_pos.x << ", " << std::setw(3) << (int) old_pos.y << ") \t→\tnew(" << std::setw(3) << (int)new_pos.x << ", " << std::setw(3) << (int)new_pos.y << ")" << RESET << std::endl;
}

bool EventTranslation::exec(){
    //! NOTE: Can avoid absolute values. and use translation instead
    dynamic_cast<VelocityDef*>(target)->VelocityDef::change_position( new_pos );
}

bool EventTranslation::reverse_exec(){
    //! NOTE: Can avoid absolute values. and use translation instead
    dynamic_cast<VelocityDef*>(target)->VelocityDef::change_position( old_pos );
}
