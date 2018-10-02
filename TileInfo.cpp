#include "TileInfo.h"

bool operator==(TileInfo& tile1, TileInfo& tile2) {
   return tile1.tileID == tile2.tileID;
}