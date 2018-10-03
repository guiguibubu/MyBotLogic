#pragma once
#include "TileInfo.h"

struct Position {

   int x;
   int y;
   unsigned int tileID;

   Position() = default;
   Position(unsigned int tileID, int x, int y) : tileID{ tileID }, x { x }, y{ y } {};

   bool operator==(Position& position1, Position& position2);

   bool operator!=(Position& position1, Position& position2);

   void move(int dx, int dy);
};