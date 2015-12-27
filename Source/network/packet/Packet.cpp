#include "network/packet/Packet.h"

#include "PacketPriority.h"

Packet::Packet()
{
	priority = MEDIUM_PRIORITY;
	reliability = RELIABLE_ORDERED;
	b = false;
}

Packet::~Packet()
{

}