#include "BlockID.h"

BlockID BlockID::AIR = BlockID(0);

BlockID::BlockID()
{
	id = 0;
}

BlockID::BlockID(unsigned char id)
{
	this->id = id;
}

BlockID::BlockID(const BlockID &other)
{
	id = other.id;
}

bool BlockID::hasProperty(BlockProperty property)
{
	return false;
}