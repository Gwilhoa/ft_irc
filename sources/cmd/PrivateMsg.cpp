/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivateMsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:36:12 by gchatain          #+#    #+#             */
/*   Updated: 2023/02/22 14:36:13 by gchatain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/ft_irc.hpp"
#include "../../includes/User.hpp"

void privatemsg(User &receiver, const std::string& msg, const std::string& name){
    std::string msg_to_send = "PRIVMSG " + name + " :" + msg;
    receiver.sendMsg(msg_to_send);
}