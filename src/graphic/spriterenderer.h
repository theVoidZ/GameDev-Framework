#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

// c++-includes

// sfml-includes
#include <SFML/Graphics/Sprite.hpp>


// qt-includes

// user-includes
#include "renderer.h"

//! NEW: Adapt this to the Resource
#include "texture2d.h"
#include "sprite2d.h"
#include "transform.h"


namespace gdf {

namespace graphic {


//! NOTE: The sprite renderer should adapat to the new type of Resource 'Texture2D'
class SpriteRenderer    :   public Renderer
{
    public:
        SpriteRenderer();
        ~SpriteRenderer();

    public:
        void init();

        void setSprite2D(Sprite2D *sprt2d );

    public:
        //Color color;
        bool flip_x;
        bool flip_y;


    public:
        //Getters
        Bounds getBounds() const;
        Bounds getGlobalBounds() const;


};

}}

#endif // SPRITERENDERER_H
