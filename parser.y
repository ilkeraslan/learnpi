// Types used in parser
%union {
  struct ast *ast;
  int integer;
  struct symlist *symbol_list;
  int function_id;
  struct value *value;
  char *str;
  int type;
}

%token <integer> INTEGER

%token <integer> ADDITION SUBTRACTION MULTIPLICATION DIVISION MODULUS OR_OPEPARTION AND_OPEPARTION NOT_OPEPARTION
%token <integer> OPEN_PARANTHESIS CLOSE_PARANTHESIS OPEN_BRACKET CLOSE_BRACKET OPEN_BRACE CLOSE_BRACE DOT COMMA ASSIGN

// Parser initial point
%start learnpi

%%
learnpi: /* nothing */
  | learnpi statement {
      if(debug) dumpast($2, 0);
      struct value *value = eval($2);
      if(value) {
         treefree($2);
      }
    }
   | learnpi ACTION NAME PARAM symlist START list ENDACTION {
                                                      dodef($3, $5, $7);
                                                   }
   | learnpi ACTION NAME START list ENDACTION {
                                                      dodef($3, NULL, $5);
                                                   }
   | learnpi error { yyerrok; yyparse(); }
;