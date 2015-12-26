#pragma once

#include <string>
#include <vector>

#include "UUID.h"
#include "entity/EntityUniqueID.h"
#include "gamemode/GameType.h"
#include "level/GeneratorType.h"
#include "level/dimension/DimensionId.h"
#include "block/BlockPos.h"
#include "util/Vec3.h"

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

	virtual unsigned char getId() const = 0;

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

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);

	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};

class PlayStatusPacket : public Packet
{
public:
	enum PlayStatus
	{
		LOGIN_SUCCESS,
		LOGIN_FAILED_CLIENT,
		LOGIN_FAILED_SERVER,
		PLAYER_SPAWN
	};

	PlayStatus status;

	PlayStatusPacket();
	PlayStatusPacket(PlayStatus status);

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);

	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};

class DisconnectPacket : public Packet
{
public:
	std::string message;

	DisconnectPacket();
	DisconnectPacket(const std::string &message);

	unsigned char getId() const;

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

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);

	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);

	void add(const Packet *packet);
	void compress();
};

class TextPacket : public Packet
{
public:
	enum MessageType : char
	{
		RAW,
		CHAT,
		TRANSLATION,
		POPUP,
		TIP,
		SYSTEM
	};

	MessageType type;
	std::string source;
	std::string message;
	std::vector<std::string> params;

	TextPacket();
	TextPacket(MessageType type);

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);

	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};

class SetTimePacket : public Packet
{
public:
	int time;
	bool started;

	SetTimePacket();
	SetTimePacket(int time);

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);

	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};

class StartGamePacket : public Packet
{
public:
	int seed;
	DimensionId dimensionId;
	GeneratorType generatorType;
	BlockPos spawnPos;
	GameType gametype;
	bool creative;
	int stopTime;
	int what;
	EntityUniqueID uniqueID;
	Vec3 pos;

	StartGamePacket();

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);

	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};

class PlayerActionPacket : public Packet
{
public:
	enum PlayerAction
	{
		START_BREAK,
		ABORT_BREAK,
		STOP_BREAK,

		RELEASE_ITEM = 5,
		STOP_SLEEPING,
		RESPAWN,
		JUMP,
		START_SPRINT,
		STOP_SPRINT,
		START_SNEAK,
		STOP_SNEAK,
		DIMENSION_CHANGE
	};

	BlockPos pos;
	int face;
	PlayerAction action;
	int what;
	EntityUniqueID uniqueID;

	PlayerActionPacket();
	PlayerActionPacket(PlayerAction action, EntityUniqueID uniqueID, BlockPos pos, int face);

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);

	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};

class SetSpawnPositionPacket : public Packet
{
public:
	BlockPos pos;

	SetSpawnPositionPacket();
	SetSpawnPositionPacket(const BlockPos &pos);

	unsigned char getId() const;

	void write(RakNet::BitStream *bs) const;
	void read(RakNet::BitStream *bs);

	void handle(const RakNet::RakNetGUID &guid, NetServerHandler *handler);
};