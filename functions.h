#include "learnpi.h"

#define PI_BAD_GPIO         -3 // GPIO not 0-53
#define NO_KEY_PRESSED      "NO_KEY_IS_PRESSED"

int yylineno;
int yyparse();

void yyerror(char *s, ...);
int get_value_type(struct val *value);

struct val *create_LED(struct val **pin);
struct val *create_COMPLEXTYPE(struct val **pin, int pin_no, int datatype);
struct val *create_BUTTON(struct val **pin);
struct val *create_KEYPAD(struct val ** pin);
struct val *create_BUZZER(struct val ** pin);
struct val *create_SERVO_MOTOR(struct val ** pin);

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
struct val *calculate_not_equals(struct val *first, struct val *second);
struct val *calculate_greater_equal_than(struct val *first, struct val *second);
struct val *calculate_less_equal_than(struct val *first, struct val *second);

struct val *create_bit_value(int bit_value);
struct val *create_integer_value(int integer_value);
struct val *create_decimal_value(double decimal_value);
struct val *create_string_value(char *string_value);

struct val *create_led_value(struct val ** pin, int is_declaration);
struct val *create_button_value(struct val ** pin, int is_declaration);
struct val *create_keypad_value(struct val ** pin, int is_declaration);
struct val *create_buzzer_value(struct val ** pin, int is_declaration);
struct val *create_servo_motor_value(struct val ** pin, int is_declaration);
struct val *create_complex_value(struct val ** pin, int number_of_pins, int datatype);

int led_on(struct val * value);
int led_off(struct val * value);
struct val *is_button_pressed(struct val * value);
struct val *get_pressed_key(struct val * value);
char read_last_pressed_key(struct val * value);
