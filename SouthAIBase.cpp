#include "SouthAIBase.h"
#include "AIHelper.h"
#include "AIPlayer.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include <vector>

std::vector<Unit>southBuildings;

void BuildSouthAIBase(PlayerNum aiPlayerNum, const LOCATION& initBaseLoc)
{
	/*LOCATION vechStartLoc(initBaseLoc.x + 4, initBaseLoc.y + 4);
	LOCATION commonOreLoc(225 + X_, 113 + Y_);
	MAP_RECT miningIdleRect(commonOreLoc.x - 4, commonOreLoc.y, commonOreLoc.x + 6, commonOreLoc.y + 4);
	MAP_RECT buidlingIdleRect(initBaseLoc.x - 6, initBaseLoc.y, initBaseLoc.x + 8, initBaseLoc.y + 6);
	Unit unit;*/

	BuildGuardPosterCluster(aiPlayerNum, LOCATION(246 + X_, 133 + Y_));

	/*CreateAIBuilding(unit, mapCommandCenter, initBaseLoc, aiPlayerNum, mapNone, southBuildings);
	Unit structureFactory;
	CreateAIBuilding(structureFactory, map_id::mapStructureFactory, LOCATION(244 + X_, 100 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);

	CreateAIBuilding(unit, mapStandardLab, LOCATION(244 + X_, 105 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(unit, mapAdvancedResidence, LOCATION(239 + X_, 100 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(unit, mapAdvancedResidence, LOCATION(239 + X_, 104 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(unit, mapMedicalCenter, LOCATION(236 + X_, 100 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(unit, mapAgridome, LOCATION(235 + X_, 103 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(unit, mapDIRT, LOCATION(248 + X_, 100 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(unit, mapDIRT, LOCATION(248 + X_, 103 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(unit, mapMHDGenerator, LOCATION(220 + X_, 101 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(unit, mapMHDGenerator, LOCATION(224 + X_, 101 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);

	Unit vehicleFactory;
	CreateAIBuilding(vehicleFactory, mapVehicleFactory, LOCATION(244 + X_, 112 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(unit, mapVehicleFactory, LOCATION(239 + X_, 112 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);

	Unit commonSmelter;
	CreateAIBuilding(commonSmelter, mapCommonOreSmelter, LOCATION(commonOreLoc.x + 4, commonOreLoc.y - 4), aiPlayerNum, map_id::mapNone, southBuildings);
	Unit secondCommonSmelter;
	CreateAIBuilding(commonSmelter, mapCommonOreSmelter, LOCATION(commonOreLoc.x - 1, commonOreLoc.y - 4), aiPlayerNum, map_id::mapNone, southBuildings);
	Unit commonMine;

	TethysGame::CreateBeacon(map_id::mapMiningBeacon, commonOreLoc.x, commonOreLoc.y, BeaconTypes::OreTypeCommon, Yield::Bar3, Variant::Variant3);
	CreateAIBuilding(commonMine, mapCommonOreMine, commonOreLoc, aiPlayerNum, map_id::mapNone, southBuildings);

	createGuardPostCluster(aiPlayerNum, LOCATION(251 + X_, 90 + Y_), southBuildings);
	createGuardPostCluster(aiPlayerNum, LOCATION(243 + X_, 90 + Y_), southBuildings);
	createGuardPostCluster(aiPlayerNum, LOCATION(235 + X_, 90 + Y_), southBuildings);
	createGuardPostCluster(aiPlayerNum, LOCATION(227 + X_, 90 + Y_), southBuildings);

	createGuardPostCluster(aiPlayerNum, LOCATION(238 + X_, 121 + Y_), southBuildings);
	createGuardPostCluster(aiPlayerNum, LOCATION(248 + X_, 121 + Y_), southBuildings);
	createGuardPostCluster(aiPlayerNum, LOCATION(243 + X_, 116 + Y_), southBuildings);

	CreateTubeLine(LOCATION(244 + X_, 103 + Y_), LOCATION(244 + X_, 122 + Y_));
	CreateTubeLine(LOCATION(237 + X_, 110 + Y_), LOCATION(228 + X_, 110 + Y_));

	MiningGroup miningGroup;
	SetupMiningGroup(miningGroup, commonMine, commonSmelter, miningIdleRect, 3, aiPlayerNum);*/
}

void BuildGuardPosterCluster(PlayerNum aiPlayerNum, const LOCATION center)
{
	createGuardPostCluster(aiPlayerNum, LOCATION(center.x, center.y), southBuildings);
	createGuardPostCluster(aiPlayerNum, LOCATION(center.x + 6, center.y), southBuildings);
	createGuardPostCluster(aiPlayerNum, LOCATION(center.x - 6, center.y), southBuildings);
	createGuardPostCluster(aiPlayerNum, LOCATION(center.x - 12, center.y), southBuildings);
}