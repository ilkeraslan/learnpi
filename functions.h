#include "learnpi.h"

void yyerror(char *s, ...);

struct val *create_LED(struct val **pin);
struct val *create_COMPLEXTYPE(struct val **pin, int pin_no, int datatype);

struct val *sum(struct val *first, struct val *second);
struct val *subtract(struct val *first, struct val *second);
struct val *multiply(struct val *first, struct val *second);
struct val *divide(struct val *first, struct val *second);
struct val *get_absolute_value(struct val *value);
struct val *change_sign(struct val *value);
struct val *calculate_logical_and(struct val *first, struct val *second);
struct val *calculate_logical_or(struct val *first, struct val *second);
struct val *calculate_greater_than(struct val *first, struct val *second);
struct val *calculate_less_than(struct val *first, struct val *second);
struct val *calculate_equals(struct val *first, struct val *second);
struct val *calculate_greater_equal_than(struct val *first, struct val *second);
struct val *calculate_less_equal_than(struct val *first, struct val *second);

struct val *create_bit_value(int bit_value);
struct val *create_integer_value(int integer_value);
struct val *create_decimal_value(double decimal_value);
struct val *create_string_value(char *string_value);
