#pragma once
#include "TileInfo.h"
#include "NPCInfo.h"

//couple NPC-Tile indiauqnt quel tile doit qtteindre le NPC pour gagner
struct Cible {

   NPCInfo npc;
   TileInfo tile;

   Cible() = default;
   Cible(TileInfo& tile, NPCInfo& npc) : tile{ tile }, npc{ npc } {};
};