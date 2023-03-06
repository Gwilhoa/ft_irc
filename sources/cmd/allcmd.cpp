#include "ft_irc.hpp"

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
    if (name.find("#") == 0){
        std::cout << "[NICK] Error syntaxe nickname must no begin by '#'" << std::endl;
        user.sendMsg("ERROR :Nickname must no begin by '#'");
        return false;
    }
    (void)myServer;
    myServer.SendToAllWith(nicknameUsername(user) + std::string(" NICK ") + name + std::string("\n"), user);
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
    if (name.find("#") == 0){
        std::cout << "Error syntax" << std::endl;
        return false;
    }
    
    (void) myServer;
    std::vector<std::string> split = ft_split(name, ' ');
    if (split.size() == 4) {
        return (user.setUsername(split[3].substr(1)));
         //myServer.SendToAllWith(nicknameUsername(user) + std::string(" NICK ") + name + std::string("\n"), user);
    }
    return false;
}

bool quit(User &user, std::string &name, Server &myServer){
    (void) (name);
     myServer.SendToAllWith(nicknameUsername(user) + std::string(" QUIT ") + name + std::string("\n"), user);
    myServer.quit(user);
    return true;
}

bool part(User &user, std::string &args, Server &myServer){
    std::string name = ft_split(args, ' ')[0];
    Channel* myChan = myServer.getChannelByName(name);
    if (myChan){
        myChan->sendToAll(nicknameUsername(user) + std::string(" PART ") + args + std::string("\n"));
        std::string* ret = myChan->removeUser(user);
        if (ret){
            myServer.removeChannel(*ret);
        }
        
        return true;
    }
    return false;
}

bool privatemsg(User &receiver, std::string &msg, Server &myServer){
    if (!receiver.completed)
    {
        std::cout << "Not completed" << std::endl;
        return false;
    }
    std::string sender = ft_split(msg, ' ')[0];
    Channel* myChan = myServer.getChannelByName(sender);
    if (myChan ){
        myChan->sendToAllUnless(nicknameUsername(receiver) + std::string(" PRIVMSG ") + msg + std::string("\n"), receiver);
        return true;
    }
    else {
        User* use = myServer.getUserByName(sender);
        if (use && myServer.IsInTheSameChannel(&receiver, use)){
            use->sendMsg(nicknameUsername(receiver) + std::string(" PRIVMSG ") + msg + std::string("\n"));
            return true;
        }
    }
    return false;
}

/*bool notice (User &receiver, std::string &msg, Server &myServer){
    if (!receiver.completed)
        return false;
    User* use = myServer.getUserByName(ft_split(msg, ' ')[0]);
    if (use){
        use->sendMsg(nicknameUsername(receiver) + std::string(" NOTICE ") + msg + std::string("\n"));
        receiver.sendMsg(nicknameUsername(receiver) + std::string(" NOTICE ") + msg + std::string("\n"));
        return true;
    }
    return false;
}*/

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
    if (myChan && args.size() == 2 && myChan->is_op(receiver)){
        User* use = myChan->getUserByName(args[1]);
        if (use){
            myChan->sendToAll(nicknameUsername(receiver) + std::string(" MODE ") + args[0] +  " +o " + args[1] + std::string("\n"));
            myChan->op(*use);
            return true;
        }
    }
        myServer.Show();
    return false;
}

bool ping(User &receiver, std::string &msg, Server &myServer){
    (void)myServer;
    receiver.sendMsg("PONG " + msg);
    return true;
}

bool kick(User &receiver, std::string &msg, Server &myServer){
    if (!receiver.completed)
    {
        std::cout << "Not completed" << std::endl;
        return false;
    }
    (void)receiver;
    std::vector<std::string> args = ft_split(msg, ' ');
    Channel* myChan = myServer.getChannelByName(args[0]);
    if (myChan && args.size() == 2){
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
    myServer.Show();
    if (!receiver.completed)
    {
        std::cout << "Not completed" << std::endl;
        return false;
    }
    if (msg.find("#") != 0){
        std::cout << "Error syntax" << std::endl;
        return false;
    }
    Channel *myChan = (myServer.getChannelByName(msg));
    if (myChan == NULL) {
            Channel* temp = myServer.addChannel(msg);
            temp->addUser(receiver);
            temp->sendToAll(nicknameUsername(receiver) + std::string(" JOIN :") + msg + std::string("\n"));
    }
    else {
        myChan->addUser(receiver);
        myChan->sendToAll(nicknameUsername(receiver) + std::string(" JOIN :") + msg + std::string("\n"));
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
    while (receivedMessage.find('\r') != std::string::npos)
        receivedMessage.erase(receivedMessage.find('\r'), 1);
    std::vector<std::string> Command = ft_split(receivedMessage, '\n');
    for (std::vector<std::string>::iterator it = Command.begin(); it != Command.end(); it++){
        execCommand(receiver, *it, myServer);
    }
}

void execCommand(User &receiver, std::string &mystring, Server &myServer){
    std::map<std::string, bool(*)(User&, std::string&, Server&)> CommandList;
    std::string args = mystring.substr(mystring.find(' ', 0) + 1);
    std::string cmd = ft_split(mystring, ' ')[0];
    CommandList["QUIT"] = quit;
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
    std::cout << "fd : " << receiver.getFd() << " execute : " << cmd << " " << args << std::endl;
    if (CommandList.find(cmd) != CommandList.end()){
           CommandList[cmd](receiver, args, myServer);
    }
    else
        receiver.sendMsg("Error " + cmd + " is not a command\n");
}