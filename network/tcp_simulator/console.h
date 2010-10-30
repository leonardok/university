#ifndef __CONSOLE_H__
#define __CONSOLE_H__

char *gpl_message = "TCP Simulator  Copyright (C) 2010  Leonardo Korndorfer\n"
    "This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n"
    "This is free software, and you are welcome to redistribute it\n"
    "under certain conditions; type `show c' for details.\n";

typedef struct cmd_s cmd_t;
struct cmd_s
{
	char *cmd;
	char *description;
	void (*action)(void);
};

void show_help(void);

#define COMMAND_NUM 6
cmd_t commands[COMMAND_NUM] = {
	{"help",   "show this help", show_help},
	{"open",   "send SYN to other host", NULL},
	{"sndack", "send ack to other host", NULL},
	{"sndpkg", "send package to other host", NULL},
	{"close",  "send FIN to other host", NULL},
	{"quit",   "quit this console", NULL}
	};

#endif //__CONSOLE_H__
