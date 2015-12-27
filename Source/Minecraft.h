#pragma once

#include <string>

class RakNetInstance;
class RakNetPacketSender;
class NetServerHandler;

class Minecraft
{
private:
	bool running;

	RakNetInstance *raknet;
	RakNetPacketSender *packetSender;

	NetServerHandler *netServerHandler;

	std::string name;

public:
	Minecraft();
	~Minecraft();

	bool init();
	void run();

	void hostMultiplayer(int port, int players);
	void tick();

	void setName(const std::string &name);
	const std::string &getName() const;

	bool isRunning() const;
};

