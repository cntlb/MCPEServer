#include "network/packet/BatchPacket.h"
#include "network/MinecraftPackets.h"

#include "leveldb/zlib_compressor.h"
#include "BitStream.h"

leveldb::ZlibCompressor *BatchPacket::mCompressor = new leveldb::ZlibCompressor;

BatchPacket::BatchPacket()
{
	i = 0;
}

unsigned char BatchPacket::getId() const
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
		if (bs->ReadBits(out, 32))
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
		pkbs.ReadBits((unsigned char *)&pkId, 8);

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