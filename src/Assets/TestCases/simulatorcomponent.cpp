#include "simulatorcomponent.h"
#include "kernel/gameobject.h"
#include "Core/System/transform.h"

#include "Assets/TestCases/velocitydef.h"
#include "time_management/timekeeper.h"
#include "time_management/eventvelocity.h"
#include "time_management/eventtranslation.h"
#include "time_management/eventvaluechange.h"

#include "time_management/chrono.h"

SimulatorComponent::SimulatorComponent()
{

}

void SimulatorComponent::init(){
    ch = game_object()->getComponent<Chrono>();
}

void SimulatorComponent::update(sf::Time dt){
    // SIMPLE behavior, ( moving with x velocity )
    // velocity controler

    if( ch == nullptr )
        return;

    if( ch->status_ == ChronoPlayStatus::BACKWARD )
        return;

    // step = 0 : idle
    if( steps == 0 ){
        if( ch != nullptr ){
            if( ch->lifetime.asSeconds() >= 1.f ){
    //            std::cout << "Toward moving @" << game_object()->life_time.asSeconds() << std::endl;
                // start moving for 4 sec
                VelocityDef* vel = game_object()->getComponent<VelocityDef>();
                if( vel != nullptr ){
                    sf::Vector2f old = sf::Vector2f(vel->spx, vel->spy);
                    vel->change_velocity(100.f, 0.f);

                    //! Callback for timekeeper
                    foreach (TimeKeeper* tk, game_object()->getComponentsOfType<TimeKeeper>() ) {
                        tk->onVelocityChanged(vel, old, sf::Vector2f( vel->spx, vel->spy), ch->lifetime.asMilliseconds() );
                        tk->onValueChanged(this, 0, 1, ch->lifetime.asMilliseconds() );
                    }
                    steps = 1;

                }
            }
        }
    }else if ( steps == 1 ){
        t += dt;
        if( ch != nullptr ){
            if( ch->lifetime.asSeconds() >= 6.f ){
    //            std::cout << "Stopping @" << game_object()->life_time.asSeconds() << std::endl;
                VelocityDef* vel = game_object()->getComponent<VelocityDef>();
                if( vel != nullptr ){
                    sf::Vector2f old = sf::Vector2f(vel->spx, vel->spy);
                    vel->change_velocity(0.f, 0.f);

                    //! Callback for timekeeper
                    foreach (TimeKeeper* tk, game_object()->getComponentsOfType<TimeKeeper>() ) {
                        tk->onVelocityChanged(vel, old, sf::Vector2f( vel->spx, vel->spy), ch->lifetime.asMilliseconds() );
                        tk->onValueChanged(this, 1, 2, ch->lifetime.asMilliseconds() );
                    }
                    steps = 2;
                }
            }else{
                /*
                if( t > sf::seconds(1.f) ){
                    t = sf::Time::Zero;
                    VelocityDef* vel = game_object()->getComponent<VelocityDef>();
                    if( vel != nullptr ){
                        sf::Vector2f old = vel->getPosition();
                        vel->change_position( sf::Vector2f ( vel->getPosition().x , vel->getPosition().y + 35 ) );

                        //! Callback for timekeeper
                        foreach (TimeKeeper* tk, game_object()->getComponentsOfType<TimeKeeper>() ) {
                            tk->onTranslationChanged(vel, old, vel->getPosition(), game_object()->life_time.asMilliseconds() );
                        }
                    }
                }
                */
            }
        }
    }else if( steps == 2 ){
        // AFK: trigger rewind

    }
}

