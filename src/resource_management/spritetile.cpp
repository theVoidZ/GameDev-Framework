#include "spritetile.h"

SpriteTile::SpriteTile()
{

}

SpriteTile::SpriteTile(const SpriteTile &sprt_tile){

}

SpriteTile::~SpriteTile(){

}

void SpriteTile::init(std::string file_name, int line_count, int col_count){
    init(file_name, line_count, col_count, line_count*col_count);
}

void SpriteTile::init(std::string file_name, int line_count, int col_count, int sprite_count){
    img_buffer.loadFromFile(file_name);

    column_count = col_count;
    row_count = line_count;

    width = img_buffer.getSize().x;
    height = img_buffer.getSize().y;


    float part_x = width/col_count;
    float part_y = height/line_count;

    for( int i=0;i< line_count;i++){
        for( int j=0;j<col_count;j++){
            if( i*col_count + j > sprite_count )
                return;

            sf::Image img_temp;
            img_temp.create(part_x, part_y);
            img_temp.copy(img_buffer, 0, 0, sf::IntRect( j*part_x, i*part_y, part_x, part_y ), false );
            sf::Texture* t = new sf::Texture();
            t->loadFromImage(img_temp);
            tex_tile.push_back(t);
        }
    }

}
