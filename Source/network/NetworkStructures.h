#pragma once

#include <string>

#include "UUID.h"

#include "PacketPriority.h"

namespace leveldb
{
	class ZlibCompressor;
};

class NetServerHandler;

namespace RakNet
{
	class BitStream;
	struct RakNetGUID;
};

class Packet
{
public:
	PacketPriority priority;
	PacketReliability reliability;
	bool b1;

	Packet();
	virtual ~Packet();

	virtual int getId() const = 0;

	virtual void write(RakNet::BitStream *) const = 0;
	virtual void read(RakNet::BitStream *) = 0;

	virtual void handle(const RakNet::RakNetGUID &, NetServerHandler *) = 0;
};

class LoginPacket : public Packet
{
public:
	std::string username;
	std::string clientSecret;
	std::string serverAddress;
	int filler;
	long long clientId;
	mce::UUID uuid;
	int protocol1;
	int protocol2;
	std::string what;
	bool transparency;
	std::string skin;

	LoginPacket();

	int getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);

	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};

class PlayStatusPacket : public Packet
{
public:
	enum Status
	{
		LOGIN_SUCCESS,
		LOGIN_FAILED_CLIENT,
		LOGIN_FAILED_SERVER,
		PLAYER_SPAWN
	};

	int status;

	PlayStatusPacket();

	int getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);

	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};

class DisconnectPacket : public Packet
{
public:
	std::string message;

	DisconnectPacket();

	int getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);

	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};

class BatchPacket : public Packet
{
public:
	static leveldb::ZlibCompressor *mCompressor;

	int i;
	std::string payload;
	std::string raw;

	BatchPacket();

	int getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);

	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);

	void add(const Packet *packet);
	void compress();
};