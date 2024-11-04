#include "Error.hpp"
Error::Error(/* args */)
{
}

Error::~Error()
{
}

std::string Error::ERR_ERRONEUSNICKNAME() const {
    return "432" <</* server->client->name */ << " :Erroneous nickname" ;
}


std::string Error::ERR_NICKNAMEINUSE   () { return "433 <nick> :Nickname is already in use";}
std::string Error::ERR_NICKCOLLISION   () { return " 436 <nick> :Nickname collision KILL from <user>@<host>";}
std::string Error::ERR_UNAVAILRESOURCE   () {return "437  <nick/channel> :Nick/channel is temporarily unavailable";}
std::string Error::ERR_RESTRICTED   () {return " 484 :Your connection is restricted!";}
std::string Error::ERR_NEEDMOREPARAMS   () { return " 461 <command> :Not enough parameters";}
std::string Error::ERR_BANNEDFROMCHAN   () { return "<channel> :Cannot join channel (+b)";}
std::string Error::ERR_INVITEONLYCHAN    () {return "473 <channel> :Cannot join channel (+i)" ; }
std::string Error::ERR_BADCHANNELKEY    () { return " 475 <channel> :Cannot join channel (+k)";}
std::string Error::ERR_CHANNELISFULL    () {return "471 <channel> :Cannot join channel (+l)";}
std::string Error::ERR_BADCHANMASK    () {return " 476 <channel> :Bad Channel Mask";}
std::string Error::ERR_NOSUCHCHANNEL     () {return "403 <channel name> :No such channel";}
std::string Error::ERR_TOOMANYCHANNELS     () {return "405 <channel name> :You have joined too many channels";}
std::string Error::ERR_TOOMANYTARGETS    () {return "407 <target> :<error code> recipients. <abort message>";}
std::string Error::RPL_TOPIC    () {return "332  <channel> :<topic>";}
std::string Error::ERR_UNAVAILRESOURCE    () {return "437 <nick/channel> :Nick/channel is temporarily unavailable";}
std::string Error::ERR_CHANOPRIVSNEEDED    () {return "482 <channel> :You're not channel operator"}
std::string Error::ERR_USERNOTINCHANNEL    () {return "441 <nick> <channel> :They aren't on that channel"}
std::string Error::ERR_NOTONCHANNEL   () {return "442  <channel> :You're not on that channel";}
std::string Error::ERR_NOSUCHNICK   () {return "401 <nickname> :No such nick/channel";}
std::string Error::ERR_USERONCHANNEL   () {return "443  <user> <channel> :is already on channel";}
std::string Error::RPL_INVITING     () {return "341  <channel> <nick>";}
std::string Error::RPL_AWAY    () {return "301 <nick> :<away message>";}
std::string Error::ERR_NOCHANMODES    () {return "447 <channel> :Channel doesn't support modes";}
std::string Error::ERR_KEYSET   () {return "476 <channel> :Channel key already set"; }
std::string Error::ERR_NOCHANMODES  () {return "477 <channel> :Channel doesn't support modes";}
std::string Error::ERR_CHANOPRIVSNEEDED () {return "482 <channel> :You're not channel operator";}
std::string Error::ERR_UNKNOWNMODE () {return "472 <char> :is unknown mode char to me for <channel>";}
std::string Error::RPL_CHANNELMODEIS () {return "<channel> <mode> <mode params>";}
std::string Error::RPL_BANLIST() {return "367 <channel> <banmask>";}
std::string Error::RPL_ENDOFBANLIST() {return "368 <channel> :End of channel ban list"}
std::string Error::RPL_EXCEPTLIST  () {return "348 <channel> <exceptionmask>";}
std::string Error::RPL_ENDOFEXCEPTLIST  () {return "349 <channel> :End of channel exception list";} 
std::string Error::RPL_INVITELIST  () {return "346 <channel> <invitemask>";}
std::string Error::RPL_ENDOFINVITELIST () {return "347  <channel> :End of channel invite list";}
std::string Error::RPL_UNIQOPIS () {return "325 <channel> <nickname>";}