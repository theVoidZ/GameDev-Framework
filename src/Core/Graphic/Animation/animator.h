#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <algorithm>

#include "Core/System/behavior.h"
#include "Core/Graphic/Animation/animatorcullingmode.h"
#include "Core/Graphic/Animation/animatorupdatemode.h"

class AnimatorCondition;
class AnimatorController;
class AnimatorState;
class AnimatorTransitionBase;
class Animation;

class Animator : public Behavior
{
    public:
        Animator();

    public:
        void update( sf::Time dt );

    protected:
        void update_animation( sf::Time dt );

    public:
//        void setDefaultState( AnimatorState | std::string );

    public:
        AnimatorCullingMode culling_mode;
        AnimatorUpdateMode update_mode;
        AnimatorController* runtime_animator_controller;

    public:
        AnimatorState* current_state;
        //While transiting, keeps track of the next state and the duration of the transition, because time will run over several updates
        //next_step will get lost otherwise.
        AnimatorState* next_state;

        AnimatorTransitionBase* current_transition;

        bool is_transiting;
        sf::Time transition_remaining_duration;

        std::list<AnimatorTransitionBase*> soloed_transition;

        //Time of the whole animator
        sf::Time play_back;
        //Time ( moment) of the last loaded state. ( to compute exit_time )
        sf::Time last_transition_time;

        bool has_changed_animation;

    public:
        Animation* current_playing_animation = nullptr;

};

#endif // ANIMATOR_H
