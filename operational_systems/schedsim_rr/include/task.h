/*
 *  task.h
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 4/22/10.
 *  Copyright 2010. All rights reserved.
 *
 */

using namespace std;

#define MAX_PROCESSES 1024

enum TASK_STATE {
	TASK_READY,
	TASK_WAINTING,
	TASK_FINISH
};

enum INSTRUCTION_TYPE {
	PROCESS,
	SLEEP
};


class task_class {
/* class private methods */
private:
	struct instructions_s {
		int duration;         // in seconds
		int instruction;      // of INSTRUCTION_TYPE
	};
	typedef struct instructions_s instructions_t;
	
	int priority;	              // task priority 
	int time_to_come;             // time when this task will arrive in the 
	                              // timeline
	int state;                    // ready, executing, waiting or finish
	
	int process_id;               // give it a pid
	
	int instruction_pointer;      // current instruction
	instructions_t *instructions; // instructions array
	
	
/* class public methods */
public:
	int get_next_ready();
	int priority_inc();
	int priority_dec();
	int load_instructions();
};