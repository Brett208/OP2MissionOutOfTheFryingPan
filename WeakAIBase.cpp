#include "WeakAIBase.h"
#include "DefensiveFightGroup.h"
#include "AIHelper.h"
#include "AIPlayer.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include <memory>


int GetTankCount();
std::unique_ptr<OffensiveFightGroup> offensiveFightGroupPointer;
std::vector<Unit> offensiveVehicleFactories;
std::vector<Unit> defensiveVehicleFactories;

std::vector<TargetTankCount> offensiveTankCount{
	TargetTankCount {map_id::mapLynx, map_id::mapMicrowave, 0}
};

void UpdateWeakAIBase()
{
	offensiveFightGroupPointer->UpdateTaskedFightGroups();
	if (offensiveFightGroupPointer->IsFull()) {
		offensiveFightGroupPointer->Attack(offensiveTankCount);
	}
}

void BuildAIBase(PlayerNum  aiPlayerNum, const LOCATION& initBaseLoc)
{
	offensiveTankCount[0].count = GetTankCount();

	LOCATION currentLoc = initBaseLoc;
	LOCATION vechStartLoc(initBaseLoc.x + 4, initBaseLoc.y + 4);
	MAP_RECT miningIdleRect(initBaseLoc.x - 4, initBaseLoc.y, initBaseLoc.x + 6, initBaseLoc.y + 4);
	Unit unit;
	
	CreateInitialAIUnit(unit, mapCommandCenter, initBaseLoc, aiPlayerNum, map_id::mapNone);//ComandCenter
	
	currentLoc.x = initBaseLoc.x + 5;
	CreateInitialAIUnit(unit, mapStructureFactory, currentLoc, aiPlayerNum, map_id::mapNone);

	currentLoc.x = initBaseLoc.x + 2;
	currentLoc.y = initBaseLoc.y + - 4;
	CreateInitialAIUnit(unit, mapResidence, currentLoc, aiPlayerNum, map_id::mapNone);

	currentLoc.x = initBaseLoc.x - 2;
	CreateInitialAIUnit(unit, mapAgridome, currentLoc, aiPlayerNum, map_id::mapNone);

	currentLoc.x = initBaseLoc.x - 6;
	CreateInitialAIUnit(unit, mapDIRT, currentLoc, aiPlayerNum, map_id::mapNone);

	currentLoc.x = initBaseLoc.x + 5;
	CreateInitialAIUnit(unit, mapMedicalCenter, currentLoc, aiPlayerNum, map_id::mapNone);
	
	currentLoc.x = initBaseLoc.x - 5;
	currentLoc.y = initBaseLoc.y;
	Unit commonSmelter;
	CreateInitialAIUnit(commonSmelter, mapCommonOreSmelter, currentLoc, aiPlayerNum, map_id::mapNone);
	
	currentLoc.x = initBaseLoc.x - 10;
	Unit secondCommonSmelter;
	CreateInitialAIUnit(commonSmelter, mapCommonOreSmelter, currentLoc, aiPlayerNum, map_id::mapNone);

	currentLoc.y = initBaseLoc.y + 4;
	Unit commonMine;
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, currentLoc.x, currentLoc.y, BeaconTypes::OreTypeCommon, Yield::Bar2, Variant::Variant3);
	CreateInitialAIUnit(commonMine, mapCommonOreMine, currentLoc, aiPlayerNum, map_id::mapNone);

	currentLoc.x = initBaseLoc.x;
	currentLoc.y = initBaseLoc.y + 5;
	Unit defenseVehicleFactory;
	CreateInitialAIUnit(defenseVehicleFactory, mapVehicleFactory, currentLoc, aiPlayerNum, map_id::mapNone);
	defensiveVehicleFactories.push_back(defenseVehicleFactory);

	currentLoc.y = initBaseLoc.y + 9;
	Unit offenseVehicleFactory;

	for (int i = 0; i < HumanPlayerCount() - 1; ++i)
	{
		CreateInitialAIUnit(offenseVehicleFactory, mapVehicleFactory, currentLoc, aiPlayerNum, map_id::mapNone);
		offensiveVehicleFactories.push_back(offenseVehicleFactory);
		currentLoc.y = currentLoc.y + 4;
	}

	currentLoc.y = initBaseLoc.y + 16;
	CreateInitialAIUnit(unit, mapTokamak, currentLoc, aiPlayerNum, map_id::mapNone);

	currentLoc.x = initBaseLoc.x + 3;
	CreateInitialAIUnit(unit, mapTokamak, currentLoc, aiPlayerNum, map_id::mapNone);

	CreateTubeLine(initBaseLoc + LOCATION(0, -3), initBaseLoc + LOCATION(0, -1));
	CreateTubeLine(initBaseLoc + LOCATION(0, 1), initBaseLoc + LOCATION(0, 5));
	CreateTubeLine(initBaseLoc + LOCATION(-2, 0), initBaseLoc + LOCATION(-1, 0));
	CreateTubeLine(initBaseLoc + LOCATION(1, 0), initBaseLoc + LOCATION(3, 0));

	MiningGroup miningGroup;
	SetupMiningGroup(miningGroup, commonMine, commonSmelter, miningIdleRect, 3, aiPlayerNum);
	//SetupMiningGroup(miningGroup, commonMine, secondCommonSmelter, miningIdleRect, 3, aiPlayerNum);

	MAP_RECT guardedRect(68 + X_, 122 + Y_, 85 + X_, 140 + Y_);

	const std::vector<TargetTankCount> targetTanks{
		TargetTankCount{map_id::mapLynx, map_id::mapMicrowave, 3},
		TargetTankCount{map_id::mapLynx, map_id::mapESG, 3},
		TargetTankCount{map_id::mapLynx, map_id::mapEMP, 3},
		TargetTankCount{map_id::mapLynx, map_id::mapRPG, 3},
		TargetTankCount{map_id::mapLynx, map_id::mapStickyfoam, 3}
	};

	DefensiveFightGroup defensiveFightGroup(aiPlayerNum, HumanPlayerCount());

	defensiveFightGroup.Initialize(guardedRect, defensiveVehicleFactories);
	defensiveFightGroup.Populate(targetTanks);

	MAP_RECT offensiveGuardedRect(85 + X_, 140 + Y_, 89 + X_, 144 + Y_);
	OffensiveFightGroup offensiveFightGroup(aiPlayerNum, HumanPlayerCount());
	
	offensiveFightGroup.Initialize(offensiveGuardedRect, offensiveVehicleFactories, offensiveTankCount);

	offensiveFightGroupPointer = std::make_unique<OffensiveFightGroup>(offensiveFightGroup);
}

void CreateInitialAIUnit(Unit& unit, map_id unitType, LOCATION loc, PlayerNum aiPlayerNum, map_id Cargo)
{
	const UnitDirection rotation = UnitDirection::South;
	TethysGame::CreateUnit(unit, unitType, loc, aiPlayerNum, Cargo, rotation);
}

int GetTankCount()
{
	int humanPlayerCount = HumanPlayerCount();
	switch (humanPlayerCount)
	{
	case 2: {
		return 5;
	}
	case 3: {
		return 8;
	}
	default: {
		return 12;
	}
	}
}

