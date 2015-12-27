#include "level/dimension/HellDimension.h"

HellDimension::HellDimension(Level *level)
	: Dimension(level, DIMENSION_HELL)
{

}

void HellDimension::init()
{
	Dimension::init();

	setUltraWarm(true);
	setCeiling(true);
}

void HellDimension::updateLightRamp()
{

}

bool HellDimension::isNaturalDimension() const
{
	return false;
}

bool HellDimension::isValidSpawn(int x, int z) const
{
	return false;
}

Color HellDimension::getFogColor(float) const
{
	return Color::RED;
}

float HellDimension::getFogDistanceScale() const
{
	return 0.4f;
}

bool HellDimension::isFoggyAt(int x, int z) const
{
	return true;
}

bool HellDimension::mayRespawn() const
{
	return false;
}

std::string HellDimension::getName() const
{
	return "Nether";
}

void HellDimension::getTimeOfDay(int, float) const
{

}