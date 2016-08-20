#include "gui.h"

#include "kernel/gameinfo.h"

Gui::Gui()
{

}

void Gui::drawCircle(float radius){
    sf::CircleShape circle = sf::CircleShape( radius, 30 );
    circle.setPosition( 0, 0);
    circle.setFillColor( sf::Color::Red );

    gdf::kernel::GameInfo::game_info->draw( circle );
}

void Gui::drawRectangle(float x, float y, float w, float h){
    sf::RectangleShape r = sf::RectangleShape( sf::Vector2f(w, h) );
    r.setPosition( x, y);
    r.setOutlineThickness(2);
    r.setFillColor( sf::Color(255,255,255,255) );
    r.setOutlineColor( sf::Color::Black );

    gdf::kernel::GameInfo::game_info->draw( r );
}
