#include "network/NetServerHandler.h"

#include "network/NetworkStructures.h"
#include "network/PacketSender.h"

#include "RakNetTypes.h"

#include "level/Level.h"
#include "entity/Player.h"

#include "SharedConstants.h"
#include "util/Util.h"

NetServerHandler::NetServerHandler(Level *level, GameMode *gamemode, RakNetInstance *raknet, PacketSender *sender)
{
	this->level = level;
	this->gamemode = gamemode;
	this->raknet = raknet;
	this->sender = sender;
}

NetServerHandler::~NetServerHandler()
{

}

Player *NetServerHandler::_getPlayer(const RakNet::RakNetGUID &guid)
{
	for (auto &player : level->getPlayers())
		if (player->guid == guid)
			return player.get();

	return NULL;
}

void NetServerHandler::_displayGameMessage(const std::string &source, const std::string &message)
{
	TextPacket pk(TextPacket::MessageType::CHAT);
	pk.source = source;
	pk.message = message;
	sender->send(pk);
}

bool NetServerHandler::allowIncomingPacketId(const RakNet::RakNetGUID &guid, int id)
{
	return true;
}

void NetServerHandler::onNewClient(const RakNet::RakNetGUID &guid)
{
	
}

void NetServerHandler::onDisconnect(const RakNet::RakNetGUID &guid, const std::string &message)
{

}

void NetServerHandler::disconnectClient(const RakNet::RakNetGUID &guid, const std::string &message)
{
	sender->send(guid, DisconnectPacket(message));
	onDisconnect(guid, message);
}

void NetServerHandler::handle(const RakNet::RakNetGUID &guid, LoginPacket *packet)
{
	//if (_getPlayer(guid))
	//	return;

	printf("[INFO] Connected player\n");

	if (packet->protocol1 != SharedConstants::NetworkProtocolVersion)
	{
		if (packet->protocol1 < SharedConstants::NetworkProtocolVersion)
			sender->send(guid, PlayStatusPacket(PlayStatusPacket::LOGIN_FAILED_CLIENT));
		else
			sender->send(guid, PlayStatusPacket(PlayStatusPacket::LOGIN_FAILED_SERVER));
		
		return;
	}

	bool nameValid = true;

	int len = packet->username.length();
	if (len > 16 || len < 3)
		nameValid = false;

	for (int i = 0; i < len; i++)
	{
		char c = packet->username[i];
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9' && c == '_'))
			continue;

		nameValid = false;
		break;
	}

	std::string iusername = Util::toLower(packet->username);

	if (!nameValid || !iusername.compare("rcon") || !iusername.compare("console"))
		disconnectClient(guid, "disconnectionScreen.invalidName");
	else if (packet->skin.length() != 64 * 32 * 4 && packet->skin.length() != 64 * 64 * 4)
		disconnectClient(guid, "disconnectionScreen.invalidSkin");

	sender->send(guid, PlayStatusPacket(PlayStatusPacket::LOGIN_SUCCESS));

	//Player *player = new Player(level);

	StartGamePacket startPacket;
	startPacket.seed = -198465456;
	startPacket.dimensionId = DimensionId::NORMAL;
	startPacket.generatorType = GeneratorType::NORMAL;
	startPacket.spawnPos = BlockPos(0, 65, 0);
	startPacket.gametype = GameType::SURVIVAL;
	startPacket.creative = true;
	startPacket.stopTime = 0;
	startPacket.uniqueID.id = 0;
	startPacket.pos = Vec3(0, 65, 0);
	sender->send(guid, startPacket);

	sender->send(guid, SetSpawnPositionPacket(BlockPos(0, 65, 0)));
	sender->send(guid, SetTimePacket(0));

	sender->send(guid, PlayStatusPacket(PlayStatusPacket::PLAYER_SPAWN));
}

void NetServerHandler::handle(const RakNet::RakNetGUID &guid, TextPacket *packet)
{
	if (packet->type != TextPacket::CHAT)
		return;

	if (!packet->message.empty())
	{
		if (packet->message[0] == '/')
			printf("[INFO] %s /%s\n", packet->source.c_str(), packet->message.c_str());
		else
		{
			printf("[INFO] <%s> %s\n", packet->source.c_str(), packet->message.c_str());
			_displayGameMessage(packet->source, packet->message);
		}
	}
}

void NetServerHandler::handle(const RakNet::RakNetGUID &guid, PlayerActionPacket *packet)
{
	switch (packet->action)
	{
	case PlayerActionPacket::START_BREAK:
		printf("[DEBUG] START_BREAK");
		break;
	case PlayerActionPacket::ABORT_BREAK:
		printf("[DEBUG] ABORT_BREAK");
		break;
	case PlayerActionPacket::STOP_BREAK:
		printf("[DEBUG] STOP_BREAK");
		break;
	case PlayerActionPacket::RELEASE_ITEM:
		printf("[DEBUG] RELEASE_ITEM");
		break;
	case PlayerActionPacket::STOP_SLEEPING:
		printf("[DEBUG] STOP_SLEEPING");
		break;
	case PlayerActionPacket::RESPAWN:
		printf("[DEBUG] RESPAWN");
		break;
	case PlayerActionPacket::JUMP:
		printf("[DEBUG] JUMP");
		break;
	case PlayerActionPacket::START_SPRINT:
		printf("[DEBUG] START_SPRINT");
		break;
	case PlayerActionPacket::STOP_SPRINT:
		printf("[DEBUG] STOP_SPRINT");
		break;
	case PlayerActionPacket::START_SNEAK:
		printf("[DEBUG] START_SNEAK");
		break;
	case PlayerActionPacket::STOP_SNEAK:
		printf("[DEBUG] STOP_SNEAK");
		break;
	case PlayerActionPacket::DIMENSION_CHANGE:
		printf("[DEBUG] DIMENSION_CHANGE");
		break;
	}
	printf(" X: %d Y: %d Z: %d\n", packet->pos.x, packet->pos.y, packet->pos.z);
}

void NetServerHandler::onEntityAdded(Entity &entity)
{

}

void NetServerHandler::onEntityRemoved(Entity &entity)
{

}

void NetServerHandler::onNewChunkFor(Player &player, LevelChunk &chunk)
{

}