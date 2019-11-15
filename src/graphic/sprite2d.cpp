#include "sprite2d.h"

#include "texture2d.h"


namespace gdf {
namespace graphic {


Sprite2D::Sprite2D()
{

}

void Sprite2D::setTexture2D(gdf::kernel::tracker_ptr<Texture2D> texture, bool resetRect){
    sh_texture2d = texture;
    if( !sh_texture2d.expired() ){
        this->setTexture( *sh_texture2d.get(), resetRect );
        this->setOrigin( texture.get()->pivot_ );
    }
}

}}
