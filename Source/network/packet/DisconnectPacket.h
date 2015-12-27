#pragma once

#include <string>

#include "network/packet/Packet.h"

class DisconnectPacket : public Packet
{
public:
	std::string message;

	DisconnectPacket();

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);
	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};