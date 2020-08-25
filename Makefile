parser: parser.tab.c lex.yy.c
	gcc -Wall -pthread -o learnpi learnpi.c parser.tab.c learnpi.lex.c functions.c -lpigpio -lrt
parcer.tab.c: parser.y
	yacc parser.y
lex.yy.c: lexer.l
	flex lexer.l