#include "network/NetworkStructures.h"

#include "BitStream.h"

#include "network/PacketUtil.h"
#include "network/NetServerHandler.h"
#include "network/MinecraftPackets.h"

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

PlayStatusPacket::PlayStatusPacket(PlayStatus status)
{
	this->status = status;
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


DisconnectPacket::DisconnectPacket()
{

}

DisconnectPacket::DisconnectPacket(const std::string &message)
{
	this->message = message;
}

unsigned char DisconnectPacket::getId() const
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


TextPacket::TextPacket()
{

}

TextPacket::TextPacket(MessageType type)
{
	this->type = type;
}

unsigned char TextPacket::getId() const
{
	return 5;
}

void TextPacket::write(RakNet::BitStream *bs) const
{
	unsigned char id = getId() - 114;
	bs->WriteBits(&id, 8);

	bs->WriteBits((unsigned char *)&type, 8);

	switch (type)
	{
	case MessageType::POPUP:
	case MessageType::CHAT:
		PacketUtil::writeString(source, bs);
	case MessageType::RAW:
	case MessageType::TIP:
	case MessageType::SYSTEM:
		PacketUtil::writeString(message, bs);
		break;
	case MessageType::TRANSLATION:
		PacketUtil::writeString(message, bs);

		size_t count = params.size();
		bs->WriteBits((unsigned char *)&count, 8);

		for (const std::string param : params)
			PacketUtil::writeString(param, bs);
		break;
	}
}

void TextPacket::read(RakNet::BitStream *bs)
{
	bs->ReadBits((unsigned char *)&type, 8);

	switch (type)
	{
	case MessageType::POPUP:
	case MessageType::CHAT:
		PacketUtil::readString(bs, source);
	case MessageType::RAW:
	case MessageType::TIP:
	case MessageType::SYSTEM:
		PacketUtil::readString(bs, message);
		break;
	case MessageType::TRANSLATION:
		PacketUtil::readString(bs, message);

		unsigned char count;
		bs->ReadBits(&count, 8);

		for (int i = 0; i < count; i++)
		{
			std::string param;
			PacketUtil::readString(bs, param);

			params.push_back(param);
		}
	}
}

void TextPacket::handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler)
{
	handler->handle(guid, this);
}


SetTimePacket::SetTimePacket()
{

}

SetTimePacket::SetTimePacket(int time)
{
	this->time = time;
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


PlayerActionPacket::PlayerActionPacket()
{

}

PlayerActionPacket::PlayerActionPacket(PlayerAction action, EntityUniqueID uniqueID, BlockPos pos, int face)
{
	this->action = action;
	this->uniqueID = uniqueID;
	this->pos = pos;
	this->face = face;
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


SetSpawnPositionPacket::SetSpawnPositionPacket()
{

}

SetSpawnPositionPacket::SetSpawnPositionPacket(const BlockPos &pos)
{
	this->pos = pos;
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