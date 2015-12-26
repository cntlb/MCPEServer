#include "NetServerHandler.h"

#include "NetworkStructures.h"
#include "PacketSender.h"

#include "RakNetTypes.h"

#include "SharedConstants.h"
#include "util\Util.h"

NetServerHandler::NetServerHandler(RakNetInstance *raknet, PacketSender *sender)
{
	this->raknet = raknet;
	this->sender = sender;
}

NetServerHandler::~NetServerHandler()
{

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
	DisconnectPacket pk;
	pk.message = message;
	sender->send(guid, pk);

	onDisconnect(guid, message);
}

void NetServerHandler::handle(const RakNet::RakNetGUID &guid, LoginPacket *packet)
{
	if (packet->protocol1 != SharedConstants::NetworkProtocolVersion)
	{
		PlayStatusPacket statusPacket;
		if (packet->protocol1 < SharedConstants::NetworkProtocolVersion)
			statusPacket.status = PlayStatusPacket::LOGIN_FAILED_CLIENT;
		else
			statusPacket.status = PlayStatusPacket::LOGIN_FAILED_SERVER;
		sender->send(guid, statusPacket);

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

	PlayStatusPacket status1;
	status1.status = PlayStatusPacket::LOGIN_SUCCESS;
	sender->send(guid, status1);

	/*PlayStatusPacket status2;
	status2.status = PlayStatusPacket::PLAYER_SPAWN;
	sender->send(guid, status2);*/
}