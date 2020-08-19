## LearnPi

This is a project to learn programming with RaspberryPi via a basic language.

To compile:
- `bison -d parser.y`
- `flex -o learnpi.lex.c lexer.l`
- `gcc -o learnpi parser.tab.c learnpi.lex.c learnpi.c`