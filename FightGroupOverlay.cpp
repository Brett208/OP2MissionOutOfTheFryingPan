#include "FightGroupOverlay.h"

FightGroupOverlay::FightGroupOverlay(PlayerNum aiPlayerNum, int humanPlayerCount) : 
	aiPlayerNum(aiPlayerNum), humanPlayerCount(humanPlayerCount) {}

void FightGroupOverlay::Initialize(MAP_RECT guardedRect, const Unit& vehicleFactory)
{
	this->vehicleFactory = vehicleFactory;
	this->guardedRect = guardedRect;

	fightGroup = CreateFightGroup(Player[aiPlayerNum]);
	fightGroup.DoGuardRect();
	fightGroup.SetRect(guardedRect);
	fightGroup.AddGuardedRect(guardedRect);

	buildingGroup.Destroy();
	buildingGroup = CreateBuildingGroup(Player[aiPlayerNum]);
	buildingGroup.RecordVehReinforceGroup(fightGroup, 1);
	buildingGroup.TakeUnit(vehicleFactory);
}

void FightGroupOverlay::SetTankCounts(const std::vector<TargetTankCount>& targetTankCounts)
{
	targetCount = 0;
	for (const auto& targetTankCount : targetTankCounts) {
		targetCount += targetTankCount.count;
		fightGroup.SetTargCount(targetTankCount.tankType, targetTankCount.weaponType, targetTankCount.count);
	}
}

void FightGroupOverlay::AddTank(map_id tankType, map_id weapon)
{
	int direction = TethysGame::GetRand(8);

	Unit unit;
	TethysGame::CreateUnit(unit, tankType, GetGuardedRect().RandPt(), aiPlayerNum, weapon, direction);
	unit.DoSetLights(true);
	fightGroup.TakeUnit(unit);
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

void FightGroupOverlay::BasicAttack() {
	fightGroup.DoAttackEnemy();
}

FightGroup FightGroupOverlay::GetFightGroup() {
	return fightGroup;
}

bool FightGroupOverlay::IsFull()
{
	return GetFightGroupCount() == targetCount;
}

int FightGroupOverlay::GetFightGroupCount()
{
	return fightGroup.TotalUnitCount();
}
