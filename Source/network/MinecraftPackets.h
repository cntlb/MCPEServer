#pragma once

#include <memory>

#include "network/NetworkStructures.h"
#include "network/PacketEnumeration.h"

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
		case ID_PLAY_STATUS:
			packet = std::unique_ptr<Packet>(new PlayStatusPacket);
			break;
		case ID_DISCONNECT:
			packet = std::unique_ptr<Packet>(new DisconnectPacket);
			break;
		case ID_BATCH:
			packet = std::unique_ptr<Packet>(new BatchPacket);
			break;
		case ID_TEXT:
			packet = std::unique_ptr<Packet>(new TextPacket);
			break;
		case ID_SET_TIME:
			packet = std::unique_ptr<Packet>(new SetTimePacket);
			break;
		case ID_START_GAME:
			packet = std::unique_ptr<Packet>(new StartGamePacket);
			break;
		case ID_PLAYER_ACTION:
			packet = std::unique_ptr<Packet>(new PlayerActionPacket);
			break;
		case ID_SET_SPAWN_POSITION:
			packet = std::unique_ptr<Packet>(new SetSpawnPositionPacket);
			break;
		}
		return packet;
	}
};