#include "network/packet/PlayerActionPacket.h"
#include "network/NetServerHandler.h"

#include "BitStream.h"

PlayerActionPacket::PlayerActionPacket()
{
}

unsigned char PlayerActionPacket::getId() const
{
	return 29;
}

void PlayerActionPacket::write(RakNet::BitStream *bs) const
{
	unsigned char id = getId() - 114;
	bs->WriteBits(&id, 8);

	if (RakNet::BitStream::IsNetworkOrderInternal())
	{
		bs->WriteBits((unsigned char *)&uniqueID, 64);
		bs->WriteBits((unsigned char *)&action, 32);
		bs->WriteBits((unsigned char *)&pos.x, 32);
		bs->WriteBits((unsigned char *)&pos.y, 32);
		bs->WriteBits((unsigned char *)&pos.z, 32);
		bs->WriteBits((unsigned char *)&face, 32);
	}
	else
	{
		unsigned char out1[8];
		RakNet::BitStream::ReverseBytes((unsigned char *)&uniqueID, out1, 8);
		bs->WriteBits(out1, 64);

		unsigned char out2[4];
		RakNet::BitStream::ReverseBytes((unsigned char *)&action, out2, 4);
		bs->WriteBits(out2, 32);

		RakNet::BitStream::ReverseBytes((unsigned char *)&pos.x, out2, 4);
		bs->WriteBits(out2, 32);

		RakNet::BitStream::ReverseBytes((unsigned char *)&pos.y, out2, 4);
		bs->WriteBits(out2, 32);

		RakNet::BitStream::ReverseBytes((unsigned char *)&pos.z, out2, 4);
		bs->WriteBits(out2, 32);

		RakNet::BitStream::ReverseBytes((unsigned char *)&face, out2, 4);
		bs->WriteBits(out2, 32);
	}
}

void PlayerActionPacket::read(RakNet::BitStream *bs)
{
	if (RakNet::BitStream::IsNetworkOrderInternal())
	{
		bs->ReadBits((unsigned char *)&uniqueID, 64);
		bs->ReadBits((unsigned char *)&action, 32);
		bs->ReadBits((unsigned char *)&pos.x, 32);
		bs->ReadBits((unsigned char *)&pos.y, 32);
		bs->ReadBits((unsigned char *)&pos.z, 32);
		bs->ReadBits((unsigned char *)&face, 32);
	}
	else
	{
		unsigned char out1[8];
		if (bs->ReadBits(out1, 64))
			RakNet::BitStream::ReverseBytes(out1, (unsigned char *)&uniqueID, 8);

		unsigned char out2[4];
		if (bs->ReadBits(out2, 32))
			RakNet::BitStream::ReverseBytes(out2, (unsigned char *)&action, 4);

		if (bs->ReadBits(out2, 32))
			RakNet::BitStream::ReverseBytes(out2, (unsigned char *)&pos.x, 4);

		if (bs->ReadBits(out2, 32))
			RakNet::BitStream::ReverseBytes(out2, (unsigned char *)&pos.y, 4);

		if (bs->ReadBits(out2, 32))
			RakNet::BitStream::ReverseBytes(out2, (unsigned char *)&pos.z, 4);

		if (bs->ReadBits(out2, 32))
			RakNet::BitStream::ReverseBytes(out2, (unsigned char *)&face, 4);
	}
}

void PlayerActionPacket::handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler)
{
	handler->handle(guid, this);
}