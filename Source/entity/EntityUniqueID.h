#pragma once

class EntityUniqueID
{
public:
	long long id;

	EntityUniqueID &operator = (long long &&id);
};
