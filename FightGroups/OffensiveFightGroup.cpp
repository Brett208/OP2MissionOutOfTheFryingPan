#include "OffensiveFightGroup.h"
#include "../MapRectEx.h"

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

		TakeUnit(tank);
	}
}

void OffensiveFightGroup::Attack(const std::vector<TargetTankCount>& targetCounts)
{
	TaskFightGroup(*this);
	Initialize(GetGuardedRect(), vehicleFactories, targetCounts);
}

void OffensiveFightGroup::TaskFightGroup(FightGroupOverlay& group)
{
	int choice = TethysGame::GetRand(4);

	switch (choice)
	{
	case 0: // General Attack
		group.BasicAttack();
		return;
	case 1: // Attack Command Center / Structure Factory / Vehicle Factory
		AttackBuilding(group, std::vector<map_id>{ map_id::mapCommandCenter, mapStructureFactory, mapVehicleFactory });
		return;
	case 2: // Attack Mining Building
		AttackBuilding(group, std::vector<map_id>{
			mapCommonOreSmelter, mapRareOreSmelter, mapCommonOreMine, mapRareOreMine});
		return;
	case 3: // Spaceport / Advanced Lab
		AttackBuilding(group, std::vector<map_id> { mapSpaceport, mapAdvancedLab});
		return;
	}
}

std::vector<TargetRegion> OffensiveFightGroup::GetPossibleTargetRegions(const std::vector<TargetRegion>& targetRegionList)
{
	std::vector<TargetRegion> viableTargetRegions;
	std::vector<Unit> buildings;

	if (!targetRegionList.empty())
	{
		for (const TargetRegion& targetRegion : targetRegionList)
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

bool OffensiveFightGroup::SkipRegion(const TargetRegion& region, const std::vector<map_id>& buildingTypes)
{
	std::vector<Unit> buildings;

	GetHumanBuildings(buildings, buildingTypes, region.area);
	if (!buildings.empty())
	{
		return TethysGame::GetRand(100) <= 25;
	}
	return false;
}

TargetRegion OffensiveFightGroup::GetTargetRegion(const std::vector<TargetRegion>& possibleTargetRegions, const std::vector<map_id>& targetBuildingTypes)
{
	if (possibleTargetRegions.empty())
	{
		return TargetRegion{ MapEx::GetFullRect() };
	}
	else
	{
		for (const TargetRegion& targetRegion : possibleTargetRegions)
		{
			if (!SkipRegion(targetRegion, targetBuildingTypes))
			{
				return targetRegion;
			}
		}
		return possibleTargetRegions.back();
	}
	return TargetRegion{ MapEx::GetFullRect() };
}

std::vector<Unit> OffensiveFightGroup::SelectTargetBuildings(const TargetRegion& targetRegion, const std::vector<map_id>& buildingTypes)
{
	std::vector<Unit> buildings;

	GetHumanBuildings(buildings, buildingTypes, targetRegion.area);
	return buildings;
}

void OffensiveFightGroup::AttackBuilding(FightGroupOverlay& group, const std::vector<map_id>& buildingTypes)
{
	std::vector<TargetRegion> viableTargetRegions = GetPossibleTargetRegions(targetRegions);
	TargetRegion targetRegion = GetTargetRegion(viableTargetRegions, buildingTypes);
	std::vector<Unit> buildings = SelectTargetBuildings(targetRegion, buildingTypes);

	if (buildings.empty())
	{
		group.BasicAttack();
		return;
	}

	Unit building = buildings[TethysGame::GetRand(buildings.size())];
	fightGroupsWithTarget.push_back(FightGroupTarget{ std::make_shared<FightGroupOverlay>(group), building, targetRegion.waypoints });
}

void OffensiveFightGroup::GetHumanBuildings(std::vector<Unit>& buildingsOut, const std::vector<map_id>& buildingTypes, const MAP_RECT& region)
{
	for (map_id buildingType : buildingTypes) {
		GetHumanBuildings(buildingsOut, buildingType, region);
	}
}

void OffensiveFightGroup::GetHumanBuildings(std::vector<Unit>& buildingsOut, map_id buildingType, const MAP_RECT& region)
{
	Unit building;
	for (std::size_t i = 0; i < humanPlayerCount; ++i)
	{
		PlayerBuildingEnum playerBuildingEnum(i, buildingType);

		while (playerBuildingEnum.GetNext(building))
		{
			if(MapEx::Check(region, building.Location()))
			{
				buildingsOut.push_back(building);
			}
		}
	}
}

void OffensiveFightGroup::UpdateTaskedFightGroups()
{
	for (int i = fightGroupsWithTarget.size(); i-- > 0; )
	{
		UpdateTaskedFightGroup(fightGroupsWithTarget[i]);
	}
}

void OffensiveFightGroup::UpdateTaskedFightGroup(FightGroupTarget& fightGroupWithTarget)
{
	if (!fightGroupWithTarget.initiatedAttack)
	{
		if (fightGroupWithTarget.AreWaypointsEmpty())
		{
			fightGroupWithTarget.CommenceAttack();
			fightGroupWithTarget.initiatedAttack = true;
		}
		else
		{
			// TODO: Check if the fight group has reached the next waypoint, and if so, remove it from the list of waypoints
			//if (IsWaypointReached(fightGroupWithTarget.GetNextWaypoint(), *fightGroupWithTarget.fightGroup))
			//{
			//	//fightGroupWithTarget.waypoints.erase(fightGroupWithTarget.waypoints.begin());
			//}
		}
	}
	else
	{
		if (!fightGroupWithTarget.building.IsLive())
		{
			FightGroupTarget fightGroupTarget = fightGroupWithTarget;
			fightGroupsWithTarget.erase(std::remove(fightGroupsWithTarget.begin(), fightGroupsWithTarget.end(), fightGroupWithTarget), fightGroupsWithTarget.end());
			TaskFightGroup(*fightGroupTarget.fightGroup);
		}
	}
}

void OffensiveFightGroup::SetTargetRegions(const std::vector<TargetRegion>& targetRegions)
{
	this->targetRegions = targetRegions;
}

bool OffensiveFightGroup::IsWaypointReached(const LOCATION& loc, FightGroupOverlay& fightGroup) const
{
	return fightGroup.PercentageVehiclesInRect(MapEx::GetRectCenteredOnLoc(loc, 10)) >= percentageVehiclesRequiredAtWaypoint;
}
