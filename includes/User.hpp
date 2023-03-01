/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:36:06 by gchatain          #+#    #+#             */
/*   Updated: 2023/02/22 14:36:07 by gchatain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef User_HPP
# define User_HPP
# include "../includes/ft_irc.hpp"
# include "../includes/Channel.hpp"
# include "../includes/Server.hpp"

class User
{
	private :
		int _fd;
		int _port;
		int _addr;
		std::string _nickname;
		std::string _username;

	public :
		//Server *_myCurrentServer;
		bool canKick;
		bool root;
		User();
		User(int fd, struct sockaddr_in addr/*, Server *myCurrentServer*/);
		User(const User &c);
		~User();
		User & operator=(const User &c);
        struct pollfd getpollfd() const;
        void sendMsg(const std::string& msg) const;
        //getters and setters
        int getFd() const;
        int getPort() const;
        int getAddr() const;
        std::string getNickname() const;
        void setNickname(const std::string &newName);
		std::string getUsername() const {return _username;}
		void setUsername(const std::string &username){
			_username = username;
		}
		void setCurrentChannel();
		Channel *myCurrentChannel;
		bool operator==(const User& rhs) const;
		bool operator>(const User& rhs) const {
			return _fd > rhs._fd;
		}
		bool operator<(const User& rhs) const {
			return _fd < rhs._fd;
		}
		void sendNumeric(const int& msg) const;
};
#endif
