#include <iostream>
#include "Biome.h"
#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include "transform.h"
#include <math.h>
#include <iostream>
#include <fstream>


Biome::Biome(){

}

void Biome::on_gui(){
    std::string str;
    str = std::to_string(max_height);

}

void Biome::init(){
	srand (time(NULL));

	// Resource manager
	textures.push_back( sf::Texture() );
	textures[0].loadFromFile( "../media/stone_tileset.png");
	textures.push_back( sf::Texture() );
	textures[1].loadFromFile( "../media/clone_stone_tileset.png");

	ore_textures.push_back( sf::Texture() );
	ore_textures[0].loadFromFile("../media/silver_ore.png");

	{
		// texture is already loaded via ResourceManager
		int sprite_count = 16;
		int column_count = 16;
		int row_count = 1;

		sf::Vector2u size = textures[0].getSize();
		int width = size.x;
		int height = size.y;

		float part_x = width / column_count;
		float part_y = height / row_count;

		for(int i = 0; i < row_count; i++){
			for(int j = 0; j < column_count; j++){
				if(i * column_count + j > sprite_count)
					return;
				sheet_boundaries.push_back(sf::IntRect(j * part_x, i * part_y, part_x, part_y));
			}
		}
	}

	// Biome generation HERE
	mappingtiles.resize(max_height);
	for( int i = 0; i<mappingtiles.size(); i++){
		mappingtiles[i].resize(max_height);
	}

	for(int i=0;i<mappingtiles.size();i++){
		tiles.push_back( std::vector<TileSetBase*>(mappingtiles.at(0).size() ) );
		for(int j = 0; j < mappingtiles.at(0).size(); j++){
			if(mappingtiles[i][j] == 1){
				tiles[i][j] = new TileSetBase();
				tiles[i][j]->_id = next_block;
			}else if(mappingtiles[i][j] == 0){
				tiles[i][j] = nullptr;
			}
		}
	}
}

void Biome::update(sf::Time dt){

}

void Biome::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	for(int i=0;i<mappingtiles.size();i++){
		for(int j=0;j<mappingtiles.at(0).size();j++){
			if(mappingtiles[i][j] != 0){
				sf::Sprite sprite;
				sprite.setTexture( textures[mappingtiles[i][j]-1] );
				sprite.setTextureRect( sheet_boundaries[ tiles[i][j]->_current_tile_index ] );
				sprite.setPosition(i*tile_size.x, j*tile_size.y);
				target.draw(sprite, states);

				if( tiles[i][j]->_ore != 0 ){
					sf::Sprite ore_srpite;
					ore_srpite.setTexture( ore_textures[0] );
					ore_srpite.setPosition(i*tile_size.x, j*tile_size.y);
					target.draw( ore_srpite, states);
				}
			}
		}
	}

}

void Biome::create_at(int posx, int posy){
	sf::Vector2f root_pos = this->game_object()->transform().get()->get_position();
	sf::Vector2i pos_index = { (posx-(int)root_pos.x)/tile_size.x, (posy-(int)root_pos.y)/tile_size.y};
	if( pos_index.x >=0 && pos_index.x < tile_size.x){
		if( pos_index.y >=0 && pos_index.y < tile_size.y){

			if(mappingtiles[pos_index.x][pos_index.y] == 0){
				tiles[pos_index.x][pos_index.y] = new TileSetBase();
				// Load tileset


				tiles[pos_index.x][pos_index.y]->_id = next_block;
				mappingtiles[pos_index.x][pos_index.y] = tiles[pos_index.x][pos_index.y]->_id;

				//adapting
				adapt_tile_id(pos_index.x, pos_index.y, tiles[pos_index.x][pos_index.y]->_id, 0);

//				std::cout << "tile code: " << (int)tiles[pos_index.x][pos_index.y]->_current_tile_index << std::endl;
			}
		}
	}
}

void Biome::destroy_at(int posx, int posy){
	sf::Vector2f root_pos = this->game_object()->transform().get()->get_position();
	sf::Vector2i pos_index = { (posx-(int)root_pos.x)/tile_size.x, (posy-(int)root_pos.y)/tile_size.y};
	if( pos_index.x >=0 && pos_index.x < tile_size.x){
		if( pos_index.y >=0 && pos_index.y < tile_size.y){

			if(mappingtiles[pos_index.x][pos_index.y] != 0){
				if(tiles[pos_index.x][pos_index.y] != nullptr ){
					if( tiles[pos_index.x][pos_index.y]->_destructible ){
						tiles[pos_index.x][pos_index.y]->_durability--;
						if(tiles[pos_index.x][pos_index.y]->_durability <= 0){
							mappingtiles[pos_index.x][pos_index.y] = 0;
							adapt_tile_id(pos_index.x, pos_index.y, tiles[pos_index.x][pos_index.y]->_id, 1);
							delete tiles[pos_index.x][pos_index.y];
							tiles[pos_index.x][pos_index.y] = nullptr;

						}
					}
				}
			}
		}
	}
}

void Biome::adapt_tile_id(int posx, int posy, int type, int operation){
	int max_height = 10;

	if( operation == 0){ // create
		if(posx - 1 >= 0){ // left
			if(mappingtiles[posx - 1][posy] == type){
				tiles[posx][posy]->_current_tile_index |= 0x8;
				tiles[posx - 1][posy]->_current_tile_index |= 0x4;
			}

		}else{
			tiles[posx][posy]->_current_tile_index |= 0x8;
		}

		if(posx + 1 < max_height){ // right
			if(mappingtiles[posx + 1][posy] == type){
				tiles[posx][posy]->_current_tile_index |= 0x4;
				tiles[posx + 1][posy]->_current_tile_index |= 0x8;
			}
		}else{
			tiles[posx][posy]->_current_tile_index |= 0x4;
		}

		if(posy - 1 >= 0){ // top
			if(mappingtiles[posx][posy - 1] == type){
				tiles[posx][posy]->_current_tile_index |= 0x2;
				tiles[posx][posy - 1]->_current_tile_index |= 0x1;
			}
		}else{
			tiles[posx][posy]->_current_tile_index |= 0x2;
		}

		if(posy + 1 < max_height){ // bottom
			if(mappingtiles[posx][posy + 1] == type){
				tiles[posx][posy]->_current_tile_index |= 0x1;
				tiles[posx][posy + 1]->_current_tile_index |= 0x2;

			}
		}else{
			tiles[posx][posy]->_current_tile_index |= 0x1;
		}

	}else if(operation == 1 ){ // destroy
		if(posx - 1 >= 0){ // left
			if(mappingtiles[posx - 1][posy] == type){
				tiles[posx - 1][posy]->_current_tile_index &= 0xB;
			}

		}

		if(posx + 1 < max_height){ // right
			if(mappingtiles[posx + 1][posy] == type){
				tiles[posx + 1][posy]->_current_tile_index &= 0x7;
			}
		}
		if(posy - 1 >= 0){ // top
			if(mappingtiles[posx][posy - 1] == type){
				tiles[posx][posy - 1]->_current_tile_index &= 0xE;
			}
		}

		if(posy + 1 < max_height){ // bottom
			if(mappingtiles[posx][posy + 1] == type){
				tiles[posx][posy + 1]->_current_tile_index &= 0xD;

			}
		}
	}

}

