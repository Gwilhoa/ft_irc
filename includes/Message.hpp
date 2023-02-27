#ifndef Message_HPP
# define Message_HPP

# include "../includes/ft_irc.hpp"
class Message
{
    private:
        std::string _str;
        User        *_creator;
        Channel     *_myCurrentChannel;

    public:
        Message(std::string str, User        *creator, Channel     *myCurrentChannel) :
        _str(str), _creator(creator), _myCurrentChannel(myCurrentChannel)
        {
            //std::cout << creator->getNickname() << " say " << str << " on " << myCurrentChannel->getName() << std::endl;
        }  
};

#endif