#include "ft_irc.hpp"

int main()
{
	try {
		channel *chan = new channel("channelname");
		p((chan->getName())); 
		Client *bob = new Client(true, "BOB");
		Client *MIAM = new Client(false, "MIAM");

		chan->addClient(bob);
		chan->addClient(bob);

		chan->setChopChangeTopic(bob, true);
		// p(chan->topic("nihongo no renshu"));
		delete chan;
		delete MIAM;
		delete bob;
	}
	catch(std::exception &e) {
		std::cout << "operation failed" <<  std::endl;
	}
	return 0;
}