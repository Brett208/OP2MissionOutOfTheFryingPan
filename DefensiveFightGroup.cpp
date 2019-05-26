#include "DefensiveFightGroup.h"

void DefensiveFightGroup::Initialize(MAP_RECT guardedRect, const Unit& vehicleFactory) 
{
	FightGroupOverlay::Initialize(guardedRect, vehicleFactory);
}

void DefensiveFightGroup::Populate()
{
	Unit unit;
	//TethysGame::CreateUnit(unit, map_id::mapLynx, LOCATION(100 + X_, 130 + Y_), 0, map_id::mapLaser, South);

	// 3 ESG, 3 EMP, 3 Sticky, 3 RPG, 3 Microwave
	AddLynx(GetGuardedRect().RandPt(), map_id::mapESG);
	AddLynx(GetGuardedRect().RandPt(), map_id::mapESG);
	AddLynx(GetGuardedRect().RandPt(), map_id::mapESG);

	AddLynx(GetGuardedRect().RandPt(), map_id::mapEMP);
	AddLynx(GetGuardedRect().RandPt(), map_id::mapEMP);
	AddLynx(GetGuardedRect().RandPt(), map_id::mapEMP);

	AddLynx(GetGuardedRect().RandPt(), map_id::mapStickyfoam);
	AddLynx(GetGuardedRect().RandPt(), map_id::mapStickyfoam);
	AddLynx(GetGuardedRect().RandPt(), map_id::mapStickyfoam);

	AddLynx(GetGuardedRect().RandPt(), map_id::mapRPG);
	AddLynx(GetGuardedRect().RandPt(), map_id::mapRPG);
	AddLynx(GetGuardedRect().RandPt(), map_id::mapRPG);

	AddLynx(GetGuardedRect().RandPt(), map_id::mapMicrowave);
	AddLynx(GetGuardedRect().RandPt(), map_id::mapMicrowave);
	AddLynx(GetGuardedRect().RandPt(), map_id::mapMicrowave);

	const std::vector<TargetTankCount> targetTankCount{
		{mapLynx, mapESG, SelectTargetCount()},
		{mapLynx, mapEMP, SelectTargetCount()},
		{mapLynx, mapStickyfoam, SelectTargetCount()},
		{mapLynx, mapRPG, SelectTargetCount() },
		{mapLynx, mapMicrowave, SelectTargetCount()} };
	SetTankCounts(targetTankCount);
}