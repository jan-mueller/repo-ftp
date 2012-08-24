#include "network.h"
#include "helpers.h"
#include "command.h"

#include <string.h>

#include <sys/socket.h>

#include <netdb.h>

void handleConnection(int sockfd,struct sockaddr_in *clientAddr);
int running=1;

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
   char buffer[1024]={0};
   int len;

   sendString(sockfd,"220 ftp.hack.me FTP server");
	recvString(sockfd,buffer);		

	while(strncasecmp(buffer, "USER anonymous", 14)){
		sendString(sockfd,USERFAILED " This FTP is anonymous only");
		recvString(sockfd,buffer);		
   }
	
	
	sendString(sockfd,USER" Please enter password");
	recvString(sockfd,buffer);

	while(strncasecmp(buffer, "PASS ", 5)){
		sendString(sockfd,USERFAILED" Please login with USER and PASS");
		recvString(sockfd,buffer);
	}

	sendString(sockfd,PASS" Login successful");
	
	len = recvString(sockfd,buffer);
	
	if(!strncasecmp(buffer,"SYST",4)){
		sendString(sockfd,SYST" UNIX Type: L8");
	}
	while(running);	


   shutdown(sockfd,SHUT_RDWR);
}
