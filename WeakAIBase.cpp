#include "WeakAIBase.h"
#include "DefensiveFightGroup.h"
#include "AIHelper.h"
#include "AIPlayer.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include <memory>
#include <vector>


int GetDefensiveTankCount();
std::vector<std::unique_ptr<OffensiveFightGroup>> offensiveFightGroups;
std::vector<Unit> defensiveVehicleFactories;
std::vector<Unit> weakAiBuildings;

std::vector<TargetTankCount> offensiveTankCount{
	TargetTankCount {map_id::mapLynx, map_id::mapMicrowave, 5}
};

Export void AddTankWeakAIBase()
{
	auto& offensiveFightGroup = offensiveFightGroups[TethysGame::GetRand(offensiveFightGroups.size())];
	offensiveFightGroup->CreateTank(mapLynx, mapMicrowave);	
}

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
	LOCATION currentLoc = initBaseLoc;
	LOCATION vechStartLoc(initBaseLoc.x + 4, initBaseLoc.y + 4);
	MAP_RECT miningIdleRect(initBaseLoc.x - 4, initBaseLoc.y, initBaseLoc.x + 6, initBaseLoc.y + 4);
	MAP_RECT buidlingIdleRect(initBaseLoc.x - 6, initBaseLoc.y, initBaseLoc.x + 8, initBaseLoc.y + 6);
	Unit unit;

	CreateAIBuilding(unit, mapCommandCenter, initBaseLoc, aiPlayerNum, map_id::mapNone, weakAiBuildings);//ComandCenter

	currentLoc.x = initBaseLoc.x + 5;
	Unit structureFactory;
	CreateAIBuilding(structureFactory, map_id::mapStructureFactory, currentLoc, aiPlayerNum, map_id::mapNone, weakAiBuildings);

	currentLoc.x = initBaseLoc.x + 2;
	currentLoc.y = initBaseLoc.y - 4;
	CreateAIBuilding(unit, mapResidence, currentLoc, aiPlayerNum, map_id::mapNone, weakAiBuildings);

	currentLoc.x = initBaseLoc.x - 2;
	CreateAIBuilding(unit, mapAgridome, currentLoc, aiPlayerNum, map_id::mapNone, weakAiBuildings);

	currentLoc.x = initBaseLoc.x - 6;
	CreateAIBuilding(unit, mapDIRT, currentLoc, aiPlayerNum, map_id::mapNone, weakAiBuildings);

	currentLoc.x = initBaseLoc.x + 5;
	CreateAIBuilding(unit, mapMedicalCenter, currentLoc, aiPlayerNum, map_id::mapNone, weakAiBuildings);

	currentLoc.x = initBaseLoc.x - 5;
	currentLoc.y = initBaseLoc.y;
	Unit commonSmelter;
	CreateAIBuilding(commonSmelter, mapCommonOreSmelter, currentLoc, aiPlayerNum, map_id::mapNone, weakAiBuildings);
	weakAiBuildings.push_back(commonSmelter);

	currentLoc.x = initBaseLoc.x - 10;
	Unit secondCommonSmelter;
	CreateAIBuilding(secondCommonSmelter, mapCommonOreSmelter, currentLoc, aiPlayerNum, map_id::mapNone, weakAiBuildings);
	weakAiBuildings.push_back(secondCommonSmelter);

	currentLoc.y = initBaseLoc.y + 4;
	Unit commonMine;
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, currentLoc.x, currentLoc.y, BeaconTypes::OreTypeCommon, Yield::Bar2, Variant::Variant3);
	CreateAIBuilding(commonMine, mapCommonOreMine, currentLoc, aiPlayerNum, map_id::mapNone, weakAiBuildings);

	currentLoc.x = initBaseLoc.x;
	currentLoc.y = initBaseLoc.y + 5;
	Unit defenseVehicleFactory;
	CreateAIBuilding(defenseVehicleFactory, map_id::mapVehicleFactory, currentLoc, aiPlayerNum, map_id::mapNone, weakAiBuildings);
	defensiveVehicleFactories.push_back(defenseVehicleFactory);

	currentLoc.y = initBaseLoc.y + 9;
	Unit offenseVehicleFactory;

	MAP_RECT offensiveGuardedRect(80 + X_, 135 + Y_, 89 + X_, 145 + Y_);

	for (int i = 0; i < HumanPlayerCount() - 1; ++i)
	{
		CreateAIBuilding(offenseVehicleFactory, mapVehicleFactory, currentLoc, aiPlayerNum, map_id::mapNone, weakAiBuildings);

		OffensiveFightGroup offensiveFightGroup(aiPlayerNum, HumanPlayerCount());
		offensiveFightGroup.Initialize(offensiveGuardedRect, { offenseVehicleFactory }, offensiveTankCount);
		offensiveFightGroups.push_back(std::make_unique<OffensiveFightGroup>(offensiveFightGroup));

		currentLoc.y += + 4;
	}

	currentLoc.x = initBaseLoc.x - 12;
	currentLoc.y = initBaseLoc.y + 16;
	CreateAIBuilding(unit, mapTokamak, currentLoc, aiPlayerNum, map_id::mapNone, weakAiBuildings);

	currentLoc.x += + 3;
	CreateAIBuilding(unit, mapTokamak, currentLoc, aiPlayerNum, map_id::mapNone, weakAiBuildings);

	createGuardPostCluster(aiPlayerNum, LOCATION(88 + X_, 127 + Y_), weakAiBuildings);
	createGuardPostCluster(aiPlayerNum, LOCATION(80 + X_, 118 + Y_), weakAiBuildings);
	createGuardPostCluster(aiPlayerNum, LOCATION(85 + X_, 138 + Y_), weakAiBuildings);
	createGuardPostCluster(aiPlayerNum, LOCATION(80 + X_, 152 + Y_), weakAiBuildings);

	CreateTubeLine(initBaseLoc + LOCATION(0, -3), initBaseLoc + LOCATION(0, -1));
	CreateTubeLine(initBaseLoc + LOCATION(0, 1), initBaseLoc + LOCATION(0, 5));
	CreateTubeLine(initBaseLoc + LOCATION(-2, 0), initBaseLoc + LOCATION(-1, 0));
	CreateTubeLine(initBaseLoc + LOCATION(1, 0), initBaseLoc + LOCATION(3, 0));

	BuildingGroup buildingGroup;
	SetupBuildingGroup(buildingGroup, structureFactory, defenseVehicleFactory, weakAiBuildings, aiPlayerNum, buidlingIdleRect);
	recordBuildings(buildingGroup);


	MiningGroup miningGroup;
	SetupMiningGroup(miningGroup, commonMine, commonSmelter, miningIdleRect, 3, aiPlayerNum);
	SetupMiningGroup(miningGroup, commonMine, secondCommonSmelter, miningIdleRect, 3, aiPlayerNum);

	MAP_RECT guardedRect(68 + X_, 122 + Y_, 85 + X_, 140 + Y_);

	const std::vector<TargetTankCount> targetTanks{
		TargetTankCount{map_id::mapLynx, map_id::mapMicrowave, GetDefensiveTankCount()},
		TargetTankCount{map_id::mapLynx, map_id::mapESG, GetDefensiveTankCount()},
		TargetTankCount{map_id::mapLynx, map_id::mapEMP, GetDefensiveTankCount()},
		TargetTankCount{map_id::mapLynx, map_id::mapRPG, GetDefensiveTankCount()},
		TargetTankCount{map_id::mapLynx, map_id::mapStickyfoam, GetDefensiveTankCount()}
	};

	DefensiveFightGroup defensiveFightGroup(aiPlayerNum, HumanPlayerCount());

	defensiveFightGroup.Initialize(guardedRect, defensiveVehicleFactories);
	defensiveFightGroup.Populate(targetTanks);
}

int GetDefensiveTankCount()
{
	int humanPlayerCount = HumanPlayerCount();
	switch (humanPlayerCount)
	{
	case 2: {
		return 3;
	}
	case 3: {
		return 5;
	}
	default: {
		return 8;
	}
	}
}

void createGuardPostCluster(PlayerNum aiPlayerNum, LOCATION loc) {
	
	Unit unit;
	TethysGame::CreateUnit(unit, mapGuardPost, loc, aiPlayerNum, mapEMP, South);
	weakAiBuildings.push_back(unit);

	loc.y += 2;
	TethysGame::CreateUnit(unit, mapGuardPost, loc, aiPlayerNum, mapESG, South);
	weakAiBuildings.push_back(unit);

	loc.x += 2;
	loc.y -= 1;
	TethysGame::CreateUnit(unit, mapGuardPost, loc, aiPlayerNum, mapStickyfoam, South);
	weakAiBuildings.push_back(unit);
}

void recordBuildings(BuildingGroup& buildingGroup)
{
	buildingGroup.RecordBuilding(LOCATION(74 + X_, 125 + Y_), mapAgridome, mapNone);
	buildingGroup.RecordBuilding(LOCATION(78 + X_, 125 + Y_), mapResidence, mapNone);
	buildingGroup.RecordBuilding(LOCATION(81 + X_, 125 + Y_), mapMedicalCenter, mapNone);
	buildingGroup.RecordBuilding(LOCATION(70 + X_, 125 + Y_), mapDIRT, mapNone);
	buildingGroup.RecordBuilding(LOCATION(66 + X_, 128 + Y_), mapDIRT, mapNone);
}
