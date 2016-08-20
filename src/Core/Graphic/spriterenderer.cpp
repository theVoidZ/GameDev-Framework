#include "spriterenderer.h"
#include "Core/System/transform.h"

#include "time_management/timekeeper.h"

SpriteRenderer::SpriteRenderer()
{

}

void SpriteRenderer::update(sf::Time dt){
    //! FIXME: origin is not WORKING
    sprite.setOrigin( sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);

    Renderer::update(dt);
}

void SpriteRenderer::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw( sprite, states);

}

void SpriteRenderer::setSprite(std::shared_ptr<Texture2D> tex){
    sprite.setTexture2D( tex );
}

Bounds SpriteRenderer::getBounds(){
    //! Position is 0,0 .... ? GlobalBounds has no effect. I am using my own hierarchy.
    //! FIXME: Size is not working properly

    sf::FloatRect rect = sprite.getGlobalBounds();
    sf::Vector2f top_left = game_object()->transform()->transform_point( sf::Vector2f( rect.left, rect.top ) );

    Bounds b;
    b.setMinMax(top_left, sf::Vector2f( top_left.x + rect.width, top_left.y + rect.height ) );
    return b;
}
