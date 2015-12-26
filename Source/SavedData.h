#pragma once

class CompoundTag;

class SavedData
{
public:
	virtual ~SavedData() = 0 {}

	virtual void load(const CompoundTag &tag) = 0;
	virtual void save(CompoundTag &tag) = 0;
};