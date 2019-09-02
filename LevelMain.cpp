#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include "WeakAIBase.h"
#include "DisasterHelper.h"
#include "AIPlayer.h"
#include "PlayerInitialization.h"
#include "VolcanoHelper.h"
#include "OffensiveFightGroup.h"
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

std::vector<bool> moraleFree; // If each player's morale is free
const int disastersAndMoraleTimer = 20'000;



void FreeMorale(int playerIndex)
{
	Unit unit;
	moraleFree[playerIndex] = true;
	TethysGame::FreeMoraleLevel(playerIndex);
	TethysGame::AddMessage(unit, "Morale is waivering, Good Luck Commander!", playerIndex, SoundID::sndMessage2);
}

void CheckMorale()
{
	for (int i = 0; i < HumanPlayerCount(); ++i) {
		if (moraleFree[i]) {
			continue;
		}

		if (TethysGame::Time() > disastersAndMoraleTimer) {
			FreeMorale(i);
		}

		PlayerBuildingEnum playerBuildingEnum = PlayerBuildingEnum(i, map_id::mapStandardLab);

		Unit unit;
		while (playerBuildingEnum.GetNext(unit))
		{
			if (unit.GetType() == map_id::mapStandardLab)
			{
				FreeMorale(i);
				break;
			}
		}
	}
}

void AIInitialization()
{
	LOCATION AIWeakBaseLoc(76 + X_, 132 + Y_);
	PlayerNum aiIndex = GetAIIndex();
	Player[aiIndex].GoAI();
	Player[aiIndex].SetColorNumber(GetAIColor());
	Player[aiIndex].GoPlymouth();
	BuildAIBase(aiIndex, AIWeakBaseLoc);
}

Export int InitProc()
{
	disasterHelper.SetMapProperties(256, 256, false);

	if (TethysGame::CanHaveDisasters())
	{
		Trigger DisasterTimeTrig = CreateTimeTrigger(true, false, 2000, 4500, "CreateDisaster"); //Set time in ticks (marks / 100)
	}

	if (TethysGame::UsesMorale()) {
		moraleFree.resize(HumanPlayerCount(), false);
	}
	else {
		moraleFree.resize(HumanPlayerCount(), true);
	}

	TethysGame::SetMusicPlayList(8, 2, PlayList);

	TethysGame::ForceMoraleGood(PlayerNum::PlayerAll);
	
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

	InitializeVolcanos();
	InitializePlayers(HumanPlayerCount());
	AIInitialization();

	CreateMicrobeWallLine(LOCATION(39 + X_, 99 + Y_), LOCATION(64 + X_, 99 + Y_));
	CreateMicrobeWallLine(LOCATION(39 + X_, 126 + Y_), LOCATION(64 + X_, 126 + Y_));

	//Trigger BlightTrigger = CreateTimeTrigger(true, true, 1, 1, "SpawnBlight");
	
	return true;
}

Export void AIProc() 
{
	CheckMorale();
	UpdateWeakAIBase();
}


Export void SpawnBlight()
{
	LOCATION blightSpawnLoc(1 + X_, 1 + Y_);
	// Setup Blight
	GameMap::SetVirusUL(blightSpawnLoc, 1);  // Spawn the Blight
	TethysGame::SetMicrobeSpreadSpeed(60);  	// Set the Blight's spread speed

	// Warning Message
	TethysGame::AddMessage(1248, 576, "Microbe growth detected!", -1, 152);

	GameMap::SetVirusUL(blightSpawnLoc, 1); // Spawn the blight
	TethysGame::SetMicrobeSpreadSpeed(60);	// set blight speed

	TethysGame::AddMessage(1248, 576, "The Blight is Approaching", -1, 152); // Check Sound Message
	
}
}

Export void CreateDisaster()
{
	if (!disasterHelper.MapPropertiesSet())
	{
		disasterHelper.SetMapProperties(256, 256, false); //MapWidth, MapHeight, Does map wrap East/West
	}

	disasterHelper.CreateRandomDisaster();
}

Export void NoResponseToTrigger() {}	//Optional function export, supposed to be empty
