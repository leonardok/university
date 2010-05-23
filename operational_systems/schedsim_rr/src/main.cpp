#include <iostream>
#include "task_queues.h"
#include "task.h"

int main (int argc, char * const argv[]) {
	/* local variables definition */
	
	int i;                             /* generic counters */
	//scheduler_class scheduler;         /* scheduler object */
	
	
	
	/* 
	 * verify if the files passed are readble
	 */
	for (i=0; ; i++) {
		/* gather file name and create a new object to store it's attributes */
		
	}
	
	/* create task array. can create only MAX_PROCESSES simultaneous processes */
	task_class tasks[MAX_PROCESSES];
	
	
	/*
	 * create the proccess queues: waiting, ready, executing and finish
	 */
	
	/*
	 * at this point we start to schedule the processess
	 */
	while (true) {
		printf("we are scheduling!\n");
		
	}
	
    
    return 0;
}
