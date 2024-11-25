#ifndef CMDUTILS_HPP
#define CMDUTILS_HPP

// client Channel manager
#include "ft_irc.hpp"
#include "struct.hpp"
typedef std::vector<Channel *> chanVec;
typedef std::vector<Client *> clientVec;

namespace CMDH {
	// using clientsVec = chanVec&;
	// using chanVec = chanVec&;

	clientVec& clientsArr(Client * newClient = NULL);
	chanVec& channelsArr(Channel * newChannel = NULL);

	void removeClientChan(Client * client, Channel * chan);
	void clientDisconnect(Client * client);

	Channel * findChan(std::string name);

	void destroyChan(Channel * chan);

	bool joinCheckMode(Channel * chan, const Cmd & cmd, int & nbWp);

	Client *findClient(const std::string name);
}

#endif