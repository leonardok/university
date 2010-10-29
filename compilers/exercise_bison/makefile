# bison -d grammar.y; flex -i lexer.lex; gcc grammar.tab.c lex.yy.c -lfl

all: grammar.o lexer.o
	gcc grammar.tab.c lex.yy.c main.c -o parser -ll

grammar.o:
	bison -d grammar.y

lexer.o:
	flex -i lexer.lex

clean:
	rm grammar.tab.c lex.yy.c grammar.tab.h parser
