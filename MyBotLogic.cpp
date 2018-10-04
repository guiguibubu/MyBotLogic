#include "MyBotLogic.h"

#include "TurnInfo.h"
#include "NPCInfo.h"

#include <ctime>
#include <chrono>
#include <iomanip> // put_time
#include <sstream>

#include "Windows.h"

#include <algorithm>
#include "myTools.h"
#include "PathFinder.h"

MyBotLogic::MyBotLogic()
{
   //Write Code Here
}

/*virtual*/ MyBotLogic::~MyBotLogic()
{
   //Write Code Here
}

/*virtual*/ void MyBotLogic::Configure(int argc, char *argv[], const std::string& _logpath)
{
#ifdef BOT_LOGIC_DEBUG
   mLogger.Init(_logpath, "MyBotLogic.log");
   PathFinder::configLog(_logpath);
#endif

   BOT_LOGIC_LOG(mLogger, "Configure", true);


   //Write Code Here
}

/*virtual*/ void MyBotLogic::Start()
{
   //Write Code Here

   BOT_LOGIC_LOG(mLogger, "Bot Started", true);
}

/*virtual*/ void MyBotLogic::Init(LevelInfo& _levelInfo)
{
   //Write Code Here
   BOT_LOGIC_LOG(mLogger, "Bot Initiated", true);

   // on recence les tiles a atteindre et interdites
   listeTileGoals.empty();
   listeTileInterdite.empty();
   for (auto tile : _levelInfo.tiles) {
      // on memorise toutes les positions visibles dans le niveau
      listePosition.push_back(Position::Position(tile.second.tileID, getPositionX(_levelInfo, tile.second), getPositionY(_levelInfo, tile.second)));
      if (tile.second.tileType == Tile::ETileType::TileAttribute_Goal) {
         listeTileGoals.push_back(tile.second);
      }
      else if (tile.second.tileType == Tile::ETileType::TileAttribute_Forbidden) {
         listeTileInterdite.push_back(tile.second);
      }
   }

   // on associe chaque npc a une tile goal
   for (auto npc : _levelInfo.npcs) {
      TileInfo tileGoal;
      int minDistance = _levelInfo.colCount*_levelInfo.rowCount;
      for (TileInfo tile : listeTileGoals) {
         int minDistanceOld = minDistance;
         minDistance = (std::min)(minDistance, distanceNbTiles(_levelInfo, npc.second.tileID, tile.tileID));
         if (minDistance != minDistanceOld && !tileGoalDejaAssigne(listeCibles, tile.tileID)) {
            tileGoal = tile;
         }
      }
      listeCibles.push_back(Cible::Cible(tileGoal, npc.second));
   }
   // on liste tous les chemin des differents NPC
   for (Cible cible : listeCibles) {
      PathFinder pathfinder = PathFinder::PathFinder(cible.tileGoal.tileID, cible.npc.tileID, listePosition, convertIntoListID(listeTileInterdite));
      dicoChemin[cible.npc.npcID] = pathfinder.chemin;
      //dicoChemin[cible.npc.npcID] = PathFinder::PathFinder(cible.tileGoal.tileID, cible.npc.tileID, listePosition, listeTileInterdite).chemin;
   }

   // liste des npc allant de du npc le plus proche a celui le plus eloigne de sa cible
   listeOrderedNpcByDistance = getOrderedNpcByDistance(_levelInfo.npcs, dicoChemin);
   std::reverse(listeOrderedNpcByDistance.begin(), listeOrderedNpcByDistance.end());

#ifdef BOT_LOGIC_DEBUG
   BOT_LOGIC_LOG(mLogger, "Liste position : ", true);
   for (Position position : listePosition) {
      BOT_LOGIC_LOG(mLogger, "Tile " + std::to_string(position.tileID) + " (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ")", true);
   }
   BOT_LOGIC_LOG(mLogger, "Tile goals : ", true);
   for (TileInfo tile : listeTileGoals) {
      BOT_LOGIC_LOG(mLogger, std::to_string(tile.tileID) + " ", false);
   }
   BOT_LOGIC_LOG(mLogger, "", true);
   BOT_LOGIC_LOG(mLogger, "Tile interdite : ", false);
   for (TileInfo tile : listeTileInterdite) {
      BOT_LOGIC_LOG(mLogger, std::to_string(tile.tileID) + " ", false);
   }
   BOT_LOGIC_LOG(mLogger, "", true);
   for (Cible cible : listeCibles) {
      BOT_LOGIC_LOG(mLogger, std::to_string(cible.npc.npcID) + " doit aller vers " + std::to_string(cible.tileGoal.tileID), true);
   }
   std::stringstream ss;
   ss << "NPC Ordered :";
   for (unsigned int npcID : listeOrderedNpcByDistance) {
      ss << npcID;
      ss << " ";
   }
   ss << std::endl;

   BOT_LOGIC_LOG(mLogger, ss.str(), true);
#endif



}

/*virtual*/ void MyBotLogic::OnGameStarted()
{
   //Write Code Here
   BOT_LOGIC_LOG(mLogger, "Bot on game started", true);


}

/*virtual*/ void MyBotLogic::FillActionList(TurnInfo& _turnInfo, std::vector<Action*>& _actionList)
{
   //Write Code Here.
   std::vector<unsigned int> listeTileCibleTour;
   std::map<unsigned int, unsigned int> dicoTileCibleTour;
   listeTileCibleTour.clear();
   dicoTileCibleTour.clear();
   //   // liste des npc allant de du npc le plus proche a celui le plus eloigne de sa cible
   //   std::vector<unsigned int> listeOrderedNpcByDistance = getOrderedNpcByDistance(_turnInfo.npcs, dicoChemin);
   //   std::reverse(listeOrderedNpcByDistance.begin(), listeOrderedNpcByDistance.end());
   //#ifdef BOT_LOGIC_DEBUG
   //   std::stringstream ss;
   //   ss << "NPC Ordered :";
   //   for (unsigned int npcID : listeOrderedNpcByDistance) {
   //      ss << npcID;
   //      ss << " ";
   //   }
   //   ss << std::endl;
   //
   //   BOT_LOGIC_LOG(mLogger, ss.str(), true);
   //#endif
      //premiere boucle pour savoir ou veulent aller et ou sont les npc
   for (unsigned int npcID : listeOrderedNpcByDistance) {
      NPCInfo npc = _turnInfo.npcs.at(npcID);

      unsigned int tileCible;
      //on recupere sa cible
      Cible cibleNPC = getCibleByNPC(listeCibles, npc.npcID);
      // s'il n'est pas a son goal
      if (npc.tileID != cibleNPC.tileGoal.tileID) {
         //on recupere la position de la tile a atteindre
         //Position positionTile = getPositionByTile(listePosition, cibleNPC.tileGoal.tileID);
         tileCible = (dicoChemin.at(npc.npcID).empty()) ? npc.tileID : dicoChemin.at(npc.npcID).back();
         dicoTileCibleTour[npc.npcID] = tileCible;
         // si la tuile n'est pas deja visee par un autre NPC
         if (std::find(listeTileCibleTour.begin(), listeTileCibleTour.end(), tileCible) == listeTileCibleTour.end()) {
            listeTileCibleTour.push_back(tileCible);
            if (!(dicoChemin.at(npc.npcID).empty())) {
               (&dicoChemin[npc.npcID])->pop_back();
            }

            // on donne l'ordre du mouvement

            //on recupere la position actuelle du NPC
            Position positionNPC = getPositionByTile(listePosition, npc.tileID);

            Position positionTile = getPositionByTile(listePosition, tileCible);
            //on en deduit la direction a prendre
            Tile::ETilePosition direction = getDirection(positionTile.x - positionNPC.x, positionTile.y - positionNPC.y);
            //on indique au npc la direction a prendre
            _actionList.push_back(new Move(npc.npcID, direction));

#ifdef BOT_LOGIC_DEBUG
            std::stringstream ss;
            ss << currentTimeForLog() << " : " << npc.npcID << " move to ";
            ss << tilePositionToString(direction);
            ss << std::endl;

            BOT_LOGIC_LOG(mLogger, ss.str(), true);
#endif
         }
      }
      //
      //   // boucle pour donner les ordre de mouvement
      //   for (unsigned int npcID : listeOrderedNpcByDistance) {
      //      NPCInfo npc = _turnInfo.npcs.at(npcID);
      //
      //      //on recupere la position actuelle du NPC
      //      Position positionNPC = getPositionByTile(listePosition, npc.tileID);
      //
      //      unsigned int tileCible = dicoTileCibleTour.at(npc.npcID);
      //
      //      // si la tuile n'est pas deja visee par un autre NPC
      //      if (std::find(listeTileCibleTour.begin(), listeTileCibleTour.end(), tileCible) == listeTileCibleTour.end()) {
      //         Position positionTile = getPositionByTile(listePosition, tileCible);
      //         //on en deduit la direction a prendre
      //         Tile::ETilePosition direction = getDirection(positionTile.x - positionNPC.x, positionTile.y - positionNPC.y);
      //         //on indique au npc la direction a prendre
      //         _actionList.push_back(new Move(npc.npcID, direction));
      //
      //#ifdef BOT_LOGIC_DEBUG
      //         std::stringstream ss;
      //         ss << currentTimeForLog() << " : " << npc.npcID << " move to ";
      //         ss << tilePositionToString(direction);
      //         ss << std::endl;
      //
      //         BOT_LOGIC_LOG(mLogger, ss.str(), true);
      //#endif
            //}
   }
}

/*virtual*/ void MyBotLogic::Exit()
{
   //Write Code Here
}