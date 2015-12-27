#include "level/dimension/NormalDimension.h"

NormalDimension::NormalDimension(Level *level)
	: Dimension(level, DIMENSION_NORMAL)
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