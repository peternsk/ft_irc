#include "ft_irc.hpp"
// get Channels static
#include "cmd.hpp"


std::string chanName = "#lalal";
int main() {
	Client * bob = new Client("nana");
	Client * mia = new Client("babnaa");

	CMDH::clientsArr(bob);
	std::vector<Client *> clients = CMDH::clientsArr(mia);

	for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		std::cout << (*it)->getName() << std::endl;
	}

	Cmd cmd1;
	cmd1.client = bob;
	cmd1.cmd = JOIN;
	cmd1.arg.push_back(chanName);

	Cmd cmd2;
	cmd2.client = mia;
	cmd2.cmd = JOIN;
	cmd2.arg.push_back(chanName);
	cmd2.password.push_back("m");
	cmd2.password.push_back("mama");


	
	execCmd(cmd1);
	chanVec channels = CMDH::channelsArr();
	channels[0]->setWpMode(bob, "m");

	execCmd(cmd2);
	Cmd cmd3;
	cmd3.client = mia;
	cmd3.cmd = TOPIC;
	cmd3.arg.push_back("new topic");
	cmd3.chan = CMDH::findChan(chanName);
	execCmd(cmd3);

	Cmd cmd4;
	cmd4.client = mia;
	cmd4.cmd = TOPIC;
	cmd4.chan = CMDH::findChan(chanName);
	execCmd(cmd4);


	for (chanVec::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		std::cout << (*it)->getName() << " name" << std::endl;
	}


	// client are automaticaly destroy with the client disconnect function
	CMDH::clientDisconnect(bob);
	CMDH::clientDisconnect(mia);
	// void removeClientChan(Client * client, Channel * chan);

// comment je recois la struct et dependamment de se que je recois je fais dautre truc avec

// parsing

// executer les command ex private user Channel

// ??? array ? variable static pour les Channels et clients perhaps?

//// si je fais un container static avec les clients
// et les Channels jamais oublier de les enlever
// lorsque un user se deco ou le Channels doit etre detruit

}