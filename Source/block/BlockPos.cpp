#include <cmath>

#include "block/BlockPos.h"

#include "level/ChunkPos.h"
#include "util/Vec3.h"

BlockPos::BlockPos()
{
	x = 0;
	y = 0;
	z = 0;
}

BlockPos::BlockPos(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

BlockPos::BlockPos(const ChunkPos &pos, int y)
{
	x = pos.x << 4;
	z = pos.z << 4;
	this->y = y;
}

BlockPos::BlockPos(const Vec3 &vec3)
{
	BlockPos(vec3.x, vec3.y, vec3.z);
}

BlockPos::BlockPos(float x, float y, float z)
{
	this->x = (int)floorf(x);
	this->y = (int)floorf(y);
	this->z = (int)floorf(z);
}