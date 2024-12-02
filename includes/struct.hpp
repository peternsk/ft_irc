#ifndef CMD_STRUCT_HPP
#define CMD_STRUCT_HPP

#include "ft_irc.hpp"

struct Cmd {
	std::string prefix; //ajouter prefixe pour cetain mode d'envoie
	std::string cmd;  // changé la datatype a std::string pour faciliter le code et le triage
	std::string mode; // pourquoi mode si ca peut aller dans argument ? && changé la datatype a std::string pour faciliter le code et le triage
	std::vector< std::string > arg;
	std::vector < std::string > password;
	Client * client;
	Channel * chan;
};

// class Cmd {
// 	public:


// 		std::string prefix; //ajouter prefixe pour cetain mode d'envoie
// 		std::string cmd;  // changé la datatype a std::string pour faciliter le code et le triage
// 		std::string mode; // pourquoi mode si ca peut aller dans argument ? && changé la datatype a std::string pour faciliter le code et le triage
// 		std::vector< std::string > arg;
// 		std::vector < std::string > password;
// 		Client * client;
// 		Channel * chan;
// };


#endif
