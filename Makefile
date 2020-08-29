SHELL := /bin/bash
learnpi: lexer.l parser.y functions.c functions.h learnpi.c learnpi.h
	flex lexer.l ; bison -d parser.y ; gcc -Wall -lfl *.c -o learnpi -lm -lpigpio -lpthread; 
	rm lex.yy.c parser.tab.*;