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
    (void)myServer;
    user.setNickname(name);
    return false;
}

bool pass(User &user, std::string name, Server &myServer){
    if (! user.PassValid(name, myServer))
        myServer.quit(user);
    return false;
}

bool user(User &user, std::string name, Server &myServer){
    (void)myServer;
    user.setUsername(name);
    return false;
}

bool quit(User &user, std::string name, Server &myServer){
    myServer.quit(user);
    return false;
}

bool part(User &user, std::string name, Server &myServer){
    (void)myServer;
    Channel* myChan = myServer.getChannelByName(firstArgu(name));
    if (myChan){
        myChan->removeUser(user);
        return true;
    }
    return false;
}

bool privatemsg(User &receiver, std::string msg, Server &myServer){
    std::string firstArg = firstArgu(msg);
    Channel* myChan = myServer.getChannelByName(firstArg);
    if (myChan){
        (void)receiver;
    }
    else {
        User* use = myServer.getUserByName(firstArg);
        if (use){
            (void)use;
        }
    }
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
        receiver.sendMsg(std::string(":") + std::string(receiver.getNickname())+ std::string("!localhost JOIN :") + msg);
    }
    else{
        receiver.sendMsg(std::string(":") + std::string(receiver.getNickname())+ std::string("!localhost JOIN :") + msg);
        myChan->addUser(receiver, false);
        //receiver.myCurrentChannel = myChan;
    }
    return true;
}

void execCommand(User &receiver, std::string &mystring, Server &myServer){
    std::vector<std::string> Command = ft_split(mystring, '\n');
    for (std::vector<std::string>::iterator it = Command.begin(); it != Command.end(); it++){
        defineCommand(receiver, *it, myServer);
    }
}

void defineCommand(User &receiver, std::string &mystring, Server &myServer){
    std::cout << "Command take " << mystring << std::endl;

    std::vector < std::pair < std::string, bool(*)(User&, std::string, Server&) > > CommandList;
    std::string oldString = mystring;

    CommandList.push_back(make_pair("PING", ping));
    CommandList.push_back(make_pair("JOIN", joinChannel));
    CommandList.push_back(make_pair("KICK", kick));
    CommandList.push_back(make_pair("USER", user));
    CommandList.push_back(make_pair("NICK", nick));
    CommandList.push_back(make_pair("MODE", mode));
    CommandList.push_back(make_pair("PASS", pass));

    for (std::vector< std::pair < std::string, bool(*)(User&, std::string, Server&) > >::iterator it = (CommandList.begin()); it != CommandList.end(); it++){
        if (mystring.find((*it).first, 0) == 0){
            mystring = mystring.erase(0, (*it).first.length());
            int Alpha = gotAlpha(mystring);
            if (Alpha > 0)
            {
                if ((*it).second(receiver, &(mystring[Alpha]), myServer))
                    (void) oldString;
            }
            else
            {
                if (Alpha == -1)
                    receiver.sendMsg("Error " + (*it).first + " don't have argument\n");
                else
                    receiver.sendMsg("Error " + (*it).first + " need spaces between command and args\n");
            }
            break;
        }
    }
    //receiver.sendMsg(oldString);
}

/**
bool commandManager(User &user, const std::string& name){
    defineCommand(user, name);
} 
int main(int argc, char **argv){
    User a;
    defineCommand(a, (argv[1]));

}*/