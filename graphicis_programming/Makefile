# WARNING: If under VirtualBox use: export LIBGL_ALWAYS_INDIRECT=1


ifeq ($(OS),Windows_NT)
    CCFLAGS += -D WIN32
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CCFLAGS += -D LINUX
	LDFLAGS += -lglut -lGL -lGLU
    endif
    ifeq ($(UNAME_S),Darwin)
        CCFLAGS += -D OSX
	LDFLAGS += -framework glut -framework opengl
    endif
endif



fractal_leo:
	g++ fractal_leo.cpp ${CCFLAGS} ${LDFLAGS} -o fractal_leo

snake:
	g++ gl_snake.cpp ${CCFLAGS} ${LDFLAGS} -o snake
