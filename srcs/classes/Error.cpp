#include "Error.hpp"
Error::Error(/* args */){}

Error::~Error(){}
std::string Error::ERR_ERRONEUSNICKNAME(std::string name){
    return  "\033[31;1m432 "  + name +  "\033[35;3m: Erroneous nickname\033[0m\n" ;
}
std::string Error::ERR_TOPICNOTSET   (std::string chan) { return "\033[31;1m331 \033[34m" + chan + "\033[35;3m :No topic is set\033[0m\n";}
std::string Error::ERR_NICKNAMEINUSE   (std::string name) { return "\033[31;1m433 \033[34m" + name + "\033[35;3m :Nickname is already in use\033[0m\n";}
// std::string Error::ERR_NICKCOLLISION   (std::string name) { return "436 " + name +  ":Nickname collision KILL from <user>@<host>";}
// std::string Error::ERR_UNAVAILRESOURCE   () {return "437  <nick/channel> :Nick/channel is temporarily unavailable";}
std::string Error::ERR_RESTRICTED   () {return "\033[35;3m \033[31;1m484 :Your connection is restricted!\033[0m\n";}
std::string Error::ERR_NEEDMOREPARAMS   (std::string cmd) { return "\033[31;1m461 \033[34m" + cmd + "\033[35;3m :Not enough parameters\033[0m\n";}
std::string Error::ERR_BANNEDFROMCHAN   () { return "<channel>\033[35;3m :Cannot join channel (+b)\033[0m\n";}
std::string Error::ERR_INVITEONLYCHAN    (std::string chan) {return "\033[31;1m473 \033[34m" + chan + "\033[35;3m :Cannot join channel (+i)\033[0m\n" ; }
std::string Error::ERR_BADCHANNELKEY    (std::string chan) { return "\033[31;1m475 \033[34m" + chan + "\033[35;3m :Cannot join channel (+k)\033[0m\n";}
std::string Error::ERR_CHANNELISFULL    (std::string chan) {return "\033[35;3m471 " + chan + ": Cannot join channel (+l)\033[0m\n";}
std::string Error::ERR_BADCHANMASK    () {return "\033[35;3m 476 <channel> : Bad Channel Mask\033[0m\n";}
std::string Error::ERR_NOSUCHCHANNEL     (std::string chan) {return "\033[31;1m403 \033[34m" + chan + "\033[35;3m : No such channel\033[0m\n";}
std::string Error::ERR_TOOMANYCHANNELS     () {return "\033[31;1m405 <channel name> : You have joined too many channels\033[0m\n";}
std::string Error::ERR_TOOMANYTARGETS    () {return "\033[31;1m407 <target> : <error code> recipients. <abort message>\033[0m\n";}
std::string Error::RPL_TOPIC    (std::string chan, std::string topic) {return "\033[31;1m332 \033[34m" + chan + "\033[35;3m :" + topic + "\033[0m\n";}
std::string Error::ERR_USERNOTINCHANNEL    (std::string name, std::string chan) {return "\033[31;1m441 \033[34m" + name + " " + chan + "\033[35;3m :They aren't on that channel\033[0m\n";}
std::string Error::ERR_NOTONCHANNEL   (std::string chan) {return "\033[31;1m442 \033[34m" +  chan + "\033[35;3m: You're not on that channel\033[0m\n";}
std::string Error::ERR_NOSUCHNICK   (std::string name) {return "\033[31;1m401 \033[34m" + name + "\033[35;3m: No such nick/channel\033[0m\n";}
std::string Error::ERR_USERONCHANNEL   (std::string name, std::string chan) {return "\033[31;1m443 \033[34m" + name + " " + chan + "\033[35;3m: is already on channel\033[0m\n";}
std::string Error::RPL_INVITING     () {return "\033[31;1m341  <channel> <nick>\033[0m\n";}
std::string Error::RPL_AWAY    () {return "\033[31;1m301 <nick> : <away message>\033[0m\n";}
std::string Error::ERR_KEYSET   () {return "\033[31;1m476 <channel>\033[35;3m : Channel key already set\033[0m\n"; }
// std::string Error::ERR_NOCHANMODES  () {return "477 <channel> :Channel doesn't support modes\033[0m\n";} // dont need ?
std::string Error::ERR_CHANOPRIVSNEEDED (std::string name) {return "\033[31;1m482 \033[34m" + name +  "\033[35;3m : You're not channel operator\033[0m\n";}
std::string Error::ERR_UNKNOWNMODE (std::string mode) {return "\033[31;1m472 \033[34m" + mode + "\033[35;3m : is unknown mode char to me\033[0m\n";}
std::string Error::RPL_CHANNELMODEIS () {return "<channel> <mode> <mode params>\033[0m\n";}
// std::string Error::RPL_BANLIST() {return "367 <channel> <banmask>\033[0m\n";}
// std::string Error::RPL_ENDOFBANLIST() {return "368 <channel> : End of channel ban list\033[0m\n";}
// std::string Error::RPL_EXCEPTLIST  () {return "348 <channel> <exceptionmask>\033[0m\n";}
std::string Error::RPL_ENDOFEXCEPTLIST  () {return "\033[31;1m349 <channel> : End of channel exception list\033[0m\n";} 
std::string Error::RPL_INVITELIST  () {return "\033[31;1m346 <channel> <invitemask>\033[0m\n";}
std::string Error::RPL_ENDOFINVITELIST () {return "\033[31;1m347  <channel> : End of channel invite list\033[0m\n";}
std::string Error::RPL_UNIQOPIS () {return "\033[31;1m325 <channel> <nickname>\033[0m\n";}
std::string Error::ERR_NONICK () {return "\033[31;1m431 : No nickname given\033[0m\n";}
std::string Error::ERR_WRONGCMD (std::string name, std::string wrongCmd) {return "\033[31;1m421 \033[34m" + name + " " + wrongCmd + "\033[35;3m : Unknown command\033[0m\n";}
std::string Error::RPL_JOINCHAN (std::string name, std::string chan) {return "\033[34m" + chan + "\033[35;3m : " + name + " Join the channel!\033[0m\n";}


// JOIN 
// TOPIC
// KICK
// NICK
// PART
