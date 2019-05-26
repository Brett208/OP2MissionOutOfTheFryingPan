#pragma once
#include "FightGroupOverlay.h"
#include "Outpost2DLL/Outpost2DLL.h"


class OffensiveFightGroup : FightGroupOverlay
{
public:
	OffensiveFightGroup(PlayerNum aiPlayerNum) : FightGroupOverlay(aiPlayerNum) {}
	void Initialize(MAP_RECT guardedRect, const Unit& vehicleFactory) override;
	void Populate();	
};
