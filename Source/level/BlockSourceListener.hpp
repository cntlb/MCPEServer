#pragma once

#include <memory>

#include "block/FullBlock.h"
#include "blockentity/BlockEntity.h"

class BlockSource;
class BlockPos;

class BlockSourceListener
{
public:
	virtual ~BlockSourceListener() = 0 {}
	virtual void onSourceCreated(BlockSource &region) {}
	virtual void onSourceDestroyed(BlockSource &region) {}
	virtual void onBlocksDirty(BlockSource &region, int, int, int, int, int, int) {}
	virtual void onAreaChanged(BlockSource &region, const BlockPos &start, BlockPos const &end) {}
	virtual void onBlockChanged(BlockSource &region, const BlockPos &pos, FullBlock oldBlock, FullBlock newBlock, int update) {}
	virtual void onBrightnessChanged(BlockSource &region, const BlockPos &pos) {}
	virtual void onBlockEntityChanged(BlockSource &region, BlockEntity &entity) {}
	virtual void onBlockEntityRemoved(BlockSource &region, std::unique_ptr<BlockEntity> entity) {}
	virtual void onBlockEvent(BlockSource &region, int, int, int, int, int) {}
};
