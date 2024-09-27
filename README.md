# TCP Socket Programming Project
## Overview
This project implements a simple TCP client-server application that mimics the behavior of the ruptime command. The server sends the system's uptime information to the client upon request.

## Files
ruptimeServer.c: The server program. It listens for incoming client connections, captures the system's uptime using the uptime command, and sends the result to the client.

ruptimeClient.c: The client program. It connects to the server, sends a request, and displays the uptime information received from the server.

## Functionality
The server remains open, continuously accepting and serving new clients.

Upon connection, the client requests the server's uptime, and the server responds with the system's uptime information.
## Notes
The client and server can both be run on the localhost (127.0.0.1) for testing.
