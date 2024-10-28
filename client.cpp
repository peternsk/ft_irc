#include "client.hpp"

	Client::Client() {}
	Client::~Client() {}

	Client::Client(std::string name) : _name(name) {}

	void Client::setChop(bool SetChop, channel * chan) {
		if (_channels.find(chan) != _channels.end())
		_channels[chan] = SetChop;
	}

	bool Client::getChop(channel * chan) {
		return _channels[chan];
	}

	std::string Client::getName(void) {
		return _name;
	}

	void Client::setName(std::string name) {
		_name = name;
	}

	void Client::join(channel *chan) {
		if (_channels.find(chan) != _channels.end())
			return ;
		if (chan->getNbPeople() == 0)
			_channels[chan] = true;
		else
			_channels[chan] = false;
	}

	void Client::kick(Client * client, channel *chan) {
		if (!client || !chan)
			return ;
		if (_channels.find(chan) != _channels.end())
		{
			p("yes");
			if (_channels[chan] == true && client->isPartChan(chan))
			{
				client->removeChan(chan);
				chan->kick(client);
			}
		}
	}

	void Client::removeChan(channel *chan) {
		std::map < channel *, bool >::iterator it = _channels.find(chan);
		if (it != _channels.end())
			_channels.erase(it);
	}

	bool Client::isPartChan(channel *chan) {
		if (_channels.find(chan) != _channels.end())
			return true;
		return false;
	}

	void Client::showChannels(void) {
		for (std::map <channel *, bool >::iterator it = _channels.begin(); it != _channels.end(); ++it)
		{
			std::cout << it->first->getName() << std::endl;
		}
	}