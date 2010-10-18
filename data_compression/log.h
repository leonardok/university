/*
 *  log.h
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 5/28/10.
 *  Copyright 2010. All rights reserved.
 *
 */


enum LOG_LEVEL {
	LOG_DEBUG    = 0,
	LOG_INFO     = 1,
	LOG_WARNING  = 2,
	LOG_CRITICAL = 3		
};


void log_write(const char*, int, int, ...);
