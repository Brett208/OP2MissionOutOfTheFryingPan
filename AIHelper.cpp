#include "AIHelper.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"

namespace {
	void CreateMiningGroup(LOCATION beaconLocation, PlayerNum playerNum, 
		std::vector<Unit>& buildings, BeaconTypes beaconType, Yield yield);
}

void CreateAIBuilding(Unit& unit, map_id unitType, LOCATION loc, PlayerNum aiPlayerNum, std::vector<Unit>& buildings)
{
	const UnitDirection rotation = UnitDirection::South;
	TethysGame::CreateUnit(unit, unitType, loc, aiPlayerNum, mapNone, rotation);
	buildings.push_back(unit);
}

void CreateGuardPostCluster(PlayerNum aiPlayerNum, LOCATION loc, std::vector<Unit>& buildings) 
{
	Unit unit;
	TethysGame::CreateUnit(unit, mapGuardPost, loc, aiPlayerNum, mapEMP, South);
	buildings.push_back(unit);

	loc.y += 2;
	TethysGame::CreateUnit(unit, mapGuardPost, loc, aiPlayerNum, mapESG, South);
	buildings.push_back(unit);

	loc.x += 2;
	loc.y -= 1;
	TethysGame::CreateUnit(unit, mapGuardPost, loc, aiPlayerNum, mapStickyfoam, South);
	buildings.push_back(unit);
}

void SetupBuildingGroup(BuildingGroup& buildingGroup, Unit& structureFactory, Unit& vehicleFactory, 
	std::vector<Unit>& buildings,  PlayerNum aiPlayerNum, MAP_RECT idleRect) {
	
	buildingGroup = CreateBuildingGroup(Player[aiPlayerNum]);

	Unit unit;
	TethysGame::CreateUnit(unit,map_id::mapConVec, idleRect.RandPt(), aiPlayerNum, mapNone, South);
	unit.DoSetLights(true);
	buildingGroup.TakeUnit(unit);
	TethysGame::CreateUnit(unit, map_id::mapConVec, idleRect.RandPt(), aiPlayerNum, mapNone, South);
	unit.DoSetLights(true);
	buildingGroup.TakeUnit(unit);
	TethysGame::CreateUnit(unit, map_id::mapEarthworker, idleRect.RandPt(), aiPlayerNum, mapNone, South);
	unit.DoSetLights(true);
	buildingGroup.TakeUnit(unit);

	buildingGroup.TakeUnit(structureFactory);
	buildingGroup.TakeUnit(vehicleFactory);
	buildingGroup.SetRect(idleRect);

	for (Unit building : buildings)
	{
		buildingGroup.RecordBuilding(building.Location(), building.GetType(), building.GetCargo());
	}
}

void CreateCommonMineGroup3Bar(LOCATION beaconLocation, PlayerNum playerNum, std::vector<Unit>& buildings)
{
	CreateMiningGroup(beaconLocation, playerNum, buildings, BeaconTypes::OreTypeCommon, Yield::Bar3);
}

void CreateRareMineGroup3Bar(LOCATION beaconLocation, PlayerNum playerNum, std::vector<Unit>& buildings)
{
	CreateMiningGroup(beaconLocation, playerNum, buildings, BeaconTypes::OreTypeRare, Yield::Bar3);
}

namespace {
	void CreateMiningGroup(LOCATION beaconLocation, PlayerNum playerNum, std::vector<Unit>& buildings, BeaconTypes beaconType, Yield yield)
	{
		TethysGame::CreateBeacon(mapMiningBeacon, beaconLocation.x, beaconLocation.y, beaconType, yield, Variant3);

		Unit mine;
		// Outpost 2 bug, you create both common and rare ore mines using the mapCommonOreMine enum
		CreateAIBuilding(mine, mapCommonOreMine, beaconLocation, playerNum, buildings);

		map_id smelterType = beaconType == BeaconTypes::OreTypeCommon ? mapCommonOreSmelter : mapRareOreSmelter;

		Unit smelter;
		Unit smelter2;
		CreateAIBuilding(smelter, smelterType, beaconLocation + LOCATION(-2, -4), playerNum, buildings);
		CreateAIBuilding(smelter2, smelterType, beaconLocation + LOCATION(3, -4), playerNum, buildings);

		MAP_RECT miningIdleRect(beaconLocation.x - 5, beaconLocation.y - 5, beaconLocation.x + 5, beaconLocation.y + 5);

		MiningGroup miningGroup;
		SetupMiningGroup(miningGroup, mine, smelter, miningIdleRect, 3, playerNum);
		SetupMiningGroup(miningGroup, mine, smelter, miningIdleRect, 3, playerNum);
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
