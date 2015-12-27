#pragma once

class Level;
class Dimension;
class ChunkSource;

class BlockSource
{
public:
	BlockSource(Level *level, Dimension *dimension, ChunkSource *chunkSource, bool, bool);
};