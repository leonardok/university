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

#ifndef __TCP_H__
#define __TCP_H__

#include <stdint.h>

/* 
 * this is the maximun TCP packet size. considering a maximun of 60 bytes for
 * the header we have then 60 bytes for data. considering 20 bytes of header
 * (minimun size) we have then 100 bytes for data.
 */
#define MAX_TCP_PACKET_SIZE_IN_BYTES   120
#define DEFAULT_TCP_DATA_SIZE_IN_BYTES  40
#define DEFAULT_WINDOW_SIZE              4
#define PACKET_TTL                       5

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
} tcp_packet_type;

enum
{
	MASK_CWR = 0x1,
	MASK_ECE = 0x01,
	MASK_URG = 0x001,
	MASK_ACK = 0x0001,
	MASK_PSH = 0x00001,
	MASK_RST = 0x000001,
	MASK_SYN = 0x0000001,
	MASK_FIN = 0x00000001
} tcp_masks;

enum
{
	STATE_LISTENING, STATE_SYN_SENT, STATE_SYN_RECEIVED, STATE_ESTABLISHED, 
	STATE_FIN_WAIT_1, STATE_FIN_WAIT_2, STATE_CLOSE_WAIT, STATE_CLOSING, 
	STATE_LAST_ACK, STATE_TIME_WAIT, STATE_CLOSED
} tcp_machine_states;


/* TCP structure */
typedef struct tcp_packet_s tcp_packet_t;
struct tcp_packet_s
{
	/* this first piece of the packet has 5 words of 32 bits. 160b -> 20 bytes */
	int16_t pkt_source_port;
	int16_t pkt_destination_port;
	int32_t pkt_sequence_number;
	int32_t pkt_ack_number;
	int8_t  pkt_data_offset: 4;
	int8_t  pkt_reserved:    4;
	int8_t  pkt_flag_bits;
	int16_t pkt_window_size;
	int16_t pkt_checksum;
	int16_t pkt_urgent_poiter;
	
	/* data segment plus options can go up to 40 bytes */
	int32_t *pkt_options;
	int32_t *pkt_data;
};

int window_size;

enum 
{
	NOT_SENT, WAITING_CONFIRMATION, SENT
};

/* 
 * this is the stream structure. it holds the following fields:
 *   tcp_packet: this is the packet
 *   status:     tells us how is the packet. enum TCP_PACKET_STATUS
 */
typedef struct packet_stream_s packet_stream_t;
struct packet_stream_s
{
	tcp_packet_t tcp_packet;
	int          status;
	int          time_to_live;
	
	packet_stream_t *next_packet;
};

packet_stream_t packets_stream;

/* this variables will hold the window pointers */
packet_stream_t *window_start, *window_end, *last_pkt;



#endif //__TCP_H__
