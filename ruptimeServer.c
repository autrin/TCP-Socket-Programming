#include <stdio.h>
#include <bits/socket.h>
#include <netinet/in.h>

int main (int argc, char *argv[]){
    int serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0){
        printf("Error creating socket\n");
        return 1;
    }
    printf("Socket created\n");

    struct sockaddr_in serverAddr, clientAddr;
    serverAddr.sin_family = PF_INET;
    serverAddr.sin_port = htons(atoi(argv[1])); // server port to send a message to
    serverAddr.sin_addr.s_addr = inet_addr(INADDR_ANY); // Server ip address to send a message to
    
  
    return 0;
}