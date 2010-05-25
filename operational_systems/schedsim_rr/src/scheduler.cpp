/*
 *  class_scheduler.cpp
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 4/22/10.
 *  Copyright 2010. All rights reserved.
 *
 */
//this is for you to know where 80 colums are ending
//123456789012345678901234567890123456789012345678901234567890123456789012345678


#include "scheduler.h"

/* 
 * SCHEDULE_CLASS - PRIVATE METHODS
 */

/*
 * schedule_class::task_to_ready
 *
 * overview:
 *   change state of the task pointed by arg 1 to "ready"
 *
 * input:
 *   1. task pointer
 *
 * output:
 *   true or false
 */
int schedule_class::task_to_ready(task_class *task){
	return 0;
}

/*
 * schedule_class::task_to_waiting
 *
 * overview:
 *   change state of the task pointed by arg 1 to "waiting"
 *
 * input:
 *   1. task pointer
 *
 * output:
 *   true or false
 */

int schedule_class::task_to_waiting(task_class *task){
	return 0;
}

/*
 * schedule_class::task_preempt
 *
 * overview:
 *   do the preemption of a task. this will happen when there is a running task
 *   that has ended its CPU time. in this case it need to save the remaining 
 *   processing time needed for that burst to finish it later.
 *
 *   i.e. a time quantum for the scheduler is 5 seconds and a task has 10 seconds
 *        of CPU burst. at the end of the time quantum the ::task_preempt method
 *        needs to save how many still need to be processed and saves it in the
 *        task attribute.
 *
 * input:
 *   1. task pointer
 *
 * output:
 *   true or false
 */
int schedule_class::task_preempt(task_class *task){
	return 0;
}

/*
 * schedule_class::task_state
 *
 * overview:
 *   get the task_state
 *
 * input:
 *   1. task which to discover the state
 *
 * output:
 *   task state based on the enum TASK_STATES.
 */
int schedule_class::task_state(task_class *task){
	return TASK_FINISH;
}


/* 
 * SCHEDULE_CLASS - PUBLIC METHODS
 */


/*
 * schedule_class::do_scheduling
 *
 * overview:
 *   does the scheduling. look up in the ready list who is elegible to get
 *   processor time. the winner proccess to get the CPU will be pointed by the
 *   second argument of the function.
 *
 *   the scheduling is based on priority and how old the proccess is.
 *
 * input:
 *   1. task ready list
 *   2. pointer to task object
 *
 * output:
 *   boolean value (true or false) corresponding the logical value of having
 *   successfully scheduled.
 */
int schedule_class::do_scheduling(task_queues_class ready_queue, task_class *task){
	return 0;
}

/*
 * schedule_class::create_task
 *
 * overview:
 *   creates a task, then it loads the commands (content of the file) into and 
 *   command list.
 *
 * input:
 *   1. file path
 *   2. task object
 *
 * output:
 *   boolean value (true or false) corresponding the logical value of having
 *   created or not the new task with the instructions inside the file.
 */
int schedule_class::create_task(char *file_path, 
				task_class *task){
	/* method variables */
	string line;
	char   c;
	
	/* get file contents */
	ifstream fp(file_path);	
	if(!fp.is_open()) return 1;
	
	/* if openned the file, can create new task */
	//task_class *new_task;
	
	while (!fp.eof()){
		fp.get(c);
	}
	
	fp.close();
	
	return 0;
}
























/* EOF */