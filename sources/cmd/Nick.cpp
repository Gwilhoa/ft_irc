/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:15:17 by gchatain          #+#    #+#             */
/*   Updated: 2023/02/22 15:15:18 by gchatain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"
#include "../../includes/User.hpp"

int	nick(User &user, const std::string& new_nick){
    user.setNickname(new_nick);
    return 1;
}