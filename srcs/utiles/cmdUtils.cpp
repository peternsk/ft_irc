#include "cmdUtils.hpp"

// get clients static

namespace CMDH {

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

		if (!chan->hasClient(client))
			return ; // i dont know why but its just suppose to be ignore not to return an error
		client->removeChan(chan);
		if (chan->getNbPeople() == 1)
		{
			destroyChan(chan);
			return ;
		}
		chan->kick(client);
	}

	Channel * findChan(std::string name) {
		chanVec Channels = channelsArr();
		for (chanVec::iterator it = Channels.begin(); it != Channels.end(); ++it)
		{
			std::cout << "ttest" << (*it)->getNbPeople() << std::endl;
			std::cout << (*it)->getName() << name << std::endl;
			if ((*it)->getName() == name)
				return *it;
		}
		return NULL;
	} 

	void clientDisconnect(Client * client) {
		bool sup = false;
		chanVec& channels = channelsArr();
		do
		{
			sup = false;
			for (chanVec::iterator it = channels.begin(); it != channels.end(); ++it)
			{
				if (!(*it)->hasClient(client))
					continue ;
				(*it)->kick(client);
				if ((*it)->getNbPeople() == 0) {
					destroyChan(*it);
					sup = true;
					break;
				}
			}
		} while (sup);
	}
	void destroyChan(Channel * chan) {
		chanVec &Channels = CMDH::channelsArr(NULL);
		chanVec::iterator it = std::remove(Channels.begin(), Channels.end(), chan);
		Channels.erase(it, Channels.end());
		delete chan;
	}

	bool joinCheckMode(Channel * chan, const Cmd & cmd, int & nbWp) {
		if (chan->getNeedWp())
		{
			// std::cout << cmd.arg[1]  << "******************" << std::endl;
			nbWp++;
			if ((int)cmd.password.size() < nbWp)
				throw std::invalid_argument(Error::ERR_BADCHANNELKEY(chan->getName()));
			if (!chan->tryWp(cmd.password[nbWp - 1]))
				throw std::invalid_argument(Error::ERR_BADCHANNELKEY(chan->getName()));
		}
		if (chan->getIsInviteOnly(cmd.client))
			throw std::invalid_argument(Error::ERR_INVITEONLYCHAN(chan->getName()));
		if (!chan->checkLimitNbrPeople())
			throw std::invalid_argument(Error::ERR_CHANNELISFULL(chan->getName()));
		
		return true;
	}

	Client *findClient(const std::string name) {
		clientVec clients = CMDH::clientsArr();
		for (clientVec::iterator it = clients.begin(); it != clients.end(); ++it) {
			if ((*it)->getName() == name)
				return (*it);
		}
		return NULL;
	}
}

// TO DO :

//un fonction qui check si le client et channel exist retourn un bool

//




// si la commande est join
// JOIN #channel
// JOIN #channel1,#channel2
// JOIN #channel password
// JOIN #channel1,#channel2,#channel3 password1,password2,password3

// JOIN {
// the client
// the command
// vector arg1 channelname
// vector passwords: password
// }

//topic {
// the client
// the command ; topic
// vector arg1 channel, what to change the topic
// vector arg2 nothing
// }

// kick {
// the client
// the command ; topic
// vector arg1 channel, who to kick
// vector arg2 nothing
// }

// NICK {
// the client
// the command ; NICK
// vector arg1 newnick
// vector arg2 nothing
// }

// MODE {
// the client
// the command ; MODE
// vector arg1 channel, the mode ex -v, arg
// vector arg2 nothing
// }


// LIST {
// the client
// the command ; LIST
// vector arg1 nothing
// vector arg2 nothing
// }

// INVITE  {
// the client
// the command ; LIST
// vector arg1 pseudo, channel
// vector arg2 nothing
// }

// /MSG  {
// the client
// the command ; MSG
// vector arg1 pseudo, msg
// vector arg2 nothing
// }

// /PART #canal {
// the client
// the command ; PART
// vector arg1 channel
// vector arg2 nothing
// }

// /QUIT [message]  {
// the client
// the command ; QUIT
// vector arg1 message
// vector arg2 nothing
// }

// CMSG {
// the client
// the command ; CMSG
// vector arg1 channel, message
// vector arg2 nothing
// }



// diviser les fonction CCM et CCM helpers

// Vous devez pouvoir vous authentifier, définir un nickname, un username, re-
// joindre un channel, envoyer et recevoir des messages privés, avec votre client
// de référence