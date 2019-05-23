#pragma once
#include "FightGroupOverlay.h"
#include "Outpost2DLL/Outpost2DLL.h"

class OffensiveFightGroup : FightGroupOverlay
{
public:
	FightGroup Initialize(MAP_RECT guardedRect, const Unit& vehicleFactory, PlayerNum aiPlayerNum) override
	{
		return FightGroupOverlay::Initialize(guardedRect, vehicleFactory, aiPlayerNum);
	}
	
	void Populate(FightGroup& fightGroup, MAP_RECT attackAssembleRect);	
};
