#pragma once

#include <string>

#include "level/BlockSourceListener.hpp"
#include "level/ParticleType.h"
#include "event/LevelEvent.h"

class Vec3;
class Entity;
class LevelChunk;
class Player;

class LevelListener : public BlockSourceListener
{
public:
	virtual ~LevelListener() = 0 {}
	virtual void allChanged() {}
	virtual bool addParticle(ParticleType type, const Vec3 &, const Vec3 &, int) { return false; }
	virtual void playSound(const std::string &sound, const Vec3 &pos, float, float) {}
	virtual void playMusic(const std::string &sound, const Vec3 &pos, float) {}
	virtual void playStreamingMusic(const std::string &music, int, int, int) {}
	virtual void onEntityAdded(Entity &entity) {}
	virtual void onEntityRemoved(Entity &entity) {}
	virtual void onNewChunkFor(Player &player, LevelChunk &chunk) {}
	virtual void levelEvent(LevelEvent e, const Vec3 &vec3, int i) {}
};
