#include "entity/Mob.h"

Mob::Mob(Level *level)
	: Entity(level)
{

}

Mob::Mob(BlockSource *region)
	: Entity(region)
{

}

Mob::~Mob()
{

}
