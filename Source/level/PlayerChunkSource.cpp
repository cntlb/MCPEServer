#include "level/PlayerChunkSource.h"
#include "entity/Player.h"

PlayerChunkSource::PlayerChunkSource(Player *player, ChunkSource &source, int radius)
	: ChunkViewSource(source, MODE1)
{
	this->player = player;
	this->radius = radius;
}

void PlayerChunkSource::center(float center)
{
	centerAt(player->getPos(), center);
}

void PlayerChunkSource::centerAt(const Vec3 &pos, float center)
{

}

int PlayerChunkSource::getRadius() const
{
	return radius;
}

void PlayerChunkSource::setRadius(int radius)
{
	this->radius = radius;
	center(0.0f);
}