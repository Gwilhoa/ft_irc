
#ifndef Server_HPP
# define Server_HPP
#include "../includes/ft_irc.hpp"

class User;
class Server
{
	private :
	int _port;
	std::string _password;
	int _server_fd;
	std::map <int, User> _connected_users;

	public :
		Server(int port, std::string password);
		Server();
		Server(const Server &c);
		~Server();
		Server & operator=(const Server &c);
		int init();
		int accept_connexion();
        int disconectUser(int fd);

		//getters and setters
		int	getPort() const;
		std::string getPassword() const;
		int getServerFd() const;
		std::map <int, User> getConnectedUsers() const;
        struct pollfd *getPollFds();
};
#endif

