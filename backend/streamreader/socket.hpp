#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <string>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <cstring>

using namespace std;

class Socket{

    public:
        Socket(string URL, int port);
        ~Socket();

    private:
        int port;
        string URL;
        struct sockaddr_in sockAddr;
        int sock;

        bool tcp_handshake();
        string make_http_request(string URL);
        void create_socket();
        string receive();
};

#endif

