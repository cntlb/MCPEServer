#pragma once

#include <string>

#include "network/packet/Packet.h"

namespace leveldb
{
	class ZlibCompressor;
};

class BatchPacket : public Packet
{
public:
	static leveldb::ZlibCompressor *mCompressor;

	int i;
	std::string payload;
	std::string raw;

	BatchPacket();

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);
	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);

	void add(const Packet *packet);
	void compress();
};