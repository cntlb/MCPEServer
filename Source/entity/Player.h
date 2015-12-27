#pragma once

#include "entity/Mob.h"

#include "RakNetTypes.h"

class ChunkSource;

class Player : public Mob
{
public:
	RakNet::RakNetGUID guid;

public:
	Player(Level *level);
	~Player();

	void prepareRegion(ChunkSource &chunkSource);
};

