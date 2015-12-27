#pragma once

#include "entity/EntityDamageSource.h"

class EntityDamageByEntitySource : public EntityDamageSource
{
public:
	Entity *damager;

	EntityDamageByEntitySource(Entity &, EntityDamageCause cause);
	virtual ~EntityDamageByEntitySource();

	virtual bool isEntitySource() const;
	virtual Entity *getEntity() const;

	virtual std::string getDeathMessage(std::string, Entity *) const;
};
