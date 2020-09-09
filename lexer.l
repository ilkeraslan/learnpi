%option noyywrap nodefault yylineno
%{
#include <pigpio.h>
#include "parser.tab.h"
#include "learnpi.h"
#include "types.h"
#include "functions.h"
%}

%%
"+" |
"-" |
"*" |
"/" |
"%" |
"(" |
")" |
"[" |
"]" |
"{" |
"}" |
"." |
"," |
"=" |
";" |
"|"     { return yytext[0]; }

"OR"|"or"     { return OR_OPERATION; }
"AND"|"and"   { return AND_OPERATION; }
"NOT"|"not"   { return NOT_OPERATION; }

 /* Comparision operators */
">"     { yylval.function_id = 1; return CMP; }
"<"     { yylval.function_id = 2; return CMP; }
"!="    { yylval.function_id = 3; return CMP; }
"=="    { yylval.function_id = 4; return CMP; }
">="    { yylval.function_id = 5; return CMP; }
"<="    { yylval.function_id = 6; return CMP; }

 /* Keywords */
"if"    { return IF;}
"else"  { return ELSE; }
"while" { return WHILE; }

 /* Primitive types */
"bit"               { yylval.type = BIT_TYPE; return TYPE; }
"integer"   		{ yylval.type = INTEGER_TYPE; return TYPE; }
"decimal"           { yylval.type = DECIMAL_TYPE; return TYPE; }
"string"            { yylval.type = STRING_TYPE; return TYPE; }

 /* Composed types */
"LED"               { yylval.type = LED; return COMPLEX_TYPE; }
"BUTTON" 			{ yylval.type = BUTTON; return COMPLEX_TYPE; }
"KEYPAD" 			{ yylval.type = KEYPAD; return COMPLEX_TYPE; }
"BUZZER" 			{ yylval.type = BUZZER; return COMPLEX_TYPE; }
"SERVO_MOTOR" 		{ yylval.type = SERVO_MOTOR; return COMPLEX_TYPE; }

"led_on"                { yylval.function_id = BUILT_IN_LED_ON; return BUILT_IN_FUNCTION; }
"led_off"               { yylval.function_id = BUILT_IN_LED_OFF; return BUILT_IN_FUNCTION; }
"is_button_pressed"     { yylval.function_id = BUILT_IN_IS_BUTTON_PRESSED; return BUILT_IN_FUNCTION; }
"get_pressed_key"       { yylval.function_id = BUILT_IN_GET_PRESSED_KEY; return BUILT_IN_FUNCTION; }
"buzz_start"            { yylval.function_id = BUILT_IN_BUZZ_START; return BUILT_IN_FUNCTION; }
"buzz_stop"             { yylval.function_id = BUILT_IN_BUZZ_STOP; return BUILT_IN_FUNCTION; }
"move_servo_to_angle"   { yylval.function_id = BUILT_IN_MOVE_SERVO_TO_ANGLE; return BUILT_IN_FUNCTION; }
"move_servo_infinitely" { yylval.function_id = BUILT_IN_MOVE_SERVO_INFINITELY; return BUILT_IN_FUNCTION; }
"servo_stop"            { yylval.function_id = BUILT_IN_SERVO_STOP; return BUILT_IN_FUNCTION; }

 /* Names */
[a-zA-Z][a-zA-Z0-9_]*   { yylval.str = strdup(yytext); return NAME; }

[0-9]+         { yylval.value = create_integer_value(atoi(yytext)); return VALUE; }
[0-9]+\.[0-9]+ { yylval.value = create_decimal_value(atof(yytext)); return VALUE; }


\\\n { printf("c> "); } /* ignore line continuation */
\n+  { return EOL; }

[ \t]   /* ignore white space */
.   { yyerror("Mystery character %c\n", *yytext); }
%%