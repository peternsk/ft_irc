#include "../include/server.hpp"


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

void Server::acceptNewClient()
{
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

/********************/
/*    CMD DEF TEST   */
/********************/

void Server::JOIN(Client &m_client ,std::vector<std::string> tokens){
	(void)m_client;
	std::cout << BLU << "unsing JOIN command" << WHI << std::endl;
	Server::printVector(tokens);
}

void Server::USER(Client &m_client ,std::vector<std::string> tokens){
	(void)m_client;
	std::cout << BLU << "unsing USER command" << WHI << std::endl;
	Server::printVector(tokens);
}

void Server::KICK(Client &m_client ,std::vector<std::string> tokens){
	(void)m_client;
	std::cout << BLU << "unsing KICK command" << WHI << std::endl;
	Server::printVector(tokens);
}

void Server::INVITE(Client &m_client ,std::vector<std::string> tokens){
	(void)m_client;
	std::cout << BLU << "unsing INVITE command" << WHI << std::endl;
	Server::printVector(tokens);
}

void Server::TOPIC(Client &m_client ,std::vector<std::string> tokens){
	(void)m_client;
	std::cout << BLU << "unsing TOPIC command" << WHI << std::endl;
	Server::printVector(tokens);
}

void Server::MODE(Client &m_client ,std::vector<std::string> tokens){
	(void)m_client;
	std::cout << BLU << "unsing MODE command" << WHI << std::endl;
	Server::printVector(tokens);
}

void Server::NICK(Client &m_client ,std::vector<std::string> tokens){
	(void)m_client;
	std::cout << BLU << "unsing NICK command" << WHI << std::endl;
	Server::printVector(tokens);
}

void Server::PRIVMSG(Client &m_client ,std::vector<std::string> tokens){
	(void)m_client;
	std::cout << BLU << "unsing PRIVMSG command" << WHI << std::endl;
	Server::printVector(tokens);
}


/********************/
/*    CMD PARSER    */
/********************/

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
    tokens.push_back(clientRequest);

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
	std::string cmdArr[] = {"JOIN", "USER", "KICK", "INVITE", "TOPIC", "MODE", "NICK", "PRIVMSG"};
	std::list<std::string> cmdList(cmdArr, cmdArr + 8);
	std::vector<std::string> tokens = Server::setCmdList(clientRequest);
	void ((Server::*cmdFuncArr[]))(Client &m_client, std::vector<std::string>tokens) = {&Server::JOIN, &Server::USER, &Server::KICK,
			&Server::INVITE, &Server::TOPIC, &Server::MODE, &Server::NICK, &Server::PRIVMSG};

	int cmdPos = foundCmd(cmdList, tokens.at(1));
	if(cmdPos >= 0)
    	(this->*cmdFuncArr[cmdPos])(getClientClass(m_fd) ,tokens);
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
