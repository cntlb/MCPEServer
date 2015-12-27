#pragma once

#include <string>
#include <vector>

#include "network/packet/Packet.h"

enum MessageType : char
{
	MESSAGE_RAW,
	MESSAGE_CHAT,
	MESSAGE_TRANSLATION,
	MESSAGE_POPUP,
	MESSAGE_TIP,
	MESSAGE_SYSTEM
};

class TextPacket : public Packet
{
public:
	char type;
	std::string source;
	std::string message;
	std::vector<std::string> params;

	TextPacket();

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);
	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};