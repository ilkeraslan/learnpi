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
"then"  { return THEN; }
"else"  { return ELSE; }
"while" { return WHILE; }
"do"    { return DO; }

 /* Primitive types */
"bit"               { yylval.type = BIT_TYPE; return TYPE; }
"integer"   		{ yylval.type = INTEGER_TYPE; return TYPE; }
"decimal"           { yylval.type = DECIMAL_TYPE; return TYPE; }
"string"            { yylval.type = STRING_TYPE; return TYPE; }

 /* Names */
[a-zA-Z][a-zA-Z0-9]*   {    struct symbol *helper = NULL;
                            helper = lookup(yytext);
                            yylval.str = (char *)&helper; 
                            return NAME; }

[0-9]+         { yylval.value = create_integer_value(atoi(yytext)); return VALUE; }
[0-9]+\.[0-9]+ { yylval.value = create_decimal_value(atof(yytext)); return VALUE; }

\n { return EOL; }

[ \t]   /* ignore white space */
.   { yyerror("Mystery character %c\n", *yytext); }
%%