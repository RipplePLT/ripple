#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <string>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>

class Socket{

    public:
        Socket(string URL, int port);
        ~Socket();

    private:
        char[256] http_request;
        int sock;
        struct sockaddr_in sock;
        bool connect(string URL);
        string receive();
};

#endif

