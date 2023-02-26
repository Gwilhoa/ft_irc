/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajossera <ajossera@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:15:17 by ajossera          #+#    #+#             */
/*   Updated: 2023/02/22 15:15:18 by ajossera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"
#include "../../includes/User.hpp"

int	nick(User &user, const std::string& new_nick){
    user.setNickname(new_nick);
    return 1;
}