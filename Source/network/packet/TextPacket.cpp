#include "network/packet/TextPacket.h"
#include "network/PacketUtil.h"
#include "network/NetServerHandler.h"

#include "BitStream.h"

TextPacket::TextPacket()
{
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
	case MESSAGE_POPUP:
	case MESSAGE_CHAT:
		PacketUtil::writeString(source, bs);
	case MESSAGE_RAW:
	case MESSAGE_TIP:
	case MESSAGE_SYSTEM:
		PacketUtil::writeString(message, bs);
		break;
	case MESSAGE_TRANSLATION:
		PacketUtil::writeString(message, bs);

		unsigned char count = (unsigned char)params.size();
		bs->WriteBits(&count, 8);
		
		for (const std::string &param : params)
			PacketUtil::writeString(param, bs);
		break;
	}
}

void TextPacket::read(RakNet::BitStream *bs)
{
	bs->ReadBits((unsigned char *)&type, 8);

	switch (type)
	{
	case MESSAGE_POPUP:
	case MESSAGE_CHAT:
		PacketUtil::readString(bs, source);
	case MESSAGE_RAW:
	case MESSAGE_TIP:
	case MESSAGE_SYSTEM:
		PacketUtil::readString(bs, message);
		break;
	case MESSAGE_TRANSLATION:
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