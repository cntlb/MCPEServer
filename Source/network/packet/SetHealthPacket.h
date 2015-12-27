#pragma once

#include "network/packet/Packet.h"

class SetHealthPacket : public Packet
{
public:
	int health;

	SetHealthPacket();

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);
	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};