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

class User;
class Channel
{
    private:
        std::string             _name;
        std::map<User, bool>     _users;
        const Server            *_myCurrentServer;
        std::vector<Message>    _messages;

    public:
        Channel();
        Channel(const std::string &name, Server *myCurrentServer);
        Channel(const Channel &c);
        ~Channel();
        Channel & operator=(const Channel &c);
        //getters and setters
        std::string getName() const;
        std::map <User, bool> getUsers() const;
        void addUser(User &user, bool ope);
        void removeUser(User &user);
        void sendMsg(const std::string &msg);
        
        User *getUserByName(const std::string &userName) const;

        bool removeUser(const std::string userName){
            if (getUserByName(userName)){
                removeUser(*(getUserByName(userName)));
                return true;
            }
            else {
                std::cout << "User not found" << std::endl;
                return false;
            }
        }

        bool is_op(User& myUser){
            return _users[myUser];
            //return true;
        }

        void op(User& myUser){
            _users[myUser] = true;
            //std::map<User, bool>::iterator myIt =  _users.find(myUser);
            //myIt->second = true;
        }

        inline bool operator==(const Channel& rhs) { return _name == rhs._name; }
};

#endif