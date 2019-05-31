#pragma once
#include "Outpost2DLL/Outpost2DLL.h"
#include <vector>

struct TargetTankCount
{
	map_id tankType;
	map_id weaponType;
	int count;
};

class FightGroupOverlay
{
public:
	FightGroupOverlay(PlayerNum aiPlayerNum);
	virtual void Initialize(MAP_RECT guardedRect, const Unit& vehicleFactory);
	
protected:
	int SelectTargetCount();
	void AddLynx(const LOCATION& loc, map_id weapon);
	void ClearTargetCount();
	void SetTankCounts(const std::vector<TargetTankCount>& targetTankCounts);
	void SetLynxCount(map_id weaponType, int targetCount);
	void SetPantherCount(map_id weaponType, int targetCount);
	void SetTigerCount(map_id weaponType, int targetCount);
	void SetScorpionCount(int targetCount);
	MAP_RECT GetGuardedRect();
	void SetFightGroupTarget();
	int GetFightGroupCount();
	
private:
	MAP_RECT guardedRect;
	const PlayerNum aiPlayerNum;
	BuildingGroup buildingGroup;
	FightGroup fightGroup;
};






