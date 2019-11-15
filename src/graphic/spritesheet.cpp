#include "spritesheet.h"

namespace gdf {
namespace graphic {

SpriteSheet::SpriteSheet()
{

}

SpriteSheet::SpriteSheet(const SpriteSheet &sprt_tile){

}

SpriteSheet::~SpriteSheet(){

}

void SpriteSheet::init(gdf::kernel::tracker_ptr<Texture2D> tex, int line_count, int col_count){
    init(tex, line_count, col_count, line_count*col_count);

}

void SpriteSheet::init(gdf::kernel::tracker_ptr<Texture2D> tex, int line_count, int col_count, int sprite_count){
    texutre2d = tex;
    // texture is already loaded via ResourceManager
    column_count = col_count;
    row_count = line_count;

    sf::Vector2u size = texutre2d.get()->getSize();
    width = size.x;
    height = size.y;

    float part_x = width/col_count;
    float part_y = height/line_count;

    for( int i=0;i< line_count;i++){
        for( int j=0;j<col_count;j++){
            if( i*col_count + j > sprite_count )
                return;
            sheet_boundaries.push_back( sf::IntRect(j*part_x, i*part_y, part_x, part_y) );
        }
    }
}

}}
