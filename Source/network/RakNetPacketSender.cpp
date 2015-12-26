#include "RakNetPacketSender.h"

#include "RakNetTypes.h"
#include "BitStream.h"

#include "NetworkStructures.h"
#include "PacketEnumeration.h"
#include "RakNetInstance.h"

RakNetPacketSender::RakNetPacketSender(RakNetInstance *raknet)
{
	this->raknet = raknet;
}

RakNetPacketSender::~RakNetPacketSender()
{

}

void RakNetPacketSender::send(const Packet &packet)
{
	if (true)
	{
		RakNet::RakNetGUID guid;
		_sendInternal(guid, packet, true);
	}
	else
	{
		RakNet::RakNetGUID guid;
		_sendInternal(guid, packet, true);
	}
}

void RakNetPacketSender::send(const RakNet::RakNetGUID &guid, const Packet &packet)
{
	_sendInternal(guid, packet, false);
}

void RakNetPacketSender::sendBroadcast(const RakNet::RakNetGUID &guid, const Packet &packet)
{
	_sendInternal(guid, packet, true);
}

void RakNetPacketSender::_sendInternal(const RakNet::AddressOrGUID &addressOrGUID, const Packet &packet, bool broadcast)
{
	if (packet.getId() == 4 && ((BatchPacket &)packet).payload.empty())
	{
		return;
	}

	RakNet::BitStream bs;
	packet.write(&bs);

	if (packet.getId() == 4 || !packet.b1 || bs.GetNumberOfBytesUsed() < 256)
	{
		raknet->sendRaw(bs, packet.priority, packet.reliability, addressOrGUID, broadcast, 0);

		if (packet.getId() != 4)
		{
			raknet->getPeer();
		}
	}
	else
	{
		BatchPacket pk;
		pk.add(&packet);
		pk.compress();

		_sendInternal(addressOrGUID, pk, broadcast);
	}
}