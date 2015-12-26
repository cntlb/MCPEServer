#include "NetworkStructures.h"
#include "BitStream.h"

#include "PacketUtil.h"
#include "NetServerHandler.h"
#include "MinecraftPackets.h"

#include "leveldb/zlib_compressor.h"

Packet::Packet()
{
	priority = MEDIUM_PRIORITY;
	reliability = RELIABLE_ORDERED;
	b1 = false;
}

Packet::~Packet()
{

}


LoginPacket::LoginPacket()
{

}

int LoginPacket::getId() const
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

	PacketUtil::writeUUID(uuid, bs);
	PacketUtil::writeString(serverAddress, bs);
	PacketUtil::writeString(clientSecret, bs);
	PacketUtil::writeString(what, bs);
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

		uuid = PacketUtil::readUUID(bs);
		PacketUtil::readString(bs, serverAddress);
		PacketUtil::readString(bs, clientSecret);
		PacketUtil::readString(bs, what);
		PacketUtil::readString(bs, skin);
	}
	else
		bs->SetReadOffset(bs->GetNumberOfBitsUsed());
}

void LoginPacket::handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler)
{
	handler->handle(guid, this);
}


PlayStatusPacket::PlayStatusPacket()
{

}

int PlayStatusPacket::getId() const
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


DisconnectPacket::DisconnectPacket()
{

}

int DisconnectPacket::getId() const
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


leveldb::ZlibCompressor *BatchPacket::mCompressor = new leveldb::ZlibCompressor(1);

BatchPacket::BatchPacket()
{
	i = 0;
}

int BatchPacket::getId() const
{
	return 4;
}

void BatchPacket::write(RakNet::BitStream *bs) const
{
	unsigned char id = getId() - 114;
	bs->WriteBits(&id, 8);

	int length = payload.length();
	if (RakNet::BitStream::IsNetworkOrderInternal())
		bs->WriteBits((unsigned char *)&length, 32);
	else
	{
		unsigned char out[4];
		RakNet::BitStream::ReverseBytes((unsigned char *)&length, out, 4);
		bs->WriteBits(out, 32);
	}
	bs->Write(payload.c_str(), length);
}

void BatchPacket::read(RakNet::BitStream *bs)
{
	int length;
	if (RakNet::BitStream::IsNetworkOrderInternal())
		bs->ReadBits((unsigned char *)&length, 32);
	else
	{
		unsigned char out[4];
		if(bs->ReadBits(out, 32))
			RakNet::BitStream::ReverseBytes(out, (unsigned char *)&length, 4);
	}

	char *temp = new char[length];
	bs->Read(temp, length);
	payload += std::string(temp, length);
}

void BatchPacket::handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler)
{
	std::string raw;
	mCompressor->decompress(payload.c_str(), payload.length(), raw);

	RakNet::BitStream bs((unsigned char *)raw.c_str(), raw.length(), false);
	while (bs.GetNumberOfBitsUsed() != bs.GetReadOffset())
	{
		int pkLen;
		
		if (RakNet::BitStream::IsNetworkOrderInternal())
			bs.ReadBits((unsigned char *)&pkLen, 32);
		else
		{
			unsigned char out[4];
			if (bs.ReadBits(out, 32))
				RakNet::BitStream::ReverseBytes(out, (unsigned char *)&pkLen, 4);
		}

		RakNet::BitStream pkbs;
		bs.Read(pkbs, pkLen << 3);

		unsigned char pkId;
		pkbs.ReadBits(&pkId, 8);

		std::unique_ptr<Packet> pk;
		if (pk = MinecraftPackets::createPacket(pkId))
		{
			pk->read(&pkbs);
			pk->handle(guid, handler);
		}
		else
			break;
	}
}

void BatchPacket::add(const Packet *packet)
{
	RakNet::BitStream bs;
	packet->write(&bs);
}

void BatchPacket::compress()
{
	mCompressor->compressImpl(raw.c_str(), raw.length(), payload);
	mCompressor->inputBytes += (int)raw.length();
	mCompressor->compressedBytes += (int)payload.length();
}