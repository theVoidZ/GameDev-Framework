#include "texture2d.h"

#include <stdarg.h>

namespace gdf {
namespace graphic {

Texture2D::Texture2D()
    :Resource(), sf::Texture()
{

}

Texture2D::Texture2D(const Texture2D& tex)
    :Resource(tex), sf::Texture(tex){

}

Texture2D::~Texture2D(){

}

void Texture2D::init(std::string file_name){
    filename_ = file_name;
    loadFromFile( file_name );
}

}}
