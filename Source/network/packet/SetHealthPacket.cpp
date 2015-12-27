#include "network/packet/SetHealthPacket.h"

#include "BitStream.h"

SetHealthPacket::SetHealthPacket()
{
}

unsigned char SetHealthPacket::getId() const
{
	return 34;
}

void SetHealthPacket::write(RakNet::BitStream *bs) const
{
	unsigned char id = getId() - 114;
	bs->WriteBits(&id, 8);

	if (RakNet::BitStream::IsNetworkOrderInternal())
		bs->WriteBits((unsigned char *)&health, 32);
	else
	{
		unsigned char out[4];
		RakNet::BitStream::ReverseBytes((unsigned char *)&health, out, 4);
		bs->WriteBits(out, 32);
	}
}

void SetHealthPacket::read(RakNet::BitStream *bs)
{
	if (RakNet::BitStream::IsNetworkOrderInternal())
		bs->ReadBits((unsigned char *)&health, 32);
	else
	{
		unsigned char out[4];
		if (bs->ReadBits(out, 32))
			RakNet::BitStream::ReverseBytes(out, (unsigned char *)&health, 4);
	}
}

void SetHealthPacket::handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler)
{
}