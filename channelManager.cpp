#include "channel.hpp"
#include "client.hpp"
#include "ft_irc.hpp"
#include "channelManagerUtils.hpp"

// get Channels static

std::string chanName = "#lalal";
int main() {
	Client * bob = new Client("nana");
	Client * mia = new Client("babnaa");

	CCM::clientsArr(bob);
	std::vector<Client *> clients = CCM::clientsArr(mia);

	for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		std::cout << (*it)->getName() << std::endl;
	}

	std::vector<Channel *>& Channels = CCM::channelsArr(bob->join(chanName));
	for (std::vector<Channel *>::iterator it = Channels.begin(); it != Channels.end(); ++it)
	{
		std::cout << (*it)->getName() << std::endl;
	}
	Channel * chan = CCM::findChan(Channels, chanName);

	std::cout << chan->getName()  << std::endl;
	
	mia->join(chan);
	std::cout << chan->getNbPeople() << "before removed" << std::endl;
	CCM::removeClientChan(bob, chan);
	CCM::removeClientChan(mia, chan);
	// std::cout << chan->getNbPeople() << "after removed" << std::endl;

	std::vector<Channel *>& Channelss = CCM::channelsArr();
		std::cout << Channelss.size() << std::endl;

	for (std::vector<Channel *>::iterator it = Channelss.begin(); it != Channelss.end(); ++it)
	{
		std::cout << (*it)->getName() << Channelss.size() << std::endl;
		
	}
	// client are automaticaly destroy with the client disconnect function
	CCM::clientDisconnect(bob);
	CCM::clientDisconnect(mia);
	// void removeClientChan(Client * client, Channel * chan);

// comment je recois la struct et dependamment de se que je recois je fais dautre truc avec

// parsing

// executer les command ex private user Channel

// ??? array ? variable static pour les Channels et clients perhaps?

//// si je fais un container static avec les clients
// et les Channels jamais oublier de les enlever
// lorsque un user se deco ou le Channels doit etre detruit

}