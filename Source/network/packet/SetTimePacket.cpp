#include "network/packet/SetTimePacket.h"

#include "BitStream.h"

SetTimePacket::SetTimePacket()
{
}

unsigned char SetTimePacket::getId() const
{
	return 6;
}

void SetTimePacket::write(RakNet::BitStream *bs) const
{
	unsigned char id = getId() - 114;
	bs->WriteBits(&id, 8);

	if (RakNet::BitStream::IsNetworkOrderInternal())
	{
		bs->WriteBits((unsigned char *)&time, 32);
		bs->WriteBits((unsigned char *)&started, 8);
	}
	else
	{
		unsigned char out[4];
		RakNet::BitStream::ReverseBytes((unsigned char *)&time, out, 4);
		bs->WriteBits(out, 32);

		bs->WriteBits((unsigned char *)&started, 8);
	}
}

void SetTimePacket::read(RakNet::BitStream *bs)
{
	if (RakNet::BitStream::IsNetworkOrderInternal())
	{
		bs->ReadBits((unsigned char *)&time, 32);
		bs->ReadBits((unsigned char *)&started, 8);
	}
	else
	{
		unsigned char out[4];
		if (bs->ReadBits(out, 32))
			RakNet::BitStream::ReverseBytes(out, (unsigned char *)&time, 4);

		bs->ReadBits((unsigned char *)&started, 8);
	}
}

void SetTimePacket::handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler)
{
}