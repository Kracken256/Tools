#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

std::string exec(std::string cmd)
{
    char buffer[128];
    std::string result = std::string();
    FILE *pipe = popen(cmd.data(), "r");
    if (!pipe)
        throw std::runtime_error("popen() failed!");
    try
    {
        while (fgets(buffer, sizeof(buffer), pipe) != NULL)
        {
            result += buffer;
        }
    }
    catch (...)
    {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

void print(std::string data)
{
    std::cout << data;
}

void println(std::string data)
{
    std::cout << data << std::endl;
}

void print_help()
{
    println("Status tool");
    println("Commands:");
    println("\tnet\tShow open ports / connections");
    println("\tusers / user\tList users on box");
    println("\tsudo\tShow users in sudoers file");
    println("\thost\tShow host info");
    println("\tps\tShow running processes");
    println("\tinfo\tRun net and host command");
    println("\tall\tRun all commands");
}

int net_info()
{
    if (exec("which netstat").find("not found") != std::string::npos)
    {
        println("netstat not found");
        return -2;
    }
    println(exec("netstat -nutl"));
    return 0;
}
int user_info()
{
    println(exec("cat /etc/passwd  | awk -F \":\" {'print $1'}"));
    return 0;
}
int sudo_info()
{
    println(exec("cat /etc/sudoers | grep -v \"#\" | grep -v \"Defaults\" | grep -v \"@\" | sed -r '/^\\s*$/d'"));
    return 0;
}
int host_info()
{
    println(exec("cat /etc/hosts"));
    return 0;
}
int ps_info()
{
    println(exec("ps aux"));
    return 0;
}
int main(int argc, char *argv[])
{
    std::vector<std::string> args(argv + 1, argv + argc);

    if (args.size() == 0)
    {
        print_help();
        return 0;
    }
    if (args.size() < 1)
    {
        println("Specify command");
        return -1;
    }
    std::string command = args[0];
    if (command == "net" || command == "netstat" || command == "netinfo" || command == "n")
    {
        return net_info();
    }
    else if (command == "users" || command == "user" || command == "u")
    {
        return user_info();
    }
    else if (command == "sudo" || command == "sudoers" || command == "insudo" || command == "s")
    {
        return sudo_info();
    }
    else if (command == "host" || command == "hosts" || command == "h")
    {
        return host_info();
    }
    else if (command == "ps" || command == "p")
    {
        return ps_info();
    }
    else if (command == "info" || command == "i")
    {
        net_info();
        println("");
        println("Host info");
        host_info();
    }
    else if (command == "all" || command == "a")
    {
        println("Net info:");
        net_info();
        println("User info");
        user_info();
        println("Sudo user info");
        sudo_info();
        println("Host file info");
        host_info();
        println("Process info");
        ps_info();
        return 0;
    } else {
        println("Unrecognized command");
        print_help();
    }
    return 0;
}