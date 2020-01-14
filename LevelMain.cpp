#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include "WeakAIBase.h"
#include "NorthAIBase.h"
#include "DisasterHelper.h"
#include "AIPlayer.h"
#include "PlayerInitialization.h"
#include "VolcanoHelper.h"
#include "OffensiveFightGroup.h"
#include <vector>
#include <algorithm>

// Required data exports  (Description, Map, TechTree, GameType, NumPlayers, TechLvl, number of AI)
ExportLevelDetailsFullEx("4P, SRV, 'Out Of The Frying Pan'", "FryingPan.map", "survtech.txt", MultiSpaceRace, 5, 12, false, 1);

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

void AddVictoryConditions()
{
	Trigger trigger;

	// Children's Module
	trigger = CreateCountTrigger(true, false, PlayerAll, mapChildrenModule, mapNone, 1, cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(true, false, trigger, "Evacuate 50 Children to spacecraft");

	// Evacuation Module
	trigger = CreateCountTrigger(true, false, PlayerAll, mapEvacuationModule, mapNone, 1, cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(true, false, trigger, "Evacuate 200 colonists to spacecraft");

	// Food Cargo
	trigger = CreateCountTrigger(true, false, PlayerAll, mapFoodCargo, mapNone, 1, cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(true, false, trigger, "Evacuate 10,000 units of food to spacecraft");

	// Rare Metals Cargo
	trigger = CreateCountTrigger(true, false, PlayerAll, mapRareMetalsCargo, mapNone, 1, cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(true, false, trigger, "Evacuate 10,000 units of Rare Metals to spacecraft");

	// Common Metals Cargo
	trigger = CreateCountTrigger(true, false, PlayerAll, mapCommonMetalsCargo, mapNone, 1, cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(true, false, trigger, "Evacuate 10,000 units of Common Metals to spacecraft");
}

void AIInitialization()
{
	LOCATION AIWeakBaseLoc(76 + X_, 132 + Y_);
	LOCATION AINorthBaseLoc(244 + X_, 122 + Y_);
	PlayerNum aiIndex = GetAIIndex();
	Player[aiIndex].GoAI();
	Player[aiIndex].SetColorNumber(GetAIColor());
	Player[aiIndex].GoPlymouth();
	Player[aiIndex].SetOre(5'000);
	Player[aiIndex].SetRareOre(3'000);
	BuildAIBase(aiIndex, AIWeakBaseLoc);
	BuildNorthAIBase(aiIndex, AINorthBaseLoc);
}

void InitializeDisasterHelper()
{
	disasterHelper.SetMapProperties(LOCATION(80, 0), LOCATION(256, 256), false);
}

Export int InitProc()
{
	InitializeDisasterHelper();

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
	
	// To stablize Blight force night cycle always
	TethysGame::SetDaylightEverywhere(false);
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
	AddVictoryConditions();
	Trigger BlightTrigger = CreateTimeTrigger(true, true, 1, 1, "SpawnBlight");
	Trigger AddTank = CreateTimeTrigger(true, false, 1000, 1001, "AddTankWeakAIBase");
	
	return true;
}

Export void AIProc() 
{
	CheckMorale();
	UpdateWeakAIBase();
	
}


Export void SpawnBlight()
{
	const LOCATION blightSpawnLoc(1 + X_, 255 + Y_);
	GameMap::SetVirusUL(blightSpawnLoc, 1); // Spawn the blight
	TethysGame::SetMicrobeSpreadSpeed(60);
	AddMapMessage("The Blight is Approaching", blightSpawnLoc, 152, PlayerAll);
}


Export void CreateDisaster()
{
	if (!disasterHelper.MapPropertiesSet())
	{
		InitializeDisasterHelper();
	}

	disasterHelper.CreateRandomDisaster();
}

Export void NoResponseToTrigger() {}	//Optional function export, supposed to be empty

bool VechicleFactoryExists(const LOCATION& location)
{
	LocationEnumerator locEnum(location);

	Unit vehicleFactory;
	while (locEnum.GetNext(vehicleFactory)) {
		if (vehicleFactory.GetType() == mapVehicleFactory) {
			return true;
		}
	}

	return false;
}
