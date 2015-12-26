#pragma once

#include <memory>
#include "NetworkStructures.h"
#include "PacketEnumeration.h"

class MinecraftPackets
{
public:
	static std::unique_ptr<Packet> createPacket(int id)
	{
		std::unique_ptr<Packet> packet;

		switch (id)
		{
		case ID_LOGIN:
			packet = std::unique_ptr<Packet>(new LoginPacket);
			break;
		case ID_BATCH:
			packet = std::unique_ptr<Packet>(new BatchPacket);
			break;
		}
		return packet;
	}
};