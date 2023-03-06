/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:15:39 by gchatain          #+#    #+#             */
/*   Updated: 2023/03/06 14:24:44 by gchatain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


class User;

Channel::Channel(const std::string &name) : _name(name)
{
    _users = std::map<User, bool>();
    TOPIC = "default";
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
    TOPIC = c.TOPIC;
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

void Channel::addUser(User &user) {
    if (_users.size() == 0){
        _users.insert(std::make_pair<User, bool>(user, true));
    }
    else
        _users.insert(std::make_pair<User, bool>(user, false));
    Show();
}

std::string *Channel::removeUser(User &user)
{
    _users.erase(user);
    if (_users.size() == 1)
        _users.begin()->second = true;
    if (_users.size() == 0)
        return (&(_name));
    return NULL;
}

User *Channel::getUserByName(const std::string &userName) const {
    for (std::map<User, bool>::const_iterator it = _users.begin(); it != _users.end(); it++)
    {
        if (it->first.getNickname() == userName)
            return (const_cast<User *>(&it->first));
    }
    return (NULL);
}

bool Channel::is_op(User& myUser){
    std::cout << "aanddd " << _users[myUser] << "\n";
    if (myUser.completed)
        return _users[myUser];
    return false;
}

bool Channel::op(User& myUser){
    if (myUser.completed){
        _users[myUser] = true;
        return true;
    }
    return false;
}

void Channel::sendToAll(std::string msg){
    for (std::map<User, bool>::iterator it = _users.begin(); it != _users.end(); it ++)
    {
        it->first.sendMsg(msg);
    }
}

void Channel::sendToAllUnless(std::string msg, User& user){
    for (std::map<User, bool>::iterator it = _users.begin(); it != _users.end(); it ++)
    {
        if (!(it->first == user))
            it->first.sendMsg(msg);
    }
}

void Channel::Show(){
    std::cout << _name << " size [" << _users.size() << "] : ";
    for (std::map<User, bool>::iterator it = _users.begin(); it != _users.end(); it ++){
        if (it != _users.begin())
            std::cout << ", ";
        std::cout << it->first.getNickname() << " - " << it->second;
    }
    std::cout << std::endl;
}

bool Channel::haveUser(User &use) {
    for (std::map<User, bool>::iterator It = _users.begin(); It != _users.end(); It ++) {
        if (It->first == use)
            return true;
    }
    return false;
}