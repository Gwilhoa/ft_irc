/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:36:17 by gchatain          #+#    #+#             */
/*   Updated: 2023/03/06 16:32:32 by gchatain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "ft_irc.hpp"


class Channel;
Server::Server() : _port(), _server_fd()
{
	Server(3000, "test");
}

Server::Server(int port, const std::string& password) : _port(port), _password(password), _server_fd()
{
	_connected_users = std::vector <User>();
}

Server::Server(const Server &c) : _port(), _server_fd()
{
	*this = c;
}

Server::~Server()
{
	std::cout << "[Server] destructor called" << std::endl;
}

Server & Server::operator=(const Server &c)
{
	_port = c._port;
	_password = c._password;
	_server_fd = c._server_fd;
	return (*this);
}

int Server::init()
{
	if (_port > 65535)
	{
		std::cout << "Error: port must be between 0 and 65535" << std::endl;
		return 1;
	}
	struct sockaddr_in address = {};
	int opt = 1;

	if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		std::cout << "Error: socket failed" << std::endl;
		return 1;
	}
	if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		std::cout << "Error: setsockopt failed" << std::endl;
		return 1;
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(_port);
	if (bind(_server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		std::cout << "Error: bind failed" << std::endl;
		return 1;
	}
	if (listen(_server_fd, 3) < 0) {
        std::cout << "Error: listen failed" << std::endl;
        return 1;
    }
    std::cout << "Server started on port " << _port << std::endl;
	return 0;
}

int Server::accept_connexion(){
	int fd_user;
	struct sockaddr_in address = {};
	int addrlen = sizeof(address);
	fd_user = accept(this->_server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
	if (fd_user < 0) {
		std::cout << "Error: accept failed" << std::endl;
		return 1;
	}
	_connected_users.push_back(User(fd_user, address));
	std::cout << "New connection " <<  inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << " : " << address.sin_family << " (" << fd_user << ")" << std::endl;
	return 0;
}

int Server::disconnectUser(int fd)
{
    std::cout << "Disconnecting user " << fd << std::endl;
	for (size_t i = 0; i < _connected_users.size(); i++)
    {
        if (_connected_users[i].getFd() == fd)
        {
            for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); it++)
            {
                it->removeUser(_connected_users[i]);
            }
            _connected_users.erase(_connected_users.begin() + i);
            return 0;
        }
    }
    return 0;
}

Channel* Server::getChannel(std::string name)
{
	for (std::vector<Channel>::iterator i = _channels.begin(); i != _channels.end(); i++){
		if (i->getName() == name)
			return (&(*i));
	}
	return NULL;
}

std::vector<struct pollfd> Server::getPollFds()
{
	std::vector<struct pollfd> fds((_connected_users.size() + 2));
    int i = 0;
    fds[i].fd = _server_fd;
    fds[i].events = POLLIN;
    i++;
    for (std::vector<User>::iterator it = _connected_users.begin(); it != _connected_users.end(); it++)
    {  
		fds[i] = it->getpollfd();
        i++;
    }
    return fds;
}

std::vector <Channel> Server::getChannels() const
{
    return this->_channels;
}

Channel *Server::getChannelByName(const std::string &name) {
    for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); it++){
        if (it->getName() == name)
            return &(*it);
    }
	return NULL;
}

Channel *Server::addChannel(const std::string name) {
	Channel	newchan(name);
    _channels.push_back(newchan);
	return &(_channels.back());
}

void Server::removeChannel(const std::string &name)
{
    for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); it++)
    {
        if (it->getName() == name)
        {
            _channels.erase(it);
            return;
        }
    }
}

//getters and setters

int	Server::getPort() const
{
	return this->_port;
}

std::string Server::getPassword() const
{
	return this->_password;
}

int Server::getServerFd() const
{
	return this->_server_fd;
}

std::vector<User> Server::getConnectedUsers() const
{
	return this->_connected_users;
}

User* Server::getUserByName(std::string str){
	for (std::vector<User>::iterator it = _connected_users.begin(); it != _connected_users.end(); it ++){
		if (str == it->getNickname())
			return &(*it);
	}
	return NULL;
}

User *Server::getUSerByFd(int fd) {
    for (std::vector<User>::iterator it = _connected_users.begin(); it != _connected_users.end(); it ++){
        if (fd == it->getFd()) {
            return &*it;
		}
    }
    return NULL;
}


void Server::quit(User &user)
{
	for (std::vector<Channel>::iterator It = _channels.begin(); It != _channels.end(); It ++){
		(It->removeUser(user));
	}
	removeUser(user.getFd());
}

void Server::removeUser(int fd){
    for (std::vector<User>::iterator it = _connected_users.begin(); it != _connected_users.end(); it ++){
        if (fd == it->getFd()){
            _connected_users.erase(it);
            close(fd);
            return;
        }
    }
}

void Server::Show(){

	std::cout << "SHOW : " << std::endl;
	ShowChan();
	std::cout << std::endl;
	ShowUser();
}


void Server::ShowChan(){
	for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); it++)
    {
        it->Show();
	}
}


void Server::ShowUser(){
	for (std::vector<User>::iterator it = _connected_users.begin(); it != _connected_users.end(); it++)
    {
        it->Show();
	}
}

bool Server::IsInTheSameChannel(User* user1, User* user2){
	for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); it ++)
	{
		if (it->haveUser(*user1) && it->haveUser(*user2)){
			return true;
		}
	}
	return false;
}

void Server::SendToAllWith(std::string str, User& myUse){
	std::vector<User> myVec;
	bool Continue = true;
	for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); it ++)
	{
		if (it->haveUser(myUse)){
			std::map<User, bool> ListOfUser = it->getUsers();
			for (std::map<User, bool>::iterator UserInChannel = ListOfUser.begin(); UserInChannel != ListOfUser.end(); UserInChannel++) {
				for (std::vector<User>::iterator UserIterator = myVec.begin(); UserIterator != myVec.end() && Continue; UserIterator++) {
					if (UserInChannel->first == *UserIterator)
						Continue = false;
				}
				if (Continue == true) {
					myVec.push_back(UserInChannel->first);
					UserInChannel->first.sendMsg(str);
				}
				Continue = true;
			}
		}
	}
}


bool Server::haveNickname(std::string nickname) {
    for (std::vector<User>::iterator it = _connected_users.begin(); it != _connected_users.end(); it++)
    {
        if (it->getNickname() == nickname)
            return true;
    }
    return false;
}