#include "AIHelper.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"

namespace {
	void CreateMiningGroup(LOCATION beaconLocation, PlayerNum playerNum, 
		std::vector<Unit>& buildings, BeaconTypes beaconType, Yield yield);
}

void CreateAIBuilding(Unit& unit, map_id unitType, LOCATION loc, PlayerNum playerNum, std::vector<Unit>& buildings)
{
	const UnitDirection rotation = UnitDirection::South;
	TethysGame::CreateUnit(unit, unitType, loc, playerNum, mapNone, rotation);
	buildings.push_back(unit);
}

void CreateGuardPostCluster(PlayerNum playerNum, LOCATION loc, std::vector<Unit>& buildings) 
{
	Unit unit;
	TethysGame::CreateUnit(unit, mapGuardPost, loc, playerNum, mapEMP, South);
	buildings.push_back(unit);

	loc.y += 2;
	TethysGame::CreateUnit(unit, mapGuardPost, loc, playerNum, mapESG, South);
	buildings.push_back(unit);

	loc.x += 2;
	loc.y -= 1;
	TethysGame::CreateUnit(unit, mapGuardPost, loc, playerNum, mapStickyfoam, South);
	buildings.push_back(unit);
}

void SetupBuildingGroup(BuildingGroup& buildingGroup, Unit& structureFactory, Unit& vehicleFactory, 
	std::vector<Unit>& buildings, PlayerNum playerNum) {
	
	MAP_RECT vehicleIdleRect(structureFactory.Location(), structureFactory.Location() + LOCATION(6, 6));
	vehicleIdleRect.Inflate(5, 5);

	buildingGroup = CreateBuildingGroup(Player[playerNum]);

	Unit unit;
	TethysGame::CreateUnit(unit, map_id::mapConVec, vehicleIdleRect.RandPt(), playerNum, mapNone, South);
	unit.DoSetLights(true);
	buildingGroup.TakeUnit(unit);
	TethysGame::CreateUnit(unit, map_id::mapConVec, vehicleIdleRect.RandPt(), playerNum, mapNone, South);
	unit.DoSetLights(true);
	buildingGroup.TakeUnit(unit);
	TethysGame::CreateUnit(unit, map_id::mapEarthworker, vehicleIdleRect.RandPt(), playerNum, mapNone, South);
	unit.DoSetLights(true);
	buildingGroup.TakeUnit(unit);

	buildingGroup.TakeUnit(structureFactory);
	buildingGroup.TakeUnit(vehicleFactory);
	buildingGroup.SetRect(vehicleIdleRect);

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

		MiningGroup miningGroup;
		SetupMiningGroup(miningGroup, mine, smelter, 3, playerNum);
		SetupMiningGroup(miningGroup, mine, smelter, 3, playerNum);
	}
}

void SetupMiningGroup(MiningGroup& miningGroupOut, Unit& mine, Unit& smelter, int truckCount, PlayerNum playerNum)
{
	miningGroupOut = CreateMiningGroup(Player[playerNum]);

	MAP_RECT oreIdleRect(smelter.Location(), smelter.Location());
	oreIdleRect.Inflate(5, 5);

	miningGroupOut.Setup(mine, smelter, oreIdleRect);

	Unit truck;
	for (int i = 0; i < truckCount; ++i)
	{
		TethysGame::CreateUnit(truck, map_id::mapCargoTruck, oreIdleRect.RandPt(), playerNum, map_id::mapNone, South);
		truck.DoSetLights(true);
		miningGroupOut.TakeUnit(truck);
	}

	miningGroupOut.SetTargCount(map_id::mapCargoTruck, map_id::mapNone, truckCount);
}
