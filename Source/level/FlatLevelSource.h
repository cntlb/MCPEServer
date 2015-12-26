#pragma once

#include "level/ChunkSource.h"

class FlatLevelSource : public ChunkSource
{
public:
	static std::string DEFAULT_LAYERS;

	FlatLevelSource(Level *level, Dimension *dimension, const std::string &layers);

	void requestChunk(const ChunkPos &pos, ChunkSource::LoadMode mode);

	bool postProcess(ChunkViewSource &source);

	void loadChunk(LevelChunk &chunk);
};