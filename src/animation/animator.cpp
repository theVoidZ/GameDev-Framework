#include "animator.h"
#include "animatorstate.h"
#include "animatortransitionbase.h"
#include "animatorcondition.h"
#include "animatorcontroller.h"
#include "animationclip.h"
#include "blendtree.h"
#include "animation2.h"

#include "spriterenderer.h"
#include "gameobject.h"

#include "algorithm.h"
#include "monobehavior.h"
#include "gameinfo.h"
#include "chrono.h"
#include <fstream>
#include "tracker_ptr.h"
#include "animatorstatemachine.h"

namespace gdf {
namespace animation{

Animator::Animator(){

}

void Animator::update(sf::Time dt){
    if( current_state == nullptr )
        return;

    //increase playback time
    play_back += gdf::system::Algorithm::abs(dt);

    //true: the animator is transiting ( waiting for the duration to elapse to jump to the next state )
    if( is_transiting ){
        if( remaining_transition_duration > sf::Time::Zero ){
            remaining_transition_duration -= gdf::system::Algorithm::abs(dt);
        }else{
            //std::cout << BOLD << BRED << FYELLOW << "\tAnimator finisehd TRANSITING " << (next_transition?next_transition->source_state_->name():"nullptr")<< "->" << (next_transition?next_transition->destination_state_->name():"nullptr") << RESET << std::endl;
            //std::cout << "Param.Direction" << *(float*)runtime_animator_controller->parameters["Direction"] << std::endl;

            //! WARNING: SOme dt are LOST
            is_transiting = false;
            current_state = next_state;
            last_transition_time = play_back;

            current_playing_animation = current_state->animation_;

            if( game_object()->chrono().get()->status_ == gdf::temporal::ChronoPlayStatus::FORWARD ){
                current_playing_animation->game_object = game_object();
                current_playing_animation->play_back = sf::Time::Zero;
                current_playing_animation->should_plays = true;
                current_playing_animation->is_playing = true;
            }

            //! CLBK: Finished TRANSITING
            std::list<gdf::kernel::MonoBehavior*> l = game_object()->scene()->root().get()->get_components_in_children_of_type<gdf::kernel::MonoBehavior>();
            for (gdf::kernel::MonoBehavior* mb : l) {
                //! CLBK: onClosed
                mb->on_exit_state(next_transition);
            }
            next_transition = nullptr;
        }
    }else{
        ///////////////////////////////////////////////////////////////////////////////
        /// SOLOED TRANSITION
        ///////////////////////////////////////////////////////////////////////////////

        bool soloed_transition_exist_ = false;

        //Browse solo transition first of the current state
        std::list<AnimatorTransitionBase*>::iterator it;
        for( it = current_state->outgoing_transitions_.begin(); it != current_state->outgoing_transitions_.end() ; it++ ){

            // If SOLO transition ( priority )
            if( (*it)->solo_ == true && !(*it)->mute_ ){
                soloed_transition_exist_ = true;

                if( !(*it)->conditions_.empty() ){

                    //Self transit not allowed
                    if( !(*it)->can_transition_to_self_ && (*it)->destination_state_ == current_state )
                        break;

                    // Check transition condition
                    if( std::all_of (   (*it)->conditions_.begin(), (*it)->conditions_.end(),
                                    [&](AnimatorCondition* cond){
                                        auto p = runtime_animator_controller->parameters.find(cond->parameter);
                                        if( p != runtime_animator_controller->parameters.end() ){
                                            return gdf::animation::AnimatorCondition::evaluate_condition( runtime_animator_controller->parameters.at(cond->parameter) , cond);
                                        }else{return false;}
                                    }
                                ) )
                    {
                        // Will transit
//                        std::cout << BOLD << BRED << FYELLOW << "SOLO TRANSITION FOUND (condition) " << current_state->name() << "->" << (*it)->destination_state_->name() << RESET << std::endl;
                        next_transition  = (*it);
                        break;
                    }
                }

                // If condition are not required to transit
                if( (*it)->has_exit_time_ ){
                    if( last_transition_time + (*it)->exit_time() <= play_back ){
                        //Exit time elapsed for (*it)
//                        std::cout << BOLD << BRED << FYELLOW << "SOLO ANIMATION FOUND (exit_time) " << current_state->name() << "->" << (*it)->destination_state_->name() << RESET << std::endl;
                        next_transition  = (*it);
                        break;
                    }
                }

            }
        }

        if( !soloed_transition_exist_ ){
        ///////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////
            //Browse solo transition first of the current state
            std::list<AnimatorTransitionBase*>::iterator it;
            for( it = current_state->outgoing_transitions_.begin(); it != current_state->outgoing_transitions_.end() ; it++ ){

                // If not SOLO transition ( priority ) ( remaining not muted )
                if( !(*it)->solo_ == true && !(*it)->mute_ ){

                    if( !(*it)->conditions_.empty() ){

                        //Self transit not allowed
                        if( !(*it)->can_transition_to_self_ && (*it)->destination_state_ == current_state )
                            break;

                        // Check transition condition
                        if( std::all_of (   (*it)->conditions_.begin(), (*it)->conditions_.end(),
                                        [&](AnimatorCondition* cond){
                                            auto p = runtime_animator_controller->parameters.find(cond->parameter);
                                            if( p != runtime_animator_controller->parameters.end() ){
                                                return gdf::animation::AnimatorCondition::evaluate_condition( runtime_animator_controller->parameters.at(cond->parameter) , cond);
                                            }else{return false;}
                                        }
                                    ) )
                        {
                            // Will transit
//                            std::cout << BOLD << BRED << FYELLOW << "!SOLO ANIMATION FOUND (condition) " << current_state->name() << "->" << (*it)->destination_state_->name() << RESET << std::endl;
                            next_transition  = (*it);
                            break;
                        }

                    }

                    // If condition are not required to transit
                    if( (*it)->has_exit_time_ ){
                        if( last_transition_time + (*it)->exit_time() <= play_back ){
                            //Exit time elapsed for (*it)
                            next_transition  = (*it);
//                            std::cout << BOLD << BRED << FYELLOW << "!SOLO ANIMATION FOUND (exit_time) " << current_state->name() << "->" << (*it)->destination_state_->name() << RESET << std::endl;
                            break;
                        }
                    }

                }
            }
        }

        //If a transition is available, make transition ( duration included ), otherwise just animate the AnimationClip inside the State
        if( next_transition  != nullptr ){
            // Record data about previous animation first
            if( current_playing_animation == nullptr ){
                current_playing_animation = current_state->animation_;
                if( current_playing_animation->game_object == nullptr || current_playing_animation->game_object != game_object() ){
                    current_playing_animation->game_object = game_object();
                }
            }

            if( current_playing_animation != nullptr ){
                current_playing_animation->reset();
            }


            is_transiting = true;
            remaining_transition_duration = next_transition ->duration();
            next_state = next_transition ->destination_state_;

            //std::cout << BOLD << BRED << FYELLOW << "Animator started TRANSITING " << (next_transition?next_transition->source_state_->name():"nullptr")<< "->" << (next_transition?next_transition->destination_state_->name():"nullptr") << RESET << std::endl;

//            gdf::temporal::animator::animator_started_transition(game_object(), &next_transition, next_transition );

            //! CLBK: Start TRANSITING
            std::list<gdf::kernel::MonoBehavior*> l = game_object()->scene()->root().get()->get_components_in_children_of_type<gdf::kernel::MonoBehavior>();
            for (gdf::kernel::MonoBehavior* mb : l) {
                //! CLBK: onClosed
//                std::cout << current_transition->source_state_->name() << ":" << current_transition->destination_state_->name() << std::endl;
                mb->on_enter_state(next_transition);
            }
        }else{
            if( !is_transiting ){
                //Animate the motion inside 'next_state', do not animate while transiting

                //! NOTE: Passing the gameobject to the Animiation through this method.
                update_animation(dt);

            }
        }

    }

}

void Animator::update_animation(sf::Time dt){

//    std::cout << "Trying to update frame " << "state=" << current_state->name() << ", dt'=" << dt.asMilliseconds()  << std::endl;
    current_playing_animation = current_state->animation_;
    if( current_playing_animation->game_object == nullptr || current_playing_animation->game_object != game_object() ){
        current_playing_animation->game_object = game_object();
    }

    if( current_playing_animation != nullptr ){
        // Retrieving param to pass to BlendTree
        gdf::graphic::Sprite2D* next_sprt = nullptr;
        if( current_playing_animation->blend_tree != nullptr ){
            auto param = runtime_animator_controller->parameters.find( current_playing_animation->blend_tree->parameter_ );
            if( param != runtime_animator_controller->parameters.end() ){
                // Mechanism update
                next_sprt = current_playing_animation->step(dt, runtime_animator_controller->getParameter<float>(current_playing_animation->blend_tree->parameter_) );
            }else{
                goto xxx;
            }
        }else{
            xxx:
            next_sprt = current_playing_animation->step(dt, 0 );
        }

        // Graphic update
        if( game_object() != nullptr ){
            //! NOTE: Has to be changed into a tracker_ptr<SpriteRenderer>
            gdf::graphic::SpriteRenderer* sprt = game_object()->get_component<gdf::graphic::SpriteRenderer>();
            if( sprt != nullptr ){
                sprt->setSprite2D( next_sprt );
            }
        }
    }


}

}}
