#include "helpers.h"

void printErr(const char* msg){
    
    fprintf(stderr,"ERROR: %s\n",msg);
    exit(EXIT_FAILURE);
}

void usage(const char *arg){
    printf("\nUsage: %s port\n",arg);
    exit(EXIT_FAILURE);
}