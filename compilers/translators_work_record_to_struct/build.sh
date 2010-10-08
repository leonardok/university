#!/bin/sh

./clean.sh

bison -d record_to_struct.y
flex record_to_struct.lex
gcc -DYYDEBUG lex.yy.c record_to_struct.tab.c  -ll

