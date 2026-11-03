#pragma once
#include "FightGroupOverlay.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include "../OP2MissionSDK/HFL/Source/HFL.h"
#include "../TargetRegion.h"
#include "../MapRectEx.h"

#include <memory>
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
	/// <summary>
	/// Adds a list of TargetRegions to the fight group which it will use to semi-randomly attack an opponent.
	/// The AI will favor attacking the regions in order of the list, with index 0 being the most preferred.
	/// </summary>
	/// <param name="targetRegions">Each region includes an area to search for the opponent and a list of waypoints to reach the region.</param>
	void SetTargetRegions(const std::vector<TargetRegion>& targetRegions);

private:
	struct FightGroupTarget
	{
		std::shared_ptr<FightGroupOverlay> fightGroup;
		Unit building;
		std::vector<LOCATION> waypoints = {};
		bool initiatedAttack = false;

		bool AreWaypointsEmpty() const
		{
			return waypoints.empty();
		}

		void CommenceAttack()
		{
			// Set the fight group to idle in a rectangle around the target building so that it can attack the building without wandering off
			MAP_RECT rect = MapEx::GetRectCenteredOnLoc(building.Location(), 10);
			fightGroup->SetIdleRect(rect);
		}

/*		LOCATION GetNextWaypoint() const
		{
			if (!waypoints.empty())
			{
				return waypoints[0];
			}
			else
			{
				return LOCATION{ 1 + X_, 1 + Y_ };
			}
		}*/
	};

	std::vector<FightGroupTarget> fightGroupsWithTarget;
	std::vector<TargetRegion> targetRegions;

	const int percentageVehiclesRequiredAtWaypoint = 75;

	bool IsWaypointReached(const LOCATION& loc, FightGroupOverlay& fightGroup) const;
	void TaskFightGroup(FightGroupOverlay& group);
	void AttackBuilding(FightGroupOverlay& group, const std::vector<map_id>& buildingTypes);
	void GetHumanBuildings(std::vector<Unit>& buildingsOut, const std::vector<map_id>& buildingTypes, const MAP_RECT& region);
	void GetHumanBuildings(std::vector<Unit>& buildingsOut, map_id buildingType, const MAP_RECT& region);
	std::vector<TargetRegion> GetPossibleTargetRegions(const std::vector<TargetRegion>& targetRegionList);
	std::vector<Unit> SelectTargetBuildings(const TargetRegion& targetRegion, const std::vector<map_id>& buildingTypes);
	bool SkipRegion(const TargetRegion& region, const std::vector<map_id>& buildingTypes);
	TargetRegion GetTargetRegion(const std::vector<TargetRegion>& targetRegions, const std::vector<map_id>& buildingTypes);
	void UpdateTaskedFightGroup(FightGroupTarget& fightGroupTarget);
};
