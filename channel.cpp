#include "channel.hpp"

	// channel::channel() {

	// }
	channel::channel(std::string name) \
		: _name(verifyName(name)), _nbPeople(0), _isOnlyInvite(false), _limitPeople(-1), _needPw(false) {
	}

	channel::~channel() {

	}

	short channel::getNbPeople(void) const {
		return _nbPeople;
	}

	std::string channel::getName(void) const {
		return _name;
	}
	bool channel::getIsIniteOnly(void) const {
		return _isOnlyInvite;
	}


// gerer les code derreurs
	std::string channel::verifyName(std::string & name) {
		short lenghtMax = 200;
		if(name[0] != '#')
		{
			if (name.length() == 200)
				throw std::exception();
			name.insert(0, 1, '#');
		}
		if ((short)name.length() > lenghtMax or name.find(" ") != std::string::npos \
			or name.find("\a") != std::string::npos or name.find(",") != std::string::npos)
			throw std::exception();
		return name;
	}

	//****************************************************************//
	// COMMAND
	//****************************************************************//

	// add a client that will change it if its an operator than can change the topic even if the flag is up
	std::string channel::topic(Client *asking, std::string newTopic) {
		if (_isChopTopic && !asking->getChop(this))
			return ""; // THROW EXEPCTIONS
		if (!newTopic.empty())
			_topic = newTopic;

		// RETURN PROPER EXEPTION
		if (_topic.empty())
			throw std::exception();
		return _topic;
	}

	// void channel::join() {

	// }

	//****************************************************************//
	// MODE
	//****************************************************************//

	void channel::setInvitationMode(Client *asking, bool setOnlyInvite) {
		if (!asking->getChop(this))
			return ; //THROW ERROR
		_isOnlyInvite = setOnlyInvite;
	}

	void channel::setLimitMode(Client *asking, int setLimit) {
		if (!asking->getChop(this))
			return ; //THROW ERROR
		_limitPeople = setLimit;
	}

	void channel::setWpMode(Client *asking, std::string wp) {
		if (!asking->getChop(this))
			return ; //THROW ERROR
		if (wp.empty())
			_needPw = false;
		else {
			_needPw = true;
			_wp = wp;
		}
	}

	void channel::setChopChangeTopic(Client *asking, bool setChopTopic) {
		if (!asking->getChop(this))
			return ; //THROW ERROR
		_isChopTopic = setChopTopic;
	}

	void channel::setChop(Client *asking, const std::string &name, bool SetChop) {
		if (!asking->getChop(this))
			return ; 	// OR THROW EXECPTIONS

		if (clients.find(name) != clients.end())
			clients[name]->setChop(SetChop, this);
	}

	void channel::addClient(Client * client) {
		if (!client)
			return ; //THROW EXEPTION
		if (_nbPeople == 0)
			client->setChop(true, this);
		clients[client->getName()] = client;
	}

	void channel::kick(Client * client) {
		std::map < std::string, Client * >::iterator it = clients.find(client->getName());
		clients.erase(it);
	}

	void channel::listClients(void) {
		for (std::map <std::string, Client * >::iterator it = clients.begin(); it != clients.end(); ++it) {
			std::cout << it->first << std::endl;
		}
	}

