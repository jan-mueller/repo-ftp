#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "ftp.h"

#define CPORT 21   // CONTROL PORT
#define DPORT 20   // DATA PORT
#define ROOT "./root" // the ftp server's root directory


int main(void) {
   int sockfd, new_sockfd, yes=1;
   struct sockaddr_in host_addr, client_addr;   // my address information
   socklen_t sin_size;

   printf("Accepting requests on port %d\n", CPORT);

   if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
		printf("Failure in socket\n");
	}

   if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1){
		printf("Failure setting socket option SO_REUSEADDR\n");
	}

   host_addr.sin_family = AF_INET;      // host byte order
   host_addr.sin_port = htons(CPORT);    // short, network byte order
   host_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
   memset(&(host_addr.sin_zero), '\0', 8); // zero the rest of the struct

   if (bind(sockfd, (struct sockaddr *)&host_addr, sizeof(struct sockaddr)) == -1){
		printf("Failure bind to socket\n");
	}

   if (listen(sockfd, 20) == -1){
      printf("Failure listening on socket\n");
	}

   while(1) {   // Accept loop
      sin_size = sizeof(struct sockaddr_in);
      new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
   }
   return 0;
}

