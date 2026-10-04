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
	case 2: // Attack Mining Building
		AttackBuilding(fightGroup, std::vector<map_id>{ 
			mapCommonOreSmelter, mapRareOreSmelter, mapCommonOreMine, mapRareOreMine});
		return;
	case 3: // Spaceport / Advanced Lab
		AttackBuilding(fightGroup, std::vector<map_id> { mapSpaceport, mapAdvancedLab});
		return;
	}
}

std::vector<TargetRegion> OffensiveFightGroup::GetPossibleTargetRegions(const std::vector<TargetRegion> targetRegionList)
{
	std::vector<TargetRegion> viableTargetRegions;
	std::vector<Unit> buildings;

	if (!targetRegionList.empty())
	{
		for (TargetRegion targetRegion : targetRegionList)
		{
			GetHumanBuildings(buildings, std::vector<map_id>{ mapCommandCenter, mapStructureFactory, mapCommonOreMine, mapRareOreMine, mapCommonOreSmelter, mapRareOreSmelter }, targetRegion.area);

			if (!buildings.empty())
			{
				viableTargetRegions.push_back(targetRegion);
				buildings.clear();
			}
		}
	}
	return viableTargetRegions;
}

std::vector<Unit> OffensiveFightGroup::SelectTargetBuildings(const std::vector<TargetRegion> possibleTargetRegions, const std::vector<map_id> buildingTypes)
{
	std::vector<Unit> buildings;

	if (possibleTargetRegions.empty())
	{
		GetHumanBuildings(buildings, buildingTypes, MAP_RECT(LOCATION(0 + X_, 0 + Y_), LOCATION(GameMapEx::GetMapWidth(), GameMapEx::GetMapHeight())));
	}
	else
	{
		for (TargetRegion targetRegion : possibleTargetRegions)
		{
			GetHumanBuildings(buildings, buildingTypes, targetRegion.area);
			if (!buildings.empty())
			{
				if (TethysGame::GetRand(100) < 70)
				{
					return buildings;
				}
				else
				{
					buildings.clear();
				}
			}
		}
	}
}

void OffensiveFightGroup::AttackBuilding(FightGroup& fightGroup, const std::vector<map_id>& buildingTypes)
{
	std::vector<TargetRegion> viableTargetRegions = GetPossibleTargetRegions(targetRegions);
	std::vector<Unit> buildings = SelectTargetBuildings(viableTargetRegions, buildingTypes);

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
