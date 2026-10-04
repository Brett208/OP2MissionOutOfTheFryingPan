#pragma once
#include "FightGroupOverlay.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include "../OP2MissionSDK/HFL/Source/HFL.h"
#include "../TargetRegion.h"

#include <string>
#include <vector>


// Encapsulates an AI Fight Group that could be created offscreen or by an onscreen AI base.
class OffensiveFightGroup : public FightGroupOverlay
{
public:
	OffensiveFightGroup(PlayerNum aiPlayerNum, int humanPlayerCount) : FightGroupOverlay(aiPlayerNum, humanPlayerCount) {}
	void Initialize(MAP_RECT guardedRect, std::vector<Unit> vehicleFactories, const std::vector<TargetTankCount>& targetCounts);
	void Attack(const std::vector<TargetTankCount>& targetCounts);
	void UpdateTaskedFightGroups();
	void CreateTank(map_id type, map_id turret);
	void SetTargetRegions(const std::vector<TargetRegion>& targetRegions);

private:
	struct FightGroupTarget
	{
		FightGroup fightGroup;
		Unit building;
	};

	std::vector<FightGroupTarget> fightGroupsWithTarget;
	std::vector<TargetRegion> targetRegions;

	void TaskFightGroup(FightGroup& fightGroup);
	void AttackBuilding(FightGroup& fightGroup, const std::vector<map_id>& buildingTypes);
	void GetHumanBuildings(std::vector<Unit>& buildingsOut, const std::vector<map_id>& buildingTypes, MAP_RECT& region);
	void GetHumanBuildings(std::vector<Unit>& buildingsOut, map_id buildingType, MAP_RECT& region);
	std::vector<TargetRegion> GetPossibleTargetRegions(const std::vector<TargetRegion> targetRegionList);
	std::vector<Unit> SelectTargetBuildings(const std::vector<TargetRegion> targetRegions, const std::vector<map_id> buildingTypes);
};
