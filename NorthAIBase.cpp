#include "NorthAIBase.h"
#include "AIHelper.h"
#include "AIPlayer.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include <vector>

void BuildNorthAIBase(PlayerNum aiPlayerNum, const LOCATION& initBaseLoc) 
{ 
	std::vector<Unit> buildings;
	Unit unit;

	CreateAIBuilding(unit, mapCommandCenter, initBaseLoc, aiPlayerNum, buildings);
	Unit structureFactory;
	CreateAIBuilding(structureFactory, map_id::mapStructureFactory, LOCATION(244 + X_, 100 + Y_), aiPlayerNum, buildings);

	CreateAIBuilding(unit, mapStandardLab, LOCATION(244 + X_, 105 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapReinforcedResidence, LOCATION(239 + X_, 100 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapReinforcedResidence, LOCATION(239 + X_, 103 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapMedicalCenter, LOCATION(236 + X_, 100 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapAgridome, LOCATION(235 + X_, 103 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapDIRT, LOCATION(248 + X_, 100 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapDIRT, LOCATION(248 + X_, 103 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapNursery, LOCATION(252 + X_, 100 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapUniversity, LOCATION(252 + X_, 103 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapMHDGenerator, LOCATION(220 + X_, 101 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapMHDGenerator, LOCATION(224 + X_, 101 + Y_), aiPlayerNum,  buildings);

	Unit vehicleFactory;
	CreateAIBuilding(vehicleFactory, mapVehicleFactory, LOCATION(244 + X_, 112 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapVehicleFactory, LOCATION(239 + X_, 112 + Y_), aiPlayerNum, buildings);

	CreateCommonMineGroup3Bar(LOCATION(225 + X_, 112 + Y_), aiPlayerNum, buildings);

	CreateRareMineGroup3Bar(LOCATION(225 + X_, 123 + Y_), aiPlayerNum, buildings);
	LOCATION tubeStart = LOCATION(buildings.back().Location() + LOCATION(3, 0));
	CreateTubeLine(tubeStart, tubeStart + LOCATION(11, 0));

	CreateGuardPostCluster(aiPlayerNum, LOCATION(243 + X_, 90 + Y_), buildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(235 + X_, 90 + Y_), buildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(227 + X_, 90 + Y_), buildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(219 + X_, 90 + Y_), buildings);

	CreateGuardPostCluster(aiPlayerNum, LOCATION(238 + X_, 121 + Y_), buildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(248 + X_, 121 + Y_), buildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(243 + X_, 116 + Y_), buildings);

	TethysGame::CreateWallOrTube(242 + X_, 122 + Y_, 0, map_id::mapTube);
	TethysGame::CreateWallOrTube(247 + X_, 122 + Y_, 0, map_id::mapTube);

	CreateTubeLine(LOCATION(244 + X_, 103 + Y_), LOCATION(244 + X_, 122 + Y_));
	CreateTubeLine(LOCATION(237 + X_, 110 + Y_), LOCATION(228 + X_, 110 + Y_));

	BuildingGroup buildingGroup;
	SetupBuildingGroup(buildingGroup, structureFactory, vehicleFactory, buildings, aiPlayerNum);
}
