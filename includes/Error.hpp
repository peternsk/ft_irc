#ifndef ERROR_HPP
#define ERROR_HPP
#include <iostream>

const std::string ERR_NONICKNAMEGIVEN  = "431 :No nickname given";

class Error
{
    private:
        Error(Error &obj);
        Error &operator=(Error &ob);

    public:
        Error();
        ~Error();
        // Error( /* class server */ server *obj );
        // std::string ERR_NONICKNAMEGIVEN  () "";

        static std::string ERR_TOPICNOTSET   (std::string chan);

        // le nickname quand tu essaye de le changer ou register nest pas correct
        static std::string ERR_ERRONEUSNICKNAME  (std::string name); 
        static std::string ERR_NICKNAMEINUSE   (std::string name) ; 
        // static std::string ERR_NICKCOLLISION   (std::string name); no need
        // static std::string ERR_UNAVAILRESOURCE   ();  // not too sure
        static std::string ERR_RESTRICTED   ();  
        static std::string ERR_NEEDMOREPARAMS   (std::string cmd); 
        static std::string ERR_BANNEDFROMCHAN   (); 
        static std::string ERR_INVITEONLYCHAN    (std::string chan); 
        static std::string ERR_BADCHANNELKEY    (std::string chan); 
        static std::string ERR_CHANNELISFULL    (std::string chan); 
        static std::string ERR_BADCHANMASK    (); 
        static std::string ERR_NOSUCHCHANNEL     (std::string chan); 
        static std::string ERR_TOOMANYCHANNELS     (); 
        static std::string ERR_TOOMANYTARGETS    (); 
        static std::string RPL_TOPIC    (std::string chan, std::string topic); 
        static std::string ERR_CHANOPRIVSNEEDED    (std::string name); 
        static std::string ERR_USERNOTINCHANNEL    (std::string name, std::string chan); 
        static std::string ERR_NOTONCHANNEL   (std::string chan); 
        static std::string ERR_NOSUCHNICK   (std::string name); 
        static std::string ERR_USERONCHANNEL   (std::string name, std::string chan); 
        static std::string RPL_INVITING     (); 
        static std::string RPL_AWAY    (); 
        // static std::string ERR_NOCHANMODES    (); // dont need ?
        static std::string ERR_UNKNOWNMODE (std::string mode); 
        static std::string RPL_CHANNELMODEIS (); 
        static std::string RPL_BANLIST(); 
        static std::string RPL_ENDOFBANLIST(); 
        static std::string RPL_EXCEPTLIST  (); 
        static std::string RPL_ENDOFEXCEPTLIST  (); 
        static std::string RPL_INVITELIST  (); 
        static std::string RPL_ENDOFINVITELIST (); 
        static std::string RPL_UNIQOPIS (); 
        static std::string ERR_KEYSET();
        static std::string ERR_NONICK ();

};

#endif