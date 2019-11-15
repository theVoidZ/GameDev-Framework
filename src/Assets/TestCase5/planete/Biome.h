#ifndef BIOME_H
#define BIOME_H

#include <SFML/System.hpp>
#include "terminal_colors.h"

#include "monobehavior.h"

#include "tracker_ptr.h"
#include "TileSetBase.h"

#include "json.hpp"

namespace gdf {
namespace kernel {

class GameObject;

}}

class Biome : public gdf::kernel::Component{
	public:
		Biome();

        void on_gui();

		void init();
		void update(sf::Time dt);
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		std::vector< std::vector<TileSetBase*> > tiles;
		std::vector< std::vector<int> > mappingtiles;


	public:
		void create_at(int posx, int posy);
		void destroy_at(int posx, int posy);
		void adapt_tile_id(int posx, int posy, int type, int operation);

		std::vector< sf::Texture > textures;
		std::vector< sf::Texture > ore_textures;

		std::vector< sf::IntRect > sheet_boundaries;

	public:

		int max_height = 15;
		sf::Vector2i tile_size = {40,40};


		int next_block = 1; // To insert {1, 2}
};


#endif //BIOME_H
