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

class User;
class Channel;

std::string to_string(char *str);
void defineCommand(User &receiver, std::string mystring);




#endif
