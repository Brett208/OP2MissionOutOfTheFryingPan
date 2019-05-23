#pragma once
#include "Outpost2DLL/Outpost2DLL.h"

class FightGroupOverlay
{
public:
	virtual FightGroup Initialize(MAP_RECT guardedRect, const Unit& vehicleFactory, PlayerNum aiPlayerNum);
	void AddLynx(FightGroup& fightGroup, const LOCATION& loc, map_id weapon, PlayerNum playerNum);
	int SelectTargetCount();
	PlayerNum aiPlayerNum;

private:
	
};






