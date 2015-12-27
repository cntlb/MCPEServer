#include "network/packet/SetSpawnPositionPacket.h"

#include "BitStream.h"

SetSpawnPositionPacket::SetSpawnPositionPacket()
{
}

unsigned char SetSpawnPositionPacket::getId() const
{
	return 35;
}

void SetSpawnPositionPacket::write(RakNet::BitStream *bs) const
{
	unsigned char id = getId() - 114;
	bs->WriteBits(&id, 8);

	if (RakNet::BitStream::IsNetworkOrderInternal())
	{
		bs->WriteBits((unsigned char *)&pos.x, 32);
		bs->WriteBits((unsigned char *)&pos.y, 32);
		bs->WriteBits((unsigned char *)&pos.z, 32);
	}
	else
	{
		unsigned char out[4];
		RakNet::BitStream::ReverseBytes((unsigned char *)&pos.x, out, 4);
		bs->WriteBits(out, 32);

		RakNet::BitStream::ReverseBytes((unsigned char *)&pos.y, out, 4);
		bs->WriteBits(out, 32);

		RakNet::BitStream::ReverseBytes((unsigned char *)&pos.z, out, 4);
		bs->WriteBits(out, 32);
	}
}

void SetSpawnPositionPacket::read(RakNet::BitStream *bs)
{
	if (RakNet::BitStream::IsNetworkOrderInternal())
	{
		bs->ReadBits((unsigned char *)&pos.x, 32);
		bs->ReadBits((unsigned char *)&pos.y, 32);
		bs->ReadBits((unsigned char *)&pos.z, 32);
	}
	else
	{
		unsigned char out[4];
		if (bs->ReadBits(out, 32))
			RakNet::BitStream::ReverseBytes(out, (unsigned char *)&pos.x, 4);

		if (bs->ReadBits(out, 32))
			RakNet::BitStream::ReverseBytes(out, (unsigned char *)&pos.y, 4);

		if (bs->ReadBits(out, 32))
			RakNet::BitStream::ReverseBytes(out, (unsigned char *)&pos.z, 4);
	}
}

void SetSpawnPositionPacket::handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler)
{
}