#include "Error.hpp"
Error::Error(/* args */){}

Error::~Error(){}
std::string Error::ERR_ERRONEUSNICKNAME(std::string name){
    return  "432 "  + name +  ":Erroneous nickname" ;
}
std::string Error::ERR_TOPICNOTSET   (std::string chan) { return "331 " + chan + ":No topic is set\n";}
std::string Error::ERR_NICKNAMEINUSE   (std::string name) { return "433 " + name + ":Nickname is already in use\n";}
// std::string Error::ERR_NICKCOLLISION   (std::string name) { return "436 " + name +  ":Nickname collision KILL from <user>@<host>";}
// std::string Error::ERR_UNAVAILRESOURCE   () {return "437  <nick/channel> :Nick/channel is temporarily unavailable";}
std::string Error::ERR_RESTRICTED   () {return " 484 :Your connection is restricted!\n";}
std::string Error::ERR_NEEDMOREPARAMS   (std::string cmd) { return "461 " + cmd + ":Not enough parameters\n";}
std::string Error::ERR_BANNEDFROMCHAN   () { return "<channel> :Cannot join channel (+b)\n";}
std::string Error::ERR_INVITEONLYCHAN    (std::string chan) {return "473 " + chan + ":Cannot join channel (+i)\n" ; }
std::string Error::ERR_BADCHANNELKEY    (std::string chan) { return "475 " + chan + ":Cannot join channel (+k)\n";}
std::string Error::ERR_CHANNELISFULL    () {return "471 <channel> :Cannot join channel (+l)\n";}
std::string Error::ERR_BADCHANMASK    () {return " 476 <channel> :Bad Channel Mask\n";}
std::string Error::ERR_NOSUCHCHANNEL     (std::string chan) {return "403 " + chan + " :No such channel\n";}
std::string Error::ERR_TOOMANYCHANNELS     () {return "405 <channel name> :You have joined too many channels\n";}
std::string Error::ERR_TOOMANYTARGETS    () {return "407 <target> :<error code> recipients. <abort message>\n";}
std::string Error::RPL_TOPIC    (std::string chan, std::string topic) {return "332 " + chan + " :" + topic + "\n";}
std::string Error::ERR_USERNOTINCHANNEL    (std::string name, std::string chan) {return "441 " + name + " " + chan + ":They aren't on that channel\n";}
std::string Error::ERR_NOTONCHANNEL   (std::string chan) {return "442 " +  chan + ":You're not on that channel\n";}
std::string Error::ERR_NOSUCHNICK   (std::string name) {return "401 " + name + ":No such nick/channel\n";}
std::string Error::ERR_USERONCHANNEL   () {return "443  <user> <channel> :is already on channel\n";}
std::string Error::RPL_INVITING     () {return "341  <channel> <nick>\n";}
std::string Error::RPL_AWAY    () {return "301 <nick> :<away message>\n";}
std::string Error::ERR_KEYSET   () {return "476 <channel> :Channel key already set\n"; }
std::string Error::ERR_NOCHANMODES  () {return "477 <channel> :Channel doesn't support modes\n";}
std::string Error::ERR_CHANOPRIVSNEEDED (std::string name) {return "482 " + name +  ":You're not channel operator\n";}
std::string Error::ERR_UNKNOWNMODE () {return "472 <char> :is unknown mode char to me for <channel>\n";}
std::string Error::RPL_CHANNELMODEIS () {return "<channel> <mode> <mode params>\n";}
std::string Error::RPL_BANLIST() {return "367 <channel> <banmask>\n";}
std::string Error::RPL_ENDOFBANLIST() {return "368 <channel> :End of channel ban list\n";}
std::string Error::RPL_EXCEPTLIST  () {return "348 <channel> <exceptionmask>\n";}
std::string Error::RPL_ENDOFEXCEPTLIST  () {return "349 <channel> :End of channel exception list\n";} 
std::string Error::RPL_INVITELIST  () {return "346 <channel> <invitemask>\n";}
std::string Error::RPL_ENDOFINVITELIST () {return "347  <channel> :End of channel invite list\n";}
std::string Error::RPL_UNIQOPIS () {return "325 <channel> <nickname>\n";}


// JOIN 
// TOPIC
// KICK
// NICK
// PART

// lorsque parsing a command checker si le client et channel exist