#pragma once

#include "gamemode/GameMode.h"

class CreativeMode : public GameMode
{
public:
	CreativeMode(PacketSender *packetSender, Level *level);
	~CreativeMode();
};