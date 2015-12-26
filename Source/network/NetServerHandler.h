#pragma once

#include <string>

class RakNetInstance;
class PacketSender;
class LoginPacket;

namespace RakNet
{
	struct RakNetGUID;
};

class NetServerHandler
{
private:
	RakNetInstance *raknet;
	PacketSender *sender;

public:
	NetServerHandler(RakNetInstance *raknet, PacketSender *sender);
	~NetServerHandler();

	bool allowIncomingPacketId(const RakNet::RakNetGUID &guid, int id);

	void onNewClient(const RakNet::RakNetGUID &guid);
	void onDisconnect(const RakNet::RakNetGUID &guid, const std::string &message);

	void disconnectClient(const RakNet::RakNetGUID &guid, const std::string &message);

	void handle(const RakNet::RakNetGUID &guid, LoginPacket *packet);
};

