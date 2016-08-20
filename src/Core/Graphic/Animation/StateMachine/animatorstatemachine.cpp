#include "animatorstatemachine.h"

#include "Core/Graphic/Animation/StateMachine/statemachinebehavior.h"
#include "Core/Graphic/Animation/StateMachine/animatorstate.h"

AnimatorStateMachine::AnimatorStateMachine(std::string name)
{
    this->name_ = name;

    //State names must contain StateMachine's Name
    entry_state = new AnimatorState( this->name_ + ":" + "Entry");
    exit_state = new AnimatorState( this->name_ + ":" + "Exit");
    any_state = new AnimatorState( this->name_ + ":" + "Any");

}


AnimatorState* AnimatorStateMachine::addState(std::string name){
    AnimatorState* state =  new AnimatorState( name );
    states.push_back( state );
    return state;
}
