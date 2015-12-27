#include <sstream>
#include <memory>

#include "network/RakNetInstance.h"

#include "RakPeerInterface.h"
#include "BitStream.h"
#include "RakSleep.h"
#include "MessageIdentifiers.h"

#include "network/packet/PacketID.h"
#include "network/packet/Packet.h"
#include "network/MinecraftPackets.h"
#include "network/NetServerHandler.h"
#include "SharedConstants.h"

RakNetInstance::RakNetInstance()
{
	server = RakNet::RakPeerInterface::GetInstance();
	server->SetTimeoutTime(10000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
	server->SetOccasionalPing(true);
}

RakNetInstance::~RakNetInstance()
{
	server->Shutdown(300);
	RakNet::RakPeerInterface::DestroyInstance(server);
}

void RakNetInstance::host(unsigned short port, int maxIncomingConnections)
{
	RakNet::SocketDescriptor socketDescriptor(port, NULL);

	server = RakNet::RakPeerInterface::GetInstance();
	switch (server->Startup(maxIncomingConnections, &socketDescriptor, 1))
	{
	case RakNet::StartupResult::RAKNET_STARTED:
		break;
	case RakNet::StartupResult::SOCKET_PORT_ALREADY_IN_USE:
		printf("Port already in use.");
		return;
	case RakNet::StartupResult::STARTUP_OTHER_FAILURE:
		printf("Unknown error");
		return;
	default:
		printf("error");
		return;
	}
	server->SetMaximumIncomingConnections(maxIncomingConnections);
}

void RakNetInstance::announceServer(const std::string &name)
{
	std::stringstream ss;
	ss << "MCPE;" + name + ";" << SharedConstants::NetworkProtocolVersion << ";0.13.1;" << server->NumberOfConnections() << ";" << server->GetMaximumIncomingConnections();
	
	std::string data = ss.str();
	short length = data.length();

	RakNet::BitStream bs;
	if (RakNet::BitStream::IsNetworkOrderInternal())
		bs.WriteBits((unsigned char *)&length, 16);
	else
	{
		unsigned char out[2];
		RakNet::BitStream::ReverseBytes((unsigned char *)&length, out, 2);
		bs.WriteBits(out, 16);
	}
	bs.Write(data.c_str(), data.length());

	server->SetOfflinePingResponse((const char *)bs.GetData(), bs.GetNumberOfBytesUsed());
}

void RakNetInstance::runEvents(NetServerHandler *handler)
{
	RakSleep(30);

	RakNet::Packet *packet;
	for (packet = server->Receive(); packet; server->DeallocatePacket(packet), packet = server->Receive())
	{
		unsigned char pkId = packet->data[0];
		if (pkId == ID_UNCONNECTED_PING)
		{
			
		}
		else if (pkId == ID_NEW_INCOMING_CONNECTION)
		{
			handler->onNewClient(packet->guid);
		}
		else if (pkId == ID_DISCONNECTION_NOTIFICATION)
		{
			handler->onDisconnect(packet->guid, "");
		}
		else if (pkId >= PacketID::ID_MINECRAFT_PACKET)
		{
			RakNet::BitStream bs(packet->data, packet->length, false);
			bs.SetReadOffset(8);

			if (((char)pkId + 109) <= 108)
			{
				if (!handler->allowIncomingPacketId(packet->guid, pkId - 142))
					continue;
			}

			std::unique_ptr<Packet> pk;
			if (pk = MinecraftPackets::createPacket(pkId))
			{
				pk->read(&bs);
				pk->handle(packet->guid, handler);
			}
			else
				printf("Packet ID: %d\n", pkId);
		}
		else
			printf("Unknown packet ID: %d\n", pkId);
	}
}

void RakNetInstance::sendRaw(const RakNet::BitStream &bs, PacketPriority priority, PacketReliability reliability, RakNet::AddressOrGUID addressOrGUID, bool broadcast, unsigned int i)
{
	server->Send(&bs, priority, reliability, 0, addressOrGUID, broadcast);
}

void RakNetInstance::tick()
{

}

RakNet::RakPeerInterface *RakNetInstance::getPeer() const
{
	return server;
}