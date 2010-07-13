/*
 *  task.h
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 4/22/10.
 *  Copyright 2010. All rights reserved.
 *
 */

#ifndef __TASK_HEADER__
#define __TASK_HEADER__

#define MAX_SIZE_BUF 512


enum TASK_STATE {
	TASK_STATE_TO_COME  = 0,
	TASK_STATE_READY    = 1,
	TASK_STATE_WAINTING = 2,
	TASK_STATE_FINISHED = 3,
	TASK_STATE_EXECUTING= 4
};

enum INSTRUCTION_TYPE {
	TASK_NO_INSTRUCTION,
	TASK_INSTRUCTION_EXECUTE,
	TASK_INSTRUCTION_WAIT,
	TASK_INSTRUCTION_FINISH
};

typedef struct _instruction instruction_t;
struct _instruction {
	int duration;
	int instruction_type;
	
	instruction_t *next;
};

typedef struct _task task_t;
struct _task {
	int priority;
	int state;
	int task_number;
	int time_to_come;
	int process_time;
	int waiting_time;
	int sleep_time;
	
	instruction_t *instruction;
	instruction_t *curr_instruction;
	
	task_t *next;
};

typedef struct _queue queue_t;
struct _queue {
	task_t *task;
	queue_t *previous;
	queue_t *next;
};



/* function definitions */
int create_task(char *);
int get_argument(int, int);
int add_instruction(task_t **, int, int);
void show_process_status_header(void);
void show_sleeping_time(void);
void show_waiting_time(void);
void show_proccess_time(void);
void show_process_status(void);

#endif __TASK_HEADER__