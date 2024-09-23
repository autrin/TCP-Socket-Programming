#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]){
    int clientSocket;
    struct sockaddr_in serverAddr;
    
    serverAddr.sin_family = PF_INET; // communicatio domain
    serverAddr.sin_port = htons(atoi(argv[1])); // server port to send a message to
    serverAddr.sin_addr.s_addr = inet_addr(INADDR_ANY); // Server ip address to send a message to
    
    if(clientSocket = socket(PF_INET, SOCK_STREAM, 0) < 0){
        perror("Error creating client socket\n");
        return 1;
    }
    printf("Client socket created\n");

    
    return 0;
}