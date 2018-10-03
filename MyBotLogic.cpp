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
      listePosition.push_back(Position::Position(tile.second.tileID, getPositionX(_levelInfo,tile.second), getPositionY(_levelInfo, tile.second)));
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

#ifdef BOT_LOGIC_DEBUG
   BOT_LOGIC_LOG(mLogger, "Liste position : ", true);
   for (Position position : listePosition) {
      BOT_LOGIC_LOG(mLogger, "Tile "+std::to_string(position.tileID) + " (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ")", true);
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
      BOT_LOGIC_LOG(mLogger, std::to_string(cible.npc.npcID) + " doit aller vers " + std::to_string(cible.tile.tileID), true);
   }
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
   for (auto npc : _turnInfo.npcs) {
      //on recupere sa cible
      Cible cibleNPC = getCibleByNPC(listeCibles, npc.second.npcID);
      if (npc.second.tileID != cibleNPC.tile.tileID) {
         //on recupere la position actuelle du NPC
         Position positionNPC = getPositionByTile(listePosition, npc.second.tileID);
         //on recupere la position de la tile a atteindre
         Position positionTile = getPositionByTile(listePosition, cibleNPC.tile.tileID);
         //on en deduit la direction a prendre
         Tile::ETilePosition direction = getDirection(positionTile.x - positionNPC.x, positionTile.y - positionNPC.y);
         //on indique au npc la direction a prendre
         _actionList.push_back(new Move(npc.second.npcID, direction));

#ifdef BOT_LOGIC_DEBUG
         std::stringstream ss;
         ss << currentTimeForLog() << " : " << npc.second.npcID << " move to ";
         ss << tilePositionToString(direction);
         ss << std::endl;

         BOT_LOGIC_LOG(mLogger, ss.str(), true);
#endif
      }
   }
}

/*virtual*/ void MyBotLogic::Exit()
{
	//Write Code Here
}