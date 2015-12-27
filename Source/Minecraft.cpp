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

	setName("\xED\x85\x8C\xEC\x8A\xA4\xED\x8A\xB8");
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
				else if (strlen(cmd) > 0)
					netServerHandler->_displayGameMessage("console", cmd);
			}
		}
	}
}

void Minecraft::hostMultiplayer(int port, int players)
{
	netServerHandler = new NetServerHandler(NULL, NULL, raknet, packetSender);

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