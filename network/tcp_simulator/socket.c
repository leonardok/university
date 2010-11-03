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

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "util.h"
#include "socket.h"
#include "tcp.h"

extern int sfd_other_host;
extern unsigned char host_src_port;
extern unsigned char host_dst_port;
extern unsigned int  host_seq_number;
extern unsigned int  host_state;

void debug_addrinfo(struct addrinfo *res)
{
	struct addrinfo *p;
	for(p = res;p != NULL; p = p->ai_next) {
		char ipstr[INET6_ADDRSTRLEN];
		void *addr;
		char *ipver;
		
		/* IPv4 */
		if (p->ai_family == AF_INET) 
		{			
			struct sockaddr_in *ipv4 = 
				(struct sockaddr_in *)p->ai_addr; 
			
			addr = &(ipv4->sin_addr); 
			ipver = "IPv4";
		}
		/* IPv6 */
		else 
		{			
			struct sockaddr_in6 *ipv6 = 
				(struct sockaddr_in6 *)p->ai_addr; 
			
			addr = &(ipv6->sin6_addr); 
			ipver = "IPv6";
		}
		
		inet_ntop(res->ai_family, addr, ipstr, sizeof ipstr);
		printf("Host %s: %s.\n", ipver, ipstr);
	}
	
}


void build_tcp_packet(tcp_packet_t *tcp_packet, int src_port, int dst_port,
		      int ack_number, int flags, int window_size, void *data,
		      int data_size)
{
	tcp_packet = malloc(sizeof(tcp_packet_t) + (sizeof(char) * data_size));
	
	host_seq_number++;
	
	tcp_packet->source_port      = src_port;
	tcp_packet->destination_port = dst_port;
	tcp_packet->sequence_number  = host_seq_number;
	tcp_packet->ack_number       = ack_number;
	tcp_packet->data_offset      = 5;
	tcp_packet->reserved         = 0;
	tcp_packet->flag_bits        = flags;
	tcp_packet->window_size      = window_size;
	//tcp_packet->checksum         ;
	tcp_packet->urgent_poiter    = 0;
}


/*
 * this function will be executed in a thread waiting for new messages to come.
 */
int receive_tcp_packet_from_other(tcp_packet_t **tcp_packet)
{
	int  numbytes;
	char buf[256];
	
	while ((numbytes = recv(sfd_other_host, (void*) buf, MAXDATASIZE-1, 0)) > 0)
	{
		*tcp_packet = malloc(numbytes);
		*tcp_packet = (tcp_packet_t *)buf;
		break;
	}
	
	return TRUE;
}

int send_tcp_packet_from_other(int flags)
{
	int  bytes_sent;
	tcp_packet_t *tcp_packet;
	
	tcp_packet = malloc(sizeof(tcp_packet_t));
	tcp_packet->flag_bits = flags;
	
	if ((bytes_sent = send(sfd_other_host, (void*) tcp_packet, MAXDATASIZE-1, 0)) < 1)
	{
		perror("get_message_from_other");
		return FALSE;
	}

	return bytes_sent;
}


int get_message_from_other(void)
{
	int numbytes;
	char buf[MAXDATASIZE];
	
	if ((numbytes = recv(sfd_other_host, buf, MAXDATASIZE-1, 0)) == -1) 
	{ 
		perror("get_message_from_other");
		exit(1);
	} 
	
	buf[numbytes] = '\0';
	printf("client: received '%s'\n",buf);
	
	return TRUE;
}


int send_message_to_other(char *message)
{
	if (send(sfd_other_host, message, strlen(message), 0) == -1)
		perror("send_message_to_other");
	
	return TRUE;
}



void export_addrinfo_usable_values(struct addrinfo *res)
{
	struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
	host_dst_port = ipv4->sin_port;
	
	printf("Connection Details: src port: %d\n", host_dst_port);
}



/* 
 * this function will be handled by the host_a. in this simulation the low
 * level network stuff is abstracted from the simulation.
 */
int open_socket(void)
{
	int sfd, new_fd;
	int status;
	int backlog = 2;
	socklen_t addr_size;
	struct addrinfo hints, *res;
	struct sockaddr_storage their_addr;

	memset(&hints, 0, sizeof hints); 
	
	hints.ai_family   = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags    = AI_PASSIVE;

	status = getaddrinfo("localhost", PORT_ASCII, &hints, &res);
	if (status != 0) 
	{ 
		fprintf(stderr, "getaddrinfo Error: %s\n", gai_strerror(status)); 
		exit(1);
	}
	
	export_addrinfo_usable_values(res);
	
	/* get the socket file descriptor so we can use it later */
	sfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sfd < 0)
	{
		printf("Could not Open Socket: %s\n", strerror(errno));
		return FALSE;
	}
	
	debug_addrinfo(res);
	
	/* bind it */
	if (bind(sfd, res->ai_addr, res->ai_addrlen) == -1)
	{
		printf("Could not Bind Socket: %s\n", strerror(errno));
		return FALSE;
	}
	
	if (listen(sfd, backlog) < 0)
	{
		printf("Error Trying to Listen: %s\n", strerror(errno));
		return FALSE;
	}
	
	printf("Socket OK. Accepting Connections.\n");
	
	addr_size = sizeof(their_addr);
	new_fd = accept(sfd, (struct sockaddr *)&their_addr, &addr_size);
	if (new_fd < 0)
	{
		printf("Error on Accept: %s\n", strerror(errno));
		return FALSE;
	}
	
	/* store the new_fd to make it availiable on future communications */
	sfd_other_host = new_fd;
	
	printf("Accepted a New Connection.\n");
	
	return TRUE;
}


/*
 * this function will open the socket with the host_a
 */
int open_connection(void)
{
	int sfd;
	int status;
	struct addrinfo hints;
	struct addrinfo *res;
	
	/* Create the socket.   */
	sfd = socket (PF_INET, SOCK_STREAM, 0);
	if (sfd < 0)
	{
		perror ("socket (client)");
		return FALSE;
	}
	
	/* Connect to the server.   */

	
	memset(&hints, 0, sizeof hints);
	
	/* 
	 * family of the IP we want. AF_INET for IPv4, AF_INET6 for IPv6 and
	 * AF_UNSPEC if you dont care.
	 */
	hints.ai_family   = AF_INET;
	
	/*
	 * TCP stream sockets
	 */
	hints.ai_socktype = SOCK_STREAM;
	
	/*
	 * tells getaddrinfo() to assign the address of my local host to the 
	 * socket structures.
	 */
	//hints.ai_flags    = AI_PASSIVE;
	
	status = getaddrinfo(NULL, PORT_ASCII, &hints, &res);
	if (status != 0) 
	{ 
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status)); 
		exit(1);
	}
	
	debug_addrinfo(res);

	
	if (connect(sfd, res->ai_addr, res->ai_addrlen) != 0)
	{
		perror ("connect (client)");
		return FALSE;
	}
	
	sfd_other_host = sfd;
	
	printf("Connection With Host A Openned.\n");
	return TRUE;
}









