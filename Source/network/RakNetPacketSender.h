#pragma once

#include "network/PacketSender.h"

namespace RakNet
{
	struct AddressOrGUID;
};

class RakNetInstance;

class RakNetPacketSender : public PacketSender
{
private:
	RakNetInstance *raknet;

public:
	RakNetPacketSender(RakNetInstance *);
	virtual ~RakNetPacketSender();

	virtual void send(const Packet &);
	virtual void send(const RakNet::RakNetGUID &, const Packet &);
	virtual void sendBroadcast(const RakNet::RakNetGUID &, const Packet &);
	void _sendInternal(const RakNet::AddressOrGUID &addressOrGUID, const Packet &packet, bool b);
};

