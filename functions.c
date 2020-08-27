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

int get_value_type(struct val *value) {
	if(value) {
  	    return value->type;
	} else {
		return -1;
	}
}

struct val *create_LED(struct val **pin) {
    struct val * result;
    result = create_COMPLEXTYPE(pin, 1, LED);
    int currentMode = gpioSetMode(result->datavalue.GPIO_PIN[0], 1);
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

    switch(get_value_type(first)) {
        case INTEGER_TYPE:
            if(get_value_type(second) == INTEGER_TYPE) {
                result->type = INTEGER_TYPE;
                result->datavalue.integer = first->datavalue.integer + second->datavalue.integer;
            } else if(get_value_type(second) == DECIMAL_TYPE) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.integer + second->datavalue.decimal;
            }
            break;
        case DECIMAL_TYPE:
            if(get_value_type(second) == INTEGER_TYPE) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.decimal + second->datavalue.integer;
            } else if(get_value_type(second) == DECIMAL_TYPE) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.decimal + second->datavalue.decimal;
            }
            break;
        case STRING_TYPE:
            if(get_value_type(second) == STRING_TYPE) {
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

    switch(get_value_type(first)) {
        case INTEGER_TYPE:
            if(get_value_type(second) == INTEGER_TYPE) {
                result->type = INTEGER_TYPE;
                result->datavalue.integer = first->datavalue.integer - second->datavalue.integer;
            } else if(get_value_type(second) == DECIMAL_TYPE) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.integer - second->datavalue.decimal;
            }
            break;
        case DECIMAL_TYPE:
            if(get_value_type(second) == INTEGER_TYPE) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.decimal - second->datavalue.integer;
            } else if(get_value_type(second) == DECIMAL_TYPE) {
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

    switch(get_value_type(first)) {
        case INTEGER_TYPE:
            if(get_value_type(second) == INTEGER_TYPE) {
                result->type = INTEGER_TYPE;
                result->datavalue.integer = first->datavalue.integer * second->datavalue.integer;
            } else if(get_value_type(second) == DECIMAL_TYPE) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.integer * second->datavalue.decimal;
            }
            break;
        case DECIMAL_TYPE:
            if(get_value_type(second) == INTEGER_TYPE) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.decimal * second->datavalue.integer;
            } else if(get_value_type(second) == DECIMAL_TYPE) {
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

    switch(get_value_type(first)) {
        case INTEGER_TYPE:
            if(get_value_type(second) == INTEGER_TYPE && second->datavalue.integer != 0) {
                if(first->datavalue.integer % second->datavalue.integer == 0) {
                    result->type = INTEGER_TYPE;
                    result->datavalue.integer = first->datavalue.integer / second->datavalue.integer;
                } else {
                    result->type = DECIMAL_TYPE;
                    result->datavalue.decimal = (double)first->datavalue.integer / (double)second->datavalue.integer;
                }
            } else if(get_value_type(second) == DECIMAL_TYPE  && second->datavalue.decimal != 0) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = (double)first->datavalue.integer / second->datavalue.decimal;
            }
            break;
        case DECIMAL_TYPE:
            if(get_value_type(second) == INTEGER_TYPE  && second->datavalue.integer != 0) {
                result->type = DECIMAL_TYPE;
                result->datavalue.decimal = first->datavalue.decimal / (double)second->datavalue.integer;
            } else if(get_value_type(second) == DECIMAL_TYPE  && second->datavalue.decimal != 0) {
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

struct val *get_absolute_value(struct val *value) {
    struct val *result = malloc(sizeof(struct val));

    switch (get_value_type(value)) {
        case INTEGER_TYPE:
            if(value->datavalue.integer < 0) {
                result->datavalue.integer = -(value->datavalue.integer);
            } else {
                result->datavalue.integer = value->datavalue.integer;
            }
            break;
        case DECIMAL_TYPE:
            if(value->datavalue.integer < 0) {
                result->datavalue.decimal = -(value->datavalue.decimal);
            } else {
                result->datavalue.decimal = value->datavalue.decimal;
            }
            break;
        default:
            yyerror("Absolute value error");
            free(result);
    }

    result->type = get_value_type(value);
    return result;
}

struct val *change_sign(struct val *value) {
    struct val *result = malloc(sizeof(struct val));
    
    switch (get_value_type(value)) {
        case INTEGER_TYPE:
            result->datavalue.integer = -(value->datavalue.integer);
            break;
        case DECIMAL_TYPE:
            result->datavalue.decimal = -(value->datavalue.decimal);
            break;
        default:
            yyerror("Sign change error");
            free(result);
    }

    result->type = get_value_type(value);
    return result;
}

struct val *calculate_logical_and(struct val *first, struct val *second) {
    struct val * result = malloc(sizeof(struct val));

    if(get_value_type(first) == BIT_TYPE && get_value_type(second) == BIT_TYPE) {
        result->type = BIT_TYPE;
        result->datavalue.bit = first->datavalue.bit && second->datavalue.bit;
    } else {
        yyerror("Logical AND error");
        free(result);
    }

    return result;  
}

struct val *calculate_logical_or(struct val *first, struct val *second) {
    struct val * result = malloc(sizeof(struct val));

    if(get_value_type(first) == BIT_TYPE && get_value_type(second) == BIT_TYPE) {
        result->type = BIT_TYPE;
        result->datavalue.bit = first->datavalue.bit || second->datavalue.bit;
    } else {
        yyerror("Logical OR error");
        free(result);
    }

    return result; 
}

struct val *calculate_greater_than(struct val *first, struct val *second) {
    struct val * result = malloc(sizeof(struct val));
    int helper;

    switch(get_value_type(first)) {
        case INTEGER_TYPE:
            if(get_value_type(second) == INTEGER_TYPE) {
                result->datavalue.bit = first->datavalue.integer > second->datavalue.integer;
            } else if(get_value_type(second) == DECIMAL_TYPE) {
                result->datavalue.decimal = first->datavalue.integer > second->datavalue.decimal;
            }
            break;
        case DECIMAL_TYPE:
            if(get_value_type(second) == INTEGER_TYPE) {
                result->datavalue.decimal = first->datavalue.decimal > second->datavalue.integer;
            } else if(get_value_type(second) == DECIMAL_TYPE) {
                result->datavalue.bit = first->datavalue.decimal > second->datavalue.decimal;
            }
            break;
        case STRING_TYPE:
            if(get_value_type(second) == STRING_TYPE) {
                // String comparision
                helper = strcmp(first->datavalue.string, second->datavalue.string);

                // Check if strings are equal
                if(helper == 1) {
                    result->datavalue.bit = 1;
                } else {
                    result->datavalue.bit = 0;
                }
            }
            break;
        default:
            yyerror("Cannot calculate if greater than.");
            free(result);
    }

    result->type = BIT_TYPE;
    return result;
}

struct val *calculate_less_than(struct val *first, struct val *second) {
    struct val * result = malloc(sizeof(struct val));
    int helper;

    switch(get_value_type(first)) {
        case INTEGER_TYPE:
            if(get_value_type(second) == INTEGER_TYPE) {
                result->datavalue.bit = first->datavalue.integer < second->datavalue.integer;
            } else if(get_value_type(second) == DECIMAL_TYPE) {
                result->datavalue.decimal = first->datavalue.integer < second->datavalue.decimal;
            }
            break;
        case DECIMAL_TYPE:
            if(get_value_type(second) == INTEGER_TYPE) {
                result->datavalue.decimal = first->datavalue.decimal < second->datavalue.integer;
            } else if(get_value_type(second) == DECIMAL_TYPE) {
                result->datavalue.bit = first->datavalue.decimal < second->datavalue.decimal;
            }
            break;
        case STRING_TYPE:
            if(get_value_type(second) == STRING_TYPE) {
                // String comparision
                helper = strcmp(first->datavalue.string, second->datavalue.string);

                // Check if strings are equal
                if(helper == -1) {
                    result->datavalue.bit = 1;
                } else {
                    result->datavalue.bit = 0;
                }
            }
            break;
        default:
            yyerror("Cannot calculate if less than.");
            free(result);
    }

    result->type = BIT_TYPE;
    return result;
}

struct val *calculate_equals(struct val *first, struct val *second) {
    struct val * result = malloc(sizeof(struct val));
    int helper;

    switch(get_value_type(first)) {
        case INTEGER_TYPE:
            if(get_value_type(second) == INTEGER_TYPE) {
                result->datavalue.bit = first->datavalue.integer == second->datavalue.integer;
            } else if(get_value_type(second) == DECIMAL_TYPE) {
                result->datavalue.decimal = first->datavalue.integer == second->datavalue.decimal;
            }
            break;
        case DECIMAL_TYPE:
            if(get_value_type(second) == INTEGER_TYPE) {
                result->datavalue.decimal = first->datavalue.decimal == second->datavalue.integer;
            } else if(get_value_type(second) == DECIMAL_TYPE) {
                result->datavalue.bit = first->datavalue.decimal == second->datavalue.decimal;
            }
            break;
        case STRING_TYPE:
            if(get_value_type(second) == STRING_TYPE) {
                // String comparision
                helper = strcmp(first->datavalue.string, second->datavalue.string);

                // Check if strings are equal
                if(helper == 0) {
                    result->datavalue.bit = 1;
                } else {
                    result->datavalue.bit = 0;
                }
            }
            break;
        default:
            yyerror("Cannot calculate if equals.");
            free(result);
    }

    result->type = BIT_TYPE;
    return result;
}

struct val *calculate_greater_equal_than(struct val *first, struct val *second) {
    struct val * result = malloc(sizeof(struct val));
    int helper;

    switch(get_value_type(first)) {
        case INTEGER_TYPE:
            if(get_value_type(second) == INTEGER_TYPE) {
                result->datavalue.bit = first->datavalue.integer >= second->datavalue.integer;
            } else if(get_value_type(second) == DECIMAL_TYPE) {
                result->datavalue.decimal = first->datavalue.integer >= second->datavalue.decimal;
            }
            break;
        case DECIMAL_TYPE:
            if(get_value_type(second) == INTEGER_TYPE) {
                result->datavalue.decimal = first->datavalue.decimal >= second->datavalue.integer;
            } else if(get_value_type(second) == DECIMAL_TYPE) {
                result->datavalue.bit = first->datavalue.decimal >= second->datavalue.decimal;
            }
            break;
        case STRING_TYPE:
            if(get_value_type(second) == STRING_TYPE) {
                // String comparision
                helper = strcmp(first->datavalue.string, second->datavalue.string);

                // Check if strings are equal
                if(helper == 0 || helper == 1) {
                    result->datavalue.bit = 1;
                } else {
                    result->datavalue.bit = 0;
                }
            }
            break;
        default:
            yyerror("Cannot calculate if greater equal than.");
            free(result);
    }

    result->type = BIT_TYPE;
    return result;
}

struct val *calculate_less_equal_than(struct val *first, struct val *second) {
    struct val * result = malloc(sizeof(struct val));
    int helper;

    switch(get_value_type(first)) {
        case INTEGER_TYPE:
            if(get_value_type(second) == INTEGER_TYPE) {
                result->datavalue.bit = first->datavalue.integer <= second->datavalue.integer;
            } else if(get_value_type(second) == DECIMAL_TYPE) {
                result->datavalue.decimal = first->datavalue.integer <= second->datavalue.decimal;
            }
            break;
        case DECIMAL_TYPE:
            if(get_value_type(second) == INTEGER_TYPE) {
                result->datavalue.decimal = first->datavalue.decimal <= second->datavalue.integer;
            } else if(get_value_type(second) == DECIMAL_TYPE) {
                result->datavalue.bit = first->datavalue.decimal <= second->datavalue.decimal;
            }
            break;
        case STRING_TYPE:
            if(get_value_type(second) == STRING_TYPE) {
                // String comparision
                helper = strcmp(first->datavalue.string, second->datavalue.string);

                // Check if strings are equal
                if(helper == 0 || helper == -1) {
                    result->datavalue.bit = 1;
                } else {
                    result->datavalue.bit = 0;
                }
            }
            break;
        default:
            yyerror("Cannot calculate if less equal than.");
            free(result);
    }

    result->type = BIT_TYPE;
    return result;
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

/*
* Sets the GPIO level to on.
* gpio: 0-53
* level: 0-1
*/
int led_on(struct val * value) {
    return gpioWrite(value->datavalue.GPIO_PIN[0], 1);
}

/*
* Sets the GPIO level to off.
* gpio: 0-53
* level: 0-1
*/
int led_off(struct val * value) {
    return gpioWrite(value->datavalue.GPIO_PIN[0], 0);
}
