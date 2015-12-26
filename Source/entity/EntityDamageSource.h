#pragma once

#include <string>

#include "entity/EntityDamageCause.h"

class Entity;

class EntityDamageSource
{
public:
	EntityDamageCause cause;

	EntityDamageSource(EntityDamageCause cause);
	virtual ~EntityDamageSource();

	virtual bool isEntitySource() const;
	virtual Entity *getEntity() const;

	virtual bool isChildEntitySource() const;
	virtual Entity *getChildEntity() const;

	virtual bool isBlockSource() const;

	virtual std::string getDeathMessage(std::string, Entity *) const;
	EntityDamageCause getCause() const;
};
