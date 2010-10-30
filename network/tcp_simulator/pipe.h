#ifndef __PIPE_H__
#define __PIPE_H__


#define HOST_A_PIPE "host_a.pipe"
#define HOST_B_PIPE "host_b.pipe"

#ifdef HOST_A
#define PIPE_NAME HOST_A_PIPE
#else
#define PIPE_NAME HOST_B_PIPE
#endif


void create_pipe(char *pathname);
int  open_pipe(char *, int);
void close_pipe(int fp);
void get_work(int fp, char *buf);


#endif //__PIPE_H__