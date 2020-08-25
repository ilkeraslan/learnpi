#define _GNU_SOURCE
#include "learnpi.h"
#include "functions.h"
#include <pigpio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    struct val *result = malloc(sizeof(struct val));

    switch(typeof_value(first)) {
        case INTEGER_TYPE:
            if(typeof_value(second) == INTEGER_TYPE) {
                result->type = INTEGER_TYPE;
                result->datavalue.integer = first->datavalue.integer + second->datavalue.integer;
            } else if(typeof_value(second) == DECIMAL_TYPE) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.integer + second->datavalue.decimal;
            }
            break;
        case DECIMAL_TYPE:
            if(typeof_value(second) == INTEGER_TYPE) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.decimal + second->datavalue.integer;
            } else if(typeof_value(second) == DECIMAL_TYPE) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.decimal + second->datavalue.decimal;
            }
            break;
        case STRING_TYPE:
            if(typeof_value(second) == STRING_TYPE) {
                result->type = STRING_TYPE;
                asprintf(&result->datavalue.string, "%s%s", first->datavalue.string, second->datavalue.string);
            }
            break;
        default:
            yyerror("Sum error between types.");
            free(result);
            return NULL;
    }

    return result;
}

struct val *subtract(struct val *first, struct val *second) {
    struct val *result = malloc(sizeof(struct val));

    switch(typeof_value(first)) {
        case INTEGER_TYPE:
            if(typeof_value(second) == INTEGER_TYPE) {
                result->type = INTEGER_TYPE;
                result->datavalue.integer = first->datavalue.integer - second->datavalue.integer;
            } else if(typeof_value(second) == DECIMAL_TYPE) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.integer - second->datavalue.decimal;
            }
            break;
        case DECIMAL_TYPE:
            if(typeof_value(second) == INTEGER_TYPE) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.decimal - second->datavalue.integer;
            } else if(typeof_value(second) == DECIMAL_TYPE) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.decimal - second->datavalue.decimal;
            }
            break;
        default:
            yyerror("Subtraction error between types.");
            free(result);
            return NULL;
    }

    return result;
}

struct val *multiply(struct val *first, struct val *second) {
    struct val *result = malloc(sizeof(struct val));

    switch(typeof_value(first)) {
        case INTEGER_TYPE:
            if(typeof_value(second) == INTEGER_TYPE) {
                result->type = INTEGER_TYPE;
                result->datavalue.integer = first->datavalue.integer * second->datavalue.integer;
            } else if(typeof_value(second) == DECIMAL_TYPE) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.integer * second->datavalue.decimal;
            }
            break;
        case DECIMAL_TYPE:
            if(typeof_value(second) == INTEGER_TYPE) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.decimal * second->datavalue.integer;
            } else if(typeof_value(second) == DECIMAL_TYPE) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.decimal * second->datavalue.decimal;
            }
            break;
        default:
            yyerror("Multiplication error between types.");
            free(result);
            return NULL;
    }

    return result;
}

struct val *divide(struct val *first, struct val *second) {
    struct val *result = malloc(sizeof(struct val));

    switch(typeof_value(first)) {
        case INTEGER_TYPE:
            if(typeof_value(second) == INTEGER_TYPE && second->datavalue.integer != 0) {
                if(first->datavalue.integer % second->datavalue.integer == 0) {
                    result->type = INTEGER_TYPE;
                    result->datavalue.integer = first->datavalue.integer / second->datavalue.integer;
                } else {
                    result->type = DECIMAL_TYPE;
                    result->datavalue.decimal = (double)first->datavalue.integer / (double)second->datavalue.integer;
                }
            } else if(typeof_value(second) == DECIMAL_TYPE  && second->datavalue.decimal != 0) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = (double)first->datavalue.integer / second->datavalue.decimal;
            }
            break;
        case DECIMAL_TYPE:
            if(typeof_value(second) == INTEGER_TYPE  && second->datavalue.integer != 0) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.decimal / (double)second->datavalue.integer;
            } else if(typeof_value(second) == DECIMAL_TYPE  && second->datavalue.decimal != 0) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.decimal / second->datavalue.decimal;
            }
            break;
        default:
            yyerror("Division error between types.");
            free(result);
            return NULL;
    }

    return result;
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

struct val *create_bit_value(int bit_value) {
    if(bit_value != 0 && bit_value != 1) {
        return NULL;
    }

    struct val *bit_val = malloc(sizeof(struct val));
    bit_val->type = BIT_TYPE;
    bit_val->datavalue.bit = bit_value;
    return bit_val;
}

struct val *create_integer_value(int integer_value) {
    struct val *integer_val = malloc(sizeof(struct val));
    integer_val->type = INTEGER_TYPE;
    integer_val->datavalue.integer = integer_value;
    return integer_val;
}

struct val *create_decimal_value(double decimal_value) {
    struct val *decimal_val = malloc(sizeof(struct val));
    decimal_val->type = DECIMAL_TYPE;
    decimal_val->datavalue.decimal = decimal_value;
    return decimal_val;
}

struct val *create_string_value(char *string_value) {
    struct val *string_val = malloc(sizeof(struct val));
	string_val->type = STRING_TYPE;
    string_val->datavalue.string = strdup(string_value);
    return string_val;
}
