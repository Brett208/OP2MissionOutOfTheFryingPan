#include "OffensiveFightGroup.h"

void OffensiveFightGroup::Initialize(MAP_RECT guardedRect, std::vector<Unit> vehicleFactories, const std::vector<TargetTankCount>& targetTankCounts)
{
	FightGroupOverlay::Initialize(guardedRect, vehicleFactories);
	SetTankCounts(targetTankCounts);
}

void OffensiveFightGroup::CreateTank(map_id type, map_id turret)
{
	if (GetFightGroupCount() == targetCount) {
		return;
	}
	
	auto& vehicleFactory = vehicleFactories[TethysGame::GetRand(vehicleFactories.size())];

	if (vehicleFactory.IsLive() && !vehicleFactory.isEMPed()) {
		Unit tank;
		TethysGame::CreateUnit(tank, type, vehicleFactory.Location(), aiPlayerNum, turret, 0);
		tank.DoSetLights(true);

		GetFightGroup().TakeUnit(tank);
	}
}

void OffensiveFightGroup::Attack(const std::vector<TargetTankCount>& targetCounts)
{
	TaskFightGroup(GetFightGroup());
	Initialize(GetGuardedRect(), vehicleFactories, targetCounts);
}

void OffensiveFightGroup::TaskFightGroup(FightGroup& fightGroup)
{
	int choice = TethysGame::GetRand(4);

	switch (choice)
	{
	case 0: // General Attack
		BasicAttack();
		return;
	case 1: // Attack Command Center / Structure Factory / Vehicle Factory
		AttackBuilding(fightGroup, std::vector<map_id>{ map_id::mapCommandCenter, mapStructureFactory, mapVehicleFactory });
		return;
	case 2: // Attack MiningBuilding
		AttackBuilding(fightGroup, std::vector<map_id>{ 
			mapCommonOreSmelter, mapRareOreSmelter, mapCommonOreMine, mapRareOreMine});
		return;
	case 3: // Spaceport / Advanced Lab
		AttackBuilding(fightGroup, std::vector<map_id> { mapSpaceport, mapAdvancedLab});
		return;
	}
}

void OffensiveFightGroup::AttackBuilding(FightGroup& fightGroup, const std::vector<map_id>& buildingTypes)
{
	//TODO: Create a list of which target regions contain viable targets
	// A viable region includes (a CC, a Structure Factory, a mine, or a Smelter)

	// Check if no viable regions exist, if not, pass the entire MAP_RECT in to search (this ensures that if somehow the player is building outside the target regions, or is in process of transferring base, a valid attack still occur
		// Also, if no target regions are presented, then just pass the entire MAP_RECT in.
	// Then, starting with the first viable region, use a 70% weight to choose it for targetting, passing on to the next region if the weight fails
	// If the final region fails as a viable weight, target the first viable region.

	std::vector<Unit> buildings;
	GetHumanBuildings(buildings, buildingTypes, MAP_RECT(LOCATION(0 + X_, 0 + Y_), LOCATION(GameMapEx::GetMapWidth(), GameMapEx::GetMapHeight())));

	if (buildings.empty())
	{
		BasicAttack();
		return;
	}

	Unit building = buildings[TethysGame::GetRand(buildings.size())];

	MAP_RECT mapRect(
		building.Location().x - 5, building.Location().y - 5,
		building.Location().x + 5, building.Location().y + 5
	);
	fightGroup.SetRect(mapRect);

	fightGroupsWithTarget.push_back(FightGroupTarget{ fightGroup, building });
}

void OffensiveFightGroup::GetHumanBuildings(std::vector<Unit>& buildingsOut, const std::vector<map_id>& buildingTypes, MAP_RECT& region)
{
	for (map_id buildingType : buildingTypes) {
		GetHumanBuildings(buildingsOut, buildingType, region);
	}
}

void OffensiveFightGroup::GetHumanBuildings(std::vector<Unit>& buildingsOut, map_id buildingType, MAP_RECT& region)
{
	Unit building;
	for (std::size_t i = 0; i < humanPlayerCount; ++i)
	{
		PlayerBuildingEnum playerBuildingEnum(i, buildingType);

		while (playerBuildingEnum.GetNext(building))
		{
			if(region.Check(building.Location()))
			{
				buildingsOut.push_back(building);
			}
		}
	}
}

void OffensiveFightGroup::UpdateTaskedFightGroups()
{
	for (int i = fightGroupsWithTarget.size(); i-- > 0; ) {
		if (!fightGroupsWithTarget[i].building.IsLive()) {
			FightGroupTarget fightGroupTarget = fightGroupsWithTarget[i];
			fightGroupsWithTarget.erase(fightGroupsWithTarget.begin() + i);
			TaskFightGroup(fightGroupTarget.fightGroup);
		}
	}
}

void OffensiveFightGroup::SetTargetRegions(const std::vector<TargetRegion>& targetRegions)
{
	this->targetRegions = targetRegions;
}
