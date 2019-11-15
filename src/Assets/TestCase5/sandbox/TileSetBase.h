#ifndef TILESETBASE_H
#define TILESETBASE_H

#include <string>

#include "OreBase.h"


class TileSetBase{
	public:
		TileSetBase();

	public:
		std::string _name;

		std::string _tileset_image = "";
		int _durability = 1;
		bool _destructible = true;

		//Object Ore

		int _id = 1;
		unsigned int _current_tile_index = 0x0;
//		OreBase* _ore = nullptr;
		bool _ore = 1;

};

#endif //INCURSIO_V10_NOTIMEREVERSAL_TILESETBASE_H
