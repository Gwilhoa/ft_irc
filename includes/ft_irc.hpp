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

//std::string to_string(char *str);
void privatemsg(User &receiver, const std::string& msg, const std::string& name);
int	nick(User &user, const std::string& new_nick);

std::vector<Channel>::iterator find(std::vector<Channel> myVec, Channel myChannel){
    std::vector<Channel>::iterator it = myVec.begin();
    for (; it != myVec.end(); it ++){
        if (*it == myChannel){
            return (it);
        }
    }
    return(it);
}

/*std::vector<Server>::iterator find(std::vector<Server> myVec, Server myServer){
    std::vector<Server>::iterator it = myVec.begin();
    for (; it != myVec.end(); it ++){
        if (*it == myServer){
            return (it);
        }
    }
    return(it);
}*/

std::vector<User>::iterator find(std::vector<User> myVec, User &myUser){
    std::vector<User>::iterator it = myVec.begin();
    for (; it != myVec.end(); it ++){
        if (*it == myUser){
            return (it);
        }
    }
    return(it);
}



#endif
