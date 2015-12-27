#pragma once

#include "network/packet/Packet.h"

#include "block/BlockPos.h"

class SetSpawnPositionPacket : public Packet
{
public:
	BlockPos pos;

	SetSpawnPositionPacket();

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);
	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};