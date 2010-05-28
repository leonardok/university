/*
 *  main.cpp
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 5/15/10.
 *  Copyright 2010. All rights reserved.
 *
 *  this is the main file.
 *
 */


#include <iostream>
#include <unistd.h>

#include "scheduler.h"

#ifdef DEBUG
#include "log.h"
#endif

using namespace std;


void usage(void){
	printf("USAGE:\n");
	printf("\tcommand -q [0-10] -t file_1 [-t file_2 .. -t file_n] \n");
	
	return;
}

int main (int argc, char * const argv[]) {
	/* local variables definition */
	//int i;                             // generic counters
	task_class tasks[MAX_PROCESSES];   // tasks list
	int        tasks_counter;
	
	scheduler_class scheduler;
	                                   // TODO: declare wainting queue
					   // TODO: declare ready queue
					   // TODO: declare finish queue
					   // TODO: declare executing queue
	
	/* 
	 * check if arguments passed by command-line are ok. If not, show usage 
	 */
	printf("parsing arguments...\n");
	if (argc < 3) {
		usage();
	}
	else {
		int c;

		while ((c = getopt(argc, argv, ":q:t:")) != -1) {
			switch (c) {
				case 'q':
					scheduler.set_time_quantum(atoi(optarg));
					break;
				case 't':
					printf("\tcreate new task from file %s\n", optarg);
					tasks[tasks_counter].load_instructions(optarg);
					tasks_counter++;
					break;

				case '?':
				default:
					usage();
					break;
			}
		}
	}
	printf("\n");
		
	printf("we are scheduling!\n");
	
	while (true) {
		/* keep looping on scheduling */
		
		/* TODO: schedule among living tasks */
		/* TODO: if no task is there, busy wait */
		/* TODO: give CPU to selected task. start thread */
		/* TODO: change task state */
		/* TODO: sleep 1/(time quantum) to wait for process CPU time
		         to wait or process finishes. decrease the wait time
		         of tasks on the wait queue. If any task is OK to execute
		         move it to ready */
		/* TODO: store last tash PID */
		/* TODO: change last task state and put the descriptor in some
		         queue */

		
		/* process finished or time slice ended. new scheduling */
	}
	
    
    return 0;
}











/*EOF*/