#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

// c++-includes

// sfml-includes
#include <SFML/Graphics/Sprite.hpp>


// qt-includes

// user-includes
#include "Core/Graphic/renderer.h"
#include "Core/DataStruct/color.h"

//! NEW: Adapt this to the Resource
#include "resource_management/texture2d.h"
#include "Core/Graphic/sprite2d.h"

//! NOTE: The sprite renderer should adapat to the new type of Resource 'Texture2D'
class SpriteRenderer    :   public Renderer
{
    Q_OBJECT
    public:
        SpriteRenderer();

    public:
        void update(sf::Time dt);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        void setSprite( std::shared_ptr<Texture2D> tex);

    public:
        Color color;
        bool flip_x;
        bool flip_y;
//        sf::Sprite sf_sprite; // SPrite to draw, its texture is loaded using the AssetsHolder.

        //! deprecated: used by the animation compnent ( to be changed )
        sf::Sprite sfsprite;
        Sprite2D sprite;

    public:
        //Getters
        Bounds getBounds();

};

#endif // SPRITERENDERER_H
