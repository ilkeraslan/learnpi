parser: parser.tab.c lex.yy.c
	gcc -Wall -pthread -o learnpi learnpi.c parser.tab.c functions.c -lpigpio -lrt
parser.tab.c: parser.y
	bison -d parser.y
lex.yy.c: lexer.l
	flex lexer.l





	learnpi:	parser.tab.o lex.yy.o
			gcc -Wall -pthread -o learnpi lex.yy.o parser.tab.o functions.c -lpigpio -lrt

parser.tab.o:	parser.tab.c
				gcc -c parser.tab.c

parser.tab.c:	parser.y
				bison -d parser.y

lex.yy.o:	lex.yy.c parser.tab.h
			gcc -c lex.yy.c

lex.yy.c:	lexer.l parser.tab.c
			flex lexer.l




learnpi: lexer.l parser.y functions.c functions.h learnpi.c learnpi.h
        flex lexer.l ; bison -d parser.y ; gcc -Wall -lfl *.c -o learnpi -lm -lpigpio -lpthread;
        rm lex.yy.c parser.tab.*;

