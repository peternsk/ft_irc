#ifndef CMD_HPP
#define CMD_HPP

#include "ft_irc.hpp"
  
namespace CMD {
	void join(const Cmd &cmd);
	void topic(const Cmd &cmd);
	void kick(const Cmd &cmd);
	void nick(const Cmd &cmd);
	void mode(const Cmd &cmd);
	// void list(const Cmd &cmd);
	// void invite(const Cmd &cmd);
	void msg(const Cmd &cmd);
	void part(const Cmd &cmd);
	void quit(const Cmd &cmd);
	void cmsg(const Cmd &cmd);
}

void execCmd(const Cmd &cmd);

#endif