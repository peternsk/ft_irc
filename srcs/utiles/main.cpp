#include "ft_irc.hpp"

int main(int ac, char**av)
{
    if(ac == 3){

	    Server ser(atol(av[1]), av[2]);
	    ser.ircLogo();
	    try{
		    signal(SIGINT, Server::signalHandler); //-> catch the signal (ctrl + c)
		    signal(SIGQUIT, Server::signalHandler); //-> catch the signal (ctrl + \)
		    ser.serverInit(); //-> initialize the server
	    }
	    catch(const std::exception& e){
		    ser.closeFds(); //-> close the file descriptors
		    std::cerr << e.what() << std::endl;
	    }
	    std::cout << "The Server Closed!" << std::endl;
    }
    std::cout << "missing argument..." << std::endl;
}
