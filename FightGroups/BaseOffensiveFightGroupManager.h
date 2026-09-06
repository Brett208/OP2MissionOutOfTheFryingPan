#pragma once
#include "FightGroupOverlay.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include <memory>
#include <vector>
#include "OffensiveFightGroup.h"


/// <summary>
/// Manages the fight groups of an AI base.
/// </summary>
class BaseOffensiveFightGroupManager
{
public:
	BaseOffensiveFightGroupManager(PlayerNum aiPlayerNum, int humanPlayerCount, std::vector<TargetTankCount> initialTankCount, MAP_RECT tankStagingArea) :
		offensiveFightGroup(aiPlayerNum, humanPlayerCount), 
		offensiveTankCount(initialTankCount),
		aiPlayerNum(aiPlayerNum),
		humanPlayerCount(humanPlayerCount),
		tankStagingArea(tankStagingArea)
	{}
	void Update();
	void AddFightGroup(std::vector<Unit> vehicleFactories);
	void EnableAttack() { canAttack = true; }
	std::string DebugMessage();

private:
	OffensiveFightGroup offensiveFightGroup;
	bool canAttack = false;
	std::vector<std::unique_ptr<OffensiveFightGroup>> offensiveFightGroups;
	std::vector<TargetTankCount> offensiveTankCount;
	PlayerNum aiPlayerNum;
	int humanPlayerCount;
	MAP_RECT tankStagingArea;
};
