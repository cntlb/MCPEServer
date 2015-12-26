#include "level/dimension/NormalDimension.h"

NormalDimension::NormalDimension(Level *level)
	: Dimension(level, DimensionId::NORMAL)
{

}

void NormalDimension::init()
{
	Dimension::init();
}

std::string NormalDimension::getName() const
{
	return "Overworld";
}