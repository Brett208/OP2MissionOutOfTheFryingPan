#include "NorthAIBase.h"
#include "AIBaseShared.h"
#include "DefensiveFightGroup.h"
#include "AIHelper.h"
#include "AIPlayer.h"
#include "StrongBasesShared.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include <vector>


void BuildNorthAIBase(PlayerNum aiPlayerNum, const LOCATION& initBaseLoc)
{
	std::vector<Unit> defensiveVehicleFactories;
	std::vector<Unit> buildings;
	Unit unit;

	CreateAIBuilding(unit, mapCommandCenter, initBaseLoc, aiPlayerNum, buildings);
	Unit structureFactory;
	CreateAIBuilding(structureFactory, map_id::mapStructureFactory, LOCATION(244 + X_, 100 + Y_), aiPlayerNum, buildings);

	CreateAIBuilding(unit, mapReinforcedResidence, LOCATION(239 + X_, 100 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapReinforcedResidence, LOCATION(239 + X_, 103 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapNursery, LOCATION(248 + X_, 100 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapUniversity, LOCATION(248 + X_, 103 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapStandardLab, LOCATION(248 + X_, 97 + Y_), aiPlayerNum, buildings);

	CreateAIBuilding(unit, mapMHDGenerator, LOCATION(220 + X_, 101 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapMHDGenerator, LOCATION(224 + X_, 101 + Y_), aiPlayerNum,  buildings);
	CreateAIBuilding(unit, mapMHDGenerator, LOCATION(228 + X_, 101 + Y_), aiPlayerNum, buildings);

	Unit vehicleFactory;
	CreateAIBuilding(vehicleFactory, mapVehicleFactory, LOCATION(244 + X_, 112 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapVehicleFactory, LOCATION(239 + X_, 112 + Y_), aiPlayerNum, buildings);
	defensiveVehicleFactories.push_back(unit);

	CreateTubeLine(LOCATION(241 + X_, 112 + Y_), LOCATION(252 + X_, 112+ Y_));
	CreateAIBuilding(unit, mapAdvancedLab, LOCATION(253 + X_, 112 + Y_), aiPlayerNum, buildings);

	BuildingGroup buildingGroup;
	SetupBuildingGroup(buildingGroup, structureFactory, vehicleFactory, buildings, aiPlayerNum, BuildingGroupOptions{ 1, 2 });

	RecordTubeLine(buildingGroup, LOCATION(219 + X_, 94 + Y_), LOCATION(243 + X_, 98 + Y_));

	buildingGroup.RecordBuilding(LOCATION(251 + X_, 100 + Y_), mapDIRT, mapNone);
	buildingGroup.RecordBuilding(LOCATION(235 + X_, 103 + Y_), mapAgridome, mapNone);
	buildingGroup.RecordBuilding(LOCATION(251 + X_, 103 + Y_), mapDIRT, mapNone);
	buildingGroup.RecordBuilding(LOCATION(236 + X_, 100 + Y_), mapMedicalCenter, mapNone);

	CreateCommonMineGroup3Bar(LOCATION(225 + X_, 112 + Y_), aiPlayerNum, buildings);

	CreateRareMineGroup3Bar(LOCATION(225 + X_, 123 + Y_), aiPlayerNum, buildings);
	LOCATION tubeStart = LOCATION(buildings.back().Location() + LOCATION(3, 0));
	CreateTubeLine(tubeStart, tubeStart + LOCATION(11, 0));

	CreatePlymouthGuardPostCluster(LOCATION(243 + X_, 90 + Y_), buildings);
	CreatePlymouthGuardPostCluster(LOCATION(235 + X_, 90 + Y_), buildings);
	CreatePlymouthGuardPostCluster(LOCATION(227 + X_, 90 + Y_), buildings);
	CreatePlymouthGuardPostCluster(LOCATION(219 + X_, 90 + Y_), buildings);

	CreatePlymouthGuardPostCluster(LOCATION(238 + X_, 121 + Y_), buildings);
	CreatePlymouthGuardPostCluster(LOCATION(248 + X_, 121 + Y_), buildings);
	CreatePlymouthGuardPostCluster(LOCATION(243 + X_, 116 + Y_), buildings);
	CreatePlymouthGuardPostCluster(LOCATION(243 + X_, 124 + Y_), buildings);

	TethysGame::CreateWallOrTube(242 + X_, 122 + Y_, 0, map_id::mapTube);
	TethysGame::CreateWallOrTube(247 + X_, 122 + Y_, 0, map_id::mapTube);

	CreateTubeLine(LOCATION(244 + X_, 103 + Y_), LOCATION(244 + X_, 122 + Y_));
	CreateTubeLine(LOCATION(237 + X_, 110 + Y_), LOCATION(228 + X_, 110 + Y_));

	MAP_RECT defensiveRectPerimeter({ 214 + X_, 78 + Y_ }, { 235 + X_, 91 + Y_ });
	MAP_RECT defensiveRectInBase({ 217 + X_, 96 + Y_ }, { 255 + X_, 131 + Y_ });
	SetupDefensiveFightGroups(aiPlayerNum, defensiveVehicleFactories, defensiveRectPerimeter, defensiveRectInBase);
}
