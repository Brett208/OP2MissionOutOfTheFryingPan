#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include "AIBaseShared.h"
#include "WeakAIBase.h"
#include "NorthAIBase.h"
#include "SouthAIBase.h"
#include "DisasterHelper.h"
#include "AIPlayer.h"
#include "PlayerInitialization.h"
#include "VolcanoHelper.h"
#include "OffensiveFightGroup.h"
#include <vector>
#include <algorithm>

// Required data exports  (Description, Map, TechTree, GameType, NumPlayers, TechLvl, number of AI)
ExportLevelDetailsFullEx("5P, SRV, 'Out Of The Frying Pan'", "FryingPan.map", "survtech.txt", MultiSpaceRace, 6, 12, false, 1);

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



static void FreeMorale(int playerIndex)
{
	Unit unit;
	moraleFree[playerIndex] = true;
	TethysGame::FreeMoraleLevel(playerIndex);
	TethysGame::AddMessage(unit, "Morale is wavering, Good Luck Commander!", playerIndex, SoundID::sndMessage2);
}

static void CheckMorale()
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

static void AddVictoryConditions()
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
	LOCATION AISouthBaseLoc(242  + X_, 162 + Y_);
	PlayerNum aiIndex = GetAIIndex();
	Player[aiIndex].GoAI();
	Player[aiIndex].SetColorNumber(GetAIColor());
	Player[aiIndex].GoPlymouth();
	Player[aiIndex].SetOre(5'000);
	Player[aiIndex].SetRareOre(3'000);
	Player[aiIndex].SetKids(200);
	Player[aiIndex].SetWorkers(200);
	Player[aiIndex].SetScientists(200);
	SetAIIndex(aiIndex);
	BuildAIBase(aiIndex, AIWeakBaseLoc);
	BuildNorthAIBase(aiIndex, AINorthBaseLoc);
	BuildSouthAIBase(aiIndex, AISouthBaseLoc);
}

static void InitializeDisasterHelper()
{
	disasterHelper.SetMapProperties(LOCATION(80, 0), LOCATION(256, 256), false);
}

static void InitializeMiningBeacons()
{
	// Beacons covered by Northern Blight-blocking lava flow (2-3 bar)
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 75  + TethysGame::GetRand(5) + X_, 4  + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, Bar3,                       VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 44  + TethysGame::GetRand(5) + X_, 16 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeRare,   Bar2,                       VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 58  + TethysGame::GetRand(5) + X_, 55 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 54  + TethysGame::GetRand(5) + X_, 89 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 45  + TethysGame::GetRand(5) + X_, 94 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);

	// Beacons covered by Southern Blight-blocking lava flow (2-3 bar)
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 57  + TethysGame::GetRand(5) + X_, 128 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 45  + TethysGame::GetRand(5) + X_, 131 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 43  + TethysGame::GetRand(5) + X_, 155 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 87  + TethysGame::GetRand(5) + X_, 181 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 73  + TethysGame::GetRand(5) + X_, 183 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 96  + TethysGame::GetRand(5) + X_, 187 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeRare,   Bar2,                       VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 66  + TethysGame::GetRand(5) + X_, 211 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeRare,   TethysGame::GetRand(2) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 70  + TethysGame::GetRand(5) + X_, 242 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, Bar3,                       VariantRandom);

	// Beacons guarded by Weak AI Base (2-3 bar)
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 70  + TethysGame::GetRand(5) + X_, 114 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 89  + TethysGame::GetRand(5) + X_, 130 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 66  + TethysGame::GetRand(5) + X_, 162 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 78  + TethysGame::GetRand(5) + X_, 142 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeRare,   TethysGame::GetRand(2),     VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 54  + TethysGame::GetRand(5) + X_, 151 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeRare,   TethysGame::GetRand(2),     VariantRandom);

	// Beacons in Northern plateau (1-3 bar)
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 181 + TethysGame::GetRand(5) + X_, 3   + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(3) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 146 + TethysGame::GetRand(5) + X_, 9   + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeRare,   TethysGame::GetRand(3),     VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 109 + TethysGame::GetRand(5) + X_, 13  + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(3) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 112 + TethysGame::GetRand(5) + X_, 31  + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(3) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 211 + TethysGame::GetRand(5) + X_, 32  + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeRare,   TethysGame::GetRand(3),     VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 137 + TethysGame::GetRand(5) + X_, 35  + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(3) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 173 + TethysGame::GetRand(5) + X_, 36  + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(3) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 102 + TethysGame::GetRand(5) + X_, 54  + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeRare,   TethysGame::GetRand(3),     VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 192 + TethysGame::GetRand(5) + X_, 61  + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(3) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 175 + TethysGame::GetRand(5) + X_, 65  + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(3) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 98  + TethysGame::GetRand(5) + X_, 84  + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeRare,   TethysGame::GetRand(3),     VariantRandom);

	// Beacons in Southern plateau (1-3 bar)
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 100 + TethysGame::GetRand(5) + X_, 171 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(3) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 137 + TethysGame::GetRand(5) + X_, 181 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(3) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 167 + TethysGame::GetRand(5) + X_, 193 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeRare,   TethysGame::GetRand(3),     VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 113 + TethysGame::GetRand(5) + X_, 217 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(3) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 180 + TethysGame::GetRand(5) + X_, 226 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(3) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 153 + TethysGame::GetRand(5) + X_, 227 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeRare,   TethysGame::GetRand(3),     VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 140 + TethysGame::GetRand(5) + X_, 243 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(3) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 178 + TethysGame::GetRand(5) + X_, 247 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(3) + 1, VariantRandom);

	// Beacons guarded by North AI Base (1-2 bar)
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 214 + TethysGame::GetRand(5) + X_, 76  + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 244 + TethysGame::GetRand(5) + X_, 91  + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 225 + TethysGame::GetRand(5) + X_, 101 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 248 + TethysGame::GetRand(5) + X_, 107 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeRare,   Bar1,                       VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 235 + TethysGame::GetRand(5) + X_, 126 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 250 + TethysGame::GetRand(5) + X_, 124 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);

	// Beacons guarded by South AI Base (1-2 bar)
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 240 + TethysGame::GetRand(5) + X_, 140 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeRare, Bar1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 216 + TethysGame::GetRand(5) + X_, 144 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 229 + TethysGame::GetRand(5) + X_, 156 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 216 + TethysGame::GetRand(5) + X_, 178 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeCommon, TethysGame::GetRand(2) + 1, VariantRandom);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 247 + TethysGame::GetRand(5) + X_, 198 + TethysGame::GetRand(5) + Y_, BeaconTypes::OreTypeRare,   Bar1,                       VariantRandom);
}

Export int InitProc()
{
	InitializeDisasterHelper();
	InitializeMiningBeacons();

	if (TethysGame::CanHaveDisasters())
	{
		Trigger DisasterTimeTrig = CreateTimeTrigger(true, false, 2000, 4500, "CreateDisaster"); // 1 mark = 100 ticks
	}

	if (TethysGame::UsesMorale()) {
		moraleFree.resize(HumanPlayerCount(), false);
	}
	else {
		moraleFree.resize(HumanPlayerCount(), true);
	}

	TethysGame::SetMusicPlayList(8, 2, PlayList);

	TethysGame::ForceMoraleGood(PlayerNum::PlayerAll);
	
	// To stabilize the spread of the Blight, force night cycle always active
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

	AddVictoryConditions();

	Trigger BlightTrigger = CreateTimeTrigger(true, true, 1, 1, "SpawnBlight");
	Trigger FirstAttackTrigger = CreateTimeTrigger(true, true, 2'500, "WeakBaseAttackTrigger"); // Should be 25'000 ticks for actual game, 2'500 for debugging first attack
	
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

Export void WeakBaseAttackTrigger()
{
	weakBaseCanAttack = true;
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

static bool VehicleFactoryExists(const LOCATION& location)
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
