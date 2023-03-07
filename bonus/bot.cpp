/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:50:53 by gchatain          #+#    #+#             */
/*   Updated: 2023/03/07 10:55:05 by gchatain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>

void send_message(int fd, const std::string& message)
{
    send(fd, message.c_str(), message.length(), 0);
}


int main(int argc, char **argv){
    if (argc != 4) {
        std::cout << "Usage: ./bot <ip> <port> <password>" << std::endl;
        return 1;
    }
    int port = atoi(argv[2]);
    char *ip = argv[1];
    std::string password = argv[3];
    struct sockaddr_in address = {};
    int opt = 1;
    int bot_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (bot_fd == 0) {
        std::cout << "Error: socket failed" << std::endl;
        return 1;
    }
    if (setsockopt(bot_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cout << "Error: setsockopt failed" << std::endl;
        return 1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);
    if (connect(bot_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cout << "Error: connect failed" << std::endl;
        return 1;
    }
    std::cout << "Bot connected to server" << std::endl;
    send_message(bot_fd, std::string("PASS " + password + "\r\n"));
    send_message(bot_fd, "USER bot 0 * :bot\r\n");
    send_message(bot_fd, "NICK bot\r\n");
    send_message(bot_fd, "JOIN #bot\r\n");
    while (1) {
        pollfd bot = {};
        bot.fd = bot_fd;
        bot.events = POLLIN;
        poll(&bot, 1, 1000);
        if (bot.revents & POLLIN) {
            char buffer[1024] = {};
            int ret = recv(bot_fd, buffer, 1024, 0);
            if (ret == 0) {
                std::cout << "Server disconnected" << std::endl;
                return 0;
            }
            std::cout << buffer << std::endl;
            if (std::string(buffer).find("PING") != std::string::npos) {
                send_message(bot_fd, "PRIVMSG #bot :PONG\r\n");
            }
        }
    }
}

