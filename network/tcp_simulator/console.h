/* TCP Simulator - Simulates TCP transactions
 * Copyright (C) 2010  Leonardo Richter Korndorfer 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
void sim_close_all(void);
void sim_send_packet(void);
void sim_open_connection(void);
void sim_set_window_size(void);
void sim_auto_test(void);

#define COMMAND_NUM 7
cmd_t commands[COMMAND_NUM] = {
	{"help",   "\t\tshow this help", show_help},
	{"window_size", "\tcheck and set window size", sim_set_window_size},
	{"open_connection", "\tsimulate a handshake", sim_open_connection},
	{"send_packet", "\t\tsend ack to other host", sim_send_packet},
	{"auto-test", "\t\trun auto-test", sim_auto_test},
	{"close",  "\t\tsend FIN to other host", sim_close_all},
	{"quit",   "\t\tquit this console", quit}
	};


int pipe_a;
int pipe_b;


char *gpl_message = "TCP Simulator  Copyright (C) 2010  Leonardo Korndorfer\n"
"This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n"
"This is free software, and you are welcome to redistribute it\n"
"under certain conditions; type `show c' for details.\n";


#endif //__CONSOLE_H__
