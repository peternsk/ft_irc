#include "ft_irc.hpp"
#include "struct.hpp"



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
		Cmd vectorToStruct(std::vector<std::string> tokens, int fd);


		/****************/
		/* handle class */
		/****************/

		Client& getClientClass(int fd);
		void addClientToList(int fd);
		static void checkName(std::string name);
		static Client &findClient(std::string name);

    private:
        int serPort;
        std::string serPassword;
	    int serSocFd;
	    static bool sig;
	    static std::vector<Client> clients;
        // std::map<std::string, int> clientsMap;
        // std::map<std::string, int> channelMap;
	    std::vector<struct pollfd> fds;
		std::string command;

};

