## LearnPi

A language to learn programming with RaspberryPi.

**Disclaimer: The functionality on the target machine is experimental for the time being. I take no responsability for the electronic issues that may take place during the execution. However, a simulation mode is available by default as you can execute LearnPi on your machine and it will write the simulation results to standard output.**

## Compilation and Execution

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

## Grammar

Each `learnpi` file should end with an EOL (end of line) in order to be executed. Learnpi uses EOL to recognize each statement or expression.
The following is considered a valid `learnpi` program:
```
LED led = 3
BUTTON button = 5
led_on(led)
if(is_button_pressed(button)) {
    led_off(led)
}

```

## Credits

- https://github.com/westes/flex/
- https://www.gnu.org/software/bison/
- https://github.com/joan2937/pigpio