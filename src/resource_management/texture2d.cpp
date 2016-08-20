#include "texture2d.h"

Texture2D::Texture2D()
    :Resource()
{

}

Texture2D::Texture2D(const Texture2D& tex)
    :Resource(tex), texture(tex.texture) {
//    std::cout << "Texture2D::copy ctor " << std::endl;
}

Texture2D::~Texture2D(){

}

void Texture2D::init(std::string file_name){

    // defines how to load a texture based on args passed to 'on_load'
//    std::cout << "Texture resource is created: " << file_name << std::endl;
    texture.loadFromFile( file_name );

}
