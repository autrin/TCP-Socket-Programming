#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main (int argc, char *argv[]){
    int serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr, clientAddr;
    char receivedData[1024];
    char sentData[1024];
    FILE *fp;

    if (serverSocket < 0){
        perror("Error creating server socket\n");
        return 1;
    }
    printf("Socket created\n");

    // Set server address
    serverAddr.sin_family = PF_INET; // communicatio domain
    serverAddr.sin_port = htons(atoi(argv[1])); // Server port passed as argument
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Bind to all available interfaces
    
    // bind socket to server address
    if(bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0){
        perror("Error binding socket\n");
        return 1;
    }
    printf("Socket binded\n");

    if(listen(serverSocket, 5) < 0){ // Maximum of 5 pending connections
        perror("Error listening on socket\n");
        return 1;
    }
    printf("Listening on socket\n");

    // Accept an incoming connection
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddr, &clientAddrSize); // server accepts an incoming connection
    if(clientSocket < 0){
        perror("Error accepting connection\n");
        return 1;
    }
    printf("Connection accepted\n");

    // server reads data from client
    int numBytesRead = read(clientSocket, receivedData, sizeof(receivedData));
    if(numBytesRead < 0){
        perror("Error reading from client\n");
        return 1;
    }
    receivedData[numBytesRead] = '\0'; // Null-terminate the string
    printf("Data read from client: %s\n", receivedData);

    int numByteSent = write(clientSocket, sentData, sizeof(sentData));
    if(numByteSent < 0){
        perror("Error writing to client\n");
        return 1;
    }
    printf("Data sent to client: %s\n:", sentData);
    // Sample output: 192.168.254.2: 10:47am up 27 day(s), 50 mins, 1 user, load average: 0.18, 0.26, 0.20
    fp = popen("uptime", "r");
    if(fp == NULL){
        perror("popen failed");
        exit(1);    
    }
    while(fgets(receivedData, sizeof(receivedData), fp)){
        printf("%s", receivedData);
    }
    close(clientSocket);
    if(clientSocket < 0){
        perror("Error closing client socket\n");
        return 1;
    }
    printf("Client socket closed\n");

    close(serverSocket);
    if(serverSocket < 0){
        perror("Error closing server socket\n");
        return 1;
    }
    printf("Server socket closed\n");
    return 0;
}