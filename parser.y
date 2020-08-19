%{
#include <stdio.h>
#include <stdlib.h>
#include "learnpi.h"
#define YYDEBUG 1

int yylex();   
%}

// Types used in parser
%union {
  struct ast *ast;
  struct symlist *symbol_list;
  struct value *value;
  int integer;
  int function_id;
  char *str;
  int type;
}

%token <integer> INTEGER
%token <str> NAME
%token IF THEN ELSE ENDIF LOOP START UNTIL ENDLOOP

%token <integer> ADDITION SUBTRACTION MULTIPLICATION DIVISION MODULUS OR_OPERATION AND_OPERATION NOT_OPERATION
%token <integer> OPEN_PARANTHESIS CLOSE_PARANTHESIS OPEN_BRACKET CLOSE_BRACKET OPEN_BRACE CLOSE_BRACE DOT COMMA ASSIGN

%token ACTION PARAM ENDACTION

%nonassoc <function_id> CMP

%type <ast> statement list
%type <symbol_list> symlist

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
   | learnpi ACTION NAME PARAM symlist START list ENDACTION {define_function($3, $5, $7);}
   | learnpi ACTION NAME START list ENDACTION {define_function($3, NULL, $5);}
   | learnpi error { yyerrok; yyparse(); }
;

statement: IF exp THEN list ENDIF      { /* nothing */ }
   | IF exp THEN list ELSE list ENDIF  { /* nothing */ }
   | LOOP exp START list ENDLOOP       { /* nothing */ }
   | LOOP START list UNTIL exp ENDLOOP { /* nothing */ }
   | exp ';'
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

exp: exp CMP exp                 { /* nothing */ }
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

action: /* nothing */
;

explist: exp
 | exp ',' explist               { /* nothing */ }
;

symlist: NAME       { $$ = newsymlist($1, NULL); }
 | NAME ',' symlist { $$ = newsymlist($1, $3); }
;