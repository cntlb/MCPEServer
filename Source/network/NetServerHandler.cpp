#include "network/NetServerHandler.h"
#include "network/PacketSender.h"

#include "RakNetTypes.h"

#include "level/Level.h"
#include "entity/Player.h"
#include "SharedConstants.h"
#include "util/Util.h"

#include "level/GeneratorType.h"
#include "level/dimension/DimensionId.h"
#include "level/Difficulty.h"
#include "gamemode/GameType.h"

#include "network/packet/TextPacket.h"
#include "network/packet/DisconnectPacket.h"
#include "network/packet/PlayStatusPacket.h"
#include "network/packet/LoginPacket.h"
#include "network/packet/StartGamePacket.h"
#include "network/packet/SetSpawnPositionPacket.h"
#include "network/packet/SetTimePacket.h"
#include "network/packet/PlayerActionPacket.h"
#include "network/packet/SetDifficultyPacket.h"
#include "network/packet/SetHealthPacket.h"

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
	//for (auto &player : level->getPlayers())
	//	if (player->guid == guid)
	//		return player.get();

	return NULL;
}

Player *NetServerHandler::_getPlayer(const RakNet::RakNetGUID &guid, EntityUniqueID uniqueID)
{
	Player *player = _getPlayer(guid);
	//if (player && player->getUniqueID() == uniqueID)
	//	return player;

	return NULL;
}

void NetServerHandler::_displayGameMessage(const std::string &source, const std::string &message)
{
	TextPacket pk;
	pk.type = MESSAGE_CHAT;
	pk.source = source;
	pk.message = message;
	sender->send(pk);
}

void NetServerHandler::_sendLevelData(Player *player, const RakNet::RakNetGUID &guid)
{
	StartGamePacket startPacket;
	startPacket.seed = -198465456;
	startPacket.dimensionId = DIMENSION_NORMAL;
	startPacket.generatorType = GENERATOR_INFINITE;
	startPacket.spawnPos = BlockPos(0, 65, 0);
	startPacket.gametype = GAMETYPE_SURVIVAL;
	startPacket.creative = false;
	startPacket.stopTime = 0;
	startPacket.uniqueID = 0;
	startPacket.pos = Vec3(0, 65, 0);
	sender->send(guid, startPacket);

	SetSpawnPositionPacket spawnPositionPacket;
	spawnPositionPacket.pos = BlockPos(0, 65, 0);
	sender->send(guid, spawnPositionPacket);

	SetTimePacket timePacket;
	timePacket.time = 0;
	timePacket.started = true;
	sender->send(guid, timePacket);

	SetDifficultyPacket difficultyPacket;
	difficultyPacket.difficulty = DIFFICULTY_PEACEFUL;
	sender->send(guid, difficultyPacket);

	SetHealthPacket healthPacket;
	healthPacket.health = 10;
	sender->send(guid, healthPacket);

	PlayStatusPacket spawnStatus;
	spawnStatus.status = STATUS_PLAYER_SPAWN;
	sender->send(guid, spawnStatus);
}

void NetServerHandler::_sendAdditionalLevelData(Player *player, const RakNet::RakNetGUID &guid)
{
	// MobEffectPackets
	// UpdateAttributesPacket
	// ContainerSetContentPacket
	// CraftingDataPacket
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
	TextPacket pk;
	pk.type = MESSAGE_TRANSLATION;
	pk.message = "¡×e%multiplayer.player.left";
	pk.params.push_back("Test");
	sender->send(pk);
}

void NetServerHandler::disconnectClient(const RakNet::RakNetGUID &guid, const std::string &message)
{
	DisconnectPacket pk;
	pk.message = message;
	sender->send(guid, pk);

	onDisconnect(guid, message);
}

void NetServerHandler::handle(const RakNet::RakNetGUID &guid, LoginPacket *packet)
{
	if (_getPlayer(guid))
		return;

	if (packet->protocol1 != SharedConstants::NetworkProtocolVersion)
	{
		PlayStatusPacket pk;
		if (packet->protocol1 < SharedConstants::NetworkProtocolVersion)
			pk.status = STATUS_LOGIN_FAILED_CLIENT;
		else
			pk.status = STATUS_LOGIN_FAILED_SERVER;
		sender->send(guid, pk);
		
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

	PlayStatusPacket loginStatus;
	loginStatus.status = STATUS_LOGIN_SUCCESS;
	sender->send(guid, loginStatus);

	TextPacket pk;
	pk.type = MESSAGE_TRANSLATION;
	pk.message = "¡×e%multiplayer.player.joined";
	pk.params.push_back(packet->username);
	sender->send(pk);

	sendLoginMessageLocal(guid, packet);
}

void NetServerHandler::sendLoginMessageLocal(const RakNet::RakNetGUID &guid, LoginPacket *packet)
{
	//std::unique_ptr<Player> player_ptr = createNewPlayer(guid, packet);
	//Player *player = player_ptr.get();



	_sendLevelData(NULL, guid);
	_sendAdditionalLevelData(NULL, guid);

	printf("[DEBUG] Player with \"%s\" spawned!\n", packet->username.c_str());
}

std::unique_ptr<Player> NetServerHandler::createNewPlayer(const RakNet::RakNetGUID &guid, LoginPacket *packet)
{
	Player *player = new Player(level);

	return std::unique_ptr<Player>(player);
}

void NetServerHandler::handle(const RakNet::RakNetGUID &guid, TextPacket *packet)
{
	if (packet->type != MESSAGE_CHAT)
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
	case ACTION_START_BREAK:
		printf("[DEBUG] START_BREAK");
		break;
	case ACTION_ABORT_BREAK:
		printf("[DEBUG] ABORT_BREAK");
		break;
	case ACTION_STOP_BREAK:
		printf("[DEBUG] STOP_BREAK");
		break;
	case ACTION_RELEASE_ITEM:
		printf("[DEBUG] RELEASE_ITEM");
		break;
	case ACTION_STOP_SLEEPING:
		printf("[DEBUG] STOP_SLEEPING");
		break;
	case ACTION_RESPAWN:
		printf("[DEBUG] RESPAWN");
		break;
	case ACTION_JUMP:
		printf("[DEBUG] JUMP");
		break;
	case ACTION_START_SPRINT:
		printf("[DEBUG] START_SPRINT");
		break;
	case ACTION_STOP_SPRINT:
		printf("[DEBUG] STOP_SPRINT");
		break;
	case ACTION_START_SNEAK:
		printf("[DEBUG] START_SNEAK");
		break;
	case ACTION_STOP_SNEAK:
		printf("[DEBUG] STOP_SNEAK");
		break;
	case ACTION_DIMENSION_CHANGE:
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