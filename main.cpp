#include "ft_irc.hpp"

int main()
{
	try {
		channel *chan = new channel("channelname");
		p((chan->getName())); 
		p(chan->topic("nihongo no renshu"));
		delete chan;
	}
	catch(std::exception &e) {
		std::cout << "operation failed" <<  std::endl;
	}
	return 0;
}