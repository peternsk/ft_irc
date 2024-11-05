#include "cmd.hpp"

namespace CMD {
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
	void kick(const Cmd &cmd);
	void nick(const Cmd &cmd);
	void mode(const Cmd &cmd);
	void list(const Cmd &cmd);
	void invite(const Cmd &cmd);
	void msg(const Cmd &cmd);
	void part(const Cmd &cmd);
	void quit(const Cmd &cmd);
	void cmsg(const Cmd &cmd);
	void disc(const Cmd &cmd);

}

void execCmd(const Cmd &cmd) {
	if (!cmd.client)
	{
		p("euhh problem ave client")
		return ;
	}
	static void (*cmdlist[])(const Cmd &) = {
    	CMD::join,
    	CMD::topic
    	// CMD::kick,
    	// CMD::nick,
    	// CMD::mode,
    	// CMD::list,
    	// CMD::invite,
    	// CMD::msg,
    	// CMD::part,
    	// CMD::quit,
    	// CMD::cmsg,
		// CMD::disc
	};
	cmdlist[cmd.cmd](cmd);
}