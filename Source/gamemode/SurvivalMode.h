#pragma once

#include "GameMode.h"

class SurvivalMode : public GameMode
{
public:
	SurvivalMode(PacketSender *packetSender, Level *level);
	~SurvivalMode();
};