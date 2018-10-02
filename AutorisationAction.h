#pragma once
#include "NPCInfo.h"

// indiaue si le mouvement vers la casa voisine a la distance dx,dy est possible (mur, case autorise)
bool mouvementVoisinAutorise(NPCInfo& npc, int dx, int dy);