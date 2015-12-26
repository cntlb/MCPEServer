#pragma once

#include "block/BlockID.h"

class FullBlock
{
public:
	static FullBlock AIR;

	BlockID id;
	unsigned char damage;

	FullBlock();
	FullBlock(const BlockID &id, unsigned char damage);
};