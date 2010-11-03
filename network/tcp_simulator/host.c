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

#include "tcp.h"
#include "host.h"
#include "util.h"
#include "pipe.h"
#include "socket.h"

extern unsigned int host_state;

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
	
	while (!tcp_packet || !(tcp_packet->flag_bits & MASK_SYN))
		receive_tcp_packet_from_other(&tcp_packet);
	
	send_tcp_packet_from_other(MASK_SYN | MASK_ACK);
	
	while (!tcp_packet || !(tcp_packet->flag_bits & MASK_ACK))
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
	while (!tcp_packet || !(tcp_packet->flag_bits & (MASK_SYN | MASK_ACK)))
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
	
	return TRUE;
}


/*
 * this thread will watch for stuff to do, that come from the get work routi 
 */
void host_thread(void)
{
	
}


void cmd_send_stuff(char *buf)
{
	printf("Will send the string over the interwebs.\n");
	printf("%s\n", buf);
}


int main(void)
{
	int cmd;
	
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
		send_message_to_other("Hello Client!");
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
				
				/* get message to send over */
				int  read_size;
				char buf[MAX_PIPE_DATA_SIZE];
				
				while ((read_size = pipe_read(pipe, buf)) < 1);
								
				cmd_send_stuff(buf);
				
				break;

			case CMD_CLOSE:
				break;

			/* ACK packet */
		}
			 
	}

}
