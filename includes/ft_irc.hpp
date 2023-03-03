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


class Server;
class Channel;
class User;
class Message;

# include "User.hpp"
# include "Channel.hpp"
# include "Server.hpp"
# include "Message.hpp"



void execCommand(User &receiver, std::string &mystring, Server &myServer);
void parseCommand(User &receiver, std::string &receivedMessage, Server &myServer);
std::vector<std::string> ft_split(const std::string &str, char delim);

//commands
bool nick(User &receiver, std::string &name, Server &myServer);
bool joinChannel(User &receiver, std::string &mystring, Server &myServer);
bool part(User &receiver, std::string &mystring, Server &myServer);
bool mode(User &receiver, std::string &mystring, Server &myServer);
bool privmsg(User &receiver, std::string &mystring, Server &myServer);
bool quit(User &receiver, std::string &mystring, Server &myServer);
bool pass(User &receiver, std::string &pass, Server &myServer);
bool user(User &receiver, std::string &name, Server &myServer);

#endif
