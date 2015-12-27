#pragma once

#include <string>

#include "PacketPriority.h"
#include "RakNetTypes.h"

namespace RakNet
{
	class RakPeerInterface;
	class BitStream;
};

class NetServerHandler;

class RakNetInstance
{
private:
	RakNet::RakPeerInterface *server;

public:
	RakNetInstance();
	~RakNetInstance();

	void host(unsigned short port, int maxIncomingConnections);
	void announceServer(const std::string &name);

	void runEvents(NetServerHandler *handler);

	void sendRaw(const RakNet::BitStream &bs, PacketPriority priority, PacketReliability reliability, RakNet::AddressOrGUID addressOrGUID, bool broadcast, unsigned int i);

	void tick();

	RakNet::RakPeerInterface *getPeer() const;
};

