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

#ifndef __PIPE_H__
#define __PIPE_H__


#define MAX_PIPE_DATA_SIZE 512

void create_pipe(char *pathname);
int  open_pipe(char *, int);
void close_pipe(int fp);
int pipe_read(int fp, char *buf);
void pipe_write(int fp, char *msg);


#endif //__PIPE_H__