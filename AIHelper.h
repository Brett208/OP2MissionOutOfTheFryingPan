#pragma once
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"

void SetupBuildingGroup(BuildingGroup& buildingGroup, Unit& structreFactory, Unit& vehicleFactory,
	std::vector<Unit>& buildings, PlayerNum aiPlayerNum, MAP_RECT idleRect);

void SetupMiningGroup(MiningGroup& miningGroupOut, Unit& mine, Unit& smelter, 
	MAP_RECT& oreIdleRect, int truckCount, PlayerNum aiPlayerNum);
