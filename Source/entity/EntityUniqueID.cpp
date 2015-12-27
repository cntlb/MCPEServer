#include "entity/EntityUniqueID.h"

EntityUniqueID &EntityUniqueID::operator = (long long &&id)
{
	this->id = id;
	return *this;
}