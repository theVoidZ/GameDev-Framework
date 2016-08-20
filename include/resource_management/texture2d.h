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
#include "resource_management/resource.h"


class Texture2D : public Resource
{
    Q_OBJECT
    public:
        Texture2D();
        Texture2D(const Texture2D& tex);

        ~Texture2D();

    public:
        void init( std::string file_name );

    public:
        //! WARNING: Is public
        sf::Texture texture;

};

#endif // TEXTURE2D_H
