/*
 *  log.h
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 5/28/10.
 *  Copyright 2010. All rights reserved.
 *
 */


enum LOG_LEVEL {
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_CRITICAL		
};


void log_write(const char*, int, int, ...);
