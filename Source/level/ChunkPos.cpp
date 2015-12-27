#include "level/ChunkPos.h"

#include "block/BlockPos.h"
#include "util/Vec3.h"

ChunkPos::ChunkPos(const BlockPos &pos)
{
	x = pos.x >> 4;
	z = pos.z >> 4;
}

ChunkPos::ChunkPos(const Vec3 &vec3)
{
	ChunkPos(BlockPos(vec3.x, vec3.y, vec3.z));
}