#pragma once

#include <string>

#include "BitStream.h"

#include "UUID.h"

class PacketUtil
{
public:
	static void writeString(const std::string &str, RakNet::BitStream *bs)
	{
		unsigned short length = str.length();

		if (bs->IsNetworkOrderInternal())
			bs->WriteBits((unsigned char *)&length, 16);
		else
		{
			unsigned char out[2];
			RakNet::BitStream::ReverseBytes((unsigned char *)&length, out, 2);
			bs->WriteBits(out, 16);
		}
		bs->Write(str.c_str(), length);
	}

	static void readString(RakNet::BitStream *bs, std::string &str)
	{
		unsigned short length = 0;
		if (RakNet::BitStream::IsNetworkOrderInternal())
			bs->ReadBits((unsigned char *)&length, 16);
		else
		{
			unsigned char out[2];
			if(bs->ReadBits(out, 16))
				RakNet::BitStream::ReverseBytes(out, (unsigned char *)&length, 2);
		}

		char *temp = new char[length];
		bs->Read(temp, length);
		str += std::string(temp, length);
	}

	static void writeUUID(const mce::UUID &uuid, RakNet::BitStream *bs)
	{
		if (RakNet::BitStream::IsNetworkOrderInternal())
		{
			bs->WriteBits((unsigned char *)&uuid.part[0], 64);
			bs->WriteBits((unsigned char *)&uuid.part[1], 64);
		}
		else
		{
			unsigned char out[8];
			RakNet::BitStream::ReverseBytes((unsigned char *)&uuid.part[0], out, 8);
			bs->WriteBits(out, 64);

			RakNet::BitStream::ReverseBytes((unsigned char *)&uuid.part[1], out, 8);
			bs->WriteBits(out, 64);
		}
	}

	static mce::UUID readUUID(RakNet::BitStream *bs)
	{
		mce::UUID uuid;

		if (RakNet::BitStream::IsNetworkOrderInternal())
		{
			bs->ReadBits((unsigned char *)&uuid.part[0], 64);
			bs->ReadBits((unsigned char *)&uuid.part[1], 64);
		}
		else
		{
			unsigned char out[8];
			if(bs->ReadBits(out, 64))
				RakNet::BitStream::ReverseBytes(out, (unsigned char *)&uuid.part[0], 8);

			if (bs->ReadBits(out, 64))
				RakNet::BitStream::ReverseBytes(out, (unsigned char *)&uuid.part[1], 8);
		}
		return uuid;
	}
};