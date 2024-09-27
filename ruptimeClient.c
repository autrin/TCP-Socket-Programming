#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    int clientSocket;
    struct sockaddr_in serverAddr;
    char sentData[1024] = "Hello from client";
    char receivedData[1024];

    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    if(clientSocket < 0){
        perror("Error creating client socket\n");
        return 1;
    }
    printf("Client socket created\n");

    serverAddr.sin_family = PF_INET; // communication domain
    serverAddr.sin_port = htons(atoi(argv[1])); // server port to send a message to
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost IP address for testing
    
    socklen_t serverAddrSize = sizeof(serverAddr);
    if(connect(clientSocket, (struct sockaddr *) &serverAddr, serverAddrSize) < 0){ // (struct sockaddr *) &serverAddr casts the address of serverAddr to a pointer
        perror("Error connecting to server\n");
        return 1;
    }
    printf("Connected to server\n");

    int numBytesSent = write(clientSocket, sentData, strlen(sentData));
    if(numBytesSent < 0){ // client writes data over socket
        perror("Error writing to server\n");
        return 1;
    }
    printf("Data written to server %s\n", sentData);

    int numBytesRead = read(clientSocket, receivedData, sizeof(receivedData) - 1); // client reads data
    if(numBytesRead < 0){
        perror("Error reading from server\n");
        return 1;
    }
    receivedData[numBytesRead] = '\0'; // Null-terminate the string
    printf("Data read from server: %s\n", receivedData);
    
    close(clientSocket); // close client socket
    if(clientSocket < 0){
        perror("Error closing client socket\n");
        return 1;
    }
    printf("Client socket closed\n");
    return 0;
}
