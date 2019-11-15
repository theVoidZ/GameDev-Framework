#ifndef OREBASE_H
#define OREBASE_H

#include <string>

class OreBase{
	public:
		OreBase();

	public:
		std::string _name;
		int _id;
		std::string _tileset_image;

		int _type; // Materiel
		int _subtype; //  Ore
		unsigned char _rarity; // Common
};


#endif //INCURSIO_V10_NOTIMEREVERSAL_OREBASE_H
