#include "network/packet/SetDifficultyPacket.h"

#include "BitStream.h"

SetDifficultyPacket::SetDifficultyPacket()
{
}

unsigned char SetDifficultyPacket::getId() const
{
	return 50;
}

void SetDifficultyPacket::write(RakNet::BitStream *bs) const
{
	unsigned char id = getId() - 114;
	bs->WriteBits(&id, 8);

	if (RakNet::BitStream::IsNetworkOrderInternal())
		bs->WriteBits((unsigned char *)&difficulty, 32);
	else
	{
		unsigned char out[4];
		RakNet::BitStream::ReverseBytes((unsigned char *)&difficulty, out, 4);
		bs->WriteBits(out, 32);
	}
}

void SetDifficultyPacket::read(RakNet::BitStream *bs)
{
	if (RakNet::BitStream::IsNetworkOrderInternal())
		bs->ReadBits((unsigned char *)&difficulty, 32);
	else
	{
		unsigned char out[4];
		if (bs->ReadBits(out, 32))
			RakNet::BitStream::ReverseBytes(out, (unsigned char *)&difficulty, 4);
	}
}

void SetDifficultyPacket::handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler)
{
}