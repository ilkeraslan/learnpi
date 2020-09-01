## LearnPi

A language to learn programming with RaspberryPi.

To compile:
```
bison -d parser.y
flex -o learnpi.lex.c lexer.l
gcc -Wall -pthread -o learnpi learnpi.c parser.tab.c learnpi.lex.c functions.c -lpigpio -lrt -lfl
```

or use the make utility:
```
make
```