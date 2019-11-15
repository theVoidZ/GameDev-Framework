#include "animatorstatemachine.h"

#include "animatorstate.h"
#include "animatortransitionbase.h"

namespace gdf {
namespace animation{

AnimatorStateMachine::AnimatorStateMachine(std::string name)
{
    this->name_ = name;

}

void AnimatorStateMachine::verbose(){

}

AnimatorState* AnimatorStateMachine::add_state(std::string name){
    AnimatorState* state =  new AnimatorState( name );
    states_.push_back( state );
    return state;
}

AnimatorTransitionBase* AnimatorStateMachine::add_transition(AnimatorState *source_state, AnimatorState *destination_state){
    if(source_state != nullptr ){
        AnimatorTransitionBase* trans = source_state->add_transition(destination_state);
        transitions_.push_back(trans);
        return trans;
    }
}

AnimatorState* AnimatorStateMachine::find(std::string state_name){
    std::vector< AnimatorState* >::iterator itc = states_.begin();
    for(; itc != states_.end(); itc++ ){
        if( (*itc)->name() == state_name ){
            return (*itc);
        }
    }
    return nullptr;
}

AnimatorTransitionBase* AnimatorStateMachine::find(std::string trans_source_name, std::string trans_dest_name){
    std::vector< AnimatorTransitionBase* >::iterator itc = transitions_.begin();
    for(; itc != transitions_.end(); itc++ ){
        if( (*itc)->source_state_->name() == trans_source_name && (*itc)->destination_state_->name() == trans_dest_name ){
            return (*itc);
        }
    }
    return nullptr;
}

}}
