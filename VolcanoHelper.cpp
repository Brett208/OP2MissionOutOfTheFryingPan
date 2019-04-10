#include "VolcanoHelper.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"

Export void NWVolcanoErupts()
{
	TethysGame::SetEruption(60 + X_, 22 + Y_, 80);
	//TethysGame::SetEruption(volcanoEruptionLoc.x, volcanoEruptionLoc.y, 1000);
}

Export void SWVolcanoErupts()
{
	TethysGame::SetEruption(60 + X_, 22 + Y_, 80);
	//TethysGame::SetEruption(volcanoEruptionLoc.x, volcanoEruptionLoc.y, 1000);
}
