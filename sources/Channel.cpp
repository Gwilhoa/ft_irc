/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:15:39 by gchatain          #+#    #+#             */
/*   Updated: 2023/02/22 15:15:40 by gchatain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"
#include "../includes/Channel.hpp"
#include "../includes/User.hpp"

class User;

Channel::Channel()
{
    _name = "";
    _users = std::map<User, bool>();
}

Channel::Channel(const std::string &name, Server *myCurrentServer) : _name(name), _myCurrentServer(myCurrentServer)
{
    _users = std::map<User, bool>();
}

Channel::Channel(const Channel &c)
{
    *this = c;
}

Channel::~Channel()
{}

Channel & Channel::operator=(const Channel &c)
{
    _name = c._name;
    _users = c._users;
    return (*this);
}

std::string Channel::getName() const
{
    return (_name);
}

std::map <User, bool> Channel::getUsers() const
{
    return (_users);
}

void Channel::addUser(User &user, bool ope) {
    _users.insert(std::make_pair<User, bool>(user, ope));
    //_users[user.getFd()] = user;
}

/*void Channel::removeUser(User &user)
{
    if (_users.erase(user) == 0)
        std::cout << "User not found" << std::endl;
}*/

void Channel::sendMsg(const std::string &msg)
{
    for (std::map<User, bool>::iterator it = _users.begin(); it != _users.end(); it++){
        it->first.sendMsg(msg);
    }
}

User *Channel::getUserByName(const std::string &userName) const {
    for (std::map<User, bool>::const_iterator it = _users.begin(); it != _users.end(); it++)
    {
        if (it->first.getUsername() == userName)
            return (const_cast<User *>(&it->first));
    }
    return (NULL);
}
