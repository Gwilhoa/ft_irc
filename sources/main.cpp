/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:27:39 by gchatain          #+#    #+#             */
/*   Updated: 2023/02/07 14:27:57 by gchatain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <unistd.h>
#include "../includes/ft_irc.hpp"
#include "../includes/Server.hpp"
#include "../includes/User.hpp"


int main(int argc, char *argv[])
{
	if (argc == 3) {
		Server server = Server(atoi(argv[1]), (argv[2]));
		if (server.init() == 1)
			exit(1);
        while (true)
        {
            std::vector<struct pollfd>fds = server.getPollFds();
            std::cout << "en attente..." << std::endl;
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
                        std::cout << std::endl;
                        User *user = server.getUSerByFd(server.getPollFds()[i].fd);
                        if (user == NULL)
                            std::cout << "user not found" << std::endl;
                        else
                            parseCommand(*user, message, server);
                    }
                }
                i++;
            }
        }
	} else {
		std::cout << "usage ./ft_irc [port] [password]" << std::endl;
	}
}
