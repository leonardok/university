/*
 *  task.c
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 4/22/10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>


#include "generic.h"
#include "task.h"
#include "log.h"


#define INDENT_LEVEL 1

extern task_t *task_list;
extern task_t *task_list_head;
extern int jiffies;

/*
 * create_task
 *
 * overview:
 *   this function creates a new task
 *
 * input:
 *   1. 
 *
 * output:
 *   
 */
int get_argument(int fp, int offset){
	char argument[5];
	char buf[1];
	int  i = 0;
	
	lseek(fp, offset, SEEK_SET);
	while (read(fp, buf, 1)) {
		if (buf[0] == ' ' || buf[0] == '\n') {
			if (i == 0) continue;
			break;
		}
		argument[i++] = buf[0];
	}
	argument[i] = '\0';

	return atoi(argument);
}


int add_instruction(task_t **task_ptr, int instruction_type, int duration){
	instruction_t *instruction_ptr        = (*task_ptr)->instruction;
	instruction_t *instruction_parent_ptr = instruction_ptr;
	
	while (instruction_ptr) {
		instruction_parent_ptr = instruction_ptr;
		instruction_ptr        = instruction_ptr->next;
	}
	
	instruction_ptr = malloc(sizeof(instruction_t));

	if ((*task_ptr)->curr_instruction == NULL) {
		(*task_ptr)->curr_instruction = instruction_ptr;
		(*task_ptr)->instruction      = instruction_ptr;
	}
	
	instruction_ptr->instruction_type = instruction_type;
	instruction_ptr->duration         = duration;
	instruction_ptr->next             = NULL;
	
	if (instruction_parent_ptr) {
		instruction_parent_ptr->next = instruction_ptr;
	}
		
	return TRUE;
}

/*
** create_task
**
** overview:
**   this function creates a new task. it also set the state of the task to 
**   TASK_STATE_READY when time_to_come == 0
**
** input:
**   1. the task list
**
** output:
**   
*/
int create_task(char *file_path){
	/* local variables */
	task_t *task_ptr        = task_list;
	task_t *task_parent_ptr = NULL;
	
	int  fp;
	int  bytes_read;
	char word[20];
	char buf[1];

	int  i = 0;
	
	/*
	** walk to through task_list until task_ptr turns NULL
	** then allocate a new task
	*/
	while (task_ptr) {
		task_parent_ptr = task_ptr;
		task_ptr        = task_ptr->next;
	}
	
	/* initialize task internals */
	task_ptr                   = malloc(sizeof(task_t));
	task_ptr->state            = TASK_STATE_TO_COME;
	task_ptr->instruction      = NULL;
	task_ptr->curr_instruction = NULL;
	task_ptr->next             = NULL;
	

	if (task_list_head ==  NULL) {
		task_list      = task_ptr;
		task_list_head = task_ptr;
	}

	if (task_parent_ptr) {
		task_parent_ptr->next = task_ptr;
	}
	
	/* open file */
	if(!(fp = open(file_path, O_RDONLY))){
		printf("the file %s could not be openned, please review before you continue\n", 
		       file_path);
	}
	
	/* set task instructions and time to come */
	while (TRUE) {
		bytes_read = read(fp, buf, 1);
		
		/* if no reading was done it is because file ended */
		if (bytes_read == 0) {
			break;
		}
		
		/* if char is a space or line break word is complete */
		if (buf[0] == ' ' || buf[0] == '\n') {
			word[i] = '\0';
			
			i = 0;
			
			/* if word is time to come get argument and set it on main */
			if (!strcmp("time_to_come", word)) {
				int offset = (int) lseek(fp, 0, SEEK_CUR);
				task_ptr->time_to_come = get_argument(fp, offset);
		
				if (task_ptr->time_to_come == 0) {
					task_ptr->state = TASK_STATE_READY;
				}
			}
			
			
			/* if word is another get argument and add new instruction */
			else if (!strcmp("execute", word)) {
				int offset = (int) lseek(fp, 0, SEEK_CUR);
				add_instruction(&task_ptr, TASK_INSTRUCTION_EXECUTE, get_argument(fp, offset));
			}
			else if (!strcmp("wait", word)) {
				int offset = (int) lseek(fp, 0, SEEK_CUR);
				add_instruction(&task_ptr, TASK_INSTRUCTION_WAIT, get_argument(fp, offset));
			}
			else if (!strcmp("finish", word)) {
				int offset = (int) lseek(fp, 0, SEEK_CUR);
				add_instruction(&task_ptr, TASK_INSTRUCTION_FINISH, get_argument(fp, offset));
			}				
		}
		else {
			/* if get's here the word is comming */
			word[i++] = buf[0];
		}
		
	}	
	close(fp);
	
	return TRUE;
}

void show_process_status_header(void) {
	task_t *task_local_ptr = task_list_head;

	printf("procs:\t");
	int i = 0;
	while (task_local_ptr) {
		printf("P%d ", i);
		i++;
		task_local_ptr = task_local_ptr->next;		
	}
	printf("\n");
}

void show_proccess_time(void){
	task_t *task_local_ptr = task_list_head;
	
	printf("CPU:\t");
	while (task_local_ptr) {
		char str[5];
		sprintf(str, "%d", task_local_ptr->process_time);
		if (strlen(str) == 2) {
			printf("%d ", task_local_ptr->process_time);
		}
		else
			printf("%d  ", task_local_ptr->process_time);
		
		task_local_ptr = task_local_ptr->next;		
	}
	printf("\n");	
}

void show_sleeping_time(void){
	task_t *task_local_ptr = task_list_head;
	
	printf("sleep:\t");
	while (task_local_ptr) {
		char str[5];
		sprintf(str, "%d", task_local_ptr->sleep_time);
		if (strlen(str) == 2) {
			printf("%d ", task_local_ptr->sleep_time);
		}
		else
			printf("%d  ", task_local_ptr->sleep_time);

		task_local_ptr = task_local_ptr->next;		
	}
	printf("\n");	
}


void show_waiting_time(void){
	task_t *task_local_ptr = task_list_head;
	
	printf("wait:\t");
	while (task_local_ptr) {
		char str[5];
		sprintf(str, "%d", task_local_ptr->waiting_time);
		if (strlen(str) == 2) {
			printf("%d ", task_local_ptr->waiting_time);
		}
		else
			printf("%d  ", task_local_ptr->waiting_time);
		
		task_local_ptr = task_local_ptr->next;		
	}
	printf("\n");	
}


void show_process_status(void) {
	task_t *task_local_ptr = task_list_head;
	
	printf("%d\t", jiffies);
	while (task_local_ptr) {
		switch (task_local_ptr->state) {
			case 0:
				printf("-  ");
				break;
			case 1:
				printf("R  ");
				break;
			case 2:
				printf("W  ");
				break;
			case 3:
				printf("F  ");
				break;
			case 4:
				printf("E  ");
				break;
			default:
				break;
		}
		task_local_ptr = task_local_ptr->next;		
	}
	printf("\n");
}










/*EOF*/
