#pragma once
#include "TileInfo.h"

struct Position {

   int x;
   int y;
   unsigned int tileID;

   Position() = default;
   Position(unsigned int tileID, int x, int y) : tileID{ tileID }, x { x }, y{ y } {};
};