/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:15:23 by gchatain          #+#    #+#             */
/*   Updated: 2023/02/22 15:15:24 by gchatain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include "../includes/ft_irc.hpp"

std::vector<std::string> ft_split(const std::string &str, char delim)
{
    std::vector<std::string> res;
    std::string tmp = str;
    while (tmp.size())
    {
        int pos = tmp.find(delim);
        if (pos == -1)
        {
            res.push_back(tmp);
            return (res);
        }
        res.push_back(tmp.substr(0, pos));
        tmp = tmp.substr(pos + 1);
    }
    return (res);
}