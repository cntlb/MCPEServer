#pragma once

#include "level/dimension/Dimension.h"

class HellDimension : public Dimension
{
public:
	HellDimension(Level *level);

	virtual void init();

	virtual void updateLightRamp();

	virtual bool isNaturalDimension() const;
	virtual bool isValidSpawn(int, int) const;

	virtual Color getFogColor(float) const;
	virtual float getFogDistanceScale() const;

	virtual bool isFoggyAt(int, int) const;

	virtual bool mayRespawn() const;

	virtual std::string getName() const;

	virtual void getTimeOfDay(int, float) const;
};