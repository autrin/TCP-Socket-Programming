#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main (int argc, char *argv[]){
    int serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr, clientAddr;
    char receivedData[1024];
    char sentData[1024];
    if (serverSocket < 0){
        perror("Error creating server socket\n");
        return 1;
    }
    printf("Socket created\n");

    serverAddr.sin_family = PF_INET; // communicatio domain
    serverAddr.sin_port = htons(atoi(argv[1])); // server port to send a message to
    serverAddr.sin_addr.s_addr = inet_addr(INADDR_ANY); // Server ip address to send a message to
    
    if(bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0){
        perror("Error binding socket\n");
        return 1;
    }
    printf("Socket binded\n");

    if(listen(serverSocket, 5) < 0){ // server listens to port, 5 is the number of allowed pending connections
        perror("Error listening on socket\n");
        return 1;
    }
    printf("Listening on socket\n");
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddr, &clientAddrSize); // server accepts an incoming connection
    if(clientSocket < 0){
        perror("Error accepting connection\n");
    }
    printf("Connection accepted\n");

    // server reads data from client
    int numBytesRead = read(clientSocket, receivedData, sizeof(receivedData));
    if(numBytesRead < 0){
        perror("Error reading from client\n");
        return 1;
    }
    printf("Data read from client: %s\n", receivedData);

    int numByteSent = write(clientSocket, sentData, sizeof(sentData));
    if(numByteSent < 0){
        perror("Error writing to client\n");
        return 1;
    }
    printf("Data sent to client: %s\n:", sentData);

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