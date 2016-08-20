#ifndef ANIMATORSTATE_H
#define ANIMATORSTATE_H

#include <QString>

#include <list>
#include <string>

#include "kernel/object.h"
#include "Core/Graphic/Animation/StateMachine/motiontype.h"

class AnimatorTransitionBase;
class StateMachineBehavior;
class Animation;

class AnimatorState : public gdf::kernel::Object
{
    public:
        struct Parametrized{
            //Order is important.
            //! Default value for this variable.
            float default_value;
            //! Attached parameter for this variable.
            std::string parameter;
            //! Set whether the parameter is active or the default value.
            bool active;
        };

    public:
        AnimatorState(std::string name_="");
        ~AnimatorState();

    public:
        //! Attach a state machine behavior to this state
        template< typename T >
        StateMachineBehavior* addStateMachineBehavior();

        //! Add an outgoing transition from this state to destination_state
        AnimatorTransitionBase* addTransition(AnimatorState* destination_state);

        //! remove a transition attached to this state
        void removeTransition(AnimatorTransitionBase* transition);
        void removeTransition(AnimatorState* state);

        //! remove a state machine behavior attached to this state
        //!
    public:
        //! The Behavior list assigned to this state.
        std::list<StateMachineBehavior*> behaviors;
        //!	The transitions that are going out of the state.
        std::list<AnimatorTransitionBase*> transitions;
        //! Animation attached to this state ( instead of Motion )
        Animation* animation = nullptr;


    public:
        // Public members.
        //! 'mirror' args of the animation
        Parametrized mirror = {false, "", false};
        //! 'speed' args of the animation
        Parametrized speed = {1.0f, "", false};

    public:
        //! Holds the tag of the state
        std::string tag = "";

        //! ???
        float cycle_offset = 0.0f; // frame where loop starts. ?

        //! Specify whether it contains a AnimationClip or BlendTree
        MotionType motion_type = MotionType::IsAnimationClip;

};

#endif // ANIMATORSTATE_H
