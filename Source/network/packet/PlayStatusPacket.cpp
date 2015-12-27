#include "network/packet/PlayStatusPacket.h"

#include "BitStream.h"

PlayStatusPacket::PlayStatusPacket()
{
}

unsigned char PlayStatusPacket::getId() const
{
	return 2;
}

void PlayStatusPacket::write(RakNet::BitStream *bs) const
{
	unsigned char id = getId() - 114;
	bs->WriteBits(&id, 8);

	if (RakNet::BitStream::IsNetworkOrderInternal())
		bs->WriteBits((unsigned char *)&status, 32);
	else
	{
		unsigned char out[4];
		RakNet::BitStream::ReverseBytes((unsigned char *)&status, out, 4);
		bs->WriteBits(out, 32);
	}
}

void PlayStatusPacket::read(RakNet::BitStream *bs)
{
	if (RakNet::BitStream::IsNetworkOrderInternal())
		bs->ReadBits((unsigned char *)&status, 32);
	else
	{
		unsigned char out[4];
		if (bs->ReadBits(out, 32))
			RakNet::BitStream::ReverseBytes(out, (unsigned char *)&status, 4);
	}
}

void PlayStatusPacket::handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler)
{
}