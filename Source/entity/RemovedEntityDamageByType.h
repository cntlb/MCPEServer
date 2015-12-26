#pragma once

#include "entity/EntityDamageSource.h"

#include "entity/EntityType.h"

class RemovedEntityDamageByType : public EntityDamageSource
{
public:
	RemovedEntityDamageByType(EntityDamageCause cause, EntityType type);
	virtual ~RemovedEntityDamageByType();
	virtual std::string getDeathMessage(std::string, Entity *) const;
};
