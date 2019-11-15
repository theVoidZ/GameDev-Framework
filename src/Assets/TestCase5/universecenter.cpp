#include "universecenter.h"

#include "gameobject.h"
#include "camera.h"
#include "renderer.h"

// USE IT AS COLLIDER



UniverseCenter::UniverseCenter()
{

}

void UniverseCenter::on_mouse_button_pressed(const sf::Event& event){

}


void UniverseCenter::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    int cc=5;
    sf::CircleShape c(cc);
    c.setFillColor( sf::Color::White );
    c.setOutlineColor( sf::Color::Red );
    c.setOutlineThickness(2);
    c.setOrigin( sf::Vector2f(cc,cc) );
    target.draw( c, states );
}
