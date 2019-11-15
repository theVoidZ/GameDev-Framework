#include "animatorstate.h"

#include "animatortransitionbase.h"
#include "animation2.h"

namespace gdf {
namespace animation{

AnimatorState::AnimatorState(std::string name)
{
    this->name_ = name;

}

AnimatorState::~AnimatorState(){
    outgoing_transitions_.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatorState::verbose(){

}

AnimatorTransitionBase* AnimatorState::add_transition(AnimatorState* destination_state){

    //Otherwise, it doesn't exist
    AnimatorTransitionBase* t1 = new AnimatorTransitionBase(this, destination_state);
    outgoing_transitions_.push_back( t1 );

    AnimatorTransitionBase* t2 = new AnimatorTransitionBase(destination_state, this);
    incoming_transitions_.push_back( t2 );

    // Bind both transitions
    t1->opposite_transition = t2;
    t2->opposite_transition = t1;
    t2->duration_ = t1->duration_; // Binds t2 duration to t1 duration.

    // Return the normal Transition and not the BDN_Transition
    return t1;

}

}}
