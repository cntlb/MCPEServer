#pragma once

#include <vector>
#include <memory>

#include "entity\player\Player.h"

class Level
{
private:
	std::vector<std::unique_ptr<Player>> players;

public:
	Level();
	~Level();

	void addEntity(std::unique_ptr<Entity> entity);
	void addPlayer(std::unique_ptr<Player> player);

	void tick();

	Player *getPlayer(const std::string &username) const;
	std::vector<std::unique_ptr<Player>> &getPlayers();
};

