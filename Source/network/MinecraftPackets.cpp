#include "network/MinecraftPackets.h"

#include "network/packet/PacketID.h"
#include "network/packet/Packet.h"
#include "network/packet/LoginPacket.h"
#include "network/packet/PlayStatusPacket.h"
#include "network/packet/DisconnectPacket.h"
#include "network/packet/BatchPacket.h"
#include "network/packet/TextPacket.h"
#include "network/packet/SetTimePacket.h"
#include "network/packet/StartGamePacket.h"
#include "network/packet/PlayerActionPacket.h"
#include "network/packet/SetSpawnPositionPacket.h"
#include "network/packet/SetDifficultyPacket.h"
#include "network/packet/SetHealthPacket.h"

std::unique_ptr<Packet> MinecraftPackets::createPacket(int id)
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
	case ID_SET_HEALTH:
		packet = std::unique_ptr<Packet>(new SetHealthPacket);
		break;
	case ID_SET_SPAWN_POSITION:
		packet = std::unique_ptr<Packet>(new SetSpawnPositionPacket);
		break;
	case ID_SET_DIFFICULTY:
		packet = std::unique_ptr<Packet>(new SetDifficultyPacket);
		break;
	}
	return packet;
}