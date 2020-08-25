#include "learnpi.h"
#include "functions.h"
#include <pigpio.h>
#include <stdlib.h>
#include <stdio.h>

int yylineno;
int yyparse();

void yyerror(char *s, ...) {
  fprintf(stderr, "Error: %d \n", yylineno);
}

struct val *create_LED(struct val **pin) {
    struct val * result;
    result = create_COMPLEXTYPE(pin, 1, LED);
    pinMode(result->datavalue.GPIO_PIN[0], PI_OUTPUT);
    return result;
}

struct val *create_COMPLEXTYPE(struct val **pin, int pin_no, int datatype) {
    // Allocate memory 
    struct val *result = malloc(sizeof(struct val));

    // Local helper
    int i = 0;

    // Assign the argument datatype to result type    
    result->type = datatype;
    result->datavalue.GPIO_PIN = malloc(pin_no * sizeof(int));

    while(i < pin_no) {
        if(pin[i]->datavalue.GPIO_PIN < 0 || pin[i]->datavalue.GPIO_PIN > 50) {
            yyerror("invalid value %d for pin declaration", pin[i]->datavalue.GPIO_PIN);
            free(result);
            break;
        }

        result->datavalue.GPIO_PIN[i] = pin[i]->datavalue.GPIO_PIN;
        i =+ 1;
    }
    return result;
}

struct val *sum(struct val *first, struct val *second) {
    return NULL;
}

struct val *subtract(struct val *first, struct val *second) {
    return NULL;
}

struct val *multiply(struct val *first, struct val *second) {
    return NULL;
}

struct val *divide(struct val *first, struct val *second) {
    return NULL;
}

struct val *get_absolute_value(struct val *ast) {
    return NULL;
}

struct val *sign(struct val *ast) { // TODO: change name
    return NULL;
}

struct val *calculate_logical_and(struct val *first, struct val *second) {
    return NULL;
}

struct val *calculate_logical_or(struct val *first, struct val *second) {
    return NULL;
}

struct val *calculate_greater_than(struct val *first, struct val *second) {
    return NULL;
}

struct val *calculate_less_than(struct val *first, struct val *second) {
    return NULL;
}

struct val *calculate_equals(struct val *first, struct val *second) {
    return NULL;
}

struct val *calculate_greater_equal_than(struct val *first, struct val *second) {
    return NULL;
}

struct val *calculate_less_equal_than(struct val *first, struct val *second) {
    return NULL;
}