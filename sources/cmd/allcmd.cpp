#include "../../includes/ft_irc.hpp"

typedef struct s_command {
    std::string str;
    bool(*ptr)(User&, std::string, Server&);
} t_command;


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

std::string nicknameUsername(User &user)
{
	std::string res(":" + user.getNickname() + "!" + user.getUsername());
	return res;
}


bool nick(User &user, std::string &name, Server &myServer){
    (void)myServer;
    user.setNickname(name);
    return true;
}

bool pass(User &user, std::string &pass, Server &myServer){
    if (pass != myServer.getPassword()) {
        user.sendMsg("ERROR :Password is not correct");
        myServer.quit(user);
        return false;
    }
    user.validPass();
    return true;
}

bool user(User &user, std::string &name, Server &myServer){
    (void)myServer;
    user.setUsername((ft_split(name, ' ')[3]).substr(1));
    return true;
}

bool quit(User &user, std::string &name, Server &myServer){
    (void) (name);
    myServer.quit(user);
    return true;
}

bool part(User &user, std::string &args, Server &myServer){
    (void)myServer;
    std::string name = ft_split(args, ' ')[0];
    Channel* myChan = myServer.getChannelByName(name);
    if (myChan){
        myChan->removeUser(user);
        return true;
    }
    return false;
}

bool privatemsg(User &receiver, std::string &msg, Server &myServer){
    if (!receiver.completed)
        return false;
    std::string sender = ft_split(msg, ' ')[0];
    Channel* myChan = myServer.getChannelByName(sender);
    if (myChan){
        myChan->sendToAll(nicknameUsername(receiver) + std::string(" PRIVMSG ") + msg + std::string("\n"));
        return true;
    }
    else {
        User* use = myServer.getUserByName(sender);
        if (use){
            std::cout << "TYUII\n";
            use->sendMsg(nicknameUsername(receiver) + std::string(" PRIVMSG ") + msg + std::string("\n"));
            return true;
        }
    }
    return false;
}

bool notice (User &receiver, std::string &msg, Server &myServer){
    if (!receiver.completed)
        return false;
    (void)receiver;
    (void)msg;
    (void)myServer;
    return false;
}

bool who (User &receiver, std::string &msg, Server &myServer){
    (void)receiver;
    (void)msg;
    (void)myServer;
    return false;
}

bool mode (User &receiver, std::string &msg, Server &myServer){
    if (!receiver.completed)
        return false;
    std::vector<std::string> args = ft_split(msg, ' ');
    Channel* myChan = myServer.getChannelByName(args[0]);
    if (myChan && myChan->is_op(receiver)){
        User* use = myChan->getUserByName(args[1]);
        if (use){
            myChan->op(*use);
            return true;
        }
    }
    return false;
}

bool ping(User &receiver, std::string &msg, Server &myServer){
    (void)myServer;
    receiver.sendMsg("PONG " + msg);
    return true;
}

bool kick(User &receiver, std::string &msg, Server &myServer){
    if (!receiver.completed)
        return false;
    (void)receiver;
    std::vector<std::string> args = ft_split(msg, ' ');
    Channel* myChan = myServer.getChannelByName(args[0]);
    if (myChan){
        User* use = myChan->getUserByName(args[1]);
        
        if (myChan->is_op(receiver) && use){
            myChan->sendToAll(nicknameUsername(receiver) + std::string(" KICK ") + msg + std::string("\n"));
            myChan->removeUser(*use);
            return true;
        }
    }
    return false;
}

bool joinChannel(User &receiver, std::string &msg, Server &myServer){
    if (!receiver.completed)
        return false;
    Channel *myChan = (myServer.getChannelByName(msg));
    if (myChan == NULL){
        Channel temp = myServer.addChannel(msg);
        temp.addUser(receiver, true);
        temp.is_op(receiver);
        //receiver.sendMsg(std::string("332") + ":" + std::string(receiver.getNickname()) + "!localhost JOIN : " + msg);
        //receiver.sendNumeric(332);
        //receiver.sendMsg(std::string(":ircserv 332 aurele #a :"));
        temp.sendToAll(nicknameUsername(receiver) + std::string(" JOIN :") + msg + std::string("\n"));
        //receiver.sendMsg(nicknameUsername(receiver) + std::string(" JOIN :") + msg + std::string("\n"));
        //receiver.sendMsg(":aurele!aurele@mf-F943E88F.rev.sfr.net JOIN :#A");
    }
    else{
        //receiver.sendMsg(std::string(":") + std::string(receiver.getNickname())+ std::string("!localhost JOIN : ") + msg);
        myChan->addUser(receiver, false);
        myChan->sendToAll(nicknameUsername(receiver) + std::string(" JOIN :") + msg + std::string("\n"));
        //receiver.myCurrentChannel = myChan;
    }
    return true;
}

bool cap(User &receiver, std::string &msg, Server &myServer){
    (void)myServer;
    (void)msg;
    (void)receiver;
    return true;
}

void parseCommand(User &receiver, std::string &receivedMessage, Server &myServer){
    std::vector<std::string> Command = ft_split(receivedMessage, '\n');
    for (std::vector<std::string>::iterator it = Command.begin(); it != Command.end(); it++){
        execCommand(receiver, *it, myServer);
    }
}

void execCommand(User &receiver, std::string &mystring, Server &myServer){
    //std::cout << "Command take " << mystring << std::endl;

    //std::vector < std::pair < std::string, bool(*)(User&, std::string, Server&) > > CommandList;
    std::map<std::string, bool(*)(User&, std::string&, Server&)> CommandList;
    std::string args = mystring.substr(mystring.find(' ', 0) + 1);
    std::string cmd = ft_split(mystring, ' ')[0];
    //std::string cmd = firstArgu(mystring);
    CommandList["QUIT"] = quit;
    //CommandList["PRIVMSG"] = privatemsg;
    //CommandList["NOTICE"] = notice;
    CommandList["PART"] = part;
    CommandList["PING"] = ping;
    CommandList["JOIN"] = joinChannel;
    CommandList["PRIVMSG"] = privatemsg;
    CommandList["KICK"] = kick;
    CommandList["USER"] = user;
    CommandList["NICK"] = nick;
    CommandList["MODE"] = mode;
    CommandList["PASS"] = pass;
    CommandList["CAP"] = cap;
    CommandList["WHO"] = who;

    std::cout << (std::string("Command [") + cmd + std::string("] and "));

    if (args.find('\r') != std::string::npos)
        args.erase(args.find('\r'), 1);
    std::cout << (std::string("args : [") + args + std::string("]\n"));
    if (CommandList.find(cmd) != CommandList.end()){
           CommandList[cmd](receiver, args, myServer);
    }
    else
        receiver.sendMsg("Error " + cmd + " is not a command\n");


//    for (std::map< std::pair < std::string, bool(*)(User&, std::string, Server&) > >::iterator it = (CommandList.begin()); it != CommandList.end(); it++){
//        if (mystring.find((*it).first, 0) == 0){
//            mystring = mystring.erase(0, (*it).first.length());
//            int Alpha = gotAlpha(mystring);
//            if (Alpha > 0)
//            {
//                if ((*it).second(receiver, &(mystring[Alpha]), myServer))
//                    (void) oldString;
//            }
//            else
//            {
//                if (Alpha == -1)
//                    receiver.sendMsg("Error " + (*it).first + " don't have argument\n");
//                else
//                    receiver.sendMsg("Error " + (*it).first + " need spaces between command and args\n");
//            }
//            break;
//        }
//    }
}

/**
bool commandManager(User &user, const std::string& name){
    execCommand(user, name);
} 
int main(int argc, char **argv){
    User a;
    execCommand(a, (argv[1]));

}*/