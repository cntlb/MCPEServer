#pragma once

#include "network/packet/Packet.h"

class SetTimePacket : public Packet
{
public:
	int time;
	bool started;

	SetTimePacket();

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);
	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};