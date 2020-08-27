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
%token <value> VALUE
%token <function_id> BUILT_IN_FUNCTION
%token IF THEN ELSE ENDIF LOOP START UNTIL ENDLOOP EOL

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

statement: IF exp EOL list ENDIF      { /* nothing */ }
   | IF exp EOL list ELSE list ENDIF  { /* nothing */ }
   | IF exp EOL list ELIF exp EOL list ELSE list ENDIF { /* nothing */ }
   | WHILE exp list { /* nothing */ }
   | WHILE list DO exp { /* nothing */ }
   | exp ';'
;

exp: exp COMPARISION exp                     { $$ = new_comparision($2, $1, $3); }
   | exp '+' exp                             { $$ = new_ast_with_children('+', $1, $3); }
   | exp '-' exp                             { $$ = new_ast_with_children('-', $1, $3); }
   | exp '*' exp                             { $$ = new_ast_with_children('*', $1, $3); }
   | exp '/' exp                             { $$ = new_ast_with_children('/', $1, $3); }
   | '|' exp                                 { $$ = new_ast_with_child(ABSOLUTE_VALUE, $2); }
   | exp AND_OPERATION exp                   { $$ = new_ast_with_children(LOGICAL_AND, $1, $3); }
   | exp OR_OPERATION exp                    { $$ = new_ast_with_children(LOGICAL_OR, $1, $3); }
   | '(' exp ')'                             { $$ = $2; }
   | '-' exp %prec UMINUS                    { $$ = new_ast_with_child(UNARY_MINUS, $2); }
   | VALUE                                   { $$ = new_value($1); }
   | NAME                                    { $$ = new_reference($1); }
   | NAME BUILT_IN_FUNCTION '(' ')'          { $$ = new_builtin_function($2, $1, NULL); }
   | NAME BUILT_IN_FUNCTION '(' explist ')'  { $$ = new_builtin_function($2, $1, $4); }
   | BUILT_IN_FUNCTION '(' explist ')'       { $$ = new_builtin_function($1, NULL, $3); }
   | NAME '(' explist ')'                    { $$ = newcall($1, $3); }
   | NAME '(' ')'                            { $$ = newcall($1, NULL); }
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