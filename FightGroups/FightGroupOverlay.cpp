#include "FightGroupOverlay.h"
#include "../MapRectEx.h"

FightGroupOverlay::FightGroupOverlay(PlayerNum aiPlayerNum, int humanPlayerCount) : 
	aiPlayerNum(aiPlayerNum), humanPlayerCount(humanPlayerCount) {}

void FightGroupOverlay::Initialize(MAP_RECT guardedRect, std::vector<Unit> vehicleFactories)
{
	this->vehicleFactories = vehicleFactories;
	this->guardedRect = guardedRect;
	tanks.clear();

	fightGroup = CreateFightGroup(Player[aiPlayerNum]);
	fightGroup.DoGuardRect();
	fightGroup.SetRect(guardedRect);
	fightGroup.AddGuardedRect(guardedRect);

	if (buildingGroup.IsInitialized()) {
		buildingGroup.Destroy();
	}

	buildingGroup = CreateBuildingGroup(Player[aiPlayerNum]);
	buildingGroup.RecordVehReinforceGroup(fightGroup, 1);
	for (Unit& vehicleFactory : vehicleFactories) {
		if (vehicleFactory.IsLive()) {
			buildingGroup.TakeUnit(vehicleFactory);
		}
	}
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

float FightGroupOverlay::PercentageVehiclesInRect(const MAP_RECT& rect) const
{
	int totalFightGroupCount = GetFightGroupCount();
	int unitsInRect = 0;

	for (const Unit& tank : tanks) {
		if (MapEx::Check(rect, tank.Location()))
		{
			unitsInRect++;
		}
	}
	return (totalFightGroupCount > 0) ? (100.0f * unitsInRect / totalFightGroupCount) : 0.0f;
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

MAP_RECT FightGroupOverlay::GetGuardedRect() const
{
	return guardedRect;
}

void FightGroupOverlay::BasicAttack() {
	fightGroup.DoAttackEnemy();
}

void FightGroupOverlay::TakeUnit(Unit& unit)
{
	fightGroup.TakeUnit(unit);
	tanks.push_back(unit);
}

bool FightGroupOverlay::IsFull()
{
	return GetFightGroupCount() == targetCount;
}

int FightGroupOverlay::GetFightGroupCount() const
{
	return const_cast<FightGroup&>(fightGroup).TotalUnitCount();
}
