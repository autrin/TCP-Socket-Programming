#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]){
    int clientSocket;
    struct sockaddr_in serverAddr;
    
    if(clientSocket = socket(PF_INET, SOCK_STREAM, 0) < 0){
        perror("Error creating client socket\n");
        return 1;
    }
    printf("Client socket created\n");

    
    return 0;
}