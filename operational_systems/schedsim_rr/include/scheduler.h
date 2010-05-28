/*
 *  class_scheduler.h
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 4/22/10.
 *  Copyright 2010. All rights reserved.
 *
 */

using namespace std;

#include <fstream>
#include "task_queues.h"

class scheduler_class {
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
	int do_scheduling(task_queues_class, task_class *);
	
	/* task related methods */
	int create_task(char *, task_class *);
	
	/* misc class methods */
	void set_time_quantum(int);
};