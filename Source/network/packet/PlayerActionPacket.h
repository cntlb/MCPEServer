#pragma once

#include "network/packet/Packet.h"

#include "block/BlockPos.h"
#include "entity/EntityUniqueID.h"

enum PlayerAction
{
	ACTION_START_BREAK,
	ACTION_ABORT_BREAK,
	ACTION_STOP_BREAK,

	ACTION_RELEASE_ITEM = 5,
	ACTION_STOP_SLEEPING,
	ACTION_RESPAWN,
	ACTION_JUMP,
	ACTION_START_SPRINT,
	ACTION_STOP_SPRINT,
	ACTION_START_SNEAK,
	ACTION_STOP_SNEAK,
	ACTION_DIMENSION_CHANGE
};

class PlayerActionPacket : public Packet
{
public:
	BlockPos pos;
	int face;
	int action;
	int what;
	EntityUniqueID uniqueID;

	PlayerActionPacket();

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);
	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};