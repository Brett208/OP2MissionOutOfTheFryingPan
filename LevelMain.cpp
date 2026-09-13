#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include "AIBases/AIBaseShared.h"
#include "AIBases/WeakAIBase.h"
#include "AIBases/NorthAIBase.h"
#include "AIBases/SouthAIBase.h"
#include "DisasterHelper.h"
#include "AIPlayer.h"
#include "PlayerInitialization.h"
#include "VolcanoHelper.h"
#include "FightGroups/OffensiveFightGroup.h"
#include "Environment.h"
#include <vector>
#include <algorithm>

// Prevent using the Windows defined macros that step on the C++ standard function calls
#undef min
#undef max

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
bool hasBlightEnteredWestRegion = false;


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

static Yield GetRandomYield(Yield yieldA, Yield yieldB)
{
	const int minYield = std::min(static_cast<int>(yieldA), static_cast<int>(yieldB));
	const int maxYield = std::max(static_cast<int>(yieldA), static_cast<int>(yieldB));

	return static_cast<Yield>(minYield + TethysGame::GetRand(maxYield - minYield + 1));
}

static void CreateCommonBeacon(LOCATION location, Yield yield)
{
	TethysGame::CreateBeacon(mapMiningBeacon, location.x + TethysGame::GetRand(5) + X_, location.y + TethysGame::GetRand(5) + Y_, OreTypeCommon, yield, VariantRandom);
}

static void CreateCommonBeacon(LOCATION location, Yield yieldMin, Yield yieldMax)
{
	CreateCommonBeacon(location, GetRandomYield(yieldMin, yieldMax));
}

static void CreateRareBeacon(LOCATION location, Yield yield)
{
	TethysGame::CreateBeacon(mapMiningBeacon, location.x + TethysGame::GetRand(5) + X_, location.y + TethysGame::GetRand(5) + Y_, OreTypeRare, yield, VariantRandom);
}

static void CreateRareBeacon(LOCATION location, Yield yieldMin, Yield yieldMax)
{
	CreateRareBeacon(location, GetRandomYield(yieldMin, yieldMax));
}

static void InitializeMiningBeacons()
{
	// Beacons that will be covered by Northern lava flow
	CreateCommonBeacon(LOCATION(75, 4), Bar3);
	CreateRareBeacon(LOCATION(44, 16), Bar2);
	CreateCommonBeacon(LOCATION(58, 55), Bar2, Bar3);
	CreateCommonBeacon(LOCATION(54, 89), Bar2, Bar3);
	CreateCommonBeacon(LOCATION(45, 94), Bar2, Bar3);

	// Beacons that will be covered by Southern lava flow
	CreateCommonBeacon(LOCATION(57, 128), Bar2, Bar3);
	CreateCommonBeacon(LOCATION(45, 131), Bar2, Bar3);
	CreateCommonBeacon(LOCATION(43, 155), Bar2, Bar3);
	CreateCommonBeacon(LOCATION(87, 181), Bar2, Bar3);
	CreateCommonBeacon(LOCATION(73, 183), Bar2, Bar3);
	CreateRareBeacon(LOCATION(96, 187), Bar2);
	CreateRareBeacon(LOCATION(66, 211), Bar2, Bar3);
	CreateCommonBeacon(LOCATION(70, 242), Bar3);

	// Beacons guarded by Weak AI Base
	CreateCommonBeacon(LOCATION(70, 114), Bar2, Bar3);
	CreateRareBeacon(LOCATION(78, 142), Bar2, Bar3);
	if (HumanPlayerCount() > 2)
	{
		CreateCommonBeacon(LOCATION(89, 130), Bar2, Bar3);
	}
	if (HumanPlayerCount() > 3)
	{
		CreateCommonBeacon(LOCATION(66, 162), Bar2, Bar3);
		CreateRareBeacon(LOCATION(54, 151), Bar2, Bar3);
	}

	// Beacons in Northern plateau
	CreateCommonBeacon(LOCATION(181, 3), Bar1, Bar2);
	CreateRareBeacon(LOCATION(146, 9), Bar1, Bar2);

	if (HumanPlayerCount() > 2)
	{
		CreateCommonBeacon(LOCATION(109, 13), Bar1, Bar2);
		CreateCommonBeacon(LOCATION(112, 31), Bar1, Bar2);
		CreateRareBeacon(LOCATION(211, 32), Bar1, Bar2);
	}
	if (HumanPlayerCount() > 3)
	{
		CreateCommonBeacon(LOCATION(137, 35), Bar1, Bar2);
		CreateCommonBeacon(LOCATION(173, 36), Bar1, Bar2);
		CreateRareBeacon(LOCATION(102, 54), Bar1, Bar2);
	}
	if (HumanPlayerCount() > 4)
	{
		CreateCommonBeacon(LOCATION(192, 61), Bar1, Bar2);
		CreateCommonBeacon(LOCATION(175, 65), Bar1, Bar2);
		CreateRareBeacon(LOCATION(98, 84), Bar1, Bar2);
	}

	// Beacons in Southern plateau
	CreateCommonBeacon(LOCATION(100, 171), Bar1, Bar2);
	CreateRareBeacon(LOCATION(167, 193), Bar1, Bar2);
	
	if (HumanPlayerCount() > 2)
	{
		CreateCommonBeacon(LOCATION(137, 181), Bar1, Bar2);
		CreateCommonBeacon(LOCATION(113, 217), Bar1, Bar2);
	}
	if(HumanPlayerCount() > 3)
	{
		CreateCommonBeacon(LOCATION(180, 226), Bar1, Bar2);
		CreateRareBeacon(LOCATION(153, 227), Bar1, Bar2);
	}
	if (HumanPlayerCount() > 4)
	{
		CreateCommonBeacon(LOCATION(140, 243), Bar1, Bar2);
		CreateCommonBeacon(LOCATION(178, 247), Bar1, Bar2);
	}
	

	// Beacons guarded by North AI Base
	CreateCommonBeacon(LOCATION(214, 76), Bar1, Bar2);
	CreateCommonBeacon(LOCATION(244, 91), Bar1, Bar2);

	if (HumanPlayerCount() > 2)
	{
		CreateRareBeacon(LOCATION(248, 107), Bar1, Bar2);
		CreateCommonBeacon(LOCATION(225, 101), Bar1, Bar2);
	}
	if (HumanPlayerCount() > 4)
	{
		CreateCommonBeacon(LOCATION(235, 126), Bar1, Bar2);
		CreateCommonBeacon(LOCATION(250, 124), Bar1, Bar2);
	}

	// Beacons guarded by South AI Base
	CreateCommonBeacon(LOCATION(216, 144), Bar1, Bar2);
	CreateCommonBeacon(LOCATION(229, 156), Bar1, Bar2);

	if (HumanPlayerCount() > 2)
	{
		CreateRareBeacon(LOCATION(240, 140), Bar1, Bar2);
		CreateCommonBeacon(LOCATION(216, 178), Bar1, Bar2);
	}
	if (HumanPlayerCount() > 3)
	{
		CreateRareBeacon(LOCATION(247, 198), Bar1, Bar2);
	}
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

	if (!hasBlightEnteredWestRegion && IsBlightInArea(MAP_RECT(86 + X_, 98 + Y_, 86 + X_, 131 + Y_)))
	{
		hasBlightEnteredWestRegion = true;
	}
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
	AllowWeakAIBaseAttack();
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
