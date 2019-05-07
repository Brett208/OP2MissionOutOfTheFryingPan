#pragma once
#include "AIBaseBuilder.h"
#include "HFL/Source/HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"

void AIInitialization();
int HumanPlayerCount();
PlayerNum GetAIIndex();
PlayerColor GetAIColor(bool allowBlack = false);


