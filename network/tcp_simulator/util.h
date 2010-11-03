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

#ifndef __UTIL_H__
#define __UTIL_H__

#define TRUE  1
#define FALSE 0

enum 
{
	HOST_A,	HOST_B
};

#define HOST_A_PIPE "host_a.pipe"
#define HOST_B_PIPE "host_b.pipe"

#ifdef DEF_HOST_A
#define HOST      HOST_A
#define PIPE_NAME HOST_A_PIPE

#else
#define HOST      HOST_B
#define PIPE_NAME HOST_B_PIPE
#endif

#define PORT       5555
#define PORT_ASCII "5555"
#define SERVERHOST "localhost"


/*
 * this enum is the commands that can be send to the host.
 * CMD_LSTN - this is the server mode.
 * CMD_CNCT - client mode. will connect to a listen()ing server
 *
 */
enum
{
	CMD_LISTEN,
	CMD_CONNECT,
	CMD_CLOSE,
	CMD_SEND_PKT,
	CMD_SND_SYN
} command_types;

#endif //__UTIL_H__
