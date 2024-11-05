#pragma once

struct Cmd {
	Client * client;
	short cmd;
	std::vector< std::string > arg;
	std::vector < std::string > password;
};