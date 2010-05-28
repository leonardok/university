/*
 *  task.cpp
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 4/22/10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include <iostream>
#include "task.h"

/*
 * task_class::get_next_ready
 *
 * overview:
 *   this function is yet to be proven useful
 *
 * input:
 *   1. 
 *
 * output:
 *   
 */
int task_class::get_next_ready(){	
	return true;
}

/*
 * task_class::priority_inc
 *
 * overview:
 *   increase the priority of a task by increase_factor.
 *   i.e. new priority = old priority + increase_factor
 *
 * input:
 *   1. the task to increase the priority
 *   2. the factor to sum with the current priority
 *
 * output:
 *   true if could increase the task priority
 *   false if could not increase
 */
int task_class::priority_inc(task_class *task, 
			     int increase_factor){
	return true;
}

/*
 * task_class::priority_dec
 *
 * overview:
 *   decrease the priority of a task by decrease_factor.
 *
 * input:
 *   1. the task to decrease the priority
 *   2. the factor to subtract with the current priority
 *
 * output:
 *   true if could decrease the task priority
 *   false if could not decrease
 */
int task_class::priority_dec(task_class *task, 
			     int decrease_factor){
	return true;
}

/*
 * task_class::load_instructions
 *
 * overview:
 *   this method loads a set of instructions to a task object pointed by 
 *   argument #1. The instructions are to be inside the file in the following
 *   format:
 *     process 10
 *     sleep   5
 *     process 3
 *     sleep   8
 *     finish
 *
 *   more than one white spaces are to be ignored by parser.
 *
 * input:
 *   1. a task pointer
 *   2. a file path which to collect the instructions from
 *
 * output:
 *   true if could load the instructions
 *   false if could not
 */
int task_class::load_instructions(char *file_path){
#ifdef DEBUG
	printf("\t\tloading instructions\n");
#endif
	fstream fp;
	
	fp.open(file_path, ios::in);
	if(!fp){
		printf("not possible to read from file\n");
		return false;
	}
	
	char buff[512];
	while (fp >> buff) {
		if (buff[0] == '#' || strlen(buff) <= 1) {
			continue;
		}
		
		
		/* new instruction */
		instructions_s new_instruction;
		
		if (!strcmp(buff, "time_to_come")) {
			printf("\t\ttime to come is     ", atoi(buff));
		}
		else if (!strcmp(buff, "execute")) {
			printf("\t\texecute instruction ");
			new_instruction.command  = TASK_INSTRUCTION_EXECUTE;
		}
		else if (!strcmp(buff, "wait")) {
			printf("\t\twait instruction    ");
			new_instruction.command  = TASK_INSTRUCTION_WAIT;
		}
		else {
			printf("\t\tfinish instruction  ");
			new_instruction.command  = TASK_INSTRUCTION_FINISH;
		}
		fp >> buff;
		new_instruction.argument = atoi(buff);
		printf("%s\n", buff);


		
	}
	printf("\n");

	
	return true;
}













/*EOF*/