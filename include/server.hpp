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
#include <list> //-> for list
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
#define BLU "\e[1;34m" //-> for blue color
#define MAG "\e[1;35m" //-> for magenta color
#define CYN "\e[1;36m" //-> for cyan color
#define BLK "\e[1;30m" //-> for black color
#define GRY "\e[1;90m" //-> for gray color
#define RESET "\e[0m" //-> to reset color
#define LBLU "\e[0;34m" //-> for light blue color
#define LMAG "\e[0;35m" //-> for light magenta color
#define LCYN "\e[0;36m" //-> for light cyan color
#define LGRN "\e[0;32m" //-> for light green color
#define LRED "\e[0;31m" //-> for light red color
#define LYEL "\e[0;33m" //-> for light yellow color
#define BWHT "\e[1;97m" //-> for bright white color
#define BGRN "\e[1;92m" //-> for bright green color
#define BRED "\e[1;91m" //-> for bright red color
#define BYEL "\e[1;93m" //-> for bright yellow color
#define BBLU "\e[1;94m" //-> for bright blue color
#define BMAG "\e[1;95m" //-> for bright magenta color
#define BCYN "\e[1;96m" //-> for bright cyan color
#define BBLK "\e[1;90m" //-> for bright black (dark gray) color



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
		void ircLogo();

		/****************/
		/* mid parssing */
		/****************/

		std::vector<std::string> setCmdList(std::string clientRequest);
		void cmdHandler(int fd, std::string clientRequest);
		int foundCmd(std::list <std::string>&cmdArr, const std::string& cmd);
		void printVector(std::vector<std::string> tokens);

		/****************/
		/*   CMD FUNC   */
		/****************/

		void JOIN(Client &m_client ,std::vector<std::string> tokens);
		void USER(Client &m_client ,std::vector<std::string> tokens);
		void KICK(Client &m_client ,std::vector<std::string> tokens);
		void INVITE(Client &m_client ,std::vector<std::string> tokens);
		void TOPIC(Client &m_client ,std::vector<std::string> tokens);
		void MODE(Client &m_client ,std::vector<std::string> tokens);
		void NICK(Client &m_client ,std::vector<std::string> tokens);
		void PRIVMSG(Client &m_client ,std::vector<std::string> tokens);

		/****************/
		/* handle class */
		/****************/

		Client& getClientClass(int fd);
		void addClientToList(int fd);

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

