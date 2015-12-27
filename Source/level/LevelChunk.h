#pragma once

class Level;
class Dimension;
class ChunkPos;

class LevelChunk
{
private:


public:
	LevelChunk(Level *level, Dimension *dimension, const ChunkPos &pos, bool);
};