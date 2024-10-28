#pragma once

#include "ft_irc.hpp"
#include "client.hpp" 

class Client;
class channel {
	public:
	// helpers;
	void listClients(void);
	// peut etre pas utile
	// channel();

	// potentiellement call la fonction quand ya pu de gens dedans 
		//et verifier quand quelqun quit cmb de gens encore
	~channel();

	//getters
	std::string getName(void) const;
	short getNbPeople(void) const;
	bool getIsIniteOnly(void) const;

	// creer just quand quelqun join jpense
	channel(std::string name);

// **************************************************************//
// CLIENTS
// **************************************************************//

	void addClient(Client * client);

// **************************************************************//
// COMMAND
// **************************************************************//
	// void join();
	void kick(Client * client);
	// invite
	std::string topic(Client *asking, std::string newTopic = "");



	// make a function to write to everyone the message sent

// **************************************************************//
// MODE
// **************************************************************//
	// — i : Définir/supprimer le canal sur invitation uniquement
	void setInvitationMode(Client *asking, bool setOninvite = false);
	// — t : Définir/supprimer les restrictions de la commande TOPIC pour les opé-
	// rateurs de canaux
	void setChopChangeTopic(Client *asking, bool setChopTopic = false);
	// — k : Définir/supprimer la clé du canal (mot de passe)
	void setWpMode(Client *asking, std::string wp = "");
	// — o : Donner/retirer le privilège de l’opérateur de canal
	void setChop(Client *asking, const std::string &name, bool SetChop = false);
	// — l : Définir/supprimer la limite d’utilisateurs pour le canal
	void setLimitMode(Client *asking, int setLimit = -1);




	private:
	std::string _name;
	std::string _topic;
	int _nbPeople;

// for modes
	// changing the topic only chop
	bool _isChopTopic;
	bool _isOnlyInvite;
	int _limitPeople;
	bool _needPw;
	std::string _wp;

	// list all the client connected 

	std::string verifyName(std::string & name);
	// THE CLIENTS
	std::map < std::string, Client * > clients;
	
};	


// 1.3 Channels

//    A channel is a named group of one or more clients which will all
//    receive messages addressed to that channel.  The channel is created
//    implicitly when the first client joins it, and the channel ceases to
//    exist when the last client leaves it.  While channel exists, any
//    client can reference the channel using the name of the channel.

// done****
//    Channels names are strings (beginning with a '&' or '#' character) of
//    length up to 200 characters.  Apart from the the requirement that the
//    first character being either '&' or '#';
//	  the only restriction on a
//    channel name is that it may not contain any spaces (' '), a control G
//    (^G or ASCII 7), or a comma (',' which is used as a list item
//    separator by the protocol).



//    There are two types of channels allowed by this protocol.  One is a
//    distributed channel which is known to all the servers that are
//    connected to the network. These channels are marked by the first
//    character being a only clients on the server where it exists may join
//    it.  These are distinguished by a leading '&' character.  On top of
//    these two types, there are the various channel modes available to
//    alter the characteristics of individual channels.  See section 4.2.3			TO DO
//    (MODE command) for more details on this.

//    To create a new channel or become part of an existing channel, a user
//    is required to JOIN the channel.  If the channel doesn't exist prior
//    to joining, the channel is created and the creating user becomes a
//    channel operator.  If the channel already exists, whether or not your
//    request to JOIN that channel is honoured depends on the current modes
//    of the channel. For example, if the channel is invite-only, (+i),
//    then you may only join if invited.  As part of the protocol, a user
//    may be a part of several channels at once, but a limit of ten (10)
//    channels is recommended as being ample for both experienced and
//    novice users.  See section 8.13 for more information on this.

//    If the IRC network becomes disjoint because of a split between two
//    servers, the channel on each side is only composed of those clients
//    which are connected to servers on the respective sides of the split,
//    possibly ceasing to exist on one side of the split.  When the split
//    is healed, the connecting servers announce to each other who they
//    think is in each channel and the mode of that channel.  If the
//    channel exists on both sides, the JOINs and MODEs are interpreted in
//    an inclusive manner so that both sides of the new connection will
//    agree about which clients are in the channel and what modes the
//    channel has.

// 1.3.1 Channel Operators

//    The channel operator (also referred to as a "chop" or "chanop") on a
//    given channel is considered to 'own' that channel.  In recognition of
//    this status, channel operators are endowed with certain powers which
//    enable them to keep control and some sort of sanity in their channel.
//    As an owner of a channel, a channel operator is not required to have
//    reasons for their actions, although if their actions are generally
//    antisocial or otherwise abusive, it might be reasonable to ask an IRC
//    operator to intervene, or for the usersjust leave and go elsewhere
//    and form their own channel.

//    The commands which may only be used by channel operators are:

//         KICK    - Eject a client from the channel
//         MODE    - Change the channel's mode
//         INVITE  - Invite a client to an invite-only channel (mode +i)
//         TOPIC   - Change the channel topic in a mode +t channel




// Oikarinen & Reed                                                [Page 6]
// 
// RFC 1459              Internet Relay Chat Protocol              May 1993


//    A channel operator is identified by the '@' symbol next to their
//    nickname whenever it is associated with a channel (ie replies to the
//    NAMES, WHO and WHOIS commands).


// KICK - Ejecter un client du channel
// ◦ INVITE - Inviter un client au channel
		// le client invite quelqun dautre et regarde si le channel est sur invite ou nn
// ◦ TOPIC - Modifier ou afficher le thème du channel
// ◦ MODE - Changer le mode du channel :
// — i : Définir/supprimer le canal sur invitation uniquement
// 6
// ft_irc Internet Relay Chat
// — t : Définir/supprimer les restrictions de la commande TOPIC pour les opé-
// rateurs de canaux
// — k : Définir/supprimer la clé du canal (mot de passe)
// — o : Donner/retirer le privilège de l’opérateur de canal
// — l : Définir/supprimer la limite d’utilisateurs pour le canal



//avoir un array the operator;