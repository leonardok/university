/*
 *  task_queues.h
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 5/23/10.
 *  Copyright 2010. All rights reserved.
 *
 */

using namespace std;

#include "task.h"

class task_queues_class {
private:
	task_class *task;
public:
	int add_task(task_class *);
	int rem_task(task_class *);
};