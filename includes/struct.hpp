#ifndef CMD_STRUCT_HPP
#define CMD_STRUCT_HPP

struct Cmd {
	short cmd;
	short mode;
	std::vector< std::string > arg;
	std::vector < std::string > password;
	Client * client;
	Channel * chan;
};

#endif
 