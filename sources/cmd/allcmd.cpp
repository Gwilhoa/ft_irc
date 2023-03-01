#include "../../includes/ft_irc.hpp"

typedef struct s_command {
    std::string str;
    void(*ptr)(User&, std::string, Server&);
} t_command;

t_command defineOneCommand(std::string str, void (*pf)(User&, std::string, Server&)) {
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

void nick(User &user, std::string name, Server &myServer){
    user.setNickname(name);
}

void pass(User &user, std::string name, Server &myServer){
    //user.setNickname(name);
}

void user(User &user, std::string name, Server &myServer){
    user.setUsername(name);
}

void quit(User &user, std::string name, Server &myServer){
    user.setNickname(name);
}

void part(User &user, std::string name, Server &myServer){
    user.setNickname(name);
}

void privatemsg(User &receiver, std::string msg, Server &myServer){
    //std::string msg_to_send = "PRIVMSG " + name + " :" + msg;
    receiver.sendMsg(msg);
}

void notice (User &receiver, std::string msg, Server &myServer){

}

void mode (User &receiver, std::string msg, Server &myServer){
    
}

void ping(User &receiver, std::string msg, Server &myServer){
    receiver.sendMsg("PONG " + msg);
}

void kick(User &receiver, std::string msg, Server &myServer){
    if (receiver.myCurrentChannel && receiver.canKick)
        receiver.myCurrentChannel->removeUser(msg);
}

void joinChannel(User &receiver, std::string msg, Server &myServer){
    std::cout << msg << "\n";
    dprintf(1, "a");
    //std::cout << receiver._myCurrentServer;
    Channel *myChan = (myServer.getChannelByName(msg));
    dprintf(1, "b");
    if (myChan == NULL){
        Channel temp = myServer.addChannel(msg);
        receiver.myCurrentChannel = &temp;
        receiver.sendNumeric(RPL_TOPIC);
        receiver.sendMsg((RPL_TOPIC) + " JOIN :" + msg);
    }
    else{
        receiver.myCurrentChannel = myChan;
    }
}

void defineCommand(User &receiver, std::string mystring, Server &myServer){

    std::cout << "Command take " << mystring << std::endl;

    std::vector<t_command> CommandList;
    CommandList.push_back(defineOneCommand("PING", ping));
    CommandList.push_back(defineOneCommand("JOIN", joinChannel));
    CommandList.push_back(defineOneCommand("KICK", kick));
    CommandList.push_back(defineOneCommand("USER", user));


    for (std::vector<s_command>::iterator it = (CommandList.begin()); it != CommandList.end(); it++){
        if (mystring.find((*it).str, 0) == 0){
            mystring = mystring.erase(0, (*it).str.length());
            int Alpha = gotAlpha(mystring);
            if (Alpha > 0)
                (*it).ptr(receiver, &(mystring[Alpha]), myServer);
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
}

/**
void commandManager(User &user, const std::string& name){
    defineCommand(user, name);
} 

int main(int argc, char **argv){
    User a;
    defineCommand(a, (argv[1]));

}*/