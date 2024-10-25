#include "channel.hpp"

	// channel::channel() {

	// }
	channel::channel(std::string name) \
		: _name(verifyName(name)), _nbPeople(1), _isOnlyInvite(false), _limitPeople(-1), _needPw(false) {

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

	std::string channel::topic(std::string newTopic) {
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

	void channel::setInvitationMode(bool setOnlyInvite) {
		if (!setOnlyInvite)
			_isOnlyInvite = false;
		else
			_isOnlyInvite = true;
	}

	void channel::setLimitMode(int setLimit) {
		if (setLimit == -1)
			_limitPeople = -1;
		else
			_limitPeople = setLimit;
	}

	void channel::setWpMode(std::string wp) {
		if (wp.empty())
			_needPw = false;
		else {
			_needPw = true;
			_wp = wp;
		}
	}


