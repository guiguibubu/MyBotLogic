#pragma once
#include <vector>
#include "Position.h"

struct PathFinder {

   unsigned int tileGoal;
   unsigned int tileStart;
   std::vector<Position> listePosition;
   std::vector<TileInfo> listeTileInterdite;
   PathFinder() = default;
};