#include "DefensiveFightGroup.h"

void DefensiveFightGroup::Initialize(MAP_RECT guardedRect, const Unit& vehicleFactory) 
{
	FightGroupOverlay::Initialize(guardedRect, vehicleFactory);
}

void DefensiveFightGroup::Populate(const std::vector<TargetTankCount>& targetTankCounts)
{
	for (const auto& targetTank : targetTankCounts)
	{
		for (int count = 0; count < targetTank.count; ++count) {
			AddTank(targetTank.tankType, targetTank.weaponType);
		}
	}

	SetTankCounts(targetTankCounts);
}
