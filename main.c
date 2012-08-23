#include "network.h"
#include "helpers.h"

#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

void handleConnection(int sockfd,struct sockaddr_in *clientAddr);

int main(int argc, char *argv[]){

    int socket,acceptedSocket;
    socklen_t size = sizeof(struct sockaddr_in);
    struct sockaddr_in clientAddr;
    
    if(argc!=2)
        usage(argv[0]);
    
    socket = createBindSocket(atoi(argv[1]));
    
    if(listen(socket,20) == -1){
        printErr("Unable to listen on socket");
    }
    
    while(1){
        acceptedSocket = accept(socket,(struct sockaddr*)&clientAddr,&size);
        if(acceptedSocket== -1){
            printErr("Unable to accept connection");
        }
        
        handleConnection(acceptedSocket,&clientAddr);
    }
    shutdown(socket,SHUT_RDWR);
    return 0;
}

void handleConnection(int sockfd,struct sockaddr_in* clientAddr){
    char buffer[500];
    int len;
    printf("test");
    len = recvString(sockfd,buffer);
    printf("%s\n",buffer);
    sendString(sockfd,buffer);
    shutdown(sockfd,SHUT_RDWR);
}