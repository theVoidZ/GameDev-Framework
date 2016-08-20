#include "velocitydef.h"

#include "Core/System/transform.h"
#include "time_management/timekeeper.h"

#include "time_management/eventtranslation.h"

VelocityDef::VelocityDef()
{
    velocity = sf::Vector2f(spx / 1000 / 1000, spy / 1000 / 1000 );
}

sf::Vector2f VelocityDef::getPosition(){
    if( game_object() != nullptr ){
        Transform*t = game_object()->transform();
        return t->get_position();
    }
}

void VelocityDef::change_position(sf::Vector2f pos){
    if( game_object() != nullptr ){
        Transform* t = game_object()->transform();
        t->Transform::set_position( pos );
    }
}

void VelocityDef::change_velocity(float spx, float spy){
    this->spx = spx;
    this->spy = spy;
    velocity = sf::Vector2f(spx / 1000 / 1000, spy / 1000 / 1000 );
}

void VelocityDef::update(sf::Time dt){
    if( game_object() != nullptr ){
        Transform* t = game_object()->transform();
        if( t != nullptr ){
            t->translate( sf::Vector2f( velocity.x * dt.asMicroseconds(), velocity.y * dt.asMicroseconds() ) );
        }
    }
}
