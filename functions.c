#include "learnpi.h"
#include "functions.h"
#include <pigpio.h>

struct val *create_LED(struct val ** pin) {
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