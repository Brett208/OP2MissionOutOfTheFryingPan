#pragma once
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include <vector>

void CreateAIBuilding(Unit& unit, map_id unitType, LOCATION loc, PlayerNum aiPlayerNum, map_id Cargo,
	std::vector<Unit>& buildings);

void createGuardPostCluster(PlayerNum aiPlayerNum, LOCATION loc, std::vector<Unit>& buildings);

void SetupBuildingGroup(BuildingGroup& buildingGroup, Unit& structreFactory, Unit& vehicleFactory,
	std::vector<Unit>& buildings, PlayerNum aiPlayerNum, MAP_RECT idleRect);

void SetupMiningGroup(MiningGroup& miningGroupOut, Unit& mine, Unit& smelter, 
	MAP_RECT& oreIdleRect, int truckCount, PlayerNum aiPlayerNum);
