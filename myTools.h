#pragma once

#include <string>
#include "Globals.h"
#include "TileInfo.h"
#include "LevelInfo.h"

   std::string tilePositionToString(Tile::ETilePosition tilePosition);
   std::string tileTypeToString(Tile::ETileType tileType);
   std::string currentTimeForLog();
   
   //Renvoie le nb de case a parcourir pour atteindre la tile2 en partant de la tile 1
   //renvois -1 s'il est impossible d'atteindre la tile2 a partir de la tile1
   int distanceNbTiles(LevelInfo& level, TileInfo& tile1, TileInfo& tile2);
   
   //Renvoie le nb de case separant la tile2 et la tile 1 selon l'axe X ou Y (tile2 - tile1)
   int distanceNbTilesX(LevelInfo& level, TileInfo& tile1, TileInfo& tile2);
   int distanceNbTilesY(LevelInfo& level, TileInfo& tile1, TileInfo& tile2);

   //Renvoie la position en X et Y d'une tile dans le niveau
   //renvois -1 si la tile n'existe pas
   int getPositionX(LevelInfo& level, TileInfo& tile);
   int getPositionY(LevelInfo& level, TileInfo& tile);

   //Renvoie l'ID de la tile en (x,y)
   //renvois -1 si la tile n'existe pas
   int getIdTile(LevelInfo& level, unsigned int x, unsigned int y);

   //renvoie le mouvement selon X et Y a partir du mouvement cardinal
   /*
   NE (1 ,-1)
   E  (1 , 0)
   SE (0 , 1)
   SW (-1, 1)
   W  (-1, 0)
   NW (0 ,-1)
   CENTER (0,0)
   */
   int getMouvementX(Tile::ETilePosition mouvement);
   int getMouvementY(Tile::ETilePosition mouvement);