#ifndef SPRITE2D_H
#define SPRITE2D_H

// c++-includes
#include <string>
#include <iostream>
#include <memory>

// sfml-includes
#include <SFML/Graphics/Sprite.hpp>

// qt-includes

// user-includes
#include "tracker_ptr.h"

//! Sprite2D relies on sf::Sprite
//! 1st- Inherits from sf::Sprite
//! 2nd- Encapsulate an sf::Sprite


namespace gdf {
namespace graphic {

class Texture2D;

//! NOTE: Due to sf::Sprite, Sprite2D has its own sf::Transformable. However, Sprite2D is only manipulated through its game object.
class Sprite2D : public sf::Sprite
{
    public:
        Sprite2D();

    public:
        //! FIX: RESTRICT ANY ACCESS TO sf::Sprite methods.
        void setTexture2D( gdf::kernel::tracker_ptr<Texture2D> texture, bool resetRect=false);

    public:
        gdf::kernel::tracker_ptr< Texture2D > sh_texture2d;

};

}}

#endif // SPRITE2D_H
