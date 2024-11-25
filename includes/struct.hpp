#pragma once

struct Cmd {
	short cmd;
	short mode;
	std::vector< std::string > arg;
	std::vector < std::string > password;
	Client * client;
	Channel * chan;
};