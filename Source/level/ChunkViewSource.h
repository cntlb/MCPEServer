#pragma once

#include "level/ChunkSource.h"

class ChunkViewSource : public ChunkSource
{
public:
	ChunkViewSource(ChunkSource &source, LoadMode mode);
};