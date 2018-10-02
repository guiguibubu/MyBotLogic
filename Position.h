#pragma once

struct Position {

   int x;
   int y;
   unsigned int tileID;

   Position(int x, int y) : x{ x }, y{ y } {};

   // renvoie la position correspondant a la tile en argument
   // Return : Position (-1, -1) si cette position n'existe pas dans le niveau
   static Position getPosition(unsigned int tileID);
};