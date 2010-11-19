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

#ifndef __HOST_H__
#define __HOST_H__

enum
{
	TO_REXMT, TO_TIME_WAIT, TO_USER_TIME
} time_out_events;

unsigned int  host_seq_number;
unsigned char host_src_port;
unsigned char host_dst_port;

unsigned int  host_state;

char *message_to_send = NULL;

#endif //__HOST_H__
