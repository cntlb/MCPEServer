#include "gamemode/SurvivalMode.h"

SurvivalMode::SurvivalMode(PacketSender *packetSender, Level *level)
	: GameMode(packetSender, level)
{

}

SurvivalMode::~SurvivalMode()
{

}

void SurvivalMode::startDestroyBlock(Player &player, BlockPos pos, signed char side)
{

}

void SurvivalMode::destroyBlock(Player &player, BlockPos pos, signed char side)
{

}

void SurvivalMode::tick()
{

}

void SurvivalMode::useItem(Player &player, ItemInstance &item)
{

}

void SurvivalMode::useItemOn(Player &player, ItemInstance *item, const BlockPos &blockPos, signed char side, const Vec3 &pos)
{

}