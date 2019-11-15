#include "animatortransitionbase.h"


#include "animatorstate.h"
#include "animatorcondition.h"

namespace gdf {
namespace animation{

AnimatorTransitionBase::AnimatorTransitionBase()
{
    this->duration_ = new sf::Time();
    *duration_ = sf::Time::Zero;
}

AnimatorTransitionBase::AnimatorTransitionBase(AnimatorState *source, AnimatorState *dest){
    duration_ = new sf::Time();
    *duration_ = sf::Time::Zero;

    source_state_ = source;
    destination_state_ = dest;
}

AnimatorTransitionBase::~AnimatorTransitionBase(){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatorTransitionBase::verbose(){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatorTransitionBase::addCondition(std::string parameter, AnimatorConditionMode mode, float threshold){
    conditions_.push_back(new AnimatorCondition( parameter, mode, threshold));
}

sf::Time AnimatorTransitionBase::exit_time() const{
    return exit_time_;
}

sf::Time AnimatorTransitionBase::duration() const{
    return *duration_;
}

void AnimatorTransitionBase::set_exit_time(sf::Time duration){
    has_exit_time_ = true;
    exit_time_ = duration;
}

}}
