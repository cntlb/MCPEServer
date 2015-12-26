#pragma once

class PacketSender;
class Level;
class Player;
class Entity;

class GameMode
{
private:
	PacketSender *packetSender;
	Level *level;

public:
	GameMode(PacketSender *packetSender, Level *level);
	virtual ~GameMode();

	virtual void attack(Player *player, Entity *entity);
};