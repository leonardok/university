srcdir = .

CC = gcc
CFLAGS = 
CXX = g++
CXXFLAGS = 

LEX = /usr/bin/flex
YACC = /usr/bin/bison


all: record_to_struct

record_to_struct: lex.record yy.record
	${CC} -o record_to_struct record_to_struct.tab.o lex.record_to_struct.o

lex.record: lexer
	${CC} -c lex.record_to_struct.c -ll
lexer:
	${LEX} -Precord_to_struct record_to_struct.lex

yy.record: parser
	${CC} -c record_to_struct.tab.c -ly
parser: 
	${YACC} --defines record_to_struct.y
