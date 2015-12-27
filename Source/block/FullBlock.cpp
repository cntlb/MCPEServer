#include "block/FullBlock.h"

FullBlock::FullBlock()
{
	damage = 0;
}

FullBlock::FullBlock(const BlockID &id, unsigned char damage)
{
	this->id = id;
	this->damage = damage;
}