#pragma once

#include "network/packet/Packet.h"

enum PlayStatus
{
	STATUS_LOGIN_SUCCESS,
	STATUS_LOGIN_FAILED_CLIENT,
	STATUS_LOGIN_FAILED_SERVER,
	STATUS_PLAYER_SPAWN
};

class PlayStatusPacket : public Packet
{
public:
	int status;

	PlayStatusPacket();

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);
	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};