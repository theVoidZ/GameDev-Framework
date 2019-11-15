#include "TileSetBase.h"

TileSetBase::TileSetBase(){
	// Randomly set ore ( only silver for now )
	_ore = rand() % 2;
}
