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

    // socket failed to bind to ip or port
    if (bind(srvr, (sockaddr*)&address, addrLen) < 0) {
        std::cerr << "Error: did not bind to PORT or IP properly\n";
        close(srvr);
        return -1;
    }

    // server is now bound, listening for a connection, fails if listening function didn't work
    if (listen(srvr, MAX_CONNECTIONS) < 0) {
        std::cerr << "Error: failure to listen for connections\n";
        close(srvr);
        return -1;
    }

    // server is now listening, repeatedly grab new connections in a while loop
    while(true) {
        int newSocket = accept(srvr, (sockaddr*)&address, (socklen_t*)&addrLen);
        if (newSocket < 0) {
            std::cerr << "Error: failed to accept connection\n";
            continue;
        }

        char buffer[BUFFER_SIZE] = {0};
        int readDataLen = read(newSocket, buffer, BUFFER_SIZE);
        if (readDataLen < 0) {
            std::cerr << "Error: failed to read request\n";
            close(newSocket);
            continue;
        }

        std::cout << "Request: " << buffer << std::endl;

        // Extract requested file name from request
        std::string request(buffer);
        std::string fileName = "FilesForServerFolder-1/index.html";  // Default file

        size_t startPos = request.find("GET /");
        if (startPos != std::string::npos) {
            size_t endPos = request.find(" ", startPos + 5);
            std::string requestedFile = request.substr(startPos + 5, endPos - (startPos + 5));

            if (requestedFile.empty() || requestedFile == "/") {
                fileName = "FilesForServerFolder-1/index.html";
            } else {
                fileName = "FilesForServerFolder-1/" + requestedFile;
            }
        }

        // Read the requested file
        std::ifstream file(fileName);
        std::stringstream fileStream;
        if (file) {
            fileStream << file.rdbuf();
            file.close();
        } else {
            fileStream << "<h1>404 Not Found</h1>";
        }
        std::string fileContent = fileStream.str();

        // Send response
        std::string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n\r\n" + fileContent;

        send(newSocket, response.c_str(), response.length(), 0);
        close(newSocket);
    }
}