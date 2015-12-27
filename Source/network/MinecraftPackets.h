#pragma once

#include <memory>

#include "network/packet/Packet.h"

class MinecraftPackets
{
public:
	static std::unique_ptr<Packet> createPacket(int id);
};