#include "MyBotLogic.h"

#include "TurnInfo.h"
#include "NPCInfo.h"

#include <ctime>
#include <chrono>
#include <iomanip> // put_time
#include <sstream>

#include "windows.h"

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

   // on recence les tiles a atteindre
   listeTileGoals.empty();
   short int nbTilesTotal = _levelInfo.tiles.size();
   for (int i = 0; i < nbTilesTotal; i++) {
      TileInfo tile = _levelInfo.tiles[i];
      if (tile.tileType == Tile::ETileType::TileAttribute_Goal) {
         listeTileGoals.push_back(tile);
      }
   }
   // on recense les tiles a atteindre
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
      Tile::ETilePosition direction = Tile::NE;
      _actionList.push_back(new Move(npc.second.npcID, direction));

#ifdef _DEBUG
      std::stringstream ss;
      ss << currentTimeForLog() << " : " << npc.second.npcID << " move to ";
      ss << tilePositionToString(direction);
      ss << std::endl;

      BOT_LOGIC_LOG(mLogger, ss.str(), true);
#endif
   }
}

/*virtual*/ void MyBotLogic::Exit()
{
	//Write Code Here
}