#include "level/Level.h"

Level::Level(std::unique_ptr<LevelStorage> storage, const std::string &levelName, const LevelSettings &settings, bool)
{

}

Level::~Level()
{

}

void Level::onSourceCreated(BlockSource &region)
{

}

void Level::onSourceDestroyed(BlockSource &region)
{

}

void Level::onBlockChanged(BlockSource &region, const BlockPos &pos, FullBlock oldBlock, FullBlock newBlock, int update)
{

}

void Level::addEntity(std::unique_ptr<Entity> entity)
{

}

void Level::addPlayer(std::unique_ptr<Player> player)
{

}

void Level::addGlobalEntity(std::unique_ptr<Entity> entity)
{

}

void Level::onPlayerDeath(Player &player, const EntityDamageSource &damageSource)
{

}

void Level::tick()
{

}

void Level::directTickEntities(BlockSource &region)
{

}

void Level::updateSleepingPlayerList()
{

}

void Level::setDifficulty(Difficulty difficulty)
{

}

void Level::runLightUpdates(BlockSource &region, const LightLayer &layer, const BlockPos &pos1, const BlockPos &pos2)
{

}

void Level::onNewChunkFor(Player &player, LevelChunk &chunk)
{

}

void Level::onChunkLoaded(LevelChunk &chunk)
{

}

void Level::removeEntity(std::unique_ptr<Entity> &&entity, bool)
{

}

void Level::removeEntity(Entity &entity, bool)
{

}

Player *Level::getPlayer(const std::string &username) const
{
	return NULL;
}

std::vector<std::unique_ptr<Player>> &Level::getPlayers()
{
	return players;
}