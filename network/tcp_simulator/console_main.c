/* TCP Simulator - This program simulates a TCP communication between two hosts
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
#include "console.h"
#include "util.h"

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



int main(void)
{
	int i;
	char command[256];

	printf("%s\n", gpl_message);
	printf("Hi! I'am the TCP console. Type commands in me.\n");
	printf("type \"> help\" to see availiable commands.i\n\n");
	while (TRUE)
	{
		printf("> ");
		scanf("%s", &command);

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
