#ifndef __TCP_H__
#define __TCP_H__


#include <stdint.h>

enum
{
	CWR,
	ECE,
	URG,
	ACK,
	PSH,
	RST,
	SYN,
	FIN
} packet_type;

/* TCP structure */
typedef tcp_s tcp_t;
struct tcp_s
{
	int16_t source_port;
	int16_t destination_port;
	int32_t sequence_number;
	int32_t ack_number;
	int8_t  data_offset: 4;
	int8_t  reserved:    4;
	int8_t  flag_bits;
	int16_t window_size;
	int16_t checksum;
	int16_t urgent_poiter;
};


#endif //__TCP_H__
