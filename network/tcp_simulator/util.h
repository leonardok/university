#ifndef __UTIL_H__
#define __UTIL_H__

#define TRUE  1
#define FALSE 0

enum
{
	CMD_OPEN,
	CMD_CLOSE,
	CMD_SEND_ACK,
	CMD_SEND_SYN
} command_types;

#endif //__UTIL_H__
