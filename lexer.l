%option noyywrap nodefault yylineno
%{
#include "parser.tab.h"
#include "learnpi.h"
#include "types.h"

char is_file = '0';
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

 /* Operatori di confronto */
">"     { yylval.function_id = 1; return CMP; }  /* Operatore maggiore */
"<"     { yylval.function_id = 2; return CMP; }  /* Operatore minore */
"!="    { yylval.function_id = 3; return CMP; }  /* Operatore di disuguaglianza */
"="     { yylval.function_id = 4; return CMP; }  /* Operatore di uguaglianza */
">="    { yylval.function_id = 5; return CMP; }  /* Operatore maggiore uguale */
"<="    { yylval.function_id = 6; return CMP; }  /* Operatore minore uguale */

 /* Primitive types */
"bit"               { yylval.type = BIT_TYPE; return TYPE; }
"integer"   		    { yylval.type = INTEGER_TYPE; return TYPE; }
"decimal"           { yylval.type = DECIMAL_TYPE; return TYPE; }
"string"            { yylval.type = STRING_TYPE; return TYPE; }

. { yyerror("Mystery character %c\n", *yytext); exit(1); }
%%

int newfile(char *fn) {
  FILE *f;

  if(strcmp(fn, "stdin")) {
    // Found files
    f = fopen(fn, "r");
		is_file = '1';
  } else {
    // Use standard input
    f = stdin;
		is_file = '0';
  }

  if(!f) {
    perror(fn);
    return -1;
  }

  yyin = f;

  return 1;
}

int main(int argc, char **argv) {

	symstack = calloc(1, sizeof(struct symtable_stack));
	symstack->next = NULL;
	symstack->symtab = NULL;

	initialize_symbol_table_stack();

	newfile("stdin");
	for(int i = 1; i < argc; i++) {
		if(checkSuffix(argv[1], ".learnpi") == 1 && newfile(argv[i])) {
			yyparse();
		} else {
			fprintf(stderr, "Not a valid file.\n");
		}
	}

	free_symbol_table_stack();
}

int checkSuffix(const char *str, const char *suffix) {
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}