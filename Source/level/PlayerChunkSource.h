#pragma once

#include "ChunkViewSource.h"

class Player;
class Vec3;

class PlayerChunkSource : public ChunkViewSource
{
private:
	Player *player;
	int radius;

public:
	PlayerChunkSource(Player *player, ChunkSource &source, int radius);

	void center(float center);
	void centerAt(const Vec3 &pos, float center);

	int getRadius() const;
	void setRadius(int radius);
};