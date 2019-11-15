#ifndef ANIMATORSTATE_H
#define ANIMATORSTATE_H

#include <list>
#include <string>

#include "object.h"


namespace gdf {
namespace animation{


class AnimatorTransitionBase;
class Animation2;

enum class MotionType{
    IsAnimationClip,
    IsBlendTree
};

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

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        void verbose();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////


    public:
        //! Attach a state machine behavior to this state

        //! Add an outgoing transition from this state to destination_state
        AnimatorTransitionBase* add_transition(AnimatorState* destination_state);

    public:
        //!	The transitions that are going out of the state.
        std::list<AnimatorTransitionBase*> outgoing_transitions_;
        std::list<AnimatorTransitionBase*> incoming_transitions_;

        //! Animation attached to this state ( instead of Motion )
        Animation2* animation_ = nullptr;


    public:
        // Public members.
        //! 'mirror' args of the animation
        Parametrized mirror = {false, "", false};
        //! 'speed' args of the animation
        Parametrized speed = {1.0f, "", false};

    public:
        //! Holds the tag of the state
        //! Used instead of names, to denote a group of state having same features
        std::string tag = "";

        //! ???
//        float cycle_offset = 0.0f; // frame where loop starts. ?

};

}}

#endif // ANIMATORSTATE_H
