#include "OffensiveFightGroup.h"

void OffensiveFightGroup::Initialize(MAP_RECT guardedRect, const Unit& vehicleFactory)
{
	FightGroupOverlay::Initialize(guardedRect, vehicleFactory);
}

void OffensiveFightGroup::Populate()
{
	SetLynxCount(map_id::mapMicrowave, SelectTargetCount());
}
