#include "animator.h"
#include "Core/Graphic/Animation/StateMachine/animatorstate.h"
#include "Core/Graphic/Animation/StateMachine/animatortransitionbase.h"
#include "Core/Graphic/Animation/StateMachine/animatorcondition.h"
#include "Core/Graphic/Animation/animatorcontroller.h"
#include "Core/Graphic/Animation/animationclip.h"
#include "Core/Graphic/Animation/blendtree.h"
#include "Core/Graphic/Animation/animation.h"
#include "Core/Graphic/Animation/StateMachine/statemachinebehavior.h"

#include "Core/Utilities/algorithm.h"

Animator::Animator()
{
    current_playing_animation = new Animation();
    // current_state = entry when animatorController is associated
    is_transiting = false;
    play_back = sf::Time::Zero;
    last_transition_time = sf::Time::Zero;
    has_changed_animation = true;
}

void Animator::update(sf::Time dt){
    if( current_state == nullptr )
        return;

    //increase playback time
    play_back += dt;

    //Engine that executes the StateMachine will be implemented inside the 'Animator'

    //true: the animator is transiting ( waiting for the duration to elapse to jump to the next state )
    if( is_transiting ){
        if( transition_remaining_duration > sf::Time::Zero ){
            transition_remaining_duration -= dt;
        }else{
            //std::cout << "Has transited" << std::endl;
            is_transiting = false;
            current_state = next_state;
            last_transition_time = play_back;

            for( StateMachineBehavior* smb : current_state->behaviors ){
                smb->onStateEnter(nullptr, nullptr, -1);
            }

        }
    }else{

        AnimatorTransitionBase* choosen_one = nullptr;

        //There is solo transition
        if( !soloed_transition.empty() ){
            //Transit to the first that meets the requirements amongs the transitions in the list
            std::list<AnimatorTransitionBase*>::iterator it;
            for( it = soloed_transition.begin(); it != soloed_transition.end() ; it++ ){
                if( !(*it)->mute ){
                    if( !(*it)->conditions.empty() ){
                        if( std::all_of (   (*it)->conditions.begin(), (*it)->conditions.end(),
                                        [&](AnimatorCondition* cond){ return Algorithm::evaluateCondition( runtime_animator_controller->parameters[cond->parameter] , cond); }
                                    ) )
                        {
                            if( !(*it)->can_transition_to_self && (*it)->destination_state == current_state )
                                break;
                            choosen_one = (*it);
                            break;
                        }
                    }
                    if( (*it)->has_exit_time ){
                        if( last_transition_time.asSeconds() + (*it)->exit_time >= play_back.asSeconds() ){
                            //Exit time reached
                            if( !(*it)->can_transition_to_self && (*it)->destination_state == current_state )
                                break;
                            choosen_one = (*it);
                            break;
                        }
                    }
                }
            }

        }else{
            //No solo transition does exist
            //check if there is muted transitions
            std::list<AnimatorTransitionBase*>::iterator it;
            for( it = current_state->transitions.begin(); it != current_state->transitions.end() ; it++ ){
                AnimatorTransitionBase* trans = *it;
                if( !(*it)->mute ){
                    if( !(*it)->conditions.empty() ){
                        if( std::all_of (   (*it)->conditions.begin(), (*it)->conditions.end(),
                                        [&](AnimatorCondition* cond){ return Algorithm::evaluateCondition( runtime_animator_controller->parameters[cond->parameter] , cond); }
                                    ) )
                        {
                            choosen_one = (*it);
                            break;
                        }
                    }
                    if( (*it)->has_exit_time ){
                        if( last_transition_time.asSeconds() + (*it)->exit_time < play_back.asSeconds() ){
                            //Exit time reached
                            choosen_one = (*it);
                            break;
                        }
                    }
                }
            }

        }

        //If a transition is available, make transition, otherwise just animate the AnimationClip inside the State
        if( choosen_one != nullptr ){
            has_changed_animation = true;
            is_transiting = true;
            transition_remaining_duration = sf::seconds( choosen_one->duration );
            next_state = choosen_one->destination_state;
            current_transition = choosen_one;

            for( StateMachineBehavior* smb : current_state->behaviors ){
                smb->onStateExit(nullptr, nullptr, -1);
            }

        }else{
            if( !is_transiting ){
                //Animate the motion inside 'next_state', do not animate while transiting

                update_animation(dt);
                //Same code as in "Animation"

                has_changed_animation = false;

                for( StateMachineBehavior* smb : current_state->behaviors ){
                    smb->onStateUpdate(nullptr, nullptr, -1);
                }

            }
        }

    }

}

void Animator::update_animation(sf::Time dt){
//    std::cout << "Trying to update frame " << "state=" << current_state->name << ", dt'=" << dt.asMilliseconds()  << std::endl;
    current_playing_animation = current_state->animation;

    if( current_playing_animation != nullptr ){
        if( has_changed_animation ){
            //reset animation's values.
            current_playing_animation->stop();
            current_playing_animation->play();
        }

        //Make a step in the animation
        if( current_state->motion_type == MotionType::IsAnimationClip ){
            auto speed = runtime_animator_controller->parameters.find( current_state->speed.parameter );
            current_playing_animation->animate_clip( sf::seconds(       (current_state->speed.active && speed != runtime_animator_controller->parameters.end() )
                                                                        ? runtime_animator_controller->getParameter<float>( current_state->speed.parameter )*dt.asSeconds()
                                                                        : current_state->speed.default_value*dt.asSeconds() )
                                                     );

        }else if( current_state->motion_type == MotionType::IsBlendTree ){
            auto speed = runtime_animator_controller->parameters.find( current_state->speed.parameter );
            current_playing_animation->animate_blend_tree( sf::seconds(       (current_state->speed.active && speed != runtime_animator_controller->parameters.end() )
                                                                        ? runtime_animator_controller->getParameter<float>( current_state->speed.parameter )*dt.asSeconds()
                                                                        : current_state->speed.default_value*dt.asSeconds() )
                                                            );
        }
    }

}
