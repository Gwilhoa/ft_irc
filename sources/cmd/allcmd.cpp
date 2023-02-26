#include "../../includes/ft_irc.hpp"
#include "../../includes/User.hpp"

typedef struct s_command {
    std::string str;
    int(*ptr)(User&, std::string);
} t_command;

t_command defineOneCommand(std::string str, int (*pf)(User&, std::string)) {
    t_command ret;
    ret.str = str;
    ret.ptr = pf;
    return ret;
}

int gotAlpha(std::string str)
{
    for (int i = 0; str[i] != 0; i++){
        if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
            return i;
    }
    return -1;
}

int	nick(User &user, const std::string& name){
    user.setNickname(name);
    return 1;
}

void privatemsg(User &receiver, const std::string& msg, const std::string& name){
    std::string msg_to_send = "PRIVMSG " + name + " :" + msg;
    receiver.sendMsg(msg_to_send);
}

int joinChannel(User &receiver, std::string msg){
    std::cout << msg << "\n";
    Channel *myChan = &(receiver._myCurrentServer->getChannelByName(msg));
    if (myChan == NULL)
        *(receiver.myCurrentChannel) = (receiver._myCurrentServer->addChannel(msg));
    else
        receiver.myCurrentChannel = myChan;
    return 1;
}

void defineCommand(User &receiver, std::string mystring){

    std::vector<t_command> CommandList;
    CommandList.push_back(defineOneCommand("JOIN", joinChannel));

    for (std::vector<s_command>::iterator it = (CommandList.begin()); it != CommandList.end(); it++){
        if (mystring.find((*it).str, 0) == 0){
            mystring = mystring.erase(0, (*it).str.length());
            int Alpha = gotAlpha(mystring);
            if (Alpha > 0)
                (*it).ptr(receiver, &(mystring[Alpha]));
            else
            {
                if (Alpha == -1)
                    std::cout << "Error " << (*it).str << " don't have argument" << std::endl;
                else
                    std::cout << "Error " << (*it).str << " need spaces between command and args" << std::endl;
            }
            break;
        }
    }
}

/*
void commandManager(User &user, const std::string& name){
    defineCommand(user, name);
} 

int main(int argc, char **argv){
    User a;
    defineCommand(a, (argv[1]));

}*/