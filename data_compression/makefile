CC=gcc
HUFFMAN_SOURCES=adaptative_huffman.c adaptative_huffman.h
OTHER_SOURCES=log.c log.h
SOURCES=main.c ${HUFFMAN_SOURCES} ${OTHER_SOURCES}

all:
	${CC} -g ${SOURCES} -Wall -DINFO

debug:
	${CC} -g ${SOURCES} -Wall -DDEBUG
