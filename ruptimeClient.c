#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char *argv[]){
    int clientSocket;
    if(clientSocket = socket(PF_INET, SOCK_STREAM, 0) < 0){
        perror("Error creating client socket\n");
        return 1;
    }
    
    return 0;
}