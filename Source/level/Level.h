#pragma once

#include <vector>
#include <memory>

#include "level/BlockSourceListener.hpp"
#include "level/Difficulty.h"
#include "level/LevelStorage.h"
#include "level/dimension/DimensionId.h"
#include "entity/Player.h"
#include "entity/EntityDamageSource.h"

class LevelSettings;
class LevelChunk;
class LightLayer;

class Level : public BlockSourceListener
{
private:
	std::vector<std::unique_ptr<Player>> players;

public:
	Level(std::unique_ptr<LevelStorage> storage, const std::string &levelName, const LevelSettings &settings, bool);
	~Level();

	void onSourceCreated(BlockSource &region);
	void onSourceDestroyed(BlockSource &region);

	void onBlockChanged(BlockSource &region, const BlockPos &pos, FullBlock oldBlock, FullBlock newBlock, int update);

	void addEntity(std::unique_ptr<Entity> entity);
	void addPlayer(std::unique_ptr<Player> player);
	void addGlobalEntity(std::unique_ptr<Entity> entity);

	void onPlayerDeath(Player &player, const EntityDamageSource &damageSource);

	void tick();
	void directTickEntities(BlockSource &region);
	void updateSleepingPlayerList();

	void setDifficulty(Difficulty difficulty);

	void runLightUpdates(BlockSource &region, const LightLayer &layer, const BlockPos &pos1, const BlockPos &pos2);

	void onNewChunkFor(Player &player, LevelChunk &chunk);
	void onChunkLoaded(LevelChunk &chunk);

	void removeEntity(std::unique_ptr<Entity> &&entity, bool);
	void removeEntity(Entity &entity, bool);

	Dimension *createDimension(DimensionId id);

	Player *getPlayer(const std::string &username) const;
	std::vector<std::unique_ptr<Player>> &getPlayers();
};

