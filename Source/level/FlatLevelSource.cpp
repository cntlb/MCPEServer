#include "level/FlatLevelSource.h"

std::string FlatLevelSource::DEFAULT_LAYERS = "[8,3,3,2]";

FlatLevelSource::FlatLevelSource(Level *level, Dimension *dimension, const std::string &layers)
	: ChunkSource(level, dimension, 16)
{

}

void FlatLevelSource::requestChunk(const ChunkPos &pos, ChunkSource::LoadMode mode)
{

}

bool FlatLevelSource::postProcess(ChunkViewSource &source)
{
	return true;
}

void FlatLevelSource::loadChunk(LevelChunk &chunk)
{

}