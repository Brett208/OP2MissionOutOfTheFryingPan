#pragma once
#include "FightGroupOverlay.h"
#include "Outpost2DLL/Outpost2DLL.h"

class DefensiveFightGroup : FightGroupOverlay
{
public:
	DefensiveFightGroup(PlayerNum aiPlayerNum) : FightGroupOverlay(aiPlayerNum) {}

	void Initialize(MAP_RECT guardedRect, const Unit& vehicleFactory) override;
	void Populate();

private:
	
};
