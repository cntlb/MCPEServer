#include "level/dimension/Dimension.h"

#include "level/dimension/NormalDimension.h"
#include "level/dimension/HellDimension.h"

std::unique_ptr<Dimension> Dimension::createNew(DimensionId id, Level *level)
{
	std::unique_ptr<Dimension> dimension;
	if (id == DIMENSION_NORMAL)
		dimension = std::unique_ptr<Dimension>(new NormalDimension(level));
	else if (id == DIMENSION_HELL)
		dimension = std::unique_ptr<Dimension>(new HellDimension(level));

	return dimension;
}

Dimension::Dimension(Level *level, DimensionId id)
{
	this->level = level;
	this->id = id;
}

Dimension::~Dimension()
{

}

void Dimension::onBlockChanged(BlockSource &, BlockPos const &, FullBlock, FullBlock, int)
{

}

void Dimension::onBlockEvent(BlockSource &, int, int, int, int, int)
{

}

void Dimension::onNewChunkFor(Player &, LevelChunk &)
{

}

void Dimension::init()
{

}

void Dimension::tick()
{

}

void Dimension::updateLightRamp()
{

}

bool Dimension::isNaturalDimension() const
{
	return true;
}

bool Dimension::isValidSpawn(int x, int z) const
{
	return false;
}

Color Dimension::getFogColor(float) const
{
	return Color::BLACK;
}

float Dimension::getFogDistanceScale() const
{
	return 0.5f;
}

bool Dimension::isFoggyAt(int x, int z) const
{
	return false;
}

float Dimension::getCloudHeight() const
{
	return 128.0f;
}

bool Dimension::mayRespawn() const
{
	return true;
}

bool Dimension::hasGround() const
{
	return true;
}

void Dimension::getSpawnYPosition()
{

}

bool Dimension::hasBedrockFog()
{
	return true;
}

float Dimension::getClearColorScale()
{
	return 0.03125f;
}

void Dimension::load(const CompoundTag &tag)
{

}

void Dimension::save(CompoundTag &tag)
{

}

void Dimension::sendDimensionPackets()
{

}

void Dimension::sendBroadcast(const Packet &packet, Player *player)
{

}

void Dimension::addMoveEntityPacket(const MoveEntityPacketData &)
{

}

void Dimension::addSetEntityMotionPacket(Entity &entity)
{

}

void Dimension::getTimeOfDay(int, float) const
{

}

ChunkSource *Dimension::getChunkSource() const
{
	return NULL;
}


void Dimension::setCeiling(bool value)
{
	ceiling = value;
}

void Dimension::setUltraWarm(bool value)
{
	ultrawarm = value;
}

Level *Dimension::getLevel() const
{
	return level;
}

Level *Dimension::getLevelCount() const
{
	return level;
}

DimensionId Dimension::getId() const
{
	return id;
}

int Dimension::getHeight() const
{
	return 128;
}

bool Dimension::isDay() const
{
	return true;
}