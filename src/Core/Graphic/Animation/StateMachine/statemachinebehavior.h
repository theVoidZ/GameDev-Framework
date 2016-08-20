#ifndef STATEMACHINEBEHAVIOUR_H
#define STATEMACHINEBEHAVIOUR_H

#include "Core/scriptableobject.h"

class Animator;
class AnimatorStateMachine;
class AnimatorState;

/**
 * ScriptableObject are objects that dont need to be attached to a GameObject.
 */
class StateMachineBehavior : public ScriptableObject
{
    public:
        StateMachineBehavior();

    public:
        void onStateMachineEnter(Animator* animator, AnimatorStateMachine* state_machine);
        void onStateMachineExit(Animator* animator, AnimatorStateMachine* state_machine);

    public:
        //Messages
        virtual void onStateEnter(Animator* animator, AnimatorState* animator_state, int layer_index) = 0;
        virtual void onStateExit(Animator* animator, AnimatorState* animator_state, int layer_index) = 0;
        virtual void onStateIK(Animator* animator, AnimatorState* animator_state, int layer_index) = 0;
        virtual void onStateMove(Animator* animator, AnimatorState* animator_state, int layer_index) = 0;
        virtual void onStateUpdate(Animator* animator, AnimatorState* animator_state, int layer_index) = 0;

};

#endif // STATEMACHINEBEHAVIOUR_H
