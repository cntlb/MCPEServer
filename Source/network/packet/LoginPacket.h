#pragma once

#include <string>

#include "network/packet/Packet.h"
#include "UUID.h"

class LoginPacket : public Packet
{
public:
	std::string username;
	std::string clientSecret;
	std::string serverAddress;
	long long clientId;
	mce::UUID clientUUID;
	int protocol1;
	int protocol2;
	std::string skinName;
	std::string skin;

	LoginPacket();

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);
	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};