/* 
 * File:   helpers.h
 * Author: philip
 *
 * Created on 22. August 2012, 01:12
 */

#ifndef HELPERS_H
#define	HELPERS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdlib.h>
#include <stdio.h>
    
    /**
     * prints the given message and quit the program
     * 
     * @param msg       Errormessage
     */
    void printErr(const char *msg);
    void usage(const char *arg);


#ifdef	__cplusplus
}
#endif

#endif	/* HELPERS_H */

