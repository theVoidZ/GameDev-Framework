#ifndef ANIMATORSTATEMACHINE_H
#define ANIMATORSTATEMACHINE_H

#include <string>
#include <list>
#include <vector>

#include "kernel/object.h"

class StateMachineBehavior;
class AnimatorState;

class AnimatorStateMachine : public gdf::kernel::Object
{
    public:
        AnimatorStateMachine(std::string name_="StateMachine");

    public:
        AnimatorState* addState(std::string name_ );

    public:
        //! Behaviours attached to the state machine
        std::list< StateMachineBehavior* > behaviours;

        //!
        AnimatorState* entry_state = nullptr;
        AnimatorState* exit_state = nullptr;
        AnimatorState* any_state = nullptr;

        //! Sub states machines
        std::list<AnimatorStateMachine*> state_machines;

        //! All states
        std::vector< AnimatorState* > states;

};

#endif // ANIMATORSTATEMACHINE_H
