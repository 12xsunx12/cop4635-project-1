# HTTP Server Protocol Documentation

This document describes the protocol implementation and message exchange between the web browser client and the HTTP server implemented in this project.

## Protocol Overview

The server implements HTTP/1.1 protocol over TCP/IP for communication with web browsers. It specifically handles GET requests and provides appropriate responses with either requested files or error messages.

## Network Protocol Stack

1. Application Layer: HTTP/1.1
2. Transport Layer: TCP (SOCK_STREAM)
3. Network Layer: IPv4 (AF_INET)

## Server Initialization

### Socket Creation and Configuration
```cpp
socket(AF_INET, SOCK_STREAM, 0)
```
- Creates a TCP socket using IPv4
- Returns a file descriptor for the socket
- Configuration includes:
  - `AF_INET`: IPv4 protocol
  - `SOCK_STREAM`: TCP protocol
  - `SO_REUSEADDR`: Enables immediate port reuse

### Address Binding
```cpp
bind(srvr, (sockaddr*)&address, addrLen)
```
- Binds the server to:
  - Port: 60001 (defined in PORT macro)
  - IP: INADDR_ANY (listens on all available network interfaces)
  - Address Family: AF_INET (IPv4)

## Connection Handling

### Connection Listening
```cpp
listen(srvr, MAX_CONNECTIONS)
```
- Listens for incoming connections
- Queue size: 10 connections (defined in MAX_CONNECTIONS)

### Connection Acceptance
```cpp
accept(srvr, (sockaddr*)&address, (socklen_t*)&addrLen)
```
- Accepts new client connections
- Creates new socket for each accepted connection
- Returns file descriptor for the new connection

## Message Exchange Protocol

### 1. Client Request Processing

#### Request Reading
```cpp
read(newSocket, buffer, BUFFER_SIZE)
```
- Reads HTTP request from client
- Buffer size: 1024 bytes (defined in BUFFER_SIZE)
- Parses GET requests from the received data

#### Request Format
Example client GET request:
```
GET /index.html HTTP/1.1
Host: 127.0.0.1:60001
Connection: keep-alive
...
```

### 2. Server Response Processing

#### Response Format
Server sends HTTP responses with the following structure:
```
HTTP/1.1 200 OK
Content-Type: text/html
Connection: close

[File Content]
```

#### Response Sending
```cpp
send(newSocket, response.c_str(), response.length(), 0)
```
- Sends HTTP response to client
- Includes headers and requested file content
- Or sends 404 error for non-existent files

## Error Handling

### HTTP Status Codes
- 200 OK: Successful request
- 404 Not Found: File not found

### Socket Error Handling
- Socket creation failures
- Binding failures
- Connection acceptance errors
- Read/Write operation errors

## Connection Termination

### Per-Request Cleanup
```cpp
close(newSocket)
```
- Closes the connection socket after each request
- Ensures proper resource cleanup

### Server Shutdown
- Handles SIGINT (Ctrl+C) for clean shutdown
- Closes main server socket
- Frees allocated resources

## Libraries and Dependencies

The server implementation relies on the following system libraries:
- `sys/socket.h`: Socket programming functions
- `netinet/in.h`: Internet address family
- `unistd.h`: POSIX operating system API
- `fstream`: File operations
- `sstream`: String stream processing

## Buffer and Connection Limits

- Maximum connections queue: 10
- Request buffer size: 1024 bytes
- Default port: 60001