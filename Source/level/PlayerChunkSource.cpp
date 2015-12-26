#include "PlayerChunkSource.h"

PlayerChunkSource::PlayerChunkSource(Player *player, ChunkSource &source, int radius)
	: ChunkViewSource(source, MODE1)
{
	this->player = player;
	this->radius = radius;
}