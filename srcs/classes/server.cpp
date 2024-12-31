// #include "server.hpp"
// #include "cmdUtils.hpp"
// #include "cmd.hpp"

#include "ft_irc.hpp"

std::vector<Client> Server::clients;


/*********************************************************/
/*            SERVER CONSTRUCTOR / DESTRUCTOR            */
/*********************************************************/

Server::Server(int m_serPort, std::string m_serPassword)
    : serPort(m_serPort), serPassword(m_serPassword){
    serSocFd = -1;
}

Server::~Server(){
}


/*********************************************************/
/*                   SERVER METHODS                      */
/*********************************************************/


/********************/
/*   SERVER INIT    */
/********************/

void Server::ircLogo(){

	std::cout << "▒▓████▓▒ ▒▓███████▓▒   ▒▓██████▓▒ " << std::endl;
	std::cout << "  ▒██▒   ▒▓█▓▒  ▒▓█▓▒ ▒▓█▓▒  ▒▓█▓▒" << std::endl;
	std::cout << "  ▒██▒   ▒▓█▓▒  ▒▓█▓▒ ▒▓█▓▒       " << std::endl;
	std::cout << "  ▒██▒   ▒▓███████▓▒  ▒▓█▓▒       " << std::endl;
	std::cout << "  ▒██▒   ▒▓█▓▒  ▒▓█▓▒ ▒▓█▓▒       " << std::endl;
	std::cout << "  ▒██▒   ▒▓█▓▒  ▒▓█▓▒ ▒▓█▓▒  ▒▓█▓▒" << std::endl;
	std::cout << "▒▓████▓▒ ▒▓█▓▒  ▒▓█▓▒  ▒▓██████▓▒ " << std::endl;
	std::cout << "     [ Internet Relay Chat ]" << std::endl;
	std::cout << std::endl;
}

void Server::serSocket()
{
	struct sockaddr_in add;
	struct pollfd NewPoll;
	add.sin_family = AF_INET;
    std::cout << YEL << "SERVER PORT: " << this->serPort << WHI << std::endl;
    std::cout << YEL << "SERVER PASS: " << this->serPassword << WHI << std::endl;
	add.sin_port = htons(this->serPort);
	add.sin_addr.s_addr = INADDR_ANY;

	this->serSocFd = socket(AF_INET, SOCK_STREAM, 0);
	if(this->serSocFd == -1)
		throw(std::runtime_error("faild to create socket"));

	int en = 1;
	if(setsockopt(this->serSocFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		throw(std::runtime_error("faild to set option (SO_REUSEADDR) on socket"));
	if (fcntl(this->serSocFd, F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error("faild to set option (O_NONBLOCK) on socket"));
	if (bind(this->serSocFd, (struct sockaddr *)&add, sizeof(add)) == -1)
		throw(std::runtime_error("faild to bind socket"));
	if (listen(this->serSocFd, SOMAXCONN) == -1)
		throw(std::runtime_error("listen() faild"));

	NewPoll.fd = this->serSocFd;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;
	fds.push_back(NewPoll);
}

void Server::serverInit()
{
	serSocket();
	std::cout << GRE << "Server <" << serSocFd << "> Connected" << WHI << std::endl;
	std::cout << "Waiting to accept a connection...\n";
	while (Server::sig == false)
	{
		if((poll(&fds[0],fds.size(),-1) == -1) && Server::sig == false)
			throw(std::runtime_error("poll() faild"));

		for (size_t i = 0; i < fds.size(); i++)
		{
			std::cout << "test 1...\n";
			if (fds[i].revents & POLLIN)
			{
				if (fds[i].fd == serSocFd)
					acceptNewClient();
				else
					receiveNewData(fds[i].fd);
			}
		}
	}
	closeFds();
}

bool Server::sig = false;

void Server::signalHandler(int signum){
    (void)signum;
    std::cout << "signal receieve" << std::endl;
    Server::sig = true;
}

/********************/
/*   SERVER CLOSE   */
/********************/

void Server::closeFds(){
	for(size_t i = 0; i < clients.size(); i++){
		std::cout << RED << "Client <" << clients[i].GetFd() << "> Disconnected" << WHI << std::endl;
		close(clients[i].GetFd());
	}
	if (serSocFd != -1){
		std::cout << RED << "Server <" << serSocFd << "> Disconnected" << WHI << std::endl;
		close(serSocFd);
	}
}

void Server::clearClients(int fd){
	for(size_t i = 0; i < fds.size(); i++){
		if (fds[i].fd == fd)
			{fds.erase(fds.begin() + i); break;}
	}
	for(size_t i = 0; i < clients.size(); i++){
		if (clients[i].GetFd() == fd)
			{clients.erase(clients.begin() + i); break;}
	}

}


/********************/
/*  SERVER REQUEST  */
/********************/
int BUFCLIENTNAME = 0;
void Server::acceptNewClient()
{

	std::cout << "test 2...\n";
	Client cli;
	struct sockaddr_in cliadd;
	struct pollfd NewPoll;
	socklen_t len = sizeof(cliadd);

	int incofd = accept(serSocFd, (sockaddr *)&(cliadd), &len);
	if (incofd == -1)
		{std::cout << "accept() failed" << std::endl; return;}

	if (fcntl(incofd, F_SETFL, O_NONBLOCK) == -1)
		{std::cout << "fcntl() failed" << std::endl; return;}

	NewPoll.fd = incofd;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;

	cli.SetFd(incofd);
	cli.setIpAdd(inet_ntoa((cliadd.sin_addr)));

			// NOT SURE
			std::stringstream ss;
			ss << (BUFCLIENTNAME);
			cli.setName(ss.str());
			BUFCLIENTNAME++;

	clients.push_back(cli);
	fds.push_back(NewPoll);

	std::cout << GRE << "Client <" << incofd << "> Connected" << WHI << std::endl;
}

void Server::receiveNewData(int m_fd)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	ssize_t bytes = recv(m_fd, buff, sizeof(buff) - 1 , 0);

	if(bytes <= 0){
		std::cout << RED << "Client <" << m_fd << "> Disconnected" << WHI << std::endl;
		clearClients(m_fd);
		close(m_fd);
	}
	else{
		buff[bytes] = '\0';
		Server::cmdHandler(m_fd, buff);
	}
}

std::vector<std::string> Server::setCmdList(std::string clientRequest){

	std::vector<std::string> tokens;
    std::string token;

    size_t pos = 0;

    while (((pos = clientRequest.find(" ")) != std::string::npos)
		|| ((pos = clientRequest.find(",")) != std::string::npos)
		|| ((pos = clientRequest.find('\n')) != std::string::npos)
		|| ((pos = clientRequest.find('\t')) != std::string::npos)){

        token = clientRequest.substr(0, pos);
		if(token[0] != ':' && tokens.empty() == 1){
        	tokens.push_back("EMPTY");
        	// tokens.push_back(token);
		}
        tokens.push_back(token);
        clientRequest.erase(0, pos + 1);
    }
    // tokens.push_back(clientRequest); tout est enlever normalement fac c vide cause des probleme sinon
	return tokens;
}

int Server::foundCmd(std::list <std::string>&cmdArr, const std::string& cmd) {
	int pos = 0;
	for (std::list<std::string>::iterator it = cmdArr.begin(); it != cmdArr.end(); ++it) {
		if(*it == cmd){
    		std::cout << GRE << *it << WHI << std::endl;
			return pos;
		}
		pos++;
    }
	return (std::cout << RED << "COMMAND NOT FOUND" << WHI << std::endl, -1);
}

void Server::cmdHandler(int m_fd, std::string clientRequest){
	std::string cmdArr[] = {"JOIN", "KICK", "TOPIC", "MODE", "NICK",  "MSG", "PART", "QUIT", "USER", "INVITE"};

	std::list<std::string> cmdList(cmdArr, cmdArr + 8);

	std::vector<std::string> tokens = Server::setCmdList(clientRequest);

	//print tokens DEBUG
	std::cout << std::endl;
	int i = 0;
	for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
		std::cout << "TOKENS" << i << ":"<< *it << std::endl;
		i++;
	}
	std::cout << "END"<< std::endl;


	void (*cmdFuncArr[])(const Cmd &cmd) = {CMD::join, CMD::kick,
			CMD::topic, CMD::mode, CMD::nick, CMD::msg, CMD::part, CMD::quit}; // y va falloir add cmsg message pour channel

	int cmdPos = foundCmd(cmdList, tokens.at(1));


	if(cmdPos >= 0){
		Cmd cmd = vectorToStruct(tokens, m_fd);
		try {
			std::cout << "client name" << cmd.client->getName() << std::endl;
    		(cmdFuncArr[cmdPos])(cmd);
		}
		catch  (const std::exception& e) {
			// send the error to the clients
			send(m_fd, e.what(), strlen(e.what()), 0);
		}
	}
}

void Server::printVector(std::vector<std::string> tokens){
	for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it){
		std::cout << BBLU << "------------------" << WHI << std::endl;
    	std::cout << GRE << *it << WHI << std::endl;
	}
}

/****************/
/* Client class */
/****************/

void Server::addClientToList(int fd){
	/*

	*/
	std::cout << MAG << "Client FD : " << LBLU << fd << std::endl;
}

void Server::checkName(std::string name) {
	std::vector<Client>::iterator it;
	for (it = clients.begin(); it != clients.end(); ++it) {
		if (name == it->getName())
			throw std::invalid_argument(Error::ERR_NICKNAMEINUSE(name));
	}
	for (int i = 0; i < (int)name.size(); i++) {
    	if (!std::isalnum(static_cast<unsigned char>(name[i])))
			throw std::invalid_argument(Error::ERR_ERRONEUSNICKNAME(name));
    	}
}

Client &Server::findClient(std::string name) {
	std::vector<Client>::iterator it;
	for (it = clients.begin(); it != clients.end(); ++it) {
		if (name == it->getName())
			return *it;
	}
	throw std::invalid_argument(Error::ERR_NOSUCHNICK(name));
}

Client& Server::getClientClass(int fd){

	std::vector<Client>::iterator it;
	for (it = clients.begin(); it != clients.end(); ++it) {
		if(it->GetFd() == fd){
			std::cout << MAG << "Client FD : " << LBLU << it->GetFd() << std::endl;
			break;
		}
	}
	return *it;
}

Cmd Server::vectorToStruct(std::vector<std::string> tokens, int fd){
	Cmd newStruct;

	int vectPos = 0;
	bool chanSwitch = false;
	// jai modifier de if a des else if pour si ya dequoi de pas correct
	for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it){
		if(it->at(0) == ':' && vectPos == 0)
			newStruct.prefix = it->data();
		else if(it->length() > 0 && vectPos == 1)
			newStruct.cmd = it->data();
		
		// else if(Server::isMode(it->data()) && vectPos == 3)
		// 	newStruct.mode = it->data();

		else if(it->at(0) == ':' && vectPos > 0)
			newStruct.arg.push_back(it->data());

		else if (newStruct.cmd == "JOIN" && it->at(0) == '#' && vectPos > 0) {
			newStruct.arg.push_back(it->data());
			chanSwitch = true; // chanswitch ca sert a quoi?
		}
		else if(it->at(0) == '#' && vectPos > 0){
			newStruct.arg.push_back(it->data());
		}
		else if(it->at(0) && vectPos > 0 && chanSwitch == true)
			newStruct.password.push_back(it->data()); 
		else if (*it != "EMPTY") {
			newStruct.arg.push_back(it->data());
		}
		vectPos++;
	}
	newStruct.client = &Server::getClientClass(fd);
	return newStruct;
}


// cestt supposer marcher comment la avec les chans 

// si ya personne dans une channel ca doit delete la chan /// marche pas

// check list
// topic
// mode +k -k +i -i +t

// probleme si tu fais une commande avec un espace sans rien