#include "network/packet/DisconnectPacket.h"
#include "network/PacketUtil.h"

#include "BitStream.h"

DisconnectPacket::DisconnectPacket()
{
}

unsigned char DisconnectPacket::getId() const
{
	return 3;
}

void DisconnectPacket::write(RakNet::BitStream *bs) const
{
	unsigned char id = getId() - 114;
	bs->WriteBits((unsigned char *)&id, 8);

	PacketUtil::writeString(message, bs);
}

void DisconnectPacket::read(RakNet::BitStream *bs)
{
	PacketUtil::readString(bs, message);
}

void DisconnectPacket::handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler)
{
}