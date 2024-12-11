#include "cmd.hpp"
namespace CMD {



	void join(const Cmd &cmd) {
		int nbWp = 0;
		// normaly no error if you try to join even if you are already there >> simply ignored cmd
		for (int i = 0; i < (int)cmd.arg.size(); ++i) // I did this loop if joining multiple channels at the sametime
		{
				// make sur that he is not already in the channel
				// create the channels because it doesnt exist
				Channel *chan = CMDH::findChan(cmd.arg[i]);
				if (!chan)
					CMDH::channelsArr(cmd.client->join(cmd.arg[i]));
				else {
					if (!CMDH::joinCheckMode(chan, cmd, nbWp))
					continue;
					cmd.client->join(chan);
				}				
		}
	}

	void topic(const Cmd &cmd) {
		if (cmd.arg.size() > 1)
			throw std::invalid_argument(Error::ERR_NEEDMOREPARAMS("TOPIC"));
		cmd.chan->topic(cmd.client, cmd.arg[0]);
	}

	void kick(const Cmd &cmd) {
		if (cmd.chan->hasClient(cmd.client))
		{
			// get client to kick
			Client *toKick = CMDH::findClient(cmd.arg[0]);
			if (!toKick)
				throw invalid_argument(Error::ERR_NOSUCHNICK(cmd.arg[0]));
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
			if(cmd.mode == "-I")
				cmd.chan->setInvitationMode(cmd.client);
			if(cmd.mode == "+I")
				cmd.chan->setInvitationMode(cmd.client, true);
			if(cmd.mode == "-T")
				cmd.chan->setChopChangeTopic(cmd.client);
			if(cmd.mode == "+T")
				cmd.chan->setChopChangeTopic(cmd.client, true);
			if(cmd.mode == "-K")
				cmd.chan->setWpMode(cmd.client);
			if(cmd.mode == "+K")
				cmd.chan->setWpMode(cmd.client, cmd.arg[0]);
			if(cmd.mode == "+O")
				cmd.chan->setChop(cmd.client, cmd.arg[0], true);
			if(cmd.mode == "-O")
				cmd.chan->setChop(cmd.client, cmd.arg[0]);
			if(cmd.mode == "+L")
				cmd.chan->setLimitMode(cmd.client, std::stoi(cmd.arg[0]));
			if(cmd.mode == "-L")
				cmd.chan->setLimitMode(cmd.client);
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
		cmd.chan->sendMSGClient(cmd.arg[0]);
	}
};
