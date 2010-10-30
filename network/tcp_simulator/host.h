#ifndef __HOST_H__
#define __HOST_H__


enum
{
	LISTEN, SYN_SENT, SYN_RECEIVED, ESTABLISHED, FIN_WAIT_1,
	FIN_WAIT_2, CLOSE_WAIT, CLOSING, LAST_ACK, TIME_WAIT, CLOSED
} tcp_machine_states;

enum
{
	TO_REXMT, TO_TIME_WAIT, TO_USER_TIME
} time_out_events;



int pipe_descriptor;



#endif //__HOST_H__
