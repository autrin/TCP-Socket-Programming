#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]){
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    serverAddr.sin_family = PF_INET; // communicatio domain
    serverAddr.sin_port = htons(atoi(argv[1])); // server port to send a message to
    serverAddr.sin_addr.s_addr = inet_addr(INADDR_ANY); // Server ip address to send a message to
    
    if(clientSocket = socket(PF_INET, SOCK_STREAM, 0) < 0){
        perror("Error creating client socket\n");
        return 1;
    }
    printf("Client socket created\n");
    socklen_t sercverAddrSize = sizeof(serverAddr);
    if(connect(clientSocket, (struct sockaddr *) &serverAddr, sercverAddrSize) < 0){
        perror("Error connecting to server\n");
        return 1;
    }
    printf("Connected to server\n");
    int numBytesSent = write(clientSocket, buffer, sizeof(buffer));
    if(numBytesSent < 0){ // client writes data over socket
        perror("Error writing to server\n");
        return 1;
    }
    printf("Data written to server\n");

    return 0;
}