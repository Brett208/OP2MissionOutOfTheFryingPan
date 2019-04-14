#include "VolcanoHelper.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"

const MAP_RECT LavaCellRect(1 + X_, 1 + Y_, 256 + X_, 255 + Y_);
const MAP_RECT NWLavaPath(64 + X_, 22 + Y_, 65 + X_, 25 + Y_);
const MAP_RECT SWLavaPath(90 + X_, 246 + Y_, 91 + X_, 252 + Y_);
const MAP_RECT SELavaPath(180 + X_, 171 + Y_, 181 + X_, 174 + Y_);
const LOCATION NWVolcanoFlowLoc(64 + X_, 20 + Y_);
const LOCATION SWVolcanoFlowLoc(90 + X_, 246 + Y_);
const LOCATION SEVolcanoFlowLoc(180 + X_, 170 + Y_);

Export void NWVolcanoErupts()
{
	TethysGame::SetEruption(64 + X_, 21 + Y_, 80);
	//TethysGame::SetEruption(volcanoEruptionLoc.x, volcanoEruptionLoc.y, 1000);
}

Export void SWVolcanoErupts()
{
	TethysGame::SetEruption(90 + X_, 246 + Y_, 80);
	//TethysGame::SetEruption(volcanoEruptionLoc.x, volcanoEruptionLoc.y, 1000);

}

Export void SEVolcanoErupts()
{
	TethysGame::SetEruption(180 + X_, 171 + Y_, 80);
	//TethysGame::SetEruption(volcanoEruptionLoc.x, volcanoEruptionLoc.y, 1000);
}

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
