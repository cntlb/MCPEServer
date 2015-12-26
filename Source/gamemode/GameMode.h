#pragma once

#include <functional>

#include "block/BlockPos.h"

class PacketSender;
class Level;
class Player;
class Entity;
class InputMode;
class ItemInstance;

class GameMode
{
private:
	PacketSender *packetSender;
	Level *level;

public:
	GameMode(PacketSender *packetSender, Level *level);
	virtual ~GameMode();

	void _creativeDestroyBlock(Player &player, BlockPos pos, signed char side);
	void _destroyBlockInternal(Player &player, BlockPos pos, signed char side);

	virtual void startDestroyBlock(Player &player, BlockPos pos, signed char side);
	virtual void destroyBlock(Player &player, BlockPos pos, signed char side);
	virtual void continueDestroyBlock(Player &player, BlockPos pos, signed char side);
	virtual void stopDestroyBlock(Player &player);

	virtual void startBuildBlock(Player &player, BlockPos pos, signed char side);
	virtual void buildBlock(Player &player, BlockPos pos, signed char side);
	virtual void continueBuildBlock(Player &player, BlockPos pos, signed char side);
	virtual void stopBuildBlock(Player &player);

	virtual void tick();

	virtual float getPickRange(Player *player);

	virtual void useItem(Player &player, ItemInstance &item);
	virtual void useItemOn(Player &player, ItemInstance *item, const BlockPos &blockPos, signed char side, const Vec3 &pos);

	virtual void interact(Player &player, Entity &entity);
	virtual void attack(Player &player, Entity &entity);

	void _releaseUsingItemInternal(Player *player);
	virtual void releaseUsingItem(Player &player);
};