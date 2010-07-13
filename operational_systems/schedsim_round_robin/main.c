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

/*
 * known issues
 *
 * 1. will crash if jiffies greater than int
 *
 */


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "task.h"
#include "queues.h"
#include "generic.h"
#include "scheduler.h"

/*
** global variables
*/
int jiffies = 0;

/* system queues */
queue_t *ready_queue;
queue_t *waiting_queue;
queue_t *finish_queue;
queue_t *to_come;

task_t *task_list;
task_t *task_list_head;


/* local functions prototypes */
void usage(void);

void usage(void){
	printf("USAGE:\n");
	printf("\tcommand -q [0-10] -t file_1 [-t file_2 .. -t file_n] \n");
	
	exit(-1);
}

int main (int argc, char * const argv[]) {
	ready_queue    = NULL;
	waiting_queue  = NULL;
	finish_queue   = NULL;
	to_come        = NULL;
	
	task_list      = NULL;
	task_list_head = NULL;
	/* 
	** local variables definition 
	*/
	
	/* 
	** task lists.
	** task_list has all system tasks
	** task_list_head is a pointer to the head
	*/
		
	
	/* other accessory variables */
	int task_counter = 0;
	int quantum      = 0;
	
	
	/* 
	 ** check if arguments passed by command-line are ok. If not, show usage 
	 */
	if (argc < 3) {
		usage();
		exit(-1);
	}
	
	/*
	 ** parse command line stuff
	 */
	int c;
	while ((c = getopt(argc, argv, ":q:t:")) != -1) {
		switch (c) {
			case 'q':
				/* set the round robin time slice */
				quantum = atoi(optarg);
				break;
				
			case 't':
				if(!create_task(optarg))
					exit(-1);
				
				task_counter++;
				break;
				
			case '?':
			default:
				usage();
				break;
		}
	}
	
	/*
	** build the yet_to_come queue. this is made of processes that are stalled because
	** they did not come ate this point. this will happen when time to come is greater
	** then 0
	*/
	get_tasks_on_queue(task_list, &to_come, TASK_STATE_TO_COME);
	
	/*
	** build the ready queue. this queue is made of processes that have come already
	*/
	get_tasks_on_queue(task_list, &ready_queue, TASK_STATE_READY);
	
	show_process_status_header();

	/*
	** at this point we have all processess that have come already are on the ready
	** queue. from now on we need to keep track only of processes that did not come
	** yet and on the process executing.
	*/
	task_t *current_task = NULL;
	int    time_slice    = quantum;
	while (TRUE) {
		/*
		** first thing on the loop is to check which tasks have time to come
		** equal or less than current jiffies, so we can promote those to ready queue
		** and wait next chance to get some CPU
		*/
		get_have_to_come_tasks();
				
		/* 
		** decrease duration of wait instructions and check if a task can be
		** promoted to ready queue
		*/
		decrease_duration_of_waiting_process();
		
		
		/* process finished or time slice ended. new scheduling */
		if (((!current_task || current_task->curr_instruction->duration <= 0) && 
		     ready_queue != NULL) || time_slice == 0) {
			int reschedule_flag = 0;
			/*
			** if curr instruction ended get next, there's a chance of next
			** been to execute some more
			*/
			if (current_task && current_task->curr_instruction->duration <= 0) {
				current_task->curr_instruction = current_task->curr_instruction->next;
				if (!current_task->curr_instruction) {
					queue_add_task(current_task, &finish_queue);
					current_task->state = TASK_STATE_FINISHED;
					get_finished_tasks();
					reschedule_flag = 1;
				}
				else if (current_task->curr_instruction->instruction_type == TASK_INSTRUCTION_WAIT) {
					queue_add_task(current_task, &waiting_queue);
					current_task->state = TASK_STATE_WAINTING;
					reschedule_flag = 1;
				}
				/*else if (current_task->curr_instruction->instruction_type == TASK_INSTRUCTION_FINISH) {
					queue_add_task(current_task, &finish_queue);
					current_task->state = TASK_STATE_FINISHED;
					get_finished_tasks();

					reschedule_flag = 1;
				}*/
			}
			
			/* 
			** if time slice ended is because it was executing, so we need to put 
			** it on execution line again. will be placed at the end of the queue
			*/
			if (time_slice <= 0 && !reschedule_flag) {
				queue_add_task(current_task, &ready_queue);
				reschedule_flag = 1;
			}
			
			if (reschedule_flag || !current_task) {
				current_task    = schedule();
				if (!current_task && !waiting_queue) {
					break;
				}
				current_task->state = TASK_STATE_EXECUTING;
				time_slice      = quantum;
				reschedule_flag = 0;
			}
		}
		
		/* fix new time stamps */
		if (current_task) {
			time_slice--;
			current_task->curr_instruction->duration--;
		}
		
		show_process_status();
		
		current_task->process_time++;
		increase_wait_time();
		increase_sleep_time();
		
		jiffies++;
		sleep(1);
	}
	
	show_proccess_time();
	show_waiting_time();
	show_sleeping_time();
	
	return 0;
}











/*EOF*/
