#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char *argv[]){
    int clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    return 0;
}