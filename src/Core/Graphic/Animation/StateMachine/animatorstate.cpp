#include "animatorstate.h"

#include "Core/Graphic/Animation/StateMachine/statemachinebehavior.h"
#include "Core/Graphic/Animation/StateMachine/animatortransitionbase.h"
#include "Core/Graphic/Animation/StateMachine/statemachinebehavior.h"
#include "Core/Graphic/Animation/animation.h"

AnimatorState::AnimatorState(std::string name)
{
    this->name_ = name;

}

AnimatorState::~AnimatorState(){
    transitions.clear();
    behaviors.clear();
}

template< typename T >
StateMachineBehavior* AnimatorState::addStateMachineBehavior(){
    behaviors.push_back( new T() );
}

AnimatorTransitionBase* AnimatorState::addTransition(AnimatorState* destination_state){
    // Check existence of such transition. ( Allow only one transition between two same state )
    std::list<AnimatorTransitionBase*>::iterator it;
    for( it = transitions.begin(); it != transitions.end(); it++ ){
        if( (*it)->destination_state == destination_state ){
            return *it;
        }
    }

    //Otherwise, it doesn't exist
    AnimatorTransitionBase* t = new AnimatorTransitionBase();
    t->destination_state = destination_state;
    transitions.push_back( t );
    return t;

}

void AnimatorState::removeTransition(AnimatorTransitionBase* transition){
    // Check existence of such transition. ( Allow only one transition between two same state )
    transitions.remove( transition );
}

void AnimatorState::removeTransition(AnimatorState *state){
    transitions.remove_if( [state](AnimatorTransitionBase* t){ return t->destination_state == state;} );
}
