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
		if (cmd.chan->hasClient(cmd.client))
		{
			// get client to kick
			Client *toKick = CMDH::findClient(cmd.arg[0]);
			if (!toKick)
				throw std::invalid_argument(Error::ERR_NOSUCHNICK(cmd.arg[0]));
			cmd.client->kick(toKick, cmd.chan);
		}
		 // does not have the one doing the cmd
		else
			throw std::invalid_argument(Error::ERR_NOTONCHANNEL(cmd.chan->getName()));
	}

	void nick(const Cmd &cmd) {
		cmd.client->setName(cmd.arg[0]);
	}

	void mode(const Cmd &cmd) {
		Channel *chan = CMDH::findChan(cmd.arg[0]);
			if(cmd.arg[1] == "-i")
				chan->setInvitationMode(cmd.client);
			if(cmd.arg[1] == "+i")
				chan->setInvitationMode(cmd.client, true);
			if(cmd.arg[1] == "-t")
				chan->setChopChangeTopic(cmd.client);
			if(cmd.arg[1] == "+t")
				chan->setChopChangeTopic(cmd.client, true);
			if(cmd.arg[1] == "-k")
				chan->setWpMode(cmd.client);
			if(cmd.arg[1] == "+k")
				chan->setWpMode(cmd.client, cmd.arg[2]);
			if(cmd.arg[1] == "+o")
				chan->setChop(cmd.client, cmd.arg[1], true);
			if(cmd.arg[1] == "-o")
				chan->setChop(cmd.client, cmd.arg[1]);
			if(cmd.arg[1] == "+l") {
				// linux i only have access to stoi in c++11
				// cmd.chan->setLimitMode(cmd.client, std::stoi(cmd.arg[0]));
				int long nbr;
				std::stringstream(cmd.arg[1]) >> nbr;
				chan->setLimitMode(cmd.client, nbr);
			}
			if(cmd.arg[1] == "-l")
				chan->setLimitMode(cmd.client);
		}

	// void list(const Cmd &cmd) { // faut til le faire ??

	// }
	// void invite(const Cmd &cmd) { // comment faire?

	// }
	void msg(const Cmd &cmd) {
		Client * toSend = CMDH::findClient(cmd.arg[0]);
		if (!toSend)
			std::invalid_argument(Error::ERR_NOSUCHNICK(cmd.arg[0]));
		// envoyer un message *********************************
	}
	void part(const Cmd &cmd) {
		CMDH::removeClientChan(cmd.client, cmd.chan);
	}
	void quit(const Cmd &cmd) {
		CMDH::clientDisconnect(cmd.client);
	}
	void cmsg(const Cmd &cmd) {
		if (!cmd.chan->hasClient(cmd.client))
			std::invalid_argument(Error::ERR_NOTONCHANNEL(cmd.chan->getName())); 
		cmd.chan->sendMSGClient(cmd.arg[0], cmd.client);
	}
}
