#ifndef TYPES_H
#define TYPES_H

enum built_in_function_types { // TODO: Decide builtin functions
  B_on = 1,
  B_off,
  B_blink,
  B_print,
  B_clear,
  B_set_cursor,
  B_pressed,
  B_key,
  B_sound,
  B_mute,
  B_temperature,
  B_light,
  B_rotate,
  B_stop,
  B_detected,
  B_delay
};

// Primitive types
enum type {
    BIT_TYPE,
    INTEGER_TYPE,
    DECIMAL_TYPE,
    STRING_TYPE,
    LED
};

#endif