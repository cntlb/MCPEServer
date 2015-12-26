#pragma once

#include <memory>
#include <functional>

#include "entity/EntityType.h"

class ChunkPos;
class LevelChunk;
class BlockPos;
class BlockSource;
class ChunkViewSource;
class Level;
class Dimension;
class Random;

class ChunkSource
{
private:
	int chunkSide;
	
	Level *level;
	Dimension *dimension;

public:
	enum LoadMode
	{
		MODE0,
		MODE1
	};

	ChunkSource(Level *level, Dimension *dimension, int chunkSide);
	ChunkSource(std::unique_ptr<ChunkSource> source);
	ChunkSource(ChunkSource &source);
	virtual ~ChunkSource();

	virtual void getExistingChunk(const ChunkPos &pos);
	virtual void requestChunk(const ChunkPos &pos, LoadMode mode);
	virtual void releaseChunk(LevelChunk &chunk);

	virtual bool postProcess(ChunkViewSource &source);

	virtual void loadChunk(LevelChunk &chunk);

	virtual void postProcessMobsAt(BlockSource *region, int i1, int i2, Random &random);
	virtual void getMobsAt(BlockSource &region, EntityType type, const BlockPos &pos);

	virtual void saveLiveChunk(LevelChunk &chunk);

	virtual void hintDiscardBatchBegin();
	virtual void hintDiscardBatchEnd();

	virtual void acquireDiscarded(std::unique_ptr<LevelChunk> &&chunk);

	virtual void getStoredChunks() const;
	virtual void getStoredChunks();

	virtual void compact();

	virtual void waitDiscardFinished();

	virtual void getView(const BlockPos &pos1, const BlockPos &pos2, LoadMode mode, bool b, const std::function<void (LevelChunk *&)> &f);

	Level *getLevel() const;
	Dimension *getDimension() const;
};