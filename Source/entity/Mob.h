#pragma once

#include "Entity.h"

class Mob :
	public Entity
{
public:
	Mob(Level *level);
	Mob(BlockSource *region);
	~Mob();
};

