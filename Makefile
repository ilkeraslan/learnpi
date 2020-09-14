parser: parser.tab.c lex.yy.c
	gcc -Wall -pthread -o learnpi learnpi.c parser.tab.c learnpi.lex.c functions.c -lpigpio -lm -lrt -lfl
parser.tab.c: parser.y
	bison -d parser.y
lex.yy.c: lexer.l
	flex lexer.l