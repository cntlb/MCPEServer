#include "entity/Entity.h"

Entity::Entity(Level *level)
{

}

Entity::Entity(BlockSource *region)
{

}

Entity::~Entity()
{

}

void Entity::_postInit()
{

}

void Entity::reset()
{

}

void Entity::remove()
{

}


void Entity::setPos(const Vec3 &pos)
{

}

const Vec3 &Entity::getPos() const
{
	return pos;
}

const Vec3 &Entity::getPosOld() const
{
	return oldPos;
}


const Vec3 &Entity::getVelocity() const
{
	return motion;
}


void Entity::move(const Vec3 &pos)
{
	
}

void Entity::moveRelative(float x, float y, float z)
{

}


BlockSource *Entity::getRegion() const
{
	return region;
}

Dimension *Entity::getDimension() const
{
	return NULL;
}
