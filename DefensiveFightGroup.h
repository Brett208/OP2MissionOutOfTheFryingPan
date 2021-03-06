#pragma once
#include "FightGroupOverlay.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include <vector>

class DefensiveFightGroup : FightGroupOverlay
{
public:
	DefensiveFightGroup(PlayerNum aiPlayerNum, int humanPlayerCount) : FightGroupOverlay(aiPlayerNum, humanPlayerCount) {}
	void Initialize(MAP_RECT guardedRect, std::vector<Unit> vehicleFactories) override;
	void Populate(const std::vector<TargetTankCount>& targetTankCounts);

private:
	
};
