#ifndef __HOST_H__
#define __HOST_H__


struct

enum
{
	LISTEN, SYN_SENT, SYN_RECEIVED, ESTABLISHED, FIN_WAIT_1,
	FIN_WAIT_2, CLOSE_WAIT, CLOSING, LAST_ACK, TIME_WAIT, CLOSED
} tcp_machine_states;

enum
{
	REXMT, TIME_WAIT, USER_TIME
} time_out_events;


#endif //__HOST_H__
