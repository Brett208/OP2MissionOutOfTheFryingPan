#include "NorthAIBase.h"
#include "AIHelper.h"
#include "AIPlayer.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include <vector>

std::vector<Unit>buildings;

void BuildNorthAIBase(PlayerNum aiPlayerNum, const LOCATION& initBaseLoc) 
{ 
	LOCATION vechStartLoc(initBaseLoc.x + 4, initBaseLoc.y + 4);
	MAP_RECT miningIdleRect(initBaseLoc.x - 4, initBaseLoc.y, initBaseLoc.x + 6, initBaseLoc.y + 4);
	MAP_RECT buidlingIdleRect(initBaseLoc.x - 6, initBaseLoc.y, initBaseLoc.x + 8, initBaseLoc.y + 6);
	Unit unit;

	CreateAIBuilding(unit, mapCommandCenter, initBaseLoc, aiPlayerNum, mapNone, buildings);
	Unit structureFactory;
	CreateAIBuilding(structureFactory, map_id::mapStructureFactory, LOCATION(244 + X_ ,100 + Y_), aiPlayerNum, map_id::mapNone, buildings);

	CreateAIBuilding(unit, mapStandardLab, LOCATION(244 + X_, 105 + Y_), aiPlayerNum, map_id::mapNone, buildings);
	CreateAIBuilding(unit, mapAdvancedResidence, LOCATION(239 + X_, 100 + Y_), aiPlayerNum, map_id::mapNone, buildings);
	CreateAIBuilding(unit, mapAdvancedResidence, LOCATION(239 + X_, 104 + Y_), aiPlayerNum, map_id::mapNone, buildings);
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
	CreateAIBuilding(commonSmelter, mapCommonOreSmelter, LOCATION(221 + X_, 109 + Y_), aiPlayerNum, map_id::mapNone, buildings);
	Unit secondCommonSmelter;
	CreateAIBuilding(commonSmelter, mapCommonOreSmelter, LOCATION(226 + X_, 109 + Y_), aiPlayerNum, map_id::mapNone, buildings);
	Unit commonMine;
	LOCATION commonOreLoc(225 + X_, 113 + Y_);
	TethysGame::CreateBeacon(map_id::mapMiningBeacon, commonOreLoc.x, commonOreLoc.y, BeaconTypes::OreTypeCommon, Yield::Bar3, Variant::Variant3);
	CreateAIBuilding(commonMine, mapCommonOreMine, commonOreLoc, aiPlayerNum, map_id::mapNone, buildings);

	createGuardPostCluster(aiPlayerNum, LOCATION(251 + X_, 90 + Y_), buildings);
	createGuardPostCluster(aiPlayerNum, LOCATION(243 + X_, 90 + Y_), buildings);
	createGuardPostCluster(aiPlayerNum, LOCATION(235 + X_, 90 + Y_), buildings);
	createGuardPostCluster(aiPlayerNum, LOCATION(227 + X_, 90 + Y_), buildings);

	createGuardPostCluster(aiPlayerNum, LOCATION(238 + X_, 121 + Y_), buildings);
	createGuardPostCluster(aiPlayerNum, LOCATION(248 + X_, 121 + Y_), buildings);
	createGuardPostCluster(aiPlayerNum, LOCATION(243 + X_, 116 + Y_), buildings);

	CreateTubeLine(LOCATION(244 + X_, 103 + Y_), LOCATION(244 + X_, 122 + Y_));
	CreateTubeLine(LOCATION(237 + X_, 110 + Y_), LOCATION(228 + X_, 110 + Y_));	
}