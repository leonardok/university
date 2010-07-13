/*
 *  queues.c
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 4/22/10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include <stdlib.h>

#include "task.h"
#include "queues.h"
#include "log.h"

extern int     jiffies;
extern queue_t *ready_queue;
extern queue_t *waiting_queue;
extern queue_t *to_come;


#define INDENT_LEVEL 2

extern int jiffies;

task_t* remove_first_task_from_queue (queue_t **queue) {
	queue_t *task_ptr        = *queue;
	
	if (task_ptr) {
		*queue = task_ptr->next;
		return task_ptr->task;
	}
	
	return NULL;
	
}

void queue_add_task(task_t *task, queue_t **queue){
	queue_t *queue_ptr        = NULL;
	queue_t *queue_parent_ptr = *queue;
	
	if (!*queue) {
		queue_ptr = malloc(sizeof(queue_t));
		queue_ptr->task     = task;
		queue_ptr->previous = NULL;
		
		*queue = queue_ptr;
		return;
	}
	queue_ptr        = *queue;
	while (queue_ptr) {
		queue_parent_ptr = queue_ptr;
		queue_ptr        = queue_ptr->next;
	}
	queue_ptr = malloc(sizeof(queue_t));
	queue_ptr->task = task;
	
	if (queue_ptr->previous) {
		queue_ptr->previous = queue_parent_ptr;
	}
	
	queue_parent_ptr->next = queue_ptr;
	return;
}


void get_tasks_on_queue(task_t *task_list, queue_t **local_queue_ptr, int task_state){
	task_t *task_ptr = task_list;
	
	while (task_ptr) {
		if (task_ptr->state == task_state) {
			queue_add_task(task_ptr, local_queue_ptr);
		}
		task_ptr = task_ptr->next;
	}
	
	return;
}


void get_have_to_come_tasks(void){
	queue_t *task_ptr        = to_come;
	queue_t *task_parent_ptr = NULL;
	
	/* 
	** go through all tasks on the ready queue to see if any changed state to READY 
	** also we check the time_to_come <= jiffies to see if the task is here, so we 
	** check state to TASK_STATE_TO_COME anyway.
	*/
	while (task_ptr) {
		if ((task_ptr->task->state == TASK_STATE_TO_COME) && (task_ptr->task->time_to_come <= jiffies)) {
			task_ptr->task->state = TASK_STATE_READY;
			queue_add_task(task_ptr->task, &ready_queue);
			
			/* new we can remove this task from to_come queue */
			if (task_parent_ptr) {
				task_parent_ptr->next = task_ptr->next;
			}
			/* if get in the else is that is the first, so change head */
			else	to_come = task_ptr->next;

		}
		task_parent_ptr = task_ptr;
		task_ptr        = task_ptr->next;
	}
	return;
}


void get_finished_tasks (void){
	queue_t *task_ptr        = ready_queue;
	queue_t *task_parent_ptr = NULL;
	
	while (task_ptr) {
		if (task_ptr->task->state == TASK_STATE_FINISHED) {
			/* new we can remove this task from to_come queue */
			if (task_parent_ptr) {
				task_parent_ptr->next = task_ptr->next;
			}
			/* if get in the else is that is the first, so change head */
			else	to_come = task_ptr->next;
			
		}
		task_parent_ptr = task_ptr;
		task_ptr        = task_ptr->next;
	}
	return;
}



void decrease_duration_of_waiting_process (void) {
	queue_t *task_ptr      = waiting_queue;
	queue_t *task_last_ptr = NULL;
	while (task_ptr) {
		if (task_ptr->task->state == TASK_STATE_WAINTING) {
			task_ptr->task->curr_instruction->duration--;
			
			if (task_ptr->task->curr_instruction->duration <= 0) {
				if (task_last_ptr)
					task_last_ptr = task_ptr->next;
				else	waiting_queue = task_ptr->next;
				
				task_ptr->task->curr_instruction = task_ptr->task->curr_instruction->next;
				task_ptr->task->state = TASK_STATE_READY;
				queue_add_task(task_ptr->task, &ready_queue);
			}
		}
		task_last_ptr = task_ptr;
		task_ptr      = task_ptr->next;
	}
}






/*EOF*/
