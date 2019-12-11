#include <vector>
#include "AIHelper.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"

void SetupBuildingGroup(BuildingGroup& buildingGroup, Unit& structreFactory, Unit& vehicleFactory, 
	std::vector<Unit>& buildings,  PlayerNum aiPlayerNum, MAP_RECT idleRect) {
	
	buildingGroup = CreateBuildingGroup(Player[aiPlayerNum]);

	Unit unit;
	TethysGame::CreateUnit(unit,map_id::mapConVec, idleRect.RandPt(), aiPlayerNum, mapNone, South);
	buildingGroup.TakeUnit(unit);
	TethysGame::CreateUnit(unit, map_id::mapEarthworker, idleRect.RandPt(), aiPlayerNum, mapNone, South);
	buildingGroup.TakeUnit(unit);

	buildingGroup.TakeUnit(structreFactory);
	buildingGroup.TakeUnit(vehicleFactory);
	buildingGroup.SetRect(idleRect);

	for (Unit building : buildings)
	{
		buildingGroup.RecordBuilding(building.Location(), building.GetType(), map_id::mapNone);
	}
}

void SetupMiningGroup(MiningGroup& miningGroupOut, Unit& mine, Unit& smelter, 
	MAP_RECT& oreIdleRect, int truckCount, PlayerNum aiPlayerNum)
{
	miningGroupOut = CreateMiningGroup(Player[aiPlayerNum]);

	//const LOCATION smelterLoc = smelter.Location();
	miningGroupOut.Setup(mine, smelter, oreIdleRect);

	Unit truck;
	for (int i = 0; i < truckCount; ++i)
	{
		TethysGame::CreateUnit(truck, map_id::mapCargoTruck, oreIdleRect.RandPt(), aiPlayerNum, map_id::mapNone, South);
		truck.DoSetLights(true);
		miningGroupOut.TakeUnit(truck);
	}

	miningGroupOut.SetTargCount(map_id::mapCargoTruck, map_id::mapNone, truckCount);
}
