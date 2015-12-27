#include "network/packet/LoginPacket.h"
#include "network/PacketUtil.h"
#include "network/NetServerHandler.h"

#include "BitStream.h"

LoginPacket::LoginPacket()
{

}

unsigned char LoginPacket::getId() const
{
	return 1;
}

void LoginPacket::write(RakNet::BitStream *bs) const
{
	unsigned char id = getId() - 114;
	bs->WriteBits(&id, 8);

	PacketUtil::writeString(username, bs);

	if (RakNet::BitStream::IsNetworkOrderInternal())
	{
		bs->WriteBits((unsigned char *)&protocol1, 32);
		bs->WriteBits((unsigned char *)&protocol2, 32);
		bs->WriteBits((unsigned char *)&clientId, 64);
	}
	else
	{
		unsigned char out[2];
		RakNet::BitStream::ReverseBytes((unsigned char *)&protocol1, out, 4);
		bs->WriteBits(out, 32);

		RakNet::BitStream::ReverseBytes((unsigned char *)&protocol2, out, 4);
		bs->WriteBits(out, 32);

		RakNet::BitStream::ReverseBytes((unsigned char *)&clientId, out, 8);
		bs->WriteBits(out, 64);
	}

	PacketUtil::writeUUID(clientUUID, bs);
	PacketUtil::writeString(serverAddress, bs);
	PacketUtil::writeString(clientSecret, bs);
	PacketUtil::writeString(skinName, bs);
	PacketUtil::writeString(skin, bs);
}

void LoginPacket::read(RakNet::BitStream *bs)
{
	PacketUtil::readString(bs, username);
	if (bs->GetNumberOfBitsUsed() != bs->GetReadOffset())
	{
		if (RakNet::BitStream::IsNetworkOrderInternal())
		{
			bs->ReadBits((unsigned char *)&protocol1, 32);
			bs->ReadBits((unsigned char *)&protocol2, 32);
		}
		else
		{
			unsigned char out[4];
			if (bs->ReadBits(out, 32))
				RakNet::BitStream::ReverseBytes(out, (unsigned char *)&protocol1, 4);

			if (bs->ReadBits(out, 32))
				RakNet::BitStream::ReverseBytes(out, (unsigned char *)&protocol2, 4);
		}
	}

	if (protocol1 == 38)
	{
		if (RakNet::BitStream::IsNetworkOrderInternal())
			bs->ReadBits((unsigned char *)&clientId, 64);
		else
		{
			unsigned char out[8];
			if (bs->ReadBits(out, 64))
				RakNet::BitStream::ReverseBytes(out, (unsigned char *)&clientId, 8);
		}

		clientUUID = PacketUtil::readUUID(bs);
		PacketUtil::readString(bs, serverAddress);
		PacketUtil::readString(bs, clientSecret);
		PacketUtil::readString(bs, skinName);
		PacketUtil::readString(bs, skin);
	}
	else
		bs->SetReadOffset(bs->GetNumberOfBitsUsed());
}

void LoginPacket::handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler)
{
	handler->handle(guid, this);
}