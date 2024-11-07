// #include <cstdlib>
// #include <cstring>
// #include <iostream>
// #include <string>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <unistd.h>
// #include <netdb.h>
// #include <fcntl.h>

// class AClient;
// class AChannel;

#include <iostream>
#include <vector> //-> for vector
#include <map> //-> for map
#include <sys/socket.h> //-> for socket()
#include <sys/types.h> //-> for socket()
#include <netinet/in.h> //-> for sockaddr_in
#include <fcntl.h> //-> for fcntl()
#include <unistd.h> //-> for close()
#include <arpa/inet.h> //-> for inet_ntoa()
#include <poll.h> //-> for poll()
#include <csignal> //-> for signal()
#include <stdlib.h> //-> for atol

#define RED "\e[1;31m" //-> for red color
#define WHI "\e[0;37m" //-> for white color
#define GRE "\e[1;32m" //-> for green color
#define YEL "\e[1;33m" //-> for yellow color


/*********************************************************/
/*                   CLIENT CLASS                        */
/*********************************************************/

class Client //-> class for client
{
private:
	int Fd; //-> client file descriptor
	std::string IPadd; //-> client ip address
public:
	Client(){}; //-> default constructor
	int GetFd(){return Fd;} //-> getter for fd

	void SetFd(int fd){Fd = fd;} //-> setter for fd
	void setIpAdd(std::string ipadd){IPadd = ipadd;} //-> setter for ipadd
};

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */


/*********************************************************/
/*                STRUCTS / LINKED LIST                  */
/*********************************************************/

/* 	
std::string command; -> the argument of the command
s_cmdLinkedlist *next; -> next node
*/
typedef struct s_cmdLinkedlist {
	std::string command;
	s_cmdLinkedlist *next;
} t_cmdLinkedlist;


/* 	
std::string channel; -> the channel that the user want to join.
std::string key; -> the key to the channel that user need.
bool leaving; -. if there is a Zero, the client  is leaving all or one channel
s_joinList *next; -> next node
*/
typedef struct s_joinList {
	std::string channel;
	std::string key;
	bool leaving;
	s_joinList *next;
} t_joinList;


/*********************************************************/
/*                   SERVER CLASS                        */
/*********************************************************/

class Server {
    public:
        Server(int m_serPort, std::string m_serPassword);
        ~Server();
	    void serverInit();
	    void serSocket();
	    void acceptNewClient();
	    void receiveNewData(int fd);
	    static void signalHandler(int signum);
	    void closeFds();
	    void clearClients(int fd);

		/****************/
		/* mid parssing */
		/****************/

		void setCmdList(std::string clientRequest);
		int linkedListSize(t_cmdLinkedlist *cmdlist);
		void cmdHandler();


    private:
        int serPort;
        std::string serPassword;
	    int serSocFd;
	    static bool sig;
	    std::vector<Client> clients;
        // std::map<std::string, int> clientsMap;
        // std::map<std::string, int> channelMap;
	    std::vector<struct pollfd> fds;
		std::string command;

};