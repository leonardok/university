/*
 *  log.h
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 5/28/10.
 *  Copyright 2010. All rights reserved.
 *
 */

using namespace std;

enum LOG_LEVEL {
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_CRITICAL		
};

class log_class {
public:
	void write(char*, int);
};