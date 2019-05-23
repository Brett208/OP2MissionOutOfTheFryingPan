#include "OffensiveFightGroup.h"

void OffensiveFightGroup::Populate(FightGroup& fightGroup, MAP_RECT attackAssembleRect)
{
	fightGroup.SetTargCount(map_id::mapLynx, map_id::mapMicrowave, SelectTargetCount());
}
