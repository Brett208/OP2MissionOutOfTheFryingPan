#pragma once
#include "FightGroupOverlay.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include <vector>


class OffensiveFightGroup : public FightGroupOverlay
{
public:
	OffensiveFightGroup(PlayerNum aiPlayerNum, int humanPlayerCount) : FightGroupOverlay(aiPlayerNum, humanPlayerCount) {}
	void Initialize(MAP_RECT guardedRect, std::vector<Unit> vehicleFactories, const std::vector<TargetTankCount>& targetCounts);
	void Attack(const std::vector<TargetTankCount>& targetCounts);
	void UpdateTaskedFightGroups();

private:
	struct FightGroupTarget
	{
		FightGroup fightGroup;
		Unit building;
	};

	std::vector<FightGroupTarget> fightGroupsWithTarget;

	void TaskFightGroup(FightGroup& fightGroup);
	void AttackBuilding(FightGroup& fightGroup, const std::vector<map_id>& buildingTypes);
	void GetHumanBuildings(std::vector<Unit>& buildingsOut, const std::vector<map_id>& buildingTypes);
	void GetHumanBuildings(std::vector<Unit>& buildingsOut, map_id buildingType);
	
};
