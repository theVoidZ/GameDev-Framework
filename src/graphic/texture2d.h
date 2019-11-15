#ifndef TEXTURE2D_H
#define TEXTURE2D_H

// c++-includes
#include <string>
#include <string.h>
#include <iostream>

// sfml-includes
#include <SFML/Graphics/Texture.hpp>

// qt-includes

// user-includes
#include "resource.h"


namespace gdf {
namespace graphic {


class Texture2D : public Resource, public sf::Texture
{
    public:
        Texture2D();
        Texture2D(const Texture2D& tex);

        ~Texture2D();

    public:
        void init( std::string file_name );

        sf::Vector2f pivot_ = sf::Vector2f();

};

}}
#endif // TEXTURE2D_H
