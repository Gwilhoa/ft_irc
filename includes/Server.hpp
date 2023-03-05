/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:35:57 by gchatain          #+#    #+#             */
/*   Updated: 2023/02/22 14:36:03 by gchatain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Server_HPP
# define Server_HPP
#include "../includes/ft_irc.hpp"
//#include "../includes/Channel.hpp"
class Channel;
class User;

class Server
{
	private :
		int _port;
		std::string _password;
		int _server_fd;
		std::vector <User> _connected_users;
		std::vector <Channel> _channels;

	public :
		Server(int port, const std::string& password);
		Server();
		Server(const Server &c);
		~Server();
		Server & operator=(const Server &c);
		int init();
		int accept_connexion();
        int disconnectUser(int fd);
        User *getUSerByFd(int fd);

		//getters and setters
		int	getPort() const;
		std::string getPassword() const;
		int getServerFd() const;
		std::vector<User> getConnectedUsers() const;
        struct pollfd *getPollFds();
        std::vector <Channel> getChannels() const;
		Channel *getChannel(std::string name);
        Channel *addChannel(const std::string name);
        void removeChannel(const std::string &name);
        Channel *getChannelByName(const std::string &name);


		inline bool operator==(const Server& rhs) { return _server_fd == rhs._server_fd; }

		void removeUser(int fd);
	
		void quit(User &user);
		User* getUserByName(std::string str);

		void Show();
		void ShowChan();
		void ShowUser();
};
#endif

