#pragma once

#include "network/packet/Packet.h"

class SetDifficultyPacket : public Packet
{
public:
	int difficulty;

	SetDifficultyPacket();

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);
	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};