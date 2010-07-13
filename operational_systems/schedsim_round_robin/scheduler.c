/*
 *  scheduler.c
 *  schedsim_round_robin
 *
 *  Created by Leonardo Korndorfer on 6/20/10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include "task.h"
#include "queues.h"

extern queue_t *ready_queue;
extern queue_t *waiting_queue;

task_t * schedule(void) {
	return remove_first_task_from_queue(&ready_queue);
}


void increase_sleep_time(void){
	queue_t *queue_ptr = waiting_queue;
	while (queue_ptr) {
		queue_ptr->task->sleep_time++;
		queue_ptr = queue_ptr->next;
	}
	
}


void increase_wait_time(void){
	queue_t *queue_ptr = ready_queue;
	while (queue_ptr) {
		queue_ptr->task->waiting_time++;
		queue_ptr = queue_ptr->next;
	}
	
}