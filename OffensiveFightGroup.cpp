#include "OffensiveFightGroup.h"

void OffensiveFightGroup::Initialize(MAP_RECT guardedRect, const Unit& vehicleFactory)
{
	FightGroupOverlay::Initialize(GetGuardedRect(), vehicleFactory);
}

void OffensiveFightGroup::Populate()
{
	SetLynxCount(map_id::mapMicrowave, SelectTargetCount());
}

void OffensiveFightGroup::OrderAttack()
{
	if (GetFightGroupCount() == SelectTargetCount())
	{
		FightGroupAttack();	
	}
}
