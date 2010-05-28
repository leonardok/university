/*
 *  task.h
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 4/22/10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include <fstream>

using namespace std;

#define MAX_PROCESSES 1024

enum TASK_STATE {
	TASK_STATE_READY,
	TASK_STATE_WAINTING,
	TASK_STATE_FINISHED
};

enum INSTRUCTION_TYPE {
	TASK_INSTRUCTION_EXECUTE,
	TASK_INSTRUCTION_WAIT,
	TASK_INSTRUCTION_FINISH
};



class task_class {
/* class private methods */
private:
	typedef struct instructions_s instructions_t;
	struct instructions_s {
		int argument;         // in seconds
		int command;          // of INSTRUCTION_TYPE
		
		instructions_t *next;
	};
	
	int priority;	              // task priority 
	int time_to_come;             // time when this task will arrive in the 
	                              // timeline
	int state;                    // ready, executing, waiting or finish
	
	int process_id;               // give it a pid
	
	int instruction_pointer;      // current instruction
	instructions_s instructions; // instructions array
	instructions_t *current_instruction;
	
	
/* class public methods */
public:
	int get_next_ready();
	int priority_inc(task_class *, int);
	int priority_dec(task_class *, int);
	int load_instructions(char *);
};

