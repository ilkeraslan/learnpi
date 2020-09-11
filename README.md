## LearnPi

A language to learn programming with RaspberryPi.

To compile:
```
bison -d parser.y
flex -o learnpi.lex.c lexer.l
gcc -Wall -pthread -o learnpi learnpi.c parser.tab.c learnpi.lex.c functions.c -lpigpio -lm -lrt -lfl
```

or use the make utility:
```
make
```

To be able to use the language, the file should have an extension of `.learnpi`.
For example, the following command should be able to run your specified program:
```
./learnpi example.learnpi
```

Each `learnpi` file should end with an EOL (end of line) in order to be executed. Learnpi uses EOL to recognize each statement or expression.
The following is considered a valid `learnpi` program:
```
x = 2
y = x + 4

```
