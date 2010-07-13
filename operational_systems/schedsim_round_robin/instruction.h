/*
 *  instruction.h
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 5/30/10.
 *  Copyright 2010. All rights reserved.
 *
 */

#define MAX_PROCESSES 50
#define TRUE  1
#define FALSE 0

enum TASK_STATE {
	TASK_STATE_READY,
	TASK_STATE_WAINTING,
	TASK_STATE_FINISHED
};

enum INSTRUCTION_TYPE {
	TASK_NO_INSTRUCTION,
	TASK_INSTRUCTION_EXECUTE,
	TASK_INSTRUCTION_WAIT,
	TASK_INSTRUCTION_FINISH
};

typedef struct instruction_s instruction_t;
struct instruction_s {
	int duration;          // in seconds
	int instruction_type;  // of INSTRUCTION_TYPE
	
	instruction_t *next;
};

class instruction_class {
private:
	int instruction_pointer;              // current instruction
	instruction_t *current_instruction;
	
public:	
	instruction_s *instructions;         // instructions array

	instruction_class();
	int add_instruction(int, int);
	int get_instruction(int, int);
};