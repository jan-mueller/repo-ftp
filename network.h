/* 
 * File:   network.h
 * Author: philip
 *
 * Created on 22. August 2012, 00:33
 */

#ifndef NETWORK_H
#define	NETWORK_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define END "\r\n"
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
    
    /**
     * Function to send an given String over a Socket
     * 
     * @param socketfd      file discriptor of the socket
     * @param buffer        String which will be send
     * @return  1 on success and 0 on failure
     */
    int sendString(int socketfd,char *buffer);
    
    /**
     * Function to store received String in an given char array 
     * 
     * @param socketfd      file discriptor of the socket
     * @param destBuffer    containts the received String
     * @return length of received String and zero if failt 
     */
    int recvString(int socketfd, char *destBuffer);

    /**
     * create a socket and bind to given port
     * 
     * @param port
     * @return socket file discriptor
     */
    int createBindSocket(int port);

#ifdef	__cplusplus
}
#endif

#endif	/* NETWORK_H */

