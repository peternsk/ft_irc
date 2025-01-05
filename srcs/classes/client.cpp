#include "client.hpp"


	Client::Client() {}
	Client::~Client() {
	}

	bool isAlphaNumeric(const std::string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i]) && !isalpha(str[i])) {
            return false;
        }
    }
    return true;
}

	Client::Client(std::string name) {

		// mettre ca ou tu creer le client
		if (isAlphaNumeric(name))
			throw std::invalid_argument(Error::ERR_ERRONEUSNICKNAME(name));
		
		if (!CMDH::findClient(name))
			throw std::invalid_argument(Error::ERR_NICKNAMEINUSE(name));
		_name = name;
	}

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
		if (CMDH::findClient(name))
			throw std::invalid_argument(Error::ERR_NICKNAMEINUSE(name));
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
			throw std::invalid_argument(Error::ERR_USERONCHANNEL(_name, chan->getName())); // change the exepiton "tried to join a Channel already in"
		_Channels[chan] = false;
		chan->addClient(this);
	}

	void Client::kick(Client * client, Channel *chan) {
		if (!client || !chan)
			return ;
		if (_Channels.find(chan) != _Channels.end())
		{
			if (_Channels[chan] == true)
			{
				client->removeChan(chan);
				chan->kick(client);
			}
			else if (!_Channels[chan])
				throw std::runtime_error(Error::ERR_CHANOPRIVSNEEDED(chan->getName()));
			else
				throw std::runtime_error(Error::ERR_USERNOTINCHANNEL(client->getName(), chan->getName()));
		}
	}

	/********************/
	/*   AJOUT PETER    */
	/********************/

	int  Client::GetFd(){
		return this->_fd;
	}

	void Client::SetFd(int fd){
		this->_fd = fd;
	}

	void Client::setIpAdd(std::string ipadd){
		this->_IPadd = ipadd;
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