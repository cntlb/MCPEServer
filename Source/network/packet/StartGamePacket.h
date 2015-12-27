#pragma once

#include "network/packet/Packet.h"

#include "block/BlockPos.h"
#include "entity/EntityUniqueID.h"
#include "util/Vec3.h"

class StartGamePacket : public Packet
{
public:
	int seed;
	char dimensionId;
	int generatorType;
	BlockPos spawnPos;
	int gametype;
	bool creative;
	int stopTime;
	int what;
	EntityUniqueID uniqueID;
	Vec3 pos;

	StartGamePacket();

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);
	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};