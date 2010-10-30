/******************************************************************************/
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
		exit(0);
	}
}

int open_pipe(char *pipe_name, int mode) 
{
	int pipe = 0;
	printf("open pipe\n");
	fopen(pipe_name, "w");
	
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
void get_work(int fp, char *buf)
{
	read(fp, buf, sizeof(buf));
	printf("%s", buf);
}