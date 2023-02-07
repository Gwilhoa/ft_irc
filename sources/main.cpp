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



#include "../includes/ft_irc.hpp"

void accept_connexion(int server_fd){
	int new_socket;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
	if (new_socket < 0) {
		std::cout << "Error: accept failed" << std::endl;
	}
	std::cout << "New connection" << std::endl;

}

void initialize_server(int port, std::string password) {
	int server_fd;
	struct sockaddr_in address;
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1) {
		std::cout << "Error: socket creation failed" << std::endl;
		exit(1);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		std::cout << "Error: bind failed" << std::endl;
		exit(1);
	}
	listen(server_fd, 3);
	std::cout << "Server started on port " << port << std::endl;
	std::cout << "Password: " << password << std::endl;
	accept_connexion(server_fd);

}
int main(int argc, char *argv[])
{
	if (argc == 3) {
		std::string password = to_string(argv[2]);
        initialize_server(atoi(argv[1]), password);
	} else {
		std::cout << "usage ./ft_irc [port]" << std::endl;
	}
}


