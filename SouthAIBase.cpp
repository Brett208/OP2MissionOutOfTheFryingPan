#include "SouthAIBase.h"
#include "AIHelper.h"
#include "AIPlayer.h"
#include "StrongBasesShared.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"

void BuildSouthAIBase(PlayerNum aiPlayerNum, const LOCATION& initBaseLoc)
{
	std::vector<Unit> defensiveVehicleFactories;
	std::vector<Unit> buildings;
	Unit unit;

	CreateGuardPosterClusters(aiPlayerNum, LOCATION(242 + X_, 135 + Y_), buildings);

	CreateAIBuilding(unit, mapCommandCenter, initBaseLoc, aiPlayerNum, buildings);

	Unit structureFactory;
	CreateAIBuilding(structureFactory, map_id::mapStructureFactory, LOCATION(242 + X_, 175 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapReinforcedResidence, LOCATION(237 + X_, 174 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapReinforcedResidence, LOCATION(237 + X_, 177 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapStandardLab, LOCATION(234 + X_, 171 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapMedicalCenter, LOCATION(234 + X_, 174 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapMedicalCenter, LOCATION(234 + X_, 177 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapAgridome, LOCATION(230 + X_, 174 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapAgridome, LOCATION(230 + X_, 177 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapDIRT, LOCATION(226 + X_, 174 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapDIRT, LOCATION(226 + X_, 177 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapNursery, LOCATION(223 + X_, 174 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapUniversity, LOCATION(223 + X_, 177 + Y_), aiPlayerNum, buildings);

	CreateAIBuilding(unit, mapMHDGenerator, LOCATION(252 + X_, 148 + Y_), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapMHDGenerator, LOCATION(252 + X_, 152 + Y_), aiPlayerNum, buildings);

	CreateAIBuilding(unit, mapAdvancedLab, LOCATION(initBaseLoc.x, 152 + Y_), aiPlayerNum, buildings);

	Unit vehicleFactory;
	CreateAIBuilding(vehicleFactory, mapVehicleFactory, LOCATION(250 + X_, initBaseLoc.y), aiPlayerNum, buildings);
	CreateAIBuilding(unit, mapVehicleFactory, LOCATION(250 + X_, initBaseLoc.y - 4), aiPlayerNum, buildings);
	defensiveVehicleFactories.push_back(unit);

	CreateCommonMineGroup3Bar(LOCATION(247 + X_, 188 + Y_), aiPlayerNum, buildings);

	CreateRareMineGroup3Bar(LOCATION(251 + X_, 175 + Y_), aiPlayerNum, buildings);
	LOCATION tubeStartLoc = buildings[buildings.size() - 2].Location() - LOCATION(3, 0);
	CreateTubeLine(tubeStartLoc, tubeStartLoc - LOCATION(4, 0));

	CreateGuardPostCluster(aiPlayerNum, LOCATION(210 + X_, 181 + Y_), buildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(216 + X_, 185 + Y_), buildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(222 + X_, 189 + Y_), buildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(228 + X_, 193 + Y_), buildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(234 + X_, 197 + Y_), buildings);

	CreateGuardPostCluster(aiPlayerNum, LOCATION(initBaseLoc.x - 5, initBaseLoc.y - 2), buildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(initBaseLoc.x, initBaseLoc.y + 2), buildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(initBaseLoc.x, initBaseLoc.y - 6), buildings);

	CreateTubeLine(LOCATION(initBaseLoc.x, initBaseLoc.y - 2), LOCATION(initBaseLoc.x, 155 + Y_));
	CreateTubeLine(LOCATION(initBaseLoc.x, initBaseLoc.y + 1), LOCATION(initBaseLoc.x, 173 + Y_));

	CreateTubeLine(LOCATION(initBaseLoc.x, 175 + Y_), LOCATION(initBaseLoc.x, 183 + Y_));

	CreateTubeLine(LOCATION(initBaseLoc.x + 2, initBaseLoc.y), LOCATION(247 + X_, initBaseLoc.y));

	BuildingGroup buildingGroup;
	SetupBuildingGroup(buildingGroup, structureFactory, vehicleFactory, buildings, aiPlayerNum);

	MAP_RECT defensiveRectPerimeter({ 189 + X_, 181 + Y_ }, { 205 + X_, 217 + Y_ });
	MAP_RECT defensiveRectInBase({ 218 + X_, 143 + Y_ }, { 256 + X_, 192 + Y_ });
	SetupDefensiveFightGroups(aiPlayerNum, defensiveVehicleFactories, defensiveRectPerimeter, defensiveRectInBase);
}

void CreateGuardPosterClusters(PlayerNum aiPlayerNum, const LOCATION center, std::vector<Unit>& southBuildings)
{
	CreateGuardPostCluster(aiPlayerNum, LOCATION(center.x, center.y), southBuildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(center.x + 6, center.y), southBuildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(center.x - 6, center.y), southBuildings);
	CreateGuardPostCluster(aiPlayerNum, LOCATION(center.x - 12, center.y), southBuildings);
}
