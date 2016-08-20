#include "sprite2d.h"

#include "resource_management/texture2d.h"

Sprite2D::Sprite2D()
{

}

void Sprite2D::setTexture2D(std::shared_ptr<Texture2D> texture, bool resetRect){
    sh_texture2d = texture;
    if( sh_texture2d.get() != nullptr )
        this->setTexture( sh_texture2d.get()->texture, resetRect );
}
