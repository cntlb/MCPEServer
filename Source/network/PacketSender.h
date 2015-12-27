#pragma once

class Packet;

namespace RakNet
{
	struct RakNetGUID;
};

class PacketSender
{
public:
	virtual ~PacketSender() = 0 {};

	virtual void send(const Packet &) = 0;
	virtual void send(const RakNet::RakNetGUID &, const Packet &) = 0;
	virtual void sendBroadcast(const RakNet::RakNetGUID &, const Packet &) = 0;
};

