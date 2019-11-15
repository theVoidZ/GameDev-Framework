#include "chrono.h"

#include "gameobject.h"

namespace gdf {
namespace temporal {

Chrono::Chrono()
{
}

Chrono::~Chrono(){
    std::cout << BYELLOW << BOLD << "~Chrono" << RESET << std::endl;

    if( host_object<gdf::kernel::GameObject>() != nullptr  ){

    }
}

void Chrono::init(){
    //! WARNING: Auto update chrono_ is not set for gameobject or scene.
}

void Chrono::update(sf::Time dt){
    lifetime_ += dt;
}

void Chrono::rewind(){
    status_ = ChronoPlayStatus::BACKWARD;
    speed_factor_ = -abs( speed_factor_ );
}

void Chrono::forward(){
    status_ = ChronoPlayStatus::FORWARD;
    speed_factor_ = abs( speed_factor_ );
}

void Chrono::freeze(){
    status_ = ChronoPlayStatus::STOPPED;
    // cant put (0), beceause on resume, no effect
//    speed_factor_ = ;
}

void Chrono::set_lifetime(sf::Time lifetime){
    if( lifetime_ == lifetime )
        return;

    this->lifetime_ = lifetime;
}

void Chrono::set_spawn_time( sf::Time spawn_time ){
    if( spawn_time_ == spawn_time )
        return;

    this->spawn_time_ = spawn_time;
}

void Chrono::set_speed_factor(float speed_fac){
    if( speed_factor_ == speed_fac )
        return;

    this->speed_factor_ = speed_fac;
}

void Chrono::set_status(gdf::temporal::ChronoPlayStatus status){
    if( status_ == status )
        return;

    this->status_ = status;
}

}}
