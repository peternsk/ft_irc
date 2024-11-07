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

void Server::irfLogo(){

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

void Server::receiveNewData(int fd)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1 , 0);

	if(bytes <= 0){
		std::cout << RED << "Client <" << fd << "> Disconnected" << WHI << std::endl;
		clearClients(fd);
		close(fd);
	}
	else{
		buff[bytes] = '\0';
		Server::cmdHandler(buff);
		// std::cout << YEL << "Client <" << fd << "> Data: " << WHI << buff;
		//here you can add your code to process the received data: parse, check, authenticate, handle the command, etc...
	}
}



/********************/
/*    CMD PARSER    */
/********************/

std::vector<std::string> Server::setCmdList(std::string clientRequest){

	std::vector<std::string> tokens;
    std::string token;

    size_t pos = 0;

    while (((pos = clientRequest.find(" ")) != std::string::npos) 
		|| ((pos = clientRequest.find(",")) != std::string::npos)){
        token = clientRequest.substr(0, pos);
        tokens.push_back(token);
        clientRequest.erase(0, pos + 1);
    }
    tokens.push_back(clientRequest);

	return tokens;
}

void Server::cmdHandler(std::string clientRequest){
	std::string cmdArr[] = {"JOIN", "USER", "KICK", "INVITE", "TOPIC", "MODE", "NICK"};
	std::vector<std::string> tokens = Server::setCmdList(clientRequest);

	std::cout << tokens.at(0) << std::endl;
	std::cout << tokens.at(1) << std::endl;
	std::cout << tokens.at(2) << std::endl;
	std::cout << tokens.at(3) << std::endl;
	std::cout << tokens.at(4) << std::endl;
	std::cout << tokens.at(5) << std::endl;
	std::cout << tokens.at(6) << std::endl;
	// void ((Server::*funcArr[]))() = {&Server::debug, &Server::info, &Server::warning, &Server::error};
	// void ((Server::*funcArr[]))() = {&Server::Client::join()};

}