/*
 *  task_queues.h
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 5/23/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "task.h"

using namespace std;


class task_queues_class {
private:
	task_class *task;
	
public:
	int add_task(task *);
	int rem_task(task *);
};