#pragma once
#include <vector>
#include "Position.h"

struct PathFinder {

   unsigned int tileGoal;
   unsigned int tileStart;
   std::vector<Position> listePosition;
   std::vector<TileInfo> listeTileInterdite;

private:
   std::vector<unsigned int> tileVisited;
   std::vector<unsigned int> tileCameFrom;
   void init();
public:
   PathFinder() = default;
   PathFinder(unsigned int tileGoal, unsigned int tileStart, std::vector<Position> listePosition, std::vector<TileInfo> listeTileInterdite) : tileGoal { tileGoal }, tileStart{ tileStart }, listePosition{ listePosition }, listeTileInterdite{ listeTileInterdite }  {
      init();
   };
};