#include "myTools.h"
#include <ctime>
#include <chrono>
#include <iomanip> // put_time
#include <sstream>
#include <algorithm>
#include <cstdlib>

std::string tilePositionToString(Tile::ETilePosition tilePosition) {
   std::string positionStr;

   switch (tilePosition)
   {
   case Tile::ETilePosition::NE:
      positionStr = "NE";
      break;
   case Tile::ETilePosition::E:
      positionStr = "E";
      break;
   case Tile::ETilePosition::SE:
      positionStr = "SE";
      break;
   case Tile::ETilePosition::SW:
      positionStr = "SW";
      break;
   case Tile::ETilePosition::W:
      positionStr = "W";
      break;
   case Tile::ETilePosition::NW:
      positionStr = "NW";
      break;
   case Tile::ETilePosition::CENTER:
      positionStr = "CENTER";
      break;
   default:
      break;
   }
   return positionStr;
}

std::string tileTypeToString(Tile::ETileType tileType) {
   std::string typeStr;

   switch (tileType)
   {
   case Tile::ETileType::TileAttribute_Default:
      typeStr = "TileDefault";
      break;
   case Tile::ETileType::TileAttribute_Goal:
      typeStr = "TileGoal";
      break;
   case Tile::ETileType::TileAttribute_Forbidden:
      typeStr = "TileForbidden";
      break;
   case Tile::ETileType::TileAttribute_Omniscient:
      typeStr = "TileOmniscient";
      break;
   default:
      break;
   }
   return typeStr;
}

std::string currentTimeForLog() {
   std::string currentTime;
   auto now = std::chrono::system_clock::now();
   auto in_time_t = std::chrono::system_clock::to_time_t(now);

   struct tm time_info;
   localtime_s(&time_info, &in_time_t);

   std::stringstream ss;
   ss << std::put_time(&time_info, "%Y-%m-%d %X");
   return ss.str();
}

int distanceNbTiles(LevelInfo& level, TileInfo& tile1, TileInfo& tile2) {
   int dx = std::abs(distanceNbTilesX(level, tile1, tile2));
   int dy = std::abs(distanceNbTilesY(level, tile1, tile2));
   return dx + dy;
}

int distanceNbTilesX(LevelInfo& level, TileInfo& tile1, TileInfo& tile2) {
   int tile1X = getPositionX(level, tile1);
   int tile2X = getPositionX(level, tile2);
   int dx = std::abs(tile2X - tile1X);
   return dx;
}

int distanceNbTilesY(LevelInfo& level, TileInfo& tile1, TileInfo& tile2) {
   int tile1Y = getPositionY(level, tile1);
   int tile2Y = getPositionY(level, tile2);
   int dy = std::abs(tile2Y - tile1Y);
   return dy;
}

int getPositionX(LevelInfo& level, TileInfo& tile) {
   return tile.tileID % level.colCount;
}
int getPositionY(LevelInfo& level, TileInfo& tile) {
   return tile.tileID / level.colCount;
}

int getIdTile(LevelInfo& level, unsigned int x, unsigned int y) {
   return y * level.colCount + x;
}

int getMouvementX(Tile::ETilePosition mouvement) {
   int x = 0;
   switch(mouvement) {
   case Tile::ETilePosition::NE:
      x = 1; 
      break;
   case Tile::ETilePosition::E:
      x = 1;
      break; 
   case Tile::ETilePosition::SE:
      x = 0;
      break;
   case Tile::ETilePosition::SW:
      x = -1;
      break;
   case Tile::ETilePosition::W:
      x = -1;
      break;
   case Tile::ETilePosition::NW:
      x = 0;
      break;
   case Tile::ETilePosition::CENTER:
      x = 0;
      break;
   default: 
      break;
   }
   return x;
}
int getMouvementY(Tile::ETilePosition mouvement) {
   int y = 0;
   switch (mouvement) {
   case Tile::ETilePosition::NE:
      y = -1;
      break;
   case Tile::ETilePosition::E:
      y = 0;
      break;
   case Tile::ETilePosition::SE:
      y = 1;
      break;
   case Tile::ETilePosition::SW:
      y = 1;
      break;
   case Tile::ETilePosition::W:
      y = 0;
      break;
   case Tile::ETilePosition::NW:
      y = -1;
      break;
   case Tile::ETilePosition::CENTER:
      y = 0;
      break;
   default:
      break;
   }
   return y;
}