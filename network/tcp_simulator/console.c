/* TCP Simulator - Simulates TCP transactions
 * Copyright (C) 2010  Leonardo Richter Korndorfer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include "console.h"
#include "util.h"
#include "pipe.h"

extern cmd_t commands[COMMAND_NUM];

void show_help(void)
{
	printf("\nHELP\n");
	printf("Availiable Commands:\n");

	int i;
	for (i = 0; i< COMMAND_NUM; i++)
	{
		printf("\t%s\t%s\n", commands[i].cmd, commands[i].description);
	}
	printf("\n");
}


void quit(void)
{
	exit(0);
}

void sim_close_all(void)
{
	printf("sending CMD_CLOSE to Host A\n");
	char cmd[10] = "CMD_CLOSE";
	pipe_write(pipe_a, cmd);
	
	printf("sending CMD_CLOSE to Host B\n");
	pipe_write(pipe_b, cmd);
}


void sim_send_packet(void)
{
	printf("sending data over to host B\n");
	pipe_write(pipe_a, "CMD_SEND_PKT");
	
	char string_to_send[MAX_PIPE_DATA_SIZE];
	printf("Please enter a string for me to send. (max of 512b)\n");
	scanf("%s", string_to_send);
	pipe_write(pipe_a, string_to_send);
}


void sim_open_connection(void)
{
	printf("sending CMD_LISTEN to Host A\n");
	
	char cmd[12] = "CMD_LISTEN";
	pipe_write(pipe_a, cmd);
	
	
	printf("sending CMD_CONNECT to Host B\n");
	
	strcpy(cmd, "CMD_CONNECT");
	pipe_write(pipe_b, cmd);
}


int main(void)
{
	int i;
	char command[256];
	
	/* open pipes for sending commands */
	pipe_a = open_pipe(HOST_A_PIPE, O_WRONLY);
	pipe_b = open_pipe(HOST_B_PIPE, O_WRONLY);
	
	if ((pipe_a == -1) || (pipe_b == -1))
		exit(0);

	printf("%s\n", gpl_message);
	printf("Hi! I'am the TCP console. Type commands in me.\n");
	printf("type \"> help\" to see availiable commands.i\n\n");
	
	
	while (TRUE)
	{
		printf("> ");
		scanf("%s", command);

		for (i = 0; i < COMMAND_NUM; i++)
		{
			if (!strcmp(command, commands[i].cmd))
			{
				commands[i].action();
				break;
			}
		}
		
	}
}
