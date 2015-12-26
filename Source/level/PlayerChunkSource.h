#pragma once

#include "ChunkViewSource.h"

class Player;

class PlayerChunkSource : public ChunkViewSource
{
private:
	Player *player;
	int radius;

public:
	PlayerChunkSource(Player *player, ChunkSource &source, int radius);
};