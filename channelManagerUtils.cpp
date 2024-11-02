#include "channelManagerUtils.hpp"

// get clients static

namespace CCM {

	// get Client static
	clientVec& clientsArr(Client * newClient) {
		static clientVec clients;
		if (newClient)
			clients.push_back(newClient);
		return clients;
	}
	
	// get Channels static
	chanVec& channelsArr(Channel * newChannel) {
		static chanVec Channels;
		if (newChannel)
			Channels.push_back(newChannel);
		return Channels;
	}

	void removeClientChan(Client * client, Channel * chan) {

		client->removeChan(chan);
		if (chan->getNbPeople() == 1)
		{
			destroyChan(chan);
			return ;
		}
		chan->kick(client);
	}

	Channel * findChan(chanVec Channels, std::string name) {
		for (chanVec::iterator it = Channels.begin(); it != Channels.end(); ++it)
		{
			std::cout << "ttest" << (*it)->getNbPeople() << std::endl;
			std::cout << (*it)->getName() << name << std::endl;
			if ((*it)->getName() == name)
				return *it;
		}
		throw std::exception();
	} 

	void clientDisconnect(Client * client) {
		chanVec& channels = channelsArr();
		for (chanVec::iterator it = channels.begin(); it != channels.end(); ++it)
		{
			if (!(*it)->hasClient(client))
				continue ;
			(*it)->kick(client);
			if ((*it)->getNbPeople() == 1)
				destroyChan(*it);
		}
		delete client;
	}
	void destroyChan(Channel * chan) {
		chanVec &Channels = CCM::channelsArr(NULL);
		chanVec::iterator it = std::remove(Channels.begin(), Channels.end(), chan);
		Channels.erase(it, Channels.end());
		delete chan;
	}
}
