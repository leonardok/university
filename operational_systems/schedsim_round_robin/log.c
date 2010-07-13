/*
 *  log.cpp
 *  schedsim_rr
 *
 *  Created by Leonardo Korndorfer on 5/28/10.
 *  Copyright 2010. All rights reserved.
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "log.h"

/*
 * log_write
 *
 * overview:
 *   write logs
 *
 * input:
 *   1. the message to print
 *   2. the indentation level in what to put the message
 *   3. the log level of the message
 *   4. variable list of arguments. this is the arguments for the
 *      formatted message that can be the same as printf
 *
 * output:
 *   void
 *
 * example:
 *   log_write("Hello %s%c!", 0, LOG_DEBUG, "worl", 'd');
 */
void log_write(const char *log_message, int indent_level, int log_level, ...){
#ifdef LOG_DEBUG
        declared_level = LOG_DEBUG;
#endif
#ifdef LOG_WARNING
        declared_level = LOG_WARNING;
#endif
#ifdef LOG_INFO
        declared_level = LOG_INFO;
#endif
#ifdef CRITICAL
        declared_level = LOG_CRITICAL;
#endif

        va_list ap;
        int d;
	int i;
        char c, *s;

	/* description of malloc 	 
	 * times 2 characters because we are printing "--" ---------------+
	 * indentation level of log string ---------------------+         |
	 * get_size of char ---------------------+              |         |
	 *                                       |              |         |
	 *                                 /-----------\   /----------\   | */
	char *indent_string = (char*)malloc(sizeof(char) * indent_level * 2);
	indent_string = strcpy(indent_string, "--");
	
	for (i=1; i<=indent_level; i++) {
		indent_string = strcat(indent_string, "--");
	}
	
	switch (log_level) {
		case LOG_DEBUG:
		case LOG_INFO:
		case LOG_WARNING:
		case LOG_CRITICAL:
			printf("[%s %s] %s ", __DATE__, __TIME__, indent_string);
                        break;
	}
	
	free(indent_string);

        va_start(ap, log_level);

        /* we can copy the va_args to another var ap2 with va_copy
         * i am not doing this as there is no need to reiterate on 
         * va_args 
         */
        while (*log_message)
                if(*log_message== '%'){
                        *log_message++;
                        switch(*log_message++) {
                        case 's':                       /* string */
                                s = va_arg(ap, char *);
                                printf("%s", s);
                                break;
                        case 'd':                       /* int */
                                d = va_arg(ap, int);
                                printf("%d", d);
                                break;
                        case 'c':                       /* char */
                                /* Note: char is promoted to int. */
                                c = va_arg(ap, int);
                                printf("%c", c);
                                break;
                        }
                }
                else {
                         printf("%c", *log_message++);
                }
        va_end(ap);
	
        printf("\n");
}
