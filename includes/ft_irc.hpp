#pragma once

#include <cstring>
#include <iostream>
#include <vector> //-> for vector
#include <map> //-> for map
#include <list> //-> for list
#include <sys/socket.h> //-> for socket()
#include <sys/types.h> //-> for socket()
#include <netinet/in.h> //-> for sockaddr_in
#include <fcntl.h> //-> for fcntl()
#include <unistd.h> //-> for close()
#include <arpa/inet.h> //-> for inet_ntoa()
#include <poll.h> //-> for poll()
#include <csignal> //-> for signal()
#include <stdlib.h> //-> for atol


/*---- color ----*/
#define RED "\e[1;31m" //-> for red color
#define WHI "\e[0;37m" //-> for white color
#define GRE "\e[1;32m" //-> for green color
#define YEL "\e[1;33m" //-> for yellow color
#define BLU "\e[1;34m" //-> for blue color
#define MAG "\e[1;35m" //-> for magenta color
#define CYN "\e[1;36m" //-> for cyan color
#define BLK "\e[1;30m" //-> for black color
#define GRY "\e[1;90m" //-> for gray color
#define RESET "\e[0m" //-> to reset color
#define LBLU "\e[0;34m" //-> for light blue color
#define LMAG "\e[0;35m" //-> for light magenta color
#define LCYN "\e[0;36m" //-> for light cyan color
#define LGRN "\e[0;32m" //-> for light green color
#define LRED "\e[0;31m" //-> for light red color
#define LYEL "\e[0;33m" //-> for light yellow color
#define BWHT "\e[1;97m" //-> for bright white color
#define BGRN "\e[1;92m" //-> for bright green color
#define BRED "\e[1;91m" //-> for bright red color
#define BYEL "\e[1;93m" //-> for bright yellow color
#define BBLU "\e[1;94m" //-> for bright blue color
#define BMAG "\e[1;95m" //-> for bright magenta color
#define BCYN "\e[1;96m" //-> for bright cyan color
#define BBLK "\e[1;90m" //-> for bright black (dark gray) color

//class
#include "channel.hpp"

#define p(x) std::cout << x << std::endl;
#define pp(x, y) std::cout << x << ", " << y<< std::endl;
#define ppp(x, y, z) std::cout << x << ", " << y << ", " << z << std::endl;


// attention dans le projet avec les containers TOUJOURS FINIR DE LIRE AVANT DECRIRE
