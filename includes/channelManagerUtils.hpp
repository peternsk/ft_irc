#ifndef CHANNELMANAGERUTILS_HPP
#define CHANNELMANAGERUTILS_HPP

// client Channel manager
#include "ft_irc.hpp"

typedef std::vector<Channel *> chanVec;
typedef std::vector<Client *> clientVec;

namespace CCM {
	// using clientsVec = chanVec&;
	// using chanVec = chanVec&;

	clientVec& clientsArr(Client * newClient = NULL);
	chanVec& channelsArr(Channel * newChannel = NULL);

	void removeClientChan(Client * client, Channel * chan);
	void clientDisconnect(Client * client);

	Channel * findChan(chanVec Channels, std::string name);

	void destroyChan(Channel * chan);
}

#endif