#include "cmd.hpp"
namespace CMD {
// ONLY FOR HELP AND DEBUG
	void printCMD(Cmd &cmd) {
		std::cout << "prefixe: " << cmd.prefix << std::endl;
		std::cout << "cmd: " << cmd.cmd << std::endl;

		int i = 0;
		for (std::vector<std::string>::iterator it = cmd.arg.begin(); it != cmd.arg.end(); it++) {
			std::cout << "arg " << i << ":"<< *it << std::endl;
			i++;
		}
		i = 0;
		for (std::vector<std::string>::iterator it = cmd.password.begin(); it != cmd.password.end(); it++) {
			std::cout << "PASSWORD " << i << ":"<< *it << std::endl;
			i++;
		}

		std::cout << "client: " << cmd.client << std::endl;
		std::cout << "chan: " << cmd.chan << std::endl;
	}

	void join(const Cmd &cmd) {
		int nbWp = 0;
		if (cmd.arg.size() < 1)
			throw std::invalid_argument(Error::ERR_NEEDMOREPARAMS("JOIN"));
		// normaly no error if you try to join even if you are already there >> simply ignored cmd
		for (int i = 0; i < (int)cmd.arg.size(); ++i) // I did this loop if joining multiple channels at the sametime
		{
			// make sur that he is not already in the channel
			// create the channels because it doesnt exist
			Channel *chan = CMDH::findChan(cmd.arg[i]);
			if (!chan) {
				CMDH::channelsArr(cmd.client->join(cmd.arg[i]));
				std::cout << "CREATE CHANNEL" << std::endl;
			}
			else {
				if (!CMDH::joinCheckMode(chan, cmd, nbWp))
					continue;
				cmd.client->join(chan);
				std::cout << "JOINED CHANNEL" << std::endl;
			}
		}
	}

	void topic(const Cmd &cmd) {  // la jsp peut etre que ca depends si avec lime chat il est dans une chan
		std::cout << "TOPIC" << std::endl;
		printCMD((Cmd &)cmd);

		if (cmd.arg.size() < 1)
			throw std::invalid_argument(Error::ERR_NEEDMOREPARAMS("TOPIC"));
		
		Channel *chan =  CMDH::findChan(cmd.arg[0]);
		if (!chan)
			throw std::invalid_argument(Error::ERR_NOSUCHCHANNEL(cmd.arg[0]));
		// (void)chan;
		//everything after the cmd topic if just one big string
		std::cout << (int)cmd.arg.size() << std::endl;
		if ((int)cmd.arg.size()  > 1) {
			std::string newTopic;
			for (int i = 1; i < (int)cmd.arg.size(); i++) {
				newTopic += cmd.arg[i];
				newTopic += " ";
			}
			chan->topic(cmd.client, newTopic);
		}
		else
			chan->topic(cmd.client);
	}

	void kick(const Cmd &cmd) {
		if ((int)cmd.arg.size() < 2)
			throw std::invalid_argument(Error::ERR_NEEDMOREPARAMS("KICK"));

		Channel *chan = CMDH::findChan(cmd.arg[0]);
		if (!chan) 
			throw std::invalid_argument(Error::ERR_NOSUCHCHANNEL(cmd.arg[0]));
		if (!chan->hasClient(cmd.client))
			throw std::invalid_argument(Error::ERR_NOTONCHANNEL(chan->getName()));
		
		Client * toKick = &(Server::findClient(cmd.arg[1]));
		if (toKick->GetFd() == cmd.client->GetFd())
			return ;
		if (!toKick->isPartChan(chan))
			throw std::invalid_argument(Error::ERR_USERNOTINCHANNEL(toKick->getName(), chan->getName()));
			

		// get client to kick
		cmd.client->kick(toKick, chan);
	}

	void nick(const Cmd &cmd) {
		if ((int)cmd.arg.size() < 1)
			throw std::invalid_argument(Error::ERR_ERRONEUSNICKNAME(cmd.arg[0]));


		CMDH::channelsArr(NULL);
		Server::checkName(cmd.arg[0]);
		cmd.client->setName(cmd.arg[0]);

		// chaque chan change the name
	}

	void mode(const Cmd &cmd) {
		if ((int)cmd.arg.size() < 2)
			throw std::invalid_argument(Error::ERR_NEEDMOREPARAMS("MODE"));
		Channel *chan = CMDH::findChan(cmd.arg[0]);
		if (!chan)
			throw std::invalid_argument(Error::ERR_NOSUCHCHANNEL(cmd.arg[0]));
		else if(cmd.arg[1] == "-i")
			chan->setInvitationMode(cmd.client);
		else if(cmd.arg[1] == "+i")
			chan->setInvitationMode(cmd.client, true);
		else if(cmd.arg[1] == "-t")
			chan->setChopChangeTopic(cmd.client);
		else if(cmd.arg[1] == "+t")
			chan->setChopChangeTopic(cmd.client, true);
		else if(cmd.arg[1] == "-k")
			chan->setWpMode(cmd.client, cmd.arg);
		else if(cmd.arg[1] == "+k")
			chan->setWpMode(cmd.client, cmd.arg);
		else if(cmd.arg[1] == "+o")
			chan->setChop(cmd.client, cmd.arg[1], true);
		else if(cmd.arg[1] == "-o")
			chan->setChop(cmd.client, cmd.arg[1]);
		else if(cmd.arg[1] == "+l") {
			// linux i only have access to stoi in c++11
			// cmd.chan->setLimitMode(cmd.client, std::stoi(cmd.arg[0]));
			int long nbr;
			std::stringstream(cmd.arg[2]) >> nbr;
			chan->setLimitMode(cmd.client, nbr);
		}
		else if(cmd.arg[1] == "-l")
			chan->setLimitMode(cmd.client);
		else
			throw std::invalid_argument(Error::ERR_UNKNOWNMODE(cmd.arg[1]));
	}

	// void list(const Cmd &cmd) { // faut til le faire ??

	// }

	void invite(const Cmd &cmd) {
		// CHECK LES RIGHTS DES GENS err 482
		if ((int)cmd.arg.size() != 2)
			throw std::invalid_argument(Error::ERR_NEEDMOREPARAMS("INVITE"));
		Channel *chan = CMDH::findChan(cmd.arg[1]);
		if (!chan) 
			throw std::invalid_argument(Error::ERR_NOSUCHCHANNEL(cmd.arg[1]));

		if (!cmd.client->isPartChan(chan))
			throw std::invalid_argument(Error::ERR_NOTONCHANNEL(chan->getName()));

		Client * toSend = &(Server::findClient(cmd.arg[0]));

		std::string msg = cmd.client->getName() + " INVITE " + toSend->getName() + ": " + chan->getName() + "\n";
		if (toSend->GetFd() == cmd.client->GetFd())
			throw std::invalid_argument(Error::ERR_USERONCHANNEL(cmd.arg[0], cmd.arg[1]));
		if (!toSend->isPartChan(chan))
			send(toSend->GetFd(), msg.c_str(), msg.length(), 0);
		else
			return ;
		chan->PendingInvite(toSend);
	}

	void msg(const Cmd &cmd) {
		std::cout << "FD**************" <<cmd.client->GetFd() << std::endl;
		if ((int)cmd.arg.size() < 2)
			throw std::invalid_argument(Error::ERR_NEEDMOREPARAMS("MSG"));

		std::string msg = cmd.client->getName();
		msg += ":";
		for(int i = 1; i < (int)cmd.arg.size(); i++) {
			msg += " ";
			msg += cmd.arg[i];
		}
		msg += "\n";

		// if its a chan
		if ((char)cmd.arg[0][0] == '#') {
			Channel *chan = CMDH::findChan(cmd.arg[0]);
			//chan does not exist
			if (!chan)
				throw std::invalid_argument(Error::ERR_NOSUCHCHANNEL(cmd.arg[0]));
			
			if (!chan->hasClient(cmd.client))
				std::invalid_argument(Error::ERR_NOTONCHANNEL(chan->getName())); 
			std::string chanMsg = "[" + chan->getName() + "] " + msg;
			chan->sendMSGClient(chanMsg, cmd.client);
		}
		else {
			Client * toSend = &(Server::findClient(cmd.arg[0]));
			send(toSend->GetFd(), msg.c_str(), msg.length(), 0);
		}



		// envoyer un message ********************************* 
	}
	void part(const Cmd &cmd) { // yeah works fine
		if ((int)cmd.arg.size() < 1)
			throw std::invalid_argument(Error::ERR_NEEDMOREPARAMS("PART"));
		Channel *chan = CMDH::findChan(cmd.arg[0]);
		//chan does not exist
		if (!chan)
			throw std::invalid_argument(Error::ERR_NOSUCHCHANNEL(cmd.arg[0]));
			// not on channel
		if (!chan->hasClient(cmd.client))
			throw std::invalid_argument(Error::ERR_NOTONCHANNEL(cmd.arg[0]));
		CMDH::removeClientChan(cmd.client, chan);
	}
	void quit(const Cmd &cmd) {
		cmd.client->setQuit();
	}
}
