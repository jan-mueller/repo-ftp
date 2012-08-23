#include "network.h"
#include "helpers.h"
#include "command.h"

#include <string.h>

#include <sys/socket.h>

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
    char buffer[1024];
    int len;
    sendString(sockfd,"220 ftp.hack.me FTP server");
    
	while(recvString(sockfd,buffer)){
		if(strncasecmp(buffer, "USER anonymous", 14))
			sendString(sockfd,USERFAILED " This FTP is anonymous only");
		else
			break;
	}
    
	sendString(sockfd,USER" Please enter password");

	while(recvString(sockfd,buffer)){
		if(strncasecmp(buffer, "PASS", 4))
			sendString(sockfd,USERFAILED" Please login with USER and PASS");
		else
			break;
	}

	sendString(sockfd,PASS" Login successful");
	
	len = recvString(sockfd,buffer);

    shutdown(sockfd,SHUT_RDWR);
}
