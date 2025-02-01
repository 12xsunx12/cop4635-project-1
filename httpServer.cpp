#include "httpServer.hpp"

Server::Server() {
    startServer();
}

int Server::startServer() {
    srvrFields = (AF_INET, SOCK_STREAM, 0); //af_inet for ipv4 //sock stream for tcp/ip protocols

    // -1 if socket fails
    if (srvrFields < 0) {
        std::cerr << "Error: problem initializing server\n";
        close(srvrFields); //close is from unistd.h
        return -1;
    }

    // binding to an ip and a port
    address.sin_family = AF_INET; // for ipv4
    address.sin_addr.s_addr = INADDR_ANY; // make server listen to all interfaces on our system
    address.sin_port = htons(PORT);

    int addrLen = sizeof(address);

    if (bind(srvrFields, (sockaddr*)&address, addrLen) < 0) {
        std::cerr("Error: did not bind to PORT or IP properly\n");
        close(srvrFields);
        return -1;
    }

    // server is now bound, listening for a connection
    if (listen(srvrFields, MAX_CONNECTIONS) < 0) {
        std::cerr("Error: failure to listen for connections\n");
        close(srvrFields);
        return -1;
    }

    // server is now listening, repeatedly grab new connections in a while loop
    while(true) {

        // type casting sockaddr_in* to sockaddr*
        int newSocket = accept(srvrFields, (sockaddr*)&address, (socklen_t*)&addrLen);

        // now that a socket has been established to an endpoint, data can be sent and recieved
    }
}