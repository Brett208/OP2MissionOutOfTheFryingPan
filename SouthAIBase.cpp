#include "SouthAIBase.h"
#include "AIHelper.h"
#include "AIPlayer.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"

void BuildSouthAIBase(PlayerNum aiPlayerNum, const LOCATION& initBaseLoc)
{
	std::vector<Unit>southBuildings;
	LOCATION vechStartLoc(initBaseLoc.x + 4, initBaseLoc.y + 4);
	LOCATION commonOreLoc(247 + X_, 189 + Y_);
	MAP_RECT commonMiningIdleRect(commonOreLoc.x - 4, commonOreLoc.y, commonOreLoc.x + 6, commonOreLoc.y + 4);
	MAP_RECT buidlingIdleRect(initBaseLoc.x - 10, initBaseLoc.y - 7, initBaseLoc.x - 1, initBaseLoc.y - 3);
	Unit unit;

	CreateGuardPosterClusters(aiPlayerNum, LOCATION(242 + X_, 135 + Y_), southBuildings);

	CreateAIBuilding(unit, mapCommandCenter, initBaseLoc, aiPlayerNum, mapNone, southBuildings);

	Unit structureFactory;
	CreateAIBuilding(structureFactory, map_id::mapStructureFactory, LOCATION(242 + X_, 175 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(unit, mapReinforcedResidence, LOCATION(237 + X_, 174 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(unit, mapReinforcedResidence, LOCATION(237 + X_, 177 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(unit, mapMedicalCenter, LOCATION(234 + X_, 174 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(unit, mapMedicalCenter, LOCATION(234 + X_, 177 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(unit, mapAgridome, LOCATION(230 + X_, 174 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(unit, mapAgridome, LOCATION(230 + X_, 177 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(unit, mapDIRT, LOCATION(226 + X_, 174 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(unit, mapDIRT, LOCATION(226 + X_, 177 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);

	CreateAIBuilding(unit, mapMHDGenerator, LOCATION(252 + X_, 148 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(unit, mapMHDGenerator, LOCATION(252 + X_, 152 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);

	CreateAIBuilding(unit, mapAdvancedLab, LOCATION(initBaseLoc.x, 152 + Y_), aiPlayerNum, map_id::mapNone, southBuildings);

	Unit vehicleFactory;
	Unit defensiveVehicleFactory;
	CreateAIBuilding(vehicleFactory, mapVehicleFactory, LOCATION(250 + X_, initBaseLoc.y), aiPlayerNum, map_id::mapNone, southBuildings);
	CreateAIBuilding(defensiveVehicleFactory, mapVehicleFactory, LOCATION(250 + X_, initBaseLoc.y - 4), aiPlayerNum, map_id::mapNone, southBuildings);

	Unit commonSmelter;
	CreateAIBuilding(commonSmelter, mapCommonOreSmelter, LOCATION(commonOreLoc.x + 2, commonOreLoc.y - 4), aiPlayerNum, map_id::mapNone, southBuildings);
	Unit secondCommonSmelter;
	CreateAIBuilding(secondCommonSmelter, mapCommonOreSmelter, LOCATION(commonOreLoc.x - 3, commonOreLoc.y - 4), aiPlayerNum, map_id::mapNone, southBuildings);
	Unit commonMine;

	TethysGame::CreateBeacon(map_id::mapMiningBeacon, commonOreLoc.x, commonOreLoc.y, BeaconTypes::OreTypeCommon, Yield::Bar3, Variant::Variant3);
	CreateAIBuilding(commonMine, mapCommonOreMine, commonOreLoc, aiPlayerNum, map_id::mapNone, southBuildings);

	CreateGuardPostCluster(aiPlayerNum, LOCATION(214 + X_, 181 + Y_), southBuildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(220 + X_, 185 + Y_), southBuildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(226 + X_, 189 + Y_), southBuildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(232 + X_, 193 + Y_), southBuildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(238 + X_, 197 + Y_), southBuildings);

	CreateGuardPostCluster(aiPlayerNum, LOCATION(initBaseLoc.x - 5, initBaseLoc.y - 2), southBuildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(initBaseLoc.x, initBaseLoc.y + 2), southBuildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(initBaseLoc.x, initBaseLoc.y - 6), southBuildings);

	CreateTubeLine(LOCATION(initBaseLoc.x, initBaseLoc.y - 2), LOCATION(initBaseLoc.x, 155 + Y_));
	CreateTubeLine(LOCATION(initBaseLoc.x, initBaseLoc.y + 1), LOCATION(initBaseLoc.x, 173 + Y_));

	CreateTubeLine(LOCATION(initBaseLoc.x, 175 + Y_), LOCATION(initBaseLoc.x, 183 + Y_));

	CreateTubeLine(LOCATION(initBaseLoc.x + 2, initBaseLoc.y), LOCATION(247 + X_, initBaseLoc.y));

	MiningGroup miningGroup;
	SetupMiningGroup(miningGroup, commonMine, commonSmelter, commonMiningIdleRect, 2, aiPlayerNum);
	SetupMiningGroup(miningGroup, commonMine, secondCommonSmelter, commonMiningIdleRect, 2, aiPlayerNum);
}

void CreateGuardPosterClusters(PlayerNum aiPlayerNum, const LOCATION center, std::vector<Unit>& southBuildings)
{
	CreateGuardPostCluster(aiPlayerNum, LOCATION(center.x, center.y), southBuildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(center.x + 6, center.y), southBuildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(center.x - 6, center.y), southBuildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(center.x - 12, center.y), southBuildings);
}
