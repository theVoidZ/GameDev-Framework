#include "spriterenderer.h"

#include "gameobject.h"
#include "hierarchy.h"
#include "bounds.h"



namespace gdf {
namespace graphic {

SpriteRenderer::SpriteRenderer()
{

}

SpriteRenderer::~SpriteRenderer(){

}

void SpriteRenderer::init(){

}

void SpriteRenderer::setSprite2D(Sprite2D* sprt2d){
    drawable_ = sprt2d;
}

Bounds SpriteRenderer::getBounds() const{

    if( drawable_ == nullptr)
        return Bounds();

    sf::FloatRect r = static_cast<gdf::graphic::Sprite2D*>(drawable_)->getGlobalBounds();
    Bounds b;
    b.set_min_max( {r.left, r.top}, {r.left + r.width, r.top + r.height} );
    return b;
}

Bounds SpriteRenderer::getGlobalBounds() const{
    if( drawable_ == nullptr)
        return Bounds();

    if( game_object()!= nullptr ){
        if( !game_object()->transform().expired() ){
            sf::Vector2f go_pos = game_object()->transform().get()->get_world_position() - static_cast<gdf::graphic::Sprite2D*>(drawable_)->getOrigin();

            sf::FloatRect r = static_cast<gdf::graphic::Sprite2D*>(drawable_)->getLocalBounds();
            Bounds b;
            b.set_min_max(go_pos, {go_pos.x+r.width, go_pos.y+r.height} );
            return b;
        }
    }
    return Bounds();
}

}}

