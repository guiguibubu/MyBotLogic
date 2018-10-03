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

int distanceNbTiles(LevelInfo& level, unsigned int tile1ID, unsigned int tile2ID) {
   return distanceNbTiles(level, getTileInfoFromID(level, tile1ID), getTileInfoFromID(level, tile2ID));
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
   return tile.tileID % level.colCount - (getPositionY(level, tile) / 2);
}
int getPositionY(LevelInfo& level, TileInfo& tile) {
   return tile.tileID / level.colCount;
}

int getIdTile(LevelInfo& level, unsigned int x, unsigned int y) {
   return y * level.colCount + x;
}

int getMouvementX(Tile::ETilePosition mouvement) {
   int x = 0;
   switch (mouvement) {
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

Tile::ETilePosition getDirection(int dx, int dy) {
   Tile::ETilePosition direction = Tile::ETilePosition::CENTER;
   if (dx >= 1) {
      if (dy <= -1) {
         direction = Tile::ETilePosition::NE;
      }
      else if (dy == 0) {
         direction = Tile::ETilePosition::E;
      }
   }
   else if (dx == 0) {
      if (dy >= 1) {
         direction = Tile::ETilePosition::SE;
      }
      else if (dy <= -1) {
         direction = Tile::ETilePosition::NW;
      }
      else {
         direction = Tile::ETilePosition::CENTER;
      }
   }
   else {
      if (dy >= 1) {
         direction = Tile::ETilePosition::SW;
      }
      else if (dy == 0) {
         direction = Tile::ETilePosition::W;
      }
   }
   
   return direction;
}

TileInfo getTileInfoFromID(LevelInfo& level, unsigned int tileID) {
   return level.tiles.find(tileID)->second;
}

ObjectInfo getObjectInfoFromID(LevelInfo& level, unsigned int objectID) {
   return level.objects.find(objectID)->second;
}

std::vector<ObjectInfo> getObjectsOnTile(LevelInfo& level, unsigned int tileID) {
   std::vector<ObjectInfo> listeObjectsOnTile;
   for (auto object : level.objects) {
      if (object.second.tileID == tileID) {
         listeObjectsOnTile.push_back(object.second);
      }
   }
   return listeObjectsOnTile;
}

Tile::ETilePosition getCoteOppose(Tile::ETilePosition cote) {
   Tile::ETilePosition coteOppose = Tile::ETilePosition::CENTER;
   switch (cote) {
   case Tile::ETilePosition::E:
      coteOppose = Tile::ETilePosition::W;
      break;
   case Tile::ETilePosition::SE:
      coteOppose = Tile::ETilePosition::NW;
      break;
   case Tile::ETilePosition::SW:
      coteOppose = Tile::ETilePosition::NE;
      break;
   case Tile::ETilePosition::W:
      coteOppose = Tile::ETilePosition::E;
      break;
   case Tile::ETilePosition::NW:
      coteOppose = Tile::ETilePosition::SE;
      break;
   case Tile::ETilePosition::NE:
      coteOppose = Tile::ETilePosition::SW;
      break;
   default:
      break;
   }
   return coteOppose;
}

bool estUnePorte(LevelInfo& level, unsigned int objectID) {
   bool estUnePorte = false;
   std::set<Object::EObjectType> objectTypes = getObjectInfoFromID(level, objectID).objectTypes;
   int j = 0;
   int nbTypes = objectTypes.size();
   while (!estUnePorte && j < nbTypes) {
      estUnePorte = *std::next(objectTypes.begin(), j) == Object::EObjectType::ObjectType_Door;
      j++;
   }
   return estUnePorte;
}
bool estUnePorteFermee(LevelInfo& level, unsigned int objectID) {
   bool estUnePorteFermee = false;
   ObjectInfo objet = getObjectInfoFromID(level, objectID);
   std::set<Object::EObjectType> objectTypes = objet.objectTypes;
   std::set<Object::EObjectState> objectStates = objet.objectStates;
   int j = 0;
   int nbTypes = objectTypes.size();
   while (!estUnePorteFermee && j < nbTypes) {
      estUnePorteFermee = *std::next(objectTypes.begin(), j) == Object::EObjectType::ObjectType_Door
         && *std::next(objectStates.begin(), j) == Object::EObjectState::ObjectState_Closed;
      j++;
   }
   return estUnePorteFermee;
}
bool estUneFenetre(LevelInfo& level, unsigned int objectID) {
   bool estUneFenetre = false;
   std::set<Object::EObjectType> objectTypes = getObjectInfoFromID(level, objectID).objectTypes;
   int j = 0;
   int nbTypes = objectTypes.size();
   while (!estUneFenetre && j < nbTypes) {
      estUneFenetre = *std::next(objectTypes.begin(), j) == Object::EObjectType::ObjectType_Window;
      j++;
   }
   return estUneFenetre;
}
bool estUnMur(LevelInfo& level, unsigned int objectID) {
   bool estUnMur = false;
   std::set<Object::EObjectType> objectTypes = getObjectInfoFromID(level, objectID).objectTypes;
   int j = 0;
   int nbTypes = objectTypes.size();
   while (!estUnMur && j < nbTypes) {
      estUnMur = *std::next(objectTypes.begin(), j) == Object::EObjectType::ObjectType_Wall;
      j++;
   }
   return estUnMur;
}

bool tileGoalDejaAssigne(std::vector<Cible> listeCibles, unsigned int tileID) {
   bool dejaAssigne = false;
   int nbCibles = listeCibles.size();
   int i = 0;
   while (!dejaAssigne && i < nbCibles) {
      dejaAssigne = listeCibles[i].tile.tileID == tileID;
      i++;
   }
   return dejaAssigne;
}

Cible getCibleByNPC(std::vector<Cible> listeCibles, unsigned int npcID) {
   Cible cibleNPC;
   int nbCibles = listeCibles.size();
   int i = 0;
   bool found = false;
   while (!found && i < nbCibles) {
      found = listeCibles[i].npc.npcID == npcID;
      if (found) {
         cibleNPC = listeCibles[i];
      }
      i++;
   }
   return cibleNPC;
}

Position getPositionByTile(std::vector<Position> listePosition, unsigned int tileID) {
   Position positionTile = Position::Position();
   int nbPosition = listePosition.size();
   int i = 0;
   bool found = false;
   while (!found && i < nbPosition) {
      found = listePosition[i].tileID == tileID;
      if (found) {
         positionTile = listePosition[i];
      }
      i++;
   }
   return positionTile;
}