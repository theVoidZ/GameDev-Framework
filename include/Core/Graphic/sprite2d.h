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

//! Sprite2D relies on sf::Sprite
//! 1st- Inherits from sf::Sprite
//! 2nd- Encapsulate an sf::Sprite

class Texture2D;

class Sprite2D  : public sf::Sprite
{
    public:
        Sprite2D();

    public:
        void setTexture2D( std::shared_ptr<Texture2D> texture, bool resetRect=false);

    public:
        std::shared_ptr< Texture2D > sh_texture2d;

};

#endif // SPRITE2D_H
