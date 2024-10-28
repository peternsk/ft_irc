#include "ft_irc.hpp"

int main()
{
	// when adding a user to a channel add to the user and the channel
	// user->addchannel(chan)
	// chan->adduser(user)
	try {
		channel *chan = new channel("channelname");
		p((chan->getName())); 
		Client *bob = new Client("BOB");
		Client *MIAM = new Client("MIAM");

		chan->addClient(bob);
		bob->join(chan);

		chan->addClient(MIAM);
		MIAM->join(chan);

		p("");
		p("miam channels");
		MIAM->showChannels();
		p("");

		p("bob channels");
		bob->showChannels();
		p("");

		p("list clients on cvhannels");
		chan->listClients();
		bob->kick(MIAM, chan);

		p("miam channels");
		MIAM->showChannels();

		p("bob channels");
		bob->showChannels();

		chan->setChopChangeTopic(bob, true);
		// p(chan->topic("nihongo no renshu"));
		chan->listClients();
		delete chan;
		delete MIAM;
		delete bob;
	}
	catch(std::exception &e) {
		std::cout << "operation failed" <<  std::endl;
	}
	return 0;
}