#include "httpServer.hpp"

httpServer::httpServer() {
    startServer();
}

int httpServer::startServer() {
    int srvr = socket(AF_INET, SOCK_STREAM, 0); //af_inet for ipv4 //sock stream for tcp/ip protocols

    // -1 if socket fails
    if (srvr < 0) {
        std::cerr << "Error: problem initializing server\n";
        close(srvr); //close is from unistd.h
        return -1;
    }

    // set socket option; helps with removing the time gap between re-using ports after you close the program and re-launch it
    int opt = 1;
    setsockopt(srvr, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // binding to an ip and a port
    address.sin_family = AF_INET; // for ipv4
    address.sin_addr.s_addr = INADDR_ANY; // make server listen to all interfaces on our system
    address.sin_port = htons(PORT);

    int addrLen = sizeof(address);

    if (bind(srvr, (sockaddr*)&address, addrLen) < 0) {
        std::cerr << "Error: did not bind to PORT or IP properly\n";
        close(srvr);
        return -1;
    }

    // server is now bound, listening for a connection
    if (listen(srvr, MAX_CONNECTIONS) < 0) {
        std::cerr << "Error: failure to listen for connections\n";
        close(srvr);
        return -1;
    }

    // server is now listening, repeatedly grab new connections in a while loop
    while(true) {

        // type casting sockaddr_in* to sockaddr*
        int newSocket = accept(srvr, (sockaddr*)&address, (socklen_t*)&addrLen);

        // now that a socket has been established to an endpoint, data can be sent and recieved
        std::string request;
        char buffer[BUFFER_SIZE] = {0};
        int readDataLen = read(newSocket, buffer, BUFFER_SIZE); 

        // print the request
        std::cout << buffer << std::endl;

        // send a basic response as testing, to see if we recieve anything from the browser view
        std::string response = 
        "HTTP/1.1 200 OK\r\n" // header
        "Content-Type:text/plane\r\n"
        "Connection:close\r\n\r\n"
        "Hello from server!";

        send(newSocket, response.c_str(), response.length(), 0);
        close(newSocket);
    }
}