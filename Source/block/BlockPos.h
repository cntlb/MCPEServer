#pragma once

class ChunkPos;
class Vec3;

class BlockPos
{
public:
	int x, y, z;

public:
	BlockPos();
	BlockPos(int x, int y, int z);
	BlockPos(const ChunkPos &pos, int y);
	BlockPos(const Vec3 &vec3);
	BlockPos(float x, float y, float z);
};
