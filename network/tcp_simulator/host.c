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
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "tcp.h"
#include "host.h"
#include "util.h"
#include "pipe.h"
#include "socket.h"

extern unsigned int host_state;
extern int          window_size;

/*
 * we need to show the packets that come to our network "stack"
 */
void dump_packets(void)
{
	
}


void cmd_listen(void)
{
	tcp_packet_t *tcp_packet = NULL;
	
	host_state = STATE_LISTENING;
	printf("You can now connect to the other host with the \"connect()\" call.\n");
	
	while (!tcp_packet || !(tcp_packet->pkt_flag_bits & MASK_SYN))
		receive_tcp_packet_from_other(&tcp_packet);
	
	send_tcp_packet_from_other(MASK_SYN | MASK_ACK);
	
	while (!tcp_packet || !(tcp_packet->pkt_flag_bits & MASK_ACK))
		receive_tcp_packet_from_other(&tcp_packet);
	
	printf("STATE_ESTABLISHED\n");
	host_state = STATE_ESTABLISHED;
}


/*
 * to connect to other host we will send a SYN to other host and change our 
 * state to STATE_SYN_SENT. we then wait for a SYN+ACK and thus send an ACK.
 */
void cmd_connect(void)
{
	tcp_packet_t *tcp_packet;
	printf("Connecting to the other host.\n");
	
	/* send SYN */
	send_tcp_packet_from_other(MASK_SYN);
	printf("state: STATE_SYN_SENT\n");
	
	/* 
	 * receive SYN+ACK. if did not receive with righ flags, keep trying. 
	 * TODO: time out here. we can give it to a thread, if not finished at
	 * given timeout, kill it and send SYN again.
	 */
	while (!tcp_packet || !(tcp_packet->pkt_flag_bits & (MASK_SYN | MASK_ACK)))
		receive_tcp_packet_from_other(&tcp_packet);
	printf("state: STATE_SYN_RECEIVED\n");
	
	/* send ACK */
	send_tcp_packet_from_other(MASK_ACK);
	
	printf("state: STATE_ESTABLISHED\n");
	host_state = STATE_ESTABLISHED;
}


int get_work(int fp)
{
	int read_size;
	char buf[128];
	
	while ((read_size = pipe_read(fp, buf)) < 1);
	
	buf[read_size] = 0;
	printf("Buff Read %d bytes: %s\n", read_size, buf);
	
	if (!strncmp(buf, "CMD_LISTEN", read_size))
		return CMD_LISTEN;
	
	if (!strncmp(buf, "CMD_CONNECT", read_size))
		return CMD_CONNECT;
	
	if (!strncmp(buf, "CMD_SEND_PKT", read_size))
		return CMD_SEND_PKT;
	
	if (strstr(buf, "CMD_CHNG_WINDOW_SIZE") != NULL)
	{
		/* return the first char after the '=' token */
		char *new_window_sz_str = (strstr(buf, "="));
		window_size = atoi(++new_window_sz_str);
		
		return CMD_CHNG_WINDOW_SIZE;
	}
		
	
	return -1;
}

void build_tcp_packet(tcp_packet_t *tcp_packet, int src_port, int dst_port,
		      int ack_number, int flags, int window_size, int seq_number, 
		      void *data, int data_size, char *options)
{
	tcp_packet = malloc(sizeof(tcp_packet_t) + (sizeof(char) * data_size));
		
	tcp_packet->pkt_source_port      = src_port;
	tcp_packet->pkt_destination_port = dst_port;
	tcp_packet->pkt_sequence_number  = seq_number;
	tcp_packet->pkt_ack_number       = ack_number;
	
	tcp_packet->pkt_reserved         = 0;
	tcp_packet->pkt_flag_bits        = flags;
	tcp_packet->pkt_window_size      = window_size;
		//tcp_packet->pkt_checksum         ;
	tcp_packet->pkt_urgent_poiter    = 0;
	
	if (options == NULL)
		tcp_packet->pkt_data_offset = 0;
	else 
		tcp_packet->pkt_data_offset = (sizeof(options) / 32);
	
	tcp_packet->pkt_data = malloc(data_size);
	tcp_packet->pkt_data = data;
	
}


/* put packets into packets_stream */
void *break_message_into_packets(void)
{
	printf("starting break_message_into_packets \n");
	
	int i;
	int data_size;
	packet_stream_t *packet     = NULL;
	packet_stream_t *new_packet = NULL;
	
	char *message_ptr = message_to_send;
	
	/* message size in bytes */
	int message_size  = strlen(message_to_send) * sizeof(char);
	
	printf("message to send is %s with size %d\n", message_ptr, message_size);

	
	/* this assumes we are NOT sending options over */
	int num_of_pieces = message_size % DEFAULT_TCP_DATA_SIZE_IN_BYTES;
	
	printf("splitting into %d pieces\n", num_of_pieces);
	
	/* split pieces into array of tcp packets */
	for (i = 0; i <= num_of_pieces; i++) 
	{
		printf("building packet %d\n", i);

		/* 
		 * if we are going with only one message, it probably doesnt have
		 * more than 40 bytes, so dont need to allocate all space 
		 */
		data_size = message_size;
		
		if (num_of_pieces > 0)
			data_size = 40;
		
		
		/* first packet is static allocated */
		if (i == 0)
		{
			packet = &packets_stream;
		}
		/* allocate new packet */
		else
		{
			/*  */
			new_packet = malloc(sizeof(tcp_packet_t) + data_size);
			packet->next_packet = new_packet;
			
			/* now point "new packet" by "packet" to continue */
			packet = new_packet;
		}
		
		
		char *data = malloc(data_size);
		memcpy(data, message_ptr, data_size);
				
		/* TODO: use build_tcp_packet here */
		build_tcp_packet(&(packet->tcp_packet),
				 host_src_port, 
				 host_dst_port,
				 0,                // ack number
				 0,                // flags 
				 window_size,      // window size
				 host_seq_number,  // host sequence number
				 (void *) data,    // data
				 data_size,        // data_size
				 NULL              // options
				 );
		
		host_seq_number++;
		
		/* point to the first of next message segment */
		message_ptr += data_size;
		
		packet->status      = NOT_SENT;
		packet->next_packet = NULL;		
	}
	
	printf("ended break_message_into_packets\n");
	
	return NULL;
}

/* this function sets the window pointers to the packets */
void initialize_tcp_window(void)
{
	printf("start initialize_tcp_window\n");
	int i;
	packet_stream_t *packet_ptr = &packets_stream;
	
	printf("debug 1\n");

	window_start = packet_ptr;
	for (i = 0; ((i < window_size) && (packet_ptr->next_packet != NULL)); i++) 
	{
		printf("debug 2\n");

		packet_ptr = packet_ptr->next_packet;
	}
	
	printf("debug 3\n");

	window_end = packet_ptr;
	
	printf("ended initialize_tcp_window\n");
}


/*
 * this thread will send stuff to the other host
 */
void send_stuff_thread(void)
{
	packet_stream_t *packet_ptr;
	
	/* 
	 * this thread never sleeps. send the message to other host
	 * whenever there is stuff to send.
	 */
	while (TRUE) 
	{
		sleep(5);
		if (message_to_send != NULL)
		{
			printf("message found, breaking message into pieces\n");
			break_message_into_packets();
			initialize_tcp_window();
			
			
			while (last_pkt->status != SENT)
			{
				sleep(1);
				packet_ptr = window_start;
				
				while (packet_ptr != window_end) 
				{
					if ((packet_ptr->status == NOT_SENT) || 
					    ((packet_ptr->status != SENT) && (packet_ptr->time_to_live >= PACKET_TTL)))						
					    
					{
						printf("sending tcp packet with seq. %d\n", packet_ptr->tcp_packet.pkt_sequence_number);
						send_tcp_packet(&packet_ptr->tcp_packet);
					}
					
					/* slide window */
					if (packet_ptr->status == SENT)
					{
						window_end   = window_end->next_packet;
						window_start = window_start->next_packet;
					}						
				}
			}
		}
	}
	
}


void cmd_send_stuff(char *buf)
{
	printf("Will send the string over the interwebs.\n");
	printf("%s\n", buf);
}


int main(void)
{
	int cmd;
	
	/* initialize window size to defult */
	window_size = DEFAULT_WINDOW_SIZE;
	
	message_to_send = NULL;
	
	/*pthread_t pthread_id[2];
	pthread_attr_t attr;*/
	
	/* 
	 * start named pipe, this is where the host will receive user commands.
	 * it will be a producer/consumer design. pipe name should be passed as
	 * command-line argument
	 */
	create_pipe(PIPE_NAME);
	int pipe = open_pipe(PIPE_NAME, O_RDONLY);

	
	/*
	 * open a socket to do the communication. packet transaction will be 
	 * simulated above a normal connection.
	 */
	if (HOST == HOST_A)
	{
		open_socket();
		send_message_to_other("Hello Client! You can start your simulation.");
		get_message_from_other();
		printf("\n\n\n");
	}
	else 
	{
		open_connection();
		get_message_from_other();
		send_message_to_other("Hi Server.");
		printf("\n\n\n");
	}


	/*
	 * once connection is stablished we can start the SIM STATE MACHINE.
	 * our state machine will start in CLOSED 
	 */
	host_state = STATE_CLOSED;
	
	host_seq_number = rand();
	
	/*
	 * at this point we need to start our threads that will exchange 
	 * messages with the other host.
	 */
	
	/* thread to construct packets */
	pthread_t pthread_id[10];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_create(&pthread_id[0], 
		       &attr, 
		       (void *) &send_stuff_thread,
		       (void *) NULL);
	/*
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	pthread_create(&pthread_id[0], &attr, 
		       (void *)&receive_tcp_packet_from_other, NULL);
	*/
	

	/* loop until gets work to do */
	while (TRUE)
	{
		/* 
		 * get work from console. this is the link we have with the
		 * outside world (client)
		 */
		fflush(stdout);
		cmd = get_work(pipe);

		int  read_size;
		char buf[MAX_PIPE_DATA_SIZE];
		
		switch (cmd)
		{
			case CMD_LISTEN:
				printf("got CMD_LISTEN\n");
				cmd_listen();
				break;

			case CMD_CONNECT:
				printf("got CMD_CONNECT\n");
				cmd_connect();
				break;
				
			case CMD_SEND_PKT:
				printf("got CMD_SEND_PKT\n");
				
				sleep(1);
				
				/* get message to send over */
				while ((read_size = pipe_read(pipe, buf)) < 1);
								
				message_to_send = malloc(read_size * sizeof(char));
				strncpy(buf, message_to_send, read_size);
				
				break;
				
			case CMD_CHNG_WINDOW_SIZE:				
				printf("changed window size to %d\n", window_size);
				
				break;

			case CMD_CLOSE:
				break;

			/* ACK packet */
				
			default:
				printf("did not recognize cmd!\n");
		}
			 
	}

}
