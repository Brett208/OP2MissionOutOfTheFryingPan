#include "FightGroupOverlay.h"
#include "AIPlayer.h"

FightGroup FightGroupOverlay::Initialize(MAP_RECT guardedRect, const Unit& vehicleFactory, PlayerNum aiPlayerNum)
{
	this->aiPlayerNum = aiPlayerNum;

	FightGroup fightGroup = CreateFightGroup(Player[aiPlayerNum]);
	fightGroup.DoGuardRect();
	fightGroup.SetRect(guardedRect);
	fightGroup.AddGuardedRect(guardedRect);

	BuildingGroup buildingGroup = CreateBuildingGroup(Player[aiPlayerNum]);
	buildingGroup.RecordVehReinforceGroup(fightGroup, 1);
	buildingGroup.TakeUnit(vehicleFactory);

	return fightGroup;
}

void FightGroupOverlay::AddLynx(FightGroup& fightGroup, const LOCATION& loc, map_id weapon, PlayerNum playerNum)
{
	int direction = TethysGame::GetRand(8);

	Unit unit;
	TethysGame::CreateUnit(unit, map_id::mapLynx, loc, playerNum, weapon, direction);
	unit.DoSetLights(true);
	fightGroup.TakeUnit(unit);
}

int FightGroupOverlay::SelectTargetCount()
{
	switch (HumanPlayerCount())
	{
	case 2: {
		return 5;
	}
	case 3: {
		return 8;
	}
	default: {
		return 12;
	}
	}
}