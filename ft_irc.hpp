#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
#include "client.hpp"
//class
#include "channel.hpp"
#include "cmdUtils.hpp"

#define p(x) std::cout << x << std::endl;
#define pp(x, y) std::cout << x << ", " << y<< std::endl;
#define ppp(x, y, z) std::cout << x << ", " << y << ", " << z << std::endl;

#define JOIN	0
#define TOPIC	1 
#define KICK	2
#define NICK	3
#define MODE	4
#define LIST	5
#define INVITE	6
#define MSG		7
#define PART	8
#define QUIT	9
#define CMSG	10
#define DISK	11

struct Cmd {
	Client * client;
	short cmd;
	std::vector< std::string > arg;
	std::vector < std::string > password;
};

// attention dans le projet avec les containers TOUJOURS FINIR DE LIRE AVANT DECRIRE
