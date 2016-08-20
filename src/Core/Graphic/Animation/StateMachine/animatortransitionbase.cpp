#include "animatortransitionbase.h"


#include "Core/Graphic/Animation/StateMachine/animatorstate.h"
#include "Core/Graphic/Animation/StateMachine/animatorcondition.h"

AnimatorTransitionBase::AnimatorTransitionBase()
{

}

AnimatorTransitionBase::~AnimatorTransitionBase(){

}

void AnimatorTransitionBase::addCondition(std::string parameter, AnimatorConditionMode mode, float threshold){
    conditions.push_back(new AnimatorCondition( parameter, mode, threshold));
}
