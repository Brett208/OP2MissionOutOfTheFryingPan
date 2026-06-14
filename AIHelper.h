#pragma once
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include <vector>

struct BuildingGroupOptions
{
	int conVecCount = 2;
	int earthworkerCount = 1;
};

void CreateAIBuilding(Unit& unit, map_id unitType, LOCATION loc, PlayerNum playerNum, std::vector<Unit>& buildings);

void CreateGuardPostCluster(PlayerNum playerNum, LOCATION loc, std::vector<Unit>& buildings);

void SetupBuildingGroup(BuildingGroup& buildingGroup, Unit& structureFactory, Unit& vehicleFactory,
	std::vector<Unit>& buildings, PlayerNum playerNum, BuildingGroupOptions buildingGroupOptions = BuildingGroupOptions());

// Creates 2 smelters north of the mining beacon
void CreateCommonMineGroup3Bar(LOCATION beaconLocation, PlayerNum playerNum, std::vector<Unit>& buildings);

// Creates 2 smelters north of the mining beacon
void CreateRareMineGroup3Bar(LOCATION beaconLocation, PlayerNum playerNum, std::vector<Unit>& buildings);

void SetupMiningGroup(MiningGroup& miningGroupOut, Unit& mine, Unit& smelter, int truckCount, PlayerNum playerNum);
