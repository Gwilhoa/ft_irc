

#ifndef User_HPP
# define User_HPP
#include "../includes/ft_irc.hpp"
class User
{
private :
	int _fd;
	int _port;
	int _addr;
	std::string _nickname;
	public :
		User();
		User(int fd, struct sockaddr_in addr);
		User(const User &c);
		~User();
		User & operator=(const User &c);
        struct pollfd getpollfd();
        //getters and setters
        int getFd() const;
        int getPort() const;
        int getAddr() const;
        std::string getNickname() const;
};
#endif
