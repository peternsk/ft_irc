#include "cmd.hpp"
namespace CMD {


	void join(const Cmd &cmd) {
		int nbWp = 0;
		// p("sdfdsffsd");
		for (int i = 0; i < (int)cmd.arg.size(); ++i)
		{
			try {
				// make sur that he is not already in the channel
				Channel *chan = CMDH::findChan(cmd.arg[i]);
				if (!CMDH::joinCheckMode(chan, cmd, nbWp))
					continue;
				p("joins channel");
				cmd.client->join(chan);
			}
			catch(std::exception & e) {
				p("channel doesnt exist so create it");
				// create the channels because it doesnt exist
				CMDH::channelsArr(cmd.client->join(cmd.arg[i]));
			}
		}
	}

	void topic(const Cmd &cmd) {
		if (cmd.arg.size() > 1)
			throw std::exception();
		if (cmd.arg.size() == 1)
			cmd.chan->topic(cmd.client, cmd.arg[0]);
		else
		{

			pp("this is the topic", cmd.chan->topic(cmd.client));
			// send to client the topic
		}
	}

	void kick(const Cmd &cmd) {
		if (cmd.chan->hasClient(cmd.client))
		{
			// get client to kick
			Client *toKick = CMDH::findClient(cmd.arg[0]);
			if (!toKick)
				return // exeption client to kick dont even exist
			cmd.client->kick(toKick, cmd.chan);
		}
		// else channels doesnt have the client
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
			return ; // error client does not exist
		// envoyer un message
	}

	void part(const Cmd &cmd) {
		CMDH::removeClientChan(cmd.client, cmd.chan);
	}

	void quit(const Cmd &cmd) {
		CMDH::clientDisconnect(cmd.client);
	}

	void cmsg(const Cmd &cmd) {
		cmd.chan->sendMSGClient(cmd.arg[0]);
	}
};
