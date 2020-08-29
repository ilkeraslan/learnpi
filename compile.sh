#!/bin/bash
bison -d parser.y
flex lexer.l
gcc -Wall -lfl *.c -o learnpi -lm -lpigpio -lpthread;