#pragma once

#include "ft_irc.hpp"
#include "channel.hpp"

class Channel;

class Client {
public :
//helpers
	void showChannels(void);
	Client();
	Client(std::string name);
	~Client();

	bool isPartChan(Channel *chan);
	void setChop(bool SetChop, Channel * chan);
	void setName(std::string name);
	bool getChop(Channel * chan) ;
	
	std::string getName(void);

	Channel *join(std::string name);
	
	void join(Channel *chan);

	void removeChan(Channel *chan);

	void kick(Client * client, Channel * chan);

	/*===== AJOUT PETER=====*/
	int GetFd();

	void SetFd(int fd);
	void setIpAdd(std::string ipadd);

private :
	std::map <Channel *, bool > _Channels;
	std::string _name;
	int _fd;
	std::string _IPadd;
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

//         KICK    - Eject a Client from the Channel
//         MODE    - Change the Channel's mode
//         INVITE  - Invite a Client to an invite-only Channel (mode +i)
//         TOPIC   - Change the Channel topic in a mode +t Channel
