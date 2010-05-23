/*
 *  class_scheduler.h
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 4/22/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

//this is for you to know where 80 colums are ending
//123456789012345678901234567890123456789012345678901234567890123456789012345678


#include <fstream>
#include "task.h"

using namespace std;

class schedule_class {
/* class private methods */		
private:
	int quantum;
	
	int task_to_ready(task_class *task);
	int task_to_waiting(task_class *task);
	int task_preempt(task_class *);
	int task_state(task_class *);
	
/* class public methods */
public:
	/* scheduler related methods */
	int do_scheduling();
	
	/* task related methods */
	int create_task(char *, task_class *);
	
	
};