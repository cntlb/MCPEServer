#pragma once

#include "entity/EntityDamageSource.h"

#include "block/FullBlock.h"

class EntityDamageByBlockSource : public EntityDamageSource
{
public:
	FullBlock block;

	EntityDamageByBlockSource(FullBlock block, EntityDamageCause cause);
	virtual ~EntityDamageByBlockSource();

	virtual bool isBlockSource() const;

	virtual std::string getDeathMessage(std::string, Entity *) const;

	FullBlock getBlock() const;
};
