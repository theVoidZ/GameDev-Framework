#ifndef ANIMATORTRANSITIONBASE_H
#define ANIMATORTRANSITIONBASE_H

#include <list>
#include <string>

#include "kernel/object.h"
#include "Core/Graphic/Animation/StateMachine/animatorconditionmode.h"

class AnimatorState;
class AnimatorCondition;

class AnimatorTransitionBase : public gdf::kernel::Object
{
    public:
        AnimatorTransitionBase();
        ~AnimatorTransitionBase();

    public:
        //! Add new condition to this transition ( do not check validity of the parameter )
        void addCondition( std::string parameter, AnimatorConditionMode mode, float threshold );

    public:
        std::list<AnimatorCondition*> conditions;

        AnimatorState* destination_state = nullptr;

        bool mute = false; // is ignored
        bool solo = false; // Set active and mute others 'non-soloed'

        bool can_transition_to_self = true;
        float duration = 0.0f; // Duration of the transition
        bool has_exit_time = true;
        float exit_time = 0.0f;

};

#endif // ANIMATORTRANSITIONBASE_H
