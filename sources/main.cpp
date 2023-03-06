/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:27:39 by gchatain          #+#    #+#             */
/*   Updated: 2023/03/06 16:31:59 by gchatain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "ft_irc.hpp"


int main(int argc, char *argv[])
{
    std::string str = "";
	if (argc == 3) {
		Server server = Server(atoi(argv[1]), (argv[2]));
		if (server.init() == 1)
			exit(1);
        while (true)
        {
            std::vector<struct pollfd>fds = server.getPollFds();
            std::cout << "waiting..." << std::endl;
            int ret = poll((&(*fds.begin())), server.getConnectedUsers().size() + 1, -1);
            std::cout << "processing..." << std::endl;
            if (ret < 0) {
                std::cout << "poll error" << std::endl;
                exit(1);
            }
            size_t i = 0;
            while (i < server.getConnectedUsers().size() + 1)
            {
                if (fds[i].revents & POLLIN)
                {
                    if (i == 0)
                    {
                        server.accept_connexion();
                    }
                    else {
                        char buffer[1024];
                        int n = recv(server.getPollFds()[i].fd, buffer, 1024, 0);
                        if (n == 0) {
                            server.disconnectUser(server.getPollFds()[i].fd);
                        }
                        buffer[n] = '\0';
                        std::string message(buffer);
                        str += message;
                        User *user = server.getUSerByFd(server.getPollFds()[i].fd);
                        if (str.find("\r\n") != std::string::npos){
                            if (user == NULL)
                               std::cout << "user not found" << std::endl;
                            else {
                                parseCommand(*user, str, server);
                                str = "";
                            }
                        }
                    }
                }
                i++;
            }
        }
	} else {
		std::cout << "usage ./ft_irc [port] [password]" << std::endl;
	}
}
