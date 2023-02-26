/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:35:43 by gchatain          #+#    #+#             */
/*   Updated: 2023/02/22 14:35:47 by gchatain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include "../includes/ft_irc.hpp"
//#include "Server.hpp"

class Channel
{
    private:
        std::string         _name;
        std::vector<User >  _users;
        const Server        *_myCurrentServer;

    public:
        Channel();
        Channel(const std::string &name, Server *myCurrentServer);
        Channel(const Channel &c);
        ~Channel();
        Channel & operator=(const Channel &c);
        //getters and setters
        std::string getName() const;
        std::vector <User> getUsers() const;
        void addUser(User &user);
        void removeUser(User &user);
        void sendMsg(const std::string &msg);
};

#endif