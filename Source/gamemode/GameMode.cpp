#include "GameMode.h"

GameMode::GameMode(PacketSender *packetSender, Level *level)
{
	this->packetSender = packetSender;
	this->level = level;
}

GameMode::~GameMode()
{

}

void GameMode::attack(Player *player, Entity *entity)
{

}