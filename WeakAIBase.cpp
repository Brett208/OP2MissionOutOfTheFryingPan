#include "WeakAIBase.h"
#include "DefensiveFightGroup.h"
#include "AIHelper.h"
#include "AIPlayer.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include <memory>
#include <vector>


int GetTankCount();
std::vector<std::unique_ptr<OffensiveFightGroup>> offensiveFightGroups;
std::vector<Unit> defensiveVehicleFactories;
std::vector<Unit> weakAiBuildings;

std::vector<TargetTankCount> offensiveTankCount{
	TargetTankCount {map_id::mapLynx, map_id::mapMicrowave, 0}
};

void UpdateWeakAIBase()
{
	for (auto& offensiveFightGroup : offensiveFightGroups) {
		offensiveFightGroup->UpdateTaskedFightGroups();
		if (offensiveFightGroup->IsFull()) {
			offensiveFightGroup->Attack(offensiveTankCount);
		}
	}
}

void BuildAIBase(PlayerNum  aiPlayerNum, const LOCATION& initBaseLoc)
{
	offensiveTankCount[0].count = GetTankCount();

	LOCATION currentLoc = initBaseLoc;
	LOCATION vechStartLoc(initBaseLoc.x + 4, initBaseLoc.y + 4);
	MAP_RECT miningIdleRect(initBaseLoc.x - 4, initBaseLoc.y, initBaseLoc.x + 6, initBaseLoc.y + 4);
	MAP_RECT buidlingIdleRect(initBaseLoc.x - 6, initBaseLoc.y, initBaseLoc.x + 8, initBaseLoc.y + 6);
	Unit unit;
	
	CreateInitialAIBuilding(unit, mapCommandCenter, initBaseLoc, aiPlayerNum, map_id::mapNone);//ComandCenter
	
	currentLoc.x = initBaseLoc.x + 5;
	Unit structureFactory;
	CreateInitialAIBuilding(structureFactory, map_id::mapStructureFactory, currentLoc, aiPlayerNum, map_id::mapNone);
	
	currentLoc.x = initBaseLoc.x + 2;
	currentLoc.y = initBaseLoc.y - 4;
	CreateInitialAIBuilding(unit, mapResidence, currentLoc, aiPlayerNum, map_id::mapNone);
	
	currentLoc.x = initBaseLoc.x - 2;
	CreateInitialAIBuilding(unit, mapAgridome, currentLoc, aiPlayerNum, map_id::mapNone);
	
	currentLoc.x = initBaseLoc.x - 6;
	CreateInitialAIBuilding(unit, mapDIRT, currentLoc, aiPlayerNum, map_id::mapNone);

	currentLoc.x = initBaseLoc.x + 5;
	CreateInitialAIBuilding(unit, mapMedicalCenter, currentLoc, aiPlayerNum, map_id::mapNone);
	
	currentLoc.x = initBaseLoc.x - 5;
	currentLoc.y = initBaseLoc.y;
	Unit commonSmelter;
	CreateInitialAIBuilding(commonSmelter, mapCommonOreSmelter, currentLoc, aiPlayerNum, map_id::mapNone);
	weakAiBuildings.push_back(commonSmelter);
	
	currentLoc.x = initBaseLoc.x - 10;
	Unit secondCommonSmelter;
	CreateInitialAIBuilding(commonSmelter, mapCommonOreSmelter, currentLoc, aiPlayerNum, map_id::mapNone);

	currentLoc.y = initBaseLoc.y + 4;
	Unit commonMine;
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, currentLoc.x, currentLoc.y, BeaconTypes::OreTypeCommon, Yield::Bar2, Variant::Variant3);
	CreateInitialAIBuilding(commonMine, mapCommonOreMine, currentLoc, aiPlayerNum, map_id::mapNone);

	currentLoc.x = initBaseLoc.x;
	currentLoc.y = initBaseLoc.y + 5;
	Unit defenseVehicleFactory;
	CreateInitialAIBuilding(defenseVehicleFactory, map_id::mapVehicleFactory, currentLoc, aiPlayerNum, map_id::mapNone);
	defensiveVehicleFactories.push_back(defenseVehicleFactory);

	currentLoc.y = initBaseLoc.y + 9;
	Unit offenseVehicleFactory;

	MAP_RECT offensiveGuardedRect(85 + X_, 140 + Y_, 89 + X_, 144 + Y_);

	for (int i = 0; i < HumanPlayerCount() - 1; ++i)
	{
		CreateInitialAIBuilding(offenseVehicleFactory, mapVehicleFactory, currentLoc, aiPlayerNum, map_id::mapNone);

		OffensiveFightGroup offensiveFightGroup(aiPlayerNum, HumanPlayerCount());
		offensiveFightGroup.Initialize(offensiveGuardedRect, { offenseVehicleFactory }, offensiveTankCount);
		offensiveFightGroups.push_back(std::make_unique<OffensiveFightGroup>(offensiveFightGroup));

		currentLoc.y = currentLoc.y + 4;
	}

	currentLoc.y = initBaseLoc.y + 16;
	CreateInitialAIBuilding(unit, mapTokamak, currentLoc, aiPlayerNum, map_id::mapNone);

	currentLoc.x = initBaseLoc.x + 3;
	CreateInitialAIBuilding(unit, mapTokamak, currentLoc, aiPlayerNum, map_id::mapNone);

	CreateTubeLine(initBaseLoc + LOCATION(0, -3), initBaseLoc + LOCATION(0, -1));
	CreateTubeLine(initBaseLoc + LOCATION(0, 1), initBaseLoc + LOCATION(0, 5));
	CreateTubeLine(initBaseLoc + LOCATION(-2, 0), initBaseLoc + LOCATION(-1, 0));
	CreateTubeLine(initBaseLoc + LOCATION(1, 0), initBaseLoc + LOCATION(3, 0));

	BuildingGroup buildingGroup;
	SetupBuildingGroup(buildingGroup, structureFactory, defenseVehicleFactory, weakAiBuildings, aiPlayerNum, buidlingIdleRect);

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
}

void CreateInitialAIBuilding(Unit& unit, map_id unitType, LOCATION loc, PlayerNum aiPlayerNum, map_id Cargo)
{
	const UnitDirection rotation = UnitDirection::South;
	TethysGame::CreateUnit(unit, unitType, loc, aiPlayerNum, Cargo, rotation);
	weakAiBuildings.push_back(unit);
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

