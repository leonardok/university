# libdir
LIB_DIR=include

SOURCES=src/main.cpp src/scheduler.cpp src/task.cpp src/task_queues.cpp

GCC=g++

all:
	${GCC} -I${LIB_DIR} ${SOURCES} -Wall

debug:
	${GCC} -I${LIB_DIR} ${SOURCES} -Wall -DDEBUG