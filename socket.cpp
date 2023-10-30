#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BOLDBLACK "\033[1m\033[30m" 
#define BOLDRED "\033[1m\033[31m"
#define BOLDGREEN "\033[1m\033[32m"

class Server
{
private:
    int sock_fd;
    unordered_map<string, int> con_fd;
    struct sockaddr_in sock_addr;
    struct sockaddr_in con_addr;
    int con_addrlen = sizeof(con_addr);
    int bytes_read;
    char buffer[1024];

public:
    int tc = 0;
    string lc = "";
    void bind(const char *host, int port)
    {
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_addr.s_addr = inet_addr(host);
        sock_addr.sin_port = htons(port);
        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        ::bind(sock_fd, (struct sockaddr *)&sock_addr, sizeof(struct sockaddr));
        cout << "\n [" << BOLDGREEN << "+" << RESET << "] Server Info:\n\n"
             << "     │\n"
             << "     ├──━ host ➜ " << host << "\n"
             << "     │\n"
             << "     └──━ port ➜ " << port << endl;
    }
    void listen(int n)
    {
        ::listen(sock_fd, n);
        cout << "\n\n [" << BOLDGREEN << "+" << RESET << "] Server Status: Running\n"
             << "\n\n [" << BOLDGREEN << "+" << RESET << "] All Connections:\n"
             << endl;
    }
    void accept()
    {
        int fd = ::accept(sock_fd, (struct sockaddr *)&con_addr, (socklen_t *)&con_addrlen);
   
        bytes_read = read(fd, buffer, 1024);
        buffer[bytes_read] = '\0';
        con_fd.insert({buffer, fd});

        cout << "     │\n"
             << "     ├──━ 💻  " << buffer << endl;
        lc=buffer;
        tc++;
    }
    void send(const char *msg, string ignore_id = "")
    {
        for (auto &it : con_fd)
        {
            if (it.first != ignore_id)
            {
                write(it.second, msg, strlen(msg));
            }
        }
    }
    int recv(string id)
    {
        bytes_read = read(con_fd[id], buffer, 1024);
        buffer[bytes_read] = '\0';
        if (bytes_read == 0)
        {
            string dis_msg = BOLDRED + ("  " + id + " left") + RESET;
            con_fd.erase(id);
            send(dis_msg.c_str());
            return -1;
        }
        else
        {
            send(buffer, id);
        }
        return 0;
    }
    void close()
    {
        ::close(sock_fd);
    }
};

class Client
{
private:
    int dest_fd, bytes_read;
    char buffer[1024];
    struct sockaddr_in dest_addr;

public:
    void connect(const char *host, int port)
    {
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_addr.s_addr = inet_addr(host);
        dest_addr.sin_port = htons(port);
        dest_addr.sin_zero[8] = '\0';
        dest_fd = socket(AF_INET, SOCK_STREAM, 0);
        ::connect(dest_fd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr));
    }
    void send(const char *msg)
    {
        write(dest_fd, msg, strlen(msg));
    }
    string recv()
    {
        bytes_read = read(dest_fd, buffer, 1024);
        buffer[bytes_read] = '\0';
        if (sizeof(buffer) > 0)
        {
            return buffer;
        }
    }
    void close()
    {
        ::close(dest_fd);
    }
};
