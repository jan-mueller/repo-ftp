#include "network.h"
#include "helpers.h"


int sendString(int socketfd, char *buffer){
    int sentBytes,bytesToSend;
    bytesToSend = strlen(buffer);

    while(bytesToSend > 0){
        sentBytes = send(socketfd,buffer,bytesToSend,0);
        if(sentBytes == -1){
            return 0;
        }
        bytesToSend -= sentBytes;
        buffer +=sentBytes;
    }
    send(socketfd,"\n",1,0);
    return 1;
}

int recvString(int socketfd, char *destBuffer){
    int receivedBytes=0;
    char *ptr;
    int endseq=0;
    
    ptr = destBuffer;
    while(recv(socketfd,ptr,1,0)==1){
        if(*ptr==END[endseq] && endseq < sizeof(END)-1 )
            endseq++;
        else
            endseq=0;
        
        if(endseq == sizeof(END)-2){
            ptr--;
            ptr='\0';
            break;
        }
        
        ptr++;
        receivedBytes++;
    }
    return receivedBytes;
}

int createBindSocket(int port){
    int socketfd;
    int yes=1; // ????????
    struct sockaddr_in host_addr;
    
    if((socketfd = socket(PF_INET,SOCK_STREAM,0))== -1)
        printErr("Unable to create socket");
    
    if(setsockopt(socketfd,SOL_SOCKET, SO_REUSEADDR,&yes,sizeof(int)) == -1)
        printErr("Unable to setup the socket");
    
    host_addr.sin_family=AF_INET;
    host_addr.sin_port = htons(port);
    host_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(host_addr.sin_zero),0,8);
    
    if(bind(socketfd,(struct sockaddr*)&host_addr,sizeof(struct sockaddr)) == -1)
        printErr("Unable to bind socket");
    
    return socketfd;
}
