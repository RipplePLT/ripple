#include "socket.hpp"


Socket::Socket(string URL, int port){
    this->port = port;
    this->URL = URL;
    create_socket();
}

Socket::~Socket(){


}

void Socket::create_socket(){
    if((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Socket creation failed");
        exit(1);
    }

    memset(&sockAddr, 0, sizeof(sockAddr));
    if(inet_addr(this->URL.c_str()) == -1){
        struct hostent *he;
        struct in_addr **addr_list;

        if((he = gethostbyname(this->URL.c_str())) ==NULL){
            perror("failed to get host name");
            exit(1);
        }

        addr_list = (struct in_addr **) he->h_addr_list;

        for(int i = 0; addr_list[i] != NULL; i++){
            sockAddr.sin_addr = *addr_list[i];
            cout<<  this->URL << "resolved to " <<inet_ntoa(*addr_list[i])<<endl;
            break;
        }
    }else{
        this->sockAddr.sin_addr.s_addr =inet_addr(URL.c_str());
    }

    this->sockAddr.sin_family = AF_INET;
    this->sockAddr.sin_port = htons(port);
}

/*
 * Connects to a webpage - Goes through full TCP handshake
 */
bool Socket::tcp_handshake(){
    



}

/*
 * Receives data from web
 *
 */
string Socket::receive(){


}
