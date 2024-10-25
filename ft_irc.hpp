#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

//class
#include "channel.hpp"
#include "operator.hpp"

#define p(x) std::cout << x << std::endl;
#define pp(x, y) std::cout << x << ", " << y<< std::endl;
#define ppp(x, y, z) std::cout << x << ", " << y << ", " << z << std::endl;


// attention dans le projet avec les containers TOUJOURS FINIR DE LIRE AVANT DECRIRE
