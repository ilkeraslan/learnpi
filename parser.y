%{
#include <stdio.h>
#include <stdlib.h>
#include "learnpi.h"
#include "functions.h"

#define YYDEBUG 1

int yylex();   
%}

%union {
  struct ast *ast;
  struct symbol_list *symbol_list;
  struct val *value;
  int integer;
  int function_id;
  char *str;
  int type;
}

%token <type> TYPE COMPLEX_TYPE COMPLEX_TYPE_NOPIN
%token <integer> INTEGER
%token <str> NAME
%token <value> VALUE
%token <function_id> BUILT_IN_FUNCTION
%token IF THEN ELSE ENDIF START UNTIL EOL WHILE DO

%token <integer> OR_OPERATION AND_OPERATION NOT_OPERATION

%nonassoc <function_id> CMP
%nonassoc UMINUS

%type <ast> statement exp list explist
%type <symbol_list> sym_list

%start learnpi

%%
learnpi: /* nothing */
   | learnpi statement {
      struct val *value = eval($2);
      if(value) {
         treefree($2);
      }
    }
   | learnpi NAME '(' sym_list ')' '=' list EOL {
      dodef($2, $4, $7);
   }
   | learnpi error { yyerrok; yyparse(); }
;

statement: IF exp EOL list EOL               { $$ = newflow(IF_STATEMENT, $2, $4, NULL); }
   | IF exp EOL list ELSE list EOL           { $$ = newflow(IF_STATEMENT, $2, $4, $6); }
   | WHILE exp list EOL                      { $$ = newflow(LOOP_STATEMENT, $2, $3, NULL); }
   | WHILE list DO exp EOL                   { $$ = newflow(LOOP_STATEMENT, $2, $4, NULL); }
   | exp EOL
   | COMPLEX_TYPE NAME EOL                   { $$ = new_declaration($2, $1); }
;

exp: exp CMP exp                             { $$ = new_comparison($2, $1, $3); }
   | exp '+' exp                             { $$ = new_ast_with_children('+', $1, $3); }
   | exp '-' exp                             { $$ = new_ast_with_children('-', $1, $3); }
   | exp '*' exp                             { $$ = new_ast_with_children('*', $1, $3); }
   | exp '/' exp                             { $$ = new_ast_with_children('/', $1, $3); }
   | '|' exp                                 { $$ = new_ast_with_child('|', $2); }
   | exp AND_OPERATION exp                   { $$ = new_ast_with_children(LOGICAL_AND, $1, $3); }
   | exp OR_OPERATION exp                    { $$ = new_ast_with_children(LOGICAL_OR, $1, $3); }
   | '(' exp ')'                             { $$ = $2; }
   | '-' exp %prec UMINUS                    { $$ = new_ast_with_child(UNARY_MINUS, $2); }
   | VALUE                                   { $$ = new_value($1); }
   | NAME                                    { $$ = new_reference($1); }
   | NAME '=' exp                            { $$ = new_assignment($1, $3); }
   | NAME BUILT_IN_FUNCTION '(' ')'          { $$ = new_builtin_function($2, $1, NULL); } /* Node for builtin function without parameters*/
   | NAME BUILT_IN_FUNCTION '(' explist ')'  { $$ = new_builtin_function($2, $1, $4); } /* Node for builtin function with parameters */
   | BUILT_IN_FUNCTION '(' explist ')'       { $$ = new_builtin_function($1, NULL, $3); } /* Node for builtin function without name */
   | NAME '(' ')'                            { $$ = new_user_function($1, NULL); } /* Node for user function call without parameters */
   | NAME '(' explist ')'                    { $$ = new_user_function($1, $3); } /* Node for user function call with parameters */
;

list: /* nothing */ { $$ = NULL; }
   | statement list {
                  if ($2 == NULL) {
                        $$ = $1;
                  } else {
                        $$ = $1;
                  }
               }
;

explist: exp
 | exp ',' explist   { $$ = new_ast_with_children(STATEMENT_LIST, $1, $3); }
;

sym_list: NAME       { $$ = create_symbol_list($1, NULL); }
 | NAME ',' sym_list { $$ = create_symbol_list($1, $3); }
;

%%