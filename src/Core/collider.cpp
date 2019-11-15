#include "collider.h"

#include "renderer.h"
#include "bounds.h"
#include "gameobject.h"

Collider::Collider()
{
    aabb = new Bounds({0,0}, {50,50});
    global_aabb = new Bounds();

    displacement = sf::Vector2f(0,0);
}

void Collider::update(sf::Time dt){
    go_pos = game_object()->transform().get()->get_world_position();
    if( global_aabb != nullptr ){
        global_aabb->set_min_max( {go_pos.x + aabb->min().x, go_pos.y + aabb->min().y},  {go_pos.x + aabb->max().x, go_pos.y + aabb->max().y});
    }
}

void Collider::fixed_update(sf::Time dt){

}

void Collider::late_update(sf::Time dt){
}

void Collider::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    /// Draw AABB
    if( aabb != nullptr ){
        sf::RectangleShape rect;
        rect.setPosition( displacement + aabb->min() );
        rect.setSize( aabb->size() );
        rect.setFillColor( sf::Color(255,255,255,128) );
        //target.draw( rect, states);

    }
}

void Collider::on_gui(){


}
