#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include "DisasterHelper.h"
#include "AIPlayer.h"
#include "PlayerInitialization.h"
#include "VolcanoHelper.h"
#include <vector>
#include <algorithm>


// Required data exports  (Description, Map, TechTree, GameType, NumPlayers, TechLvl, number of AI)
ExportLevelDetailsFullEx("4P, SRV, 'Out Of The Frying Pan'", "OutOfTheFryingPan.map", "survtech.txt", MultiSpaceRace, 5, 12, false, 1);

DisasterHelper disasterHelper;

struct ScriptGlobal
{
} scriptGlobal;
ExportSaveLoadData(scriptGlobal);


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



Export int InitProc()
{
	HFLInit();

	disasterHelper.SetMapProperties(256, 256, false);

	if (TethysGame::CanHaveDisasters())
	{
		Trigger DisasterTimeTrig = CreateTimeTrigger(true, false, 2000, 4500, "CreateDisaster"); //Set time in ticks (marks / 100)
	}

	TethysGame::SetMusicPlayList(8, 2, PlayList);

	TethysGame::ForceMoraleGood(PlayerNum::PlayerAll);
	if (TethysGame::UsesMorale()) {
		TethysGame::FreeMoraleLevel(PlayerNum::PlayerAll);
	}

	TethysGame::SetDaylightEverywhere(TethysGame::UsesDayNight() == 0);
	TethysGame::SetDaylightMoves(true);
	GameMap::SetInitialLightLevel(TethysGame::GetRand(128));

	for (int i = 0; i < HumanPlayerCount(); ++i)
	{
		for (int j = i + 1; j < HumanPlayerCount(); ++j) {
			Player[i].AllyWith(j);
			Player[j].AllyWith(i);
		}
	}

	InitializePlayers(HumanPlayerCount());
	InitializeVolcanos();
	
	Trigger BlightTrigger = CreateTimeTrigger(true, true, 1, 1, "SpawnBlight");
	
	return true;
}

Export void AIProc() 
{
	
}

Export void SpawnBlight()
{
	LOCATION blightSpawnLoc(1 + X_, 1 + Y_);
	// Setup Blight
	GameMap::SetVirusUL(blightSpawnLoc, 1);  // Spawn the Blight
	TethysGame::SetMicrobeSpreadSpeed(60);  	// Set the Blight's spread speed

	// Warning Message
	TethysGame::AddMessage(1248, 576, "Microbe growth detected!", -1, 152);
}

Export void NoResponseToTrigger() {}	//Optional function export, supposed to be empty
