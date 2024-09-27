#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]){
    int clientSocket;
    struct sockaddr_in serverAddr;
    char sentData[1024];
    char receivedData[1024];
    FILE *fp;
    
    serverAddr.sin_family = PF_INET; // communicatio domain
    serverAddr.sin_port = htons(atoi(argv[1])); // server port to send a message to
    serverAddr.sin_addr.s_addr = inet_addr(INADDR_ANY); // Server ip address to send a message to
    
    if(clientSocket = socket(PF_INET, SOCK_STREAM, 0) < 0){
        perror("Error creating client socket\n");
        return 1;
    }
    printf("Client socket created\n");
    socklen_t sercverAddrSize = sizeof(serverAddr);
    if(connect(clientSocket, (struct sockaddr *) &serverAddr, sercverAddrSize) < 0){ // (struct sockaddr *) &serverAddr casts the address of serverAddr to a pointer
        perror("Error connecting to server\n");
        return 1;
    }
    printf("Connected to server\n");
    int numBytesSent = write(clientSocket, sentData, sizeof(sentData));
    if(numBytesSent < 0){ // client writes data over socket
        perror("Error writing to server\n");
        return 1;
    }
    printf("Data written to server %s\n", sentData);

    int numBytesRead = read(clientSocket, receivedData, sizeof(receivedData)); // client reads data
    if(numBytesRead < 0){
        perror("Error reading from server\n");
        return 1;
    }
    // Sample output: 192.168.254.2: 10:47am up 27 day(s), 50 mins, 1 user, load average: 0.18, 0.26, 0.20

    printf("Data read from server: %s\n", receivedData);
    
    close(clientSocket); // close client socket
    if(clientSocket < 0){
        perror("Error closing client socket\n");
        return 1;
    }
    printf("Client socket closed\n");
    return 0;
}