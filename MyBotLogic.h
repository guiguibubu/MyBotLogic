#pragma once

#include "BotLogicIF.h"
#include "Logger.h"
#include "TileInfo.h"
#include "Cible.h"
#include "Position.h"
#include "PathFinder.h"

#ifdef _DEBUG
   #define BOT_LOGIC_DEBUG
#endif

#ifdef BOT_LOGIC_DEBUG
   #define BOT_LOGIC_LOG(logger, text, autoEndLine) logger.Log(text, autoEndLine)
#else
   #define BOT_LOGIC_LOG(logger, text, autoEndLine) 0
#endif

//Custom BotLogic where the AIBot decision making algorithms should be implemented.
//This class must be instantiated in main.cpp.
class MyBotLogic : public virtual BotLogicIF
{

private:
   // liste de toutes les tuiles goals
   std::vector<TileInfo> listeTileGoals;
   // liste de toutes les tuiles interdites
   std::vector<TileInfo> listeTileInterdite;
   // liste de toutes les cibles (npc/tileGoal)
   std::vector<Cible> listeCibles;
   // liste des positions de toutes les tuiles du niveau
   std::vector<Position> listePosition;
   // dictionnaire donnant pour chaque npc son chemin vers son objectif
   // [tileGoal, tileGoal -1 , ....., tileStart+1]
   std::map<unsigned int, std::vector<unsigned int>> dicoChemin;
   // liste des npc allant de du npc le plus proche a celui le plus eloigne de sa cible
   std::vector<unsigned int> listeOrderedNpcByDistance;
public:
	MyBotLogic();
	virtual ~MyBotLogic();

	virtual void Configure(int argc, char *argv[], const std::string& _logpath);
	virtual void Start();
	virtual void Init(LevelInfo& _levelInfo);
	virtual void OnGameStarted();
	virtual void FillActionList(TurnInfo& _turnInfo, std::vector<Action*>& _actionList);   //calculate moves for a single turn
	virtual void Exit();

protected:
	Logger mLogger;
};

