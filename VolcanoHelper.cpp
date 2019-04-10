#include "VolcanoHelper.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"

const MAP_RECT LavaCellRect(1 + X_, 1 + Y_, 256 + X_, 255 + Y_);
const MAP_RECT NWLavaPath(63 + X_, 22 + Y_, 63 + X_, 24 + Y_);
const MAP_RECT SWLavaPath(90 + X_, 248 + Y_, 90 + X_, 250 + Y_);
const MAP_RECT SELavaPath(180 + X_, 170 + Y_, 180 + X_, 174 + Y_);
const LOCATION NWVolcanoFlowLoc(65 + X_, 22 + Y_);
const LOCATION SWVolcanoFlowLoc(89 + X_, 246 + Y_);
const LOCATION SEVolcanoFlowLoc(179 + X_, 170 + Y_);

Export void NWVolcanoErupts()
{
	TethysGame::SetEruption(63 + X_, 22 + Y_, 80);
	//TethysGame::SetEruption(volcanoEruptionLoc.x, volcanoEruptionLoc.y, 1000);
}

Export void SWVolcanoErupts()
{
	TethysGame::SetEruption(89 + X_, 246 + Y_, 80);
	//TethysGame::SetEruption(volcanoEruptionLoc.x, volcanoEruptionLoc.y, 1000);

}

Export void SEVolcanoErupts()
{
	TethysGame::SetEruption(179 + X_, 170 + Y_, 80);
	//TethysGame::SetEruption(volcanoEruptionLoc.x, volcanoEruptionLoc.y, 1000);
}

void InitializeVolcanos()
{
	SetLavaPossibleAllSlowCells(LavaCellRect);

	AnimateFlowSE(NWVolcanoFlowLoc);
	AnimateFlowSE(SWVolcanoFlowLoc);

	SetLavaPossibleRegion(NWLavaPath);
	SetLavaPossibleRegion(SWLavaPath);
	SetLavaPossibleRegion(SELavaPath);

	Trigger NWTrigVolcanoEruption = CreateTimeTrigger(true, true, 10, "NWVolcanoErupts");
	Trigger SWTrigVolcanoEruption = CreateTimeTrigger(true, true, 10, "SWVolcanoErupts");
}