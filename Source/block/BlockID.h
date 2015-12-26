#pragma once

#include "block/BlockProperty.h"

class BlockID
{
public:
	static BlockID AIR;

	unsigned char id;

	BlockID();
	BlockID(unsigned char id);
	BlockID(const BlockID &other);

	bool hasProperty(BlockProperty property);
};