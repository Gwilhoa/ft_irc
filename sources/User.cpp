/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:36:25 by gchatain          #+#    #+#             */
/*   Updated: 2023/02/22 14:36:26 by gchatain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/User.hpp"

User::User()
{

}

User::User(int fd, struct sockaddr_in addr, Server *myCurrentServer) : 
myCurrentChannel(NULL), _fd(fd), _port(addr.sin_port), _addr(addr.sin_addr.s_addr), _nickname("default"), _myCurrentServer(myCurrentServer)
{
}

User::User(const User &c)
{
	*this = c;
}

User::~User()
{}

User & User::operator=(const User &c)
{
	_addr = c._addr;
	_port = c._port;
	_fd = c._fd;
	_nickname = c._nickname;
	return (*this);
}

struct pollfd User::getpollfd() const
{
    struct pollfd user = {};

    user.fd = this->_fd;
    user.events = POLLIN;
    return (user);
}

void User::sendMsg(const std::string& msg) const
{
    send(this->_fd, msg.c_str(), msg.size(), 0);
}

void User::sendNumeric(const int& msg) const
{
    send(this->_fd, &msg, 1, 0);
}


//getters and setters
int User::getFd() const
{
    return _fd;
}

int User::getPort() const
{
    return _port;
}

int User::getAddr() const
{
    return _addr;
}

std::string User::getNickname() const
{
    return _nickname;
}

void User::setNickname(const std::string &newName)
{
    this->_nickname = newName;
}

bool User::operator==(const User &rhs) const {
    return _fd == rhs._fd;
}
