#include "mycomponent.h"

#include "kernel/gameobject.h"

MyComponent::MyComponent()
{

}

void MyComponent::init(){
	tex.loadFromFile("Hornet.png");
	comp_sprt.setTexture(tex);
}

void MyComponent::update(sf::Time dt){
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

    comp_sprt.move( sf::Vector2f( velocity.x , velocity.y ) );


}

void MyComponent::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	target.draw( comp_sprt, states );
}
