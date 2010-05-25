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
#include "task_queues.h"

using namespace std;

void usage(void){
	printf("USAGE:\n");
	printf("\tcommand -ts [0-10] -tsk file1 [file2 .. filen] \n");
	
	exit(1);
}

int main (int argc, char * const argv[]) {
	/* local variables definition */
	
	int i;                             // generic counters
	task_class tasks[MAX_PROCESSES];   // tasks list
	
	                                   // TODO: declare wainting queue
					   // TODO: declare ready queue
					   // TODO: declare finish queue
					   // TODO: declare executing queue

	
	/* TODO: check if arguments passed by command-line are ok. If not,
	         show usage */
	/* TODO: if arguments ok load the instructions inside tasks */
		
	/* 
	 * verify if the files passed are readble, and create the tasks
	 */
	for (i=0; ; i++) {}
	
		
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