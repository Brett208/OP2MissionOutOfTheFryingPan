#include "WeakAIBase.h"
#include "DefensiveFightGroup.h"
#include "OffensiveFightGroup.h"
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
	Unit unit;

	CreateAIBuilding(unit, mapCommandCenter, initBaseLoc, aiPlayerNum, weakAiBuildings);//ComandCenter

	currentLoc.x = initBaseLoc.x + 5;
	Unit structureFactory;
	CreateAIBuilding(structureFactory, map_id::mapStructureFactory, currentLoc, aiPlayerNum, weakAiBuildings);

	currentLoc.x = initBaseLoc.x + 2;
	currentLoc.y = initBaseLoc.y - 4;
	CreateAIBuilding(unit, mapResidence, currentLoc, aiPlayerNum, weakAiBuildings);

	currentLoc.x = initBaseLoc.x - 2;
	CreateAIBuilding(unit, mapAgridome, currentLoc, aiPlayerNum, weakAiBuildings);

	currentLoc.x = initBaseLoc.x - 6;
	CreateAIBuilding(unit, mapDIRT, currentLoc, aiPlayerNum, weakAiBuildings);

	currentLoc.x = initBaseLoc.x + 5;
	CreateAIBuilding(unit, mapMedicalCenter, currentLoc, aiPlayerNum, weakAiBuildings);

	currentLoc.x = initBaseLoc.x - 5;
	currentLoc.y = initBaseLoc.y;
	Unit commonSmelter;
	CreateAIBuilding(commonSmelter, mapCommonOreSmelter, currentLoc, aiPlayerNum, weakAiBuildings);

	Unit commonSmelter3;
	currentLoc.x = initBaseLoc.x - 15;
	CreateAIBuilding(commonSmelter3, mapCommonOreSmelter, currentLoc, aiPlayerNum, weakAiBuildings);

	currentLoc.x = initBaseLoc.x - 10;
	Unit commonSmelter2;
	CreateAIBuilding(commonSmelter2, mapCommonOreSmelter, currentLoc, aiPlayerNum, weakAiBuildings);

	currentLoc.y = initBaseLoc.y + 4;
	Unit commonMine;
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, currentLoc.x, currentLoc.y, BeaconTypes::OreTypeCommon, Yield::Bar2, Variant::Variant3);
	CreateAIBuilding(commonMine, mapCommonOreMine, currentLoc, aiPlayerNum, weakAiBuildings);

	currentLoc.x = initBaseLoc.x;
	currentLoc.y = initBaseLoc.y + 5;
	Unit defenseVehicleFactory;
	CreateAIBuilding(defenseVehicleFactory, map_id::mapVehicleFactory, currentLoc, aiPlayerNum, weakAiBuildings);
	defensiveVehicleFactories.push_back(defenseVehicleFactory);

	currentLoc.y = initBaseLoc.y + 9;
	Unit offenseVehicleFactory;

	MAP_RECT offensiveGuardedRect(80 + X_, 135 + Y_, 89 + X_, 145 + Y_);

	for (int i = 0; i < HumanPlayerCount() - 1; ++i)
	{
		CreateAIBuilding(offenseVehicleFactory, mapVehicleFactory, currentLoc, aiPlayerNum, weakAiBuildings);

		OffensiveFightGroup offensiveFightGroup(aiPlayerNum, HumanPlayerCount());
		offensiveFightGroup.Initialize(offensiveGuardedRect, { offenseVehicleFactory }, offensiveTankCount);
		offensiveFightGroups.push_back(std::make_unique<OffensiveFightGroup>(offensiveFightGroup));

		currentLoc.y += + 4;
	}

	currentLoc.x = initBaseLoc.x - 12;
	currentLoc.y = initBaseLoc.y + 16;
	CreateAIBuilding(unit, mapTokamak, currentLoc, aiPlayerNum, weakAiBuildings);

	currentLoc.x += + 3;
	CreateAIBuilding(unit, mapTokamak, currentLoc, aiPlayerNum, weakAiBuildings);

	CreateGuardPostCluster(aiPlayerNum, LOCATION(88 + X_, 127 + Y_), weakAiBuildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(68 + X_, 118 + Y_), weakAiBuildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(80 + X_, 118 + Y_), weakAiBuildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(85 + X_, 138 + Y_), weakAiBuildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(80 + X_, 152 + Y_), weakAiBuildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(66 + X_, 152 + Y_), weakAiBuildings);


	CreateTubeLine(initBaseLoc + LOCATION(0, -3), initBaseLoc + LOCATION(0, -1));
	CreateTubeLine(initBaseLoc + LOCATION(0, 1), initBaseLoc + LOCATION(0, 5));
	CreateTubeLine(initBaseLoc + LOCATION(-2, 0), initBaseLoc + LOCATION(-1, 0));
	CreateTubeLine(initBaseLoc + LOCATION(1, 0), initBaseLoc + LOCATION(3, 0));

	BuildingGroup buildingGroup;
	SetupBuildingGroup(buildingGroup, structureFactory, defenseVehicleFactory, weakAiBuildings, aiPlayerNum);
	RecordBuildings(buildingGroup);

	MAP_RECT miningIdleRect(initBaseLoc.x - 4, initBaseLoc.y, initBaseLoc.x + 6, initBaseLoc.y + 4);
	MiningGroup miningGroup;
	SetupMiningGroup(miningGroup, commonMine, commonSmelter, 2, aiPlayerNum);
	SetupMiningGroup(miningGroup, commonMine, commonSmelter2, 2, aiPlayerNum);
	SetupMiningGroup(miningGroup, commonMine, commonSmelter3, 2, aiPlayerNum);

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

void RecordBuildings(BuildingGroup& buildingGroup)
{
	buildingGroup.RecordBuilding(LOCATION(74 + X_, 125 + Y_), mapAgridome, mapNone);
	buildingGroup.RecordBuilding(LOCATION(78 + X_, 125 + Y_), mapResidence, mapNone);
	buildingGroup.RecordBuilding(LOCATION(81 + X_, 125 + Y_), mapMedicalCenter, mapNone);
	buildingGroup.RecordBuilding(LOCATION(70 + X_, 125 + Y_), mapDIRT, mapNone);
	buildingGroup.RecordBuilding(LOCATION(66 + X_, 128 + Y_), mapDIRT, mapNone);
}
