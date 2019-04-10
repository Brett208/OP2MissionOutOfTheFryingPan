#include "VolcanoHelper.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"

const MAP_RECT LavaCellRect(1 + X_, 1 + Y_, 256 + X_, 255 + Y_);
const MAP_RECT NWLavaPath(60 + X_, 20 + Y_, 60 + X_, 22 + Y_);
const MAP_RECT SWLavaPath(90 + X_, 248 + Y_, 90 + X_, 250 + Y_);
const MAP_RECT SELavaPath(180 + X_, 170 + Y_, 180 + X_, 174 + Y_);
const LOCATION NWVolcanoFlowLoc(62 + X_, 20 + Y_);
const LOCATION SWVolcanoFlowLoc(90 + X_, 246 + Y_);
const LOCATION SEVolcanoFlowLoc(179 + X_, 170 + Y_);
const int LavaFlowRate = 80; //1000

void InitializeVolcanos()
{
	SetLavaPossibleAllSlowCells(LavaCellRect);

	AnimateFlowSE(NWVolcanoFlowLoc);
	AnimateFlowSE(SWVolcanoFlowLoc);
	AnimateFlowSE(SEVolcanoFlowLoc);

	SetLavaPossibleRegion(NWLavaPath);
	SetLavaPossibleRegion(SWLavaPath);
	SetLavaPossibleRegion(SELavaPath);

	Trigger NWTrigVolcanoEruption = CreateTimeTrigger(true, true, 10, "NWVolcanoErupts");
	Trigger SWTrigVolcanoEruption = CreateTimeTrigger(true, true, 10, "SWVolcanoErupts");
	Trigger SETrigVolcanoEruption = CreateTimeTrigger(true, true, 10, "SEVolcanoErupts");
}

Export void NWVolcanoErupts()
{
	TethysGame::SetEruption(NWVolcanoFlowLoc.x, NWVolcanoFlowLoc.y, LavaFlowRate);
}

Export void SWVolcanoErupts()
{
	TethysGame::SetEruption(SWVolcanoFlowLoc.x, SWVolcanoFlowLoc.y, LavaFlowRate);
}

Export void SEVolcanoErupts()
{
	TethysGame::SetEruption(SEVolcanoFlowLoc.x, SEVolcanoFlowLoc.y, LavaFlowRate);
}
