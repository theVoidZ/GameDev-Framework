#include "chrono.h"

#include "Core/Utilities/algorithm.h"

Chrono::Chrono()
{

}

Chrono::~Chrono(){

}

void Chrono::init(){
    status_ = ChronoPlayStatus::FORWARD;
}

void Chrono::update(sf::Time dt){

    if( status_ == ChronoPlayStatus::FORWARD ){
        lifetime += dt;
    }else if( status_ == ChronoPlayStatus::STOPPED ){

    }else if( status_ == ChronoPlayStatus::BACKWARD ){
        lifetime -= dt;
        lifetime = Algorithm::clamp(lifetime, sf::Time::Zero, lifetime);
    }
}
