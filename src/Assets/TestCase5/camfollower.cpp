#include "camfollower.h"

#include "gameinfo.h"
#include "camera.h"
#include "gameobject.h"

CamFollower::CamFollower()
{

}

void CamFollower::init(){

}

void CamFollower::update(sf::Time dt){
    if( !following_go.expired() ){
        if( cam != nullptr ){
            cam->setCenter( following_go.get()->transform().get()->get_world_position() );
        }
    }
}

void CamFollower::draw(sf::RenderTarget &target, sf::RenderStates states) const{

}
