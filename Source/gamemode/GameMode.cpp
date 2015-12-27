#include "gamemode/GameMode.h"

GameMode::GameMode(PacketSender *packetSender, Level *level)
{
	this->packetSender = packetSender;
	this->level = level;
}

GameMode::~GameMode()
{

}

void GameMode::_creativeDestroyBlock(Player &player, BlockPos pos, signed char side)
{

}

void GameMode::_destroyBlockInternal(Player &player, BlockPos pos, signed char side)
{

}

void GameMode::startDestroyBlock(Player &player, BlockPos pos, signed char side)
{

}

void GameMode::destroyBlock(Player &player, BlockPos pos, signed char side)
{

}

void GameMode::continueDestroyBlock(Player &player, BlockPos pos, signed char side)
{

}

void GameMode::stopDestroyBlock(Player &player)
{

}

void GameMode::startBuildBlock(Player &player, BlockPos pos, signed char side)
{

}

void GameMode::buildBlock(Player &player, BlockPos pos, signed char side)
{

}

void GameMode::continueBuildBlock(Player &player, BlockPos pos, signed char side)
{

}

void GameMode::stopBuildBlock(Player &player)
{

}

void GameMode::tick()
{

}

float GameMode::getPickRange(Player *player)
{
	return 5.0f;
}

void GameMode::useItem(Player &player, ItemInstance &item)
{

}

void GameMode::useItemOn(Player &player, ItemInstance *item, const BlockPos &blockPos, signed char side, const Vec3 &pos)
{

}

void GameMode::interact(Player &player, Entity &entity)
{

}

void GameMode::attack(Player &player, Entity &entity)
{

}

void GameMode::_releaseUsingItemInternal(Player *player)
{

}

void GameMode::releaseUsingItem(Player &player)
{

}