#pragma once
#include "Outpost2DLL/Outpost2DLL.h"
#include <vector>

struct TargetTankCount
{
	map_id tankType;
	map_id weaponType;
	int count;
};

/// <summary>
/// The virtual basis of a fight group that could be offensive or defensive in nature.
/// </summary>
class FightGroupOverlay
{
public:
	FightGroupOverlay(PlayerNum aiPlayerNum, int humanPlayerCount);
	virtual void Initialize(MAP_RECT guardedRect, std::vector<Unit> vehicleFactories);
	bool IsFull();
	int vehicleFactoryCount() { return vehicleFactories.size(); }

	float PercentageVehiclesInRect(const MAP_RECT& rect) const;
	inline void SetIdleRect(MAP_RECT rect) { fightGroup.SetRect(rect); }
	void BasicAttack();

protected:
	const PlayerNum aiPlayerNum;
	const std::size_t humanPlayerCount;
	std::vector<Unit> vehicleFactories;
	std::vector<Unit> tanks;
	
	void AddTank(map_id tankType, map_id weapon);

	void ClearTargetCount();
	void SetTankCounts(const std::vector<TargetTankCount>& targetTankCounts);
	void SetLynxCount(map_id weaponType, int targetCount);
	void SetPantherCount(map_id weaponType, int targetCount);
	void SetTigerCount(map_id weaponType, int targetCount);
	void SetScorpionCount(int targetCount);

	MAP_RECT GetGuardedRect() const;
	
	/// <summary>
	/// Total alive units currently in the fight group.
	/// </summary>
	int GetFightGroupCount() const;

	void TakeUnit(Unit& unit);
	//FightGroup GetFightGroup() const;
	int targetCount = 0;

private:
	MAP_RECT guardedRect;
	BuildingGroup buildingGroup;
	FightGroup fightGroup;
};
