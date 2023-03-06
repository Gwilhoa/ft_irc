/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:15:23 by gchatain          #+#    #+#             */
/*   Updated: 2023/03/06 14:25:22 by gchatain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

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

std::string intToString(size_t nb) {
    std::string ret("");
    while (nb != 0) {
        std::string newstr;
        newstr.push_back((nb % 10) + '0');
        ret.insert(0, newstr);
        nb /= 10;
    }
    return ret;
}