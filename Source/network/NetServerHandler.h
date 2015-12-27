#pragma once

#include <string>
#include <memory>

#include "level/LevelListener.hpp"
#include "entity/EntityUniqueID.h"

class Level;
class GameMode;
class Player;

class RakNetInstance;
class PacketSender;

class LoginPacket;
class TextPacket;
class PlayerActionPacket;

namespace RakNet
{
	struct RakNetGUID;
};

class NetServerHandler : public LevelListener
{
private:
	Level *level;
	GameMode *gamemode;

	RakNetInstance *raknet;
	PacketSender *sender;

public:
	NetServerHandler(Level *level, GameMode *gamemode, RakNetInstance *raknet, PacketSender *sender);
	~NetServerHandler();

	Player *_getPlayer(const RakNet::RakNetGUID &guid);
	Player *_getPlayer(const RakNet::RakNetGUID &guid, EntityUniqueID uniqueID);

	void _displayGameMessage(const std::string &source, const std::string &message);

	void _sendLevelData(Player *player, const RakNet::RakNetGUID &guid);
	void _sendAdditionalLevelData(Player *player, const RakNet::RakNetGUID &guid);

	bool allowIncomingPacketId(const RakNet::RakNetGUID &guid, int id);

	void onNewClient(const RakNet::RakNetGUID &guid);
	void onDisconnect(const RakNet::RakNetGUID &guid, const std::string &message);

	void disconnectClient(const RakNet::RakNetGUID &guid, const std::string &message);

	void handle(const RakNet::RakNetGUID &guid, LoginPacket *packet);
	void sendLoginMessageLocal(const RakNet::RakNetGUID &guid, LoginPacket *packet);
	std::unique_ptr<Player> createNewPlayer(const RakNet::RakNetGUID &guid, LoginPacket *packet);

	void handle(const RakNet::RakNetGUID &guid, TextPacket *packet);
	void handle(const RakNet::RakNetGUID &guid, PlayerActionPacket *packet);

	void onEntityAdded(Entity &entity);
	void onEntityRemoved(Entity &entity);

	void onNewChunkFor(Player &player, LevelChunk &chunk);
};

