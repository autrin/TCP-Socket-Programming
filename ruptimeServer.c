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

    return 0;
}