#include "network/packet/StartGamePacket.h"

#include "BitStream.h"

StartGamePacket::StartGamePacket()
{
}

unsigned char StartGamePacket::getId() const
{
	return 7;
}

void StartGamePacket::write(RakNet::BitStream *bs) const
{
	unsigned char id = getId() - 114;
	bs->WriteBits(&id, 8);

	if (RakNet::BitStream::IsNetworkOrderInternal())
	{
		bs->WriteBits((unsigned char *)&seed, 32);
		bs->WriteBits((unsigned char *)&dimensionId, 8);
		bs->WriteBits((unsigned char *)&generatorType, 32);
		bs->WriteBits((unsigned char *)&gametype, 32);
		bs->WriteBits((unsigned char *)&uniqueID, 64);
		bs->WriteBits((unsigned char *)&spawnPos.x, 32);
		bs->WriteBits((unsigned char *)&spawnPos.y, 32);
		bs->WriteBits((unsigned char *)&spawnPos.z, 32);
		bs->WriteBits((unsigned char *)&pos.x, 32);
		bs->WriteBits((unsigned char *)&pos.y, 32);
		bs->WriteBits((unsigned char *)&pos.z, 32);
		bs->WriteBits((unsigned char *)&creative, 8);
		bs->WriteBits((unsigned char *)&stopTime, 32);
	}
	else
	{
		unsigned char out1[4];
		RakNet::BitStream::ReverseBytes((unsigned char *)&seed, out1, 4);
		bs->WriteBits(out1, 32);

		bs->WriteBits((unsigned char *)&dimensionId, 8);

		RakNet::BitStream::ReverseBytes((unsigned char *)&generatorType, out1, 4);
		bs->WriteBits(out1, 32);

		RakNet::BitStream::ReverseBytes((unsigned char *)&gametype, out1, 4);
		bs->WriteBits(out1, 32);

		unsigned char out2[8];
		RakNet::BitStream::ReverseBytes((unsigned char *)&uniqueID, out2, 8);
		bs->WriteBits(out2, 64);

		RakNet::BitStream::ReverseBytes((unsigned char *)&spawnPos.x, out1, 4);
		bs->WriteBits(out1, 32);

		RakNet::BitStream::ReverseBytes((unsigned char *)&spawnPos.y, out1, 4);
		bs->WriteBits(out1, 32);

		RakNet::BitStream::ReverseBytes((unsigned char *)&spawnPos.z, out1, 4);
		bs->WriteBits(out1, 32);

		RakNet::BitStream::ReverseBytes((unsigned char *)&pos.x, out1, 4);
		bs->WriteBits(out1, 32);

		RakNet::BitStream::ReverseBytes((unsigned char *)&pos.y, out1, 4);
		bs->WriteBits(out1, 32);

		RakNet::BitStream::ReverseBytes((unsigned char *)&pos.z, out1, 4);
		bs->WriteBits(out1, 32);

		bs->WriteBits((unsigned char *)&creative, 8);

		RakNet::BitStream::ReverseBytes((unsigned char *)&stopTime, out1, 4);
		bs->WriteBits(out1, 32);
	}
}

void StartGamePacket::read(RakNet::BitStream *bs)
{
}

void StartGamePacket::handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler)
{
}