#include "SouthAIBase.h"
#include "AIBaseShared.h"
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

	CreateMiddleGuardPostClusters(LOCATION(242 + X_, 135 + Y_), buildings);

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

	CreateAIBuilding(unit, mapMHDGenerator, LOCATION(252 + X_, 144 + Y_), aiPlayerNum, buildings);
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

	CreatePlymouthGuardPostCluster(LOCATION(210 + X_, 181 + Y_), buildings);
	CreatePlymouthGuardPostCluster(LOCATION(216 + X_, 185 + Y_), buildings);
	CreatePlymouthGuardPostCluster(LOCATION(222 + X_, 189 + Y_), buildings);
	CreatePlymouthGuardPostCluster(LOCATION(228 + X_, 193 + Y_), buildings);
	CreatePlymouthGuardPostCluster(LOCATION(234 + X_, 197 + Y_), buildings);
	CreatePlymouthGuardPostCluster(LOCATION(239 + X_, 202 + Y_), buildings);
	CreatePlymouthGuardPostCluster(LOCATION(initBaseLoc.x - 5, initBaseLoc.y - 2), buildings);
	CreatePlymouthGuardPostCluster(LOCATION(initBaseLoc.x, initBaseLoc.y + 2), buildings);
	CreatePlymouthGuardPostCluster(LOCATION(initBaseLoc.x, initBaseLoc.y - 6), buildings);

	CreateTubeLine(LOCATION(initBaseLoc.x, initBaseLoc.y - 2), LOCATION(initBaseLoc.x, 155 + Y_));
	CreateTubeLine(LOCATION(initBaseLoc.x, initBaseLoc.y + 1), LOCATION(initBaseLoc.x, 173 + Y_));

	CreateTubeLine(LOCATION(initBaseLoc.x, 175 + Y_), LOCATION(initBaseLoc.x, 183 + Y_));

	CreateTubeLine(LOCATION(initBaseLoc.x + 2, initBaseLoc.y), LOCATION(247 + X_, initBaseLoc.y));

	BuildingGroup buildingGroup;
	SetupBuildingGroup(buildingGroup, structureFactory, vehicleFactory, buildings, aiPlayerNum, BuildingGroupOptions{ 1, 2 });

	RecordTubeLine(buildingGroup, LOCATION(241 + X_, 183 + Y_), LOCATION(241 + X_, 202 + Y_));
	RecordTubeLine(buildingGroup, LOCATION(235 + X_, 196 + Y_), LOCATION(241 + X_, 196 + Y_));
	RecordTubeLine(buildingGroup, LOCATION(229 + X_, 192 + Y_), LOCATION(235 + X_, 195 + Y_));
	RecordTubeLine(buildingGroup, LOCATION(223 + X_, 188 + Y_), LOCATION(229 + X_, 191 + Y_));
	RecordTubeLine(buildingGroup, LOCATION(217 + X_, 184 + Y_), LOCATION(223 + X_, 187 + Y_));
	RecordTubeLine(buildingGroup, LOCATION(211 + X_, 180 + Y_), LOCATION(217 + X_, 185 + Y_));
	RecordTubeLine(buildingGroup, LOCATION(217 + X_, 179 + Y_), LOCATION(223 + X_, 179 + Y_));

	MAP_RECT defensiveRectPerimeter({ 189 + X_, 181 + Y_ }, { 205 + X_, 217 + Y_ });
	MAP_RECT defensiveRectInBase({ 218 + X_, 143 + Y_ }, { 256 + X_, 192 + Y_ });
	SetupDefensiveFightGroups(aiPlayerNum, defensiveVehicleFactories, defensiveRectPerimeter, defensiveRectInBase);
}

void CreateMiddleGuardPostClusters(const LOCATION& center, std::vector<Unit>& southBuildings)
{
	CreatePlymouthGuardPostCluster(LOCATION(center.x, center.y), southBuildings);
	CreatePlymouthGuardPostCluster(LOCATION(center.x + 6, center.y), southBuildings);
	CreatePlymouthGuardPostCluster(LOCATION(center.x - 6, center.y), southBuildings);
	CreatePlymouthGuardPostCluster(LOCATION(center.x - 12, center.y), southBuildings);
}
