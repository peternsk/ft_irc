#ifndef ERROR_HPP
#define ERROR_HPP
#include <iostream>

const std::string ERR_NONICKNAMEGIVEN  = "431 :No nickname given";

class Error
{
    private:
        // Error();
        // Error(Error &obj);
        // Error &operator=(Error &ob);
        // std::string name;

    public:
        // ~Error();
        // Error( /* class server */ server *obj );
        // std::string ERR_NONICKNAMEGIVEN  () ""; 
        std::string ERR_ERRONEUSNICKNAME  () const; 
        std::string ERR_NICKNAMEINUSE   () ; 
        std::string ERR_NICKCOLLISION   (); 
        std::string ERR_UNAVAILRESOURCE   (); 
        std::string ERR_RESTRICTED   (); 
        std::string ERR_NEEDMOREPARAMS   (); 
        std::string ERR_BANNEDFROMCHAN   (); 
        std::string ERR_INVITEONLYCHAN    (); 
        std::string ERR_BADCHANNELKEY    (); 
        std::string ERR_CHANNELISFULL    (); 
        std::string ERR_BADCHANMASK    (); 
        std::string ERR_NOSUCHCHANNEL     (); 
        std::string ERR_TOOMANYCHANNELS     (); 
        std::string ERR_TOOMANYTARGETS    (); 
        std::string RPL_TOPIC    (); 
        std::string ERR_UNAVAILRESOURCE    (); 
        std::string ERR_CHANOPRIVSNEEDED    (); 
        std::string ERR_USERNOTINCHANNEL    (); 
        std::string ERR_NOTONCHANNEL   (); 
        std::string ERR_NOSUCHNICK   (); 
        std::string ERR_USERONCHANNEL   (); 
        std::string RPL_INVITING     (); 
        std::string RPL_AWAY    (); 
        std::string ERR_NOCHANMODES    (); 
        std::string ERR_KEYSET   (); 
        std::string ERR_NOCHANMODES  (); 
        std::string ERR_CHANOPRIVSNEEDED (); 
        std::string ERR_UNKNOWNMODE (); 
        std::string RPL_CHANNELMODEIS (); 
        std::string RPL_BANLIST(); 
        std::string RPL_ENDOFBANLIST(); 
        std::string RPL_EXCEPTLIST  (); 
        std::string RPL_ENDOFEXCEPTLIST  (); 
        std::string RPL_INVITELIST  (); 
        std::string RPL_ENDOFINVITELIST (); 
        std::string RPL_UNIQOPIS (); 
};

#endif