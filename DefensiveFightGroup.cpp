#include "DefensiveFightGroup.h"

void DefensiveFightGroup::Populate(FightGroup& fightGroup, MAP_RECT guardedRect)
{
	Unit unit;
	//TethysGame::CreateUnit(unit, map_id::mapLynx, LOCATION(100 + X_, 130 + Y_), 0, map_id::mapLaser, South);

	// 3 ESG, 3 EMP, 3 Sticky, 3 RPG, 3 Microwave
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapESG, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapESG, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapESG, aiPlayerNum);

	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapEMP, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapEMP, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapEMP, aiPlayerNum);

	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapStickyfoam, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapStickyfoam, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapStickyfoam, aiPlayerNum);

	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapRPG, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapRPG, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapRPG, aiPlayerNum);

	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapMicrowave, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapMicrowave, aiPlayerNum);
	AddLynx(fightGroup, guardedRect.RandPt(), map_id::mapMicrowave, aiPlayerNum);

	int targetUnitCount = SelectTargetCount();

	fightGroup.SetTargCount(map_id::mapLynx, map_id::mapESG, targetUnitCount);
	fightGroup.SetTargCount(map_id::mapLynx, map_id::mapRPG, targetUnitCount);
	fightGroup.SetTargCount(map_id::mapLynx, map_id::mapMicrowave, targetUnitCount);
	fightGroup.SetTargCount(map_id::mapLynx, map_id::mapStickyfoam, targetUnitCount);
	fightGroup.SetTargCount(map_id::mapLynx, map_id::mapEMP, targetUnitCount);
}