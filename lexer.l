%option noyywrap nodefault yylineno
%{
#include <pigpio.h>
#include "parser.tab.h"
#include "learnpi.h"
#include "types.h"
#include "functions.h"
%}

%%
"+"     { return ADDITION; }
"-"     { return SUBTRACTION; }
"*"     { return MULTIPLICATION; }
"/"     { return DIVISION; }
"%"     { return MODULUS; }
"("     { return OPEN_PARANTHESIS; }
")"     { return CLOSE_PARANTHESIS; }
"["     { return OPEN_BRACKET; }
"]"     { return CLOSE_BRACKET; }
"{"     { return OPEN_BRACE; }
"}"     { return CLOSE_BRACE; }
"."     { return DOT; }
","     { return COMMA; }
"="     { return ASSIGN; }

"OR"|"or"     { return OR_OPERATION; }
"AND"|"and"   { return AND_OPERATION; }
"NOT"|"not"   { return NOT_OPERATION; }

 /* Comparision operators */
">"     { yylval.function_id = 1; return CMP; }
"<"     { yylval.function_id = 2; return CMP; }
"!="    { yylval.function_id = 3; return CMP; }
"="     { yylval.function_id = 4; return CMP; }
">="    { yylval.function_id = 5; return CMP; }
"<="    { yylval.function_id = 6; return CMP; }

 /* Primitive types */
"bit"               { yylval.type = BIT_TYPE; return TYPE; }
"integer"   		    { yylval.type = INTEGER_TYPE; return TYPE; }
"decimal"           { yylval.type = DECIMAL_TYPE; return TYPE; }
"string"            { yylval.type = STRING_TYPE; return TYPE; }

. { yyerror("Mystery character %c\n", *yytext); exit(1); }
%%