#pragma once

#include <memory>

#include "util/Vec2.h"
#include "util/Vec3.h"

#include "network/NetworkStructures.h"

class Dimension;
class Level;
class BlockSource;

class Entity
{
private:
	Vec3 pos;
	Vec3 oldPos;
	Vec3 motion;
	Vec2 rotation;

	Level *level;
	BlockSource *region;

	bool removed;

public:
	Entity(Level *level);
	Entity(BlockSource *region);
	virtual ~Entity();

	virtual void _postInit();
	virtual void reset();
	virtual void remove();

	virtual void setPos(const Vec3 &pos);
	virtual const Vec3 &getPos() const;
	virtual const Vec3 &getPosOld() const;

	virtual const Vec3 &getVelocity() const;

	virtual void move(const Vec3 &pos);
	virtual void moveRelative(float x, float y, float z);

	BlockSource *getRegion() const;
	Dimension *getDimension() const;
};

