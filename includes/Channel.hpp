/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:35:43 by gchatain          #+#    #+#             */
/*   Updated: 2023/03/06 14:24:11 by gchatain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include "ft_irc.hpp"


class User;
class Channel
{
    private:
        std::string             _name;
        std::map<User, bool>     _users;

    public:
        //Channel();
        Channel(const std::string &name);
        Channel(const Channel &c);
        ~Channel();
        Channel & operator=(const Channel &c);
        //getters and setters
        std::string getName() const;
        std::map <User, bool> getUsers() const;
        void addUser(User &user);
        std::string * removeUser(User &user);
        User *getUserByName(const std::string &userName) const;
        bool is_op(User& myUser);
        bool op(User& myUser);
        void sendToAll(std::string msg);
        inline bool operator==(const Channel& rhs) { return _name == rhs._name; }
        void Show();
};

#endif