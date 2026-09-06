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
	std::vector<Unit> buildings;
	GetHumanBuildings(buildings, buildingTypes);

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

void OffensiveFightGroup::GetHumanBuildings(std::vector<Unit>& buildingsOut, const std::vector<map_id>& buildingTypes)
{
	for (map_id buildingType : buildingTypes) {
		GetHumanBuildings(buildingsOut, buildingType);
	}
}

void OffensiveFightGroup::GetHumanBuildings(std::vector<Unit>& buildingsOut, map_id buildingType)
{
	Unit building;
	for (std::size_t i = 0; i < humanPlayerCount; ++i)
	{
		PlayerBuildingEnum playerBuildingEnum(i, buildingType);

		while (playerBuildingEnum.GetNext(building))
		{
			buildingsOut.push_back(building);
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
