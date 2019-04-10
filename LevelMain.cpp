#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include "PlayerInitialization.h"
#include <vector>
#include <algorithm>


// Required data exports  (Description, Map, TechTree, GameType, NumPlayers, TechLvl, number of AI)
ExportLevelDetailsFullEx("4P, SRV, 'Out Of The Frying Pan'", "OutOfTheFryingPan.map", "survtech.txt", MultiSpaceRace, 5, 12, false, 1);

struct ScriptGlobal
{
} scriptGlobal;
ExportSaveLoadData(scriptGlobal);

const MAP_RECT LavaCellRect(1 + X_, 1 + Y_, 256 + X_, 255 + Y_);
const LOCATION NWVolcanoFlowLoc(60 + X_, 20 + Y_);
const LOCATION SWVolcanoFlowLoc(179+ X_, 70 + Y_);

// List of songs to play
SongIds PlayList[] = {
	SongIds::songStatic03,
	SongIds::songEden32, // Eden 5
	SongIds::songEP42,
	SongIds::songEP51,
	SongIds::songEP52,
	SongIds::songEP61,
	SongIds::songEP62,
	SongIds::songEP63
};

int HumanPlayerCount()
{
	return TethysGame::NoPlayers() - 1;
}

//Note: Scenario must have 5 or fewer human players to work.
PlayerColor GetAIColor(bool allowBlack = false)
{
	int totalColors = 6;
	if (allowBlack) {
		totalColors++;
	}

	std::vector<int> availableColors;
	for (int i = 0; i < totalColors; ++i) {
		availableColors.push_back(i);
	}

	for (int i = 0; i < TethysGame::NoPlayers() - 1; ++i)
	{
		availableColors.erase(
			std::remove(availableColors.begin(), availableColors.end(), ExtPlayer[i].GetColorNumber()), availableColors.end());
	}

	if (availableColors.size() == 0) {
		return PlayerColor::PlayerBlue;
	}

	const int colorIndex = TethysGame::GetRand(availableColors.size());

	return static_cast<PlayerColor>(availableColors[colorIndex]);
}

// AI player is last player
PlayerNum GetAIIndex()
{
	for (int i = 0; i < 7; ++i)
	{
		if (!Player[i].IsHuman()) {
			return static_cast<PlayerNum>(i);
		}
	}

	throw std::runtime_error("No AI player detected");
}

Export void NWVolcanoErupts()
{
	TethysGame::SetEruption(60 + X_, 22 + Y_, 80);
	//TethysGame::SetEruption(volcanoEruptionLoc.x, volcanoEruptionLoc.y, 1000);
}

Export void SWVolcanoErupts()
{
	TethysGame::SetEruption(60 + X_, 22 + Y_, 80);
	//TethysGame::SetEruption(volcanoEruptionLoc.x, volcanoEruptionLoc.y, 1000);
}

Export int InitProc()
{
	HFLInit();

	PlayerNum aiIndex = GetAIIndex();
	Player[aiIndex].GoAI();
	Player[aiIndex].SetColorNumber(GetAIColor());

	TethysGame::SetMusicPlayList(8, 2, PlayList);

	TethysGame::ForceMoraleGood(PlayerNum::PlayerAll);
	if (TethysGame::UsesMorale()) {
		TethysGame::FreeMoraleLevel(PlayerNum::PlayerAll);
	}


	TethysGame::SetDaylightEverywhere(TethysGame::UsesDayNight() == 0);
	TethysGame::SetDaylightMoves(1);
	GameMap::SetInitialLightLevel(TethysGame::GetRand(128));

	SetLavaPossibleAllSlowCells(LavaCellRect);

	AnimateFlowSE(NWVolcanoFlowLoc);
	AnimateFlowSE(SWVolcanoFlowLoc);

	Trigger NWTrigVolcanoEruption = CreateTimeTrigger(true, true, 10, "NWVolcanoErupts");
	Trigger SWTrigVolcanoEruption = CreateTimeTrigger(true, true, 10, "SWVolcanoErupts");

	for (int i = 0; i < HumanPlayerCount(); ++i)
	{
		for (int j = i + 1; j < HumanPlayerCount(); ++j) {
			Player[i].AllyWith(j);
			Player[j].AllyWith(i);
		}
	}

	InitializePlayers(HumanPlayerCount());

	return true;
}

Export void AIProc() 
{
	
}

Export void NoResponseToTrigger() {}	//Optional function export, supposed to be empty
