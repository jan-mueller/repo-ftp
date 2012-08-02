#ifndef _FTP_H_

#define _FTP_H_

char const banner[]="Welcome to the VulnFTP-0.0.1";

/* FTP Command tokens */
enum command_types{ 
	USER, PASS, ACCT, CWD, CDUP, SMNT, REIN, QUIT, PORT, PASV, TYPE, STRU, MODE, 
	RETR, STOR, STOU, APPE, ALLO, REST, RNFR, RNTO, ABOR, DELE, RMD, MKD, PWD, 
	LIST, NLST, SITE, SIZE, SYST, STAT, HELP, NOOP, EOFC, ERROR,
};

/* struct used to build a table mapping command character sequences to
 *    their command token listed above */
struct command_list{
	char *command;
	enum command_types command_code;
};

/* Lookup table for FTP Commands*/
struct command_list command_lookup[] = {
	{"USER", USER}, {"PASS", PASS}, {"ACCT", ACCT}, {"CWD", CWD},
	{"CDUP", CDUP}, {"SMNT", SMNT}, {"REIN", REIN}, {"QUIT", QUIT},
	{"PORT", PORT}, {"PASV", PASV}, {"TYPE", TYPE}, {"STRU", STRU},
	{"MODE", MODE}, {"RETR", RETR}, {"STOR", STOR}, {"STOU", STOU},
	{"APPE", APPE}, {"ALLO", ALLO}, {"REST", REST}, {"RNFR", RNFR},
	{"RNTO", RNTO}, {"ABOR", ABOR}, {"DELE", DELE}, {"RMD", RMD},
	{"MKD", MKD}, {"XMKD", MKD}, {"XRMD", RMD}, {"PWD", PWD},
	{"XPWD", PWD}, {"LIST", LIST}, {"NLST", NLST}, {"SITE", SITE},
	{"SIZE", SIZE}, {"SYST", SYST}, {"STAT", STAT}, {"HELP", HELP},
	{"NOOP", NOOP}, {"EOFC", EOFC},
};

enum command_modes {LOGIN, PASSWORD, COMMANDS, EXIT};


#endif
