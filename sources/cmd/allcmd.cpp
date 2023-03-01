#include "../../includes/ft_irc.hpp"

typedef struct s_command {
    std::string str;
    bool(*ptr)(User&, std::string, Server&);
} t_command;

std::string firstArgu(std::string &src){
    std::string retStr = retStr.substr(0, src.find(' ', 0));
    src = src.substr(src.find(' ', 0) + 1);
    return retStr;
}

t_command defineOneCommand(std::string str, bool (*pf)(User&, std::string, Server&)) {
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

bool nick(User &user, std::string name, Server &myServer){
    user.setNickname(name);
    return false;
}

bool pass(User &user, std::string name, Server &myServer){
    //user.setNickname(name);
    return false;
}

bool user(User &user, std::string name, Server &myServer){
    user.setUsername(name);
    return false;
}

bool quit(User &user, std::string name, Server &myServer){
    user.setNickname(name);
    return false;
}

bool part(User &user, std::string name, Server &myServer){
    Channel* myChan = myServer.getChannelByName(firstArgu(name));
    if (myChan){
        myChan->removeUser(user);
        return true;
    }
    return false;
}

bool privatemsg(User &receiver, std::string msg, Server &myServer){
    //std::string msg_to_send = "PRIVMSG " + name + " :" + msg;
    receiver.sendMsg(msg);
    return false;
}

bool notice (User &receiver, std::string msg, Server &myServer){
    return false;
}

bool mode (User &receiver, std::string msg, Server &myServer){
    Channel* myChan = myServer.getChannelByName(firstArgu(msg));
    if (myChan && myChan->is_op(receiver)){
        User* use = myChan->getUserByName(firstArgu(msg));
        if (use){
            myChan->op(*use);
            return true;
        }
    }
    return false;
}

bool ping(User &receiver, std::string msg, Server &myServer){
    receiver.sendMsg("PONG " + msg);
    return true;
}

bool kick(User &receiver, std::string msg, Server &myServer){
    Channel* myChan = myServer.getChannelByName(firstArgu(msg));
    if (myChan){
        User* use = myChan->getUserByName(firstArgu(msg));
        if (use){
            myChan->removeUser(*use);
            return true;
        }
    }
    return false;
}

bool joinChannel(User &receiver, std::string msg, Server &myServer){
    std::cout << msg << "\n";
    //std::cout << receiver._myCurrentServer;
    Channel *myChan = (myServer.getChannelByName(msg));
    if (myChan == NULL){
        Channel temp = myServer.addChannel(msg);
        temp.addUser(receiver, true);
        //receiver.myCurrentChannel = &temp;
        //receiver.sendNumeric(RPL_TOPIC);
        receiver.sendMsg(std::string(":") + std::string("aurele")+ std::string("!localhost JOIN :") + msg);
    }
    else{
        receiver.sendMsg(std::string(":") + std::string("aurele")+ std::string("!localhost JOIN :") + msg);
        myChan->addUser(receiver, false);
        //receiver.myCurrentChannel = myChan;
    }
    return true;
}

void defineCommand(User &receiver, std::string mystring, Server &myServer){
    std::string other = mystring.substr(mystring.find('\n', 0)+ 1 , mystring.length());
    mystring = mystring.substr(0, mystring.find('\n', 0));
    std::cout << "Command take " << mystring << std::endl;

    std::vector<t_command> CommandList;
    std::string oldString = mystring;
    CommandList.push_back(defineOneCommand("PING", ping));
    CommandList.push_back(defineOneCommand("JOIN", joinChannel));
    CommandList.push_back(defineOneCommand("KICK", kick));
    CommandList.push_back(defineOneCommand("USER", user));
    CommandList.push_back(defineOneCommand("NICK", nick));
    CommandList.push_back(defineOneCommand("MODE", mode));

    for (std::vector<s_command>::iterator it = (CommandList.begin()); it != CommandList.end(); it++){
        if (mystring.find((*it).str, 0) == 0){
            mystring = mystring.erase(0, (*it).str.length());
            int Alpha = gotAlpha(mystring);
            if (Alpha > 0)
            {
                if ((*it).ptr(receiver, &(mystring[Alpha]), myServer))
                    (void) oldString;//receiver.sendMsg(oldString + ":");
            }
            else
            {
                if (Alpha == -1)
                    receiver.sendMsg("Error " + (*it).str + " don't have argument\n");
                else
                    receiver.sendMsg("Error " + (*it).str + " need spaces between command and args\n");
            }
            break;
        }
    }
    if (other.length() > 0)
        defineCommand(receiver, other, myServer);
}

/**
bool commandManager(User &user, const std::string& name){
    defineCommand(user, name);
} 
int main(int argc, char **argv){
    User a;
    defineCommand(a, (argv[1]));

}*/