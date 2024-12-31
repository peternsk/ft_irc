
#include "ft_irc.hpp"
// #include "channel.hpp"

	// channel::channel() {

	// }

	Channel::Channel(std::string name)
		: _name(verifyName(name)), _nbPeople(0), _isOnlyInvite(false), _limitPeople(-1), _needPw(false) {
	}

	Channel::~Channel() {

	}

	short Channel::getNbPeople(void) const {
		return _nbPeople;
	}

	std::string Channel::getName(void) const {
		return _name;
	}
	bool Channel::getIsInviteOnly(void) const {
		return _isOnlyInvite;
	}


// gerer les code derreurs
	std::string Channel::verifyName(std::string & name) {
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
	void Channel::topic(Client *asking, std::string newTopic) {
		if (!hasClient(asking))
			throw std::invalid_argument(Error::ERR_NOTONCHANNEL(asking->getName()));
		if (!newTopic.empty()) {
			if (_isChopTopic && !asking->getChop(this))
				throw std::invalid_argument(Error::ERR_CHANOPRIVSNEEDED(asking->getName()));
			_topic = newTopic;
			return ;
		}

		// RETURN PROPER EXEPTION
		if (_topic.empty())
			throw std::runtime_error(Error::ERR_TOPICNOTSET(_name));;
		// return the topics;
		throw std::runtime_error(Error::RPL_TOPIC(_name, _topic));
	}

	// void Channel::join() {

	// }

	//****************************************************************//
	// MODE
	//****************************************************************//

	void Channel::setInvitationMode(Client *asking, bool setOnlyInvite) {
		if (!asking->getChop(this))
			throw std::invalid_argument(Error::ERR_CHANOPRIVSNEEDED(asking->getName()));
		_isOnlyInvite = setOnlyInvite;
	}

	void Channel::setLimitMode(Client *asking, int setLimit) {
		if (!asking->getChop(this))
			throw std::invalid_argument(Error::ERR_CHANOPRIVSNEEDED(asking->getName()));
		_limitPeople = setLimit;
	}

	void Channel::setWpMode(Client *asking, std::vector<std::string> arg) {
		if (!asking->getChop(this))
			throw std::invalid_argument(Error::ERR_CHANOPRIVSNEEDED(asking->getName()));
		if ((int)arg.size() < 3)
			_needPw = false;
		else {
			_needPw = true;
			_wp = arg[2];
		}
	}

	void Channel::setChopChangeTopic(Client *asking, bool setChopTopic) {
		if (!asking->getChop(this))
			throw std::invalid_argument(Error::ERR_CHANOPRIVSNEEDED(asking->getName()));
		_isChopTopic = setChopTopic;
	}

	void Channel::setChop(Client *asking, const std::string &name, bool SetChop) {
		listClients();
		if (!asking->getChop(this))
			throw std::invalid_argument(Error::ERR_CHANOPRIVSNEEDED(asking->getName()));

		if (clients.find(name) == clients.end())
			throw std::invalid_argument(Error::ERR_NOSUCHNICK(name));
		clients[name]->setChop(SetChop, this);
	}

	void Channel::addClient(Client * client) {
		if (!client)
			return ;
		if (_nbPeople == 0)
			client->setChop(true, this);
		_nbPeople++;
		clients[client->getName()] = client;
	}

	void Channel::kick(Client * client) {
		std::map < std::string, Client * >::iterator it = clients.find(client->getName());
		clients.erase(it);
		_nbPeople--;
	}

	void Channel::listClients(void) {
		std::cout << clients.size() << " this is the size" << std::endl;
		for (std::map <std::string, Client * >::iterator it = clients.begin(); it != clients.end(); ++it) {
			std::cout << it->first << std::endl;
		}
	}

	void Channel::sendMSGClient(const std::string &msg, Client * sender) {
		for (std::map<std::string, Client *>::iterator it = clients.begin(); it != clients.end(); ++it) {
			if (it->first == sender->getName())
				continue;
			send(it->second->GetFd(), msg.c_str(), msg.length(), 0);		
		}
	}

	bool Channel::hasClient(Client * client) {
		if (clients.find(client->getName()) != clients.end())
			return true;
		return false;
	}

	bool Channel::getNeedWp(void) const {
		return _needPw;
	}

	bool Channel::tryWp(const std::string & trywp) {
		if (_wp == trywp)
			return true;
		return false;
	}
