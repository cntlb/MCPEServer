#pragma once

class BlockPos;
class Vec3;

class ChunkPos
{
public:
	int x, z;

	ChunkPos(const BlockPos &pos);
	ChunkPos(const Vec3 &vec3);
};
