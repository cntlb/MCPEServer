#pragma once

#include <string>
#include <memory>

#include "level/LevelListener.hpp"
#include "SavedData.h"

#include "level/dimension/DimensionId.h"
#include "level/GeneratorType.h"

#include "util/Color.h"

#include "block/FullBlock.h"

class Level;
class BlockSource;
class BlockPos;
class Player;
class LevelChunk;
class CompoundTag;
class ChunkSource;
class Packet;
class MoveEntityPacketData;
class Entity;

class Dimension : public LevelListener, public SavedData
{
private:
	Level *level;
	DimensionId id;

	bool ultrawarm;
	bool ceiling;

public:
	static std::unique_ptr<Dimension> createNew(DimensionId id, Level *level);

	Dimension(Level *level, DimensionId id);
	virtual ~Dimension();

	std::unique_ptr<ChunkSource> _createGenerator(GeneratorType type);

	virtual void onBlockChanged(BlockSource &, BlockPos const &, FullBlock, FullBlock, int);
	virtual void onBlockEvent(BlockSource &, int, int, int, int, int);
	virtual void onNewChunkFor(Player &, LevelChunk &);

	virtual void init();

	virtual void tick();
	virtual void updateLightRamp();

	virtual bool isNaturalDimension() const;
	virtual bool isValidSpawn(int x, int z) const;

	virtual Color getFogColor(float) const;
	virtual float getFogDistanceScale() const;
	virtual bool isFoggyAt(int x, int z) const;

	virtual float getCloudHeight() const;

	virtual bool mayRespawn() const;
	virtual bool hasGround() const;

	virtual void getSpawnYPosition();

	virtual bool hasBedrockFog();
	virtual float getClearColorScale();

	virtual std::string getName() const = 0;

	virtual void load(const CompoundTag &);
	virtual void save(CompoundTag &);

	virtual void sendDimensionPackets();
	virtual void sendBroadcast(const Packet &packet, Player *player);

	virtual void addMoveEntityPacket(const MoveEntityPacketData &);
	virtual void addSetEntityMotionPacket(Entity &entity);

	virtual void getTimeOfDay(int, float) const;

	ChunkSource *getChunkSource() const;

	void setCeiling(bool value);
	void setUltraWarm(bool value);

	Level *getLevel() const;
	Level *getLevelCount() const;
	DimensionId getId() const;

	int getHeight() const;
	bool isDay() const;
};