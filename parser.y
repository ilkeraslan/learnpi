%{
#include <stdio.h>
#include <stdlib.h>
#include "learnpi.h"
#include "functions.h"

#define YYDEBUG 1

int yylex();   
%}

// Types used in parser
%union {
  struct ast *ast;
  struct symbol_list *symbol_list;
  struct value *value;
  int integer;
  int function_id;
  char *str;
  int type;
}

%token <type> TYPE COMPLEX_TYPE COMPLEX_TYPE_NOPIN // TODO: change this
%token <integer> INTEGER
%token <str> NAME
%token IF THEN ELSE ENDIF LOOP START UNTIL ENDLOOP

%token <integer> ADDITION SUBTRACTION MULTIPLICATION DIVISION MODULUS OR_OPERATION AND_OPERATION NOT_OPERATION
%token <integer> OPEN_PARANTHESIS CLOSE_PARANTHESIS OPEN_BRACKET CLOSE_BRACKET OPEN_BRACE CLOSE_BRACE DOT COMMA ASSIGN

%nonassoc <function_id> COMPARISION

%type <ast> statement list
%type <symbol_list> list_of_symbol

// Parser initial point
%start learnpi

%%
learnpi: /* nothing */
   | learnpi statement {
      struct value *value = eval($2);
      if(value) {
         treefree($2);
      }
    }
   | learnpi error { yyerrok; yyparse(); }
;

statement: IF exp THEN list ENDIF      { /* nothing */ }
   | IF exp THEN list ELSE list ENDIF  { /* nothing */ }
   | IF exp THEN list ELIF exp THEN list ELSE list ENDIF { /* nothing */ }
   | WHILE exp list { /* nothing */ }
   | WHILE list DO exp { /* nothing */ }
   | exp ';'
;

exp: exp COMPARISION exp         { /* nothing */ }
   | exp '+' exp                 { /* nothing */ }
   | exp '-' exp                 { /* nothing */ }
   | exp '*' exp                 { /* nothing */ }
   | exp '/' exp                 { /* nothing */ }
   | '|' exp                     { /* nothing */ }
   | exp AND_OPERATION exp       { /* nothing */ }
   | exp OR_OPERATION exp        { /* nothing */ }
   | '(' exp ')'                 { /* nothing */ }
   | '-' exp %prec UMINUS        { /* nothing */ }
   | NAME                        { /* nothing */ }
   | NAME '(' explist ')'        { /* nothing */ }
   | NAME '(' ')'                { /* nothing */ }
;

list: /* nothing */ { $$ = NULL; }
   | statement list {
                  if ($2 == NULL) {
                        $$ = $1;
                  } else {
                        $$ = $1;//newast(T_stmtlist, $1, $2);
                  }
               }
;

action: /* nothing */
;

explist: exp
 | exp ',' explist               { /* nothing */ }
;

list_of_symbol: NAME       { $$ = create_symbol_list($1, NULL); }
 | NAME ',' symbol_list { $$ = create_symbol_list($1, $3); }
;

%%