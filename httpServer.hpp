#ifndef H_SERVER
#define H_SERVER

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 60001
#define MAX_CONNECTIONS 10
#define BUFFER_SIZE 1024

class httpServer { 
    public:
        httpServer();
        int startServer();

    private:
    int srvrFields;
    sockaddr_in address;
};

#endif