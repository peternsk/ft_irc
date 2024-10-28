#pragma once

#include "ft_irc.hpp"
#include "channel.hpp"

class channel;

class Client {
public :
//helpers
	void showChannels(void);
	Client();
	Client(std::string name);
	~Client();

	bool isPartChan(channel *chan);
	void setChop(bool SetChop, channel * chan);
	void setName(std::string name);
	bool getChop(channel * chan) ;
	std::string getName(void);

	void join(channel *chan);
	void removeChan(channel *chan);

	void kick(Client * client, channel * chan);

private :
	std::map <channel *, bool > _channels;
	std::string _name;
};

// 1.2.1 Operators

//    To allow a reasonable amount of order to be kept within the IRC
//    network, a special class of Clients (operators) is allowed to perform
//    general maintenance functions on the network.  Although the powers
//    granted to an operator can be considered as 'dangerous', they are
//    nonetheless required.  Operators should be able to perform basic
//    network tasks such as disconnecting and reconnecting servers as
//    needed to prevent long-term use of bad network routing.  In
//    recognition of this need, the protocol discussed herein provides for
//    operators only to be able to perform such functions.  See sections
//    4.1.7 (SQUIT) and 4.3.5 (CONNECT).

//    A more controversial power of operators is the ability  to  remove  a
//    user  from  the connected network by 'force', i.e. operators are able
//    to close the connection between any Client and server.   The
//    justification for  this  is delicate since its abuse is both
//    destructive and annoying.  For further details on this type of
//    action, see section 4.6.1 (KILL).

//         KICK    - Eject a Client from the channel
//         MODE    - Change the channel's mode
//         INVITE  - Invite a Client to an invite-only channel (mode +i)
//         TOPIC   - Change the channel topic in a mode +t channel
