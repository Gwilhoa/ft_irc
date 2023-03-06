/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:36:06 by gchatain          #+#    #+#             */
/*   Updated: 2023/03/06 14:24:23 by gchatain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef User_HPP
# define User_HPP
#include "ft_irc.hpp"

class User
{
	private :
		int _fd;
		int _port;
		int _addr;
		std::string _nickname;
		std::string _username;
		bool haveNick;
		bool havePass;
		bool haveUser;

	public :
		bool completed;
		User(){
			haveNick = false;
			havePass = false;
			haveUser = false;
		};
		User(int fd, struct sockaddr_in addr);
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
        void setNickname(std::string &newName);
		std::string getUsername() const {return _username;}
		void setUsername(const std::string &username){
			_username = username;
			haveUser = true;
			checkAll();
		}
		void setCurrentChannel();

		bool operator==(const User& rhs) const;
		bool operator>(const User& rhs) const {
			return _fd > rhs._fd;
		}
		bool operator<(const User& rhs) const {
			return _fd < rhs._fd;
		}
		void sendNumeric(const int& msg) const;

		void checkAll(){
			completed = (haveNick && havePass && haveUser);
		}

		void validPass(){
			havePass = true;
		}

		void Show(){
			std::cout << "nick [" << _nickname << "], user [" << _username << "] complete [" << completed << "] is on " << _fd << std::endl;
		}
		//bool PassValid(std::string str, Server &server);
};
#endif
