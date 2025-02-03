# C++ HTTP Server Implementation

A lightweight HTTP server implementation in C++ that handles basic GET requests and serves static files.

## Authors

- Regan O'Donnell
- Thomas Alston

## Project Overview

This project implements a basic HTTP/1.1 server in C++ that can:
- Handle incoming GET requests from web browsers
- Serve static HTML files and images
- Process multiple requests until explicitly terminated
- Listen on port 60001
- Provide output of all server activities
- Handle both successful file transfers and "404 Not Found" scenarios

The server includes proper HTTP header handling, file path resolution, and error management. It's built using standard POSIX socket programming interfaces and can communicate with any standard web browser.

## Getting Started

### Prerequisites

- C++ compiler with C++11 support (g++ will work fine)
- POSIX-compliant operating system (Linux/Unix/WSL)
- Make build system

### Compilation

To compile the server, navigate to the project directory and run:

```bash
make
```

This will generate the executable using the provided Makefile.

### Running the Server

1. After compilation, the server will automatically start when you run the executable.
2. Open your web browser and navigate to:
   ```
   http://127.0.0.1:60001
   ```
3. You'll be presented with the home page, which includes test links for both existing and non-existent resources.

### Stopping the Server

1. To stop the server, press `CTRL+C` in the terminal where the server is running
2. After stopping the server, clean up the build files with:
   ```bash
   make clean
   ```

## Implementation Details

The server is implemented across several files:
- `httpServer.cpp` - Main server implementation
- `httpServer.hpp` - Server class definition and constants
- `main.cpp` - Entry point
- `index.html` - Default landing page
- `testPresence.html` - Test page for image serving

The server utilizes standard C++ libraries and POSIX socket programming to handle HTTP communications, file I/O, and network operations.

## Features

- HTTP/1.1 GET request handling
- Static file serving
- Default index.html routing
- 404 error handling for non-existent resources
- Clean shutdown handling
- Verbose server activity logging

## Project Status

✅ Complete and functional implementation including:
- Basic HTTP server functionality
- File serving capabilities
- Error handling
- Multiple request processing
- Clean shutdown procedures