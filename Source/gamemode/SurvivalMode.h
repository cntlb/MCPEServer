#pragma once

#include "gamemode/GameMode.h"

class SurvivalMode : public GameMode
{
public:
	SurvivalMode(PacketSender *packetSender, Level *level);
	~SurvivalMode();

	void startDestroyBlock(Player &player, BlockPos pos, signed char side);
	void destroyBlock(Player &player, BlockPos pos, signed char side);

	void tick();

	void useItem(Player &player, ItemInstance &item);
	void useItemOn(Player &player, ItemInstance *item, const BlockPos &blockPos, signed char side, const Vec3 &pos);
};