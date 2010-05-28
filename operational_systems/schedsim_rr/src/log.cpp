/*
 *  log.cpp
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 5/28/10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include "log.h"

void log_class::write(char *log_message, int level){
	switch (level) {
		case LOG_DEBUG:
#ifdef DEBUG
			printf("%s\n", _TIME_);
#endif
		case LOG_INFO:
		case LOG_WARNING:
		case LOG_CRITICAL:
			break;
	}
}