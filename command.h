#ifndef _COMMAND_H_

#define _COMMAND_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ABORT "426"
#define CWD "250"
#define SYST "215"
#define PWD "257"
#define COMOK "200"
#define COMFA "500"
#define PASV "227"
#define TRANSOK "226"
#define USERFAILED "530"
#define USER "331"
#define PASS "230"


int abor();

int cwd();

int dele();

int list();

int mdtm();

int mkd();

int nlst();

int pass();

int pasv();

int port();

int pwd();

int quit();

int retr();

int rmd();

int rnfr();

int rnto();

int site();

int size();

int stor();

int type();

int user();


#endif
