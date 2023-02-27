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
    _users = std::vector<User>();
}

Channel::Channel(const std::string &name, Server *myCurrentServer) : _name(name), _myCurrentServer(myCurrentServer)
{
    _users = std::vector<User>();
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

std::vector <User> Channel::getUsers() const
{
    return (_users);
}

void Channel::addUser(User &user)
{
    if (find(_users, user) == _users.end())
    {
        _users.push_back(user);
        user.myCurrentChannel = this;
    }
    else
        std::cout << "User yet inside the channel" << std::endl;
}

void Channel::removeUser(User &user)
{
    if (find(_users, user) != _users.end())
        _users.erase(find(_users, user));
    else
        std::cout << "User not found" << std::endl;
}

void Channel::sendMsg(const std::string &msg)
{
    std::vector<User>::iterator it = _users.begin();
    while (it != _users.end())
    {
        it->sendMsg(msg);
        it++;
    }
}