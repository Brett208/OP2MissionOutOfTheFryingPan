#include "FightGroupOverlay.h"
#include "AIPlayer.h"

FightGroupOverlay::FightGroupOverlay(PlayerNum aiPlayerNum) : aiPlayerNum(aiPlayerNum) {}

void FightGroupOverlay::Initialize(MAP_RECT guardedRect, const Unit& vehicleFactory)
{
	this->guardedRect = guardedRect;

	fightGroup = CreateFightGroup(Player[aiPlayerNum]);
	fightGroup.DoGuardRect();
	fightGroup.SetRect(guardedRect);
	fightGroup.AddGuardedRect(guardedRect);

	buildingGroup = CreateBuildingGroup(Player[aiPlayerNum]);
	buildingGroup.RecordVehReinforceGroup(fightGroup, 1);
	buildingGroup.TakeUnit(vehicleFactory);
}

void FightGroupOverlay::SetTankCounts(const std::vector<TargetTankCount>& targetTankCounts)
{
	for (const auto& targetTankCount : targetTankCounts) {
		fightGroup.SetTargCount(targetTankCount.tankType, targetTankCount.weaponType, targetTankCount.count);
	}
}

void FightGroupOverlay::AddLynx(const LOCATION& loc, map_id weapon)
{
	int direction = TethysGame::GetRand(8);

	Unit unit;
	TethysGame::CreateUnit(unit, map_id::mapLynx, loc, aiPlayerNum, weapon, direction);
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

void FightGroupOverlay::ClearTargetCount()
{
	fightGroup.ClearTargCount();
}

void FightGroupOverlay::SetLynxCount(map_id weaponType, int targetCount)
{
	fightGroup.SetTargCount(map_id::mapLynx, weaponType, targetCount);
}

void FightGroupOverlay::SetPantherCount(map_id weaponType, int targetCount)
{
	fightGroup.SetTargCount(map_id::mapPanther, weaponType, targetCount);
}

void FightGroupOverlay::SetTigerCount(map_id weaponType, int targetCount)
{
	fightGroup.SetTargCount(map_id::mapTiger, weaponType, targetCount);
}

void FightGroupOverlay::SetScorpionCount(int targetCount)
{
	fightGroup.SetTargCount(map_id::mapScorpion, map_id::mapEnergyCannon, targetCount);
}

MAP_RECT FightGroupOverlay::GetGuardedRect()
{
	return guardedRect;
}