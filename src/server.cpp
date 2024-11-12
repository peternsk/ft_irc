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
/*    CMD DEF TEST   */
/********************/

void Server::JOIN(std::vector<std::string> tokens){
	std::cout << BLU << "unsing JOIN command" << WHI << std::endl;
}

void Server::USER(std::vector<std::string> tokens){
	std::cout << BLU << "unsing USER command" << WHI << std::endl;
}

void Server::KICK(std::vector<std::string> tokens){
	std::cout << BLU << "unsing KICK command" << WHI << std::endl;
}

void Server::INVITE(std::vector<std::string> tokens){
	std::cout << BLU << "unsing INVITE command" << WHI << std::endl;
}

void Server::TOPIC(std::vector<std::string> tokens){
	std::cout << BLU << "unsing TOPIC command" << WHI << std::endl;
}

void Server::MODE(std::vector<std::string> tokens){
	std::cout << BLU << "unsing MODE command" << WHI << std::endl;
}

void Server::NICK(std::vector<std::string> tokens){
	std::cout << BLU << "unsing NICK command" << WHI << std::endl;
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

	std::cout << BBLU << "------------------" << WHI << std::endl;
	std::cout << RED << tokens.at(0) << WHI << std::endl;
	std::cout << BBLU << "------------------" << WHI << std::endl;
	std::cout << GRE << tokens.at(1) << WHI << std::endl;
	std::cout << BBLU << "------------------" << WHI << std::endl;
	std::cout << YEL << tokens.at(2) << WHI << std::endl;
	std::cout << BBLU << "------------------" << WHI << std::endl;
	std::cout << BBLU << tokens.at(3) << WHI << std::endl;
	std::cout << BBLU << "------------------" << WHI << std::endl;
	std::cout << BBLU << tokens.at(4) << WHI << std::endl;
	std::cout << BBLU << "------------------" << WHI << std::endl;
	std::cout << BBLU << tokens.at(5) << WHI << std::endl;
	std::cout << BBLU << "------------------" << WHI << std::endl;

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

void Server::cmdHandler(std::string clientRequest){
	std::string cmdArr[] = {"JOIN", "USER", "KICK", "INVITE", "TOPIC", "MODE", "NICK"};
	std::list<std::string> cmdList(cmdArr, cmdArr + 7);
	std::vector<std::string> tokens = Server::setCmdList(clientRequest);
	void ((Server::*cmdFuncArr[]))(std::vector<std::string>tokens) = {&Server::JOIN, &Server::USER, &Server::KICK, &Server::INVITE, &Server::TOPIC, &Server::MODE, &Server::NICK};

	int cmdPos = Server::foundCmd(cmdList, tokens.at(1));
	if(cmdPos >= 0)
    	(this->*cmdFuncArr[cmdPos])(tokens);
}


void Server::printVector(std::vector<std::string> tokens){
	for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
    	std::cout << GRE << *it << WHI << std::endl;
}
