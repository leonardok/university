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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <fcntl.h>

#include <sys/stat.h>
#include <errno.h>

#include "pipe.h"
#include "util.h"

void create_pipe(char *pathname)
{
	if (mkfifo(pathname, 0666) != 0)
	{
		printf("Could Not Create Fifo: %s\n", strerror(errno));
		
		if (errno != EEXIST)
			exit(0);
	}
	
	return;
}

int open_pipe(char *pipe_name, int mode) 
{	
	/* 
	 * pipes are open with O_NONBLOCK because if not, the open call will
	 * wait until the other end is openned. if we call an open(read)
	 * the open call would wait until an open(write) is made.
	 */
	int pipe = open(pipe_name, (mode|O_NONBLOCK));
	
	if(pipe == -1) {
		printf("Could Not Open Fifo: %s\n", strerror(errno));
	}	
	return pipe;
}

void close_pipe(int fp)
{
	close(fp);
	return;
}


/*
 * do our consummer role. when we receive work, dump it to the console then we
 * know what is going on.
 */
int pipe_read(int fp, char *buf)
{
	return read(fp, buf, MAX_PIPE_DATA_SIZE);	
}




void pipe_write(int fp, char *msg)
{
	int bytes_written;
	
	int  msg_size = strlen(msg);
	
	printf("Message Size: %d Bytes\n", msg_size);
	if ((bytes_written = write(fp, msg, msg_size) < 0))
	{
		printf("Could Not Write into Fifo: %s\n", strerror(errno));
	}

	return;
}






