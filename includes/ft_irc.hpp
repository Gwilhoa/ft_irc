/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:35:54 by gchatain          #+#    #+#             */
/*   Updated: 2023/02/22 14:35:55 by gchatain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_H
# define FT_IRC_H
# include <iostream>
# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <cstdlib>
# include <arpa/inet.h>
# include <map>
# include <poll.h>
# include <vector>
# include <stdio.h>

class Server;
class Channel;
class User;
class Message;

# include "User.hpp"
# include "Channel.hpp"
# include "Server.hpp"
# include "Message.hpp"
# include "numeric.hpp"

/*
enum grade {
    operator = , random
};*/

//std::string to_string(char *str);
void execCommand(User &receiver, std::string &mystring, Server &myServer);
void parseCommand(User &receiver, std::string &receivedMessage, Server &myServer);
std::vector<std::string> ft_split(const std::string &str, char delim);

std::string firstArgu(std::string &src);/*{
    //std::string retStr = retStr.substr(0, src.find(' ', 0));
    //src = src.substr(src.find(' ', 0) + 1);
    return "e";//retStr;
}*/



#endif
