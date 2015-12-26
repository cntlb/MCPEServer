#include "Minecraft.h"

#include "network/RakNetInstance.h"
#include "network/RakNetPacketSender.h"
#include "network/NetServerHandler.h"

#include "Kbhit.h"
#include "Gets.h"

Minecraft::Minecraft()
{
	running = true;

	raknet = new RakNetInstance;
	packetSender = new RakNetPacketSender(raknet);

	setName("C++ Server!");
	hostMultiplayer(19132, 10);
}

Minecraft::~Minecraft()
{
	delete raknet;
	delete packetSender;
}

bool Minecraft::init()
{
	return true;
}

void Minecraft::run()
{
	if (init())
	{
		while (running)
		{
			raknet->runEvents(netServerHandler);

			tick();

			if (kbhit())
			{
				char cmd[1024];
				Gets(cmd, 1024);

				if (strcmp(cmd, "stop") == 0)
					break;
			}
		}
	}
}

void Minecraft::hostMultiplayer(int port, int players)
{
	netServerHandler = new NetServerHandler(raknet, packetSender);

	raknet->host(port, players);
	raknet->announceServer(name);
}

void Minecraft::tick()
{
	raknet->tick();
}

void Minecraft::setName(const std::string &name)
{
	this->name = name;
}

const std::string &Minecraft::getName() const
{
	return name;
}

bool Minecraft::isRunning() const
{
	return running;
}