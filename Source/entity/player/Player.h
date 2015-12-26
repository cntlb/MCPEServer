#pragma once

#include "entity\Mob.h"

class Player :
	public Mob
{
public:
	Player(Level *level);
	~Player();
};

