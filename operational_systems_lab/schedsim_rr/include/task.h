/*
 *  task.h
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 4/22/10.
 *  Copyright 2010. All rights reserved.
 *
 */

struct instructions_s {
	char *command;
	int  argument;
};

typedef struct instructions_s instructions_t;


struct task_s {
	int priority;
	int time_to_come;
	int state;
	
	instructions_t intructions;
};
typedef struct task_s task_t;