#include "moveobject.h"

#include "Core/System/transform.h"
#include "Assets/TestCases/velocitydef.h"
#include "time_management/timekeeper.h"
#include "time_management/eventvelocity.h"
#include "time_management/eventtranslation.h"
#include "time_management/timewinder.h"

#include "time_management/chrono.h"

MoveObject::MoveObject()
{

}

void MoveObject::update(sf::Time dt){
    if( game_object() == nullptr )
        return;

    float speed_per_sec = 300.f;
    sf::Vector2f velocity;

    // while there are pending events...
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ){
        velocity.x = (-speed_per_sec/1000.f/1000.f) * dt.asMicroseconds();
    }else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ){
        velocity.x = (+speed_per_sec/1000/1000) * dt.asMicroseconds();
    }

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ){
        velocity.y = (-speed_per_sec/1000/1000) * dt.asMicroseconds();
    }else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ){
        velocity.y = (+speed_per_sec/1000/1000) * dt.asMicroseconds();
    }

    game_object()->transform()->translate( sf::Vector2f( velocity.x , velocity.y ) );


}

void MoveObject::on_text_entered(const sf::Event &event){
    std::cout << (char)event.text.unicode << std::endl;
}

void MoveObject::on_closed(const sf::Event&){
    std::cout << FRED << BOLD << "You shall not pass !! " << RESET << std::endl;
}

void MoveObject::on_mouse_button_pressed(const sf::Event &event){
    if( event.mouseButton.button == sf::Mouse::Button::Left ){

        Chrono* ch = getComponent<Chrono>();
        if( ch != nullptr ){
//            std::cout << "GameObject life_time = " << ch->lifetime.asMilliseconds() << std::endl;

            VelocityDef* vel = game_object()->getComponent<VelocityDef>();
            if( vel != nullptr ){
                sf::Vector2f old = vel->getPosition();
                vel->change_position( sf::Vector2f ( event.mouseButton.x , event.mouseButton.y ) );

                //! Callback for timekeeper
                foreach (TimeKeeper* tk, game_object()->getComponentsOfType<TimeKeeper>() ) {
                    tk->onTranslationChanged(vel, old, vel->getPosition(), ch->lifetime.asMilliseconds() );
                }
            }
        }
    }
}

void MoveObject::on_key_pressed(const sf::Event &event){
    if( event.key.code == sf::Keyboard::LShift ){
        std::cout <<  "# REWINDING: Saving the current status" << std::endl;
        Chrono* ch = getComponent<Chrono>();

        if( ch != nullptr ){

            if( ch->status_ == ChronoPlayStatus::FORWARD ){

                //Invoke a freeze function on the GameObject to create a point in the time
                // Hard-Coded example
                VelocityDef* vel = getComponent<VelocityDef>();
                if( vel != nullptr ){
                    sf::Vector2f old = sf::Vector2f( vel->spx, vel->spy );
                    vel->change_velocity(0.f, 0.f);

                    //! Callback for timekeeper
                    foreach (TimeKeeper* tk, game_object()->getComponentsOfType<TimeKeeper>() ) {
                        tk->onVelocityChanged(vel, old, sf::Vector2f(0,0), ch->lifetime.asMilliseconds() );
                    }

                }

                std::cout << FGREEN "------------------------------------------------------------" << RESET << std::endl;
                gdf::kernel::GameInfo::game_info->active_scene()->getComponent<TimeWinder>()->verbose();
                std::cout << FGREEN << "------------------------------------------------------------" << RESET << std::endl;

                ch->status_ = ChronoPlayStatus::BACKWARD;
            }

        }
    }

}

void MoveObject::on_key_released(const sf::Event &event){
    if( event.key.code == sf::Keyboard::LShift ){
        Chrono* ch = getComponent<Chrono>();

        if( ch != nullptr ){
            std::cout << "-----------------------------------------------------------------\n";
            gdf::kernel::GameInfo::game_info->active_scene()->getComponent<TimeWinder>()->verbose();
            std::cout << "-----------------------------------------------------------------\n";
            std::cout << "# GamePlay back to normal\n";

            ch->status_ = ChronoPlayStatus::FORWARD;
        }
    }
}
