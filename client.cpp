#include "client.hpp"

	Client::Client() : _isChop(false) {}
	Client::~Client() {}

	Client::Client(bool setChop, std::string name) : _isChop(setChop), _name(name) {}

	void Client::setChop(bool SetChop) {
		_isChop = SetChop;
	}

	bool Client::getChop(void) {
		return _isChop;
	}

	std::string Client::getName(void) {
		return _name;
	}

	void Client::setName(std::string name) {
		_name = name;
	}