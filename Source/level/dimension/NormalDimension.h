#pragma once

#include "level/dimension/Dimension.h"

class NormalDimension : public Dimension
{
public:
	NormalDimension(Level *level);

	void init();

	std::string getName() const;
};