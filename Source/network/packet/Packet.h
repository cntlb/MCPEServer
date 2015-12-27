#pragma once

namespace RakNet
{
	class BitStream;
	struct RakNetGUID;
};

class NetServerHandler;

class Packet
{
public:
	int priority;
	int reliability;
	bool b;

	Packet();
	virtual ~Packet();

	virtual unsigned char getId() const = 0;

	virtual void write(RakNet::BitStream *) const = 0;
	virtual void read(RakNet::BitStream *) = 0;

	virtual void handle(const RakNet::RakNetGUID &, NetServerHandler *) = 0;
};