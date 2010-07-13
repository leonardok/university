/*
 *  task.h
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 4/22/10.
 *  Copyright 2010. All rights reserved.
 *
 */

#ifndef __QUEUES_HEADER__
#define __QUEUES_HEADER__

task_t* remove_first_task_from_queue (queue_t **);
void get_tasks_on_queue(task_t *, queue_t **, int);
void queue_add_task(task_t *, queue_t **);
void get_ready_tasks(task_t **, queue_t **);
void get_have_to_come_tasks(void);
void decrease_duration_of_waiting_process(void);
void get_finished_tasks (void);


#endif __QUEUES_HEADER__