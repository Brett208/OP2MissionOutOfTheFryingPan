#include "NorthAIBase.h"
#include "AIHelper.h"
#include "AIPlayer.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include <vector>

void BuildNorthAIBase(PlayerNum aiPlayerNum, const LOCATION& initBaseLoc) 
{ 
	std::vector<Unit>buildings;
	LOCATION vechStartLoc(initBaseLoc.x + 4, initBaseLoc.y + 4);
	LOCATION commonOreLoc(225 + X_, 113 + Y_);
	MAP_RECT commonMiningIdleRect(commonOreLoc.x - 4, commonOreLoc.y, commonOreLoc.x + 6, commonOreLoc.y + 4);
	MAP_RECT buidlingIdleRect(initBaseLoc.x - 6, initBaseLoc.y, initBaseLoc.x + 8, initBaseLoc.y + 6);
	Unit unit;

	CreateAIBuilding(unit, mapCommandCenter, initBaseLoc, aiPlayerNum, mapNone, buildings);
	Unit structureFactory;
	CreateAIBuilding(structureFactory, map_id::mapStructureFactory, LOCATION(244 + X_ ,100 + Y_), aiPlayerNum, map_id::mapNone, buildings);

	CreateAIBuilding(unit, mapStandardLab, LOCATION(244 + X_, 105 + Y_), aiPlayerNum, map_id::mapNone, buildings);
	CreateAIBuilding(unit, mapReinforcedResidence, LOCATION(239 + X_, 100 + Y_), aiPlayerNum, map_id::mapNone, buildings);
	CreateAIBuilding(unit, mapReinforcedResidence, LOCATION(239 + X_, 103 + Y_), aiPlayerNum, map_id::mapNone, buildings);
	CreateAIBuilding(unit, mapMedicalCenter, LOCATION(236 + X_, 100 + Y_), aiPlayerNum, map_id::mapNone, buildings);
	CreateAIBuilding(unit, mapAgridome, LOCATION(235 + X_, 103 + Y_), aiPlayerNum, map_id::mapNone, buildings);
	CreateAIBuilding(unit, mapDIRT, LOCATION(248 + X_, 100 + Y_), aiPlayerNum, map_id::mapNone, buildings);
	CreateAIBuilding(unit, mapDIRT, LOCATION(248 + X_, 103 + Y_), aiPlayerNum, map_id::mapNone, buildings);
	CreateAIBuilding(unit, mapMHDGenerator, LOCATION(220 + X_, 101 + Y_), aiPlayerNum, map_id::mapNone, buildings);
	CreateAIBuilding(unit, mapMHDGenerator, LOCATION(224 + X_, 101 + Y_), aiPlayerNum, map_id::mapNone, buildings);

	Unit vehicleFactory;
	CreateAIBuilding(vehicleFactory, mapVehicleFactory, LOCATION(244 + X_, 112 + Y_), aiPlayerNum, map_id::mapNone, buildings);
	CreateAIBuilding(unit, mapVehicleFactory, LOCATION(239 + X_, 112 + Y_), aiPlayerNum, map_id::mapNone, buildings);

	Unit commonSmelter;
	CreateAIBuilding(commonSmelter, mapCommonOreSmelter,LOCATION(commonOreLoc.x + 4, commonOreLoc.y - 4), aiPlayerNum, map_id::mapNone, buildings);
	Unit secondCommonSmelter;
	CreateAIBuilding(commonSmelter, mapCommonOreSmelter, LOCATION(commonOreLoc.x - 1, commonOreLoc.y - 4), aiPlayerNum, map_id::mapNone, buildings);
	Unit commonMine;

	TethysGame::CreateBeacon(map_id::mapMiningBeacon, commonOreLoc.x, commonOreLoc.y, BeaconTypes::OreTypeCommon, Yield::Bar3, Variant::Variant3);
	CreateAIBuilding(commonMine, mapCommonOreMine, commonOreLoc, aiPlayerNum, map_id::mapNone, buildings);

	CreateGuardPostCluster(aiPlayerNum, LOCATION(243 + X_, 90 + Y_), buildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(235 + X_, 90 + Y_), buildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(227 + X_, 90 + Y_), buildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(219 + X_, 90 + Y_), buildings);

	CreateGuardPostCluster(aiPlayerNum, LOCATION(238 + X_, 121 + Y_), buildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(248 + X_, 121 + Y_), buildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(243 + X_, 116 + Y_), buildings);

	CreateTubeLine(LOCATION(244 + X_, 103 + Y_), LOCATION(244 + X_, 122 + Y_));
	CreateTubeLine(LOCATION(237 + X_, 110 + Y_), LOCATION(228 + X_, 110 + Y_));	

	MiningGroup miningGroup;
	SetupMiningGroup(miningGroup, commonMine, commonSmelter, commonMiningIdleRect, 3, aiPlayerNum);
}
