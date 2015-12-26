#include "level/ChunkSource.h"

ChunkSource::ChunkSource(Level *level, Dimension *dimension, int chunkSide)
{
	this->chunkSide = chunkSide;
	this->level = level;
	this->dimension = dimension;
}

ChunkSource::ChunkSource(std::unique_ptr<ChunkSource> source)
{

}

ChunkSource::ChunkSource(ChunkSource &source)
{

}

ChunkSource::~ChunkSource()
{

}

void ChunkSource::getExistingChunk(const ChunkPos &pos)
{

}

void ChunkSource::requestChunk(const ChunkPos &pos, LoadMode mode)
{

}

void ChunkSource::releaseChunk(LevelChunk &chunk)
{

}

bool ChunkSource::postProcess(ChunkViewSource &source)
{
	return true;
}

void ChunkSource::loadChunk(LevelChunk &chunk)
{

}

void ChunkSource::postProcessMobsAt(BlockSource *region, int i1, int i2, Random &random)
{

}

void ChunkSource::getMobsAt(BlockSource &region, EntityType type, const BlockPos &pos)
{

}

void ChunkSource::saveLiveChunk(LevelChunk &chunk)
{

}

void ChunkSource::hintDiscardBatchBegin()
{

}

void ChunkSource::hintDiscardBatchEnd()
{

}

void ChunkSource::acquireDiscarded(std::unique_ptr<LevelChunk> &&chunk)
{

}

void ChunkSource::getStoredChunks() const
{

}

void ChunkSource::getStoredChunks()
{

}

void ChunkSource::compact()
{

}

void ChunkSource::waitDiscardFinished()
{

}

void ChunkSource::getView(const BlockPos &pos1, const BlockPos &pos2, LoadMode mode, bool b, const std::function<void(LevelChunk *&)> &f)
{

}

Level *ChunkSource::getLevel() const
{
	return level;
}

Dimension *ChunkSource::getDimension() const
{
	return dimension;
}