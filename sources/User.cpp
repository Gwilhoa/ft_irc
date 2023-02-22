

#include "../includes/User.hpp"

User::User()
{

}

User::User(int fd, struct sockaddr_in addr)
{
	_fd = fd;
	_port = addr.sin_port;
	_addr = addr.sin_addr.s_addr;
	_nickname = "default";
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

struct pollfd User::getpollfd()
{
    struct pollfd user = {};

    user.fd = this->_fd;
    user.events = POLLIN;
    return (user);
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