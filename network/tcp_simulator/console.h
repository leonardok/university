#ifndef __CONSOLE_H__
#define __CONSOLE_H__

typedef struct cmd_s cmd_t;
struct cmd_s
{
	char *cmd;
	char *description;
	void (*action)(void);
};

void show_help(void);
void quit(void);
void passive_open(void);
void active_open(void);

#define COMMAND_NUM 6
cmd_t commands[COMMAND_NUM] = {
	{"help",   "\t\tshow this help", show_help},
	//{"passive_open host", "tell host to start to listen", NULL},
	{"active_open host", "tell host start a connection with other host", active_open},
	{"sndack", "\t\tsend ack to other host", NULL},
	{"sndpkg", "\t\tsend package to other host", NULL},
	{"close",  "\t\tsend FIN to other host", passive_open},
	{"quit",   "\t\tquit this console", quit}
	};


int pipe_a;
int pipe_b;


char *gpl_message = "TCP Simulator  Copyright (C) 2010  Leonardo Korndorfer\n"
"This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n"
"This is free software, and you are welcome to redistribute it\n"
"under certain conditions; type `show c' for details.\n";


#endif //__CONSOLE_H__
