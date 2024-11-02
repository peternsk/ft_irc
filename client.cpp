#include "client.hpp"

	Client::Client() {}
	Client::~Client() {}

	Client::Client(std::string name) : _name(name) {}

	void Client::setChop(bool SetChop, Channel * chan) {
		if (_Channels.find(chan) != _Channels.end())
		_Channels[chan] = SetChop;
	}

	bool Client::getChop(Channel * chan) {
		return _Channels[chan];
	}

	std::string Client::getName(void) {
		return _name;
	}

	void Client::setName(std::string name) {
		_name = name;
	}

	Channel *Client::join(std::string name) {
		Channel *newChan = new Channel(name);
		newChan->addClient(this);
		_Channels[newChan] = true;
		return newChan;
	}

	void Client::join(Channel *chan) {
		if (_Channels.find(chan) != _Channels.end())
			throw std::exception(); // change the exepiton "tried to join a Channel already in"
		_Channels[chan] = false;
		chan->addClient(this);
	}

	void Client::kick(Client * client, Channel *chan) {
		if (!client || !chan)
			return ;
		if (_Channels.find(chan) != _Channels.end())
		{
			if (_Channels[chan] == true && client->isPartChan(chan))
			{
				client->removeChan(chan);
				chan->kick(client);
			}
		}
	}

	void Client::removeChan(Channel *chan) {
		std::map < Channel *, bool >::iterator it = _Channels.find(chan);
		if (it != _Channels.end())
			_Channels.erase(it);
	}

	bool Client::isPartChan(Channel *chan) {
		if (_Channels.find(chan) != _Channels.end())
			return true;
		return false;
	}

	void Client::showChannels(void) {
		for (std::map <Channel *, bool >::iterator it = _Channels.begin(); it != _Channels.end(); ++it)
		{
			std::cout << it->first->getName() << std::endl;
		}
	}