## LearnPi

This is a project to learn programming with RaspberryPi via a basic language.

To compile:
- `bison -d parser.y`
- `flex -o learnpi.lex.c lexer.l`
- `gcc -Wall -pthread -o learnpi learnpi.c parser.tab.c learnpi.lex.c functions.c -lpigpio -lrt`

or use the make utility:
`make`